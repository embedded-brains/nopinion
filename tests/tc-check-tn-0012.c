/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0012
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
 * @defgroup NopinionReqCheckTn0012 spec:/nopinion/req/check-tn-0012
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0012_Pre_First_SetsIcc,
  NopinionReqCheckTn0012_Pre_First_Other,
  NopinionReqCheckTn0012_Pre_First_NA
} NopinionReqCheckTn0012_Pre_First;

typedef enum {
  NopinionReqCheckTn0012_Pre_Branch_IccAnnul,
  NopinionReqCheckTn0012_Pre_Branch_Icc,
  NopinionReqCheckTn0012_Pre_Branch_Unconditional,
  NopinionReqCheckTn0012_Pre_Branch_Other,
  NopinionReqCheckTn0012_Pre_Branch_Absent,
  NopinionReqCheckTn0012_Pre_Branch_NA
} NopinionReqCheckTn0012_Pre_Branch;

typedef enum {
  NopinionReqCheckTn0012_Pre_Slot_FPop1,
  NopinionReqCheckTn0012_Pre_Slot_FPop2,
  NopinionReqCheckTn0012_Pre_Slot_FBfcc,
  NopinionReqCheckTn0012_Pre_Slot_FLoad,
  NopinionReqCheckTn0012_Pre_Slot_Other,
  NopinionReqCheckTn0012_Pre_Slot_Absent,
  NopinionReqCheckTn0012_Pre_Slot_NA
} NopinionReqCheckTn0012_Pre_Slot;

typedef enum {
  NopinionReqCheckTn0012_Pre_Target_FPop1,
  NopinionReqCheckTn0012_Pre_Target_FPop2,
  NopinionReqCheckTn0012_Pre_Target_FBfcc,
  NopinionReqCheckTn0012_Pre_Target_FLoad,
  NopinionReqCheckTn0012_Pre_Target_Other,
  NopinionReqCheckTn0012_Pre_Target_Unknown,
  NopinionReqCheckTn0012_Pre_Target_NA
} NopinionReqCheckTn0012_Pre_Target;

typedef enum {
  NopinionReqCheckTn0012_Post_Finding_None,
  NopinionReqCheckTn0012_Post_Finding_Definite,
  NopinionReqCheckTn0012_Post_Finding_Possible,
  NopinionReqCheckTn0012_Post_Finding_NA
} NopinionReqCheckTn0012_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_First_NA : 1;
  uint8_t Pre_Branch_NA : 1;
  uint8_t Pre_Slot_NA : 1;
  uint8_t Pre_Target_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0012_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0012 test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the first instruction.
   */
  uint32_t first;

  /**
   * @brief This member contains the second instruction.
   */
  uint32_t branch;

  /**
   * @brief This member contains the third instruction.
   */
  uint32_t slot;

  /**
   * @brief This member contains the instruction at the target of the branch.
   */
  uint32_t target;

  /**
   * @brief This member is true, if the code section ends after the first
   *   instruction.
   */
  bool branch_absent;

  /**
   * @brief This member is true, if the code section ends after the second
   *   instruction.
   */
  bool slot_absent;

  /**
   * @brief This member is true, if a relocation applies to the branch.
   */
  bool relocated;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

  struct {
    /**
     * @brief This member defines the pre-condition indices for the next
     *   action.
     */
    size_t pci[ 4 ];

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
    NopinionReqCheckTn0012_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0012_Context;

static NopinionReqCheckTn0012_Context NopinionReqCheckTn0012_Instance;

static const char *const NopinionReqCheckTn0012_PreDesc_First[] =
  { "SetsIcc", "Other", "NA" };

static const char *const NopinionReqCheckTn0012_PreDesc_Branch[] =
  { "IccAnnul", "Icc", "Unconditional", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0012_PreDesc_Slot[] =
  { "FPop1", "FPop2", "FBfcc", "FLoad", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0012_PreDesc_Target[] =
  { "FPop1", "FPop2", "FBfcc", "FLoad", "Other", "Unknown", "NA" };

static const char *const *const NopinionReqCheckTn0012_PreDesc[] = {
  NopinionReqCheckTn0012_PreDesc_First,
  NopinionReqCheckTn0012_PreDesc_Branch,
  NopinionReqCheckTn0012_PreDesc_Slot,
  NopinionReqCheckTn0012_PreDesc_Target,
  NULL
};

static void NopinionReqCheckTn0012_Pre_First_Prepare(
  NopinionReqCheckTn0012_Context  *ctx,
  NopinionReqCheckTn0012_Pre_First state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0012_Pre_First_SetsIcc: {
      /*
       * While the first instruction modifies the integer condition codes.
       */
      ctx->first = TxSubcc();
      break;
    }

    case NopinionReqCheckTn0012_Pre_First_Other: {
      /*
       * While the first instruction neither modifies the integer condition
       * codes nor transfers control.
       */
      ctx->first = TxSt();
      break;
    }

    case NopinionReqCheckTn0012_Pre_First_NA:
      break;
  }
}

static void NopinionReqCheckTn0012_Pre_Branch_Prepare(
  NopinionReqCheckTn0012_Context   *ctx,
  NopinionReqCheckTn0012_Pre_Branch state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0012_Pre_Branch_IccAnnul: {
      /*
       * While the second instruction is a branch on integer condition codes
       * which depends on the condition codes and has the annul bit set.
       */
      ctx->branch = TxBicc( 1, true, -3 );
      break;
    }

    case NopinionReqCheckTn0012_Pre_Branch_Icc: {
      /*
       * While the second instruction is a branch on integer condition codes
       * which depends on the condition codes and has the annul bit cleared.
       */
      ctx->branch = TxBicc( 1, false, -3 );
      break;
    }

    case NopinionReqCheckTn0012_Pre_Branch_Unconditional: {
      /*
       * While the second instruction is a branch on integer condition codes
       * which does not depend on the condition codes.
       */
      ctx->branch = TxBicc( 8, false, -3 );
      break;
    }

    case NopinionReqCheckTn0012_Pre_Branch_Other: {
      /*
       * While the second instruction transfers no control.
       */
      ctx->branch = TxAdd();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Branch_Absent: {
      /*
       * While the code section ends after the first instruction.
       */
      ctx->branch_absent = true;
      break;
    }

    case NopinionReqCheckTn0012_Pre_Branch_NA:
      break;
  }
}

static void NopinionReqCheckTn0012_Pre_Slot_Prepare(
  NopinionReqCheckTn0012_Context *ctx,
  NopinionReqCheckTn0012_Pre_Slot state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0012_Pre_Slot_FPop1: {
      /*
       * While the third instruction is an FPop1 instruction.
       */
      ctx->slot = TxFadds();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Slot_FPop2: {
      /*
       * While the third instruction is an FPop2 instruction.
       */
      ctx->slot = TxFcmps();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Slot_FBfcc: {
      /*
       * While the third instruction is a branch on floating-point condition
       * codes.
       */
      ctx->slot = TxFbfcc( false, 0 );
      break;
    }

    case NopinionReqCheckTn0012_Pre_Slot_FLoad: {
      /*
       * While the third instruction is a load of a floating-point register.
       */
      ctx->slot = TxLdf();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Slot_Other: {
      /*
       * While the third instruction is no floating-point instruction and
       * transfers no control.
       */
      ctx->slot = TxAdd();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Slot_Absent: {
      /*
       * While the code section ends after the second instruction.
       */
      ctx->slot_absent = true;
      break;
    }

    case NopinionReqCheckTn0012_Pre_Slot_NA:
      break;
  }
}

static void NopinionReqCheckTn0012_Pre_Target_Prepare(
  NopinionReqCheckTn0012_Context   *ctx,
  NopinionReqCheckTn0012_Pre_Target state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0012_Pre_Target_FPop1: {
      /*
       * While the target of the branch is an FPop1 instruction.
       */
      ctx->target = TxFadds();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Target_FPop2: {
      /*
       * While the target of the branch is an FPop2 instruction.
       */
      ctx->target = TxFcmps();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Target_FBfcc: {
      /*
       * While the target of the branch is a branch on floating-point condition
       * codes.
       */
      ctx->target = TxFbfcc( false, 0 );
      break;
    }

    case NopinionReqCheckTn0012_Pre_Target_FLoad: {
      /*
       * While the target of the branch is a load of a floating-point register.
       */
      ctx->target = TxLdf();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Target_Other: {
      /*
       * While the target of the branch is no floating-point instruction and
       * transfers no control.
       */
      ctx->target = TxAdd();
      break;
    }

    case NopinionReqCheckTn0012_Pre_Target_Unknown: {
      /*
       * While the target of the branch is an unknown instruction.
       */
      ctx->target = TxAdd();
      ctx->relocated = true;
      break;
    }

    case NopinionReqCheckTn0012_Pre_Target_NA:
      break;
  }
}

static void NopinionReqCheckTn0012_Post_Finding_Check(
  NopinionReqCheckTn0012_Context     *ctx,
  NopinionReqCheckTn0012_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0012_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of the incorrect annulation
       * erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 8, "TN-0012" ), 0 );
      break;
    }

    case NopinionReqCheckTn0012_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of the incorrect
       * annulation erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 8, "TN-0012" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 8, "TN-0012" ) );
      break;
    }

    case NopinionReqCheckTn0012_Post_Finding_Possible: {
      /*
       * The errata checker shall report one possible finding of the incorrect
       * annulation erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 8, "TN-0012" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 8, "TN-0012" ) );
      break;
    }

    case NopinionReqCheckTn0012_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0012_Prepare(
  NopinionReqCheckTn0012_Context *ctx
)
{
  TxImageInit( &ctx->image );
  ctx->target = TxNop();
  ctx->slot = TxNop();
  ctx->branch_absent = false;
  ctx->slot_absent = false;
  ctx->relocated = false;
}

static void NopinionReqCheckTn0012_Action(
  NopinionReqCheckTn0012_Context *ctx
)
{
  TxAppend( &ctx->image, ctx->target );
  TxAppend( &ctx->image, TxNop() );
  TxAppend( &ctx->image, ctx->first );

  if ( !ctx->branch_absent ) {
    TxAppend( &ctx->image, ctx->branch );

    if ( ctx->relocated ) {
      TxAddRelocation( &ctx->image, 3 );
    }

    if ( !ctx->slot_absent ) {
      TxAppend( &ctx->image, ctx->slot );
    }
  }

  ctx->report = TxCheck( &ctx->image, NOTE_0012 );
}

/* clang-format off */

static const NopinionReqCheckTn0012_Entry
NopinionReqCheckTn0012_Entries[] = {
  { 1, 0, 0, 0, 0, NopinionReqCheckTn0012_Post_Finding_NA },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0012_Post_Finding_None },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0012_Post_Finding_Definite },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0012_Post_Finding_Possible },
  { 0, 0, 0, 1, 1, NopinionReqCheckTn0012_Post_Finding_None },
  { 0, 0, 0, 1, 1, NopinionReqCheckTn0012_Post_Finding_Possible }
};

static const uint8_t
NopinionReqCheckTn0012_Map[] = {
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 2, 2,
  2, 1, 1, 3, 2, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1, 3, 2, 2, 2, 1, 1, 3, 2, 2, 2, 1,
  1, 3, 2, 2, 2, 1, 1, 3, 2, 2, 2, 1, 1, 3, 2, 2, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqCheckTn0012_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCheckTn0012_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqCheckTn0012_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0012_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0012_Scope,
  .initial_context = &NopinionReqCheckTn0012_Instance
};

static inline NopinionReqCheckTn0012_Entry NopinionReqCheckTn0012_PopEntry(
  NopinionReqCheckTn0012_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0012_Entries[ NopinionReqCheckTn0012_Map[ index ] ];
}

static void NopinionReqCheckTn0012_SetPreConditionStates(
  NopinionReqCheckTn0012_Context *ctx
)
{
  ctx->Map.pcs[ 0 ] = ctx->Map.pci[ 0 ];
  ctx->Map.pcs[ 1 ] = ctx->Map.pci[ 1 ];

  if ( ctx->Map.entry.Pre_Slot_NA ) {
    ctx->Map.pcs[ 2 ] = NopinionReqCheckTn0012_Pre_Slot_NA;
  } else {
    ctx->Map.pcs[ 2 ] = ctx->Map.pci[ 2 ];
  }

  if ( ctx->Map.entry.Pre_Target_NA ) {
    ctx->Map.pcs[ 3 ] = NopinionReqCheckTn0012_Pre_Target_NA;
  } else {
    ctx->Map.pcs[ 3 ] = ctx->Map.pci[ 3 ];
  }
}

static void NopinionReqCheckTn0012_TestVariant(
  NopinionReqCheckTn0012_Context *ctx
)
{
  NopinionReqCheckTn0012_Pre_First_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0012_Pre_Branch_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0012_Pre_Slot_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckTn0012_Pre_Target_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqCheckTn0012_Action( ctx );
  NopinionReqCheckTn0012_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0012( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqCheckTn0012, &NopinionReqCheckTn0012_Fixture )
{
  NopinionReqCheckTn0012_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pci[ 0 ] = NopinionReqCheckTn0012_Pre_First_SetsIcc;
    ctx->Map.pci[ 0 ] < NopinionReqCheckTn0012_Pre_First_NA;
    ++ctx->Map.pci[ 0 ]
  ) {
    for (
      ctx->Map.pci[ 1 ] = NopinionReqCheckTn0012_Pre_Branch_IccAnnul;
      ctx->Map.pci[ 1 ] < NopinionReqCheckTn0012_Pre_Branch_NA;
      ++ctx->Map.pci[ 1 ]
    ) {
      for (
        ctx->Map.pci[ 2 ] = NopinionReqCheckTn0012_Pre_Slot_FPop1;
        ctx->Map.pci[ 2 ] < NopinionReqCheckTn0012_Pre_Slot_NA;
        ++ctx->Map.pci[ 2 ]
      ) {
        for (
          ctx->Map.pci[ 3 ] = NopinionReqCheckTn0012_Pre_Target_FPop1;
          ctx->Map.pci[ 3 ] < NopinionReqCheckTn0012_Pre_Target_NA;
          ++ctx->Map.pci[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqCheckTn0012_PopEntry( ctx );

          if ( ctx->Map.entry.Skip ) {
            continue;
          }

          NopinionReqCheckTn0012_SetPreConditionStates( ctx );
          NopinionReqCheckTn0012_Prepare( ctx );
          NopinionReqCheckTn0012_TestVariant( ctx );
        }
      }
    }
  }
}

/** @} */
