/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckTn0011
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
 * @defgroup NopinionReqCheckTn0011 spec:/nopinion/req/check-tn-0011
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckTn0011_Pre_Instruction_Swap,
  NopinionReqCheckTn0011_Pre_Instruction_Ldstub,
  NopinionReqCheckTn0011_Pre_Instruction_Casa,
  NopinionReqCheckTn0011_Pre_Instruction_Other,
  NopinionReqCheckTn0011_Pre_Instruction_NA
} NopinionReqCheckTn0011_Pre_Instruction;

typedef enum {
  NopinionReqCheckTn0011_Pre_Previous_Bicc,
  NopinionReqCheckTn0011_Pre_Previous_FBfcc,
  NopinionReqCheckTn0011_Pre_Previous_CBccc,
  NopinionReqCheckTn0011_Pre_Previous_Call,
  NopinionReqCheckTn0011_Pre_Previous_Jmpl,
  NopinionReqCheckTn0011_Pre_Previous_Other,
  NopinionReqCheckTn0011_Pre_Previous_None,
  NopinionReqCheckTn0011_Pre_Previous_NA
} NopinionReqCheckTn0011_Pre_Previous;

typedef enum {
  NopinionReqCheckTn0011_Pre_Address_Aligned,
  NopinionReqCheckTn0011_Pre_Address_Unaligned,
  NopinionReqCheckTn0011_Pre_Address_NA
} NopinionReqCheckTn0011_Pre_Address;

typedef enum {
  NopinionReqCheckTn0011_Pre_File_Executable,
  NopinionReqCheckTn0011_Pre_File_RelocatableAligned,
  NopinionReqCheckTn0011_Pre_File_RelocatableUnaligned,
  NopinionReqCheckTn0011_Pre_File_NA
} NopinionReqCheckTn0011_Pre_File;

typedef enum {
  NopinionReqCheckTn0011_Post_DelaySlot_None,
  NopinionReqCheckTn0011_Post_DelaySlot_Definite,
  NopinionReqCheckTn0011_Post_DelaySlot_NA
} NopinionReqCheckTn0011_Post_DelaySlot;

typedef enum {
  NopinionReqCheckTn0011_Post_Alignment_None,
  NopinionReqCheckTn0011_Post_Alignment_Definite,
  NopinionReqCheckTn0011_Post_Alignment_Possible,
  NopinionReqCheckTn0011_Post_Alignment_NA
} NopinionReqCheckTn0011_Post_Alignment;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Instruction_NA : 1;
  uint16_t Pre_Previous_NA : 1;
  uint16_t Pre_Address_NA : 1;
  uint16_t Pre_File_NA : 1;
  uint16_t Post_DelaySlot : 2;
  uint16_t Post_Alignment : 2;
} NopinionReqCheckTn0011_Entry;

/**
 * @brief Test context for spec:/nopinion/req/check-tn-0011 test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the instruction.
   */
  uint32_t instruction;

  /**
   * @brief This member contains the instruction before the instruction.
   */
  uint32_t previous;

  /**
   * @brief This member is true, if the instruction is the first instruction.
   */
  bool first;

  /**
   * @brief This member is true, if the address of the instruction is
   *   unaligned.
   */
  bool unaligned;

  /**
   * @brief This member contains the offset of the instruction.
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
    NopinionReqCheckTn0011_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckTn0011_Context;

static NopinionReqCheckTn0011_Context NopinionReqCheckTn0011_Instance;

static const char *const NopinionReqCheckTn0011_PreDesc_Instruction[] =
  { "Swap", "Ldstub", "Casa", "Other", "NA" };

static const char *const NopinionReqCheckTn0011_PreDesc_Previous[] =
  { "Bicc", "FBfcc", "CBccc", "Call", "Jmpl", "Other", "None", "NA" };

static const char *const NopinionReqCheckTn0011_PreDesc_Address[] =
  { "Aligned", "Unaligned", "NA" };

static const char *const NopinionReqCheckTn0011_PreDesc_File[] =
  { "Executable", "RelocatableAligned", "RelocatableUnaligned", "NA" };

static const char *const *const NopinionReqCheckTn0011_PreDesc[] = {
  NopinionReqCheckTn0011_PreDesc_Instruction,
  NopinionReqCheckTn0011_PreDesc_Previous,
  NopinionReqCheckTn0011_PreDesc_Address,
  NopinionReqCheckTn0011_PreDesc_File,
  NULL
};

static void NopinionReqCheckTn0011_Pre_Instruction_Prepare(
  NopinionReqCheckTn0011_Context        *ctx,
  NopinionReqCheckTn0011_Pre_Instruction state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0011_Pre_Instruction_Swap: {
      /*
       * While the instruction is a SWAP instruction.
       */
      ctx->instruction = TxSwap();
      break;
    }

    case NopinionReqCheckTn0011_Pre_Instruction_Ldstub: {
      /*
       * While the instruction is an LDSTUB instruction.
       */
      ctx->instruction = TxLdstub();
      break;
    }

    case NopinionReqCheckTn0011_Pre_Instruction_Casa: {
      /*
       * While the instruction is a CASA instruction.
       */
      ctx->instruction = TxCasa();
      break;
    }

    case NopinionReqCheckTn0011_Pre_Instruction_Other: {
      /*
       * While the instruction is no atomic instruction and transfers no
       * control.
       */
      ctx->instruction = TxLd();
      break;
    }

    case NopinionReqCheckTn0011_Pre_Instruction_NA:
      break;
  }
}

static void NopinionReqCheckTn0011_Pre_Previous_Prepare(
  NopinionReqCheckTn0011_Context     *ctx,
  NopinionReqCheckTn0011_Pre_Previous state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0011_Pre_Previous_Bicc: {
      /*
       * While the instruction before the instruction is a branch on integer
       * condition codes.
       */
      ctx->previous = TxBicc( 1, false, 2 );
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_FBfcc: {
      /*
       * While the instruction before the instruction is a branch on
       * floating-point condition codes.
       */
      ctx->previous = TxFbfcc( false, 2 );
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_CBccc: {
      /*
       * While the instruction before the instruction is a branch on
       * coprocessor condition codes.
       */
      ctx->previous = TxCbccc( 2 );
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_Call: {
      /*
       * While the instruction before the instruction is a CALL instruction.
       */
      ctx->previous = TxCall( 2 );
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_Jmpl: {
      /*
       * While the instruction before the instruction is a JMPL instruction.
       */
      ctx->previous = TxJmpl();
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_Other: {
      /*
       * While the instruction before the instruction transfers no control.
       */
      ctx->previous = TxAdd();
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_None: {
      /*
       * While the instruction is the first instruction of the code section.
       */
      ctx->first = true;
      break;
    }

    case NopinionReqCheckTn0011_Pre_Previous_NA:
      break;
  }
}

static void NopinionReqCheckTn0011_Pre_Address_Prepare(
  NopinionReqCheckTn0011_Context    *ctx,
  NopinionReqCheckTn0011_Pre_Address state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0011_Pre_Address_Aligned: {
      /*
       * While the address of the instruction is an integral multiple of 16.
       */
      ctx->unaligned = false;
      break;
    }

    case NopinionReqCheckTn0011_Pre_Address_Unaligned: {
      /*
       * While the address of the instruction is no integral multiple of 16.
       */
      ctx->unaligned = true;
      break;
    }

    case NopinionReqCheckTn0011_Pre_Address_NA:
      break;
  }
}

static void NopinionReqCheckTn0011_Pre_File_Prepare(
  NopinionReqCheckTn0011_Context *ctx,
  NopinionReqCheckTn0011_Pre_File state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0011_Pre_File_Executable: {
      /*
       * While the ELF file is an executable.
       */
      ctx->image.executable = true;
      ctx->image.address = 0x40000000;
      break;
    }

    case NopinionReqCheckTn0011_Pre_File_RelocatableAligned: {
      /*
       * While the ELF file is relocatable, while the alignment of the code
       * section is an integral multiple of 16.
       */
      ctx->image.alignment = 16;
      break;
    }

    case NopinionReqCheckTn0011_Pre_File_RelocatableUnaligned: {
      /*
       * While the ELF file is relocatable, while the alignment of the code
       * section is less than 16.
       */
      ctx->image.alignment = 8;
      break;
    }

    case NopinionReqCheckTn0011_Pre_File_NA:
      break;
  }
}

static void NopinionReqCheckTn0011_Post_DelaySlot_Check(
  NopinionReqCheckTn0011_Context       *ctx,
  NopinionReqCheckTn0011_Post_DelaySlot state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0011_Post_DelaySlot_None: {
      /*
       * The errata checker shall report no finding of an atomic instruction in
       * a delay slot.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "atomic-in-delay-slot" ),
        0
      );
      break;
    }

    case NopinionReqCheckTn0011_Post_DelaySlot_Definite: {
      /*
       * The errata checker shall report one definite finding of an atomic
       * instruction in a delay slot for the instruction.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "atomic-in-delay-slot" ),
        1
      );
      T_false(
        TxIsPossibleAt( ctx->report, ctx->offset, "atomic-in-delay-slot" )
      );
      break;
    }

    case NopinionReqCheckTn0011_Post_DelaySlot_NA:
      break;
  }
}

static void NopinionReqCheckTn0011_Post_Alignment_Check(
  NopinionReqCheckTn0011_Context       *ctx,
  NopinionReqCheckTn0011_Post_Alignment state
)
{
  switch ( state ) {
    case NopinionReqCheckTn0011_Post_Alignment_None: {
      /*
       * The errata checker shall report no finding of an atomic instruction
       * which does not start a 16-byte block.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "atomic-not-aligned" ),
        0
      );
      break;
    }

    case NopinionReqCheckTn0011_Post_Alignment_Definite: {
      /*
       * The errata checker shall report one definite finding of an atomic
       * instruction which does not start a 16-byte block for the instruction.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "atomic-not-aligned" ),
        1
      );
      T_false(
        TxIsPossibleAt( ctx->report, ctx->offset, "atomic-not-aligned" )
      );
      break;
    }

    case NopinionReqCheckTn0011_Post_Alignment_Possible: {
      /*
       * The errata checker shall report one possible finding of an atomic
       * instruction which does not start a 16-byte block for the instruction.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "atomic-not-aligned" ),
        1
      );
      T_true(
        TxIsPossibleAt( ctx->report, ctx->offset, "atomic-not-aligned" )
      );
      break;
    }

    case NopinionReqCheckTn0011_Post_Alignment_NA:
      break;
  }
}

static void NopinionReqCheckTn0011_Prepare(
  NopinionReqCheckTn0011_Context *ctx
)
{
  TxImageInit( &ctx->image );
  ctx->first = false;
}

static void NopinionReqCheckTn0011_Action(
  NopinionReqCheckTn0011_Context *ctx
)
{
  size_t i;
  size_t index;

  if ( ctx->first ) {
    index = 0;

    if ( ctx->unaligned ) {
      ctx->image.address += 8;
    }
  } else {
    index = ctx->unaligned ? 6 : 4;

    for ( i = 0; i < index - 1; ++i ) {
      TxAppend( &ctx->image, TxNop() );
    }

    TxAppend( &ctx->image, ctx->previous );
  }

  TxAppend( &ctx->image, ctx->instruction );
  TxAppend( &ctx->image, TxNop() );
  TxAppend( &ctx->image, TxNop() );
  ctx->offset = (uint32_t) ( 4 * index );
  ctx->report = TxCheck( &ctx->image, NOTE_0011 );
}

/* clang-format off */

static const NopinionReqCheckTn0011_Entry
NopinionReqCheckTn0011_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_None,
    NopinionReqCheckTn0011_Post_Alignment_None },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_Definite,
    NopinionReqCheckTn0011_Post_Alignment_None },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_Definite,
    NopinionReqCheckTn0011_Post_Alignment_Possible },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_Definite,
    NopinionReqCheckTn0011_Post_Alignment_Definite },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_None,
    NopinionReqCheckTn0011_Post_Alignment_Possible },
  { 0, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_None,
    NopinionReqCheckTn0011_Post_Alignment_Definite },
  { 1, 0, 0, 0, 0, NopinionReqCheckTn0011_Post_DelaySlot_NA,
    NopinionReqCheckTn0011_Post_Alignment_NA }
};

static const uint8_t
NopinionReqCheckTn0011_Map[] = {
  1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 0, 0,
  4, 5, 5, 4, 0, 0, 4, 5, 5, 4, 0, 0, 4, 5, 6, 6, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3,
  3, 2, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 0, 0, 4, 5, 5, 4, 0, 0, 4, 5, 5, 4,
  0, 0, 4, 5, 6, 6, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, 1, 2, 3, 3, 2, 1, 1,
  2, 3, 3, 2, 0, 0, 4, 5, 5, 4, 0, 0, 4, 5, 5, 4, 0, 0, 4, 5, 6, 6, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6
};

/* clang-format on */

static size_t NopinionReqCheckTn0011_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCheckTn0011_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqCheckTn0011_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqCheckTn0011_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckTn0011_Scope,
  .initial_context = &NopinionReqCheckTn0011_Instance
};

static inline NopinionReqCheckTn0011_Entry NopinionReqCheckTn0011_PopEntry(
  NopinionReqCheckTn0011_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckTn0011_Entries[ NopinionReqCheckTn0011_Map[ index ] ];
}

static void NopinionReqCheckTn0011_TestVariant(
  NopinionReqCheckTn0011_Context *ctx
)
{
  NopinionReqCheckTn0011_Pre_Instruction_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckTn0011_Pre_Previous_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckTn0011_Pre_Address_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckTn0011_Pre_File_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqCheckTn0011_Action( ctx );
  NopinionReqCheckTn0011_Post_DelaySlot_Check(
    ctx,
    ctx->Map.entry.Post_DelaySlot
  );
  NopinionReqCheckTn0011_Post_Alignment_Check(
    ctx,
    ctx->Map.entry.Post_Alignment
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckTn0011( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqCheckTn0011, &NopinionReqCheckTn0011_Fixture )
{
  NopinionReqCheckTn0011_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCheckTn0011_Pre_Instruction_Swap;
    ctx->Map.pcs[ 0 ] < NopinionReqCheckTn0011_Pre_Instruction_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCheckTn0011_Pre_Previous_Bicc;
      ctx->Map.pcs[ 1 ] < NopinionReqCheckTn0011_Pre_Previous_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqCheckTn0011_Pre_Address_Aligned;
        ctx->Map.pcs[ 2 ] < NopinionReqCheckTn0011_Pre_Address_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        for (
          ctx->Map.pcs[ 3 ] = NopinionReqCheckTn0011_Pre_File_Executable;
          ctx->Map.pcs[ 3 ] < NopinionReqCheckTn0011_Pre_File_NA;
          ++ctx->Map.pcs[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqCheckTn0011_PopEntry( ctx );

          if ( ctx->Map.entry.Skip ) {
            continue;
          }

          NopinionReqCheckTn0011_Prepare( ctx );
          NopinionReqCheckTn0011_TestVariant( ctx );
        }
      }
    }
  }
}

/** @} */
