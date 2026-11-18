/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0013Dependency
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
 * @defgroup NopinionReqCheckTn0013Dependency \
 *   spec:/nopinion/req/check-tn-0013-dependency
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0013Dependency_Pre_Second_Independent,
  NopinionReqCheckTn0013Dependency_Pre_Second_ReadsDst,
  NopinionReqCheckTn0013Dependency_Pre_Second_WritesDst,
  NopinionReqCheckTn0013Dependency_Pre_Second_ReadsHalf,
  NopinionReqCheckTn0013Dependency_Pre_Second_NA
} NopinionReqCheckTn0013Dependency_Pre_Second;

typedef enum {
  NopinionReqCheckTn0013Dependency_Pre_Third_Other,
  NopinionReqCheckTn0013Dependency_Pre_Third_FPop2Independent,
  NopinionReqCheckTn0013Dependency_Pre_Third_FPop2ReadsDst,
  NopinionReqCheckTn0013Dependency_Pre_Third_StoreIndependent,
  NopinionReqCheckTn0013Dependency_Pre_Third_StoreReadsDst,
  NopinionReqCheckTn0013Dependency_Pre_Third_NA
} NopinionReqCheckTn0013Dependency_Pre_Third;

typedef enum {
  NopinionReqCheckTn0013Dependency_Pre_Fourth_Independent,
  NopinionReqCheckTn0013Dependency_Pre_Fourth_ReadsDst,
  NopinionReqCheckTn0013Dependency_Pre_Fourth_NA
} NopinionReqCheckTn0013Dependency_Pre_Fourth;

typedef enum {
  NopinionReqCheckTn0013Dependency_Pre_Fifth_Independent,
  NopinionReqCheckTn0013Dependency_Pre_Fifth_ReadsDst,
  NopinionReqCheckTn0013Dependency_Pre_Fifth_WritesDst,
  NopinionReqCheckTn0013Dependency_Pre_Fifth_NA
} NopinionReqCheckTn0013Dependency_Pre_Fifth;

typedef enum {
  NopinionReqCheckTn0013Dependency_Post_Finding_None,
  NopinionReqCheckTn0013Dependency_Post_Finding_Definite,
  NopinionReqCheckTn0013Dependency_Post_Finding_NA
} NopinionReqCheckTn0013Dependency_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Second_NA : 1;
  uint8_t Pre_Third_NA : 1;
  uint8_t Pre_Fourth_NA : 1;
  uint8_t Pre_Fifth_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0013Dependency_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0013-dependency test
 *   case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the instructions of the code section.
   */
  uint32_t code[ 5 ];

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
    NopinionReqCheckTn0013Dependency_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0013Dependency_Context;

static NopinionReqCheckTn0013Dependency_Context
  NopinionReqCheckTn0013Dependency_Instance;

static const char *const NopinionReqCheckTn0013Dependency_PreDesc_Second[] =
  { "Independent", "ReadsDst", "WritesDst", "ReadsHalf", "NA" };

static const char *const NopinionReqCheckTn0013Dependency_PreDesc_Third[] = {
  "Other",
  "FPop2Independent",
  "FPop2ReadsDst",
  "StoreIndependent",
  "StoreReadsDst",
  "NA"
};

static const char *const NopinionReqCheckTn0013Dependency_PreDesc_Fourth[] =
  { "Independent", "ReadsDst", "NA" };

static const char *const NopinionReqCheckTn0013Dependency_PreDesc_Fifth[] =
  { "Independent", "ReadsDst", "WritesDst", "NA" };

static const char *const *const NopinionReqCheckTn0013Dependency_PreDesc[] = {
  NopinionReqCheckTn0013Dependency_PreDesc_Second,
  NopinionReqCheckTn0013Dependency_PreDesc_Third,
  NopinionReqCheckTn0013Dependency_PreDesc_Fourth,
  NopinionReqCheckTn0013Dependency_PreDesc_Fifth,
  NULL
};

static void NopinionReqCheckTn0013Dependency_Pre_Second_Prepare(
  NopinionReqCheckTn0013Dependency_Context   *ctx,
  NopinionReqCheckTn0013Dependency_Pre_Second state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0013Dependency_Pre_Second_Independent: {
      /*
       * While the second instruction is an FPop1 instruction which neither
       * reads nor writes a register of the destination of the first
       * instruction.
       */
      ctx->code[ 1 ] = TxFpop1( TX_FADDD, 2, 4, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Second_ReadsDst: {
      /*
       * While the second instruction is an FPop1 instruction which reads the
       * destination of the first instruction.
       */
      ctx->code[ 1 ] = TxFpop1( TX_FADDD, 2, 16, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Second_WritesDst: {
      /*
       * While the second instruction is an FPop1 instruction which writes the
       * destination of the first instruction.
       */
      ctx->code[ 1 ] = TxFpop1( TX_FADDD, 16, 4, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Second_ReadsHalf: {
      /*
       * While the second instruction is an FPop1 instruction which reads one
       * single register of the double destination of the first instruction.
       */
      ctx->code[ 1 ] = TxFpop1( TX_FADDS, 2, 17, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Second_NA:
      break;
  }
}

static void NopinionReqCheckTn0013Dependency_Pre_Third_Prepare(
  NopinionReqCheckTn0013Dependency_Context  *ctx,
  NopinionReqCheckTn0013Dependency_Pre_Third state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0013Dependency_Pre_Third_Other: {
      /*
       * While the third instruction is no floating-point instruction and
       * transfers no control.
       */
      ctx->code[ 2 ] = TxAdd();
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Third_FPop2Independent: {
      /*
       * While the third instruction is an FPop2 instruction which reads no
       * register of the destination of the first instruction.
       */
      ctx->code[ 2 ] = TxFpop2( TX_FCMPS, 4, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Third_FPop2ReadsDst: {
      /*
       * While the third instruction is an FPop2 instruction which reads a
       * register of the destination of the first instruction.
       */
      ctx->code[ 2 ] = TxFpop2( TX_FCMPS, 17, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Third_StoreIndependent: {
      /*
       * While the third instruction is a store of a floating-point register
       * which reads no register of the destination of the first instruction.
       */
      ctx->code[ 2 ] = TxStfReg( 4 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Third_StoreReadsDst: {
      /*
       * While the third instruction is a store of a floating-point register
       * which reads a register of the destination of the first instruction.
       */
      ctx->code[ 2 ] = TxStfReg( 16 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Third_NA:
      break;
  }
}

static void NopinionReqCheckTn0013Dependency_Pre_Fourth_Prepare(
  NopinionReqCheckTn0013Dependency_Context   *ctx,
  NopinionReqCheckTn0013Dependency_Pre_Fourth state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0013Dependency_Pre_Fourth_Independent: {
      /*
       * While the fourth instruction is an FPop1 instruction which neither
       * reads nor writes a register of the destination of the first
       * instruction.
       */
      ctx->code[ 3 ] = TxFpop1( TX_FADDD, 8, 4, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Fourth_ReadsDst: {
      /*
       * While the fourth instruction is an FPop1 instruction which reads the
       * destination of the first instruction.
       */
      ctx->code[ 3 ] = TxFpop1( TX_FADDD, 8, 16, 6 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Fourth_NA:
      break;
  }
}

static void NopinionReqCheckTn0013Dependency_Pre_Fifth_Prepare(
  NopinionReqCheckTn0013Dependency_Context  *ctx,
  NopinionReqCheckTn0013Dependency_Pre_Fifth state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0013Dependency_Pre_Fifth_Independent: {
      /*
       * While the fifth instruction is an FDIV instruction which neither reads
       * nor writes a register of the destination of the first instruction.
       */
      ctx->code[ 4 ] = TxFpop1( TX_FDIVD, 24, 10, 4 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Fifth_ReadsDst: {
      /*
       * While the fifth instruction is an FDIV instruction which reads the
       * destination of the first instruction.
       */
      ctx->code[ 4 ] = TxFpop1( TX_FDIVD, 24, 16, 4 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Fifth_WritesDst: {
      /*
       * While the fifth instruction is an FDIV instruction which writes the
       * destination of the first instruction.
       */
      ctx->code[ 4 ] = TxFpop1( TX_FDIVD, 16, 10, 4 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Pre_Fifth_NA:
      break;
  }
}

static void NopinionReqCheckTn0013Dependency_Post_Finding_Check(
  NopinionReqCheckTn0013Dependency_Context     *ctx,
  NopinionReqCheckTn0013Dependency_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0013Dependency_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of the missing FDIV/FSQRT
       * result erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0013" ), 0 );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of the missing
       * FDIV/FSQRT result erratum for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0013" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "TN-0013" ) );
      break;
    }

    case NopinionReqCheckTn0013Dependency_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0013Dependency_Prepare(
  NopinionReqCheckTn0013Dependency_Context *ctx
)
{
  TxImageInit( &ctx->image );
}

static void NopinionReqCheckTn0013Dependency_Action(
  NopinionReqCheckTn0013Dependency_Context *ctx
)
{
  size_t i;

  ctx->code[ 0 ] = TxFpop1( TX_FDIVD, 16, 12, 14 );

  for ( i = 0; i < T_ARRAY_SIZE( ctx->code ); ++i ) {
    TxAppend( &ctx->image, ctx->code[ i ] );
  }

  ctx->report = TxCheck( &ctx->image, NOTE_0013 );
}

/* clang-format off */

static const NopinionReqCheckTn0013Dependency_Entry
NopinionReqCheckTn0013Dependency_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0013Dependency_Post_Finding_None },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0013Dependency_Post_Finding_Definite }
};

static const uint8_t
NopinionReqCheckTn0013Dependency_Map[] = {
  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqCheckTn0013Dependency_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqCheckTn0013Dependency_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckTn0013Dependency_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0013Dependency_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0013Dependency_Scope,
  .initial_context = &NopinionReqCheckTn0013Dependency_Instance
};

static inline NopinionReqCheckTn0013Dependency_Entry
NopinionReqCheckTn0013Dependency_PopEntry(
  NopinionReqCheckTn0013Dependency_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0013Dependency_Entries
    [ NopinionReqCheckTn0013Dependency_Map[ index ] ];
}

static void NopinionReqCheckTn0013Dependency_TestVariant(
  NopinionReqCheckTn0013Dependency_Context *ctx
)
{
  NopinionReqCheckTn0013Dependency_Pre_Second_Prepare(
    ctx,
    ctx->Map.pcs[ 0 ]
  );
  NopinionReqCheckTn0013Dependency_Pre_Third_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0013Dependency_Pre_Fourth_Prepare(
    ctx,
    ctx->Map.pcs[ 2 ]
  );
  NopinionReqCheckTn0013Dependency_Pre_Fifth_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqCheckTn0013Dependency_Action( ctx );
  NopinionReqCheckTn0013Dependency_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0013Dependency( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckTn0013Dependency,
  &NopinionReqCheckTn0013Dependency_Fixture
)
{
  NopinionReqCheckTn0013Dependency_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] =
      NopinionReqCheckTn0013Dependency_Pre_Second_Independent;
    ctx->Map.pcs[ 0 ] < NopinionReqCheckTn0013Dependency_Pre_Second_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCheckTn0013Dependency_Pre_Third_Other;
      ctx->Map.pcs[ 1 ] < NopinionReqCheckTn0013Dependency_Pre_Third_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] =
          NopinionReqCheckTn0013Dependency_Pre_Fourth_Independent;
        ctx->Map.pcs[ 2 ] < NopinionReqCheckTn0013Dependency_Pre_Fourth_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        for (
          ctx->Map.pcs[ 3 ] =
            NopinionReqCheckTn0013Dependency_Pre_Fifth_Independent;
          ctx->Map.pcs[ 3 ] < NopinionReqCheckTn0013Dependency_Pre_Fifth_NA;
          ++ctx->Map.pcs[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqCheckTn0013Dependency_PopEntry( ctx );
          NopinionReqCheckTn0013Dependency_Prepare( ctx );
          NopinionReqCheckTn0013Dependency_TestVariant( ctx );
        }
      }
    }
  }
}

/** @} */
