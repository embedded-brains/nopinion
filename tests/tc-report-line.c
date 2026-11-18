/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqReportLine
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
 * @defgroup NopinionReqReportLine spec:/nopinion/req/report-line
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqReportLine_Pre_File_Relocatable,
  NopinionReqReportLine_Pre_File_Executable,
  NopinionReqReportLine_Pre_File_NA
} NopinionReqReportLine_Pre_File;

typedef enum {
  NopinionReqReportLine_Pre_Symbols_None,
  NopinionReqReportLine_Pre_Symbols_AtStart,
  NopinionReqReportLine_Pre_Symbols_Around,
  NopinionReqReportLine_Pre_Symbols_After,
  NopinionReqReportLine_Pre_Symbols_Equal,
  NopinionReqReportLine_Pre_Symbols_NA
} NopinionReqReportLine_Pre_Symbols;

typedef enum {
  NopinionReqReportLine_Pre_Match_Definite,
  NopinionReqReportLine_Pre_Match_Possible,
  NopinionReqReportLine_Pre_Match_NA
} NopinionReqReportLine_Pre_Match;

typedef enum {
  NopinionReqReportLine_Post_Line_Expected,
  NopinionReqReportLine_Post_Line_NA
} NopinionReqReportLine_Post_Line;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_File_NA : 1;
  uint8_t Pre_Symbols_NA : 1;
  uint8_t Pre_Match_NA : 1;
  uint8_t Post_Line : 1;
} NopinionReqReportLine_Entry;

/**
 * @brief Test context for spec:/nopinion/req/report-line test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the expected address part of the line.
   */
  const char *address;

  /**
   * @brief This member contains the expected symbol part of the line.
   */
  const char *symbol;

  /**
   * @brief This member is true, if the finding is a possible finding.
   */
  bool possible;

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
    NopinionReqReportLine_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqReportLine_Context;

static NopinionReqReportLine_Context NopinionReqReportLine_Instance;

static const char *const NopinionReqReportLine_PreDesc_File[] =
  { "Relocatable", "Executable", "NA" };

static const char *const NopinionReqReportLine_PreDesc_Symbols[] =
  { "None", "AtStart", "Around", "After", "Equal", "NA" };

static const char *const NopinionReqReportLine_PreDesc_Match[] =
  { "Definite", "Possible", "NA" };

static const char *const *const NopinionReqReportLine_PreDesc[] = {
  NopinionReqReportLine_PreDesc_File,
  NopinionReqReportLine_PreDesc_Symbols,
  NopinionReqReportLine_PreDesc_Match,
  NULL
};

static void NopinionReqReportLine_Pre_File_Prepare(
  NopinionReqReportLine_Context *ctx,
  NopinionReqReportLine_Pre_File state
)
{
  switch ( state ) {
    case NopinionReqReportLine_Pre_File_Relocatable: {
      /*
       * While the ELF file is relocatable.
       */
      ctx->address = "";
      break;
    }

    case NopinionReqReportLine_Pre_File_Executable: {
      /*
       * While the ELF file is an executable.
       */
      ctx->image.executable = true;
      ctx->image.address = 0x40001000;
      ctx->address = " [0x40001004]";
      break;
    }

    case NopinionReqReportLine_Pre_File_NA:
      break;
  }
}

static void NopinionReqReportLine_Pre_Symbols_Prepare(
  NopinionReqReportLine_Context    *ctx,
  NopinionReqReportLine_Pre_Symbols state
)
{
  switch ( state ) {
    case NopinionReqReportLine_Pre_Symbols_None: {
      /*
       * While no function and no symbol without type of the code section
       * exists.
       */
      TxAddSymbol( &ctx->image, "g", 0, 0x11, TX_SECTION_TEXT );
      ctx->symbol = "";
      break;
    }

    case NopinionReqReportLine_Pre_Symbols_AtStart: {
      /*
       * While one function of the code section starts at offset 0.
       */
      ctx->symbol = " <f+0x4>";
      break;
    }

    case NopinionReqReportLine_Pre_Symbols_Around: {
      /*
       * While one function starts before the instruction and one after it.
       */
      TxAddSymbol( &ctx->image, "g", 8, 0x12, TX_SECTION_TEXT );
      TxAddSymbol( &ctx->image, "f", 0, 0x12, TX_SECTION_TEXT );
      ctx->symbol = " <f+0x4>";
      break;
    }

    case NopinionReqReportLine_Pre_Symbols_After: {
      /*
       * While every function starts after the instruction.
       */
      TxAddSymbol( &ctx->image, "g", 8, 0x12, TX_SECTION_TEXT );
      TxAddSymbol( &ctx->image, "h", 12, 0x12, TX_SECTION_TEXT );
      ctx->symbol = "";
      break;
    }

    case NopinionReqReportLine_Pre_Symbols_Equal: {
      /*
       * While three functions or symbols without type start at offset 0.
       */
      TxAddSymbol( &ctx->image, "b", 0, 0x12, TX_SECTION_TEXT );
      TxAddSymbol( &ctx->image, "c", 0, 0x10, TX_SECTION_TEXT );
      TxAddSymbol( &ctx->image, "a", 0, 0x12, TX_SECTION_TEXT );
      ctx->symbol = " <c+0x4>";
      break;
    }

    case NopinionReqReportLine_Pre_Symbols_NA:
      break;
  }
}

static void NopinionReqReportLine_Pre_Match_Prepare(
  NopinionReqReportLine_Context  *ctx,
  NopinionReqReportLine_Pre_Match state
)
{
  switch ( state ) {
    case NopinionReqReportLine_Pre_Match_Definite: {
      /*
       * While the finding is a definite finding.
       */
      ctx->possible = false;
      break;
    }

    case NopinionReqReportLine_Pre_Match_Possible: {
      /*
       * While the finding is a possible finding.
       */
      ctx->possible = true;
      break;
    }

    case NopinionReqReportLine_Pre_Match_NA:
      break;
  }
}

static void NopinionReqReportLine_Post_Line_Check(
  NopinionReqReportLine_Context  *ctx,
  NopinionReqReportLine_Post_Line state
)
{
  switch ( state ) {
    case NopinionReqReportLine_Post_Line_Expected: {
      /*
       * The errata checker shall report the line "<file>:
       * <section>+0x<offset>" followed by " \[0x<address>\]" for an
       * executable, by " \<<symbol>+0x<delta>>" for a symbol at or before the
       * instruction, by ": <erratum> <kind>" and by " possible" for a possible
       * finding.
       */
      char line[ 128 ];
      char expected[ 128 ];

      TxLineAt( ctx->report, 4, "TN-0009", line, sizeof( line ) );
      (void) snprintf(
        expected,
        sizeof( expected ),
        "t.o: .text+0x4%s%s: TN-0009 back-to-back-store%s",
        ctx->address,
        ctx->symbol,
        ctx->possible ? " possible" : ""
      );
      T_eq_str( line, expected );
      break;
    }

    case NopinionReqReportLine_Post_Line_NA:
      break;
  }
}

static void NopinionReqReportLine_Prepare( NopinionReqReportLine_Context *ctx )
{
  TxImageInit( &ctx->image );
}

static void NopinionReqReportLine_Action( NopinionReqReportLine_Context *ctx )
{
  TxAppend( &ctx->image, TxAdd() );
  TxAppend( &ctx->image, TxSt() );
  TxAppend( &ctx->image, TxAdd() );

  if ( !ctx->possible ) {
    TxAppend( &ctx->image, TxSt() );
    TxAppend( &ctx->image, TxNop() );
  }

  ctx->report = TxCheck( &ctx->image, NOTE_0009 );
}

/* clang-format off */

static const NopinionReqReportLine_Entry
NopinionReqReportLine_Entries[] = {
  { 0, 0, 0, 0, NopinionReqReportLine_Post_Line_Expected }
};

static const uint8_t
NopinionReqReportLine_Map[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqReportLine_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqReportLine_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqReportLine_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqReportLine_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqReportLine_Scope,
  .initial_context = &NopinionReqReportLine_Instance
};

static inline NopinionReqReportLine_Entry NopinionReqReportLine_PopEntry(
  NopinionReqReportLine_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqReportLine_Entries[ NopinionReqReportLine_Map[ index ] ];
}

static void NopinionReqReportLine_TestVariant(
  NopinionReqReportLine_Context *ctx
)
{
  NopinionReqReportLine_Pre_File_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqReportLine_Pre_Symbols_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqReportLine_Pre_Match_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqReportLine_Action( ctx );
  NopinionReqReportLine_Post_Line_Check( ctx, ctx->Map.entry.Post_Line );
}

/**
 * @fn void T_case_body_NopinionReqReportLine( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqReportLine, &NopinionReqReportLine_Fixture )
{
  NopinionReqReportLine_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqReportLine_Pre_File_Relocatable;
    ctx->Map.pcs[ 0 ] < NopinionReqReportLine_Pre_File_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqReportLine_Pre_Symbols_None;
      ctx->Map.pcs[ 1 ] < NopinionReqReportLine_Pre_Symbols_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqReportLine_Pre_Match_Definite;
        ctx->Map.pcs[ 2 ] < NopinionReqReportLine_Pre_Match_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        ctx->Map.entry = NopinionReqReportLine_PopEntry( ctx );
        NopinionReqReportLine_Prepare( ctx );
        NopinionReqReportLine_TestVariant( ctx );
      }
    }
  }
}

/** @} */
