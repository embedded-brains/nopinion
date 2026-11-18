/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/* GRLIB-TN-0016 section 4.1: STFSR directly after an FPop1 */
static match match_0016_fpop1( const section_context *ctx, const long *p )
{
  if ( ( flags_of( ctx, p[ 0 ] ) & F_FPOP1 ) == 0 ) {
    return MATCH_NONE;
  }

  if ( p[ 1 ] == UNKNOWN ) {
    return MATCH_POSSIBLE;
  }

  return ( flags_of( ctx, p[ 1 ] ) & F_STFSR ) != 0 ? MATCH_DEFINITE
                                                    : MATCH_NONE;
}

/*
 * GRLIB-TN-0016 section 4.2: a second STFSR within the three instructions
 * after an STFSR.
 */
static match match_0016_stfsr( const section_context *ctx, const long *p )
{
  int j;

  if ( ( flags_of( ctx, p[ 0 ] ) & F_STFSR ) == 0 ) {
    return MATCH_NONE;
  }

  for ( j = 1; j <= 3; ++j ) {
    if ( p[ j ] == UNKNOWN ) {
      return MATCH_POSSIBLE;
    }

    if ( ( flags_of( ctx, p[ j ] ) & F_STFSR ) != 0 ) {
      return MATCH_DEFINITE;
    }
  }

  return MATCH_NONE;
}

const sequence_check tn0016_fpop1_check =
  { NOTE_0016, "TN-0016", "stfsr-after-fpop1", 2, match_0016_fpop1 };

const sequence_check tn0016_stfsr_check =
  { NOTE_0016, "TN-0016", "stfsr-after-stfsr", 2, match_0016_stfsr };
