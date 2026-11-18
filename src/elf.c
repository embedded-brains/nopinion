/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "nopinion.h"

#define ET_REL 1

#define EM_SPARC 2

#define EM_SPARC32PLUS 18

#define SHT_PROGBITS 1

#define SHT_SYMTAB 2

#define SHT_RELA 4

#define SHT_REL 9

#define SHF_EXECINSTR 0x4

#define STT_NOTYPE 0

#define STT_FUNC 2

#define SHN_LORESERVE 0xff00

static int compare_symbols( const void *a, const void *b )
{
  const symbol *sa = a;
  const symbol *sb = b;

  if ( sa->value != sb->value ) {
    return sa->value < sb->value ? -1 : 1;
  }

  return strcmp( sa->name, sb->name );
}

typedef struct {
  const uint8_t *data;
  size_t         size;
  const char    *file;
  const char    *member;
  size_t         member_length;
} elf_input;

static const uint8_t *section_header( const elf_input *in, uint32_t index )
{
  uint32_t shoff = get_be32( in->data + 32 );
  uint16_t shentsize = get_be16( in->data + 46 );

  return in->data + shoff + (size_t) index * shentsize;
}

static bool in_bounds( const elf_input *in, uint32_t offset, uint32_t size )
{
  return offset <= in->size && size <= in->size - offset;
}

static void collect_symbols(
  const elf_input *in,
  uint16_t         shnum,
  uint32_t         text_index,
  section_context *ctx
)
{
  uint32_t s;

  ctx->symbols = NULL;
  ctx->symbol_count = 0;

  for ( s = 0; s < shnum; ++s ) {
    const uint8_t *sh = section_header( in, s );
    const uint8_t *strsh;
    uint32_t       off;
    uint32_t       size;
    uint32_t       stroff;
    uint32_t       strsize;
    uint32_t       n;
    uint32_t       k;

    if ( get_be32( sh + 4 ) != SHT_SYMTAB ) {
      continue;
    }

    off = get_be32( sh + 16 );
    size = get_be32( sh + 20 );

    if ( get_be32( sh + 24 ) >= shnum ) {
      return;
    }

    strsh = section_header( in, get_be32( sh + 24 ) );
    stroff = get_be32( strsh + 16 );
    strsize = get_be32( strsh + 20 );

    if ( !in_bounds( in, off, size ) || !in_bounds( in, stroff, strsize ) ) {
      return;
    }

    n = size / 16;
    ctx->symbols = malloc( sizeof( *ctx->symbols ) * ( n + 1 ) );

    if ( ctx->symbols == NULL ) {
      return;
    }

    for ( k = 0; k < n; ++k ) {
      const uint8_t *sym = in->data + off + 16 * k;
      uint32_t       name = get_be32( sym );
      uint8_t        type = sym[ 12 ] & 0xf;
      uint16_t       shndx = get_be16( sym + 14 );

      if (
        shndx != text_index || name == 0 || name >= strsize ||
        ( type != STT_FUNC && type != STT_NOTYPE )
      ) {
        continue;
      }

      ctx->symbols[ ctx->symbol_count ].value = get_be32( sym + 4 );
      ctx->symbols[ ctx->symbol_count ].name = (const char *) in->data +
                                               stroff + name;
      ++ctx->symbol_count;
    }

    qsort(
      ctx->symbols,
      ctx->symbol_count,
      sizeof( *ctx->symbols ),
      compare_symbols
    );
    return;
  }
}

static void mark_relocations(
  const elf_input *in,
  uint16_t         shnum,
  uint32_t         text_index,
  section_context *ctx
)
{
  uint32_t s;

  for ( s = 0; s < shnum; ++s ) {
    const uint8_t *sh = section_header( in, s );
    uint32_t       type = get_be32( sh + 4 );
    uint32_t       off;
    uint32_t       size;
    uint32_t       entsize;
    uint32_t       k;

    if (
      ( type != SHT_RELA && type != SHT_REL ) ||
      get_be32( sh + 28 ) != text_index
    ) {
      continue;
    }

    off = get_be32( sh + 16 );
    size = get_be32( sh + 20 );
    entsize = type == SHT_RELA ? 12 : 8;

    if ( !in_bounds( in, off, size ) ) {
      continue;
    }

    for ( k = 0; k + entsize <= size; k += entsize ) {
      uint32_t r_offset = get_be32( in->data + off + k );
      long     i = (long) ( r_offset / 4 );

      if ( i < ctx->count ) {
        ctx->info[ i ].flags |= F_RELOC;
      }
    }
  }
}

static void check_elf( const elf_input *in )
{
  const uint8_t *d = in->data;
  uint16_t       type;
  uint16_t       machine;
  uint16_t       shnum;
  uint16_t       shstrndx;
  uint32_t       shoff;
  uint16_t       shentsize;
  const uint8_t *strsh;
  uint32_t       stroff;
  uint32_t       strsize;
  uint32_t       s;

  if ( in->size < 52 || memcmp( d, "\177ELF", 4 ) != 0 ) {
    error( in->file, in->member, in->member_length, "not an ELF file" );
    return;
  }

  if ( d[ 4 ] != 1 || d[ 5 ] != 2 ) {
    error(
      in->file,
      in->member,
      in->member_length,
      "not an ELF32 big-endian file"
    );
    return;
  }

  type = get_be16( d + 16 );
  machine = get_be16( d + 18 );

  if ( machine != EM_SPARC && machine != EM_SPARC32PLUS ) {
    error( in->file, in->member, in->member_length, "not a SPARC ELF file" );
    return;
  }

  shoff = get_be32( d + 32 );
  shentsize = get_be16( d + 46 );
  shnum = get_be16( d + 48 );
  shstrndx = get_be16( d + 50 );

  if ( shnum == 0 ) {
    return;
  }

  if (
    shentsize < 40 || !in_bounds( in, shoff, (uint32_t) shnum * shentsize ) ||
    shstrndx >= shnum
  ) {
    error( in->file, in->member, in->member_length, "bad section headers" );
    return;
  }

  strsh = section_header( in, shstrndx );
  stroff = get_be32( strsh + 16 );
  strsize = get_be32( strsh + 20 );

  if ( !in_bounds( in, stroff, strsize ) ) {
    error( in->file, in->member, in->member_length, "bad string table" );
    return;
  }

  for ( s = 0; s < shnum; ++s ) {
    const uint8_t  *sh = section_header( in, s );
    uint32_t        name = get_be32( sh );
    uint32_t        off = get_be32( sh + 16 );
    uint32_t        size = get_be32( sh + 20 );
    section_context ctx;

    if (
      get_be32( sh + 4 ) != SHT_PROGBITS ||
      ( get_be32( sh + 8 ) & SHF_EXECINSTR ) == 0 || size < 4
    ) {
      continue;
    }

    if ( !in_bounds( in, off, size ) || name >= strsize ) {
      error( in->file, in->member, in->member_length, "bad code section" );
      continue;
    }

    ctx.file = in->file;
    ctx.member = in->member;
    ctx.member_length = in->member_length;
    ctx.section = (const char *) d + stroff + name;
    ctx.address = get_be32( sh + 12 );
    ctx.alignment = get_be32( sh + 32 );
    ctx.relocatable = type == ET_REL;
    ctx.code = d + off;
    ctx.count = (long) ( size / 4 );
    ctx.info = calloc( (size_t) ctx.count, sizeof( *ctx.info ) );
    ctx.target = malloc( sizeof( *ctx.target ) * (size_t) ctx.count );

    if ( ctx.info == NULL || ctx.target == NULL ) {
      error( in->file, in->member, in->member_length, "out of memory" );
      free( ctx.info );
      free( ctx.target );
      return;
    }

    mark_relocations( in, shnum, s, &ctx );
    collect_symbols( in, shnum, s, &ctx );
    check_section( &ctx );
    free( ctx.symbols );
    free( ctx.info );
    free( ctx.target );
  }
}

static size_t member_name_length( const char *name, size_t max )
{
  size_t n = 0;

  while ( n < max && name[ n ] != '/' && name[ n ] != '\n' ) {
    ++n;
  }

  return n;
}

static void check_archive( const char *file, const uint8_t *data, size_t size )
{
  size_t      pos = 8;
  const char *long_names = NULL;
  size_t      long_names_size = 0;

  while ( pos + 60 <= size ) {
    const char   *hdr = (const char *) data + pos;
    char          size_text[ 11 ];
    unsigned long member_size;
    const char   *name = hdr;
    size_t        name_length;
    elf_input     in;

    memcpy( size_text, hdr + 48, 10 );
    size_text[ 10 ] = '\0';
    member_size = strtoul( size_text, NULL, 10 );
    pos += 60;

    if ( member_size > size - pos ) {
      error( file, NULL, 0, "truncated archive" );
      return;
    }

    if ( hdr[ 0 ] == '/' && hdr[ 1 ] == '/' ) {
      long_names = (const char *) data + pos;
      long_names_size = member_size;
    } else if ( hdr[ 0 ] == '/' && hdr[ 1 ] >= '0' && hdr[ 1 ] <= '9' ) {
      unsigned long index = strtoul( hdr + 1, NULL, 10 );

      if ( long_names == NULL || index >= long_names_size ) {
        error( file, NULL, 0, "bad long member name" );
        return;
      }

      name = long_names + index;
      name_length = member_name_length( name, long_names_size - index );
      in.data = data + pos;
      in.size = member_size;
      in.file = file;
      in.member = name;
      in.member_length = name_length;
      check_elf( &in );
    } else if ( hdr[ 0 ] != '/' ) {
      name_length = member_name_length( name, 16 );
      in.data = data + pos;
      in.size = member_size;
      in.file = file;
      in.member = name;
      in.member_length = name_length;
      check_elf( &in );
    }

    pos += member_size + ( member_size & 1 );
  }
}

void check_buffer( const char *file, const uint8_t *data, size_t size )
{
  if ( size >= 8 && memcmp( data, "!<arch>\n", 8 ) == 0 ) {
    check_archive( file, data, size );
  } else if ( size >= 8 && memcmp( data, "!<thin>\n", 8 ) == 0 ) {
    error( file, NULL, 0, "thin archives are not supported" );
  } else {
    elf_input in = { data, size, file, NULL, 0 };
    check_elf( &in );
  }
}

void check_file( const char *file )
{
  int         fd;
  struct stat st;
  void       *map;

  fd = open( file, O_RDONLY );

  if ( fd < 0 ) {
    error( file, NULL, 0, strerror( errno ) );
    return;
  }

  if ( fstat( fd, &st ) != 0 ) {
    error( file, NULL, 0, strerror( errno ) );
    close( fd );
    return;
  }

  if ( st.st_size == 0 ) {
    error( file, NULL, 0, "empty file" );
    close( fd );
    return;
  }

  map = mmap( NULL, (size_t) st.st_size, PROT_READ, MAP_PRIVATE, fd, 0 );
  close( fd );

  if ( map == MAP_FAILED ) {
    error( file, NULL, 0, strerror( errno ) );
    return;
  }

  (void) madvise( map, (size_t) st.st_size, MADV_SEQUENTIAL );
  check_buffer( file, map, (size_t) st.st_size );
  munmap( map, (size_t) st.st_size );
}
