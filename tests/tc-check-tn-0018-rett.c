/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0018Rett
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
 * @defgroup NopinionReqCheckTn0018Rett spec:/nopinion/req/check-tn-0018-rett
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0018Rett_Pre_Pair_JmplRett,
  NopinionReqCheckTn0018Rett_Pre_Pair_JmplOther,
  NopinionReqCheckTn0018Rett_Pre_Pair_JmplLast,
  NopinionReqCheckTn0018Rett_Pre_Pair_OtherRett,
  NopinionReqCheckTn0018Rett_Pre_Pair_NA
} NopinionReqCheckTn0018Rett_Pre_Pair;

typedef enum {
  NopinionReqCheckTn0018Rett_Pre_Disable_Sta,
  NopinionReqCheckTn0018Rett_Pre_Disable_StaAsi,
  NopinionReqCheckTn0018Rett_Pre_Disable_StaAddress,
  NopinionReqCheckTn0018Rett_Pre_Disable_StaImmediate,
  NopinionReqCheckTn0018Rett_Pre_Disable_Other,
  NopinionReqCheckTn0018Rett_Pre_Disable_Absent,
  NopinionReqCheckTn0018Rett_Pre_Disable_NA
} NopinionReqCheckTn0018Rett_Pre_Disable;

typedef enum {
  NopinionReqCheckTn0018Rett_Pre_Reads_Both,
  NopinionReqCheckTn0018Rett_Pre_Reads_Reversed,
  NopinionReqCheckTn0018Rett_Pre_Reads_L1,
  NopinionReqCheckTn0018Rett_Pre_Reads_L2,
  NopinionReqCheckTn0018Rett_Pre_Reads_None,
  NopinionReqCheckTn0018Rett_Pre_Reads_NA
} NopinionReqCheckTn0018Rett_Pre_Reads;

typedef enum {
  NopinionReqCheckTn0018Rett_Pre_Enable_Sta,
  NopinionReqCheckTn0018Rett_Pre_Enable_StaAsi,
  NopinionReqCheckTn0018Rett_Pre_Enable_StaAddress,
  NopinionReqCheckTn0018Rett_Pre_Enable_StaImmediate,
  NopinionReqCheckTn0018Rett_Pre_Enable_Other,
  NopinionReqCheckTn0018Rett_Pre_Enable_NA
} NopinionReqCheckTn0018Rett_Pre_Enable;

typedef enum {
  NopinionReqCheckTn0018Rett_Post_Finding_None,
  NopinionReqCheckTn0018Rett_Post_Finding_Definite,
  NopinionReqCheckTn0018Rett_Post_Finding_NA
} NopinionReqCheckTn0018Rett_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Pair_NA : 1;
  uint8_t Pre_Disable_NA : 1;
  uint8_t Pre_Reads_NA : 1;
  uint8_t Pre_Enable_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0018Rett_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0018-rett test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the instructions of the pair.
   */
  uint32_t pair[ 2 ];

  /**
   * @brief This member contains the count of instructions of the pair.
   */
  size_t pair_count;

  /**
   * @brief This member contains the sixth instruction before the pair.
   */
  uint32_t disable;

  /**
   * @brief This member is true, if the code section starts after the sixth
   *   instruction before the pair.
   */
  bool disable_absent;

  /**
   * @brief This member contains the fifth to third instructions before the
   *   pair.
   */
  uint32_t reads[ 3 ];

  /**
   * @brief This member contains the second instruction before the pair.
   */
  uint32_t enable;

  /**
   * @brief This member contains the offset of the instruction of the pair.
   */
  uint32_t offset;

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
    NopinionReqCheckTn0018Rett_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0018Rett_Context;

static NopinionReqCheckTn0018Rett_Context NopinionReqCheckTn0018Rett_Instance;

static const char *const NopinionReqCheckTn0018Rett_PreDesc_Pair[] =
  { "JmplRett", "JmplOther", "JmplLast", "OtherRett", "NA" };

static const char *const NopinionReqCheckTn0018Rett_PreDesc_Disable[] =
  { "Sta", "StaAsi", "StaAddress", "StaImmediate", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0018Rett_PreDesc_Reads[] =
  { "Both", "Reversed", "L1", "L2", "None", "NA" };

static const char *const NopinionReqCheckTn0018Rett_PreDesc_Enable[] =
  { "Sta", "StaAsi", "StaAddress", "StaImmediate", "Other", "NA" };

static const char *const *const NopinionReqCheckTn0018Rett_PreDesc[] = {
  NopinionReqCheckTn0018Rett_PreDesc_Pair,
  NopinionReqCheckTn0018Rett_PreDesc_Disable,
  NopinionReqCheckTn0018Rett_PreDesc_Reads,
  NopinionReqCheckTn0018Rett_PreDesc_Enable,
  NULL
};

static void NopinionReqCheckTn0018Rett_Pre_Pair_Prepare(
  NopinionReqCheckTn0018Rett_Context *ctx,
  NopinionReqCheckTn0018Rett_Pre_Pair state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Rett_Pre_Pair_JmplRett: {
      /*
       * While the instruction of the pair is a JMPL instruction, while a RETT
       * instruction follows it.
       */
      ctx->pair[ 0 ] = TxJmpl();
      ctx->pair[ 1 ] = TxRett();
      ctx->pair_count = 2;
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Pair_JmplOther: {
      /*
       * While the instruction of the pair is a JMPL instruction, while an
       * instruction other than RETT follows it.
       */
      ctx->pair[ 0 ] = TxJmpl();
      ctx->pair[ 1 ] = TxNop();
      ctx->pair_count = 2;
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Pair_JmplLast: {
      /*
       * While the instruction of the pair is a JMPL instruction, while the
       * code section ends after it.
       */
      ctx->pair[ 0 ] = TxJmpl();
      ctx->pair_count = 1;
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Pair_OtherRett: {
      /*
       * While the instruction of the pair transfers no control, while a RETT
       * instruction follows it.
       */
      ctx->pair[ 0 ] = TxNop();
      ctx->pair[ 1 ] = TxRett();
      ctx->pair_count = 2;
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Pair_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Rett_Pre_Disable_Prepare(
  NopinionReqCheckTn0018Rett_Context    *ctx,
  NopinionReqCheckTn0018Rett_Pre_Disable state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Rett_Pre_Disable_Sta: {
      /*
       * While the sixth instruction before the instruction of the pair is an
       * STA instruction with the address space identifier 2 and the address
       * [%g0].
       */
      ctx->disable = TxFormat3Asi( 3, 0x14, TX_L4, TX_G0, 2, TX_G0 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Disable_StaAsi: {
      /*
       * While the sixth instruction before the instruction of the pair is an
       * STA instruction with the address space identifier 3 and the address
       * [%g0].
       */
      ctx->disable = TxFormat3Asi( 3, 0x14, TX_L4, TX_G0, 3, TX_G0 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Disable_StaAddress: {
      /*
       * While the sixth instruction before the instruction of the pair is an
       * STA instruction with the address space identifier 2 and the address
       * [%l0].
       */
      ctx->disable = TxFormat3Asi( 3, 0x14, TX_L4, TX_L0, 2, TX_G0 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Disable_StaImmediate: {
      /*
       * While the sixth instruction before the instruction of the pair is an
       * STA instruction with an immediate operand.
       */
      ctx->disable = TxFormat3Imm( 3, 0x14, TX_L4, TX_G0, 2 << 5 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Disable_Other: {
      /*
       * While the sixth instruction before the instruction of the pair is no
       * store.
       */
      ctx->disable = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Disable_Absent: {
      /*
       * While the code section starts with the fifth instruction before the
       * instruction of the pair.
       */
      ctx->disable_absent = true;
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Disable_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Rett_Pre_Reads_Prepare(
  NopinionReqCheckTn0018Rett_Context  *ctx,
  NopinionReqCheckTn0018Rett_Pre_Reads state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Rett_Pre_Reads_Both: {
      /*
       * While the fifth to third instructions before the instruction of the
       * pair are a NOP, OR %l1, %l1, %l1 and OR %l2, %l2, %l2.
       */
      ctx->reads[ 0 ] = TxNop();
      ctx->reads[ 1 ] = TxFormat3Reg( 2, 0x02, TX_L1, TX_L1, TX_L1 );
      ctx->reads[ 2 ] = TxFormat3Reg( 2, 0x02, TX_L2, TX_L2, TX_L2 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Reads_Reversed: {
      /*
       * While the fifth to third instructions before the instruction of the
       * pair are OR %l2, %l2, %l2, OR %l1, %l1, %l1 and a NOP.
       */
      ctx->reads[ 0 ] = TxFormat3Reg( 2, 0x02, TX_L2, TX_L2, TX_L2 );
      ctx->reads[ 1 ] = TxFormat3Reg( 2, 0x02, TX_L1, TX_L1, TX_L1 );
      ctx->reads[ 2 ] = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Reads_L1: {
      /*
       * While the fifth to third instructions before the instruction of the
       * pair are a NOP, OR %l1, %l1, %l1 and a NOP.
       */
      ctx->reads[ 0 ] = TxNop();
      ctx->reads[ 1 ] = TxFormat3Reg( 2, 0x02, TX_L1, TX_L1, TX_L1 );
      ctx->reads[ 2 ] = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Reads_L2: {
      /*
       * While the fifth to third instructions before the instruction of the
       * pair are OR %l2, %l2, %l2 and two NOPs.
       */
      ctx->reads[ 0 ] = TxFormat3Reg( 2, 0x02, TX_L2, TX_L2, TX_L2 );
      ctx->reads[ 1 ] = TxNop();
      ctx->reads[ 2 ] = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Reads_None: {
      /*
       * While the fifth to third instructions before the instruction of the
       * pair are three NOPs.
       */
      ctx->reads[ 0 ] = TxNop();
      ctx->reads[ 1 ] = TxNop();
      ctx->reads[ 2 ] = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Reads_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Rett_Pre_Enable_Prepare(
  NopinionReqCheckTn0018Rett_Context   *ctx,
  NopinionReqCheckTn0018Rett_Pre_Enable state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Rett_Pre_Enable_Sta: {
      /*
       * While the second instruction before the instruction of the pair is an
       * STA instruction with the address space identifier 2 and the address
       * [%g0].
       */
      ctx->enable = TxFormat3Asi( 3, 0x14, TX_L3, TX_G0, 2, TX_G0 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Enable_StaAsi: {
      /*
       * While the second instruction before the instruction of the pair is an
       * STA instruction with the address space identifier 3 and the address
       * [%g0].
       */
      ctx->enable = TxFormat3Asi( 3, 0x14, TX_L3, TX_G0, 3, TX_G0 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Enable_StaAddress: {
      /*
       * While the second instruction before the instruction of the pair is an
       * STA instruction with the address space identifier 2 and the address
       * [%l0].
       */
      ctx->enable = TxFormat3Asi( 3, 0x14, TX_L3, TX_L0, 2, TX_G0 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Enable_StaImmediate: {
      /*
       * While the second instruction before the instruction of the pair is an
       * STA instruction with an immediate operand.
       */
      ctx->enable = TxFormat3Imm( 3, 0x14, TX_L3, TX_G0, 2 << 5 );
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Enable_Other: {
      /*
       * While the second instruction before the instruction of the pair is no
       * store.
       */
      ctx->enable = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Rett_Pre_Enable_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Rett_Post_Finding_Check(
  NopinionReqCheckTn0018Rett_Context     *ctx,
  NopinionReqCheckTn0018Rett_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Rett_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of a JMPL, RETT pair
       * without the workaround.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "rett-without-workaround" ),
        0
      );
      break;
    }

    case NopinionReqCheckTn0018Rett_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of a JMPL, RETT
       * pair without the workaround for the instruction of the pair.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "rett-without-workaround" ),
        1
      );
      T_false(
        TxIsPossibleAt( ctx->report, ctx->offset, "rett-without-workaround" )
      );
      break;
    }

    case NopinionReqCheckTn0018Rett_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Rett_Prepare(
  NopinionReqCheckTn0018Rett_Context *ctx
)
{
  TxImageInit( &ctx->image );
  ctx->disable_absent = false;
}

static void NopinionReqCheckTn0018Rett_Action(
  NopinionReqCheckTn0018Rett_Context *ctx
)
{
  size_t i;

  if ( !ctx->disable_absent ) {
    TxAppend( &ctx->image, ctx->disable );
  }

  for ( i = 0; i < 3; ++i ) {
    TxAppend( &ctx->image, ctx->reads[ i ] );
  }

  TxAppend( &ctx->image, ctx->enable );
  TxAppend( &ctx->image, TxNop() );
  ctx->offset = (uint32_t) ( 4 * ctx->image.count );

  for ( i = 0; i < ctx->pair_count; ++i ) {
    TxAppend( &ctx->image, ctx->pair[ i ] );
  }

  ctx->report = TxCheck( &ctx->image, NOTE_0018 );
}

/* clang-format off */

static const NopinionReqCheckTn0018Rett_Entry
NopinionReqCheckTn0018Rett_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0018Rett_Post_Finding_None },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0018Rett_Post_Finding_Definite }
};

static const uint8_t
NopinionReqCheckTn0018Rett_Map[] = {
  0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0
};

/* clang-format on */

static size_t NopinionReqCheckTn0018Rett_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqCheckTn0018Rett_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckTn0018Rett_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0018Rett_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0018Rett_Scope,
  .initial_context = &NopinionReqCheckTn0018Rett_Instance
};

static inline NopinionReqCheckTn0018Rett_Entry
NopinionReqCheckTn0018Rett_PopEntry( NopinionReqCheckTn0018Rett_Context *ctx )
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0018Rett_Entries
    [ NopinionReqCheckTn0018Rett_Map[ index ] ];
}

static void NopinionReqCheckTn0018Rett_TestVariant(
  NopinionReqCheckTn0018Rett_Context *ctx
)
{
  NopinionReqCheckTn0018Rett_Pre_Pair_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0018Rett_Pre_Disable_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0018Rett_Pre_Reads_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckTn0018Rett_Pre_Enable_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqCheckTn0018Rett_Action( ctx );
  NopinionReqCheckTn0018Rett_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0018Rett( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckTn0018Rett,
  &NopinionReqCheckTn0018Rett_Fixture
)
{
  NopinionReqCheckTn0018Rett_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCheckTn0018Rett_Pre_Pair_JmplRett;
    ctx->Map.pcs[ 0 ] < NopinionReqCheckTn0018Rett_Pre_Pair_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCheckTn0018Rett_Pre_Disable_Sta;
      ctx->Map.pcs[ 1 ] < NopinionReqCheckTn0018Rett_Pre_Disable_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqCheckTn0018Rett_Pre_Reads_Both;
        ctx->Map.pcs[ 2 ] < NopinionReqCheckTn0018Rett_Pre_Reads_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        for (
          ctx->Map.pcs[ 3 ] = NopinionReqCheckTn0018Rett_Pre_Enable_Sta;
          ctx->Map.pcs[ 3 ] < NopinionReqCheckTn0018Rett_Pre_Enable_NA;
          ++ctx->Map.pcs[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqCheckTn0018Rett_PopEntry( ctx );
          NopinionReqCheckTn0018Rett_Prepare( ctx );
          NopinionReqCheckTn0018Rett_TestVariant( ctx );
        }
      }
    }
  }
}

/** @} */
