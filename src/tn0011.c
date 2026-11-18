/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/*
 * GRLIB-TN-0011: an atomic instruction shall start a 16-byte block and
 * shall not be in the delay slot of a PC-relative control-transfer
 * instruction.
 */
void check_atomic( const section_context *ctx, long i )
{
  long     path[ 1 ] = { i };
  uint32_t offset = (uint32_t) ( 4 * i );

  if ( i > 0 && ( flags_of( ctx, i - 1 ) & F_PC_RELATIVE ) != 0 ) {
    report(
      ctx,
      i,
      "TN-0011",
      "atomic-in-delay-slot",
      MATCH_DEFINITE,
      path,
      1
    );
  }

  if ( ctx->alignment >= 16 || !ctx->relocatable ) {
    if ( ( ( ctx->address + offset ) & 0xf ) != 0 ) {
      report(
        ctx,
        i,
        "TN-0011",
        "atomic-not-aligned",
        MATCH_DEFINITE,
        path,
        1
      );
    }
  } else {
    report( ctx, i, "TN-0011", "atomic-not-aligned", MATCH_POSSIBLE, path, 1 );
  }
}
