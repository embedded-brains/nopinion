/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

options opts;

statistics stats;

static const symbol *find_symbol( const section_context *ctx, uint32_t offset )
{
  size_t lo = 0;
  size_t hi = ctx->symbol_count;

  while ( lo < hi ) {
    size_t mid = lo + ( hi - lo ) / 2;

    if ( ctx->symbols[ mid ].value <= offset ) {
      lo = mid + 1;
    } else {
      hi = mid;
    }
  }

  return lo > 0 ? &ctx->symbols[ lo - 1 ] : NULL;
}

void report(
  const section_context *ctx,
  long                   start,
  const char            *note,
  const char            *kind,
  match                  m,
  const long            *path,
  int                    path_length
)
{
  uint32_t      offset = (uint32_t) ( 4 * start );
  uint32_t      address = ctx->address + offset;
  const symbol *sym;
  int           j;

  if ( m == MATCH_DEFINITE ) {
    ++stats.definite_count;
  } else {
    ++stats.possible_count;
  }

  if ( opts.quiet ) {
    return;
  }

  fprintf( opts.out, "%s", ctx->file );

  if ( ctx->member != NULL ) {
    fprintf( opts.out, "(%.*s)", (int) ctx->member_length, ctx->member );
  }

  fprintf( opts.out, ": %s+0x%x", ctx->section, offset );

  if ( !ctx->relocatable ) {
    fprintf( opts.out, " [0x%08x]", address );
  }

  sym = find_symbol( ctx, ctx->relocatable ? offset : address );

  if ( sym != NULL ) {
    fprintf(
      opts.out,
      " <%s+0x%x>",
      sym->name,
      ( ctx->relocatable ? offset : address ) - sym->value
    );
  }

  fprintf(
    opts.out,
    ": %s %s%s\n",
    note,
    kind,
    m == MATCH_POSSIBLE ? " possible" : ""
  );

  if ( opts.verbose ) {
    for ( j = 0; j < path_length; ++j ) {
      if ( path[ j ] == UNKNOWN ) {
        fprintf( opts.out, "  %8s  ?\n", "" );
        break;
      }

      fprintf(
        opts.out,
        "  %08x  %08x\n",
        (unsigned) ( 4 * path[ j ] ),
        (unsigned) insn_word( ctx, path[ j ] )
      );
    }
  }
}

void error(
  const char *file,
  const char *member,
  size_t      member_length,
  const char *msg
)
{
  stats.had_error = true;

  if ( member != NULL ) {
    fprintf(
      opts.err,
      "nopinion: %s(%.*s): %s\n",
      file,
      (int) member_length,
      member,
      msg
    );
  } else {
    fprintf( opts.err, "nopinion: %s: %s\n", file, msg );
  }
}
