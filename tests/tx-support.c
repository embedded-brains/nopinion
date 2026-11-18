/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "tx-support.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtems/test.h>

#include "nopinion.h"

#define ELF_HEADER_SIZE 52

#define SECTION_HEADER_SIZE 40

#define SYMBOL_SIZE 16

#define RELA_SIZE 12

#define REL_SIZE 8

static const char section_names[] =
  "\0.text\0.symtab\0.strtab\0.shstrtab\0.rela.text";

#define NAME_TEXT 1

#define NAME_SYMTAB 7

#define NAME_STRTAB 15

#define NAME_SHSTRTAB 23

#define NAME_RELA 33

static uint8_t elf_buffer[ 4096 ];

static bool include_indirect;

static bool quiet;

static bool verbose;

static char *report_buffer;

static size_t report_size;

static char *error_buffer;

static size_t error_size;

void TxImageInit( TxImage *image )
{
  memset( image, 0, sizeof( *image ) );
  image->alignment = 4;
  image->relocation_info = TX_SECTION_TEXT;
}

void TxAppend( TxImage *image, uint32_t instruction )
{
  T_assert_lt_sz( image->count, (size_t) TX_MAX_CODE );
  image->code[ image->count ] = instruction;
  ++image->count;
}

void TxAddRelocation( TxImage *image, size_t index )
{
  T_assert_lt_sz( image->relocation_count, (size_t) TX_MAX_RELOCATIONS );
  image->relocations[ image->relocation_count ] = (uint32_t) ( 4 * index );
  ++image->relocation_count;
}

void TxAddSymbol(
  TxImage    *image,
  const char *name,
  uint32_t    value,
  uint8_t     info,
  uint16_t    shndx
)
{
  TxSymbol *sym;

  T_assert_lt_sz( image->symbol_count, (size_t) TX_MAX_SYMBOLS );
  sym = &image->symbols[ image->symbol_count ];
  sym->name = name;
  sym->value = value;
  sym->info = info;
  sym->shndx = shndx;
  ++image->symbol_count;
}

void TxPut16( uint8_t *p, uint32_t value )
{
  p[ 0 ] = (uint8_t) ( value >> 8 );
  p[ 1 ] = (uint8_t) value;
}

void TxPut32( uint8_t *p, uint32_t value )
{
  p[ 0 ] = (uint8_t) ( value >> 24 );
  p[ 1 ] = (uint8_t) ( value >> 16 );
  p[ 2 ] = (uint8_t) ( value >> 8 );
  p[ 3 ] = (uint8_t) value;
}

uint32_t TxGet32( const uint8_t *p )
{
  return ( (uint32_t) p[ 0 ] << 24 ) | ( (uint32_t) p[ 1 ] << 16 ) |
         ( (uint32_t) p[ 2 ] << 8 ) | (uint32_t) p[ 3 ];
}

size_t TxSectionHeader( const uint8_t *buf, uint32_t index )
{
  uint32_t shoff = ( (uint32_t) buf[ 32 ] << 24 ) |
                   ( (uint32_t) buf[ 33 ] << 16 ) |
                   ( (uint32_t) buf[ 34 ] << 8 ) | (uint32_t) buf[ 35 ];

  return shoff + SECTION_HEADER_SIZE * index;
}

static void PutSection(
  uint8_t *p,
  uint32_t name,
  uint32_t type,
  uint32_t flags,
  uint32_t address,
  uint32_t offset,
  uint32_t size,
  uint32_t link,
  uint32_t info,
  uint32_t alignment,
  uint32_t entry_size
)
{
  TxPut32( p, name );
  TxPut32( p + 4, type );
  TxPut32( p + 8, flags );
  TxPut32( p + 12, address );
  TxPut32( p + 16, offset );
  TxPut32( p + 20, size );
  TxPut32( p + 24, link );
  TxPut32( p + 28, info );
  TxPut32( p + 32, alignment );
  TxPut32( p + 36, entry_size );
}

size_t TxBuildElf( const TxImage *image, uint8_t *buf, size_t size )
{
  TxSymbol        default_symbol = { "f", 0, 0x12, TX_SECTION_TEXT };
  const TxSymbol *symbols = image->symbols;
  size_t          symbol_count = image->symbol_count;
  uint32_t        entry = image->rel ? REL_SIZE : RELA_SIZE;
  uint32_t        text_offset = ELF_HEADER_SIZE;
  uint32_t        text_size = (uint32_t) ( 4 * image->count );
  uint32_t        symtab_offset = text_offset + text_size;
  uint32_t        symtab_size;
  uint32_t        strtab_offset;
  uint32_t        strtab_size;
  uint32_t        shstrtab_offset;
  uint32_t        shstrtab_size = sizeof( section_names );
  uint32_t        rela_offset;
  uint32_t        rela_size;
  uint32_t        section_offset;
  uint32_t        section_count = image->relocation_count > 0 ? 6 : 5;
  uint32_t        total;
  uint32_t        name;
  uint8_t        *sh;
  size_t          i;

  if ( symbol_count == 0 ) {
    symbols = &default_symbol;
    symbol_count = 1;
  }

  symtab_size = (uint32_t) ( SYMBOL_SIZE * ( symbol_count + 1 ) );
  strtab_offset = symtab_offset + symtab_size;
  strtab_size = 1;

  for ( i = 0; i < symbol_count; ++i ) {
    strtab_size += (uint32_t) strlen( symbols[ i ].name ) + 1;
  }

  shstrtab_offset = strtab_offset + strtab_size;
  rela_offset = shstrtab_offset + shstrtab_size;
  rela_size = (uint32_t) ( entry * image->relocation_count );
  section_offset = ( rela_offset + rela_size + 3 ) & ~3U;
  total = section_offset + section_count * SECTION_HEADER_SIZE;

  T_assert_le_sz( (size_t) total, size );
  memset( buf, 0, total );

  memcpy( buf, "\177ELF", 4 );
  buf[ 4 ] = 1;
  buf[ 5 ] = 2;
  buf[ 6 ] = 1;
  TxPut16( buf + 16, image->executable ? 2 : 1 );
  TxPut16( buf + 18, 2 );
  TxPut32( buf + 20, 1 );
  TxPut32( buf + 32, section_offset );
  TxPut16( buf + 40, ELF_HEADER_SIZE );
  TxPut16( buf + 46, SECTION_HEADER_SIZE );
  TxPut16( buf + 48, section_count );
  TxPut16( buf + 50, TX_SECTION_SHSTRTAB );

  for ( i = 0; i < image->count; ++i ) {
    TxPut32( buf + text_offset + 4 * i, image->code[ i ] );
  }

  name = 1;

  for ( i = 0; i < symbol_count; ++i ) {
    uint8_t *sym = buf + symtab_offset + SYMBOL_SIZE * ( i + 1 );
    size_t   n = strlen( symbols[ i ].name ) + 1;

    TxPut32( sym, name );
    TxPut32(
      sym + 4,
      symbols[ i ].value + ( image->executable ? image->address : 0 )
    );
    sym[ 12 ] = symbols[ i ].info;
    TxPut16( sym + 14, symbols[ i ].shndx );
    memcpy( buf + strtab_offset + name, symbols[ i ].name, n );
    name += (uint32_t) n;
  }

  memcpy( buf + shstrtab_offset, section_names, shstrtab_size );

  for ( i = 0; i < image->relocation_count; ++i ) {
    TxPut32( buf + rela_offset + entry * i, image->relocations[ i ] );
  }

  sh = buf + section_offset + SECTION_HEADER_SIZE;
  PutSection(
    sh,
    NAME_TEXT,
    1,
    6,
    image->executable ? image->address : 0,
    text_offset,
    text_size,
    0,
    0,
    image->alignment,
    0
  );
  sh += SECTION_HEADER_SIZE;
  PutSection(
    sh,
    NAME_SYMTAB,
    2,
    0,
    0,
    symtab_offset,
    symtab_size,
    TX_SECTION_STRTAB,
    1,
    4,
    SYMBOL_SIZE
  );
  sh += SECTION_HEADER_SIZE;
  PutSection(
    sh,
    NAME_STRTAB,
    3,
    0,
    0,
    strtab_offset,
    strtab_size,
    0,
    0,
    1,
    0
  );
  sh += SECTION_HEADER_SIZE;
  PutSection(
    sh,
    NAME_SHSTRTAB,
    3,
    0,
    0,
    shstrtab_offset,
    shstrtab_size,
    0,
    0,
    1,
    0
  );

  if ( image->relocation_count > 0 ) {
    sh += SECTION_HEADER_SIZE;
    PutSection(
      sh,
      NAME_RELA,
      image->rel ? 9 : 4,
      0,
      0,
      rela_offset,
      rela_size,
      TX_SECTION_SYMTAB,
      image->relocation_info,
      4,
      entry
    );
  }

  return total;
}

const char *TxCheckBuffer( const uint8_t *buf, size_t size, unsigned int notes )
{
  FILE *out;
  FILE *err;

  free( report_buffer );
  free( error_buffer );
  out = open_memstream( &report_buffer, &report_size );
  T_assert_not_null( out );
  err = open_memstream( &error_buffer, &error_size );
  T_assert_not_null( err );

  memset( &opts, 0, sizeof( opts ) );
  memset( &stats, 0, sizeof( stats ) );
  opts.out = out;
  opts.err = err;
  opts.enabled_notes = notes;
  opts.include_indirect = include_indirect;
  opts.quiet = quiet;
  opts.verbose = verbose;
  check_buffer( "t.o", buf, size );

  T_quiet_eq_int( fclose( out ), 0 );
  T_quiet_eq_int( fclose( err ), 0 );

  return report_buffer;
}

const char *TxCheckFile( const char *file, unsigned int notes )
{
  FILE *out;
  FILE *err;

  free( report_buffer );
  free( error_buffer );
  out = open_memstream( &report_buffer, &report_size );
  T_assert_not_null( out );
  err = open_memstream( &error_buffer, &error_size );
  T_assert_not_null( err );

  memset( &opts, 0, sizeof( opts ) );
  memset( &stats, 0, sizeof( stats ) );
  opts.out = out;
  opts.err = err;
  opts.enabled_notes = notes;
  check_file( file );

  T_quiet_eq_int( fclose( out ), 0 );
  T_quiet_eq_int( fclose( err ), 0 );

  return report_buffer;
}

const char *TxMain( int argc, char **argv, int *status )
{
  FILE *out;
  FILE *err;

  free( report_buffer );
  free( error_buffer );
  out = open_memstream( &report_buffer, &report_size );
  T_assert_not_null( out );
  err = open_memstream( &error_buffer, &error_size );
  T_assert_not_null( err );
  *status = nopinion_main( argc, argv, out, err );
  T_quiet_eq_int( fclose( out ), 0 );
  T_quiet_eq_int( fclose( err ), 0 );

  return report_buffer;
}

const char *TxErrors( void )
{
  return error_buffer;
}

const char *TxCheck( const TxImage *image, unsigned int notes )
{
  size_t      size;
  const char *report;

  size = TxBuildElf( image, elf_buffer, sizeof( elf_buffer ) );
  report = TxCheckBuffer( elf_buffer, size, notes );
  T_quiet_eq_sz( error_size, (size_t) 0 );

  return report;
}

void TxSetQuietVerbose( bool q, bool v )
{
  quiet = q;
  verbose = v;
}

void TxSetIncludeIndirect( bool include )
{
  include_indirect = include;
}

static const char *FindAt( const char *report, uint32_t offset, const char *note )
{
  char prefix[ 32 ];
  const char *line = report;

  (void) snprintf( prefix, sizeof( prefix ), "t.o: .text+0x%x", offset );

  while ( *line != '\0' ) {
    const char *end = strchr( line, '\n' );

    if ( end == NULL ) {
      end = line + strlen( line );
    }

    if (
      strncmp( line, prefix, strlen( prefix ) ) == 0 &&
      ( line[ strlen( prefix ) ] == ' ' || line[ strlen( prefix ) ] == ':' )
    ) {
      const char *n = strstr( line, note );

      if ( n != NULL && n < end ) {
        return line;
      }
    }

    line = *end == '\0' ? end : end + 1;
  }

  return NULL;
}

int TxCountAt( const char *report, uint32_t offset, const char *note )
{
  int count = 0;
  const char *line = report;

  while ( ( line = FindAt( line, offset, note ) ) != NULL ) {
    ++count;
    line = strchr( line, '\n' );

    if ( line == NULL ) {
      break;
    }

    ++line;
  }

  return count;
}

bool TxIsPossibleAt( const char *report, uint32_t offset, const char *note )
{
  const char *line = FindAt( report, offset, note );
  const char *end;

  if ( line == NULL ) {
    return false;
  }

  end = strchr( line, '\n' );

  if ( end == NULL ) {
    end = line + strlen( line );
  }

  return end - line >= 9 && strncmp( end - 9, " possible", 9 ) == 0;
}

uint32_t TxFormat3Reg(
  uint32_t op,
  uint32_t op3,
  uint32_t rd,
  uint32_t rs1,
  uint32_t rs2
)
{
  return ( op << 30 ) | ( rd << 25 ) | ( op3 << 19 ) | ( rs1 << 14 ) | rs2;
}

uint32_t TxFormat3Imm(
  uint32_t op,
  uint32_t op3,
  uint32_t rd,
  uint32_t rs1,
  int32_t simm13
)
{
  return ( op << 30 ) | ( rd << 25 ) | ( op3 << 19 ) | ( rs1 << 14 ) |
         ( 1U << 13 ) | ( (uint32_t) simm13 & 0x1fffU );
}

uint32_t TxFormat3Asi(
  uint32_t op,
  uint32_t op3,
  uint32_t rd,
  uint32_t rs1,
  uint32_t asi,
  uint32_t rs2
)
{
  return ( op << 30 ) | ( rd << 25 ) | ( op3 << 19 ) | ( rs1 << 14 ) |
         ( asi << 5 ) | rs2;
}

uint32_t TxNop( void )
{
  /* SETHI 0, %g0, section B.10 */
  return 0x01000000;
}

uint32_t TxAdd( void )
{
  /* ADD %g1, 1, %g1, section B.13 */
  return TxFormat3Imm( 2, 0x00, TX_G1, TX_G1, 1 );
}

uint32_t TxLd( void )
{
  /* LD [%o0], %g1, section B.1 */
  return TxFormat3Reg( 3, 0x00, TX_G1, TX_O0, TX_G0 );
}

uint32_t TxSt( void )
{
  /* ST %g1, [%o0], section B.4 */
  return TxFormat3Reg( 3, 0x04, TX_G1, TX_O0, TX_G0 );
}

uint32_t TxStd( void )
{
  /* STD %o0, [%o0], section B.4 */
  return TxFormat3Reg( 3, 0x07, TX_O0, TX_O0, TX_G0 );
}

uint32_t TxSwap( void )
{
  /* SWAP [%o0], %g1, section B.8 */
  return TxFormat3Reg( 3, 0x0f, TX_G1, TX_O0, TX_G0 );
}

uint32_t TxBicc( uint32_t cond, bool annul, int32_t disp22 )
{
  /* Bicc, section B.21 */
  return ( annul ? 1U << 29 : 0 ) | ( cond << 25 ) | ( 2U << 22 ) |
         ( (uint32_t) disp22 & 0x3fffffU );
}

uint32_t TxCall( int32_t disp30 )
{
  /* CALL, section B.24 */
  return ( 1U << 30 ) | ( (uint32_t) disp30 & 0x3fffffffU );
}

uint32_t TxJmpl( void )
{
  /* JMPL %o7 + 8, %g0, section B.25 */
  return TxFormat3Imm( 2, 0x38, TX_G0, 15, 8 );
}

uint32_t TxRett( void )
{
  /* RETT %l2 + 4, section B.26 */
  return TxFormat3Imm( 2, 0x39, TX_G0, TX_L2, 4 );
}

uint32_t TxTa( void )
{
  /* TA 0, section B.27 */
  return TxFormat3Imm( 2, 0x3a, 8, TX_G0, 0 );
}

uint32_t TxSubcc( void )
{
  /* SUBcc %g1, %o0, %g0, section B.15 */
  return TxFormat3Reg( 2, 0x14, TX_G0, TX_G1, TX_O0 );
}

uint32_t TxFadds( void )
{
  /* FADDs %f1, %f2, %f3, FPop1 of section B.33 */
  return ( 2U << 30 ) | ( 3U << 25 ) | ( 0x34U << 19 ) | ( 1U << 14 ) |
         ( 0x041U << 5 ) | 2U;
}

uint32_t TxFcmps( void )
{
  /* FCMPs %f1, %f2, FPop2 of section B.33 */
  return ( 2U << 30 ) | ( 0x35U << 19 ) | ( 1U << 14 ) | ( 0x051U << 5 ) |
         2U;
}

uint32_t TxFbfcc( bool annul, int32_t disp22 )
{
  /* FBNE, section B.22 */
  return ( annul ? 1U << 29 : 0 ) | ( 1U << 25 ) | ( 6U << 22 ) |
         ( (uint32_t) disp22 & 0x3fffffU );
}

uint32_t TxLdf( void )
{
  /* LDF [%o0], %f1, section B.2 */
  return TxFormat3Reg( 3, 0x20, 1, TX_O0, TX_G0 );
}

uint32_t TxFpop1( uint32_t opf, uint32_t rd, uint32_t rs1, uint32_t rs2 )
{
  /* FPop1, section B.33 */
  return TxFormat3Asi( 2, 0x34, rd, rs1, opf, rs2 );
}

uint32_t TxFpop2( uint32_t opf, uint32_t rs1, uint32_t rs2 )
{
  /* FPop2, section B.33 */
  return TxFormat3Asi( 2, 0x35, 0, rs1, opf, rs2 );
}

uint32_t TxLdfReg( uint32_t rd )
{
  /* LDF [%o0], %f<rd>, section B.2 */
  return TxFormat3Reg( 3, 0x20, rd, TX_O0, TX_G0 );
}

uint32_t TxStfReg( uint32_t rd )
{
  /* STF %f<rd>, [%o0], section B.5 */
  return TxFormat3Reg( 3, 0x24, rd, TX_O0, TX_G0 );
}

uint32_t TxLdstub( void )
{
  /* LDSTUB [%o0], %g1, section B.7 */
  return TxFormat3Reg( 3, 0x0d, TX_G1, TX_O0, TX_G0 );
}

uint32_t TxCasa( void )
{
  /* CASA [%o0] 10, %o1, %g1, the compare and swap of the LEON processors */
  return TxFormat3Asi( 3, 0x3c, TX_G1, TX_O0, 10, TX_O1 );
}

uint32_t TxCbccc( int32_t disp22 )
{
  /* CB123, section B.23 */
  return ( 1U << 25 ) | ( 7U << 22 ) | ( (uint32_t) disp22 & 0x3fffffU );
}

uint32_t TxStfsr( void )
{
  /* STFSR [%o0], section B.5 */
  return TxFormat3Reg( 3, 0x25, 0, TX_O0, TX_G0 );
}

uint32_t TxTicc( uint32_t cond )
{
  /* Ticc 5, section B.27 */
  return TxFormat3Imm( 2, 0x3a, cond, TX_G0, 5 );
}

uint32_t TxWrasr( uint32_t rd )
{
  /* WR %g0, %g0, %asr<rd>, section B.29 */
  return TxFormat3Reg( 2, 0x30, rd, TX_G0, TX_G0 );
}

void TxWriteElf( const char *file, const TxImage *image )
{
  size_t size;
  FILE  *f;

  size = TxBuildElf( image, elf_buffer, sizeof( elf_buffer ) );
  f = fopen( file, "wb" );
  T_assert_not_null( f );
  T_assert_eq_sz( fwrite( elf_buffer, 1, size, f ), size );
  T_assert_eq_int( fclose( f ), 0 );
}

static bool IsDefiniteAt( const char *report, uint32_t offset, const char *note )
{
  return TxCountAt( report, offset, note ) == 1 &&
         !TxIsPossibleAt( report, offset, note );
}

void TxProbeMemory( uint32_t instruction, TxMemoryProbe *probe )
{
  TxImage image;

  TxImageInit( &image );
  TxAppend( &image, instruction );
  TxAppend( &image, TxAdd() );
  TxAppend( &image, TxSt() );
  probe->sequence_a = IsDefiniteAt(
    TxCheck( &image, NOTE_0009 ),
    0,
    "TN-0009"
  );

  TxImageInit( &image );
  TxAppend( &image, instruction );
  TxAppend( &image, TxSt() );
  probe->sequence_b = IsDefiniteAt(
    TxCheck( &image, NOTE_0009 ),
    0,
    "TN-0009"
  );

  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, instruction );
  TxAppend( &image, TxSt() );
  probe->middle = IsDefiniteAt( TxCheck( &image, NOTE_0009 ), 0, "TN-0009" );

  TxImageInit( &image );
  image.alignment = 16;
  TxAppend( &image, TxCall( 2 ) );
  TxAppend( &image, instruction );
  TxAppend( &image, TxNop() );
  probe->in_delay_slot = IsDefiniteAt(
    TxCheck( &image, NOTE_0011 ),
    4,
    "atomic-in-delay-slot"
  );
}

bool TxProbeIcc( uint32_t instruction )
{
  TxImage image;

  TxImageInit( &image );
  TxAppend( &image, instruction );
  TxAppend( &image, TxBicc( 9, true, 2 ) );
  TxAppend( &image, TxFadds() );
  TxAppend( &image, TxNop() );

  return IsDefiniteAt( TxCheck( &image, NOTE_0012 ), 0, "TN-0012" );
}

static uint32_t MakeFpop( uint32_t op3, uint32_t opf, int field, uint32_t value )
{
  uint32_t reg[ 3 ] = { 0, 0, 0 };

  reg[ field ] = value;

  return TxFormat3Asi( 2, op3, reg[ TX_RD ], reg[ TX_RS1 ], opf, reg[ TX_RS2 ] );
}

/* Returns true, if the layout of the kind gives a definite TN-0013 finding */
static bool Sequence0013( uint32_t x, uint32_t dst, TxFpopKind kind )
{
  TxImage image;

  TxImageInit( &image );
  TxAppend( &image, TxFpop1( TX_FDIVS, dst, 24, 28 ) );

  switch ( kind ) {
    case TX_KIND_DIV:
      TxAppend( &image, TxFpop1( TX_FADDS, 8, 9, 10 ) );
      TxAppend( &image, TxFpop1( TX_FADDS, 11, 9, 10 ) );
      TxAppend( &image, x );
      break;
    case TX_KIND_FPOP2:
      TxAppend( &image, TxFpop1( TX_FADDS, 8, 9, 10 ) );
      TxAppend( &image, x );
      TxAppend( &image, TxFpop1( TX_FADDS, 11, 9, 10 ) );
      TxAppend( &image, TxFpop1( TX_FDIVS, 12, 13, 14 ) );
      break;
    default:
      TxAppend( &image, x );
      TxAppend( &image, TxFpop1( TX_FADDS, 8, 9, 10 ) );
      TxAppend( &image, TxFpop1( TX_FDIVS, 12, 13, 14 ) );
      break;
  }

  TxAppend( &image, TxNop() );

  return IsDefiniteAt( TxCheck( &image, NOTE_0013 ), 0, "TN-0013" );
}

void TxProbeFpop(
  uint32_t      op3,
  uint32_t      opf,
  TxFpopKind    kind,
  TxFpopProbe *probe
)
{
  TxImage image;
  uint32_t x = MakeFpop( op3, opf, TX_RD, 0 );
  int      field;

  TxImageInit( &image );
  TxAppend( &image, TxSubcc() );
  TxAppend( &image, TxBicc( 9, true, 2 ) );
  TxAppend( &image, x );
  TxAppend( &image, TxNop() );
  probe->is_fpop = IsDefiniteAt( TxCheck( &image, NOTE_0012 ), 0, "TN-0012" );

  TxImageInit( &image );
  TxAppend( &image, x );
  TxAppend( &image, TxFpop1( TX_FADDS, 8, 9, 10 ) );
  TxAppend( &image, TxFpop1( TX_FADDS, 11, 9, 10 ) );
  TxAppend( &image, TxFpop1( TX_FDIVS, 12, 13, 14 ) );
  TxAppend( &image, TxNop() );
  probe->is_div = IsDefiniteAt( TxCheck( &image, NOTE_0013 ), 0, "TN-0013" );

  probe->counted = Sequence0013( x, 17, TX_KIND_FPOP1 );
  probe->any = !Sequence0013( x, 17, kind );

  for ( field = 0; field < 3; ++field ) {
    bool present = !Sequence0013( MakeFpop( op3, opf, field, 17 ), 17, kind );
    bool wide = !Sequence0013( MakeFpop( op3, opf, field, 17 ), 16, kind );
    bool quad = !Sequence0013( MakeFpop( op3, opf, field, 18 ), 17, kind );

    if ( quad ) {
      probe->width[ field ] = 4;
    } else if ( wide ) {
      probe->width[ field ] = 2;
    } else if ( present ) {
      probe->width[ field ] = 1;
    } else {
      probe->width[ field ] = 0;
    }
  }
}

TxFlowFinding TxProbeFlow(
  uint32_t x,
  bool     relocated,
  bool     slot_is_target,
  bool     store_at_fall
)
{
  TxImage     image;
  const char *report;

  TxImageInit( &image );
  TxAppend( &image, x );
  TxAppend( &image, TxStd() );
  TxAppend( &image, store_at_fall ? TxSt() : TxAdd() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, store_at_fall ? TxAdd() : TxSt() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxBicc( 8, false, slot_is_target ? -5 : 0 ) );
  TxAppend( &image, TxNop() );

  if ( relocated ) {
    TxAddRelocation( &image, 0 );
  }

  report = TxCheck( &image, NOTE_0009 );

  if ( TxCountAt( report, 4, "TN-0009" ) == 0 ) {
    return TX_FLOW_NONE;
  }

  return TxIsPossibleAt( report, 4, "TN-0009" ) ? TX_FLOW_POSSIBLE :
                                                  TX_FLOW_DEFINITE;
}

void TxArchiveInit( TxArchive *ar )
{
  memcpy( ar->buf, "!<arch>\n", 8 );
  ar->size = 8;
}

void TxArchiveAdd(
  TxArchive     *ar,
  const char    *name,
  const uint8_t *data,
  size_t         size,
  size_t         excess
)
{
  char header[ 61 ];

  T_assert_le_sz( ar->size + 60 + size + 1, sizeof( ar->buf ) );
  (void) snprintf(
    header,
    sizeof( header ),
    "%-16s%-12s%-6s%-6s%-8s%-10zu`\n",
    name,
    "0",
    "0",
    "0",
    "644",
    size + excess
  );
  memcpy( ar->buf + ar->size, header, 60 );
  ar->size += 60;
  memcpy( ar->buf + ar->size, data, size );
  ar->size += size;

  if ( ( size & 1 ) != 0 ) {
    ar->buf[ ar->size ] = '\n';
    ++ar->size;
  }
}

void TxLineAt(
  const char *report,
  uint32_t    offset,
  const char *note,
  char       *buf,
  size_t      size
)
{
  const char *line = FindAt( report, offset, note );
  size_t      n;

  buf[ 0 ] = '\0';

  if ( line == NULL ) {
    return;
  }

  n = strcspn( line, "\n" );

  if ( n >= size ) {
    n = size - 1;
  }

  memcpy( buf, line, n );
  buf[ n ] = '\0';
}
