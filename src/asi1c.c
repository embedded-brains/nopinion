/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

/*
 * GR712RC erratum 19 and GR740 erratum 20-1: a store with ASI 0x1C may
 * update the data cache.
 */
void check_asi_1c( const section_context *ctx, long i )
{
  long path[ 1 ] = { i };

  report(
    ctx,
    i,
    "GR712RC-19/GR740-20-1",
    ( flags_of( ctx, i ) & F_ATOMIC_ASI_1C ) != 0 ? "atomic-asi-0x1c"
                                                  : "store-asi-0x1c",
    MATCH_DEFINITE,
    path,
    1
  );
}
