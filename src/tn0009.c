/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/* GRLIB-TN-0009: back-to-back stores */
static match match_0009( const section_context *ctx, const long *p )
{
  uint32_t f0 = flags_of( ctx, p[ 0 ] );

  /*
   * Sequence A: store of word size or less, any instruction other than a
   * load or store, any store.
   */
  if ( ( f0 & ( F_STORE | F_STORE_DOUBLE ) ) == F_STORE ) {
    if ( p[ 1 ] == UNKNOWN ) {
      return MATCH_POSSIBLE;
    }

    if ( ( flags_of( ctx, p[ 1 ] ) & F_MEM ) == 0 ) {
      if ( p[ 2 ] == UNKNOWN ) {
        return MATCH_POSSIBLE;
      }

      if ( ( flags_of( ctx, p[ 2 ] ) & F_STORE ) != 0 ) {
        return MATCH_DEFINITE;
      }
    }
  }

  /* Sequence B: store of double word size, any store */
  if ( ( f0 & F_STORE_DOUBLE ) != 0 ) {
    if ( p[ 1 ] == UNKNOWN ) {
      return MATCH_POSSIBLE;
    }

    if ( ( flags_of( ctx, p[ 1 ] ) & F_STORE ) != 0 ) {
      return MATCH_DEFINITE;
    }
  }

  return MATCH_NONE;
}

const sequence_check tn0009_check =
  { NOTE_0009, "TN-0009", "back-to-back-store", 3, match_0009 };
