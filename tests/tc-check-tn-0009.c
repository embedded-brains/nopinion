/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0009
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
 * @defgroup NopinionReqCheckTn0009 spec:/nopinion/req/check-tn-0009
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0009_Pre_First_StoreWord,
  NopinionReqCheckTn0009_Pre_First_StoreDouble,
  NopinionReqCheckTn0009_Pre_First_Atomic,
  NopinionReqCheckTn0009_Pre_First_Load,
  NopinionReqCheckTn0009_Pre_First_Other,
  NopinionReqCheckTn0009_Pre_First_NA
} NopinionReqCheckTn0009_Pre_First;

typedef enum {
  NopinionReqCheckTn0009_Pre_Second_StoreWord,
  NopinionReqCheckTn0009_Pre_Second_StoreDouble,
  NopinionReqCheckTn0009_Pre_Second_Atomic,
  NopinionReqCheckTn0009_Pre_Second_Load,
  NopinionReqCheckTn0009_Pre_Second_Other,
  NopinionReqCheckTn0009_Pre_Second_Absent,
  NopinionReqCheckTn0009_Pre_Second_NA
} NopinionReqCheckTn0009_Pre_Second;

typedef enum {
  NopinionReqCheckTn0009_Pre_Third_StoreWord,
  NopinionReqCheckTn0009_Pre_Third_StoreDouble,
  NopinionReqCheckTn0009_Pre_Third_Atomic,
  NopinionReqCheckTn0009_Pre_Third_Load,
  NopinionReqCheckTn0009_Pre_Third_Other,
  NopinionReqCheckTn0009_Pre_Third_Absent,
  NopinionReqCheckTn0009_Pre_Third_NA
} NopinionReqCheckTn0009_Pre_Third;

typedef enum {
  NopinionReqCheckTn0009_Post_Finding_None,
  NopinionReqCheckTn0009_Post_Finding_Definite,
  NopinionReqCheckTn0009_Post_Finding_Possible,
  NopinionReqCheckTn0009_Post_Finding_NA
} NopinionReqCheckTn0009_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_First_NA : 1;
  uint8_t Pre_Second_NA : 1;
  uint8_t Pre_Third_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0009_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0009 test case.
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
     * @brief This member defines the pre-condition indices for the next
     *   action.
     */
    size_t pci[ 3 ];

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
    NopinionReqCheckTn0009_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0009_Context;

static NopinionReqCheckTn0009_Context NopinionReqCheckTn0009_Instance;

static const char *const NopinionReqCheckTn0009_PreDesc_First[] =
  { "StoreWord", "StoreDouble", "Atomic", "Load", "Other", "NA" };

static const char *const NopinionReqCheckTn0009_PreDesc_Second[] =
  { "StoreWord", "StoreDouble", "Atomic", "Load", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0009_PreDesc_Third[] =
  { "StoreWord", "StoreDouble", "Atomic", "Load", "Other", "Absent", "NA" };

static const char *const *const NopinionReqCheckTn0009_PreDesc[] = {
  NopinionReqCheckTn0009_PreDesc_First,
  NopinionReqCheckTn0009_PreDesc_Second,
  NopinionReqCheckTn0009_PreDesc_Third,
  NULL
};

static void NopinionReqCheckTn0009_Pre_First_Prepare(
  NopinionReqCheckTn0009_Context  *ctx,
  NopinionReqCheckTn0009_Pre_First state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0009_Pre_First_StoreWord: {
      /*
       * While the first instruction of the code section is a store of word
       * size or less.
       */
      TxAppend( &ctx->image, TxSt() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_First_StoreDouble: {
      /*
       * While the first instruction of the code section is a store of double
       * word size.
       */
      TxAppend( &ctx->image, TxStd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_First_Atomic: {
      /*
       * While the first instruction of the code section is an atomic
       * load-store instruction.
       */
      TxAppend( &ctx->image, TxSwap() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_First_Load: {
      /*
       * While the first instruction of the code section is a load.
       */
      TxAppend( &ctx->image, TxLd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_First_Other: {
      /*
       * While the first instruction of the code section is neither a load, nor
       * a store, nor an atomic load-store instruction.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_First_NA:
      break;
  }
}

static void NopinionReqCheckTn0009_Pre_Second_Prepare(
  NopinionReqCheckTn0009_Context   *ctx,
  NopinionReqCheckTn0009_Pre_Second state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0009_Pre_Second_StoreWord: {
      /*
       * While the second instruction of the code section is a store of word
       * size or less.
       */
      TxAppend( &ctx->image, TxSt() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Second_StoreDouble: {
      /*
       * While the second instruction of the code section is a store of double
       * word size.
       */
      TxAppend( &ctx->image, TxStd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Second_Atomic: {
      /*
       * While the second instruction of the code section is an atomic
       * load-store instruction.
       */
      TxAppend( &ctx->image, TxSwap() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Second_Load: {
      /*
       * While the second instruction of the code section is a load.
       */
      TxAppend( &ctx->image, TxLd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Second_Other: {
      /*
       * While the second instruction of the code section is neither a load,
       * nor a store, nor an atomic load-store instruction.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Second_Absent: {
      /*
       * While the code section ends after the first instruction.
       */
      /* The code section ends after the first instruction */
      break;
    }

    case NopinionReqCheckTn0009_Pre_Second_NA:
      break;
  }
}

static void NopinionReqCheckTn0009_Pre_Third_Prepare(
  NopinionReqCheckTn0009_Context  *ctx,
  NopinionReqCheckTn0009_Pre_Third state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0009_Pre_Third_StoreWord: {
      /*
       * While the third instruction of the code section is a store of word
       * size or less.
       */
      TxAppend( &ctx->image, TxSt() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Third_StoreDouble: {
      /*
       * While the third instruction of the code section is a store of double
       * word size.
       */
      TxAppend( &ctx->image, TxStd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Third_Atomic: {
      /*
       * While the third instruction of the code section is an atomic
       * load-store instruction.
       */
      TxAppend( &ctx->image, TxSwap() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Third_Load: {
      /*
       * While the third instruction of the code section is a load.
       */
      TxAppend( &ctx->image, TxLd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Third_Other: {
      /*
       * While the third instruction of the code section is neither a load, nor
       * a store, nor an atomic load-store instruction.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0009_Pre_Third_Absent: {
      /*
       * While the code section ends after the second instruction.
       */
      /* The code section ends after the second instruction */
      break;
    }

    case NopinionReqCheckTn0009_Pre_Third_NA:
      break;
  }
}

static void NopinionReqCheckTn0009_Post_Finding_Check(
  NopinionReqCheckTn0009_Context     *ctx,
  NopinionReqCheckTn0009_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0009_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of the stale cache entry
       * erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 0 );
      break;
    }

    case NopinionReqCheckTn0009_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of the stale
       * cache entry erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "TN-0009" ) );
      break;
    }

    case NopinionReqCheckTn0009_Post_Finding_Possible: {
      /*
       * The errata checker shall report one possible finding of the stale
       * cache entry erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 0, "TN-0009" ) );
      break;
    }

    case NopinionReqCheckTn0009_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0009_Prepare(
  NopinionReqCheckTn0009_Context *ctx
)
{
  TxImageInit( &ctx->image );
}

static void NopinionReqCheckTn0009_Action(
  NopinionReqCheckTn0009_Context *ctx
)
{
  ctx->report = TxCheck( &ctx->image, NOTE_0009 );
}

/* clang-format off */

static const NopinionReqCheckTn0009_Entry
NopinionReqCheckTn0009_Entries[] = {
  { 0, 0, 0, 0, NopinionReqCheckTn0009_Post_Finding_None },
  { 1, 0, 0, 0, NopinionReqCheckTn0009_Post_Finding_NA },
  { 0, 0, 0, 0, NopinionReqCheckTn0009_Post_Finding_Definite },
  { 0, 0, 0, 1, NopinionReqCheckTn0009_Post_Finding_None },
  { 0, 0, 0, 1, NopinionReqCheckTn0009_Post_Finding_Possible },
  { 0, 0, 0, 0, NopinionReqCheckTn0009_Post_Finding_Possible }
};

static const uint8_t
NopinionReqCheckTn0009_Map[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2,
  0, 0, 0, 5, 4, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 1, 1
};

/* clang-format on */

static size_t NopinionReqCheckTn0009_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCheckTn0009_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqCheckTn0009_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0009_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0009_Scope,
  .initial_context = &NopinionReqCheckTn0009_Instance
};

static inline NopinionReqCheckTn0009_Entry NopinionReqCheckTn0009_PopEntry(
  NopinionReqCheckTn0009_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0009_Entries[ NopinionReqCheckTn0009_Map[ index ] ];
}

static void NopinionReqCheckTn0009_SetPreConditionStates(
  NopinionReqCheckTn0009_Context *ctx
)
{
  ctx->Map.pcs[ 0 ] = ctx->Map.pci[ 0 ];
  ctx->Map.pcs[ 1 ] = ctx->Map.pci[ 1 ];

  if ( ctx->Map.entry.Pre_Third_NA ) {
    ctx->Map.pcs[ 2 ] = NopinionReqCheckTn0009_Pre_Third_NA;
  } else {
    ctx->Map.pcs[ 2 ] = ctx->Map.pci[ 2 ];
  }
}

static void NopinionReqCheckTn0009_TestVariant(
  NopinionReqCheckTn0009_Context *ctx
)
{
  NopinionReqCheckTn0009_Pre_First_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0009_Pre_Second_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0009_Pre_Third_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckTn0009_Action( ctx );
  NopinionReqCheckTn0009_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0009( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqCheckTn0009, &NopinionReqCheckTn0009_Fixture )
{
  NopinionReqCheckTn0009_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pci[ 0 ] = NopinionReqCheckTn0009_Pre_First_StoreWord;
    ctx->Map.pci[ 0 ] < NopinionReqCheckTn0009_Pre_First_NA;
    ++ctx->Map.pci[ 0 ]
  ) {
    for (
      ctx->Map.pci[ 1 ] = NopinionReqCheckTn0009_Pre_Second_StoreWord;
      ctx->Map.pci[ 1 ] < NopinionReqCheckTn0009_Pre_Second_NA;
      ++ctx->Map.pci[ 1 ]
    ) {
      for (
        ctx->Map.pci[ 2 ] = NopinionReqCheckTn0009_Pre_Third_StoreWord;
        ctx->Map.pci[ 2 ] < NopinionReqCheckTn0009_Pre_Third_NA;
        ++ctx->Map.pci[ 2 ]
      ) {
        ctx->Map.entry = NopinionReqCheckTn0009_PopEntry( ctx );

        if ( ctx->Map.entry.Skip ) {
          continue;
        }

        NopinionReqCheckTn0009_SetPreConditionStates( ctx );
        NopinionReqCheckTn0009_Prepare( ctx );
        NopinionReqCheckTn0009_TestVariant( ctx );
      }
    }
  }
}

/** @} */
