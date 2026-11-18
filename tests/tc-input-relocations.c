/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqInputRelocations
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
 * @defgroup NopinionReqInputRelocations spec:/nopinion/req/input-relocations
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqInputRelocations_Pre_Type_Rela,
  NopinionReqInputRelocations_Pre_Type_Rel,
  NopinionReqInputRelocations_Pre_Type_NA
} NopinionReqInputRelocations_Pre_Type;

typedef enum {
  NopinionReqInputRelocations_Pre_Section_Code,
  NopinionReqInputRelocations_Pre_Section_Other,
  NopinionReqInputRelocations_Pre_Section_NA
} NopinionReqInputRelocations_Pre_Section;

typedef enum {
  NopinionReqInputRelocations_Pre_Table_Inside,
  NopinionReqInputRelocations_Pre_Table_Outside,
  NopinionReqInputRelocations_Pre_Table_NA
} NopinionReqInputRelocations_Pre_Table;

typedef enum {
  NopinionReqInputRelocations_Pre_Offset_Inside,
  NopinionReqInputRelocations_Pre_Offset_Beyond,
  NopinionReqInputRelocations_Pre_Offset_NA
} NopinionReqInputRelocations_Pre_Offset;

typedef enum {
  NopinionReqInputRelocations_Post_Target_Known,
  NopinionReqInputRelocations_Post_Target_Unknown,
  NopinionReqInputRelocations_Post_Target_NA
} NopinionReqInputRelocations_Post_Target;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Type_NA : 1;
  uint8_t Pre_Section_NA : 1;
  uint8_t Pre_Table_NA : 1;
  uint8_t Pre_Offset_NA : 1;
  uint8_t Post_Target : 2;
} NopinionReqInputRelocations_Entry;

/**
 * @brief Test context for spec:/nopinion/req/input-relocations test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member is true, if the relocation section exceeds the file.
   */
  bool outside;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

  struct {
    /**
     * @brief This member defines the pre-condition states for the next action.
     */
    size_t pcs[ 4 ];

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
    NopinionReqInputRelocations_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqInputRelocations_Context;

static NopinionReqInputRelocations_Context
  NopinionReqInputRelocations_Instance;

static const char *const NopinionReqInputRelocations_PreDesc_Type[] =
  { "Rela", "Rel", "NA" };

static const char *const NopinionReqInputRelocations_PreDesc_Section[] =
  { "Code", "Other", "NA" };

static const char *const NopinionReqInputRelocations_PreDesc_Table[] =
  { "Inside", "Outside", "NA" };

static const char *const NopinionReqInputRelocations_PreDesc_Offset[] =
  { "Inside", "Beyond", "NA" };

static const char *const *const NopinionReqInputRelocations_PreDesc[] = {
  NopinionReqInputRelocations_PreDesc_Type,
  NopinionReqInputRelocations_PreDesc_Section,
  NopinionReqInputRelocations_PreDesc_Table,
  NopinionReqInputRelocations_PreDesc_Offset,
  NULL
};

static void NopinionReqInputRelocations_Pre_Type_Prepare(
  NopinionReqInputRelocations_Context *ctx,
  NopinionReqInputRelocations_Pre_Type state
)
{
  switch ( state ) {
    case NopinionReqInputRelocations_Pre_Type_Rela: {
      /*
       * While the relocation section has the type SHT_RELA.
       */
      ctx->image.rel = false;
      break;
    }

    case NopinionReqInputRelocations_Pre_Type_Rel: {
      /*
       * While the relocation section has the type SHT_REL.
       */
      ctx->image.rel = true;
      break;
    }

    case NopinionReqInputRelocations_Pre_Type_NA:
      break;
  }
}

static void NopinionReqInputRelocations_Pre_Section_Prepare(
  NopinionReqInputRelocations_Context    *ctx,
  NopinionReqInputRelocations_Pre_Section state
)
{
  switch ( state ) {
    case NopinionReqInputRelocations_Pre_Section_Code: {
      /*
       * While the relocation section applies to the code section.
       */
      ctx->image.relocation_info = TX_SECTION_TEXT;
      break;
    }

    case NopinionReqInputRelocations_Pre_Section_Other: {
      /*
       * While the relocation section applies to another section.
       */
      ctx->image.relocation_info = TX_SECTION_SYMTAB;
      break;
    }

    case NopinionReqInputRelocations_Pre_Section_NA:
      break;
  }
}

static void NopinionReqInputRelocations_Pre_Table_Prepare(
  NopinionReqInputRelocations_Context  *ctx,
  NopinionReqInputRelocations_Pre_Table state
)
{
  switch ( state ) {
    case NopinionReqInputRelocations_Pre_Table_Inside: {
      /*
       * While the relocation section is inside the file.
       */
      ctx->outside = false;
      break;
    }

    case NopinionReqInputRelocations_Pre_Table_Outside: {
      /*
       * While the relocation section exceeds the file.
       */
      ctx->outside = true;
      break;
    }

    case NopinionReqInputRelocations_Pre_Table_NA:
      break;
  }
}

static void NopinionReqInputRelocations_Pre_Offset_Prepare(
  NopinionReqInputRelocations_Context   *ctx,
  NopinionReqInputRelocations_Pre_Offset state
)
{
  switch ( state ) {
    case NopinionReqInputRelocations_Pre_Offset_Inside: {
      /*
       * While the relocation applies to the CALL instruction.
       */
      TxAddRelocation( &ctx->image, 0 );
      break;
    }

    case NopinionReqInputRelocations_Pre_Offset_Beyond: {
      /*
       * While the relocation applies to an offset beyond the code section.
       */
      TxAddRelocation( &ctx->image, 1024 );
      break;
    }

    case NopinionReqInputRelocations_Pre_Offset_NA:
      break;
  }
}

static void NopinionReqInputRelocations_Post_Target_Check(
  NopinionReqInputRelocations_Context    *ctx,
  NopinionReqInputRelocations_Post_Target state
)
{
  switch ( state ) {
    case NopinionReqInputRelocations_Post_Target_Known: {
      /*
       * The errata checker shall follow the CALL instruction to its target.
       */
      T_eq_int( TxCountAt( ctx->report, 4, "TN-0009" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 4, "TN-0009" ) );
      break;
    }

    case NopinionReqInputRelocations_Post_Target_Unknown: {
      /*
       * The errata checker shall treat the target of the CALL instruction as
       * an unknown instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 4, "TN-0009" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 4, "TN-0009" ) );
      break;
    }

    case NopinionReqInputRelocations_Post_Target_NA:
      break;
  }
}

static void NopinionReqInputRelocations_Prepare(
  NopinionReqInputRelocations_Context *ctx
)
{
  TxImageInit( &ctx->image );
  TxAppend( &ctx->image, TxCall( 4 ) );
  TxAppend( &ctx->image, TxStd() );
  TxAppend( &ctx->image, TxAdd() );
  TxAppend( &ctx->image, TxNop() );
  TxAppend( &ctx->image, TxSt() );
  TxAppend( &ctx->image, TxNop() );
}

static void NopinionReqInputRelocations_Action(
  NopinionReqInputRelocations_Context *ctx
)
{
  uint8_t buf[ 4096 ];
  size_t  size;

  size = TxBuildElf( &ctx->image, buf, sizeof( buf ) );

  if ( ctx->outside ) {
    TxPut32( buf + TxSectionHeader( buf, TX_SECTION_RELA ) + 16, 0x10000 );
  }

  ctx->report = TxCheckBuffer( buf, size, NOTE_0009 );
}

/* clang-format off */

static const NopinionReqInputRelocations_Entry
NopinionReqInputRelocations_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqInputRelocations_Post_Target_Known },
  { 0, 0, 0, 0, 0, NopinionReqInputRelocations_Post_Target_Unknown }
};

static const uint8_t
NopinionReqInputRelocations_Map[] = {
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqInputRelocations_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqInputRelocations_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqInputRelocations_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqInputRelocations_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqInputRelocations_Scope,
  .initial_context = &NopinionReqInputRelocations_Instance
};

static inline NopinionReqInputRelocations_Entry
NopinionReqInputRelocations_PopEntry(
  NopinionReqInputRelocations_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqInputRelocations_Entries
    [ NopinionReqInputRelocations_Map[ index ] ];
}

static void NopinionReqInputRelocations_TestVariant(
  NopinionReqInputRelocations_Context *ctx
)
{
  NopinionReqInputRelocations_Pre_Type_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqInputRelocations_Pre_Section_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqInputRelocations_Pre_Table_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqInputRelocations_Pre_Offset_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqInputRelocations_Action( ctx );
  NopinionReqInputRelocations_Post_Target_Check(
    ctx,
    ctx->Map.entry.Post_Target
  );
}

/**
 * @fn void T_case_body_NopinionReqInputRelocations( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqInputRelocations,
  &NopinionReqInputRelocations_Fixture
)
{
  NopinionReqInputRelocations_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqInputRelocations_Pre_Type_Rela;
    ctx->Map.pcs[ 0 ] < NopinionReqInputRelocations_Pre_Type_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqInputRelocations_Pre_Section_Code;
      ctx->Map.pcs[ 1 ] < NopinionReqInputRelocations_Pre_Section_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqInputRelocations_Pre_Table_Inside;
        ctx->Map.pcs[ 2 ] < NopinionReqInputRelocations_Pre_Table_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        for (
          ctx->Map.pcs[ 3 ] = NopinionReqInputRelocations_Pre_Offset_Inside;
          ctx->Map.pcs[ 3 ] < NopinionReqInputRelocations_Pre_Offset_NA;
          ++ctx->Map.pcs[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqInputRelocations_PopEntry( ctx );
          NopinionReqInputRelocations_Prepare( ctx );
          NopinionReqInputRelocations_TestVariant( ctx );
        }
      }
    }
  }
}

/** @} */
