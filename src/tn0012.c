/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

static bool is_fp_operation( uint32_t flags )
{
  return ( flags & ( F_FPOP1 | F_FPOP2 | F_FBFCC ) ) != 0;
}

/* GRLIB-TN-0012: integer branch and floating-point operation */
static match match_0012( const section_context *ctx, const long *p )
{
  long     branch = p[ 1 ];
  long     slot;
  long     target;
  uint32_t fb;
  match    result = MATCH_NONE;

  if ( ( flags_of( ctx, p[ 0 ] ) & F_ICC_SET ) == 0 ) {
    return MATCH_NONE;
  }

  if ( branch == UNKNOWN ) {
    return MATCH_POSSIBLE;
  }

  fb = flags_of( ctx, branch );

  if ( ( fb & F_BRANCH_ICC ) == 0 ) {
    return MATCH_NONE;
  }

  slot = next_index( ctx, branch );

  /* Sequence A: annulling branch with an FP operation in the delay slot */
  if ( ( fb & F_ANNUL ) != 0 ) {
    if ( slot == UNKNOWN ) {
      result = MATCH_POSSIBLE;
    } else if ( is_fp_operation( flags_of( ctx, slot ) ) ) {
      return MATCH_DEFINITE;
    }
  }

  /* Sequence B: FP operation at the branch target */
  target = ctx->target[ branch ];

  if ( target == UNKNOWN ) {
    return MATCH_POSSIBLE;
  }

  if ( is_fp_operation( flags_of( ctx, target ) ) ) {
    return MATCH_DEFINITE;
  }

  return result;
}

const sequence_check tn0012_check =
  { NOTE_0012, "TN-0012", "fp-after-icc-branch", 2, match_0012 };
