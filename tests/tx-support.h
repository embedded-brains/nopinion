/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

/*
 * This header file provides the support of the validation test cases.  The
 * instruction encodings follow appendix B of the SPARC Architecture Manual
 * Version 8.  The file layout follows the ELF specification for a 32-bit
 * big-endian SPARC target.
 */

#ifndef TX_SUPPORT_H
#define TX_SUPPORT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define TX_MAX_CODE 64

#define TX_MAX_RELOCATIONS 8

#define TX_MAX_SYMBOLS 8

typedef struct {
  const char *name;
  uint32_t    value;
  uint8_t     info;
  uint16_t    shndx;
} TxSymbol;

typedef struct {
  uint32_t code[ TX_MAX_CODE ];
  size_t count;
  bool executable;
  uint32_t address;
  uint32_t alignment;
  uint32_t relocations[ TX_MAX_RELOCATIONS ];
  size_t relocation_count;
  bool rel;
  uint32_t relocation_info;
  TxSymbol symbols[ TX_MAX_SYMBOLS ];
  size_t symbol_count;
} TxImage;

/* The section indices of an ELF file which TxBuildElf() writes */
#define TX_SECTION_TEXT 1

#define TX_SECTION_SYMTAB 2

#define TX_SECTION_STRTAB 3

#define TX_SECTION_SHSTRTAB 4

#define TX_SECTION_RELA 5

#define TX_FAIL_CALLOC 0x1U

#define TX_FAIL_MALLOC 0x2U

#define TX_FAIL_FSTAT 0x4U

#define TX_FAIL_MMAP 0x8U

/* Lets the next call of each of the functions fail */
void TxFailNext( unsigned int functions );

/* Lets the call of malloc() after the skipped calls fail */
void TxFailMallocAfter( unsigned int skip );

/* Adds a symbol, the first symbol replaces the default symbol f */
void TxAddSymbol(
  TxImage    *image,
  const char *name,
  uint32_t    value,
  uint8_t     info,
  uint16_t    shndx
);

/* Returns the offset of the section header in the ELF file */
size_t TxSectionHeader( const uint8_t *buf, uint32_t index );

void TxPut16( uint8_t *p, uint32_t value );

void TxPut32( uint8_t *p, uint32_t value );

uint32_t TxGet32( const uint8_t *p );

/* Checks the buffer with the notes as the file "t.o" and returns the report */
const char *TxCheckBuffer( const uint8_t *buf, size_t size, unsigned int notes );

typedef struct {
  uint8_t buf[ 8192 ];
  size_t  size;
} TxArchive;

void TxArchiveInit( TxArchive *ar );

/*
 * Appends a member with the name field and the data.  The size field of the
 * member header states the size plus the excess.
 */
void TxArchiveAdd(
  TxArchive     *ar,
  const char    *name,
  const uint8_t *data,
  size_t         size,
  size_t         excess
);

/* Checks the file with the notes and returns the report */
const char *TxCheckFile( const char *file, unsigned int notes );

/* Runs nopinion_main() and returns its standard output */
const char *TxMain( int argc, char **argv, int *status );

/* Returns the error output of the last check */
const char *TxErrors( void );

void TxImageInit( TxImage *image );

void TxAppend( TxImage *image, uint32_t instruction );

void TxAddRelocation( TxImage *image, size_t index );

/*
 * Writes the ELF file of the image to the buffer and returns its size.  The
 * file holds the code section .text, the function symbol f at its start,
 * and a relocation section for each relocation of the image.
 */
size_t TxBuildElf( const TxImage *image, uint8_t *buf, size_t size );

/*
 * Checks the ELF file of the image with the notes and returns the report.
 * The file name in the report is "t.o".
 */
const char *TxCheck( const TxImage *image, unsigned int notes );

/* Selects whether TxCheck() treats an indirect target as unknown */
void TxSetIncludeIndirect( bool include_indirect );

/*
 * Copies the first report line which names the offset and the note without
 * its newline to the buffer.  Copies an empty string, if no such line
 * exists.
 */
void TxLineAt(
  const char *report,
  uint32_t    offset,
  const char *note,
  char       *buf,
  size_t      size
);

/* Selects the options -q and -v of TxCheck() */
void TxSetQuietVerbose( bool quiet, bool verbose );

/* Returns the count of report lines which name the offset */
int TxCountAt( const char *report, uint32_t offset, const char *note );

/* Returns true, if a report line names the offset and the possible kind */
bool TxIsPossibleAt( const char *report, uint32_t offset, const char *note );

#define TX_G0 0

#define TX_G1 1

#define TX_O0 8

#define TX_O1 9

#define TX_O2 10

#define TX_L0 16

#define TX_L1 17

#define TX_L2 18

#define TX_L3 19

#define TX_L4 20

uint32_t TxFormat3Reg(
  uint32_t op,
  uint32_t op3,
  uint32_t rd,
  uint32_t rs1,
  uint32_t rs2
);

uint32_t TxFormat3Imm(
  uint32_t op,
  uint32_t op3,
  uint32_t rd,
  uint32_t rs1,
  int32_t simm13
);

uint32_t TxFormat3Asi(
  uint32_t op,
  uint32_t op3,
  uint32_t rd,
  uint32_t rs1,
  uint32_t asi,
  uint32_t rs2
);

uint32_t TxNop( void );

uint32_t TxAdd( void );

uint32_t TxLd( void );

uint32_t TxSt( void );

uint32_t TxStd( void );

uint32_t TxSwap( void );

uint32_t TxBicc( uint32_t cond, bool annul, int32_t disp22 );

uint32_t TxCall( int32_t disp30 );

uint32_t TxJmpl( void );

uint32_t TxRett( void );

uint32_t TxTa( void );

uint32_t TxSubcc( void );

uint32_t TxFadds( void );

uint32_t TxFcmps( void );

uint32_t TxFbfcc( bool annul, int32_t disp22 );

uint32_t TxLdf( void );

uint32_t TxFpop1( uint32_t opf, uint32_t rd, uint32_t rs1, uint32_t rs2 );

uint32_t TxFpop2( uint32_t opf, uint32_t rs1, uint32_t rs2 );

uint32_t TxLdfReg( uint32_t rd );

uint32_t TxStfReg( uint32_t rd );

uint32_t TxLdstub( void );

uint32_t TxCasa( void );

uint32_t TxCbccc( int32_t disp22 );

uint32_t TxStfsr( void );

uint32_t TxTicc( uint32_t cond );

uint32_t TxWrasr( uint32_t rd );

/* Writes the ELF file of the image to the file */
void TxWriteElf( const char *file, const TxImage *image );

typedef struct {
  bool sequence_a;
  bool sequence_b;
  bool middle;
  bool in_delay_slot;
} TxMemoryProbe;

/*
 * Probes the instruction with the TN-0009 sequences A and B, as the middle
 * instruction of sequence A, and in the delay slot of a CALL with TN-0011.
 */
void TxProbeMemory( uint32_t instruction, TxMemoryProbe *probe );

/*
 * Returns true, if the instruction followed by an annulling branch and an
 * FPop1 instruction gives a definite TN-0012 finding.
 */
bool TxProbeIcc( uint32_t instruction );

typedef struct {
  bool is_fpop;
  bool is_div;
  bool counted;
  bool any;
  int width[ 3 ];
} TxFpopProbe;

#define TX_RS1 0

#define TX_RS2 1

#define TX_RD 2

typedef enum { TX_KIND_FPOP1, TX_KIND_DIV, TX_KIND_FPOP2 } TxFpopKind;

/*
 * Probes the floating-point operation through the checks of TN-0012 and
 * TN-0013.  A width is 0 for no operand, and 1, 2 or 4 for the count of
 * registers of the operand.
 */
void TxProbeFpop(
  uint32_t      op3,
  uint32_t      opf,
  TxFpopKind    kind,
  TxFpopProbe *probe
);

typedef enum {
  TX_FLOW_NONE,
  TX_FLOW_DEFINITE,
  TX_FLOW_POSSIBLE
} TxFlowFinding;

/*
 * Checks the code section X, STD, A, NOP, B, NOP, BA, NOP with TN-0009.
 * The STD is in the delay slot of X.  The instruction X branches to B, if
 * the target is in the section.  A is the store and B an ADD, if
 * store_at_fall is true, otherwise the other way round.  If slot_is_target
 * is true, the BA branches to the STD, otherwise to itself.  Returns the
 * finding for the STD.
 */
TxFlowFinding TxProbeFlow(
  uint32_t x,
  bool     relocated,
  bool     slot_is_target,
  bool     store_at_fall
);

#define TX_FADDS 0x041

#define TX_FADDD 0x042

#define TX_FDIVS 0x04d

#define TX_FDIVD 0x04e

#define TX_FSQRTS 0x029

#define TX_FCMPS 0x051

#endif /* TX_SUPPORT_H */
