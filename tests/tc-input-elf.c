/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqInputElf
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
 * @defgroup NopinionReqInputElf spec:/nopinion/req/input-elf
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqInputElf_Pre_File_Valid,
  NopinionReqInputElf_Pre_File_Short,
  NopinionReqInputElf_Pre_File_Magic,
  NopinionReqInputElf_Pre_File_Class64,
  NopinionReqInputElf_Pre_File_LittleEndian,
  NopinionReqInputElf_Pre_File_OtherMachine,
  NopinionReqInputElf_Pre_File_Sparc32Plus,
  NopinionReqInputElf_Pre_File_NoSections,
  NopinionReqInputElf_Pre_File_EntrySize,
  NopinionReqInputElf_Pre_File_TableOutside,
  NopinionReqInputElf_Pre_File_StringIndex,
  NopinionReqInputElf_Pre_File_StringOutside,
  NopinionReqInputElf_Pre_File_CodeOutside,
  NopinionReqInputElf_Pre_File_CodeTooLong,
  NopinionReqInputElf_Pre_File_CodeName,
  NopinionReqInputElf_Pre_File_CodeSmall,
  NopinionReqInputElf_Pre_File_NotExecutable,
  NopinionReqInputElf_Pre_File_NoBits,
  NopinionReqInputElf_Pre_File_NoMemoryInfo,
  NopinionReqInputElf_Pre_File_NoMemoryTarget,
  NopinionReqInputElf_Pre_File_NA
} NopinionReqInputElf_Pre_File;

typedef enum {
  NopinionReqInputElf_Post_Error_None,
  NopinionReqInputElf_Post_Error_NotElf,
  NopinionReqInputElf_Post_Error_NotElf32Be,
  NopinionReqInputElf_Post_Error_NotSparc,
  NopinionReqInputElf_Post_Error_BadSectionHeaders,
  NopinionReqInputElf_Post_Error_BadStringTable,
  NopinionReqInputElf_Post_Error_BadCodeSection,
  NopinionReqInputElf_Post_Error_OutOfMemory,
  NopinionReqInputElf_Post_Error_NA
} NopinionReqInputElf_Post_Error;

typedef enum {
  NopinionReqInputElf_Post_Checked_Yes,
  NopinionReqInputElf_Post_Checked_No,
  NopinionReqInputElf_Post_Checked_NA
} NopinionReqInputElf_Post_Checked;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_File_NA : 1;
  uint8_t Post_Error : 4;
  uint8_t Post_Checked : 2;
} NopinionReqInputElf_Entry;

/**
 * @brief Test context for spec:/nopinion/req/input-elf test case.
 */
typedef struct {
  /**
   * @brief This member contains the ELF file.
   */
  uint8_t buf[ 4096 ];

  /**
   * @brief This member contains the size of the ELF file.
   */
  size_t size;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

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
    NopinionReqInputElf_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqInputElf_Context;

static NopinionReqInputElf_Context NopinionReqInputElf_Instance;

static const char *const NopinionReqInputElf_PreDesc_File[] = {
  "Valid",
  "Short",
  "Magic",
  "Class64",
  "LittleEndian",
  "OtherMachine",
  "Sparc32Plus",
  "NoSections",
  "EntrySize",
  "TableOutside",
  "StringIndex",
  "StringOutside",
  "CodeOutside",
  "CodeTooLong",
  "CodeName",
  "CodeSmall",
  "NotExecutable",
  "NoBits",
  "NoMemoryInfo",
  "NoMemoryTarget",
  "NA"
};

static const char *const *const NopinionReqInputElf_PreDesc[] = {
  NopinionReqInputElf_PreDesc_File,
  NULL
};

static void NopinionReqInputElf_Pre_File_Prepare(
  NopinionReqInputElf_Context *ctx,
  NopinionReqInputElf_Pre_File state
)
{
  switch ( state ) {
    case NopinionReqInputElf_Pre_File_Valid: {
      /*
       * While the file is a valid ELF file with a code section.
       */
      /* The file is valid */
      break;
    }

    case NopinionReqInputElf_Pre_File_Short: {
      /*
       * While the file is shorter than an ELF header.
       */
      ctx->size = 51;
      break;
    }

    case NopinionReqInputElf_Pre_File_Magic: {
      /*
       * While the file is an ELF file with a wrong magic number.
       */
      ctx->buf[ 1 ] = 'X';
      break;
    }

    case NopinionReqInputElf_Pre_File_Class64: {
      /*
       * While the file is an ELF file of the 64-bit class.
       */
      ctx->buf[ 4 ] = 2;
      break;
    }

    case NopinionReqInputElf_Pre_File_LittleEndian: {
      /*
       * While the file is an ELF file with little-endian data.
       */
      ctx->buf[ 5 ] = 1;
      break;
    }

    case NopinionReqInputElf_Pre_File_OtherMachine: {
      /*
       * While the file is an ELF file for another machine than SPARC.
       */
      TxPut16( ctx->buf + 18, 3 );
      break;
    }

    case NopinionReqInputElf_Pre_File_Sparc32Plus: {
      /*
       * While the file is an ELF file for the machine SPARC32PLUS.
       */
      TxPut16( ctx->buf + 18, 18 );
      break;
    }

    case NopinionReqInputElf_Pre_File_NoSections: {
      /*
       * While the file is an ELF file without section headers.
       */
      TxPut16( ctx->buf + 48, 0 );
      break;
    }

    case NopinionReqInputElf_Pre_File_EntrySize: {
      /*
       * While the file is an ELF file with a section header entry size of less
       * than 40 bytes.
       */
      TxPut16( ctx->buf + 46, 39 );
      break;
    }

    case NopinionReqInputElf_Pre_File_TableOutside: {
      /*
       * While the file is an ELF file whose section header table exceeds the
       * file.
       */
      TxPut32( ctx->buf + 32, 0x10000 );
      break;
    }

    case NopinionReqInputElf_Pre_File_StringIndex: {
      /*
       * While the file is an ELF file whose section name string table index
       * exceeds the section count.
       */
      TxPut16( ctx->buf + 50, 6 );
      break;
    }

    case NopinionReqInputElf_Pre_File_StringOutside: {
      /*
       * While the file is an ELF file whose section name string table exceeds
       * the file.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_SHSTRTAB ) + 16,
        0x10000
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_CodeOutside: {
      /*
       * While the file is an ELF file whose code section exceeds the file.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_TEXT ) + 16,
        0x10000
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_CodeTooLong: {
      /*
       * While the file is an ELF file whose code section starts in the file
       * and ends beyond it.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_TEXT ) + 20,
        0x10000
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_CodeName: {
      /*
       * While the file is an ELF file whose code section name exceeds the
       * section name string table.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_TEXT ),
        0x10000
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_CodeSmall: {
      /*
       * While the file is an ELF file whose code section is shorter than one
       * instruction.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_TEXT ) + 20,
        3
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_NotExecutable: {
      /*
       * While the file is an ELF file whose only SHT_PROGBITS section lacks
       * the flag SHF_EXECINSTR.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_TEXT ) + 8,
        2
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_NoBits: {
      /*
       * While the file is an ELF file whose only section with the flag
       * SHF_EXECINSTR has the type SHT_NOBITS.
       */
      TxPut32(
        ctx->buf + TxSectionHeader( ctx->buf, TX_SECTION_TEXT ) + 4,
        8
      );
      break;
    }

    case NopinionReqInputElf_Pre_File_NoMemoryInfo: {
      /*
       * While the file is a valid ELF file, while the allocation of the
       * instruction information fails.
       */
      TxFailNext( TX_FAIL_CALLOC );
      break;
    }

    case NopinionReqInputElf_Pre_File_NoMemoryTarget: {
      /*
       * While the file is a valid ELF file, while the allocation of the branch
       * targets fails.
       */
      TxFailNext( TX_FAIL_MALLOC );
      break;
    }

    case NopinionReqInputElf_Pre_File_NA:
      break;
  }
}

static void NopinionReqInputElf_Post_Error_Check(
  NopinionReqInputElf_Post_Error state
)
{
  switch ( state ) {
    case NopinionReqInputElf_Post_Error_None: {
      /*
       * The errata checker shall report no error.
       */
      T_eq_str( TxErrors(), "" );
      break;
    }

    case NopinionReqInputElf_Post_Error_NotElf: {
      /*
       * The errata checker shall report the error "not an ELF file" for the
       * file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: not an ELF file\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_NotElf32Be: {
      /*
       * The errata checker shall report the error "not an ELF32 big-endian
       * file" for the file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: not an ELF32 big-endian file\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_NotSparc: {
      /*
       * The errata checker shall report the error "not a SPARC ELF file" for
       * the file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: not a SPARC ELF file\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_BadSectionHeaders: {
      /*
       * The errata checker shall report the error "bad section headers" for
       * the file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: bad section headers\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_BadStringTable: {
      /*
       * The errata checker shall report the error "bad string table" for the
       * file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: bad string table\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_BadCodeSection: {
      /*
       * The errata checker shall report the error "bad code section" for the
       * file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: bad code section\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_OutOfMemory: {
      /*
       * The errata checker shall report the error "out of memory" for the
       * file.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: out of memory\n" );
      break;
    }

    case NopinionReqInputElf_Post_Error_NA:
      break;
  }
}

static void NopinionReqInputElf_Post_Checked_Check(
  NopinionReqInputElf_Context     *ctx,
  NopinionReqInputElf_Post_Checked state
)
{
  switch ( state ) {
    case NopinionReqInputElf_Post_Checked_Yes: {
      /*
       * The errata checker shall check the code section.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 1 );
      break;
    }

    case NopinionReqInputElf_Post_Checked_No: {
      /*
       * The errata checker shall check no code section.
       */
      T_eq_int( TxCountAt( ctx->report, 0, "TN-0009" ), 0 );
      break;
    }

    case NopinionReqInputElf_Post_Checked_NA:
      break;
  }
}

static void NopinionReqInputElf_Prepare( NopinionReqInputElf_Context *ctx )
{
  TxImage image;

  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxAdd() );
  TxAppend( &image, TxSt() );
  ctx->size = TxBuildElf( &image, ctx->buf, sizeof( ctx->buf ) );
}

static void NopinionReqInputElf_Action( NopinionReqInputElf_Context *ctx )
{
  ctx->report = TxCheckBuffer( ctx->buf, ctx->size, NOTE_0009 );
  TxFailNext( 0 );
}

/* clang-format off */

static const NopinionReqInputElf_Entry
NopinionReqInputElf_Entries[] = {
  { 0, 0, NopinionReqInputElf_Post_Error_None,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_BadSectionHeaders,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_BadCodeSection,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_None,
    NopinionReqInputElf_Post_Checked_Yes },
  { 0, 0, NopinionReqInputElf_Post_Error_NotElf,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_NotElf32Be,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_OutOfMemory,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_NotSparc,
    NopinionReqInputElf_Post_Checked_No },
  { 0, 0, NopinionReqInputElf_Post_Error_BadStringTable,
    NopinionReqInputElf_Post_Checked_No }
};

static const uint8_t
NopinionReqInputElf_Map[] = {
  3, 4, 4, 5, 5, 7, 3, 0, 1, 1, 1, 8, 2, 2, 2, 0, 0, 0, 6, 6
};

/* clang-format on */

static size_t NopinionReqInputElf_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqInputElf_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqInputElf_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqInputElf_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqInputElf_Scope,
  .initial_context = &NopinionReqInputElf_Instance
};

static inline NopinionReqInputElf_Entry NopinionReqInputElf_PopEntry(
  NopinionReqInputElf_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqInputElf_Entries[ NopinionReqInputElf_Map[ index ] ];
}

static void NopinionReqInputElf_TestVariant( NopinionReqInputElf_Context *ctx )
{
  NopinionReqInputElf_Pre_File_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqInputElf_Action( ctx );
  NopinionReqInputElf_Post_Error_Check( ctx->Map.entry.Post_Error );
  NopinionReqInputElf_Post_Checked_Check( ctx, ctx->Map.entry.Post_Checked );
}

/**
 * @fn void T_case_body_NopinionReqInputElf( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqInputElf, &NopinionReqInputElf_Fixture )
{
  NopinionReqInputElf_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqInputElf_Pre_File_Valid;
    ctx->Map.pcs[ 0 ] < NopinionReqInputElf_Pre_File_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    ctx->Map.entry = NopinionReqInputElf_PopEntry( ctx );
    NopinionReqInputElf_Prepare( ctx );
    NopinionReqInputElf_TestVariant( ctx );
  }
}

/** @} */
