/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#ifndef NOPINION_H
#define NOPINION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define NOTE_0009 0x1U

#define NOTE_0011 0x2U

#define NOTE_0012 0x4U

#define NOTE_0013 0x8U

#define NOTE_0016 0x10U

#define NOTE_0018 0x20U

/* GR712RC erratum 19 and GR740 erratum 20-1 */
#define NOTE_ASI_1C 0x40U

/* GR712RC erratum 8 */
#define NOTE_POWER_DOWN 0x80U

#define NOTE_ALL                                                            \
  ( NOTE_0009 | NOTE_0011 | NOTE_0012 | NOTE_0013 | NOTE_0016 | NOTE_0018 | \
    NOTE_ASI_1C | NOTE_POWER_DOWN )

/* An index of an instruction which is outside the section or unknown */
#define UNKNOWN ( -1L )

/*
 * A path element of an annulled delay slot.  The annulled instruction
 * passes through the pipeline without an effect.
 */
#define ANNULLED ( -2L )

/* The index of the instruction after a JMPL, RETT or trap always */
#define INDIRECT ( -3L )

/* A path element after a path leaves through JMPL, RETT or trap always */
#define END ( -4L )

/* The longest sequence: FDIV/FSQRT, three instructions, FDIV/FSQRT */
#define PATH_LENGTH 5

enum {
  F_MEM = 1U << 0,
  F_STORE = 1U << 1,
  F_STORE_DOUBLE = 1U << 2,
  F_ATOMIC = 1U << 3,
  F_ICC_SET = 1U << 4,
  F_BRANCH = 1U << 5,
  F_BRANCH_ICC = 1U << 6,
  F_ANNUL = 1U << 7,
  F_FBFCC = 1U << 8,
  F_FPOP1 = 1U << 9,
  F_FPOP2 = 1U << 10,
  F_FDIV_FSQRT = 1U << 11,
  F_FLOAD = 1U << 12,
  F_FSTORE = 1U << 13,
  F_CALL = 1U << 14,
  F_INDIRECT = 1U << 15,
  F_RELOC = 1U << 16,
  F_TARGET = 1U << 17,
  F_TRAP_ALWAYS = 1U << 18,
  F_STFSR = 1U << 19,
  F_JMPL = 1U << 20,
  F_RETT = 1U << 21,
  F_TICC = 1U << 22,
  F_POWER_DOWN = 1U << 23,
  F_STORE_ASI_1C = 1U << 24,
  F_ATOMIC_ASI_1C = 1U << 25
};

#define F_PC_RELATIVE ( F_BRANCH | F_CALL )

#define DELAYED ( F_BRANCH | F_CALL | F_INDIRECT )

#define F_SEQUENCE_START ( F_STORE | F_ICC_SET | F_FPOP1 )

typedef enum { MATCH_NONE, MATCH_POSSIBLE, MATCH_DEFINITE } match;

typedef struct {
  uint32_t flags;
  uint32_t fp_src;
  uint32_t fp_dst;
} insn_info;

typedef struct {
  uint32_t    value;
  const char *name;
} symbol;

typedef struct {
  const char    *file;
  const char    *member;
  size_t         member_length;
  const char    *section;
  uint32_t       address;
  size_t         file_offset;
  size_t         member_offset;
  uint32_t       alignment;
  bool           relocatable;
  const uint8_t *code;
  long           count;
  insn_info     *info;
  long          *target;
  symbol        *symbols;
  size_t         symbol_count;
} section_context;

/*
 * A sequence check matches a path of instruction indices which starts at
 * the instruction under check.
 */
typedef struct {
  unsigned int note;
  const char  *name;
  const char  *kind;
  int          report_length;
  match ( *match )( const section_context *ctx, const long *path );
} sequence_check;

/* A URI base id of the option -b NAME=DIR */
typedef struct {
  const char *id;
  size_t      id_length;
  char       *directory;
  size_t      directory_length;
} base;

/*
 * An artifact of the SARIF log: an archive, or a member of an archive with
 * the index of the archive as its parent
 */
typedef struct artifact {
  struct artifact *next;
  size_t           index;
  size_t           parent;
  const base      *relative_base;
  const char      *member;
  size_t           member_length;
  char             uri[];
} artifact;

typedef struct {
  FILE        *out;
  FILE        *err;
  unsigned int enabled_notes;
  bool         quiet;
  bool         verbose;
  bool         include_indirect;
  bool         sarif;
  base        *bases;
  size_t       base_count;
  char        *real;
  const char  *relative;
  const base  *relative_base;
  artifact    *artifacts;
  artifact   **artifact_tail;
  size_t       artifact_count;
  artifact    *archive;
  artifact    *member;
  bool         artifacts_failed;
} options;

typedef struct {
  unsigned long definite_count;
  unsigned long possible_count;
  unsigned long instruction_count;
  bool          had_error;
} statistics;

extern options opts;

extern statistics stats;

extern const sequence_check tn0009_check;

extern const sequence_check tn0012_check;

extern const sequence_check tn0013_check;

extern const sequence_check tn0016_fpop1_check;

extern const sequence_check tn0016_stfsr_check;

static inline uint32_t get_be32( const uint8_t *p )
{
  return ( (uint32_t) p[ 0 ] << 24 ) | ( (uint32_t) p[ 1 ] << 16 ) |
         ( (uint32_t) p[ 2 ] << 8 ) | (uint32_t) p[ 3 ];
}

static inline uint16_t get_be16( const uint8_t *p )
{
  return (uint16_t) ( ( p[ 0 ] << 8 ) | p[ 1 ] );
}

static inline uint32_t insn_word( const section_context *ctx, long i )
{
  return get_be32( ctx->code + 4 * i );
}

/* decode.c */

void decode( section_context *ctx );

/* flow.c */

long next_index( const section_context *ctx, long i );

const insn_info *info_of( const section_context *ctx, long i );

/*
 * Stores the index of the instruction after the instruction for each way
 * of the flow to reach the instruction and returns the count of indices.
 * An index is UNKNOWN or INDIRECT for a target which is not in the section.
 */
int next_pcs( const section_context *ctx, long i, long *npc );

uint32_t flags_of( const section_context *ctx, long i );

match combine( bool used_unknown );

void check_section( section_context *ctx );

/* tn0011.c */

void check_atomic( const section_context *ctx, long i );

/* tn0018.c */

void check_rett( const section_context *ctx, long i );

void check_trap( const section_context *ctx, long i );

/* asi1c.c */

void check_asi_1c( const section_context *ctx, long i );

/* powerdown.c */

void check_power_down( const section_context *ctx, long i );

/* elf.c */

void check_buffer( const char *file, const uint8_t *data, size_t size );

void check_file( const char *file );

/* cli.c */

int nopinion_main( int argc, char **argv, FILE *out, FILE *err );

/* report.c */

void report(
  const section_context *ctx,
  long                   start,
  const char            *note,
  const char            *kind,
  match                  m,
  const long            *path,
  int                    path_length
);

void report_begin( void );

void report_end( void );

void report_file_end( void );

void error(
  const char *file,
  const char *member,
  size_t      member_length,
  const char *msg
);

#endif /* NOPINION_H */
