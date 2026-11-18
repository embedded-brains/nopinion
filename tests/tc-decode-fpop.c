/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqDecodeFpop
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
 * @defgroup NopinionReqDecodeFpop spec:/nopinion/req/decode-fpop
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqDecodeFpop_Pre_Instruction_Fitos,
  NopinionReqDecodeFpop_Pre_Instruction_Fitod,
  NopinionReqDecodeFpop_Pre_Instruction_Fitoq,
  NopinionReqDecodeFpop_Pre_Instruction_Fstoi,
  NopinionReqDecodeFpop_Pre_Instruction_Fdtoi,
  NopinionReqDecodeFpop_Pre_Instruction_Fqtoi,
  NopinionReqDecodeFpop_Pre_Instruction_Fstod,
  NopinionReqDecodeFpop_Pre_Instruction_Fstoq,
  NopinionReqDecodeFpop_Pre_Instruction_Fdtos,
  NopinionReqDecodeFpop_Pre_Instruction_Fdtoq,
  NopinionReqDecodeFpop_Pre_Instruction_Fqtos,
  NopinionReqDecodeFpop_Pre_Instruction_Fqtod,
  NopinionReqDecodeFpop_Pre_Instruction_Fmovs,
  NopinionReqDecodeFpop_Pre_Instruction_Fnegs,
  NopinionReqDecodeFpop_Pre_Instruction_Fabss,
  NopinionReqDecodeFpop_Pre_Instruction_Fsqrts,
  NopinionReqDecodeFpop_Pre_Instruction_Fsqrtd,
  NopinionReqDecodeFpop_Pre_Instruction_Fsqrtq,
  NopinionReqDecodeFpop_Pre_Instruction_Fadds,
  NopinionReqDecodeFpop_Pre_Instruction_Faddd,
  NopinionReqDecodeFpop_Pre_Instruction_Faddq,
  NopinionReqDecodeFpop_Pre_Instruction_Fsubs,
  NopinionReqDecodeFpop_Pre_Instruction_Fsubd,
  NopinionReqDecodeFpop_Pre_Instruction_Fsubq,
  NopinionReqDecodeFpop_Pre_Instruction_Fmuls,
  NopinionReqDecodeFpop_Pre_Instruction_Fmuld,
  NopinionReqDecodeFpop_Pre_Instruction_Fmulq,
  NopinionReqDecodeFpop_Pre_Instruction_Fdivs,
  NopinionReqDecodeFpop_Pre_Instruction_Fdivd,
  NopinionReqDecodeFpop_Pre_Instruction_Fdivq,
  NopinionReqDecodeFpop_Pre_Instruction_Fsmuld,
  NopinionReqDecodeFpop_Pre_Instruction_Fdmulq,
  NopinionReqDecodeFpop_Pre_Instruction_Fcmps,
  NopinionReqDecodeFpop_Pre_Instruction_Fcmpd,
  NopinionReqDecodeFpop_Pre_Instruction_Fcmpq,
  NopinionReqDecodeFpop_Pre_Instruction_Fcmpes,
  NopinionReqDecodeFpop_Pre_Instruction_Fcmped,
  NopinionReqDecodeFpop_Pre_Instruction_Fcmpeq,
  NopinionReqDecodeFpop_Pre_Instruction_Fpop1Undefined,
  NopinionReqDecodeFpop_Pre_Instruction_Fpop2Undefined,
  NopinionReqDecodeFpop_Pre_Instruction_NA
} NopinionReqDecodeFpop_Pre_Instruction;

typedef enum {
  NopinionReqDecodeFpop_Post_Kind_Fpop1,
  NopinionReqDecodeFpop_Post_Kind_Div,
  NopinionReqDecodeFpop_Post_Kind_Fpop2,
  NopinionReqDecodeFpop_Post_Kind_NA
} NopinionReqDecodeFpop_Post_Kind;

typedef enum {
  NopinionReqDecodeFpop_Post_Rs1_None,
  NopinionReqDecodeFpop_Post_Rs1_Single,
  NopinionReqDecodeFpop_Post_Rs1_Double,
  NopinionReqDecodeFpop_Post_Rs1_Quad,
  NopinionReqDecodeFpop_Post_Rs1_Any,
  NopinionReqDecodeFpop_Post_Rs1_NA
} NopinionReqDecodeFpop_Post_Rs1;

typedef enum {
  NopinionReqDecodeFpop_Post_Rs2_None,
  NopinionReqDecodeFpop_Post_Rs2_Single,
  NopinionReqDecodeFpop_Post_Rs2_Double,
  NopinionReqDecodeFpop_Post_Rs2_Quad,
  NopinionReqDecodeFpop_Post_Rs2_Any,
  NopinionReqDecodeFpop_Post_Rs2_NA
} NopinionReqDecodeFpop_Post_Rs2;

typedef enum {
  NopinionReqDecodeFpop_Post_Rd_None,
  NopinionReqDecodeFpop_Post_Rd_Single,
  NopinionReqDecodeFpop_Post_Rd_Double,
  NopinionReqDecodeFpop_Post_Rd_Quad,
  NopinionReqDecodeFpop_Post_Rd_Any,
  NopinionReqDecodeFpop_Post_Rd_NA
} NopinionReqDecodeFpop_Post_Rd;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Instruction_NA : 1;
  uint16_t Post_Kind : 2;
  uint16_t Post_Rs1 : 3;
  uint16_t Post_Rs2 : 3;
  uint16_t Post_Rd : 3;
} NopinionReqDecodeFpop_Entry;

/**
 * @brief Test context for spec:/nopinion/req/decode-fpop test case.
 */
typedef struct {
  /**
   * @brief This member contains the op3 field of the instruction.
   */
  uint32_t op3;

  /**
   * @brief This member contains the opf field of the instruction.
   */
  uint32_t opf;

  /**
   * @brief This member contains the kind of the instruction which selects the
   *   arrangement of the probe.
   */
  TxFpopKind kind;

  /**
   * @brief This member contains the result of the probe of the instruction.
   */
  TxFpopProbe probe;

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
    NopinionReqDecodeFpop_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqDecodeFpop_Context;

static NopinionReqDecodeFpop_Context NopinionReqDecodeFpop_Instance;

static const char *const NopinionReqDecodeFpop_PreDesc_Instruction[] = {
  "Fitos",
  "Fitod",
  "Fitoq",
  "Fstoi",
  "Fdtoi",
  "Fqtoi",
  "Fstod",
  "Fstoq",
  "Fdtos",
  "Fdtoq",
  "Fqtos",
  "Fqtod",
  "Fmovs",
  "Fnegs",
  "Fabss",
  "Fsqrts",
  "Fsqrtd",
  "Fsqrtq",
  "Fadds",
  "Faddd",
  "Faddq",
  "Fsubs",
  "Fsubd",
  "Fsubq",
  "Fmuls",
  "Fmuld",
  "Fmulq",
  "Fdivs",
  "Fdivd",
  "Fdivq",
  "Fsmuld",
  "Fdmulq",
  "Fcmps",
  "Fcmpd",
  "Fcmpq",
  "Fcmpes",
  "Fcmped",
  "Fcmpeq",
  "Fpop1Undefined",
  "Fpop2Undefined",
  "NA"
};

static const char *const *const NopinionReqDecodeFpop_PreDesc[] = {
  NopinionReqDecodeFpop_PreDesc_Instruction,
  NULL
};

static void NopinionReqDecodeFpop_Pre_Instruction_Prepare(
  NopinionReqDecodeFpop_Context        *ctx,
  NopinionReqDecodeFpop_Pre_Instruction state
)
{
  switch ( state ) {
    case NopinionReqDecodeFpop_Pre_Instruction_Fitos: {
      /*
       * While the instruction is an FiTOs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0c4;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fitod: {
      /*
       * While the instruction is an FiTOd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0c8;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fitoq: {
      /*
       * While the instruction is an FiTOq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0cc;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fstoi: {
      /*
       * While the instruction is an FsTOi instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0d1;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdtoi: {
      /*
       * While the instruction is an FdTOi instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0d2;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fqtoi: {
      /*
       * While the instruction is an FqTOi instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0d3;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fstod: {
      /*
       * While the instruction is an FsTOd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0c9;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fstoq: {
      /*
       * While the instruction is an FsTOq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0cd;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdtos: {
      /*
       * While the instruction is an FdTOs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0c6;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdtoq: {
      /*
       * While the instruction is an FdTOq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0ce;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fqtos: {
      /*
       * While the instruction is an FqTOs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0c7;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fqtod: {
      /*
       * While the instruction is an FqTOd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0cb;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fmovs: {
      /*
       * While the instruction is an FMOVs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x001;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fnegs: {
      /*
       * While the instruction is an FNEGs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x005;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fabss: {
      /*
       * While the instruction is an FABSs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x009;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsqrts: {
      /*
       * While the instruction is an FSQRTs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x029;
      ctx->kind = TX_KIND_DIV;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsqrtd: {
      /*
       * While the instruction is an FSQRTd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x02a;
      ctx->kind = TX_KIND_DIV;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsqrtq: {
      /*
       * While the instruction is an FSQRTq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x02b;
      ctx->kind = TX_KIND_DIV;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fadds: {
      /*
       * While the instruction is an FADDs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x041;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Faddd: {
      /*
       * While the instruction is an FADDd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x042;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Faddq: {
      /*
       * While the instruction is an FADDq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x043;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsubs: {
      /*
       * While the instruction is an FSUBs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x045;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsubd: {
      /*
       * While the instruction is an FSUBd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x046;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsubq: {
      /*
       * While the instruction is an FSUBq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x047;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fmuls: {
      /*
       * While the instruction is an FMULs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x049;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fmuld: {
      /*
       * While the instruction is an FMULd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x04a;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fmulq: {
      /*
       * While the instruction is an FMULq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x04b;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdivs: {
      /*
       * While the instruction is an FDIVs instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x04d;
      ctx->kind = TX_KIND_DIV;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdivd: {
      /*
       * While the instruction is an FDIVd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x04e;
      ctx->kind = TX_KIND_DIV;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdivq: {
      /*
       * While the instruction is an FDIVq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x04f;
      ctx->kind = TX_KIND_DIV;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fsmuld: {
      /*
       * While the instruction is an FsMULd instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x069;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fdmulq: {
      /*
       * While the instruction is an FdMULq instruction.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x06e;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fcmps: {
      /*
       * While the instruction is an FCMPs instruction.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x051;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fcmpd: {
      /*
       * While the instruction is an FCMPd instruction.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x052;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fcmpq: {
      /*
       * While the instruction is an FCMPq instruction.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x053;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fcmpes: {
      /*
       * While the instruction is an FCMPEs instruction.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x055;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fcmped: {
      /*
       * While the instruction is an FCMPEd instruction.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x056;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fcmpeq: {
      /*
       * While the instruction is an FCMPEq instruction.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x057;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fpop1Undefined: {
      /*
       * While the instruction is an FPop1 instruction with an undefined opf
       * field.
       */
      ctx->op3 = 0x34;
      ctx->opf = 0x0ff;
      ctx->kind = TX_KIND_FPOP1;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_Fpop2Undefined: {
      /*
       * While the instruction is an FPop2 instruction with an undefined opf
       * field.
       */
      ctx->op3 = 0x35;
      ctx->opf = 0x0ff;
      ctx->kind = TX_KIND_FPOP2;
      break;
    }

    case NopinionReqDecodeFpop_Pre_Instruction_NA:
      break;
  }
}

static void NopinionReqDecodeFpop_Post_Kind_Check(
  NopinionReqDecodeFpop_Context  *ctx,
  NopinionReqDecodeFpop_Post_Kind state
)
{
  switch ( state ) {
    case NopinionReqDecodeFpop_Post_Kind_Fpop1: {
      /*
       * The errata checker shall classify the instruction as an FPop1
       * instruction other than FDIV and FSQRT.
       */
      T_true( ctx->probe.is_fpop );
      T_false( ctx->probe.is_div );
      break;
    }

    case NopinionReqDecodeFpop_Post_Kind_Div: {
      /*
       * The errata checker shall classify the instruction as an FDIV or FSQRT
       * instruction.
       */
      T_true( ctx->probe.is_fpop );
      T_true( ctx->probe.is_div );
      T_false( ctx->probe.counted );
      break;
    }

    case NopinionReqDecodeFpop_Post_Kind_Fpop2: {
      /*
       * The errata checker shall classify the instruction as an FPop2
       * instruction.
       */
      T_true( ctx->probe.is_fpop );
      T_false( ctx->probe.is_div );
      T_false( ctx->probe.counted );
      break;
    }

    case NopinionReqDecodeFpop_Post_Kind_NA:
      break;
  }
}

static void NopinionReqDecodeFpop_Post_Rs1_Check(
  NopinionReqDecodeFpop_Context *ctx,
  NopinionReqDecodeFpop_Post_Rs1 state
)
{
  switch ( state ) {
    case NopinionReqDecodeFpop_Post_Rs1_None: {
      /*
       * The errata checker shall treat the instruction as an instruction
       * without a first source operand.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS1 ], 0 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs1_Single: {
      /*
       * The errata checker shall treat the first source operand of the
       * instruction as one register.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS1 ], 1 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs1_Double: {
      /*
       * The errata checker shall treat the first source operand of the
       * instruction as two registers.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS1 ], 2 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs1_Quad: {
      /*
       * The errata checker shall treat the first source operand of the
       * instruction as four registers.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS1 ], 4 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs1_Any: {
      /*
       * The errata checker shall treat the first source operand of the
       * instruction as a dependency on every floating-point register.
       */
      T_true( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS1 ], 4 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs1_NA:
      break;
  }
}

static void NopinionReqDecodeFpop_Post_Rs2_Check(
  NopinionReqDecodeFpop_Context *ctx,
  NopinionReqDecodeFpop_Post_Rs2 state
)
{
  switch ( state ) {
    case NopinionReqDecodeFpop_Post_Rs2_None: {
      /*
       * The errata checker shall treat the instruction as an instruction
       * without a second source operand.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS2 ], 0 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs2_Single: {
      /*
       * The errata checker shall treat the second source operand of the
       * instruction as one register.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS2 ], 1 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs2_Double: {
      /*
       * The errata checker shall treat the second source operand of the
       * instruction as two registers.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS2 ], 2 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs2_Quad: {
      /*
       * The errata checker shall treat the second source operand of the
       * instruction as four registers.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS2 ], 4 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs2_Any: {
      /*
       * The errata checker shall treat the second source operand of the
       * instruction as a dependency on every floating-point register.
       */
      T_true( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RS2 ], 4 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rs2_NA:
      break;
  }
}

static void NopinionReqDecodeFpop_Post_Rd_Check(
  NopinionReqDecodeFpop_Context *ctx,
  NopinionReqDecodeFpop_Post_Rd  state
)
{
  switch ( state ) {
    case NopinionReqDecodeFpop_Post_Rd_None: {
      /*
       * The errata checker shall treat the instruction as an instruction
       * without a destination operand.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RD ], 0 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rd_Single: {
      /*
       * The errata checker shall treat the destination operand of the
       * instruction as one register.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RD ], 1 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rd_Double: {
      /*
       * The errata checker shall treat the destination operand of the
       * instruction as two registers.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RD ], 2 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rd_Quad: {
      /*
       * The errata checker shall treat the destination operand of the
       * instruction as four registers.
       */
      T_false( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RD ], 4 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rd_Any: {
      /*
       * The errata checker shall treat the destination operand of the
       * instruction as a dependency on every floating-point register.
       */
      T_true( ctx->probe.any );
      T_eq_int( ctx->probe.width[ TX_RD ], 4 );
      break;
    }

    case NopinionReqDecodeFpop_Post_Rd_NA:
      break;
  }
}

static void NopinionReqDecodeFpop_Action( NopinionReqDecodeFpop_Context *ctx )
{
  TxProbeFpop( ctx->op3, ctx->opf, ctx->kind, &ctx->probe );
}

/* clang-format off */

static const NopinionReqDecodeFpop_Entry
NopinionReqDecodeFpop_Entries[] = {
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Single,
    NopinionReqDecodeFpop_Post_Rd_Single },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_Single,
    NopinionReqDecodeFpop_Post_Rs2_Single, NopinionReqDecodeFpop_Post_Rd_Single },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_Double,
    NopinionReqDecodeFpop_Post_Rs2_Double, NopinionReqDecodeFpop_Post_Rd_Double },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_Quad, NopinionReqDecodeFpop_Post_Rs2_Quad,
    NopinionReqDecodeFpop_Post_Rd_Quad },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Single,
    NopinionReqDecodeFpop_Post_Rd_Double },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Single,
    NopinionReqDecodeFpop_Post_Rd_Quad },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Double,
    NopinionReqDecodeFpop_Post_Rd_Single },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Quad,
    NopinionReqDecodeFpop_Post_Rd_Single },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop2,
    NopinionReqDecodeFpop_Post_Rs1_Single,
    NopinionReqDecodeFpop_Post_Rs2_Single, NopinionReqDecodeFpop_Post_Rd_None },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop2,
    NopinionReqDecodeFpop_Post_Rs1_Double,
    NopinionReqDecodeFpop_Post_Rs2_Double, NopinionReqDecodeFpop_Post_Rd_None },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop2,
    NopinionReqDecodeFpop_Post_Rs1_Quad, NopinionReqDecodeFpop_Post_Rs2_Quad,
    NopinionReqDecodeFpop_Post_Rd_None },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Double,
    NopinionReqDecodeFpop_Post_Rd_Quad },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Quad,
    NopinionReqDecodeFpop_Post_Rd_Double },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Div,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Single,
    NopinionReqDecodeFpop_Post_Rd_Single },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Div,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Double,
    NopinionReqDecodeFpop_Post_Rd_Double },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Div,
    NopinionReqDecodeFpop_Post_Rs1_None, NopinionReqDecodeFpop_Post_Rs2_Quad,
    NopinionReqDecodeFpop_Post_Rd_Quad },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Div,
    NopinionReqDecodeFpop_Post_Rs1_Single,
    NopinionReqDecodeFpop_Post_Rs2_Single, NopinionReqDecodeFpop_Post_Rd_Single },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Div,
    NopinionReqDecodeFpop_Post_Rs1_Double,
    NopinionReqDecodeFpop_Post_Rs2_Double, NopinionReqDecodeFpop_Post_Rd_Double },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Div,
    NopinionReqDecodeFpop_Post_Rs1_Quad, NopinionReqDecodeFpop_Post_Rs2_Quad,
    NopinionReqDecodeFpop_Post_Rd_Quad },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_Single,
    NopinionReqDecodeFpop_Post_Rs2_Single, NopinionReqDecodeFpop_Post_Rd_Double },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_Double,
    NopinionReqDecodeFpop_Post_Rs2_Double, NopinionReqDecodeFpop_Post_Rd_Quad },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop1,
    NopinionReqDecodeFpop_Post_Rs1_Any, NopinionReqDecodeFpop_Post_Rs2_Any,
    NopinionReqDecodeFpop_Post_Rd_Any },
  { 0, 0, NopinionReqDecodeFpop_Post_Kind_Fpop2,
    NopinionReqDecodeFpop_Post_Rs1_Any, NopinionReqDecodeFpop_Post_Rs2_Any,
    NopinionReqDecodeFpop_Post_Rd_Any }
};

static const uint8_t
NopinionReqDecodeFpop_Map[] = {
  0, 4, 5, 0, 6, 7, 4, 5, 6, 11, 7, 12, 0, 0, 0, 13, 14, 15, 1, 2, 3, 1, 2, 3,
  1, 2, 3, 16, 17, 18, 19, 20, 8, 9, 10, 8, 9, 10, 21, 22
};

/* clang-format on */

static size_t NopinionReqDecodeFpop_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqDecodeFpop_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqDecodeFpop_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqDecodeFpop_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqDecodeFpop_Scope,
  .initial_context = &NopinionReqDecodeFpop_Instance
};

static inline NopinionReqDecodeFpop_Entry NopinionReqDecodeFpop_PopEntry(
  NopinionReqDecodeFpop_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqDecodeFpop_Entries[ NopinionReqDecodeFpop_Map[ index ] ];
}

static void NopinionReqDecodeFpop_TestVariant(
  NopinionReqDecodeFpop_Context *ctx
)
{
  NopinionReqDecodeFpop_Pre_Instruction_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqDecodeFpop_Action( ctx );
  NopinionReqDecodeFpop_Post_Kind_Check( ctx, ctx->Map.entry.Post_Kind );
  NopinionReqDecodeFpop_Post_Rs1_Check( ctx, ctx->Map.entry.Post_Rs1 );
  NopinionReqDecodeFpop_Post_Rs2_Check( ctx, ctx->Map.entry.Post_Rs2 );
  NopinionReqDecodeFpop_Post_Rd_Check( ctx, ctx->Map.entry.Post_Rd );
}

/**
 * @fn void T_case_body_NopinionReqDecodeFpop( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqDecodeFpop, &NopinionReqDecodeFpop_Fixture )
{
  NopinionReqDecodeFpop_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqDecodeFpop_Pre_Instruction_Fitos;
    ctx->Map.pcs[ 0 ] < NopinionReqDecodeFpop_Pre_Instruction_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    ctx->Map.entry = NopinionReqDecodeFpop_PopEntry( ctx );
    NopinionReqDecodeFpop_TestVariant( ctx );
  }
}

/** @} */
