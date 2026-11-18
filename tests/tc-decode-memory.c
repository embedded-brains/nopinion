/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqDecodeMemory
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
 * @defgroup NopinionReqDecodeMemory spec:/nopinion/req/decode-memory
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqDecodeMemory_Pre_Instruction_Ld,
  NopinionReqDecodeMemory_Pre_Instruction_Ldub,
  NopinionReqDecodeMemory_Pre_Instruction_Lduh,
  NopinionReqDecodeMemory_Pre_Instruction_Ldd,
  NopinionReqDecodeMemory_Pre_Instruction_St,
  NopinionReqDecodeMemory_Pre_Instruction_Stb,
  NopinionReqDecodeMemory_Pre_Instruction_Sth,
  NopinionReqDecodeMemory_Pre_Instruction_Std,
  NopinionReqDecodeMemory_Pre_Instruction_Ldsb,
  NopinionReqDecodeMemory_Pre_Instruction_Ldsh,
  NopinionReqDecodeMemory_Pre_Instruction_Ldstub,
  NopinionReqDecodeMemory_Pre_Instruction_Swap,
  NopinionReqDecodeMemory_Pre_Instruction_Lda,
  NopinionReqDecodeMemory_Pre_Instruction_Lduba,
  NopinionReqDecodeMemory_Pre_Instruction_Lduha,
  NopinionReqDecodeMemory_Pre_Instruction_Ldda,
  NopinionReqDecodeMemory_Pre_Instruction_Sta,
  NopinionReqDecodeMemory_Pre_Instruction_Stba,
  NopinionReqDecodeMemory_Pre_Instruction_Stha,
  NopinionReqDecodeMemory_Pre_Instruction_Stda,
  NopinionReqDecodeMemory_Pre_Instruction_Ldsba,
  NopinionReqDecodeMemory_Pre_Instruction_Ldsha,
  NopinionReqDecodeMemory_Pre_Instruction_Ldstuba,
  NopinionReqDecodeMemory_Pre_Instruction_Swapa,
  NopinionReqDecodeMemory_Pre_Instruction_Ldf,
  NopinionReqDecodeMemory_Pre_Instruction_Ldfsr,
  NopinionReqDecodeMemory_Pre_Instruction_Lddf,
  NopinionReqDecodeMemory_Pre_Instruction_Stf,
  NopinionReqDecodeMemory_Pre_Instruction_Stfsr,
  NopinionReqDecodeMemory_Pre_Instruction_Stdfq,
  NopinionReqDecodeMemory_Pre_Instruction_Stdf,
  NopinionReqDecodeMemory_Pre_Instruction_Ldc,
  NopinionReqDecodeMemory_Pre_Instruction_Ldcsr,
  NopinionReqDecodeMemory_Pre_Instruction_Lddc,
  NopinionReqDecodeMemory_Pre_Instruction_Stc,
  NopinionReqDecodeMemory_Pre_Instruction_Stcsr,
  NopinionReqDecodeMemory_Pre_Instruction_Stdcq,
  NopinionReqDecodeMemory_Pre_Instruction_Stdc,
  NopinionReqDecodeMemory_Pre_Instruction_Casa,
  NopinionReqDecodeMemory_Pre_Instruction_Undefined,
  NopinionReqDecodeMemory_Pre_Instruction_NA
} NopinionReqDecodeMemory_Pre_Instruction;

typedef enum {
  NopinionReqDecodeMemory_Post_Class_StoreWord,
  NopinionReqDecodeMemory_Post_Class_StoreDouble,
  NopinionReqDecodeMemory_Post_Class_Atomic,
  NopinionReqDecodeMemory_Post_Class_Load,
  NopinionReqDecodeMemory_Post_Class_NA
} NopinionReqDecodeMemory_Post_Class;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Instruction_NA : 1;
  uint8_t Post_Class : 3;
} NopinionReqDecodeMemory_Entry;

/**
 * @brief Test context for spec:/nopinion/req/decode-memory test case.
 */
typedef struct {
  /**
   * @brief This member contains the instruction.
   */
  uint32_t instruction;

  /**
   * @brief This member contains the result of the probe of the instruction.
   */
  TxMemoryProbe probe;

  struct {
    /**
     * @brief This member defines the pre-condition states for the next action.
     */
    size_t pcs[ 1 ];

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
    NopinionReqDecodeMemory_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqDecodeMemory_Context;

static NopinionReqDecodeMemory_Context NopinionReqDecodeMemory_Instance;

static const char *const NopinionReqDecodeMemory_PreDesc_Instruction[] = {
  "Ld",
  "Ldub",
  "Lduh",
  "Ldd",
  "St",
  "Stb",
  "Sth",
  "Std",
  "Ldsb",
  "Ldsh",
  "Ldstub",
  "Swap",
  "Lda",
  "Lduba",
  "Lduha",
  "Ldda",
  "Sta",
  "Stba",
  "Stha",
  "Stda",
  "Ldsba",
  "Ldsha",
  "Ldstuba",
  "Swapa",
  "Ldf",
  "Ldfsr",
  "Lddf",
  "Stf",
  "Stfsr",
  "Stdfq",
  "Stdf",
  "Ldc",
  "Ldcsr",
  "Lddc",
  "Stc",
  "Stcsr",
  "Stdcq",
  "Stdc",
  "Casa",
  "Undefined",
  "NA"
};

static const char *const *const NopinionReqDecodeMemory_PreDesc[] = {
  NopinionReqDecodeMemory_PreDesc_Instruction,
  NULL
};

static void NopinionReqDecodeMemory_Pre_Instruction_Prepare(
  NopinionReqDecodeMemory_Context        *ctx,
  NopinionReqDecodeMemory_Pre_Instruction state
)
{
  switch ( state ) {
    case NopinionReqDecodeMemory_Pre_Instruction_Ld: {
      /*
       * While the instruction is an LD instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x00, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldub: {
      /*
       * While the instruction is an LDUB instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x01, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Lduh: {
      /*
       * While the instruction is an LDUH instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x02, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldd: {
      /*
       * While the instruction is an LDD instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x03, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_St: {
      /*
       * While the instruction is an ST instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x04, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stb: {
      /*
       * While the instruction is an STB instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x05, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Sth: {
      /*
       * While the instruction is an STH instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x06, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Std: {
      /*
       * While the instruction is an STD instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x07, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldsb: {
      /*
       * While the instruction is an LDSB instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x09, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldsh: {
      /*
       * While the instruction is an LDSH instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x0a, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldstub: {
      /*
       * While the instruction is an LDSTUB instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x0d, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Swap: {
      /*
       * While the instruction is an SWAP instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x0f, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Lda: {
      /*
       * While the instruction is an LDA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x10, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Lduba: {
      /*
       * While the instruction is an LDUBA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x11, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Lduha: {
      /*
       * While the instruction is an LDUHA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x12, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldda: {
      /*
       * While the instruction is an LDDA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x13, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Sta: {
      /*
       * While the instruction is an STA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x14, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stba: {
      /*
       * While the instruction is an STBA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x15, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stha: {
      /*
       * While the instruction is an STHA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x16, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stda: {
      /*
       * While the instruction is an STDA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x17, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldsba: {
      /*
       * While the instruction is an LDSBA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x19, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldsha: {
      /*
       * While the instruction is an LDSHA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x1a, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldstuba: {
      /*
       * While the instruction is an LDSTUBA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x1d, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Swapa: {
      /*
       * While the instruction is an SWAPA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x1f, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldf: {
      /*
       * While the instruction is an LDF instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x20, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldfsr: {
      /*
       * While the instruction is an LDFSR instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x21, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Lddf: {
      /*
       * While the instruction is an LDDF instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x23, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stf: {
      /*
       * While the instruction is an STF instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x24, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stfsr: {
      /*
       * While the instruction is an STFSR instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x25, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stdfq: {
      /*
       * While the instruction is an STDFQ instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x26, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stdf: {
      /*
       * While the instruction is an STDF instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x27, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldc: {
      /*
       * While the instruction is an LDC instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x30, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Ldcsr: {
      /*
       * While the instruction is an LDCSR instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x31, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Lddc: {
      /*
       * While the instruction is an LDDC instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x33, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stc: {
      /*
       * While the instruction is an STC instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x34, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stcsr: {
      /*
       * While the instruction is an STCSR instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x35, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stdcq: {
      /*
       * While the instruction is an STDCQ instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x36, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Stdc: {
      /*
       * While the instruction is an STDC instruction.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x37, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Casa: {
      /*
       * While the instruction is a CASA instruction.
       */
      ctx->instruction = TxFormat3Asi( 3, 0x3c, TX_G1, TX_O0, 10, TX_O1 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_Undefined: {
      /*
       * While the instruction is a memory instruction with an undefined op3
       * field.
       */
      ctx->instruction = TxFormat3Reg( 3, 0x08, TX_G1, TX_O0, TX_G0 );
      break;
    }

    case NopinionReqDecodeMemory_Pre_Instruction_NA:
      break;
  }
}

static void NopinionReqDecodeMemory_Post_Class_Check(
  NopinionReqDecodeMemory_Context   *ctx,
  NopinionReqDecodeMemory_Post_Class state
)
{
  switch ( state ) {
    case NopinionReqDecodeMemory_Post_Class_StoreWord: {
      /*
       * The errata checker shall classify the instruction as a store of word
       * size or less.
       */
      T_true( ctx->probe.sequence_a );
      T_false( ctx->probe.sequence_b );
      T_false( ctx->probe.middle );
      T_false( ctx->probe.in_delay_slot );
      break;
    }

    case NopinionReqDecodeMemory_Post_Class_StoreDouble: {
      /*
       * The errata checker shall classify the instruction as a store of double
       * word size.
       */
      T_false( ctx->probe.sequence_a );
      T_true( ctx->probe.sequence_b );
      T_false( ctx->probe.middle );
      T_false( ctx->probe.in_delay_slot );
      break;
    }

    case NopinionReqDecodeMemory_Post_Class_Atomic: {
      /*
       * The errata checker shall classify the instruction as an atomic
       * load-store instruction.
       */
      T_false( ctx->probe.sequence_a );
      T_false( ctx->probe.sequence_b );
      T_false( ctx->probe.middle );
      T_true( ctx->probe.in_delay_slot );
      break;
    }

    case NopinionReqDecodeMemory_Post_Class_Load: {
      /*
       * The errata checker shall classify the instruction as a load which is
       * no atomic load-store instruction.
       */
      T_false( ctx->probe.sequence_a );
      T_false( ctx->probe.sequence_b );
      T_false( ctx->probe.middle );
      T_false( ctx->probe.in_delay_slot );
      break;
    }

    case NopinionReqDecodeMemory_Post_Class_NA:
      break;
  }
}

static void NopinionReqDecodeMemory_Action(
  NopinionReqDecodeMemory_Context *ctx
)
{
  TxProbeMemory( ctx->instruction, &ctx->probe );
}

/* clang-format off */

static const NopinionReqDecodeMemory_Entry
NopinionReqDecodeMemory_Entries[] = {
  { 0, 0, NopinionReqDecodeMemory_Post_Class_Load },
  { 0, 0, NopinionReqDecodeMemory_Post_Class_StoreWord },
  { 0, 0, NopinionReqDecodeMemory_Post_Class_StoreDouble },
  { 0, 0, NopinionReqDecodeMemory_Post_Class_Atomic }
};

static const uint8_t
NopinionReqDecodeMemory_Map[] = {
  0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 3, 3, 0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 3, 3, 0, 0,
  0, 1, 1, 2, 2, 0, 0, 0, 1, 1, 2, 2, 3, 0
};

/* clang-format on */

static size_t NopinionReqDecodeMemory_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqDecodeMemory_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqDecodeMemory_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqDecodeMemory_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqDecodeMemory_Scope,
  .initial_context = &NopinionReqDecodeMemory_Instance
};

static inline NopinionReqDecodeMemory_Entry NopinionReqDecodeMemory_PopEntry(
  NopinionReqDecodeMemory_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqDecodeMemory_Entries
    [ NopinionReqDecodeMemory_Map[ index ] ];
}

static void NopinionReqDecodeMemory_TestVariant(
  NopinionReqDecodeMemory_Context *ctx
)
{
  NopinionReqDecodeMemory_Pre_Instruction_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqDecodeMemory_Action( ctx );
  NopinionReqDecodeMemory_Post_Class_Check( ctx, ctx->Map.entry.Post_Class );
}

/**
 * @fn void T_case_body_NopinionReqDecodeMemory( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqDecodeMemory,
  &NopinionReqDecodeMemory_Fixture
)
{
  NopinionReqDecodeMemory_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqDecodeMemory_Pre_Instruction_Ld;
    ctx->Map.pcs[ 0 ] < NopinionReqDecodeMemory_Pre_Instruction_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    ctx->Map.entry = NopinionReqDecodeMemory_PopEntry( ctx );
    NopinionReqDecodeMemory_TestVariant( ctx );
  }
}

/** @} */
