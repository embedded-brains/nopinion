/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0018Trap
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
 * @defgroup NopinionReqCheckTn0018Trap spec:/nopinion/req/check-tn-0018-trap
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0018Trap_Pre_Trap_Always,
  NopinionReqCheckTn0018Trap_Pre_Trap_Conditional,
  NopinionReqCheckTn0018Trap_Pre_Trap_Never,
  NopinionReqCheckTn0018Trap_Pre_Trap_Other,
  NopinionReqCheckTn0018Trap_Pre_Trap_NA
} NopinionReqCheckTn0018Trap_Pre_Trap;

typedef enum {
  NopinionReqCheckTn0018Trap_Pre_Slot_None,
  NopinionReqCheckTn0018Trap_Pre_Slot_BranchAlways,
  NopinionReqCheckTn0018Trap_Pre_Slot_BranchConditional,
  NopinionReqCheckTn0018Trap_Pre_Slot_Jmpl,
  NopinionReqCheckTn0018Trap_Pre_Slot_CallRelocated,
  NopinionReqCheckTn0018Trap_Pre_Slot_NA
} NopinionReqCheckTn0018Trap_Pre_Slot;

typedef enum {
  NopinionReqCheckTn0018Trap_Pre_Next_Jmpl,
  NopinionReqCheckTn0018Trap_Pre_Next_Other,
  NopinionReqCheckTn0018Trap_Pre_Next_Absent,
  NopinionReqCheckTn0018Trap_Pre_Next_NA
} NopinionReqCheckTn0018Trap_Pre_Next;

typedef enum {
  NopinionReqCheckTn0018Trap_Pre_Indirect_Excluded,
  NopinionReqCheckTn0018Trap_Pre_Indirect_Included,
  NopinionReqCheckTn0018Trap_Pre_Indirect_NA
} NopinionReqCheckTn0018Trap_Pre_Indirect;

typedef enum {
  NopinionReqCheckTn0018Trap_Post_Finding_None,
  NopinionReqCheckTn0018Trap_Post_Finding_Definite,
  NopinionReqCheckTn0018Trap_Post_Finding_Possible,
  NopinionReqCheckTn0018Trap_Post_Finding_NA
} NopinionReqCheckTn0018Trap_Post_Finding;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Trap_NA : 1;
  uint8_t Pre_Slot_NA : 1;
  uint8_t Pre_Next_NA : 1;
  uint8_t Pre_Indirect_NA : 1;
  uint8_t Post_Finding : 2;
} NopinionReqCheckTn0018Trap_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0018-trap test case.
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
  uint32_t trap;

  /**
   * @brief This member contains the third and the fourth instruction.
   */
  uint32_t next;

  /**
   * @brief This member is true, if the code section ends after the second
   *   instruction.
   */
  bool absent;

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
    NopinionReqCheckTn0018Trap_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0018Trap_Context;

static NopinionReqCheckTn0018Trap_Context NopinionReqCheckTn0018Trap_Instance;

static const char *const NopinionReqCheckTn0018Trap_PreDesc_Trap[] =
  { "Always", "Conditional", "Never", "Other", "NA" };

static const char *const NopinionReqCheckTn0018Trap_PreDesc_Slot[] = {
  "None",
  "BranchAlways",
  "BranchConditional",
  "Jmpl",
  "CallRelocated",
  "NA"
};

static const char *const NopinionReqCheckTn0018Trap_PreDesc_Next[] =
  { "Jmpl", "Other", "Absent", "NA" };

static const char *const NopinionReqCheckTn0018Trap_PreDesc_Indirect[] =
  { "Excluded", "Included", "NA" };

static const char *const *const NopinionReqCheckTn0018Trap_PreDesc[] = {
  NopinionReqCheckTn0018Trap_PreDesc_Trap,
  NopinionReqCheckTn0018Trap_PreDesc_Slot,
  NopinionReqCheckTn0018Trap_PreDesc_Next,
  NopinionReqCheckTn0018Trap_PreDesc_Indirect,
  NULL
};

static void NopinionReqCheckTn0018Trap_Pre_Trap_Prepare(
  NopinionReqCheckTn0018Trap_Context *ctx,
  NopinionReqCheckTn0018Trap_Pre_Trap state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Trap_Pre_Trap_Always: {
      /*
       * While the second instruction of the code section is a trap always
       * instruction.
       */
      ctx->trap = TxTicc( 8 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Trap_Conditional: {
      /*
       * While the second instruction of the code section is a trap instruction
       * with a condition other than always and never.
       */
      ctx->trap = TxTicc( 9 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Trap_Never: {
      /*
       * While the second instruction of the code section is a trap never
       * instruction.
       */
      ctx->trap = TxTicc( 0 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Trap_Other: {
      /*
       * While the second instruction of the code section is no trap
       * instruction and transfers no control.
       */
      ctx->trap = TxAdd();
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Trap_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Trap_Pre_Slot_Prepare(
  NopinionReqCheckTn0018Trap_Context *ctx,
  NopinionReqCheckTn0018Trap_Pre_Slot state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Trap_Pre_Slot_None: {
      /*
       * While the first instruction of the code section transfers no control.
       */
      ctx->first = TxNop();
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Slot_BranchAlways: {
      /*
       * While the first instruction of the code section is a branch always
       * instruction without annulment to the fourth instruction.
       */
      ctx->first = TxBicc( 8, false, 3 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Slot_BranchConditional: {
      /*
       * While the first instruction of the code section is a conditional
       * branch instruction without annulment to the fourth instruction.
       */
      ctx->first = TxBicc( 9, false, 3 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Slot_Jmpl: {
      /*
       * While the first instruction of the code section is a JMPL instruction.
       */
      ctx->first = TxJmpl();
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Slot_CallRelocated: {
      /*
       * While the first instruction of the code section is a CALL instruction
       * with a relocation.
       */
      ctx->first = TxCall( 3 );
      TxAddRelocation( &ctx->image, 0 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Slot_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Trap_Pre_Next_Prepare(
  NopinionReqCheckTn0018Trap_Context *ctx,
  NopinionReqCheckTn0018Trap_Pre_Next state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Trap_Pre_Next_Jmpl: {
      /*
       * While the third and the fourth instruction of the code section are
       * JMPL instructions.
       */
      ctx->next = TxJmpl();
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Next_Other: {
      /*
       * While the third and the fourth instruction of the code section
       * transfer no control.
       */
      ctx->next = TxAdd();
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Next_Absent: {
      /*
       * While the code section ends after the second instruction.
       */
      ctx->absent = true;
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Next_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Trap_Pre_Indirect_Prepare(
  NopinionReqCheckTn0018Trap_Pre_Indirect state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Trap_Pre_Indirect_Excluded: {
      /*
       * While the option -i is not given.
       */
      TxSetIncludeIndirect( false );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Indirect_Included: {
      /*
       * While the option -i is given.
       */
      TxSetIncludeIndirect( true );
      break;
    }

    case NopinionReqCheckTn0018Trap_Pre_Indirect_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Trap_Post_Finding_Check(
  NopinionReqCheckTn0018Trap_Context     *ctx,
  NopinionReqCheckTn0018Trap_Post_Finding state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0018Trap_Post_Finding_None: {
      /*
       * The errata checker shall report no finding of a trap instruction which
       * returns to a JMPL instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 4, "trap-returns-to-jmpl" ), 0 );
      break;
    }

    case NopinionReqCheckTn0018Trap_Post_Finding_Definite: {
      /*
       * The errata checker shall report one definite finding of a trap
       * instruction which returns to a JMPL instruction for the second
       * instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 4, "trap-returns-to-jmpl" ), 1 );
      T_false( TxIsPossibleAt( ctx->report, 4, "trap-returns-to-jmpl" ) );
      break;
    }

    case NopinionReqCheckTn0018Trap_Post_Finding_Possible: {
      /*
       * The errata checker shall report one possible finding of a trap
       * instruction which returns to a JMPL instruction for the second
       * instruction.
       */
      T_eq_int( TxCountAt( ctx->report, 4, "trap-returns-to-jmpl" ), 1 );
      T_true( TxIsPossibleAt( ctx->report, 4, "trap-returns-to-jmpl" ) );
      break;
    }

    case NopinionReqCheckTn0018Trap_Post_Finding_NA:
      break;
  }
}

static void NopinionReqCheckTn0018Trap_Prepare(
  NopinionReqCheckTn0018Trap_Context *ctx
)
{
  TxImageInit( &ctx->image );
  ctx->absent = false;
}

static void NopinionReqCheckTn0018Trap_Action(
  NopinionReqCheckTn0018Trap_Context *ctx
)
{
  TxAppend( &ctx->image, ctx->first );
  TxAppend( &ctx->image, ctx->trap );

  if ( !ctx->absent ) {
    TxAppend( &ctx->image, ctx->next );
    TxAppend( &ctx->image, ctx->next );
  }

  ctx->report = TxCheck( &ctx->image, NOTE_0018 );
}

static void NopinionReqCheckTn0018Trap_Cleanup( void )
{
  TxSetIncludeIndirect( false );
}

/* clang-format off */

static const NopinionReqCheckTn0018Trap_Entry
NopinionReqCheckTn0018Trap_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0018Trap_Post_Finding_None },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0018Trap_Post_Finding_Possible },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0018Trap_Post_Finding_Definite }
};

static const uint8_t
NopinionReqCheckTn0018Trap_Map[] = {
  2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 0, 1, 0, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqCheckTn0018Trap_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqCheckTn0018Trap_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckTn0018Trap_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0018Trap_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0018Trap_Scope,
  .initial_context = &NopinionReqCheckTn0018Trap_Instance
};

static inline NopinionReqCheckTn0018Trap_Entry
NopinionReqCheckTn0018Trap_PopEntry( NopinionReqCheckTn0018Trap_Context *ctx )
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0018Trap_Entries
    [ NopinionReqCheckTn0018Trap_Map[ index ] ];
}

static void NopinionReqCheckTn0018Trap_TestVariant(
  NopinionReqCheckTn0018Trap_Context *ctx
)
{
  NopinionReqCheckTn0018Trap_Pre_Trap_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0018Trap_Pre_Slot_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0018Trap_Pre_Next_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckTn0018Trap_Pre_Indirect_Prepare( ctx->Map.pcs[ 3 ] );
  NopinionReqCheckTn0018Trap_Action( ctx );
  NopinionReqCheckTn0018Trap_Post_Finding_Check(
    ctx,
    ctx->Map.entry.Post_Finding
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0018Trap( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckTn0018Trap,
  &NopinionReqCheckTn0018Trap_Fixture
)
{
  NopinionReqCheckTn0018Trap_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCheckTn0018Trap_Pre_Trap_Always;
    ctx->Map.pcs[ 0 ] < NopinionReqCheckTn0018Trap_Pre_Trap_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCheckTn0018Trap_Pre_Slot_None;
      ctx->Map.pcs[ 1 ] < NopinionReqCheckTn0018Trap_Pre_Slot_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqCheckTn0018Trap_Pre_Next_Jmpl;
        ctx->Map.pcs[ 2 ] < NopinionReqCheckTn0018Trap_Pre_Next_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        for (
          ctx->Map.pcs[ 3 ] = NopinionReqCheckTn0018Trap_Pre_Indirect_Excluded;
          ctx->Map.pcs[ 3 ] < NopinionReqCheckTn0018Trap_Pre_Indirect_NA;
          ++ctx->Map.pcs[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqCheckTn0018Trap_PopEntry( ctx );
          NopinionReqCheckTn0018Trap_Prepare( ctx );
          NopinionReqCheckTn0018Trap_TestVariant( ctx );
          NopinionReqCheckTn0018Trap_Cleanup();
        }
      }
    }
  }
}

/** @} */
