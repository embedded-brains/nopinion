/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqInputSymbols
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

#include "nopinion.h"
#include "tx-support.h"

#include <rtems/test.h>

/**
 * @defgroup NopinionReqInputSymbols spec:/nopinion/req/input-symbols
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqInputSymbols_Pre_Symbol_Func,
  NopinionReqInputSymbols_Pre_Symbol_NoType,
  NopinionReqInputSymbols_Pre_Symbol_Object,
  NopinionReqInputSymbols_Pre_Symbol_OtherSection,
  NopinionReqInputSymbols_Pre_Symbol_NoName,
  NopinionReqInputSymbols_Pre_Symbol_NameOutside,
  NopinionReqInputSymbols_Pre_Symbol_NA
} NopinionReqInputSymbols_Pre_Symbol;

typedef enum {
  NopinionReqInputSymbols_Pre_Symtab_Present,
  NopinionReqInputSymbols_Pre_Symtab_Absent,
  NopinionReqInputSymbols_Pre_Symtab_LinkOutside,
  NopinionReqInputSymbols_Pre_Symtab_TableOutside,
  NopinionReqInputSymbols_Pre_Symtab_StringsOutside,
  NopinionReqInputSymbols_Pre_Symtab_NoMemory,
  NopinionReqInputSymbols_Pre_Symtab_NA
} NopinionReqInputSymbols_Pre_Symtab;

typedef enum {
  NopinionReqInputSymbols_Post_Symbol_Named,
  NopinionReqInputSymbols_Post_Symbol_Unnamed,
  NopinionReqInputSymbols_Post_Symbol_NA
} NopinionReqInputSymbols_Post_Symbol;

typedef enum {
  NopinionReqInputSymbols_Post_Checked_Yes,
  NopinionReqInputSymbols_Post_Checked_NA
} NopinionReqInputSymbols_Post_Checked;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Symbol_NA : 1;
  uint8_t Pre_Symtab_NA : 1;
  uint8_t Post_Symbol : 2;
  uint8_t Post_Checked : 1;
} NopinionReqInputSymbols_Entry;

/**
 * @brief Test context for spec:/nopinion/req/input-symbols test case.
 */
typedef struct {
  /**
   * @brief This member contains the ELF file.
   */
  uint8_t buf[ 4096 ];

  /**
   * @brief This member contains the size of the ELF file.
   */
  size_t size;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

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
    NopinionReqInputSymbols_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqInputSymbols_Context;

static NopinionReqInputSymbols_Context NopinionReqInputSymbols_Instance;

static const char *const NopinionReqInputSymbols_PreDesc_Symbol[] = {
  "Func",
  "NoType",
  "Object",
  "OtherSection",
  "NoName",
  "NameOutside",
  "NA"
};

static const char *const NopinionReqInputSymbols_PreDesc_Symtab[] = {
  "Present",
  "Absent",
  "LinkOutside",
  "TableOutside",
  "StringsOutside",
  "NoMemory",
  "NA"
};

static const char *const *const NopinionReqInputSymbols_PreDesc[] = {
  NopinionReqInputSymbols_PreDesc_Symbol,
  NopinionReqInputSymbols_PreDesc_Symtab,
  NULL
};

static void NopinionReqInputSymbols_Pre_Symbol_Prepare(
  NopinionReqInputSymbols_Context   *ctx,
  NopinionReqInputSymbols_Pre_Symbol state
)
{
  switch ( state ) {
    case NopinionReqInputSymbols_Pre_Symbol_Func: {
      /*
       * While the symbol at the start of the code section is a function.
       */
      /* The symbol is a function */
      break;
    }

    case NopinionReqInputSymbols_Pre_Symbol_NoType: {
      /*
       * While the symbol at the start of the code section has no type.
       */
      ( ctx->buf +
        TxGet32(
          ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 16
        ) +
        16 )[ 12 ] = 0x10;
      break;
    }

    case NopinionReqInputSymbols_Pre_Symbol_Object: {
      /*
       * While the symbol at the start of the code section is an object.
       */
      ( ctx->buf +
        TxGet32(
          ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 16
        ) +
        16 )[ 12 ] = 0x11;
      break;
    }

    case NopinionReqInputSymbols_Pre_Symbol_OtherSection: {
      /*
       * While the symbol belongs to another section.
       */
      TxPut16(
        ctx->buf +
          TxGet32(
            ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 16
          ) +
          16 + 14,
        3
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symbol_NoName: {
      /*
       * While the symbol has no name.
       */
      TxPut32(
        ctx->buf +
          TxGet32(
            ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 16
          ) +
          16,
        0
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symbol_NameOutside: {
      /*
       * While the name of the symbol exceeds the string table.
       */
      TxPut32(
        ctx->buf +
          TxGet32(
            ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 16
          ) +
          16,
        0x10000
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symbol_NA:
      break;
  }
}

static void NopinionReqInputSymbols_Pre_Symtab_Prepare(
  NopinionReqInputSymbols_Context   *ctx,
  NopinionReqInputSymbols_Pre_Symtab state
)
{
  switch ( state ) {
    case NopinionReqInputSymbols_Pre_Symtab_Present: {
      /*
       * While the ELF file has a valid symbol table.
       */
      /* The symbol table is valid */
      break;
    }

    case NopinionReqInputSymbols_Pre_Symtab_Absent: {
      /*
       * While the ELF file has no symbol table.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 4,
        0
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symtab_LinkOutside: {
      /*
       * While the string table index of the symbol table exceeds the section
       * count.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 24,
        6
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symtab_TableOutside: {
      /*
       * While the symbol table exceeds the file.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SYMTAB ) + 16,
        0x10000
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symtab_StringsOutside: {
      /*
       * While the string table of the symbol table exceeds the file.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_STRTAB ) + 16,
        0x10000
      );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symtab_NoMemory: {
      /*
       * While the allocation of the symbols fails.
       */
      TxFailMallocAfter( 1 );
      break;
    }

    case NopinionReqInputSymbols_Pre_Symtab_NA:
      break;
  }
}

static void NopinionReqInputSymbols_Post_Symbol_Check(
  NopinionReqInputSymbols_Context    *ctx,
  NopinionReqInputSymbols_Post_Symbol state
)
{
  switch ( state ) {
    case NopinionReqInputSymbols_Post_Symbol_Named: {
      /*
       * The errata checker shall name the symbol in the report line of the
       * first instruction.
       */
      T_not_null( strstr( ctx->report, " <f+0x0>: " ) );
      break;
    }

    case NopinionReqInputSymbols_Post_Symbol_Unnamed: {
      /*
       * The errata checker shall name no symbol in the report line of the
       * first instruction.
       */
      T_null( strchr( ctx->report, '<' ) );
      break;
    }

    case NopinionReqInputSymbols_Post_Symbol_NA:
      break;
  }
}

static void NopinionReqInputSymbols_Post_Checked_Check(
  NopinionReqInputSymbols_Context     *ctx,
  NopinionReqInputSymbols_Post_Checked state
)
{
  switch ( state ) {
    case NopinionReqInputSymbols_Post_Checked_Yes: {
      /*
       * The errata checker shall check the code section.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 1 );
      break;
    }

    case NopinionReqInputSymbols_Post_Checked_NA:
      break;
  }
}

static void NopinionReqInputSymbols_Prepare(
  NopinionReqInputSymbols_Context *ctx
)
{
  TxImage image;

  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxAdd() );
  TxAppend( &image, TxSt() );
  ctx->size = TxBuildElf( &image, ctx->buf, sizeof( ctx->buf ) );
}

static void NopinionReqInputSymbols_Action(
  NopinionReqInputSymbols_Context *ctx
)
{
  ctx->report = TxCheckBuffer( ctx->buf, ctx->size, NOTE_0009 );
  TxFailNext( 0 );
}

/* clang-format off */

static const NopinionReqInputSymbols_Entry
NopinionReqInputSymbols_Entries[] = {
  { 0, 0, 0, NopinionReqInputSymbols_Post_Symbol_Unnamed,
    NopinionReqInputSymbols_Post_Checked_Yes },
  { 0, 0, 0, NopinionReqInputSymbols_Post_Symbol_Named,
    NopinionReqInputSymbols_Post_Checked_Yes }
};

static const uint8_t
NopinionReqInputSymbols_Map[] = {
  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqInputSymbols_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqInputSymbols_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqInputSymbols_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqInputSymbols_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqInputSymbols_Scope,
  .initial_context = &NopinionReqInputSymbols_Instance
};

static inline NopinionReqInputSymbols_Entry NopinionReqInputSymbols_PopEntry(
  NopinionReqInputSymbols_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqInputSymbols_Entries
    [ NopinionReqInputSymbols_Map[ index ] ];
}

static void NopinionReqInputSymbols_TestVariant(
  NopinionReqInputSymbols_Context *ctx
)
{
  NopinionReqInputSymbols_Pre_Symbol_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqInputSymbols_Pre_Symtab_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqInputSymbols_Action( ctx );
  NopinionReqInputSymbols_Post_Symbol_Check( ctx, ctx->Map.entry.Post_Symbol );
  NopinionReqInputSymbols_Post_Checked_Check(
    ctx,
    ctx->Map.entry.Post_Checked
  );
}

/**
 * @fn void T_case_body_NopinionReqInputSymbols( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqInputSymbols,
  &NopinionReqInputSymbols_Fixture
)
{
  NopinionReqInputSymbols_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqInputSymbols_Pre_Symbol_Func;
    ctx->Map.pcs[ 0 ] < NopinionReqInputSymbols_Pre_Symbol_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqInputSymbols_Pre_Symtab_Present;
      ctx->Map.pcs[ 1 ] < NopinionReqInputSymbols_Pre_Symtab_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      ctx->Map.entry = NopinionReqInputSymbols_PopEntry( ctx );
      NopinionReqInputSymbols_Prepare( ctx );
      NopinionReqInputSymbols_TestVariant( ctx );
    }
  }
}

/** @} */
