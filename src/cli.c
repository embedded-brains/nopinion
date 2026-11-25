/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nopinion.h"

/*
 * This program scans the code of SPARC V8 ELF files for the instruction
 * sequences of the following errata of the LEON3FT and LEON4 processors:
 *
 * - GRLIB-TN-0009: stale cache entry after store with data tag parity error
 *
 * - GRLIB-TN-0011: AHB lock release during atomic operation
 *
 * - GRLIB-TN-0012: incorrect annulation of floating-point operation on
 *   instruction cache parity error
 *
 * - GRLIB-TN-0013: missing FDIV/FSQRT result
 *
 * - GRLIB-TN-0016: FSR register behaviour of the GRFPC
 *
 * - GRLIB-TN-0018: RETT restart
 *
 * - GR712RC erratum 19 and GR740 erratum 20-1: stores to ASI 0x1C
 *
 * - GR712RC erratum 8: bus access after power-down
 *
 * The rules follow the descriptions of these errata and the instruction
 * formats of the SPARC Architecture Manual Version 8.
 *
 * An input file is an ELF32 big-endian SPARC object file, executable or
 * shared object, or an archive of such object files.  The program follows
 * the control flow through the delay slots.  The target of a PC-relative
 * control-transfer instruction is known unless a relocation applies to the
 * instruction.  The target of JMPL, RETT and trap always is unknown.  By
 * default, a sequence ends at such an unknown target.  An unknown
 * instruction matches every element of a sequence.  A match which needs an
 * unknown instruction is reported as possible.
 */

typedef struct {
  const char  *name;
  unsigned int notes;
} name_to_notes;

static const name_to_notes note_names[] = {
  { "0009", NOTE_0009 },
  { "0011", NOTE_0011 },
  { "0012", NOTE_0012 },
  { "0013", NOTE_0013 },
  { "0016", NOTE_0016 },
  { "0018", NOTE_0018 },
  { "gr712rc-8", NOTE_POWER_DOWN },
  { "gr712rc-19", NOTE_ASI_1C },
  { "gr740-20-1", NOTE_ASI_1C }
};

#define NOTE_NAME_COUNT ( sizeof( note_names ) / sizeof( note_names[ 0 ] ) )

static const name_to_notes part_names[] = {
  { "gr712rc", NOTE_ALL },
  { "gr740", NOTE_0016 | NOTE_ASI_1C },
  { "leon3ft-rtax", NOTE_0009 | NOTE_0011 | NOTE_0018 },
  { "ut699", NOTE_0009 | NOTE_0011 | NOTE_0013 | NOTE_0016 | NOTE_0018 },
  { "ut699e", NOTE_0009 | NOTE_0011 | NOTE_0013 | NOTE_0016 | NOTE_0018 },
  { "ut700", NOTE_0009 | NOTE_0011 | NOTE_0013 | NOTE_0016 | NOTE_0018 }
};

#define PART_NAME_COUNT ( sizeof( part_names ) / sizeof( part_names[ 0 ] ) )

/* Returns the notes of the name of length n, or 0 for an unknown name */
static unsigned int find_name(
  const name_to_notes *table,
  size_t               count,
  const char          *name,
  size_t               n
)
{
  size_t k;

  for ( k = 0; k < count; ++k ) {
    if (
      strncmp( name, table[ k ].name, n ) == 0 && table[ k ].name[ n ] == '\0'
    ) {
      return table[ k ].notes;
    }
  }

  return 0;
}

static bool parse_notes( const char *arg, unsigned int *notes )
{
  *notes = 0;

  while ( *arg != '\0' ) {
    size_t n = strcspn( arg, "," );

    if ( n > 0 ) {
      unsigned int found = find_name( note_names, NOTE_NAME_COUNT, arg, n );

      if ( found == 0 ) {
        return false;
      }

      *notes |= found;
    }

    arg += n;

    if ( *arg == ',' ) {
      ++arg;
    }
  }

  return *notes != 0;
}

static void usage( FILE *out )
{
  fprintf(
    out,
    "usage: nopinion [-b NAME=DIR] [-f FORMAT] [-p PART] [-t ERRATA] [-i] [-q]\n"
    "                [-s] [-v] FILE...\n"
    "\n"
    "Scans SPARC ELF files and archives for the instruction sequences of\n"
    "the errata GRLIB-TN-0009, -0011, -0012, -0013, -0016 and -0018, of\n"
    "the GR712RC errata 8 and 19, and of the GR740 erratum 20-1.\n"
    "\n"
    "  -b NAME=DIR\n"
    "             in a SARIF log, give the URI of each file below the\n"
    "             directory relative to the URI base id NAME\n"
    "  -f FORMAT  write the report as text (default) or as a SARIF 2.1.0\n"
    "             log: text or sarif\n"
    "  -p PART    check only the errata which affect the part: gr712rc,\n"
    "             gr740, leon3ft-rtax, ut699, ut699e or ut700\n"
    "  -t ERRATA  comma-separated list of errata to check, for example\n"
    "             0009,gr712rc-8 (default: 0009,0011,0012,0013,0016,0018,\n"
    "             gr712rc-8,gr712rc-19,gr740-20-1)\n"
    "  -i         match an unknown instruction after JMPL, RETT and\n"
    "             trap always\n"
    "  -q         report nothing, only set the exit status\n"
    "  -s         print statistics to the standard error\n"
    "  -v         print the instruction words of each sequence\n"
    "\n"
    "Exit status: 0 no sequence found, 1 a sequence found, 2 an error\n"
  );
}

/* Selects the base directory of the option -b NAME=DIR */
static int set_base( const char *arg, FILE *err )
{
  const char *eq = strchr( arg, '=' );

  if ( eq == NULL || eq == arg ) {
    usage( err );
    return 2;
  }

  free( opts.base );
  opts.base = realpath( eq + 1, NULL );

  if ( opts.base == NULL ) {
    error( eq + 1, NULL, 0, strerror( errno ) );
    return 2;
  }

  opts.base_id = arg;
  opts.base_id_length = (size_t) ( eq - arg );

  /* The real path of the root directory is the only one with a final slash */
  opts.base_length = strcmp( opts.base, "/" ) == 0 ? 0 : strlen( opts.base );
  return 0;
}

/*
 * Sets the path relative to the base directory of the file, or NULL, if the
 * real path of the file is not below the base directory.  Returns the real
 * path to free.
 */
static char *set_relative( const char *file )
{
  char *real = NULL;

  opts.relative = NULL;

  if ( opts.base != NULL ) {
    real = realpath( file, NULL );

    if (
      real != NULL && strncmp( real, opts.base, opts.base_length ) == 0 &&
      real[ opts.base_length ] == '/'
    ) {
      opts.relative = real + opts.base_length + 1;
    }
  }

  return real;
}

static int run( int argc, char **argv, FILE *out, FILE *err )
{
  bool         print_statistics = false;
  unsigned int notes = NOTE_ALL;
  unsigned int part_notes = NOTE_ALL;
  int          opt;
  int          i;

  memset( &opts, 0, sizeof( opts ) );
  memset( &stats, 0, sizeof( stats ) );
  opts.out = out;
  opts.err = err;
  opterr = 0;
  optind = 0;

  while ( ( opt = getopt( argc, argv, "b:f:hip:qst:v" ) ) != -1 ) {
    switch ( opt ) {
      case 'b':
        if ( set_base( optarg, err ) != 0 ) {
          return 2;
        }
        break;
      case 'f':
        if ( strcmp( optarg, "sarif" ) == 0 ) {
          opts.sarif = true;
        } else if ( strcmp( optarg, "text" ) == 0 ) {
          opts.sarif = false;
        } else {
          usage( err );
          return 2;
        }
        break;
      case 'h':
        usage( out );
        return 0;
      case 'i':
        opts.include_indirect = true;
        break;
      case 'p':
        part_notes = find_name(
          part_names,
          PART_NAME_COUNT,
          optarg,
          strlen( optarg )
        );

        if ( part_notes == 0 ) {
          usage( err );
          return 2;
        }
        break;
      case 'q':
        opts.quiet = true;
        break;
      case 's':
        print_statistics = true;
        break;
      case 't':
        if ( !parse_notes( optarg, &notes ) ) {
          usage( err );
          return 2;
        }
        break;
      case 'v':
        opts.verbose = true;
        break;
      default:
        usage( err );
        return 2;
    }
  }

  opts.enabled_notes = notes & part_notes;

  if ( optind >= argc || opts.enabled_notes == 0 ) {
    usage( err );
    return 2;
  }

  report_begin();

  for ( i = optind; i < argc; ++i ) {
    char *real = set_relative( argv[ i ] );

    check_file( argv[ i ] );
    free( real );
  }

  report_end();

  if ( print_statistics ) {
    fprintf(
      err,
      "instructions: %lu, definite: %lu, possible: %lu\n",
      stats.instruction_count,
      stats.definite_count,
      stats.possible_count
    );
  }

  if ( stats.had_error ) {
    return 2;
  }

  return stats.definite_count + stats.possible_count > 0 ? 1 : 0;
}

int nopinion_main( int argc, char **argv, FILE *out, FILE *err )
{
  int status = run( argc, argv, out, err );

  free( opts.base );
  opts.base = NULL;
  return status;
}
