/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqFlowDelaySlot
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
 * @defgroup NopinionReqFlowDelaySlot spec:/nopinion/req/flow-delay-slot
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqFlowDelaySlot_Pre_Instruction_BiccCond,
  NopinionReqFlowDelaySlot_Pre_Instruction_BiccCondAnnul,
  NopinionReqFlowDelaySlot_Pre_Instruction_BiccAlways,
  NopinionReqFlowDelaySlot_Pre_Instruction_BiccAlwaysAnnul,
  NopinionReqFlowDelaySlot_Pre_Instruction_BiccNever,
  NopinionReqFlowDelaySlot_Pre_Instruction_BiccNeverAnnul,
  NopinionReqFlowDelaySlot_Pre_Instruction_FbfccCond,
  NopinionReqFlowDelaySlot_Pre_Instruction_FbfccCondAnnul,
  NopinionReqFlowDelaySlot_Pre_Instruction_CbcccCond,
  NopinionReqFlowDelaySlot_Pre_Instruction_Call,
  NopinionReqFlowDelaySlot_Pre_Instruction_Jmpl,
  NopinionReqFlowDelaySlot_Pre_Instruction_Rett,
  NopinionReqFlowDelaySlot_Pre_Instruction_TrapAlways,
  NopinionReqFlowDelaySlot_Pre_Instruction_TrapCond,
  NopinionReqFlowDelaySlot_Pre_Instruction_Other,
  NopinionReqFlowDelaySlot_Pre_Instruction_NA
} NopinionReqFlowDelaySlot_Pre_Instruction;

typedef enum {
  NopinionReqFlowDelaySlot_Pre_Target_Inside,
  NopinionReqFlowDelaySlot_Pre_Target_Outside,
  NopinionReqFlowDelaySlot_Pre_Target_Relocated,
  NopinionReqFlowDelaySlot_Pre_Target_NA
} NopinionReqFlowDelaySlot_Pre_Target;

typedef enum {
  NopinionReqFlowDelaySlot_Pre_SlotIsTarget_Yes,
  NopinionReqFlowDelaySlot_Pre_SlotIsTarget_No,
  NopinionReqFlowDelaySlot_Pre_SlotIsTarget_NA
} NopinionReqFlowDelaySlot_Pre_SlotIsTarget;

typedef enum {
  NopinionReqFlowDelaySlot_Pre_Indirect_Yes,
  NopinionReqFlowDelaySlot_Pre_Indirect_No,
  NopinionReqFlowDelaySlot_Pre_Indirect_NA
} NopinionReqFlowDelaySlot_Pre_Indirect;

typedef enum {
  NopinionReqFlowDelaySlot_Post_Fall_None,
  NopinionReqFlowDelaySlot_Post_Fall_Definite,
  NopinionReqFlowDelaySlot_Post_Fall_Possible,
  NopinionReqFlowDelaySlot_Post_Fall_NA
} NopinionReqFlowDelaySlot_Post_Fall;

typedef enum {
  NopinionReqFlowDelaySlot_Post_Branch_None,
  NopinionReqFlowDelaySlot_Post_Branch_Definite,
  NopinionReqFlowDelaySlot_Post_Branch_Possible,
  NopinionReqFlowDelaySlot_Post_Branch_NA
} NopinionReqFlowDelaySlot_Post_Branch;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Instruction_NA : 1;
  uint16_t Pre_Target_NA : 1;
  uint16_t Pre_SlotIsTarget_NA : 1;
  uint16_t Pre_Indirect_NA : 1;
  uint16_t Post_Fall : 2;
  uint16_t Post_Branch : 2;
} NopinionReqFlowDelaySlot_Entry;

typedef enum {
  KindBiccCond,
  KindBiccCondAnnul,
  KindBiccAlways,
  KindBiccAlwaysAnnul,
  KindBiccNever,
  KindBiccNeverAnnul,
  KindFbfccCond,
  KindFbfccCondAnnul,
  KindCbcccCond,
  KindCall,
  KindJmpl,
  KindRett,
  KindTrapAlways,
  KindTrapCond,
  KindOther,
} Kind;

/**
 * @brief Test context for spec:/nopinion/req/flow-delay-slot test case.
 */
typedef struct {
  /**
   * @brief This member specifies the kind of the instruction.
   */
  int kind;

  /**
   * @brief This member specifies the displacement of a PC-relative
   *   instruction.
   */
  int32_t disp;

  /**
   * @brief This member is true, if a relocation applies to the instruction.
   */
  bool relocated;

  /**
   * @brief This member is true, if the delay slot is the target of another
   *   branch.
   */
  bool slot_is_target;

  /**
   * @brief This member contains the finding with the store after the delay
   *   slot.
   */
  TxFlowFinding fall;

  /**
   * @brief This member contains the finding with the store at the target.
   */
  TxFlowFinding branch;

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
    NopinionReqFlowDelaySlot_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqFlowDelaySlot_Context;

static NopinionReqFlowDelaySlot_Context NopinionReqFlowDelaySlot_Instance;

static const char *const NopinionReqFlowDelaySlot_PreDesc_Instruction[] = {
  "BiccCond",
  "BiccCondAnnul",
  "BiccAlways",
  "BiccAlwaysAnnul",
  "BiccNever",
  "BiccNeverAnnul",
  "FbfccCond",
  "FbfccCondAnnul",
  "CbcccCond",
  "Call",
  "Jmpl",
  "Rett",
  "TrapAlways",
  "TrapCond",
  "Other",
  "NA"
};

static const char *const NopinionReqFlowDelaySlot_PreDesc_Target[] =
  { "Inside", "Outside", "Relocated", "NA" };

static const char *const NopinionReqFlowDelaySlot_PreDesc_SlotIsTarget[] =
  { "Yes", "No", "NA" };

static const char *const NopinionReqFlowDelaySlot_PreDesc_Indirect[] =
  { "Yes", "No", "NA" };

static const char *const *const NopinionReqFlowDelaySlot_PreDesc[] = {
  NopinionReqFlowDelaySlot_PreDesc_Instruction,
  NopinionReqFlowDelaySlot_PreDesc_Target,
  NopinionReqFlowDelaySlot_PreDesc_SlotIsTarget,
  NopinionReqFlowDelaySlot_PreDesc_Indirect,
  NULL
};

static void NopinionReqFlowDelaySlot_Pre_Instruction_Prepare(
  NopinionReqFlowDelaySlot_Context        *ctx,
  NopinionReqFlowDelaySlot_Pre_Instruction state
)
{
  switch ( state ) {
    case NopinionReqFlowDelaySlot_Pre_Instruction_BiccCond: {
      /*
       * While the instruction is a conditional branch on integer condition
       * codes with the annul bit cleared.
       */
      ctx->kind = KindBiccCond;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_BiccCondAnnul: {
      /*
       * While the instruction is a conditional branch on integer condition
       * codes with the annul bit set.
       */
      ctx->kind = KindBiccCondAnnul;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_BiccAlways: {
      /*
       * While the instruction is a branch always on integer condition codes
       * with the annul bit cleared.
       */
      ctx->kind = KindBiccAlways;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_BiccAlwaysAnnul: {
      /*
       * While the instruction is a branch always on integer condition codes
       * with the annul bit set.
       */
      ctx->kind = KindBiccAlwaysAnnul;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_BiccNever: {
      /*
       * While the instruction is a branch never on integer condition codes
       * with the annul bit cleared.
       */
      ctx->kind = KindBiccNever;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_BiccNeverAnnul: {
      /*
       * While the instruction is a branch never on integer condition codes
       * with the annul bit set.
       */
      ctx->kind = KindBiccNeverAnnul;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_FbfccCond: {
      /*
       * While the instruction is a conditional branch on floating-point
       * condition codes with the annul bit cleared.
       */
      ctx->kind = KindFbfccCond;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_FbfccCondAnnul: {
      /*
       * While the instruction is a conditional branch on floating-point
       * condition codes with the annul bit set.
       */
      ctx->kind = KindFbfccCondAnnul;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_CbcccCond: {
      /*
       * While the instruction is a conditional branch on coprocessor condition
       * codes with the annul bit cleared.
       */
      ctx->kind = KindCbcccCond;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_Call: {
      /*
       * While the instruction is a CALL instruction.
       */
      ctx->kind = KindCall;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_Jmpl: {
      /*
       * While the instruction is a JMPL instruction.
       */
      ctx->kind = KindJmpl;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_Rett: {
      /*
       * While the instruction is an RETT instruction.
       */
      ctx->kind = KindRett;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_TrapAlways: {
      /*
       * While the instruction is a trap always instruction.
       */
      ctx->kind = KindTrapAlways;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_TrapCond: {
      /*
       * While the instruction is a conditional trap instruction.
       */
      ctx->kind = KindTrapCond;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_Other: {
      /*
       * While the instruction is an instruction which transfers no control.
       */
      ctx->kind = KindOther;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Instruction_NA:
      break;
  }
}

static void NopinionReqFlowDelaySlot_Pre_Target_Prepare(
  NopinionReqFlowDelaySlot_Context   *ctx,
  NopinionReqFlowDelaySlot_Pre_Target state
)
{
  switch ( state ) {
    case NopinionReqFlowDelaySlot_Pre_Target_Inside: {
      /*
       * While the PC-relative target of the instruction is in the code
       * section.
       */
      ctx->disp = 4;
      ctx->relocated = false;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Target_Outside: {
      /*
       * While the PC-relative target of the instruction is outside the code
       * section.
       */
      ctx->disp = 100;
      ctx->relocated = false;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Target_Relocated: {
      /*
       * While a relocation applies to the instruction.
       */
      ctx->disp = 4;
      ctx->relocated = true;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Target_NA:
      break;
  }
}

static void NopinionReqFlowDelaySlot_Pre_SlotIsTarget_Prepare(
  NopinionReqFlowDelaySlot_Context         *ctx,
  NopinionReqFlowDelaySlot_Pre_SlotIsTarget state
)
{
  switch ( state ) {
    case NopinionReqFlowDelaySlot_Pre_SlotIsTarget_Yes: {
      /*
       * While the delay slot is the target of another branch.
       */
      ctx->slot_is_target = true;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_SlotIsTarget_No: {
      /*
       * While the delay slot is the target of no other branch.
       */
      ctx->slot_is_target = false;
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_SlotIsTarget_NA:
      break;
  }
}

static void NopinionReqFlowDelaySlot_Pre_Indirect_Prepare(
  NopinionReqFlowDelaySlot_Pre_Indirect state
)
{
  switch ( state ) {
    case NopinionReqFlowDelaySlot_Pre_Indirect_Yes: {
      /*
       * While the option -i is given.
       */
      TxSetIncludeIndirect( true );
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Indirect_No: {
      /*
       * While the option -i is not given.
       */
      TxSetIncludeIndirect( false );
      break;
    }

    case NopinionReqFlowDelaySlot_Pre_Indirect_NA:
      break;
  }
}

static void NopinionReqFlowDelaySlot_Post_Fall_Check(
  NopinionReqFlowDelaySlot_Context  *ctx,
  NopinionReqFlowDelaySlot_Post_Fall state
)
{
  switch ( state ) {
    case NopinionReqFlowDelaySlot_Post_Fall_None: {
      /*
       * The errata checker shall report no finding for the store of double
       * word size in the fall-through probe.
       */
      T_eq_int( ctx->fall, TX_FLOW_NONE );
      break;
    }

    case NopinionReqFlowDelaySlot_Post_Fall_Definite: {
      /*
       * The errata checker shall report one definite finding for the store of
       * double word size in the fall-through probe.
       */
      T_eq_int( ctx->fall, TX_FLOW_DEFINITE );
      break;
    }

    case NopinionReqFlowDelaySlot_Post_Fall_Possible: {
      /*
       * The errata checker shall report one possible finding for the store of
       * double word size in the fall-through probe.
       */
      T_eq_int( ctx->fall, TX_FLOW_POSSIBLE );
      break;
    }

    case NopinionReqFlowDelaySlot_Post_Fall_NA:
      break;
  }
}

static void NopinionReqFlowDelaySlot_Post_Branch_Check(
  NopinionReqFlowDelaySlot_Context    *ctx,
  NopinionReqFlowDelaySlot_Post_Branch state
)
{
  switch ( state ) {
    case NopinionReqFlowDelaySlot_Post_Branch_None: {
      /*
       * The errata checker shall report no finding for the store of double
       * word size in the target probe.
       */
      T_eq_int( ctx->branch, TX_FLOW_NONE );
      break;
    }

    case NopinionReqFlowDelaySlot_Post_Branch_Definite: {
      /*
       * The errata checker shall report one definite finding for the store of
       * double word size in the target probe.
       */
      T_eq_int( ctx->branch, TX_FLOW_DEFINITE );
      break;
    }

    case NopinionReqFlowDelaySlot_Post_Branch_Possible: {
      /*
       * The errata checker shall report one possible finding for the store of
       * double word size in the target probe.
       */
      T_eq_int( ctx->branch, TX_FLOW_POSSIBLE );
      break;
    }

    case NopinionReqFlowDelaySlot_Post_Branch_NA:
      break;
  }
}

static void NopinionReqFlowDelaySlot_Action(
  NopinionReqFlowDelaySlot_Context *ctx
)
{
  uint32_t x;
  int32_t  disp = ctx->disp;

  switch ( ctx->kind ) {
    case KindBiccCond:
      x = TxBicc( 9, false, disp );
      break;
    case KindBiccCondAnnul:
      x = TxBicc( 9, true, disp );
      break;
    case KindBiccAlways:
      x = TxBicc( 8, false, disp );
      break;
    case KindBiccAlwaysAnnul:
      x = TxBicc( 8, true, disp );
      break;
    case KindBiccNever:
      x = TxBicc( 0, false, disp );
      break;
    case KindBiccNeverAnnul:
      x = TxBicc( 0, true, disp );
      break;
    case KindFbfccCond:
      x = TxFbfcc( false, disp );
      break;
    case KindFbfccCondAnnul:
      x = TxFbfcc( true, disp );
      break;
    case KindCbcccCond:
      x = TxCbccc( disp );
      break;
    case KindCall:
      x = TxCall( disp );
      break;
    case KindJmpl:
      x = TxJmpl();
      break;
    case KindRett:
      x = TxRett();
      break;
    case KindTrapAlways:
      x = TxTa();
      break;
    case KindTrapCond:
      x = TxFormat3Imm( 2, 0x3a, 9, TX_G0, 0 );
      break;
    case KindOther:
      x = TxAdd();
      break;
    default:
      x = TxAdd();
      break;
  }

  (void) disp;
  ctx->fall = TxProbeFlow( x, ctx->relocated, ctx->slot_is_target, true );
  ctx->branch = TxProbeFlow( x, ctx->relocated, ctx->slot_is_target, false );
}

static void NopinionReqFlowDelaySlot_Cleanup( void )
{
  TxSetIncludeIndirect( false );
}

/* clang-format off */

static const NopinionReqFlowDelaySlot_Entry
NopinionReqFlowDelaySlot_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqFlowDelaySlot_Post_Fall_Definite,
    NopinionReqFlowDelaySlot_Post_Branch_None },
  { 0, 0, 0, 0, 0, NopinionReqFlowDelaySlot_Post_Fall_Definite,
    NopinionReqFlowDelaySlot_Post_Branch_Possible },
  { 0, 0, 0, 0, 0, NopinionReqFlowDelaySlot_Post_Fall_Possible,
    NopinionReqFlowDelaySlot_Post_Branch_Possible },
  { 0, 0, 0, 0, 0, NopinionReqFlowDelaySlot_Post_Fall_Definite,
    NopinionReqFlowDelaySlot_Post_Branch_Definite },
  { 0, 0, 0, 0, 0, NopinionReqFlowDelaySlot_Post_Fall_None,
    NopinionReqFlowDelaySlot_Post_Branch_None },
  { 0, 0, 0, 0, 0, NopinionReqFlowDelaySlot_Post_Fall_None,
    NopinionReqFlowDelaySlot_Post_Branch_Definite }
};

static const uint8_t
NopinionReqFlowDelaySlot_Map[] = {
  3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 5, 5, 1, 1, 2, 2, 1, 1, 2, 2, 3, 3,
  5, 5, 1, 1, 2, 2, 1, 1, 2, 2, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4, 0, 0, 4, 4, 3, 3, 3, 3, 1, 1,
  1, 1, 1, 1, 1, 1, 3, 3, 5, 5, 1, 1, 2, 2, 1, 1, 2, 2, 3, 3, 3, 3, 1, 1, 1, 1,
  1, 1, 1, 1, 3, 3, 5, 5, 1, 1, 2, 2, 1, 1, 2, 2, 1, 0, 2, 4, 1, 0, 2, 4, 1, 0,
  2, 4, 1, 0, 2, 4, 1, 0, 2, 4, 1, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqFlowDelaySlot_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqFlowDelaySlot_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqFlowDelaySlot_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqFlowDelaySlot_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqFlowDelaySlot_Scope,
  .initial_context = &NopinionReqFlowDelaySlot_Instance
};

static inline NopinionReqFlowDelaySlot_Entry NopinionReqFlowDelaySlot_PopEntry(
  NopinionReqFlowDelaySlot_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqFlowDelaySlot_Entries
    [ NopinionReqFlowDelaySlot_Map[ index ] ];
}

static void NopinionReqFlowDelaySlot_TestVariant(
  NopinionReqFlowDelaySlot_Context *ctx
)
{
  NopinionReqFlowDelaySlot_Pre_Instruction_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqFlowDelaySlot_Pre_Target_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqFlowDelaySlot_Pre_SlotIsTarget_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqFlowDelaySlot_Pre_Indirect_Prepare( ctx->Map.pcs[ 3 ] );
  NopinionReqFlowDelaySlot_Action( ctx );
  NopinionReqFlowDelaySlot_Post_Fall_Check( ctx, ctx->Map.entry.Post_Fall );
  NopinionReqFlowDelaySlot_Post_Branch_Check(
    ctx,
    ctx->Map.entry.Post_Branch
  );
}

/**
 * @fn void T_case_body_NopinionReqFlowDelaySlot( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqFlowDelaySlot,
  &NopinionReqFlowDelaySlot_Fixture
)
{
  NopinionReqFlowDelaySlot_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqFlowDelaySlot_Pre_Instruction_BiccCond;
    ctx->Map.pcs[ 0 ] < NopinionReqFlowDelaySlot_Pre_Instruction_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqFlowDelaySlot_Pre_Target_Inside;
      ctx->Map.pcs[ 1 ] < NopinionReqFlowDelaySlot_Pre_Target_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqFlowDelaySlot_Pre_SlotIsTarget_Yes;
        ctx->Map.pcs[ 2 ] < NopinionReqFlowDelaySlot_Pre_SlotIsTarget_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        for (
          ctx->Map.pcs[ 3 ] = NopinionReqFlowDelaySlot_Pre_Indirect_Yes;
          ctx->Map.pcs[ 3 ] < NopinionReqFlowDelaySlot_Pre_Indirect_NA;
          ++ctx->Map.pcs[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqFlowDelaySlot_PopEntry( ctx );
          NopinionReqFlowDelaySlot_TestVariant( ctx );
          NopinionReqFlowDelaySlot_Cleanup();
        }
      }
    }
  }
}

/** @} */
