/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckAsi0x1c
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
 * @defgroup NopinionReqCheckAsi0x1c spec:/nopinion/req/check-asi-0x1c
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckAsi0x1c_Pre_Instruction_Sta,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Stba,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Stha,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Stda,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Ldstuba,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Swapa,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Casa,
  NopinionReqCheckAsi0x1c_Pre_Instruction_Lda,
  NopinionReqCheckAsi0x1c_Pre_Instruction_St,
  NopinionReqCheckAsi0x1c_Pre_Instruction_NA
} NopinionReqCheckAsi0x1c_Pre_Instruction;

typedef enum {
  NopinionReqCheckAsi0x1c_Pre_Asi_Bypass,
  NopinionReqCheckAsi0x1c_Pre_Asi_Other,
  NopinionReqCheckAsi0x1c_Pre_Asi_Immediate,
  NopinionReqCheckAsi0x1c_Pre_Asi_NA
} NopinionReqCheckAsi0x1c_Pre_Asi;

typedef enum {
  NopinionReqCheckAsi0x1c_Post_Kind_None,
  NopinionReqCheckAsi0x1c_Post_Kind_Store,
  NopinionReqCheckAsi0x1c_Post_Kind_Atomic,
  NopinionReqCheckAsi0x1c_Post_Kind_NA
} NopinionReqCheckAsi0x1c_Post_Kind;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Instruction_NA : 1;
  uint8_t Pre_Asi_NA : 1;
  uint8_t Post_Kind : 2;
} NopinionReqCheckAsi0x1c_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-asi-0x1c test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the field op3 of the instruction.
   */
  uint32_t op3;

  /**
   * @brief This member contains the field rd of the instruction.
   */
  uint32_t rd;

  /**
   * @brief This member contains the field rs2 of the instruction.
   */
  uint32_t rs2;

  /**
   * @brief This member contains the instruction.
   */
  uint32_t instruction;

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
    NopinionReqCheckAsi0x1c_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckAsi0x1c_Context;

static NopinionReqCheckAsi0x1c_Context NopinionReqCheckAsi0x1c_Instance;

static const char *const NopinionReqCheckAsi0x1c_PreDesc_Instruction[] = {
  "Sta",
  "Stba",
  "Stha",
  "Stda",
  "Ldstuba",
  "Swapa",
  "Casa",
  "Lda",
  "St",
  "NA"
};

static const char *const NopinionReqCheckAsi0x1c_PreDesc_Asi[] =
  { "Bypass", "Other", "Immediate", "NA" };

static const char *const *const NopinionReqCheckAsi0x1c_PreDesc[] = {
  NopinionReqCheckAsi0x1c_PreDesc_Instruction,
  NopinionReqCheckAsi0x1c_PreDesc_Asi,
  NULL
};

static void NopinionReqCheckAsi0x1c_Pre_Instruction_Prepare(
  NopinionReqCheckAsi0x1c_Context        *ctx,
  NopinionReqCheckAsi0x1c_Pre_Instruction state
)
{
  switch ( state ) {
    case NopinionReqCheckAsi0x1c_Pre_Instruction_Sta: {
      /*
       * While the instruction is an STA instruction.
       */
      ctx->op3 = 0x14;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Stba: {
      /*
       * While the instruction is an STBA instruction.
       */
      ctx->op3 = 0x15;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Stha: {
      /*
       * While the instruction is an STHA instruction.
       */
      ctx->op3 = 0x16;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Stda: {
      /*
       * While the instruction is an STDA instruction.
       */
      ctx->op3 = 0x17;
      ctx->rd = TX_L2;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Ldstuba: {
      /*
       * While the instruction is an LDSTUBA instruction.
       */
      ctx->op3 = 0x1d;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Swapa: {
      /*
       * While the instruction is a SWAPA instruction.
       */
      ctx->op3 = 0x1f;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Casa: {
      /*
       * While the instruction is a CASA instruction.
       */
      ctx->op3 = 0x3c;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_O1;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_Lda: {
      /*
       * While the instruction is an LDA instruction.
       */
      ctx->op3 = 0x10;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_St: {
      /*
       * While the instruction is an ST instruction.
       */
      ctx->op3 = 0x04;
      ctx->rd = TX_G1;
      ctx->rs2 = TX_G0;
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Instruction_NA:
      break;
  }
}

static void NopinionReqCheckAsi0x1c_Pre_Asi_Prepare(
  NopinionReqCheckAsi0x1c_Context *ctx,
  NopinionReqCheckAsi0x1c_Pre_Asi  state
)
{
  switch ( state ) {
    case NopinionReqCheckAsi0x1c_Pre_Asi_Bypass: {
      /*
       * While the field i of the instruction is 0, while the field asi of the
       * instruction is 0x1C.
       */
      ctx->instruction =
        TxFormat3Asi( 3, ctx->op3, ctx->rd, TX_O0, 0x1c, ctx->rs2 );
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Asi_Other: {
      /*
       * While the field i of the instruction is 0, while the field asi of the
       * instruction is 0x0B.
       */
      ctx->instruction =
        TxFormat3Asi( 3, ctx->op3, ctx->rd, TX_O0, 0x0b, ctx->rs2 );
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Asi_Immediate: {
      /*
       * While the field i of the instruction is 1, while bits 12 to 5 of the
       * instruction hold 0x1C.
       */
      ctx->instruction = TxFormat3Imm(
        3,
        ctx->op3,
        ctx->rd,
        TX_O0,
        0x1c << 5
      );
      break;
    }

    case NopinionReqCheckAsi0x1c_Pre_Asi_NA:
      break;
  }
}

static void NopinionReqCheckAsi0x1c_Post_Kind_Check(
  NopinionReqCheckAsi0x1c_Context  *ctx,
  NopinionReqCheckAsi0x1c_Post_Kind state
)
{
  switch ( state ) {
    case NopinionReqCheckAsi0x1c_Post_Kind_None: {
      /*
       * The errata checker shall report no finding of a store with the address
       * space identifier 0x1C.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "GR712RC-19" ), 0 );
      break;
    }

    case NopinionReqCheckAsi0x1c_Post_Kind_Store: {
      /*
       * The errata checker shall report one definite finding of a store
       * instruction with the address space identifier 0x1C for the
       * instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "GR712RC-19" ), 1 );
      T_eq_int( TxCountAt( ctx->report, 0, "store-asi-0x1c" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "store-asi-0x1c" ) );
      break;
    }

    case NopinionReqCheckAsi0x1c_Post_Kind_Atomic: {
      /*
       * The errata checker shall report one definite finding of an atomic
       * load-store instruction with the address space identifier 0x1C for the
       * instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "GR712RC-19" ), 1 );
      T_eq_int( TxCountAt( ctx->report, 0, "atomic-asi-0x1c" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "atomic-asi-0x1c" ) );
      break;
    }

    case NopinionReqCheckAsi0x1c_Post_Kind_NA:
      break;
  }
}

static void NopinionReqCheckAsi0x1c_Prepare(
  NopinionReqCheckAsi0x1c_Context *ctx
)
{
  TxImageInit( &ctx->image );
}

static void NopinionReqCheckAsi0x1c_Action(
  NopinionReqCheckAsi0x1c_Context *ctx
)
{
  TxAppend( &ctx->image, ctx->instruction );
  ctx->report = TxCheck( &ctx->image, NOTE_ASI_1C );
}

/* clang-format off */

static const NopinionReqCheckAsi0x1c_Entry
NopinionReqCheckAsi0x1c_Entries[] = {
  { 0, 0, 0, NopinionReqCheckAsi0x1c_Post_Kind_None },
  { 0, 0, 0, NopinionReqCheckAsi0x1c_Post_Kind_Store },
  { 0, 0, 0, NopinionReqCheckAsi0x1c_Post_Kind_Atomic }
};

static const uint8_t
NopinionReqCheckAsi0x1c_Map[] = {
  1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
  0
};

/* clang-format on */

static size_t NopinionReqCheckAsi0x1c_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCheckAsi0x1c_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckAsi0x1c_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckAsi0x1c_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckAsi0x1c_Scope,
  .initial_context = &NopinionReqCheckAsi0x1c_Instance
};

static inline NopinionReqCheckAsi0x1c_Entry NopinionReqCheckAsi0x1c_PopEntry(
  NopinionReqCheckAsi0x1c_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckAsi0x1c_Entries
    [ NopinionReqCheckAsi0x1c_Map[ index ] ];
}

static void NopinionReqCheckAsi0x1c_TestVariant(
  NopinionReqCheckAsi0x1c_Context *ctx
)
{
  NopinionReqCheckAsi0x1c_Pre_Instruction_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckAsi0x1c_Pre_Asi_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckAsi0x1c_Action( ctx );
  NopinionReqCheckAsi0x1c_Post_Kind_Check( ctx, ctx->Map.entry.Post_Kind );
}

/**
 * @fn void T_case_body_NopinionReqCheckAsi0x1c( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckAsi0x1c,
  &NopinionReqCheckAsi0x1c_Fixture
)
{
  NopinionReqCheckAsi0x1c_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCheckAsi0x1c_Pre_Instruction_Sta;
    ctx->Map.pcs[ 0 ] < NopinionReqCheckAsi0x1c_Pre_Instruction_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCheckAsi0x1c_Pre_Asi_Bypass;
      ctx->Map.pcs[ 1 ] < NopinionReqCheckAsi0x1c_Pre_Asi_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      ctx->Map.entry = NopinionReqCheckAsi0x1c_PopEntry( ctx );
      NopinionReqCheckAsi0x1c_Prepare( ctx );
      NopinionReqCheckAsi0x1c_TestVariant( ctx );
    }
  }
}

/** @} */
