/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCliOptions
 */

/*
 * Copyright (C) 2026 embedded brains GmbH & Co. KG
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This file was automatically generated.  Do not edit it.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nopinion.h"
#include "tx-support.h"

#include <rtems/test.h>

/**
 * @defgroup NopinionReqCliOptions spec:/nopinion/req/cli-options
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCliOptions_Pre_Option_None,
  NopinionReqCliOptions_Pre_Option_BaseNoName,
  NopinionReqCliOptions_Pre_Option_BaseNoDirectory,
  NopinionReqCliOptions_Pre_Option_BaseMissing,
  NopinionReqCliOptions_Pre_Option_FormatText,
  NopinionReqCliOptions_Pre_Option_FormatUnknown,
  NopinionReqCliOptions_Pre_Option_Help,
  NopinionReqCliOptions_Pre_Option_Indirect,
  NopinionReqCliOptions_Pre_Option_Quiet,
  NopinionReqCliOptions_Pre_Option_Statistics,
  NopinionReqCliOptions_Pre_Option_Verbose,
  NopinionReqCliOptions_Pre_Option_Note0009,
  NopinionReqCliOptions_Pre_Option_Note0011,
  NopinionReqCliOptions_Pre_Option_Note0012,
  NopinionReqCliOptions_Pre_Option_Note0013,
  NopinionReqCliOptions_Pre_Option_NoteList,
  NopinionReqCliOptions_Pre_Option_NoteUnknown,
  NopinionReqCliOptions_Pre_Option_NoteLength,
  NopinionReqCliOptions_Pre_Option_NoteEmpty,
  NopinionReqCliOptions_Pre_Option_Unknown,
  NopinionReqCliOptions_Pre_Option_NoArgument,
  NopinionReqCliOptions_Pre_Option_NA
} NopinionReqCliOptions_Pre_Option;

typedef enum {
  NopinionReqCliOptions_Pre_Files_NoOperand,
  NopinionReqCliOptions_Pre_Files_Clean,
  NopinionReqCliOptions_Pre_Files_Finding,
  NopinionReqCliOptions_Pre_Files_Possible,
  NopinionReqCliOptions_Pre_Files_Missing,
  NopinionReqCliOptions_Pre_Files_Both,
  NopinionReqCliOptions_Pre_Files_NA
} NopinionReqCliOptions_Pre_Files;

typedef enum {
  NopinionReqCliOptions_Post_Status_Success,
  NopinionReqCliOptions_Post_Status_Finding,
  NopinionReqCliOptions_Post_Status_Error,
  NopinionReqCliOptions_Post_Status_NA
} NopinionReqCliOptions_Post_Status;

typedef enum {
  NopinionReqCliOptions_Post_Output_Usage,
  NopinionReqCliOptions_Post_Output_Empty,
  NopinionReqCliOptions_Post_Output_Report,
  NopinionReqCliOptions_Post_Output_ReportIndirect,
  NopinionReqCliOptions_Post_Output_Possible,
  NopinionReqCliOptions_Post_Output_PossibleVerbose,
  NopinionReqCliOptions_Post_Output_ReportVerbose,
  NopinionReqCliOptions_Post_Output_NA
} NopinionReqCliOptions_Post_Output;

typedef enum {
  NopinionReqCliOptions_Post_Errors_Empty,
  NopinionReqCliOptions_Post_Errors_Usage,
  NopinionReqCliOptions_Post_Errors_BaseMessage,
  NopinionReqCliOptions_Post_Errors_Message,
  NopinionReqCliOptions_Post_Errors_Statistics,
  NopinionReqCliOptions_Post_Errors_MessageStatistics,
  NopinionReqCliOptions_Post_Errors_NA
} NopinionReqCliOptions_Post_Errors;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Option_NA : 1;
  uint16_t Pre_Files_NA : 1;
  uint16_t Post_Status : 2;
  uint16_t Post_Output : 3;
  uint16_t Post_Errors : 3;
} NopinionReqCliOptions_Entry;

/**
 * @brief Test context for spec:/nopinion/req/cli-options test case.
 */
typedef struct {
  /**
   * @brief This member contains the options.
   */
  const char *const *options;

  /**
   * @brief This member contains the file operands.
   */
  const char *files[ 3 ];

  /**
   * @brief This member contains the temporary directory.
   */
  char dir[ 32 ];

  /**
   * @brief This member contains the path of the file without a finding.
   */
  char clean[ 64 ];

  /**
   * @brief This member contains the path of the file with a finding.
   */
  char finding[ 64 ];

  /**
   * @brief This member contains the path of the file with only a possible
   *   finding.
   */
  char possible[ 64 ];

  /**
   * @brief This member contains the report line of the possible finding of
   *   that file.
   */
  char line_possible[ 128 ];

  /**
   * @brief This member contains the path of the file which does not exist.
   */
  char missing[ 64 ];

  /**
   * @brief This member contains the report line of the definite finding.
   */
  char line_0[ 128 ];

  /**
   * @brief This member contains the report line of the possible finding.
   */
  char line_16[ 128 ];

  /**
   * @brief This member contains the error message of the missing file.
   */
  char message[ 128 ];

  /**
   * @brief This member contains the expected statistics.
   */
  char statistics[ 128 ];

  /**
   * @brief This member contains the exit status.
   */
  int status;

  /**
   * @brief This member references the standard output.
   */
  const char *out;

  /**
   * @brief This member references the standard error.
   */
  const char *err;

  struct {
    /**
     * @brief This member defines the pre-condition states for the next action.
     */
    size_t pcs[ 2 ];

    /**
     * @brief If this member is true, then the test action loop is executed.
     */
    bool in_action_loop;

    /**
     * @brief This member contains the next transition map index.
     */
    size_t index;

    /**
     * @brief This member contains the current transition map entry.
     */
    NopinionReqCliOptions_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCliOptions_Context;

static NopinionReqCliOptions_Context NopinionReqCliOptions_Instance;

static const char *const NopinionReqCliOptions_PreDesc_Option[] = {
  "None",
  "BaseNoName",
  "BaseNoDirectory",
  "BaseMissing",
  "FormatText",
  "FormatUnknown",
  "Help",
  "Indirect",
  "Quiet",
  "Statistics",
  "Verbose",
  "Note0009",
  "Note0011",
  "Note0012",
  "Note0013",
  "NoteList",
  "NoteUnknown",
  "NoteLength",
  "NoteEmpty",
  "Unknown",
  "NoArgument",
  "NA"
};

static const char *const NopinionReqCliOptions_PreDesc_Files[] =
  { "NoOperand", "Clean", "Finding", "Possible", "Missing", "Both", "NA" };

static const char *const *const NopinionReqCliOptions_PreDesc[] = {
  NopinionReqCliOptions_PreDesc_Option,
  NopinionReqCliOptions_PreDesc_Files,
  NULL
};

static void NopinionReqCliOptions_Pre_Option_Prepare(
  NopinionReqCliOptions_Context   *ctx,
  NopinionReqCliOptions_Pre_Option state
)
{
  switch ( state ) {
    case NopinionReqCliOptions_Pre_Option_None: {
      /*
       * While no option is given.
       */
      static const char *const options[] = { NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_BaseNoName: {
      /*
       * While the option -b names no URI base id.
       */
      static const char *const options[] = { "-b", "=.", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_BaseNoDirectory: {
      /*
       * While the argument of the option -b holds no equals sign.
       */
      static const char *const options[] = { "-b", "PKG", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_BaseMissing: {
      /*
       * While the option -b names a directory which does not exist.
       */
      static const char *const options[] =
        { "-b", "PKG=tx-no-such-dir", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_FormatText: {
      /*
       * While the option -f text is given.
       */
      static const char *const options[] = { "-f", "text", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_FormatUnknown: {
      /*
       * While the option -f names an unknown format.
       */
      static const char *const options[] = { "-f", "xml", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Help: {
      /*
       * While the option -h is given.
       */
      static const char *const options[] = { "-h", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Indirect: {
      /*
       * While the option -i is given.
       */
      static const char *const options[] = { "-i", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Quiet: {
      /*
       * While the option -q is given.
       */
      static const char *const options[] = { "-q", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Statistics: {
      /*
       * While the option -s is given.
       */
      static const char *const options[] = { "-s", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Verbose: {
      /*
       * While the option -v is given.
       */
      static const char *const options[] = { "-v", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Note0009: {
      /*
       * While the option -t selects GRLIB-TN-0009.
       */
      static const char *const options[] = { "-t", "0009", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Note0011: {
      /*
       * While the option -t selects GRLIB-TN-0011.
       */
      static const char *const options[] = { "-t", "0011", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Note0012: {
      /*
       * While the option -t selects GRLIB-TN-0012.
       */
      static const char *const options[] = { "-t", "0012", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Note0013: {
      /*
       * While the option -t selects GRLIB-TN-0013.
       */
      static const char *const options[] = { "-t", "0013", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_NoteList: {
      /*
       * While the option -t selects GRLIB-TN-0011 and GRLIB-TN-0009 with empty
       * list elements.
       */
      static const char *const options[] = { "-t", ",0011,0009,", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_NoteUnknown: {
      /*
       * While the option -t names an unknown technical note.
       */
      static const char *const options[] = { "-t", "0010", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_NoteLength: {
      /*
       * While the option -t names a technical note with more than four digits.
       */
      static const char *const options[] = { "-t", "00099", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_NoteEmpty: {
      /*
       * While the option -t names no technical note.
       */
      static const char *const options[] = { "-t", ",", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_Unknown: {
      /*
       * While an unknown option is given.
       */
      static const char *const options[] = { "-x", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_NoArgument: {
      /*
       * While the option -t is given without an argument.
       */
      static const char *const options[] = { "-t", NULL };

      ctx->options = options;
      break;
    }

    case NopinionReqCliOptions_Pre_Option_NA:
      break;
  }
}

static void NopinionReqCliOptions_Pre_Files_Prepare(
  NopinionReqCliOptions_Context  *ctx,
  NopinionReqCliOptions_Pre_Files state
)
{
  switch ( state ) {
    case NopinionReqCliOptions_Pre_Files_NoOperand: {
      /*
       * While no file operand is given.
       */
      ctx->files[ 0 ] = NULL;
      break;
    }

    case NopinionReqCliOptions_Pre_Files_Clean: {
      /*
       * While the file operand names an ELF file without a finding.
       */
      ctx->files[ 0 ] = ctx->clean;
      ctx->files[ 1 ] = NULL;
      break;
    }

    case NopinionReqCliOptions_Pre_Files_Finding: {
      /*
       * While the file operand names an ELF file with a finding.
       */
      ctx->files[ 0 ] = ctx->finding;
      ctx->files[ 1 ] = NULL;
      break;
    }

    case NopinionReqCliOptions_Pre_Files_Possible: {
      /*
       * While the file operand names an ELF file with only a possible finding.
       */
      ctx->files[ 0 ] = ctx->possible;
      ctx->files[ 1 ] = NULL;
      break;
    }

    case NopinionReqCliOptions_Pre_Files_Missing: {
      /*
       * While the file operand names a file which does not exist.
       */
      ctx->files[ 0 ] = ctx->missing;
      ctx->files[ 1 ] = NULL;
      break;
    }

    case NopinionReqCliOptions_Pre_Files_Both: {
      /*
       * While the file operands name an ELF file with a finding and a file
       * which does not exist.
       */
      ctx->files[ 0 ] = ctx->finding;
      ctx->files[ 1 ] = ctx->missing;
      ctx->files[ 2 ] = NULL;
      break;
    }

    case NopinionReqCliOptions_Pre_Files_NA:
      break;
  }
}

static void NopinionReqCliOptions_Post_Status_Check(
  NopinionReqCliOptions_Context    *ctx,
  NopinionReqCliOptions_Post_Status state
)
{
  switch ( state ) {
    case NopinionReqCliOptions_Post_Status_Success: {
      /*
       * The exit status shall be 0.
       */
      T_eq_int( ctx->status, 0 );
      break;
    }

    case NopinionReqCliOptions_Post_Status_Finding: {
      /*
       * The exit status shall be 1.
       */
      T_eq_int( ctx->status, 1 );
      break;
    }

    case NopinionReqCliOptions_Post_Status_Error: {
      /*
       * The exit status shall be 2.
       */
      T_eq_int( ctx->status, 2 );
      break;
    }

    case NopinionReqCliOptions_Post_Status_NA:
      break;
  }
}

static void NopinionReqCliOptions_Post_Output_Check(
  NopinionReqCliOptions_Context    *ctx,
  NopinionReqCliOptions_Post_Output state
)
{
  switch ( state ) {
    case NopinionReqCliOptions_Post_Output_Usage: {
      /*
       * The errata checker shall write the usage text to the standard output.
       */
      T_eq_int( strncmp( ctx->out, "usage: nopinion ", 16 ), 0 );
      break;
    }

    case NopinionReqCliOptions_Post_Output_Empty: {
      /*
       * The errata checker shall write nothing to the standard output.
       */
      T_eq_str( ctx->out, "" );
      break;
    }

    case NopinionReqCliOptions_Post_Output_Report: {
      /*
       * The errata checker shall write the report line of the definite finding
       * to the standard output.
       */
      T_eq_str( ctx->out, ctx->line_0 );
      break;
    }

    case NopinionReqCliOptions_Post_Output_ReportIndirect: {
      /*
       * The errata checker shall write the report lines of the definite
       * finding and of the possible finding to the standard output.
       */
      char expected[ 512 ];

      (void) snprintf(
        expected,
        sizeof( expected ),
        "%s%s",
        ctx->line_0,
        ctx->line_16
      );
      T_eq_str( ctx->out, expected );
      break;
    }

    case NopinionReqCliOptions_Post_Output_Possible: {
      /*
       * The errata checker shall write the report line of the possible finding
       * to the standard output.
       */
      T_eq_str( ctx->out, ctx->line_possible );
      break;
    }

    case NopinionReqCliOptions_Post_Output_PossibleVerbose: {
      /*
       * The errata checker shall write the report line of the possible finding
       * and its instruction sequence to the standard output.
       */
      char expected[ 512 ];

      (void) snprintf(
        expected,
        sizeof( expected ),
        "%s  00000000  c2220000\n  00000004  82006001\n            ?\n",
        ctx->line_possible
      );
      T_eq_str( ctx->out, expected );
      break;
    }

    case NopinionReqCliOptions_Post_Output_ReportVerbose: {
      /*
       * The errata checker shall write the report line of the definite finding
       * and its instruction sequence to the standard output.
       */
      char expected[ 512 ];

      (void) snprintf(
        expected,
        sizeof( expected ),
        "%s  00000000  c2220000\n  00000004  82006001\n  00000008  c2220000\n",
        ctx->line_0
      );
      T_eq_str( ctx->out, expected );
      break;
    }

    case NopinionReqCliOptions_Post_Output_NA:
      break;
  }
}

static void NopinionReqCliOptions_Post_Errors_Check(
  NopinionReqCliOptions_Context    *ctx,
  NopinionReqCliOptions_Post_Errors state
)
{
  switch ( state ) {
    case NopinionReqCliOptions_Post_Errors_Empty: {
      /*
       * The errata checker shall write nothing to the standard error.
       */
      T_eq_str( ctx->err, "" );
      break;
    }

    case NopinionReqCliOptions_Post_Errors_Usage: {
      /*
       * The errata checker shall write the usage text to the standard error.
       */
      T_eq_int( strncmp( ctx->err, "usage: nopinion ", 16 ), 0 );
      break;
    }

    case NopinionReqCliOptions_Post_Errors_BaseMessage: {
      /*
       * The errata checker shall write the error message of the missing
       * directory of the option -b to the standard error.
       */
      T_eq_str(
        ctx->err,
        "nopinion: tx-no-such-dir: No such file or directory\n"
      );
      break;
    }

    case NopinionReqCliOptions_Post_Errors_Message: {
      /*
       * The errata checker shall write the error message of the missing file
       * to the standard error.
       */
      T_eq_str( ctx->err, ctx->message );
      break;
    }

    case NopinionReqCliOptions_Post_Errors_Statistics: {
      /*
       * The errata checker shall write the statistics to the standard error.
       */
      T_eq_str( ctx->err, ctx->statistics );
      break;
    }

    case NopinionReqCliOptions_Post_Errors_MessageStatistics: {
      /*
       * The errata checker shall write the error message of the missing file
       * and the statistics to the standard error.
       */
      char expected[ 512 ];

      (void) snprintf(
        expected,
        sizeof( expected ),
        "%s%s",
        ctx->message,
        ctx->statistics
      );
      T_eq_str( ctx->err, expected );
      break;
    }

    case NopinionReqCliOptions_Post_Errors_NA:
      break;
  }
}

static void NopinionReqCliOptions_Setup( NopinionReqCliOptions_Context *ctx )
{
  TxImage image;
  uint8_t buf[ 4096 ];
  size_t  size;
  FILE   *f;

  strcpy( ctx->dir, "tx-cli-XXXXXX" );
  T_assert_not_null( mkdtemp( ctx->dir ) );
  (void) snprintf( ctx->clean, sizeof( ctx->clean ), "%s/clean.o", ctx->dir );
  (void)
    snprintf( ctx->finding, sizeof( ctx->finding ), "%s/finding.o", ctx->dir );
  (void)
    snprintf( ctx->missing, sizeof( ctx->missing ), "%s/missing.o", ctx->dir );
  (void) snprintf(
    ctx->line_0,
    sizeof( ctx->line_0 ),
    "%s: .text+0x0 <f+0x0>: TN-0009 back-to-back-store\n",
    ctx->finding
  );
  (void) snprintf(
    ctx->line_16,
    sizeof( ctx->line_16 ),
    "%s: .text+0x10 <f+0x10>: TN-0009 back-to-back-store possible\n",
    ctx->finding
  );
  (void) snprintf(
    ctx->message,
    sizeof( ctx->message ),
    "nopinion: %s: No such file or directory\n",
    ctx->missing
  );

  TxImageInit( &image );
  TxAppend( &image, TxNop() );
  size = TxBuildElf( &image, buf, sizeof( buf ) );
  f = fopen( ctx->clean, "wb" );
  T_assert_not_null( f );
  T_assert_eq_sz( fwrite( buf, 1, size, f ), size );
  T_assert_eq_int( fclose( f ), 0 );

  (void) snprintf(
    ctx->possible,
    sizeof( ctx->possible ),
    "%s/possible.o",
    ctx->dir
  );
  (void) snprintf(
    ctx->line_possible,
    sizeof( ctx->line_possible ),
    "%s: .text+0x0 <f+0x0>: TN-0009 back-to-back-store possible\n",
    ctx->possible
  );
  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxAdd() );
  size = TxBuildElf( &image, buf, sizeof( buf ) );
  f = fopen( ctx->possible, "wb" );
  T_assert_not_null( f );
  T_assert_eq_sz( fwrite( buf, 1, size, f ), size );
  T_assert_eq_int( fclose( f ), 0 );

  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxAdd() );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxLd() );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxTa() );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxLd() );
  size = TxBuildElf( &image, buf, sizeof( buf ) );
  f = fopen( ctx->finding, "wb" );
  T_assert_not_null( f );
  T_assert_eq_sz( fwrite( buf, 1, size, f ), size );
  T_assert_eq_int( fclose( f ), 0 );
}

static void NopinionReqCliOptions_Setup_Wrap( void *arg )
{
  NopinionReqCliOptions_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqCliOptions_Setup( ctx );
}

static void NopinionReqCliOptions_Teardown(
  NopinionReqCliOptions_Context *ctx
)
{
  T_eq_int( unlink( ctx->clean ), 0 );
  T_eq_int( unlink( ctx->finding ), 0 );
  T_eq_int( unlink( ctx->possible ), 0 );
  T_eq_int( rmdir( ctx->dir ), 0 );
}

static void NopinionReqCliOptions_Teardown_Wrap( void *arg )
{
  NopinionReqCliOptions_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqCliOptions_Teardown( ctx );
}

static void NopinionReqCliOptions_Action( NopinionReqCliOptions_Context *ctx )
{
  char       *argv[ 8 ];
  int         argc = 0;
  size_t      i;
  const char *statistics;

  argv[ argc++ ] = "nopinion";

  for ( i = 0; ctx->options[ i ] != NULL; ++i ) {
    argv[ argc++ ] = (char *) ctx->options[ i ];
  }

  for ( i = 0; ctx->files[ i ] != NULL; ++i ) {
    argv[ argc++ ] = (char *) ctx->files[ i ];
  }

  argv[ argc ] = NULL;
  if ( ctx->files[ 0 ] == ctx->clean ) {
    statistics = "instructions: 1, definite: 0, possible: 0\n";
  } else if ( ctx->files[ 0 ] == ctx->possible ) {
    statistics = "instructions: 2, definite: 0, possible: 1\n";
  } else if ( ctx->files[ 0 ] == ctx->missing ) {
    statistics = "instructions: 0, definite: 0, possible: 0\n";
  } else {
    statistics = "instructions: 8, definite: 1, possible: 0\n";
  }

  (void)
    snprintf( ctx->statistics, sizeof( ctx->statistics ), "%s", statistics );
  ctx->out = TxMain( argc, argv, &ctx->status );
  ctx->err = TxErrors();
}

/* clang-format off */

static const NopinionReqCliOptions_Entry
NopinionReqCliOptions_Entries[] = {
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_Usage },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Success,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_Message },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_BaseMessage },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Success,
    NopinionReqCliOptions_Post_Output_Usage,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_Possible,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_Report,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_Report,
    NopinionReqCliOptions_Post_Errors_Message },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_ReportIndirect,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_ReportIndirect,
    NopinionReqCliOptions_Post_Errors_Message },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Success,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_Statistics },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_Report,
    NopinionReqCliOptions_Post_Errors_Statistics },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_Possible,
    NopinionReqCliOptions_Post_Errors_Statistics },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_Empty,
    NopinionReqCliOptions_Post_Errors_MessageStatistics },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_Report,
    NopinionReqCliOptions_Post_Errors_MessageStatistics },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_ReportVerbose,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Finding,
    NopinionReqCliOptions_Post_Output_PossibleVerbose,
    NopinionReqCliOptions_Post_Errors_Empty },
  { 0, 0, 0, NopinionReqCliOptions_Post_Status_Error,
    NopinionReqCliOptions_Post_Output_ReportVerbose,
    NopinionReqCliOptions_Post_Errors_Message }
};

static const uint8_t
NopinionReqCliOptions_Map[] = {
  0, 1, 6, 5, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 1,
  6, 5, 2, 7, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 1, 9, 5, 2, 10, 0, 1, 8,
  8, 2, 2, 0, 11, 12, 13, 14, 15, 0, 1, 16, 17, 2, 18, 0, 1, 6, 5, 2, 7, 0, 1,
  1, 1, 2, 2, 0, 1, 1, 1, 2, 2, 0, 1, 1, 1, 2, 2, 0, 1, 6, 5, 2, 7, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqCliOptions_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCliOptions_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqCliOptions_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqCliOptions_Fixture = {
  .setup = NopinionReqCliOptions_Setup_Wrap,
  .stop = NULL,
  .teardown = NopinionReqCliOptions_Teardown_Wrap,
  .scope = NopinionReqCliOptions_Scope,
  .initial_context = &NopinionReqCliOptions_Instance
};

static inline NopinionReqCliOptions_Entry NopinionReqCliOptions_PopEntry(
  NopinionReqCliOptions_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCliOptions_Entries[ NopinionReqCliOptions_Map[ index ] ];
}

static void NopinionReqCliOptions_TestVariant(
  NopinionReqCliOptions_Context *ctx
)
{
  NopinionReqCliOptions_Pre_Option_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCliOptions_Pre_Files_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCliOptions_Action( ctx );
  NopinionReqCliOptions_Post_Status_Check( ctx, ctx->Map.entry.Post_Status );
  NopinionReqCliOptions_Post_Output_Check( ctx, ctx->Map.entry.Post_Output );
  NopinionReqCliOptions_Post_Errors_Check( ctx, ctx->Map.entry.Post_Errors );
}

/**
 * @fn void T_case_body_NopinionReqCliOptions( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqCliOptions, &NopinionReqCliOptions_Fixture )
{
  NopinionReqCliOptions_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCliOptions_Pre_Option_None;
    ctx->Map.pcs[ 0 ] < NopinionReqCliOptions_Pre_Option_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCliOptions_Pre_Files_NoOperand;
      ctx->Map.pcs[ 1 ] < NopinionReqCliOptions_Pre_Files_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      ctx->Map.entry = NopinionReqCliOptions_PopEntry( ctx );
      NopinionReqCliOptions_TestVariant( ctx );
    }
  }
}

/** @} */
