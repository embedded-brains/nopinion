/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqFlowTrap
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
 * @defgroup NopinionReqFlowTrap spec:/nopinion/req/flow-trap
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqFlowTrap_Pre_Second_TrapAlways,
  NopinionReqFlowTrap_Pre_Second_TrapCond,
  NopinionReqFlowTrap_Pre_Second_Other,
  NopinionReqFlowTrap_Pre_Second_NA
} NopinionReqFlowTrap_Pre_Second;

typedef enum {
  NopinionReqFlowTrap_Pre_Indirect_Yes,
  NopinionReqFlowTrap_Pre_Indirect_No,
  NopinionReqFlowTrap_Pre_Indirect_NA
} NopinionReqFlowTrap_Pre_Indirect;

typedef enum {
  NopinionReqFlowTrap_Post_Finding_None,
  NopinionReqFlowTrap_Post_Finding_Definite,
  NopinionReqFlowTrap_Post_Finding_Possible,
  NopinionReqFlowTrap_Post_Finding_NA
} NopinionReqFlowTrap_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Second_NA : 1;
  uint8_t Pre_Indirect_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqFlowTrap_Entry;

/**
 * @brief Test context for spec:/nopinion/req/flow-trap test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the second instruction.
   */
  uint32_t second;

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
    NopinionReqFlowTrap_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqFlowTrap_Context;

static NopinionReqFlowTrap_Context NopinionReqFlowTrap_Instance;

static const char *const NopinionReqFlowTrap_PreDesc_Second[] =
  { "TrapAlways", "TrapCond", "Other", "NA" };

static const char *const NopinionReqFlowTrap_PreDesc_Indirect[] =
  { "Yes", "No", "NA" };

static const char *const *const NopinionReqFlowTrap_PreDesc[] = {
  NopinionReqFlowTrap_PreDesc_Second,
  NopinionReqFlowTrap_PreDesc_Indirect,
  NULL
};

static void NopinionReqFlowTrap_Pre_Second_Prepare(
  NopinionReqFlowTrap_Context   *ctx,
  NopinionReqFlowTrap_Pre_Second state
)
{
  switch ( state ) {
    case NopinionReqFlowTrap_Pre_Second_TrapAlways: {
      /*
       * While the second instruction is a trap always instruction.
       */
      ctx->second = TxTa();
      break;
    }

    case NopinionReqFlowTrap_Pre_Second_TrapCond: {
      /*
       * While the second instruction is a conditional trap instruction.
       */
      ctx->second = TxFormat3Imm( 2, 0x3a, 9, TX_G0, 0 );
      break;
    }

    case NopinionReqFlowTrap_Pre_Second_Other: {
      /*
       * While the second instruction transfers no control.
       */
      ctx->second = TxAdd();
      break;
    }

    case NopinionReqFlowTrap_Pre_Second_NA:
      break;
  }
}

static void NopinionReqFlowTrap_Pre_Indirect_Prepare(
  NopinionReqFlowTrap_Pre_Indirect state
)
{
  switch ( state ) {
    case NopinionReqFlowTrap_Pre_Indirect_Yes: {
      /*
       * While the option -i is given.
       */
      TxSetIncludeIndirect( true );
      break;
    }

    case NopinionReqFlowTrap_Pre_Indirect_No: {
      /*
       * While the option -i is not given.
       */
      TxSetIncludeIndirect( false );
      break;
    }

    case NopinionReqFlowTrap_Pre_Indirect_NA:
      break;
  }
}

static void NopinionReqFlowTrap_Post_Finding_Check(
  NopinionReqFlowTrap_Context     *ctx,
  NopinionReqFlowTrap_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqFlowTrap_Post_Finding_None: {
      /*
       * The errata checker shall report no finding for the first instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 0 );
      break;
    }

    case NopinionReqFlowTrap_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding for the first
       * instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 0, "TN-0009" ) );
      break;
    }

    case NopinionReqFlowTrap_Post_Finding_Possible: {
      /*
       * The errata checker shall report one possible finding for the first
       * instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 0, "TN-0009" ) );
      break;
    }

    case NopinionReqFlowTrap_Post_Finding_NA:
      break;
  }
}

static void NopinionReqFlowTrap_Prepare( NopinionReqFlowTrap_Context *ctx )
{
  TxImageInit( &ctx->image );
}

static void NopinionReqFlowTrap_Action( NopinionReqFlowTrap_Context *ctx )
{
  TxAppend( &ctx->image, TxSt() );
  TxAppend( &ctx->image, ctx->second );
  TxAppend( &ctx->image, TxSt() );
  TxAppend( &ctx->image, TxNop() );
  ctx->report = TxCheck( &ctx->image, NOTE_0009 );
}

static void NopinionReqFlowTrap_Cleanup( void )
{
  TxSetIncludeIndirect( false );
}

/* clang-format off */

static const NopinionReqFlowTrap_Entry
NopinionReqFlowTrap_Entries[] = {
  { 0, 0, 0, NopinionReqFlowTrap_Post_Finding_Definite },
  { 0, 0, 0, NopinionReqFlowTrap_Post_Finding_Possible },
  { 0, 0, 0, NopinionReqFlowTrap_Post_Finding_None }
};

static const uint8_t
NopinionReqFlowTrap_Map[] = {
  1, 2, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqFlowTrap_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqFlowTrap_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqFlowTrap_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqFlowTrap_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqFlowTrap_Scope,
  .initial_context = &NopinionReqFlowTrap_Instance
};

static inline NopinionReqFlowTrap_Entry NopinionReqFlowTrap_PopEntry(
  NopinionReqFlowTrap_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqFlowTrap_Entries[ NopinionReqFlowTrap_Map[ index ] ];
}

static void NopinionReqFlowTrap_TestVariant( NopinionReqFlowTrap_Context *ctx )
{
  NopinionReqFlowTrap_Pre_Second_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqFlowTrap_Pre_Indirect_Prepare( ctx->Map.pcs[ 1 ] );
  NopinionReqFlowTrap_Action( ctx );
  NopinionReqFlowTrap_Post_Finding_Check( ctx, ctx->Map.entry.Post_Finding );
}

/**
 * @fn void T_case_body_NopinionReqFlowTrap( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqFlowTrap, &NopinionReqFlowTrap_Fixture )
{
  NopinionReqFlowTrap_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqFlowTrap_Pre_Second_TrapAlways;
    ctx->Map.pcs[ 0 ] < NopinionReqFlowTrap_Pre_Second_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqFlowTrap_Pre_Indirect_Yes;
      ctx->Map.pcs[ 1 ] < NopinionReqFlowTrap_Pre_Indirect_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      ctx->Map.entry = NopinionReqFlowTrap_PopEntry( ctx );
      NopinionReqFlowTrap_Prepare( ctx );
      NopinionReqFlowTrap_TestVariant( ctx );
      NopinionReqFlowTrap_Cleanup();
    }
  }
}

/** @} */
