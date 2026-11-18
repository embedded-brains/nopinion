/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/*
 * GRLIB-TN-0013: FDIV/FSQRT, two or three instructions with at least two
 * independent FPop1 or FP load instructions, FDIV/FSQRT.
 */
static match match_0013_window(
  const section_context *ctx,
  const long            *p,
  int                    window
)
{
  uint32_t dst = info_of( ctx, p[ 0 ] )->fp_dst;
  int      counted = 0;
  bool     used_unknown = false;
  long     last = p[ window + 1 ];
  int      j;

  for ( j = 1; j <= window; ++j ) {
    const insn_info *info;

    if ( p[ j ] == UNKNOWN ) {
      return counted + window - j + 1 >= 2 ? MATCH_POSSIBLE : MATCH_NONE;
    }

    info = info_of( ctx, p[ j ] );

    if ( ( info->flags & F_FDIV_FSQRT ) != 0 ) {
      if ( j <= 2 ) {
        return MATCH_NONE;
      }

      continue;
    }

    if ( ( info->flags & ( F_FPOP1 | F_FLOAD ) ) != 0 ) {
      if ( ( ( info->fp_src | info->fp_dst ) & dst ) != 0 ) {
        return MATCH_NONE;
      }

      ++counted;
      continue;
    }

    if (
      ( info->flags & ( F_FPOP2 | F_FSTORE ) ) != 0 &&
      ( info->fp_src & dst ) != 0
    ) {
      return MATCH_NONE;
    }
  }

  if ( counted < 2 ) {
    return MATCH_NONE;
  }

  if ( last == UNKNOWN ) {
    used_unknown = true;
  } else {
    const insn_info *info = info_of( ctx, last );

    if (
      ( info->flags & F_FDIV_FSQRT ) == 0 ||
      ( ( info->fp_src | info->fp_dst ) & dst ) != 0
    ) {
      return MATCH_NONE;
    }
  }

  return combine( used_unknown );
}

static match match_0013( const section_context *ctx, const long *p )
{
  match a;
  match b;

  if ( ( flags_of( ctx, p[ 0 ] ) & F_FDIV_FSQRT ) == 0 ) {
    return MATCH_NONE;
  }

  a = match_0013_window( ctx, p, 2 );

  if ( a == MATCH_DEFINITE ) {
    return a;
  }

  b = match_0013_window( ctx, p, 3 );
  return a > b ? a : b;
}

const sequence_check tn0013_check =
  { NOTE_0013, "TN-0013", "fdiv-fsqrt-sequence", PATH_LENGTH, match_0013 };
