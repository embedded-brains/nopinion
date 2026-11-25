/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include <inttypes.h>
#include <stdlib.h>
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
static void print_uri( const char *s, size_t n )
{
  size_t k;

  fputs( *s == '/' ? "\"file://" : "\"", opts.out );

  for ( k = 0; k < n; ++k ) {
    unsigned char c = (unsigned char) s[ k ];

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
  }

  fputc( '"', opts.out );
}

static artifact *new_artifact(
  const section_context *ctx,
  const char            *uri,
  size_t                 uri_length
)
{
  artifact *a = malloc( sizeof( *a ) + uri_length + 1 );

  if ( a == NULL ) {
    error( ctx->file, ctx->member, ctx->member_length, "out of memory" );
    return NULL;
  }

  a->next = NULL;
  a->index = opts.artifact_count;
  a->parent = 0;
  a->relative_base = NULL;
  a->member = NULL;
  a->member_length = uri_length;
  memcpy( a->uri, uri, uri_length );
  a->uri[ uri_length ] = '\0';
  *opts.artifact_tail = a;
  opts.artifact_tail = &a->next;
  ++opts.artifact_count;
  return a;
}

static bool has_uri( const artifact *a, const char *uri, size_t uri_length )
{
  return a->member_length == uri_length &&
         memcmp( a->uri, uri, uri_length ) == 0;
}

/* Returns the artifact of the archive with the URI and the base, or NULL */
static artifact *find_archive( const char *uri, size_t n, const base *b )
{
  artifact *a;

  for ( a = opts.artifacts; a != NULL; a = a->next ) {
    if ( a->member == NULL && a->relative_base == b && has_uri( a, uri, n ) ) {
      return a;
    }
  }

  return NULL;
}

/* Returns the artifact of the member with the name in the archive, or NULL */
static artifact *find_member( const char *name, size_t n, size_t parent )
{
  artifact *a;

  for ( a = opts.artifacts; a != NULL; a = a->next ) {
    if ( a->member != NULL && a->parent == parent && has_uri( a, name, n ) ) {
      return a;
    }
  }

  return NULL;
}

/*
 * Returns the artifact of the member of the section and adds it and the
 * artifact of its archive on demand.  Returns NULL, if no memory is
 * available.
 */
static const artifact *member_artifact( const section_context *ctx )
{
  /* After an allocation failure, each result of the file names the archive */
  if ( opts.artifacts_failed ) {
    return NULL;
  }

  if ( opts.archive == NULL ) {
    const char *uri = opts.relative != NULL ? opts.relative : ctx->file;
    size_t      n = strlen( uri );

    opts.archive = find_archive( uri, n, opts.relative_base );

    if ( opts.archive == NULL ) {
      opts.archive = new_artifact( ctx, uri, n );

      if ( opts.archive == NULL ) {
        opts.artifacts_failed = true;
        return NULL;
      }

      opts.archive->relative_base = opts.relative_base;
    }
  }

  /* The sections of one member share the pointer to its name */
  if ( opts.member == NULL || opts.member->member != ctx->member ) {
    artifact *member = find_member(
      ctx->member,
      ctx->member_length,
      opts.archive->index
    );

    if ( member == NULL ) {
      member = new_artifact( ctx, ctx->member, ctx->member_length );

      if ( member == NULL ) {
        opts.artifacts_failed = true;
        return NULL;
      }

      member->parent = opts.archive->index;
    }

    member->member = ctx->member;
    opts.member = member;
  }

  return opts.member;
}

static void print_top_level( const char *uri, const base *b )
{
  print_uri( uri, strlen( uri ) );

  if ( b != NULL ) {
    fputs( ",\"uriBaseId\":", opts.out );
    print_json_string( b->id, b->id_length );
  }
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
  const artifact *member = NULL;
  size_t          region = ctx->file_offset + offset;
  int             j;

  if ( ctx->member != NULL ) {
    member = member_artifact( ctx );
  }

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
  if ( member != NULL ) {
    print_uri( member->uri, member->member_length );
    fprintf( opts.out, ",\"index\":%zu", member->index );
  } else {
    /*
     * Without the artifact of the member, the location names the archive
     * and the offset of the instruction in the archive.
     */
    print_top_level(
      opts.relative != NULL ? opts.relative : ctx->file,
      opts.relative_base
    );
    region += ctx->member_offset;
  }

  fprintf(
    opts.out,
    "},\"region\":{\"byteOffset\":%zu,\"byteLength\":4}",
    region
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

  fputs( ",\"properties\":{\"section\":", opts.out );
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

    /* The log omits the absolute URIs of the base directories */
    if ( opts.base_count > 0 ) {
      size_t k;

      fputs( "\"originalUriBaseIds\":{", opts.out );

      for ( k = 0; k < opts.base_count; ++k ) {
        if ( k > 0 ) {
          fputc( ',', opts.out );
        }

        print_json_string( opts.bases[ k ].id, opts.bases[ k ].id_length );
        fputs( ":{}", opts.out );
      }

      fputs( "},", opts.out );
    }

    fputs( "\"results\":[", opts.out );
  }

  opts.artifacts = NULL;
  opts.artifact_tail = &opts.artifacts;
  opts.artifact_count = 0;
  opts.archive = NULL;
  opts.member = NULL;
}

void report_file_end( void )
{
  opts.archive = NULL;
  opts.member = NULL;
  opts.artifacts_failed = false;
}

void report_end( void )
{
  artifact *a = opts.artifacts;

  if ( opts.sarif && !opts.quiet ) {
    fputs( "\n]", opts.out );

    if ( a != NULL ) {
      fputs( ",\"artifacts\":[", opts.out );
    }

    while ( a != NULL ) {
      artifact *next = a->next;

      fputs( "{\"location\":{\"uri\":", opts.out );

      if ( a->member == NULL ) {
        print_top_level( a->uri, a->relative_base );
        fputs( "}}", opts.out );
      } else {
        print_uri( a->uri, a->member_length );
        fprintf( opts.out, "},\"parentIndex\":%zu}", a->parent );
      }

      fputs( next != NULL ? "," : "]", opts.out );
      free( a );
      a = next;
    }

    fprintf(
      opts.out,
      ",\"invocations\":[{\"executionSuccessful\":%s}]}]}\n",
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
