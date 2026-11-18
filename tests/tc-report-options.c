/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqReportOptions
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

#include "nopinion.h"
#include "tx-support.h"

#include <rtems/test.h>

/**
 * @defgroup NopinionReqReportOptions spec:/nopinion/req/report-options
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqReportOptions_Pre_Quiet_Yes,
  NopinionReqReportOptions_Pre_Quiet_No,
  NopinionReqReportOptions_Pre_Quiet_NA
} NopinionReqReportOptions_Pre_Quiet;

typedef enum {
  NopinionReqReportOptions_Pre_Verbose_Yes,
  NopinionReqReportOptions_Pre_Verbose_No,
  NopinionReqReportOptions_Pre_Verbose_NA
} NopinionReqReportOptions_Pre_Verbose;

typedef enum {
  NopinionReqReportOptions_Pre_Match_Definite,
  NopinionReqReportOptions_Pre_Match_Possible,
  NopinionReqReportOptions_Pre_Match_NA
} NopinionReqReportOptions_Pre_Match;

typedef enum {
  NopinionReqReportOptions_Post_Report_Empty,
  NopinionReqReportOptions_Post_Report_Line,
  NopinionReqReportOptions_Post_Report_Path,
  NopinionReqReportOptions_Post_Report_NA
} NopinionReqReportOptions_Post_Report;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Quiet_NA : 1;
  uint8_t Pre_Verbose_NA : 1;
  uint8_t Pre_Match_NA : 1;
  uint8_t Post_Report : 2;
} NopinionReqReportOptions_Entry;

/**
 * @brief Test context for spec:/nopinion/req/report-options test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member is true, if the option -q is given.
   */
  bool quiet;

  /**
   * @brief This member is true, if the option -v is given.
   */
  bool verbose;

  /**
   * @brief This member contains the expected line of the finding.
   */
  const char *line;

  /**
   * @brief This member contains the expected lines of the instruction
   *   sequence.
   */
  const char *path;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

  struct {
    /**
     * @brief This member defines the pre-condition states for the next action.
     */
    size_t pcs[ 3 ];

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
    NopinionReqReportOptions_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqReportOptions_Context;

static NopinionReqReportOptions_Context NopinionReqReportOptions_Instance;

static const char *const NopinionReqReportOptions_PreDesc_Quiet[] =
  { "Yes", "No", "NA" };

static const char *const NopinionReqReportOptions_PreDesc_Verbose[] =
  { "Yes", "No", "NA" };

static const char *const NopinionReqReportOptions_PreDesc_Match[] =
  { "Definite", "Possible", "NA" };

static const char *const *const NopinionReqReportOptions_PreDesc[] = {
  NopinionReqReportOptions_PreDesc_Quiet,
  NopinionReqReportOptions_PreDesc_Verbose,
  NopinionReqReportOptions_PreDesc_Match,
  NULL
};

static void NopinionReqReportOptions_Pre_Quiet_Prepare(
  NopinionReqReportOptions_Context  *ctx,
  NopinionReqReportOptions_Pre_Quiet state
)
{
  switch ( state ) {
    case NopinionReqReportOptions_Pre_Quiet_Yes: {
      /*
       * While the option -q is given.
       */
      ctx->quiet = true;
      break;
    }

    case NopinionReqReportOptions_Pre_Quiet_No: {
      /*
       * While the option -q is not given.
       */
      ctx->quiet = false;
      break;
    }

    case NopinionReqReportOptions_Pre_Quiet_NA:
      break;
  }
}

static void NopinionReqReportOptions_Pre_Verbose_Prepare(
  NopinionReqReportOptions_Context    *ctx,
  NopinionReqReportOptions_Pre_Verbose state
)
{
  switch ( state ) {
    case NopinionReqReportOptions_Pre_Verbose_Yes: {
      /*
       * While the option -v is given.
       */
      ctx->verbose = true;
      break;
    }

    case NopinionReqReportOptions_Pre_Verbose_No: {
      /*
       * While the option -v is not given.
       */
      ctx->verbose = false;
      break;
    }

    case NopinionReqReportOptions_Pre_Verbose_NA:
      break;
  }
}

static void NopinionReqReportOptions_Pre_Match_Prepare(
  NopinionReqReportOptions_Context  *ctx,
  NopinionReqReportOptions_Pre_Match state
)
{
  switch ( state ) {
    case NopinionReqReportOptions_Pre_Match_Definite: {
      /*
       * While the code section holds one definite finding.
       */
      TxAppend( &ctx->image, TxSt() );
      TxAppend( &ctx->image, TxAdd() );
      TxAppend( &ctx->image, TxSt() );
      TxAppend( &ctx->image, TxLd() );
      ctx->line = "t.o: .text+0x0 <f+0x0>: TN-0009 back-to-back-store\n";
      ctx->path = "  00000000  c2220000\n"
                  "  00000004  82006001\n"
                  "  00000008  c2220000\n";
      break;
    }

    case NopinionReqReportOptions_Pre_Match_Possible: {
      /*
       * While the code section holds one possible finding.
       */
      TxAppend( &ctx->image, TxSt() );
      TxAppend( &ctx->image, TxAdd() );
      ctx->line = "t.o: .text+0x0 <f+0x0>: TN-0009 back-to-back-store "
                  "possible\n";
      ctx->path = "  00000000  c2220000\n"
                  "  00000004  82006001\n"
                  "            ?\n";
      break;
    }

    case NopinionReqReportOptions_Pre_Match_NA:
      break;
  }
}

static void NopinionReqReportOptions_Post_Report_Check(
  NopinionReqReportOptions_Context    *ctx,
  NopinionReqReportOptions_Post_Report state
)
{
  switch ( state ) {
    case NopinionReqReportOptions_Post_Report_Empty: {
      /*
       * The errata checker shall report nothing.
       */
      T_eq_str( ctx->report, "" );
      break;
    }

    case NopinionReqReportOptions_Post_Report_Line: {
      /*
       * The errata checker shall report the line of the finding.
       */
      T_eq_str( ctx->report, ctx->line );
      break;
    }

    case NopinionReqReportOptions_Post_Report_Path: {
      /*
       * The errata checker shall report the line of the finding followed by
       * one line for each instruction of the instruction sequence.
       */
      char expected[ 256 ];

      (void)
        snprintf( expected, sizeof( expected ), "%s%s", ctx->line, ctx->path );
      T_eq_str( ctx->report, expected );
      break;
    }

    case NopinionReqReportOptions_Post_Report_NA:
      break;
  }
}

static void NopinionReqReportOptions_Prepare(
  NopinionReqReportOptions_Context *ctx
)
{
  TxImageInit( &ctx->image );
}

static void NopinionReqReportOptions_Action(
  NopinionReqReportOptions_Context *ctx
)
{
  TxSetQuietVerbose( ctx->quiet, ctx->verbose );
  ctx->report = TxCheck( &ctx->image, NOTE_0009 );
  TxSetQuietVerbose( false, false );
}

/* clang-format off */

static const NopinionReqReportOptions_Entry
NopinionReqReportOptions_Entries[] = {
  { 0, 0, 0, 0, NopinionReqReportOptions_Post_Report_Empty },
  { 0, 0, 0, 0, NopinionReqReportOptions_Post_Report_Path },
  { 0, 0, 0, 0, NopinionReqReportOptions_Post_Report_Line }
};

static const uint8_t
NopinionReqReportOptions_Map[] = {
  0, 0, 0, 0, 1, 1, 2, 2
};

/* clang-format on */

static size_t NopinionReqReportOptions_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqReportOptions_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqReportOptions_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqReportOptions_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqReportOptions_Scope,
  .initial_context = &NopinionReqReportOptions_Instance
};

static inline NopinionReqReportOptions_Entry NopinionReqReportOptions_PopEntry(
  NopinionReqReportOptions_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqReportOptions_Entries
    [ NopinionReqReportOptions_Map[ index ] ];
}

static void NopinionReqReportOptions_TestVariant(
  NopinionReqReportOptions_Context *ctx
)
{
  NopinionReqReportOptions_Pre_Quiet_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqReportOptions_Pre_Verbose_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqReportOptions_Pre_Match_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqReportOptions_Action( ctx );
  NopinionReqReportOptions_Post_Report_Check(
    ctx,
    ctx->Map.entry.Post_Report
  );
}

/**
 * @fn void T_case_body_NopinionReqReportOptions( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqReportOptions,
  &NopinionReqReportOptions_Fixture
)
{
  NopinionReqReportOptions_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqReportOptions_Pre_Quiet_Yes;
    ctx->Map.pcs[ 0 ] < NopinionReqReportOptions_Pre_Quiet_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqReportOptions_Pre_Verbose_Yes;
      ctx->Map.pcs[ 1 ] < NopinionReqReportOptions_Pre_Verbose_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqReportOptions_Pre_Match_Definite;
        ctx->Map.pcs[ 2 ] < NopinionReqReportOptions_Pre_Match_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        ctx->Map.entry = NopinionReqReportOptions_PopEntry( ctx );
        NopinionReqReportOptions_Prepare( ctx );
        NopinionReqReportOptions_TestVariant( ctx );
      }
    }
  }
}

/** @} */
