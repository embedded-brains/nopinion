/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0016Fpop1
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
 * @defgroup NopinionReqCheckTn0016Fpop1 spec:/nopinion/req/check-tn-0016-fpop1
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0016Fpop1_Pre_First_Fpop1,
  NopinionReqCheckTn0016Fpop1_Pre_First_Fdiv,
  NopinionReqCheckTn0016Fpop1_Pre_First_Fpop2,
  NopinionReqCheckTn0016Fpop1_Pre_First_Load,
  NopinionReqCheckTn0016Fpop1_Pre_First_Other,
  NopinionReqCheckTn0016Fpop1_Pre_First_NA
} NopinionReqCheckTn0016Fpop1_Pre_First;

typedef enum {
  NopinionReqCheckTn0016Fpop1_Pre_Second_Stfsr,
  NopinionReqCheckTn0016Fpop1_Pre_Second_Store,
  NopinionReqCheckTn0016Fpop1_Pre_Second_Other,
  NopinionReqCheckTn0016Fpop1_Pre_Second_Absent,
  NopinionReqCheckTn0016Fpop1_Pre_Second_NA
} NopinionReqCheckTn0016Fpop1_Pre_Second;

typedef enum {
  NopinionReqCheckTn0016Fpop1_Post_Finding_None,
  NopinionReqCheckTn0016Fpop1_Post_Finding_Definite,
  NopinionReqCheckTn0016Fpop1_Post_Finding_Possible,
  NopinionReqCheckTn0016Fpop1_Post_Finding_NA
} NopinionReqCheckTn0016Fpop1_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_First_NA : 1;
  uint8_t Pre_Second_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0016Fpop1_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0016-fpop1 test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

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
    NopinionReqCheckTn0016Fpop1_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0016Fpop1_Context;

static NopinionReqCheckTn0016Fpop1_Context
  NopinionReqCheckTn0016Fpop1_Instance;

static const char *const NopinionReqCheckTn0016Fpop1_PreDesc_First[] =
  { "Fpop1", "Fdiv", "Fpop2", "Load", "Other", "NA" };

static const char *const NopinionReqCheckTn0016Fpop1_PreDesc_Second[] =
  { "Stfsr", "Store", "Other", "Absent", "NA" };

static const char *const *const NopinionReqCheckTn0016Fpop1_PreDesc[] = {
  NopinionReqCheckTn0016Fpop1_PreDesc_First,
  NopinionReqCheckTn0016Fpop1_PreDesc_Second,
  NULL
};

static void NopinionReqCheckTn0016Fpop1_Pre_First_Prepare(
  NopinionReqCheckTn0016Fpop1_Context  *ctx,
  NopinionReqCheckTn0016Fpop1_Pre_First state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Fpop1_Pre_First_Fpop1: {
      /*
       * While the first instruction of the code section is an FPop1
       * instruction other than FDIV and FSQRT.
       */
      TxAppend( &ctx->image, TxFadds() );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_First_Fdiv: {
      /*
       * While the first instruction of the code section is an FDIV
       * instruction.
       */
      TxAppend( &ctx->image, TxFpop1( TX_FDIVS, 3, 1, 2 ) );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_First_Fpop2: {
      /*
       * While the first instruction of the code section is an FPop2
       * instruction.
       */
      TxAppend( &ctx->image, TxFcmps() );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_First_Load: {
      /*
       * While the first instruction of the code section is a floating-point
       * load.
       */
      TxAppend( &ctx->image, TxLdf() );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_First_Other: {
      /*
       * While the first instruction of the code section is no floating-point
       * instruction.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_First_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Fpop1_Pre_Second_Prepare(
  NopinionReqCheckTn0016Fpop1_Context   *ctx,
  NopinionReqCheckTn0016Fpop1_Pre_Second state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Fpop1_Pre_Second_Stfsr: {
      /*
       * While the second instruction of the code section is an STFSR
       * instruction.
       */
      TxAppend( &ctx->image, TxStfsr() );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_Second_Store: {
      /*
       * While the second instruction of the code section is a floating-point
       * store other than STFSR.
       */
      TxAppend( &ctx->image, TxStfReg( 3 ) );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_Second_Other: {
      /*
       * While the second instruction of the code section is no store.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_Second_Absent: {
      /*
       * While the code section ends after the first instruction.
       */
      /* The code section ends after the first instruction */
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Pre_Second_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Fpop1_Post_Finding_Check(
  NopinionReqCheckTn0016Fpop1_Context     *ctx,
  NopinionReqCheckTn0016Fpop1_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Fpop1_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of an STFSR instruction
       * after an FPop1 instruction for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "stfsr-after-fpop1" ), 0 );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of an STFSR
       * instruction after an FPop1 instruction for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "stfsr-after-fpop1" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "stfsr-after-fpop1" ) );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Post_Finding_Possible: {
      /*
       * The errata checker shall report one possible finding of an STFSR
       * instruction after an FPop1 instruction for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "stfsr-after-fpop1" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 0, "stfsr-after-fpop1" ) );
      break;
    }

    case NopinionReqCheckTn0016Fpop1_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Fpop1_Prepare(
  NopinionReqCheckTn0016Fpop1_Context *ctx
)
{
  TxImageInit( &ctx->image );
}

static void NopinionReqCheckTn0016Fpop1_Action(
  NopinionReqCheckTn0016Fpop1_Context *ctx
)
{
  ctx->report = TxCheck( &ctx->image, NOTE_0016 );
}

/* clang-format off */

static const NopinionReqCheckTn0016Fpop1_Entry
NopinionReqCheckTn0016Fpop1_Entries[] = {
  { 0, 0, 0, NopinionReqCheckTn0016Fpop1_Post_Finding_None },
  { 0, 0, 0, NopinionReqCheckTn0016Fpop1_Post_Finding_Definite },
  { 0, 0, 0, NopinionReqCheckTn0016Fpop1_Post_Finding_Possible }
};

static const uint8_t
NopinionReqCheckTn0016Fpop1_Map[] = {
  1, 0, 0, 2, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqCheckTn0016Fpop1_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqCheckTn0016Fpop1_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckTn0016Fpop1_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0016Fpop1_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0016Fpop1_Scope,
  .initial_context = &NopinionReqCheckTn0016Fpop1_Instance
};

static inline NopinionReqCheckTn0016Fpop1_Entry
NopinionReqCheckTn0016Fpop1_PopEntry(
  NopinionReqCheckTn0016Fpop1_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0016Fpop1_Entries
    [ NopinionReqCheckTn0016Fpop1_Map[ index ] ];
}

static void NopinionReqCheckTn0016Fpop1_TestVariant(
  NopinionReqCheckTn0016Fpop1_Context *ctx
)
{
  NopinionReqCheckTn0016Fpop1_Pre_First_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0016Fpop1_Pre_Second_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0016Fpop1_Action( ctx );
  NopinionReqCheckTn0016Fpop1_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0016Fpop1( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckTn0016Fpop1,
  &NopinionReqCheckTn0016Fpop1_Fixture
)
{
  NopinionReqCheckTn0016Fpop1_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCheckTn0016Fpop1_Pre_First_Fpop1;
    ctx->Map.pcs[ 0 ] < NopinionReqCheckTn0016Fpop1_Pre_First_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCheckTn0016Fpop1_Pre_Second_Stfsr;
      ctx->Map.pcs[ 1 ] < NopinionReqCheckTn0016Fpop1_Pre_Second_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      ctx->Map.entry = NopinionReqCheckTn0016Fpop1_PopEntry( ctx );
      NopinionReqCheckTn0016Fpop1_Prepare( ctx );
      NopinionReqCheckTn0016Fpop1_TestVariant( ctx );
    }
  }
}

/** @} */
