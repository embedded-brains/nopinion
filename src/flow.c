/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include <string.h>

#include "nopinion.h"

typedef struct {
  long pc;
  long npc;
  bool annulled;
} state;

static const sequence_check *const sequence_checks[] = {
  &tn0009_check,
  &tn0012_check,
  &tn0013_check,
  &tn0016_fpop1_check,
  &tn0016_stfsr_check
};

#define SEQUENCE_CHECK_COUNT \
  ( sizeof( sequence_checks ) / sizeof( sequence_checks[ 0 ] ) )

typedef struct {
  match m[ SEQUENCE_CHECK_COUNT ];
  long  path[ SEQUENCE_CHECK_COUNT ][ PATH_LENGTH ];
} sequence_result;

long next_index( const section_context *ctx, long i )
{
  if ( i < 0 || i + 1 >= ctx->count ) {
    return UNKNOWN;
  }

  return i + 1;
}

static state make_state( long pc, long npc, bool annulled )
{
  state s = { pc, npc, annulled };

  return s;
}

/* Returns the states which may follow the instruction at s.pc */
static int step( const section_context *ctx, state s, state *next )
{
  const insn_info *info;
  uint32_t         flags;
  long             target;
  long             npc_next = next_index( ctx, s.npc );

  if ( s.annulled ) {
    next[ 0 ] = make_state( s.npc, npc_next, false );
    return 1;
  }

  info = &ctx->info[ s.pc ];
  flags = info->flags;
  target = ctx->target[ s.pc ];

  if ( ( flags & F_BRANCH ) != 0 ) {
    uint32_t cond = ( insn_word( ctx, s.pc ) >> 25 ) & 0xf;
    bool     annul = ( flags & F_ANNUL ) != 0;
    int      n = 0;

    if ( cond == 0x8 ) {
      next[ 0 ] = make_state( s.npc, target, annul );
      return 1;
    }

    if ( cond != 0x0 ) {
      next[ n ] = make_state( s.npc, target, false );
      ++n;
    }

    next[ n ] = make_state( s.npc, npc_next, annul );
    return n + 1;
  }

  if ( ( flags & F_CALL ) != 0 ) {
    next[ 0 ] = make_state( s.npc, target, false );
  } else if ( ( flags & F_INDIRECT ) != 0 ) {
    next[ 0 ] = make_state( s.npc, INDIRECT, false );
  } else if ( ( flags & F_TRAP_ALWAYS ) != 0 ) {
    next[ 0 ] = make_state( INDIRECT, UNKNOWN, false );
  } else {
    next[ 0 ] = make_state( s.npc, npc_next, false );
  }

  return 1;
}

static const insn_info no_info;

const insn_info *info_of( const section_context *ctx, long i )
{
  return i < 0 ? &no_info : &ctx->info[ i ];
}

uint32_t flags_of( const section_context *ctx, long i )
{
  return info_of( ctx, i )->flags;
}

match combine( bool used_unknown )
{
  return used_unknown ? MATCH_POSSIBLE : MATCH_DEFINITE;
}

static void check_path(
  const section_context *ctx,
  const long            *path,
  sequence_result       *r
)
{
  size_t c;

  for ( c = 0; c < SEQUENCE_CHECK_COUNT; ++c ) {
    const sequence_check *check = sequence_checks[ c ];
    match                 m;

    if (
      ( opts.enabled_notes & check->note ) == 0 || r->m[ c ] == MATCH_DEFINITE
    ) {
      continue;
    }

    m = ( *check->match )( ctx, path );

    if ( m > r->m[ c ] ) {
      r->m[ c ] = m;
      memcpy( r->path[ c ], path, sizeof( r->path[ c ] ) );
    }
  }
}

static void walk(
  const section_context *ctx,
  state                  s,
  long                  *path,
  int                    depth,
  sequence_result       *r
)
{
  state next[ 2 ];
  int   n;
  int   k;

  if ( s.annulled ) {
    path[ depth ] = ANNULLED;
  } else if ( s.pc == INDIRECT ) {
    path[ depth ] = opts.include_indirect ? UNKNOWN : END;
  } else {
    path[ depth ] = s.pc;
  }

  if (
    path[ depth ] == UNKNOWN || path[ depth ] == END ||
    depth + 1 == PATH_LENGTH
  ) {
    for ( k = depth + 1; k < PATH_LENGTH; ++k ) {
      path[ k ] = path[ depth ] == END ? END : UNKNOWN;
    }

    check_path( ctx, path, r );
    return;
  }

  n = step( ctx, s, next );

  for ( k = 0; k < n; ++k ) {
    walk( ctx, next[ k ], path, depth + 1, r );
  }
}

/* Returns the states which may execute the instruction */
static int start_states( const section_context *ctx, long i, state *starts )
{
  int start_count = 0;
  int k;

  /*
   * The instruction may be in the delay slot of the previous instruction.
   * Otherwise, or if a branch targets it, the next instruction follows it.
   */
  if ( i > 0 && ( flags_of( ctx, i - 1 ) & DELAYED ) != 0 ) {
    state prev = make_state( i - 1, i, false );
    state next[ 2 ];
    int   n = step( ctx, prev, next );

    for ( k = 0; k < n; ++k ) {
      if ( !next[ k ].annulled ) {
        starts[ start_count ] = next[ k ];
        ++start_count;
      }
    }

    if ( ( flags_of( ctx, i ) & F_TARGET ) != 0 ) {
      starts[ start_count ] = make_state( i, next_index( ctx, i ), false );
      ++start_count;
    }
  } else {
    starts[ start_count ] = make_state( i, next_index( ctx, i ), false );
    ++start_count;
  }

  return start_count;
}

int next_pcs( const section_context *ctx, long i, long *npc )
{
  state starts[ 3 ];
  int   n = start_states( ctx, i, starts );
  int   k;

  for ( k = 0; k < n; ++k ) {
    npc[ k ] = starts[ k ].npc;
  }

  return n;
}

static void check_sequences( const section_context *ctx, long i )
{
  sequence_result r;
  long            path[ PATH_LENGTH ];
  state           starts[ 3 ];
  int             start_count;
  int             k;

  memset( &r, 0, sizeof( r ) );
  start_count = start_states( ctx, i, starts );

  for ( k = 0; k < start_count; ++k ) {
    walk( ctx, starts[ k ], path, 0, &r );
  }

  for ( k = 0; k < (int) SEQUENCE_CHECK_COUNT; ++k ) {
    const sequence_check *check = sequence_checks[ k ];

    if ( r.m[ k ] != MATCH_NONE ) {
      report(
        ctx,
        i,
        check->name,
        check->kind,
        r.m[ k ],
        r.path[ k ],
        check->report_length
      );
    }
  }
}

void check_section( section_context *ctx )
{
  long i;

  decode( ctx );
  stats.instruction_count += (unsigned long) ctx->count;

  for ( i = 0; i < ctx->count; ++i ) {
    uint32_t flags = ctx->info[ i ].flags;

    if ( ( flags & F_SEQUENCE_START ) != 0 ) {
      check_sequences( ctx, i );
    }

    if (
      ( flags & F_ATOMIC ) != 0 && ( opts.enabled_notes & NOTE_0011 ) != 0
    ) {
      check_atomic( ctx, i );
    }

    if ( ( opts.enabled_notes & NOTE_0018 ) != 0 ) {
      if ( ( flags & F_JMPL ) != 0 ) {
        check_rett( ctx, i );
      }

      if ( ( flags & F_TICC ) != 0 ) {
        check_trap( ctx, i );
      }
    }

    if (
      ( flags & ( F_STORE_ASI_1C | F_ATOMIC_ASI_1C ) ) != 0 &&
      ( opts.enabled_notes & NOTE_ASI_1C ) != 0
    ) {
      check_asi_1c( ctx, i );
    }

    if (
      ( flags & F_POWER_DOWN ) != 0 &&
      ( opts.enabled_notes & NOTE_POWER_DOWN ) != 0
    ) {
      check_power_down( ctx, i );
    }
  }
}
