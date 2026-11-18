/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqDecodeIcc
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
 * @defgroup NopinionReqDecodeIcc spec:/nopinion/req/decode-icc
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqDecodeIcc_Pre_Instruction_Add,
  NopinionReqDecodeIcc_Pre_Instruction_And,
  NopinionReqDecodeIcc_Pre_Instruction_Or,
  NopinionReqDecodeIcc_Pre_Instruction_Xor,
  NopinionReqDecodeIcc_Pre_Instruction_Sub,
  NopinionReqDecodeIcc_Pre_Instruction_Andn,
  NopinionReqDecodeIcc_Pre_Instruction_Orn,
  NopinionReqDecodeIcc_Pre_Instruction_Xnor,
  NopinionReqDecodeIcc_Pre_Instruction_Addx,
  NopinionReqDecodeIcc_Pre_Instruction_Umul,
  NopinionReqDecodeIcc_Pre_Instruction_Smul,
  NopinionReqDecodeIcc_Pre_Instruction_Subx,
  NopinionReqDecodeIcc_Pre_Instruction_Udiv,
  NopinionReqDecodeIcc_Pre_Instruction_Sdiv,
  NopinionReqDecodeIcc_Pre_Instruction_Addcc,
  NopinionReqDecodeIcc_Pre_Instruction_Andcc,
  NopinionReqDecodeIcc_Pre_Instruction_Orcc,
  NopinionReqDecodeIcc_Pre_Instruction_Xorcc,
  NopinionReqDecodeIcc_Pre_Instruction_Subcc,
  NopinionReqDecodeIcc_Pre_Instruction_Andncc,
  NopinionReqDecodeIcc_Pre_Instruction_Orncc,
  NopinionReqDecodeIcc_Pre_Instruction_Xnorcc,
  NopinionReqDecodeIcc_Pre_Instruction_Addxcc,
  NopinionReqDecodeIcc_Pre_Instruction_Umulcc,
  NopinionReqDecodeIcc_Pre_Instruction_Smulcc,
  NopinionReqDecodeIcc_Pre_Instruction_Subxcc,
  NopinionReqDecodeIcc_Pre_Instruction_Udivcc,
  NopinionReqDecodeIcc_Pre_Instruction_Sdivcc,
  NopinionReqDecodeIcc_Pre_Instruction_Taddcc,
  NopinionReqDecodeIcc_Pre_Instruction_Tsubcc,
  NopinionReqDecodeIcc_Pre_Instruction_Taddcctv,
  NopinionReqDecodeIcc_Pre_Instruction_Tsubcctv,
  NopinionReqDecodeIcc_Pre_Instruction_Mulscc,
  NopinionReqDecodeIcc_Pre_Instruction_Sll,
  NopinionReqDecodeIcc_Pre_Instruction_Srl,
  NopinionReqDecodeIcc_Pre_Instruction_Sra,
  NopinionReqDecodeIcc_Pre_Instruction_Rdasr,
  NopinionReqDecodeIcc_Pre_Instruction_Rdpsr,
  NopinionReqDecodeIcc_Pre_Instruction_Rdwim,
  NopinionReqDecodeIcc_Pre_Instruction_Rdtbr,
  NopinionReqDecodeIcc_Pre_Instruction_Wrasr,
  NopinionReqDecodeIcc_Pre_Instruction_Wrpsr,
  NopinionReqDecodeIcc_Pre_Instruction_Wrwim,
  NopinionReqDecodeIcc_Pre_Instruction_Wrtbr,
  NopinionReqDecodeIcc_Pre_Instruction_Fpop1,
  NopinionReqDecodeIcc_Pre_Instruction_Fpop2,
  NopinionReqDecodeIcc_Pre_Instruction_Cpop1,
  NopinionReqDecodeIcc_Pre_Instruction_Cpop2,
  NopinionReqDecodeIcc_Pre_Instruction_Flush,
  NopinionReqDecodeIcc_Pre_Instruction_Save,
  NopinionReqDecodeIcc_Pre_Instruction_Restore,
  NopinionReqDecodeIcc_Pre_Instruction_Undefined,
  NopinionReqDecodeIcc_Pre_Instruction_NA
} NopinionReqDecodeIcc_Pre_Instruction;

typedef enum {
  NopinionReqDecodeIcc_Post_Icc_Modified,
  NopinionReqDecodeIcc_Post_Icc_Unchanged,
  NopinionReqDecodeIcc_Post_Icc_NA
} NopinionReqDecodeIcc_Post_Icc;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Instruction_NA : 1;
  uint8_t Post_Icc : 2;
} NopinionReqDecodeIcc_Entry;

/**
 * @brief Test context for spec:/nopinion/req/decode-icc test case.
 */
typedef struct {
  /**
   * @brief This member contains the instruction.
   */
  uint32_t instruction;

  /**
   * @brief This member is true, if the probe found that the instruction
   *   modifies the integer condition codes.
   */
  bool modifies;

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
    NopinionReqDecodeIcc_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqDecodeIcc_Context;

static NopinionReqDecodeIcc_Context NopinionReqDecodeIcc_Instance;

static const char *const NopinionReqDecodeIcc_PreDesc_Instruction[] = {
  "Add",
  "And",
  "Or",
  "Xor",
  "Sub",
  "Andn",
  "Orn",
  "Xnor",
  "Addx",
  "Umul",
  "Smul",
  "Subx",
  "Udiv",
  "Sdiv",
  "Addcc",
  "Andcc",
  "Orcc",
  "Xorcc",
  "Subcc",
  "Andncc",
  "Orncc",
  "Xnorcc",
  "Addxcc",
  "Umulcc",
  "Smulcc",
  "Subxcc",
  "Udivcc",
  "Sdivcc",
  "Taddcc",
  "Tsubcc",
  "Taddcctv",
  "Tsubcctv",
  "Mulscc",
  "Sll",
  "Srl",
  "Sra",
  "Rdasr",
  "Rdpsr",
  "Rdwim",
  "Rdtbr",
  "Wrasr",
  "Wrpsr",
  "Wrwim",
  "Wrtbr",
  "Fpop1",
  "Fpop2",
  "Cpop1",
  "Cpop2",
  "Flush",
  "Save",
  "Restore",
  "Undefined",
  "NA"
};

static const char *const *const NopinionReqDecodeIcc_PreDesc[] = {
  NopinionReqDecodeIcc_PreDesc_Instruction,
  NULL
};

static void NopinionReqDecodeIcc_Pre_Instruction_Prepare(
  NopinionReqDecodeIcc_Context        *ctx,
  NopinionReqDecodeIcc_Pre_Instruction state
)
{
  switch ( state ) {
    case NopinionReqDecodeIcc_Pre_Instruction_Add: {
      /*
       * While the instruction is an ADD instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x00, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_And: {
      /*
       * While the instruction is an AND instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x01, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Or: {
      /*
       * While the instruction is an OR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x02, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Xor: {
      /*
       * While the instruction is an XOR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x03, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Sub: {
      /*
       * While the instruction is an SUB instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x04, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Andn: {
      /*
       * While the instruction is an ANDN instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x05, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Orn: {
      /*
       * While the instruction is an ORN instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x06, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Xnor: {
      /*
       * While the instruction is an XNOR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x07, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Addx: {
      /*
       * While the instruction is an ADDX instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x08, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Umul: {
      /*
       * While the instruction is an UMUL instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x0a, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Smul: {
      /*
       * While the instruction is an SMUL instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x0b, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Subx: {
      /*
       * While the instruction is an SUBX instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x0c, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Udiv: {
      /*
       * While the instruction is an UDIV instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x0e, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Sdiv: {
      /*
       * While the instruction is an SDIV instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x0f, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Addcc: {
      /*
       * While the instruction is an ADDcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x10, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Andcc: {
      /*
       * While the instruction is an ANDcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x11, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Orcc: {
      /*
       * While the instruction is an ORcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x12, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Xorcc: {
      /*
       * While the instruction is an XORcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x13, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Subcc: {
      /*
       * While the instruction is an SUBcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x14, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Andncc: {
      /*
       * While the instruction is an ANDNcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x15, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Orncc: {
      /*
       * While the instruction is an ORNcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x16, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Xnorcc: {
      /*
       * While the instruction is an XNORcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x17, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Addxcc: {
      /*
       * While the instruction is an ADDXcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x18, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Umulcc: {
      /*
       * While the instruction is an UMULcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x1a, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Smulcc: {
      /*
       * While the instruction is an SMULcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x1b, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Subxcc: {
      /*
       * While the instruction is an SUBXcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x1c, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Udivcc: {
      /*
       * While the instruction is an UDIVcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x1e, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Sdivcc: {
      /*
       * While the instruction is an SDIVcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x1f, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Taddcc: {
      /*
       * While the instruction is a TADDcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x20, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Tsubcc: {
      /*
       * While the instruction is a TSUBcc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x21, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Taddcctv: {
      /*
       * While the instruction is a TADDccTV instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x22, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Tsubcctv: {
      /*
       * While the instruction is a TSUBccTV instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x23, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Mulscc: {
      /*
       * While the instruction is an MULScc instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x24, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Sll: {
      /*
       * While the instruction is an SLL instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x25, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Srl: {
      /*
       * While the instruction is an SRL instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x26, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Sra: {
      /*
       * While the instruction is an SRA instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x27, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Rdasr: {
      /*
       * While the instruction is an RDASR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x28, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Rdpsr: {
      /*
       * While the instruction is an RDPSR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x29, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Rdwim: {
      /*
       * While the instruction is an RDWIM instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x2a, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Rdtbr: {
      /*
       * While the instruction is an RDTBR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x2b, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Wrasr: {
      /*
       * While the instruction is a WRASR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x30, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Wrpsr: {
      /*
       * While the instruction is a WRPSR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x31, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Wrwim: {
      /*
       * While the instruction is a WRWIM instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x32, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Wrtbr: {
      /*
       * While the instruction is a WRTBR instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x33, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Fpop1: {
      /*
       * While the instruction is an FPop1 instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x34, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Fpop2: {
      /*
       * While the instruction is an FPop2 instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x35, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Cpop1: {
      /*
       * While the instruction is a CPop1 instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x36, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Cpop2: {
      /*
       * While the instruction is a CPop2 instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x37, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Flush: {
      /*
       * While the instruction is an FLUSH instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x3b, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Save: {
      /*
       * While the instruction is an SAVE instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x3c, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Restore: {
      /*
       * While the instruction is an RESTORE instruction.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x3d, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_Undefined: {
      /*
       * While the instruction is an arithmetic instruction with an undefined
       * op3 field.
       */
      ctx->instruction = TxFormat3Reg( 2, 0x09, TX_G0, TX_G1, TX_O0 );
      break;
    }

    case NopinionReqDecodeIcc_Pre_Instruction_NA:
      break;
  }
}

static void NopinionReqDecodeIcc_Post_Icc_Check(
  NopinionReqDecodeIcc_Context *ctx,
  NopinionReqDecodeIcc_Post_Icc state
)
{
  switch ( state ) {
    case NopinionReqDecodeIcc_Post_Icc_Modified: {
      /*
       * The errata checker shall classify the instruction as an instruction
       * which modifies the integer condition codes.
       */
      T_true( ctx->modifies );
      break;
    }

    case NopinionReqDecodeIcc_Post_Icc_Unchanged: {
      /*
       * The errata checker shall classify the instruction as an instruction
       * which does not modify the integer condition codes.
       */
      T_false( ctx->modifies );
      break;
    }

    case NopinionReqDecodeIcc_Post_Icc_NA:
      break;
  }
}

static void NopinionReqDecodeIcc_Action( NopinionReqDecodeIcc_Context *ctx )
{
  ctx->modifies = TxProbeIcc( ctx->instruction );
}

/* clang-format off */

static const NopinionReqDecodeIcc_Entry
NopinionReqDecodeIcc_Entries[] = {
  { 0, 0, NopinionReqDecodeIcc_Post_Icc_Unchanged },
  { 0, 0, NopinionReqDecodeIcc_Post_Icc_Modified }
};

static const uint8_t
NopinionReqDecodeIcc_Map[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqDecodeIcc_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqDecodeIcc_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqDecodeIcc_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqDecodeIcc_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqDecodeIcc_Scope,
  .initial_context = &NopinionReqDecodeIcc_Instance
};

static inline NopinionReqDecodeIcc_Entry NopinionReqDecodeIcc_PopEntry(
  NopinionReqDecodeIcc_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqDecodeIcc_Entries[ NopinionReqDecodeIcc_Map[ index ] ];
}

static void NopinionReqDecodeIcc_TestVariant(
  NopinionReqDecodeIcc_Context *ctx
)
{
  NopinionReqDecodeIcc_Pre_Instruction_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqDecodeIcc_Action( ctx );
  NopinionReqDecodeIcc_Post_Icc_Check( ctx, ctx->Map.entry.Post_Icc );
}

/**
 * @fn void T_case_body_NopinionReqDecodeIcc( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqDecodeIcc, &NopinionReqDecodeIcc_Fixture )
{
  NopinionReqDecodeIcc_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqDecodeIcc_Pre_Instruction_Add;
    ctx->Map.pcs[ 0 ] < NopinionReqDecodeIcc_Pre_Instruction_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    ctx->Map.entry = NopinionReqDecodeIcc_PopEntry( ctx );
    NopinionReqDecodeIcc_TestVariant( ctx );
  }
}

/** @} */
