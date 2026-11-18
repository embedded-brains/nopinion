/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCheckPowerDown
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
 * @defgroup NopinionReqCheckPowerDown spec:/nopinion/req/check-power-down
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCheckPowerDown_Pre_Write_Asr19,
  NopinionReqCheckPowerDown_Pre_Write_Asr18,
  NopinionReqCheckPowerDown_Pre_Write_Y,
  NopinionReqCheckPowerDown_Pre_Write_NA
} NopinionReqCheckPowerDown_Pre_Write;

typedef enum {
  NopinionReqCheckPowerDown_Pre_Load_Bypass,
  NopinionReqCheckPowerDown_Pre_Load_OtherAsi,
  NopinionReqCheckPowerDown_Pre_Load_OtherRegister,
  NopinionReqCheckPowerDown_Pre_Load_Ld,
  NopinionReqCheckPowerDown_Pre_Load_Absent,
  NopinionReqCheckPowerDown_Pre_Load_NA
} NopinionReqCheckPowerDown_Pre_Load;

typedef enum {
  NopinionReqCheckPowerDown_Pre_Offset_Zero,
  NopinionReqCheckPowerDown_Pre_Offset_Twelve,
  NopinionReqCheckPowerDown_Pre_Offset_Sixteen,
  NopinionReqCheckPowerDown_Pre_Offset_NA
} NopinionReqCheckPowerDown_Pre_Offset;

typedef enum {
  NopinionReqCheckPowerDown_Pre_Branch_None,
  NopinionReqCheckPowerDown_Pre_Branch_AfterLoad,
  NopinionReqCheckPowerDown_Pre_Branch_BlockEnd,
  NopinionReqCheckPowerDown_Pre_Branch_NextBlock,
  NopinionReqCheckPowerDown_Pre_Branch_End,
  NopinionReqCheckPowerDown_Pre_Branch_NA
} NopinionReqCheckPowerDown_Pre_Branch;

typedef enum {
  NopinionReqCheckPowerDown_Pre_File_BeforeFtahbram,
  NopinionReqCheckPowerDown_Pre_File_FtahbramBegin,
  NopinionReqCheckPowerDown_Pre_File_FtahbramLast,
  NopinionReqCheckPowerDown_Pre_File_FtahbramEnd,
  NopinionReqCheckPowerDown_Pre_File_RelocatableAligned,
  NopinionReqCheckPowerDown_Pre_File_RelocatableUnaligned,
  NopinionReqCheckPowerDown_Pre_File_NA
} NopinionReqCheckPowerDown_Pre_File;

typedef enum {
  NopinionReqCheckPowerDown_Post_Load_None,
  NopinionReqCheckPowerDown_Post_Load_Definite,
  NopinionReqCheckPowerDown_Post_Load_Possible,
  NopinionReqCheckPowerDown_Post_Load_NA
} NopinionReqCheckPowerDown_Post_Load;

typedef enum {
  NopinionReqCheckPowerDown_Post_Block_None,
  NopinionReqCheckPowerDown_Post_Block_Definite,
  NopinionReqCheckPowerDown_Post_Block_Possible,
  NopinionReqCheckPowerDown_Post_Block_NA
} NopinionReqCheckPowerDown_Post_Block;

typedef enum {
  NopinionReqCheckPowerDown_Post_Branch_None,
  NopinionReqCheckPowerDown_Post_Branch_Definite,
  NopinionReqCheckPowerDown_Post_Branch_Possible,
  NopinionReqCheckPowerDown_Post_Branch_NA
} NopinionReqCheckPowerDown_Post_Branch;

typedef enum {
  NopinionReqCheckPowerDown_Post_Ftahbram_None,
  NopinionReqCheckPowerDown_Post_Ftahbram_Definite,
  NopinionReqCheckPowerDown_Post_Ftahbram_NA
} NopinionReqCheckPowerDown_Post_Ftahbram;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Write_NA : 1;
  uint16_t Pre_Load_NA : 1;
  uint16_t Pre_Offset_NA : 1;
  uint16_t Pre_Branch_NA : 1;
  uint16_t Pre_File_NA : 1;
  uint16_t Post_Load : 2;
  uint16_t Post_Block : 2;
  uint16_t Post_Branch : 2;
  uint16_t Post_Ftahbram : 2;
} NopinionReqCheckPowerDown_Entry;

#define BRANCH_NONE 0

#define BRANCH_AFTER_LOAD 1

#define BRANCH_BLOCK_END 2

#define BRANCH_NEXT_BLOCK 3

#define BRANCH_END 4

/**
 * @brief Test context for spec:/nopinion/req/check-power-down test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file to check.
   */
  TxImage image;

  /**
   * @brief This member contains the write.
   */
  uint32_t write;

  /**
   * @brief This member contains the instruction after the write.
   */
  uint32_t load;

  /**
   * @brief This member is true, if the code section ends after the write.
   */
  bool load_absent;

  /**
   * @brief This member contains the index of the write.
   */
  size_t index;

  /**
   * @brief This member contains the place of the branch.
   */
  int branch;

  /**
   * @brief This member contains the offset of the write.
   */
  uint32_t offset;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

  struct {
    /**
     * @brief This member defines the pre-condition indices for the next
     *   action.
     */
    size_t pci[ 5 ];

    /**
     * @brief This member defines the pre-condition states for the next action.
     */
    size_t pcs[ 5 ];

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
    NopinionReqCheckPowerDown_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCheckPowerDown_Context;

static NopinionReqCheckPowerDown_Context NopinionReqCheckPowerDown_Instance;

static const char *const NopinionReqCheckPowerDown_PreDesc_Write[] =
  { "Asr19", "Asr18", "Y", "NA" };

static const char *const NopinionReqCheckPowerDown_PreDesc_Load[] =
  { "Bypass", "OtherAsi", "OtherRegister", "Ld", "Absent", "NA" };

static const char *const NopinionReqCheckPowerDown_PreDesc_Offset[] =
  { "Zero", "Twelve", "Sixteen", "NA" };

static const char *const NopinionReqCheckPowerDown_PreDesc_Branch[] =
  { "None", "AfterLoad", "BlockEnd", "NextBlock", "End", "NA" };

static const char *const NopinionReqCheckPowerDown_PreDesc_File[] = {
  "BeforeFtahbram",
  "FtahbramBegin",
  "FtahbramLast",
  "FtahbramEnd",
  "RelocatableAligned",
  "RelocatableUnaligned",
  "NA"
};

static const char *const *const NopinionReqCheckPowerDown_PreDesc[] = {
  NopinionReqCheckPowerDown_PreDesc_Write,
  NopinionReqCheckPowerDown_PreDesc_Load,
  NopinionReqCheckPowerDown_PreDesc_Offset,
  NopinionReqCheckPowerDown_PreDesc_Branch,
  NopinionReqCheckPowerDown_PreDesc_File,
  NULL
};

static void NopinionReqCheckPowerDown_Pre_Write_Prepare(
  NopinionReqCheckPowerDown_Context  *ctx,
  NopinionReqCheckPowerDown_Pre_Write state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Pre_Write_Asr19: {
      /*
       * While the write is a WRASR instruction to %asr19.
       */
      ctx->write = TxWrasr( 19 );
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Write_Asr18: {
      /*
       * While the write is a WRASR instruction to %asr18.
       */
      ctx->write = TxWrasr( 18 );
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Write_Y: {
      /*
       * While the write is a WRY instruction.
       */
      ctx->write = TxWrasr( 0 );
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Write_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Pre_Load_Prepare(
  NopinionReqCheckPowerDown_Context *ctx,
  NopinionReqCheckPowerDown_Pre_Load state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Pre_Load_Bypass: {
      /*
       * While the instruction after the write is an LDA instruction with the
       * address space identifier 0x1C and the destination %g0.
       */
      ctx->load = TxFormat3Asi( 3, 0x10, TX_G0, TX_O0, 0x1c, TX_G0 );
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Load_OtherAsi: {
      /*
       * While the instruction after the write is an LDA instruction with the
       * address space identifier 0x0B and the destination %g0.
       */
      ctx->load = TxFormat3Asi( 3, 0x10, TX_G0, TX_O0, 0x0b, TX_G0 );
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Load_OtherRegister: {
      /*
       * While the instruction after the write is an LDA instruction with the
       * address space identifier 0x1C and the destination %g1.
       */
      ctx->load = TxFormat3Asi( 3, 0x10, TX_G1, TX_O0, 0x1c, TX_G0 );
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Load_Ld: {
      /*
       * While the instruction after the write is an LD instruction.
       */
      ctx->load = TxLd();
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Load_Absent: {
      /*
       * While the code section ends after the write.
       */
      ctx->load_absent = true;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Load_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Pre_Offset_Prepare(
  NopinionReqCheckPowerDown_Context   *ctx,
  NopinionReqCheckPowerDown_Pre_Offset state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Pre_Offset_Zero: {
      /*
       * While the offset of the write in its 32-byte block is 0.
       */
      ctx->index = 0;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Offset_Twelve: {
      /*
       * While the offset of the write in its 32-byte block is 12.
       */
      ctx->index = 3;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Offset_Sixteen: {
      /*
       * While the offset of the write in its 32-byte block is 16.
       */
      ctx->index = 4;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Offset_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Pre_Branch_Prepare(
  NopinionReqCheckPowerDown_Context   *ctx,
  NopinionReqCheckPowerDown_Pre_Branch state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Pre_Branch_None: {
      /*
       * While no branch or jump follows the write within 15 instructions.
       */
      ctx->branch = BRANCH_NONE;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Branch_AfterLoad: {
      /*
       * While a branch follows the load.
       */
      ctx->branch = BRANCH_AFTER_LOAD;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Branch_BlockEnd: {
      /*
       * While a branch is the last instruction of the 32-byte block of the
       * write.
       */
      ctx->branch = BRANCH_BLOCK_END;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Branch_NextBlock: {
      /*
       * While a branch is the first instruction of the 32-byte block after the
       * block of the write.
       */
      ctx->branch = BRANCH_NEXT_BLOCK;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Branch_End: {
      /*
       * While the code section ends after the load.
       */
      ctx->branch = BRANCH_END;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_Branch_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Pre_File_Prepare(
  NopinionReqCheckPowerDown_Context *ctx,
  NopinionReqCheckPowerDown_Pre_File state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Pre_File_BeforeFtahbram: {
      /*
       * While the ELF file is an executable, while the code section starts at
       * 0x9FFFFFE0.
       */
      ctx->image.executable = true;
      ctx->image.address = 0x9fffffe0;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_File_FtahbramBegin: {
      /*
       * While the ELF file is an executable, while the code section starts at
       * 0xA0000000.
       */
      ctx->image.executable = true;
      ctx->image.address = 0xa0000000;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_File_FtahbramLast: {
      /*
       * While the ELF file is an executable, while the code section starts at
       * 0xA00FFFE0.
       */
      ctx->image.executable = true;
      ctx->image.address = 0xa00fffe0;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_File_FtahbramEnd: {
      /*
       * While the ELF file is an executable, while the code section starts at
       * 0xA0100000.
       */
      ctx->image.executable = true;
      ctx->image.address = 0xa0100000;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_File_RelocatableAligned: {
      /*
       * While the ELF file is relocatable, while the alignment of the code
       * section is an integral multiple of 32.
       */
      ctx->image.alignment = 32;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_File_RelocatableUnaligned: {
      /*
       * While the ELF file is relocatable, while the alignment of the code
       * section is 16.
       */
      ctx->image.alignment = 16;
      break;
    }

    case NopinionReqCheckPowerDown_Pre_File_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Post_Load_Check(
  NopinionReqCheckPowerDown_Context  *ctx,
  NopinionReqCheckPowerDown_Post_Load state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Post_Load_None: {
      /*
       * The errata checker shall report no finding of a write to %asr19
       * without the load.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-without-load" ),
        0
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Load_Definite: {
      /*
       * The errata checker shall report one definite finding of a write to
       * %asr19 without the load for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-without-load" ),
        1
      );
      T_false(
        TxIsPossibleAt( ctx->report, ctx->offset, "power-down-without-load" )
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Load_Possible: {
      /*
       * The errata checker shall report one possible finding of a write to
       * %asr19 without the load for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-without-load" ),
        1
      );
      T_true(
        TxIsPossibleAt( ctx->report, ctx->offset, "power-down-without-load" )
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Load_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Post_Block_Check(
  NopinionReqCheckPowerDown_Context   *ctx,
  NopinionReqCheckPowerDown_Post_Block state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Post_Block_None: {
      /*
       * The errata checker shall report no finding of a write to %asr19
       * outside the 32-byte block of the sequence.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-not-in-block" ),
        0
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Block_Definite: {
      /*
       * The errata checker shall report one definite finding of a write to
       * %asr19 outside the 32-byte block of the sequence for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-not-in-block" ),
        1
      );
      T_false(
        TxIsPossibleAt( ctx->report, ctx->offset, "power-down-not-in-block" )
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Block_Possible: {
      /*
       * The errata checker shall report one possible finding of a write to
       * %asr19 outside the 32-byte block of the sequence for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-not-in-block" ),
        1
      );
      T_true(
        TxIsPossibleAt( ctx->report, ctx->offset, "power-down-not-in-block" )
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Block_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Post_Branch_Check(
  NopinionReqCheckPowerDown_Context    *ctx,
  NopinionReqCheckPowerDown_Post_Branch state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Post_Branch_None: {
      /*
       * The errata checker shall report no finding of a branch or jump after
       * the load.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-branch-after-load" ),
        0
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Branch_Definite: {
      /*
       * The errata checker shall report one definite finding of a branch or
       * jump after the load for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-branch-after-load" ),
        1
      );
      T_false( TxIsPossibleAt(
        ctx->report,
        ctx->offset,
        "power-down-branch-after-load"
      ) );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Branch_Possible: {
      /*
       * The errata checker shall report one possible finding of a branch or
       * jump after the load for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-branch-after-load" ),
        1
      );
      T_true( TxIsPossibleAt(
        ctx->report,
        ctx->offset,
        "power-down-branch-after-load"
      ) );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Branch_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Post_Ftahbram_Check(
  NopinionReqCheckPowerDown_Context      *ctx,
  NopinionReqCheckPowerDown_Post_Ftahbram state
)
{
  switch ( state ) {
    case NopinionReqCheckPowerDown_Post_Ftahbram_None: {
      /*
       * The errata checker shall report no finding of a write to %asr19 in the
       * FTAHBRAM.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-in-ftahbram" ),
        0
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Ftahbram_Definite: {
      /*
       * The errata checker shall report one definite finding of a write to
       * %asr19 in the FTAHBRAM for the write.
       */
      T_eq_int(
        TxCountAt( ctx->report, ctx->offset, "power-down-in-ftahbram" ),
        1
      );
      T_false(
        TxIsPossibleAt( ctx->report, ctx->offset, "power-down-in-ftahbram" )
      );
      break;
    }

    case NopinionReqCheckPowerDown_Post_Ftahbram_NA:
      break;
  }
}

static void NopinionReqCheckPowerDown_Prepare(
  NopinionReqCheckPowerDown_Context *ctx
)
{
  TxImageInit( &ctx->image );
  ctx->load_absent = false;
  ctx->branch = BRANCH_NONE;
}

static void NopinionReqCheckPowerDown_Action(
  NopinionReqCheckPowerDown_Context *ctx
)
{
  size_t count = 16;
  size_t i;

  if ( ctx->load_absent ) {
    count = ctx->index + 1;
  } else if ( ctx->branch == BRANCH_END ) {
    count = ctx->index + 2;
  }

  for ( i = 0; i < count; ++i ) {
    TxAppend( &ctx->image, TxNop() );
  }

  ctx->image.code[ ctx->index ] = ctx->write;

  if ( !ctx->load_absent ) {
    ctx->image.code[ ctx->index + 1 ] = ctx->load;
  }

  if ( ctx->branch == BRANCH_AFTER_LOAD ) {
    ctx->image.code[ ctx->index + 2 ] = TxBicc( 8, true, 0 );
  } else if ( ctx->branch == BRANCH_BLOCK_END ) {
    ctx->image.code[ 7 ] = TxBicc( 8, true, 0 );
  } else if ( ctx->branch == BRANCH_NEXT_BLOCK ) {
    ctx->image.code[ 8 ] = TxBicc( 8, true, 0 );
  }

  ctx->offset = (uint32_t) ( 4 * ctx->index );
  ctx->report = TxCheck( &ctx->image, NOTE_POWER_DOWN );
}

/* clang-format off */

static const NopinionReqCheckPowerDown_Entry
NopinionReqCheckPowerDown_Entries[] = {
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 1, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_NA,
    NopinionReqCheckPowerDown_Post_Block_NA,
    NopinionReqCheckPowerDown_Post_Branch_NA,
    NopinionReqCheckPowerDown_Post_Ftahbram_NA },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_Definite,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_Definite,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 1, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_Definite,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Possible,
    NopinionReqCheckPowerDown_Post_Branch_Possible,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 1, 0, NopinionReqCheckPowerDown_Post_Load_Possible,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_Definite,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_Possible,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Definite,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Definite,
    NopinionReqCheckPowerDown_Post_Branch_Definite,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 1, 0, NopinionReqCheckPowerDown_Post_Load_Possible,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_None,
    NopinionReqCheckPowerDown_Post_Branch_Possible,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Definite,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Definite,
    NopinionReqCheckPowerDown_Post_Branch_Definite,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Possible,
    NopinionReqCheckPowerDown_Post_Branch_None,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Definite,
    NopinionReqCheckPowerDown_Post_Branch_Possible,
    NopinionReqCheckPowerDown_Post_Ftahbram_None },
  { 0, 0, 0, 0, 0, 0, NopinionReqCheckPowerDown_Post_Load_None,
    NopinionReqCheckPowerDown_Post_Block_Definite,
    NopinionReqCheckPowerDown_Post_Branch_Possible,
    NopinionReqCheckPowerDown_Post_Ftahbram_Definite }
};

static const uint8_t
NopinionReqCheckPowerDown_Map[] = {
  0, 8, 8, 0, 0, 17, 5, 9, 9, 5, 5, 6, 5, 9, 9, 5, 5, 6, 0, 8, 8, 0, 0, 6, 10,
  14, 14, 10, 10, 6, 0, 8, 8, 0, 0, 17, 5, 9, 9, 5, 5, 6, 5, 9, 9, 5, 5, 6, 0,
  8, 8, 0, 0, 6, 10, 14, 14, 10, 10, 6, 11, 15, 15, 11, 11, 17, 12, 16, 16, 12,
  12, 6, 12, 16, 16, 12, 12, 6, 11, 15, 15, 11, 11, 6, 18, 19, 19, 18, 18, 6,
  2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3,
  3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2,
  2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2,
  2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3,
  3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2,
  2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2,
  2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3,
  3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2,
  2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2,
  2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 2, 3,
  3, 2, 2, 2, 2, 3, 3, 2, 2, 2, 7, 13, 13, 7, 7, 7, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 13, 13, 7, 7, 7, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 13, 13, 7, 7,
  7, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
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
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4,
  4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
  4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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
  0, 0, 0, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

/* clang-format on */

static size_t NopinionReqCheckPowerDown_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCheckPowerDown_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqCheckPowerDown_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqCheckPowerDown_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqCheckPowerDown_Scope,
  .initial_context = &NopinionReqCheckPowerDown_Instance
};

static inline NopinionReqCheckPowerDown_Entry
NopinionReqCheckPowerDown_PopEntry( NopinionReqCheckPowerDown_Context *ctx )
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCheckPowerDown_Entries
    [ NopinionReqCheckPowerDown_Map[ index ] ];
}

static void NopinionReqCheckPowerDown_SetPreConditionStates(
  NopinionReqCheckPowerDown_Context *ctx
)
{
  ctx->Map.pcs[ 0 ] = ctx->Map.pci[ 0 ];
  ctx->Map.pcs[ 1 ] = ctx->Map.pci[ 1 ];
  ctx->Map.pcs[ 2 ] = ctx->Map.pci[ 2 ];

  if ( ctx->Map.entry.Pre_Branch_NA ) {
    ctx->Map.pcs[ 3 ] = NopinionReqCheckPowerDown_Pre_Branch_NA;
  } else {
    ctx->Map.pcs[ 3 ] = ctx->Map.pci[ 3 ];
  }

  ctx->Map.pcs[ 4 ] = ctx->Map.pci[ 4 ];
}

static void NopinionReqCheckPowerDown_TestVariant(
  NopinionReqCheckPowerDown_Context *ctx
)
{
  NopinionReqCheckPowerDown_Pre_Write_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCheckPowerDown_Pre_Load_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCheckPowerDown_Pre_Offset_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCheckPowerDown_Pre_Branch_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqCheckPowerDown_Pre_File_Prepare( ctx, ctx->Map.pcs[ 4 ] );
  NopinionReqCheckPowerDown_Action( ctx );
  NopinionReqCheckPowerDown_Post_Load_Check( ctx, ctx->Map.entry.Post_Load );
  NopinionReqCheckPowerDown_Post_Block_Check( ctx, ctx->Map.entry.Post_Block );
  NopinionReqCheckPowerDown_Post_Branch_Check(
    ctx,
    ctx->Map.entry.Post_Branch
  );
  NopinionReqCheckPowerDown_Post_Ftahbram_Check(
    ctx,
    ctx->Map.entry.Post_Ftahbram
  );
}

/**
 * @fn void T_case_body_NopinionReqCheckPowerDown( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqCheckPowerDown,
  &NopinionReqCheckPowerDown_Fixture
)
{
  NopinionReqCheckPowerDown_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pci[ 0 ] = NopinionReqCheckPowerDown_Pre_Write_Asr19;
    ctx->Map.pci[ 0 ] < NopinionReqCheckPowerDown_Pre_Write_NA;
    ++ctx->Map.pci[ 0 ]
  ) {
    for (
      ctx->Map.pci[ 1 ] = NopinionReqCheckPowerDown_Pre_Load_Bypass;
      ctx->Map.pci[ 1 ] < NopinionReqCheckPowerDown_Pre_Load_NA;
      ++ctx->Map.pci[ 1 ]
    ) {
      for (
        ctx->Map.pci[ 2 ] = NopinionReqCheckPowerDown_Pre_Offset_Zero;
        ctx->Map.pci[ 2 ] < NopinionReqCheckPowerDown_Pre_Offset_NA;
        ++ctx->Map.pci[ 2 ]
      ) {
        for (
          ctx->Map.pci[ 3 ] = NopinionReqCheckPowerDown_Pre_Branch_None;
          ctx->Map.pci[ 3 ] < NopinionReqCheckPowerDown_Pre_Branch_NA;
          ++ctx->Map.pci[ 3 ]
        ) {
          for (
            ctx->Map.pci[ 4 ] =
              NopinionReqCheckPowerDown_Pre_File_BeforeFtahbram;
            ctx->Map.pci[ 4 ] < NopinionReqCheckPowerDown_Pre_File_NA;
            ++ctx->Map.pci[ 4 ]
          ) {
            ctx->Map.entry = NopinionReqCheckPowerDown_PopEntry( ctx );

            if ( ctx->Map.entry.Skip ) {
              continue;
            }

            NopinionReqCheckPowerDown_SetPreConditionStates( ctx );
            NopinionReqCheckPowerDown_Prepare( ctx );
            NopinionReqCheckPowerDown_TestVariant( ctx );
          }
        }
      }
    }
  }
}

/** @} */
