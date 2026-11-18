/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/* LDA [%rs1 + %rs2] 0x1c, %g0, section B.1 of SPARC V8 */
#define LDA_BYPASS_MASK 0xfff83fe0U

#define LDA_BYPASS 0xc0800380U

/* The address area of the FTAHBRAM of the GR712RC */
#define FTAHBRAM_BEGIN 0xa0000000U

#define FTAHBRAM_END 0xa0100000U

static void report_power_down(
  const section_context *ctx,
  long                   i,
  const char            *kind,
  match                  m
)
{
  long path[ 2 ] = { i, next_index( ctx, i ) };

  report( ctx, i, "GR712RC-8", kind, m, path, 2 );
}

/*
 * Checks that no branch or jump follows the load at index i + 1 before the
 * next 32-byte boundary.
 */
static match match_branch_after_load(
  const section_context *ctx,
  long                   i,
  bool                   known
)
{
  uint32_t load_address = ctx->address + (uint32_t) ( 4 * ( i + 1 ) );
  long     last = known ? i + 1 + (long) ( ( 31 - ( load_address & 31 ) ) / 4 )
                        : i + 8;
  long     j;

  for ( j = i + 2; j <= last; ++j ) {
    if ( j >= ctx->count ) {
      return MATCH_POSSIBLE;
    }

    if ( ( flags_of( ctx, j ) & DELAYED ) != 0 ) {
      return known ? MATCH_DEFINITE : MATCH_POSSIBLE;
    }
  }

  return MATCH_NONE;
}

/* GR712RC erratum 8: workaround 2 of the power-down sequence */
void check_power_down( const section_context *ctx, long i )
{
  uint32_t address = ctx->address + (uint32_t) ( 4 * i );
  bool     known = ctx->alignment >= 32 || !ctx->relocatable;
  long     load = next_index( ctx, i );
  match    m;

  if (
    !ctx->relocatable && address >= FTAHBRAM_BEGIN && address < FTAHBRAM_END
  ) {
    report_power_down( ctx, i, "power-down-in-ftahbram", MATCH_DEFINITE );
  }

  if ( load == UNKNOWN ) {
    report_power_down( ctx, i, "power-down-without-load", MATCH_POSSIBLE );
    return;
  }

  if ( ( insn_word( ctx, load ) & LDA_BYPASS_MASK ) != LDA_BYPASS ) {
    report_power_down( ctx, i, "power-down-without-load", MATCH_DEFINITE );
    return;
  }

  if ( !known ) {
    report_power_down( ctx, i, "power-down-not-in-block", MATCH_POSSIBLE );
  } else if ( ( address & 31 ) > 12 ) {
    report_power_down( ctx, i, "power-down-not-in-block", MATCH_DEFINITE );
  }

  m = match_branch_after_load( ctx, i, known );

  if ( m != MATCH_NONE ) {
    report_power_down( ctx, i, "power-down-branch-after-load", m );
  }
}
