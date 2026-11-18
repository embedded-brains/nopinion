/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0016Stfsr
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
 * @defgroup NopinionReqCheckTn0016Stfsr spec:/nopinion/req/check-tn-0016-stfsr
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0016Stfsr_Pre_First_Stfsr,
  NopinionReqCheckTn0016Stfsr_Pre_First_Store,
  NopinionReqCheckTn0016Stfsr_Pre_First_Other,
  NopinionReqCheckTn0016Stfsr_Pre_First_NA
} NopinionReqCheckTn0016Stfsr_Pre_First;

typedef enum {
  NopinionReqCheckTn0016Stfsr_Pre_Second_Stfsr,
  NopinionReqCheckTn0016Stfsr_Pre_Second_Other,
  NopinionReqCheckTn0016Stfsr_Pre_Second_Absent,
  NopinionReqCheckTn0016Stfsr_Pre_Second_NA
} NopinionReqCheckTn0016Stfsr_Pre_Second;

typedef enum {
  NopinionReqCheckTn0016Stfsr_Pre_Third_Stfsr,
  NopinionReqCheckTn0016Stfsr_Pre_Third_Other,
  NopinionReqCheckTn0016Stfsr_Pre_Third_Absent,
  NopinionReqCheckTn0016Stfsr_Pre_Third_NA
} NopinionReqCheckTn0016Stfsr_Pre_Third;

typedef enum {
  NopinionReqCheckTn0016Stfsr_Pre_Fourth_Stfsr,
  NopinionReqCheckTn0016Stfsr_Pre_Fourth_Other,
  NopinionReqCheckTn0016Stfsr_Pre_Fourth_Absent,
  NopinionReqCheckTn0016Stfsr_Pre_Fourth_NA
} NopinionReqCheckTn0016Stfsr_Pre_Fourth;

typedef enum {
  NopinionReqCheckTn0016Stfsr_Pre_Fifth_Stfsr,
  NopinionReqCheckTn0016Stfsr_Pre_Fifth_Other,
  NopinionReqCheckTn0016Stfsr_Pre_Fifth_Absent,
  NopinionReqCheckTn0016Stfsr_Pre_Fifth_NA
} NopinionReqCheckTn0016Stfsr_Pre_Fifth;

typedef enum {
  NopinionReqCheckTn0016Stfsr_Post_Finding_None,
  NopinionReqCheckTn0016Stfsr_Post_Finding_Definite,
  NopinionReqCheckTn0016Stfsr_Post_Finding_Possible,
  NopinionReqCheckTn0016Stfsr_Post_Finding_NA
} NopinionReqCheckTn0016Stfsr_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_First_NA : 1;
  uint8_t Pre_Second_NA : 1;
  uint8_t Pre_Third_NA : 1;
  uint8_t Pre_Fourth_NA : 1;
  uint8_t Pre_Fifth_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0016Stfsr_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0016-stfsr test case.
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
    size_t pci[ 5 ];

    /**
     * @brief This member defines the pre-condition states for the next action.
     */
    size_t pcs[ 5 ];

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
    NopinionReqCheckTn0016Stfsr_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0016Stfsr_Context;

static NopinionReqCheckTn0016Stfsr_Context
  NopinionReqCheckTn0016Stfsr_Instance;

static const char *const NopinionReqCheckTn0016Stfsr_PreDesc_First[] =
  { "Stfsr", "Store", "Other", "NA" };

static const char *const NopinionReqCheckTn0016Stfsr_PreDesc_Second[] =
  { "Stfsr", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0016Stfsr_PreDesc_Third[] =
  { "Stfsr", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0016Stfsr_PreDesc_Fourth[] =
  { "Stfsr", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0016Stfsr_PreDesc_Fifth[] =
  { "Stfsr", "Other", "Absent", "NA" };

static const char *const *const NopinionReqCheckTn0016Stfsr_PreDesc[] = {
  NopinionReqCheckTn0016Stfsr_PreDesc_First,
  NopinionReqCheckTn0016Stfsr_PreDesc_Second,
  NopinionReqCheckTn0016Stfsr_PreDesc_Third,
  NopinionReqCheckTn0016Stfsr_PreDesc_Fourth,
  NopinionReqCheckTn0016Stfsr_PreDesc_Fifth,
  NULL
};

static void NopinionReqCheckTn0016Stfsr_Pre_First_Prepare(
  NopinionReqCheckTn0016Stfsr_Context  *ctx,
  NopinionReqCheckTn0016Stfsr_Pre_First state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Stfsr_Pre_First_Stfsr: {
      /*
       * While the first instruction of the code section is an STFSR
       * instruction.
       */
      TxAppend( &ctx->image, TxStfsr() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_First_Store: {
      /*
       * While the first instruction of the code section is a store other than
       * STFSR.
       */
      TxAppend( &ctx->image, TxSt() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_First_Other: {
      /*
       * While the first instruction of the code section is no store.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_First_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Stfsr_Pre_Second_Prepare(
  NopinionReqCheckTn0016Stfsr_Context   *ctx,
  NopinionReqCheckTn0016Stfsr_Pre_Second state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Stfsr_Pre_Second_Stfsr: {
      /*
       * While the second instruction of the code section is an STFSR
       * instruction.
       */
      TxAppend( &ctx->image, TxStfsr() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Second_Other: {
      /*
       * While the second instruction of the code section is no store.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Second_Absent: {
      /*
       * While the code section ends after the first instruction.
       */
      /* The code section ends after the first instruction */
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Second_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Stfsr_Pre_Third_Prepare(
  NopinionReqCheckTn0016Stfsr_Context  *ctx,
  NopinionReqCheckTn0016Stfsr_Pre_Third state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Stfsr_Pre_Third_Stfsr: {
      /*
       * While the third instruction of the code section is an STFSR
       * instruction.
       */
      TxAppend( &ctx->image, TxStfsr() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Third_Other: {
      /*
       * While the third instruction of the code section is no store.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Third_Absent: {
      /*
       * While the code section ends after the second instruction.
       */
      /* The code section ends after the second instruction */
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Third_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Stfsr_Pre_Fourth_Prepare(
  NopinionReqCheckTn0016Stfsr_Context   *ctx,
  NopinionReqCheckTn0016Stfsr_Pre_Fourth state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Stfsr_Pre_Fourth_Stfsr: {
      /*
       * While the fourth instruction of the code section is an STFSR
       * instruction.
       */
      TxAppend( &ctx->image, TxStfsr() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Fourth_Other: {
      /*
       * While the fourth instruction of the code section is no store.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Fourth_Absent: {
      /*
       * While the code section ends after the third instruction.
       */
      /* The code section ends after the third instruction */
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Fourth_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Stfsr_Pre_Fifth_Prepare(
  NopinionReqCheckTn0016Stfsr_Context  *ctx,
  NopinionReqCheckTn0016Stfsr_Pre_Fifth state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Stfsr_Pre_Fifth_Stfsr: {
      /*
       * While the fifth instruction of the code section is an STFSR
       * instruction.
       */
      TxAppend( &ctx->image, TxStfsr() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Fifth_Other: {
      /*
       * While the fifth instruction of the code section is no store.
       */
      TxAppend( &ctx->image, TxAdd() );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Fifth_Absent: {
      /*
       * While the code section ends after the fourth instruction.
       */
      /* The code section ends after the fourth instruction */
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Pre_Fifth_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Stfsr_Post_Finding_Check(
  NopinionReqCheckTn0016Stfsr_Context     *ctx,
  NopinionReqCheckTn0016Stfsr_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0016Stfsr_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of an STFSR instruction
       * after an STFSR instruction for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "stfsr-after-stfsr" ), 0 );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of an STFSR
       * instruction after an STFSR instruction for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "stfsr-after-stfsr" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "stfsr-after-stfsr" ) );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Post_Finding_Possible: {
      /*
       * The errata checker shall report one possible finding of an STFSR
       * instruction after an STFSR instruction for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "stfsr-after-stfsr" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 0, "stfsr-after-stfsr" ) );
      break;
    }

    case NopinionReqCheckTn0016Stfsr_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0016Stfsr_Prepare(
  NopinionReqCheckTn0016Stfsr_Context *ctx
)
{
  TxImageInit( &ctx->image );
}

static void NopinionReqCheckTn0016Stfsr_Action(
  NopinionReqCheckTn0016Stfsr_Context *ctx
)
{
  ctx->report = TxCheck( &ctx->image, NOTE_0016 );
}

/* clang-format off */

static const NopinionReqCheckTn0016Stfsr_Entry
NopinionReqCheckTn0016Stfsr_Entries[] = {
  { 1, 0, 0, 0, 0, 0, NopinionReqCheckTn0016Stfsr_Post_Finding_NA },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckTn0016Stfsr_Post_Finding_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckTn0016Stfsr_Post_Finding_Definite },
  { 0, 0, 0, 0, 0, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_None },
  { 0, 0, 0, 0, 1, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_None },
  { 0, 0, 0, 0, 0, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_Definite },
  { 0, 0, 0, 1, 1, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_None },
  { 0, 0, 0, 0, 1, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_Definite },
  { 0, 0, 0, 0, 0, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_Possible },
  { 0, 0, 0, 0, 1, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_Possible },
  { 0, 0, 0, 1, 1, 1, NopinionReqCheckTn0016Stfsr_Post_Finding_Possible }
};

static const uint8_t
NopinionReqCheckTn0016Stfsr_Map[] = {
  2, 2, 2, 2, 2, 2, 5, 0, 0, 2, 2, 2, 2, 2, 2, 5, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0,
  0, 2, 2, 2, 2, 2, 2, 5, 0, 0, 2, 2, 2, 1, 1, 1, 8, 0, 0, 9, 0, 0, 0, 0, 0, 0,
  0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 4, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 4, 0, 0,
  0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 4,
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0, 1, 1, 1, 1, 1, 1, 3, 0, 0,
  4, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqCheckTn0016Stfsr_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqCheckTn0016Stfsr_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckTn0016Stfsr_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0016Stfsr_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0016Stfsr_Scope,
  .initial_context = &NopinionReqCheckTn0016Stfsr_Instance
};

static inline NopinionReqCheckTn0016Stfsr_Entry
NopinionReqCheckTn0016Stfsr_PopEntry(
  NopinionReqCheckTn0016Stfsr_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0016Stfsr_Entries
    [ NopinionReqCheckTn0016Stfsr_Map[ index ] ];
}

static void NopinionReqCheckTn0016Stfsr_SetPreConditionStates(
  NopinionReqCheckTn0016Stfsr_Context *ctx
)
{
  ctx->Map.pcs[ 0 ] = ctx->Map.pci[ 0 ];
  ctx->Map.pcs[ 1 ] = ctx->Map.pci[ 1 ];

  if ( ctx->Map.entry.Pre_Third_NA ) {
    ctx->Map.pcs[ 2 ] = NopinionReqCheckTn0016Stfsr_Pre_Third_NA;
  } else {
    ctx->Map.pcs[ 2 ] = ctx->Map.pci[ 2 ];
  }

  if ( ctx->Map.entry.Pre_Fourth_NA ) {
    ctx->Map.pcs[ 3 ] = NopinionReqCheckTn0016Stfsr_Pre_Fourth_NA;
  } else {
    ctx->Map.pcs[ 3 ] = ctx->Map.pci[ 3 ];
  }

  if ( ctx->Map.entry.Pre_Fifth_NA ) {
    ctx->Map.pcs[ 4 ] = NopinionReqCheckTn0016Stfsr_Pre_Fifth_NA;
  } else {
    ctx->Map.pcs[ 4 ] = ctx->Map.pci[ 4 ];
  }
}

static void NopinionReqCheckTn0016Stfsr_TestVariant(
  NopinionReqCheckTn0016Stfsr_Context *ctx
)
{
  NopinionReqCheckTn0016Stfsr_Pre_First_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0016Stfsr_Pre_Second_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0016Stfsr_Pre_Third_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckTn0016Stfsr_Pre_Fourth_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqCheckTn0016Stfsr_Pre_Fifth_Prepare( ctx, ctx->Map.pcs[ 4 ] );
  NopinionReqCheckTn0016Stfsr_Action( ctx );
  NopinionReqCheckTn0016Stfsr_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0016Stfsr( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckTn0016Stfsr,
  &NopinionReqCheckTn0016Stfsr_Fixture
)
{
  NopinionReqCheckTn0016Stfsr_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pci[ 0 ] = NopinionReqCheckTn0016Stfsr_Pre_First_Stfsr;
    ctx->Map.pci[ 0 ] < NopinionReqCheckTn0016Stfsr_Pre_First_NA;
    ++ctx->Map.pci[ 0 ]
  ) {
    for (
      ctx->Map.pci[ 1 ] = NopinionReqCheckTn0016Stfsr_Pre_Second_Stfsr;
      ctx->Map.pci[ 1 ] < NopinionReqCheckTn0016Stfsr_Pre_Second_NA;
      ++ctx->Map.pci[ 1 ]
    ) {
      for (
        ctx->Map.pci[ 2 ] = NopinionReqCheckTn0016Stfsr_Pre_Third_Stfsr;
        ctx->Map.pci[ 2 ] < NopinionReqCheckTn0016Stfsr_Pre_Third_NA;
        ++ctx->Map.pci[ 2 ]
      ) {
        for (
          ctx->Map.pci[ 3 ] = NopinionReqCheckTn0016Stfsr_Pre_Fourth_Stfsr;
          ctx->Map.pci[ 3 ] < NopinionReqCheckTn0016Stfsr_Pre_Fourth_NA;
          ++ctx->Map.pci[ 3 ]
        ) {
          for (
            ctx->Map.pci[ 4 ] = NopinionReqCheckTn0016Stfsr_Pre_Fifth_Stfsr;
            ctx->Map.pci[ 4 ] < NopinionReqCheckTn0016Stfsr_Pre_Fifth_NA;
            ++ctx->Map.pci[ 4 ]
          ) {
            ctx->Map.entry = NopinionReqCheckTn0016Stfsr_PopEntry( ctx );

            if ( ctx->Map.entry.Skip ) {
              continue;
            }

            NopinionReqCheckTn0016Stfsr_SetPreConditionStates( ctx );
            NopinionReqCheckTn0016Stfsr_Prepare( ctx );
            NopinionReqCheckTn0016Stfsr_TestVariant( ctx );
          }
        }
      }
    }
  }
}

/** @} */
