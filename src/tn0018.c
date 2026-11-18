/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/* STA %rd, [%g0] 2 with any rd, section B.4 of SPARC V8 */
#define STA_CCTRL_MASK 0xc1ffffffU

#define STA_CCTRL 0xc0a00040U

/* OR %l1, %l1, %l1, section B.11 of SPARC V8 */
#define OR_L1 0xa2144011U

/* OR %l2, %l2, %l2 */
#define OR_L2 0xa4148012U

/*
 * Returns true, if the six instructions before the JMPL at index i hold
 * workaround #1 of GRLIB-TN-0018 section 5.1.
 */
static bool has_workaround( const section_context *ctx, long i )
{
  bool l1 = false;
  bool l2 = false;
  long j;

  if ( i < 6 ) {
    return false;
  }

  if (
    ( insn_word( ctx, i - 6 ) & STA_CCTRL_MASK ) != STA_CCTRL ||
    ( insn_word( ctx, i - 2 ) & STA_CCTRL_MASK ) != STA_CCTRL
  ) {
    return false;
  }

  for ( j = i - 5; j <= i - 3; ++j ) {
    uint32_t w = insn_word( ctx, j );

    l1 = l1 || w == OR_L1;
    l2 = l2 || w == OR_L2;
  }

  return l1 && l2;
}

/* GRLIB-TN-0018: a JMPL, RETT pair without workaround #1 */
void check_rett( const section_context *ctx, long i )
{
  long path[ 2 ] = { i, i + 1 };

  if (
    ( flags_of( ctx, next_index( ctx, i ) ) & F_RETT ) != 0 &&
    !has_workaround( ctx, i )
  ) {
    report(
      ctx,
      i,
      "TN-0018",
      "rett-without-workaround",
      MATCH_DEFINITE,
      path,
      2
    );
  }
}

/* GRLIB-TN-0018 section 4.5.1: a trap which returns to a JMPL */
void check_trap( const section_context *ctx, long i )
{
  long  npc[ 3 ];
  long  path[ 2 ] = { i, UNKNOWN };
  int   n = next_pcs( ctx, i, npc );
  match m = MATCH_NONE;
  int   k;

  for ( k = 0; k < n; ++k ) {
    match mk = MATCH_NONE;

    if (
      npc[ k ] == UNKNOWN || ( npc[ k ] == INDIRECT && opts.include_indirect )
    ) {
      mk = MATCH_POSSIBLE;
    } else if ( ( flags_of( ctx, npc[ k ] ) & F_JMPL ) != 0 ) {
      mk = MATCH_DEFINITE;
    }

    if ( mk > m ) {
      m = mk;
      path[ 1 ] = npc[ k ] < 0 ? UNKNOWN : npc[ k ];
    }
  }

  if ( m != MATCH_NONE ) {
    report( ctx, i, "TN-0018", "trap-returns-to-jmpl", m, path, 2 );
  }
}
