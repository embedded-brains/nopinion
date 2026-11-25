/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include <inttypes.h>
#include <string.h>

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

static void print_text(
  const section_context *ctx,
  uint32_t               offset,
  const symbol          *sym,
  uint32_t               delta,
  const char            *note,
  const char            *kind,
  match                  m,
  const long            *path,
  int                    path_length
)
{
  int j;

  fprintf( opts.out, "%s", ctx->file );

  if ( ctx->member != NULL ) {
    fprintf( opts.out, "(%.*s)", (int) ctx->member_length, ctx->member );
  }

  fprintf( opts.out, ": %s+0x%x", ctx->section, offset );

  if ( !ctx->relocatable ) {
    fprintf( opts.out, " [0x%08x]", ctx->address + offset );
  }

  if ( sym != NULL ) {
    fprintf( opts.out, " <%s+0x%x>", sym->name, delta );
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

/* Writes the bytes as a JSON string, RFC 8259 section 7 */
static void print_json_string( const char *s, size_t n )
{
  size_t k;

  fputc( '"', opts.out );

  for ( k = 0; k < n; ++k ) {
    unsigned char c = (unsigned char) s[ k ];

    if ( c == '"' || c == '\\' ) {
      fprintf( opts.out, "\\%c", c );
    } else if ( c < 0x20 ) {
      fprintf( opts.out, "\\u%04x", c );
    } else {
      fputc( c, opts.out );
    }
  }

  fputc( '"', opts.out );
}

/*
 * Writes the file name as a URI reference of RFC 3986.  An absolute file
 * name takes the scheme file of RFC 8089.  Each byte outside the unreserved
 * characters and the slash is percent-encoded.
 */
static void print_uri( const char *s )
{
  fputs( *s == '/' ? "\"file://" : "\"", opts.out );

  while ( *s != '\0' ) {
    unsigned char c = (unsigned char) *s;

    if (
      strchr(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~/",
        c
      ) != NULL
    ) {
      fputc( c, opts.out );
    } else {
      fprintf( opts.out, "%%%02X", c );
    }

    ++s;
  }

  fputc( '"', opts.out );
}

static void print_sarif(
  const section_context *ctx,
  uint32_t               offset,
  const symbol          *sym,
  const char            *note,
  const char            *kind,
  match                  m,
  const long            *path,
  int                    path_length
)
{
  int j;

  if ( stats.definite_count + stats.possible_count > 1 ) {
    fputc( ',', opts.out );
  }

  fprintf(
    opts.out,
    "\n{\"ruleId\":\"%s/%s\",\"level\":\"%s\",\"message\":{\"text\":"
    "\"%s %s%s\"},\"locations\":[{\"physicalLocation\":{"
    "\"artifactLocation\":{\"uri\":",
    note,
    kind,
    m == MATCH_POSSIBLE ? "warning" : "error",
    note,
    kind,
    m == MATCH_POSSIBLE ? " possible" : ""
  );
  if ( opts.relative != NULL ) {
    print_uri( opts.relative );
    fputs( ",\"uriBaseId\":", opts.out );
    print_json_string( opts.base_id, opts.base_id_length );
  } else {
    print_uri( ctx->file );
  }

  fprintf(
    opts.out,
    "},\"region\":{\"byteOffset\":%zu,\"byteLength\":4}",
    ctx->file_offset + offset
  );

  if ( !ctx->relocatable ) {
    fprintf(
      opts.out,
      ",\"address\":{\"absoluteAddress\":%" PRIu32
      ",\"kind\":\"instruction\"}",
      ctx->address + offset
    );
  }

  fputc( '}', opts.out );

  if ( sym != NULL ) {
    fputs( ",\"logicalLocations\":[{\"name\":", opts.out );
    print_json_string( sym->name, strlen( sym->name ) );
    fputs( ",\"kind\":\"function\"}]", opts.out );
  }

  fputs( ",\"properties\":{", opts.out );

  if ( ctx->member != NULL ) {
    fputs( "\"member\":", opts.out );
    print_json_string( ctx->member, ctx->member_length );
    fputc( ',', opts.out );
  }

  fputs( "\"section\":", opts.out );
  print_json_string( ctx->section, strlen( ctx->section ) );
  fprintf( opts.out, ",\"offset\":%" PRIu32 "}}]", offset );

  if ( opts.verbose ) {
    fputs( ",\"properties\":{\"instructions\":[", opts.out );

    for ( j = 0; j < path_length; ++j ) {
      if ( j > 0 ) {
        fputc( ',', opts.out );
      }

      if ( path[ j ] == UNKNOWN ) {
        fputs( "null", opts.out );
        break;
      }

      fprintf(
        opts.out,
        "{\"offset\":%ld,\"word\":%" PRIu32 "}",
        4 * path[ j ],
        insn_word( ctx, path[ j ] )
      );
    }

    fputs( "]}", opts.out );
  }

  fputc( '}', opts.out );
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
  uint32_t      key = ctx->relocatable ? offset : ctx->address + offset;
  const symbol *sym;

  if ( m == MATCH_DEFINITE ) {
    ++stats.definite_count;
  } else {
    ++stats.possible_count;
  }

  if ( opts.quiet ) {
    return;
  }

  sym = find_symbol( ctx, key );

  if ( opts.sarif ) {
    print_sarif( ctx, offset, sym, note, kind, m, path, path_length );
  } else {
    print_text(
      ctx,
      offset,
      sym,
      sym != NULL ? key - sym->value : 0,
      note,
      kind,
      m,
      path,
      path_length
    );
  }
}

/* The log follows the OASIS Standard SARIF Version 2.1.0 */
void report_begin( void )
{
  if ( opts.sarif && !opts.quiet ) {
    fputs(
      "{\"version\":\"2.1.0\",\"$schema\":\"https://docs.oasis-open.org/"
      "sarif/sarif/v2.1.0/errata01/os/schemas/sarif-schema-2.1.0.json\","
      "\"runs\":[{\"tool\":{\"driver\":{\"name\":\"nopinion\","
      "\"informationUri\":\"https://github.com/embedded-brains/nopinion\"}},",
      opts.out
    );

    /* The log omits the absolute URI of the base directory */
    if ( opts.base != NULL ) {
      fputs( "\"originalUriBaseIds\":{", opts.out );
      print_json_string( opts.base_id, opts.base_id_length );
      fputs( ":{}},", opts.out );
    }

    fputs( "\"results\":[", opts.out );
  }
}

void report_end( void )
{
  if ( opts.sarif && !opts.quiet ) {
    fprintf(
      opts.out,
      "\n],\"invocations\":[{\"executionSuccessful\":%s}]}]}\n",
      stats.had_error ? "false" : "true"
    );
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
