/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqInputArchive
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

#include <stdio.h>
#include <string.h>

#include "nopinion.h"
#include "tx-support.h"

#include <rtems/test.h>

/**
 * @defgroup NopinionReqInputArchive spec:/nopinion/req/input-archive
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqInputArchive_Pre_Before_None,
  NopinionReqInputArchive_Pre_Before_SymbolTable,
  NopinionReqInputArchive_Pre_Before_SymbolTableOdd,
  NopinionReqInputArchive_Pre_Before_SymbolTable64,
  NopinionReqInputArchive_Pre_Before_NA
} NopinionReqInputArchive_Pre_Before;

typedef enum {
  NopinionReqInputArchive_Pre_Name_Short,
  NopinionReqInputArchive_Pre_Name_ShortFull,
  NopinionReqInputArchive_Pre_Name_Long,
  NopinionReqInputArchive_Pre_Name_LongNewline,
  NopinionReqInputArchive_Pre_Name_NoTable,
  NopinionReqInputArchive_Pre_Name_Beyond,
  NopinionReqInputArchive_Pre_Name_NA
} NopinionReqInputArchive_Pre_Name;

typedef enum {
  NopinionReqInputArchive_Pre_Content_Elf,
  NopinionReqInputArchive_Pre_Content_Other,
  NopinionReqInputArchive_Pre_Content_NA
} NopinionReqInputArchive_Pre_Content;

typedef enum {
  NopinionReqInputArchive_Pre_Size_Valid,
  NopinionReqInputArchive_Pre_Size_Truncated,
  NopinionReqInputArchive_Pre_Size_Empty,
  NopinionReqInputArchive_Pre_Size_NA
} NopinionReqInputArchive_Pre_Size;

typedef enum {
  NopinionReqInputArchive_Post_Error_None,
  NopinionReqInputArchive_Post_Error_NotElf,
  NopinionReqInputArchive_Post_Error_BadLongName,
  NopinionReqInputArchive_Post_Error_Truncated,
  NopinionReqInputArchive_Post_Error_NA
} NopinionReqInputArchive_Post_Error;

typedef enum {
  NopinionReqInputArchive_Post_Member_Checked,
  NopinionReqInputArchive_Post_Member_NotChecked,
  NopinionReqInputArchive_Post_Member_NA
} NopinionReqInputArchive_Post_Member;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Before_NA : 1;
  uint16_t Pre_Name_NA : 1;
  uint16_t Pre_Content_NA : 1;
  uint16_t Pre_Size_NA : 1;
  uint16_t Post_Error : 3;
  uint16_t Post_Member : 2;
} NopinionReqInputArchive_Entry;

/**
 * @brief Test context for spec:/nopinion/req/input-archive test case.
 */
typedef struct {
  /**
   * @brief This member contains the archive.
   */
  TxArchive archive;

  /**
   * @brief This member contains the name field of the member header.
   */
  const char *name;

  /**
   * @brief This member contains the name of the member in the report.
   */
  const char *member;

  /**
   * @brief This member is true, if the member is an ELF file.
   */
  bool elf;

  /**
   * @brief This member is true, if the archive holds no further member.
   */
  bool empty;

  /**
   * @brief This member contains the excess of the size field.
   */
  size_t excess;

  /**
   * @brief This member references the report of the errata checker.
   */
  const char *report;

  struct {
    /**
     * @brief This member defines the pre-condition indices for the next
     *   action.
     */
    size_t pci[ 4 ];

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
    NopinionReqInputArchive_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqInputArchive_Context;

static NopinionReqInputArchive_Context NopinionReqInputArchive_Instance;

static const char *const NopinionReqInputArchive_PreDesc_Before[] =
  { "None", "SymbolTable", "SymbolTableOdd", "SymbolTable64", "NA" };

static const char *const NopinionReqInputArchive_PreDesc_Name[] =
  { "Short", "ShortFull", "Long", "LongNewline", "NoTable", "Beyond", "NA" };

static const char *const NopinionReqInputArchive_PreDesc_Content[] =
  { "Elf", "Other", "NA" };

static const char *const NopinionReqInputArchive_PreDesc_Size[] =
  { "Valid", "Truncated", "Empty", "NA" };

static const char *const *const NopinionReqInputArchive_PreDesc[] = {
  NopinionReqInputArchive_PreDesc_Before,
  NopinionReqInputArchive_PreDesc_Name,
  NopinionReqInputArchive_PreDesc_Content,
  NopinionReqInputArchive_PreDesc_Size,
  NULL
};

static void NopinionReqInputArchive_Pre_Before_Prepare(
  NopinionReqInputArchive_Context   *ctx,
  NopinionReqInputArchive_Pre_Before state
)
{
  switch ( state ) {
    case NopinionReqInputArchive_Pre_Before_None: {
      /*
       * While no member precedes the member.
       */
      /* No member precedes the member */
      break;
    }

    case NopinionReqInputArchive_Pre_Before_SymbolTable: {
      /*
       * While the symbol table of the archive with an even size precedes the
       * member.
       */
      TxArchiveAdd( &ctx->archive, "/", (const uint8_t *) "\0\0\0\0", 4, 0 );
      break;
    }

    case NopinionReqInputArchive_Pre_Before_SymbolTableOdd: {
      /*
       * While the symbol table of the archive with an odd size precedes the
       * member.
       */
      TxArchiveAdd( &ctx->archive, "/", (const uint8_t *) "\0\0\0\0\0", 5, 0 );
      break;
    }

    case NopinionReqInputArchive_Pre_Before_SymbolTable64: {
      /*
       * While the 64-bit symbol table of the archive precedes the member.
       */
      TxArchiveAdd(
        &ctx->archive,
        "/SYM64/",
        (const uint8_t *) "\0\0\0\0\0\0\0\0",
        8,
        0
      );
      break;
    }

    case NopinionReqInputArchive_Pre_Before_NA:
      break;
  }
}

static void NopinionReqInputArchive_Pre_Name_Prepare(
  NopinionReqInputArchive_Context *ctx,
  NopinionReqInputArchive_Pre_Name state
)
{
  switch ( state ) {
    case NopinionReqInputArchive_Pre_Name_Short: {
      /*
       * While the member header holds the name of the member.
       */
      ctx->name = "a.o/";
      ctx->member = "a.o";
      break;
    }

    case NopinionReqInputArchive_Pre_Name_ShortFull: {
      /*
       * While the member header holds the name of the member in all 16 bytes
       * of the name field.
       */
      ctx->name = "abcdefghijklmn.o";
      ctx->member = "abcdefghijklmn.o";
      break;
    }

    case NopinionReqInputArchive_Pre_Name_Long: {
      /*
       * While the member header refers to the name of the member in the long
       * name table.
       */
      TxArchiveAdd(
        &ctx->archive,
        "//",
        (const uint8_t *) "long-member-name.o/\n",
        20,
        0
      );
      ctx->name = "/0";
      ctx->member = "long-member-name.o";
      break;
    }

    case NopinionReqInputArchive_Pre_Name_LongNewline: {
      /*
       * While the member header refers to the name of the member in the long
       * name table, while the name ends with a newline.
       */
      TxArchiveAdd(
        &ctx->archive,
        "//",
        (const uint8_t *) "long-member-name.o\n",
        19,
        0
      );
      ctx->name = "/0";
      ctx->member = "long-member-name.o";
      break;
    }

    case NopinionReqInputArchive_Pre_Name_NoTable: {
      /*
       * While the member header refers to a long name and the archive has no
       * long name table.
       */
      ctx->name = "/0";
      break;
    }

    case NopinionReqInputArchive_Pre_Name_Beyond: {
      /*
       * While the member header refers to a long name beyond the long name
       * table.
       */
      TxArchiveAdd(
        &ctx->archive,
        "//",
        (const uint8_t *) "long-member-name.o/\n",
        20,
        0
      );
      ctx->name = "/99";
      break;
    }

    case NopinionReqInputArchive_Pre_Name_NA:
      break;
  }
}

static void NopinionReqInputArchive_Pre_Content_Prepare(
  NopinionReqInputArchive_Context    *ctx,
  NopinionReqInputArchive_Pre_Content state
)
{
  switch ( state ) {
    case NopinionReqInputArchive_Pre_Content_Elf: {
      /*
       * While the member is a valid ELF file.
       */
      ctx->elf = true;
      break;
    }

    case NopinionReqInputArchive_Pre_Content_Other: {
      /*
       * While the member is no ELF file.
       */
      ctx->elf = false;
      break;
    }

    case NopinionReqInputArchive_Pre_Content_NA:
      break;
  }
}

static void NopinionReqInputArchive_Pre_Size_Prepare(
  NopinionReqInputArchive_Context *ctx,
  NopinionReqInputArchive_Pre_Size state
)
{
  switch ( state ) {
    case NopinionReqInputArchive_Pre_Size_Valid: {
      /*
       * While the size field of the member header matches the member.
       */
      ctx->excess = 0;
      break;
    }

    case NopinionReqInputArchive_Pre_Size_Truncated: {
      /*
       * While the size field of the member header exceeds the archive.
       */
      ctx->excess = 1000;
      break;
    }

    case NopinionReqInputArchive_Pre_Size_Empty: {
      /*
       * While the archive holds no member after the members before it.
       */
      ctx->empty = true;
      break;
    }

    case NopinionReqInputArchive_Pre_Size_NA:
      break;
  }
}

static void NopinionReqInputArchive_Post_Error_Check(
  NopinionReqInputArchive_Context   *ctx,
  NopinionReqInputArchive_Post_Error state
)
{
  switch ( state ) {
    case NopinionReqInputArchive_Post_Error_None: {
      /*
       * The errata checker shall report no error.
       */
      T_eq_str( TxErrors(), "" );
      break;
    }

    case NopinionReqInputArchive_Post_Error_NotElf: {
      /*
       * The errata checker shall report the error "not an ELF file" for the
       * member.
       */
      char expected[ 64 ];

      (void) snprintf(
        expected,
        sizeof( expected ),
        "nopinion: t.o(%s): not an ELF file\n",
        ctx->member
      );
      T_eq_str( TxErrors(), expected );
      break;
    }

    case NopinionReqInputArchive_Post_Error_BadLongName: {
      /*
       * The errata checker shall report the error "bad long member name" for
       * the archive.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: bad long member name\n" );
      break;
    }

    case NopinionReqInputArchive_Post_Error_Truncated: {
      /*
       * The errata checker shall report the error "truncated archive" for the
       * archive.
       */
      T_eq_str( TxErrors(), "nopinion: t.o: truncated archive\n" );
      break;
    }

    case NopinionReqInputArchive_Post_Error_NA:
      break;
  }
}

static void NopinionReqInputArchive_Post_Member_Check(
  NopinionReqInputArchive_Context    *ctx,
  NopinionReqInputArchive_Post_Member state
)
{
  switch ( state ) {
    case NopinionReqInputArchive_Post_Member_Checked: {
      /*
       * The errata checker shall check the member and name it in the report.
       */
      char prefix[ 64 ];

      (void) snprintf(
        prefix,
        sizeof( prefix ),
        "t.o(%s): .text+0x0 <f+0x0>: TN-0009 ",
        ctx->member
      );
      T_eq_int( strncmp( ctx->report, prefix, strlen( prefix ) ), 0 );
      break;
    }

    case NopinionReqInputArchive_Post_Member_NotChecked: {
      /*
       * The errata checker shall check no member.
       */
      T_eq_str( ctx->report, "" );
      break;
    }

    case NopinionReqInputArchive_Post_Member_NA:
      break;
  }
}

static void NopinionReqInputArchive_Prepare(
  NopinionReqInputArchive_Context *ctx
)
{
  TxArchiveInit( &ctx->archive );
  ctx->name = "a.o/";
  ctx->member = "a.o";
  ctx->empty = false;
}

static void NopinionReqInputArchive_Action(
  NopinionReqInputArchive_Context *ctx
)
{
  if ( !ctx->empty ) {
    uint8_t buf[ 4096 ];
    size_t  size;

    if ( ctx->elf ) {
      TxImage image;

      TxImageInit( &image );
      TxAppend( &image, TxSt() );
      TxAppend( &image, TxAdd() );
      TxAppend( &image, TxSt() );
      size = TxBuildElf( &image, buf, sizeof( buf ) );
    } else {
      memcpy( buf, "text", 4 );
      size = 4;
    }

    TxArchiveAdd( &ctx->archive, ctx->name, buf, size, ctx->excess );
  }

  ctx->report = TxCheckBuffer(
    ctx->archive.buf,
    ctx->archive.size,
    NOTE_0009
  );
}

/* clang-format off */

static const NopinionReqInputArchive_Entry
NopinionReqInputArchive_Entries[] = {
  { 0, 0, 0, 0, 0, NopinionReqInputArchive_Post_Error_Truncated,
    NopinionReqInputArchive_Post_Member_NotChecked },
  { 0, 0, 0, 1, 0, NopinionReqInputArchive_Post_Error_None,
    NopinionReqInputArchive_Post_Member_NotChecked },
  { 1, 0, 0, 0, 0, NopinionReqInputArchive_Post_Error_NA,
    NopinionReqInputArchive_Post_Member_NA },
  { 0, 0, 0, 0, 0, NopinionReqInputArchive_Post_Error_None,
    NopinionReqInputArchive_Post_Member_Checked },
  { 0, 0, 0, 0, 0, NopinionReqInputArchive_Post_Error_NotElf,
    NopinionReqInputArchive_Post_Member_NotChecked },
  { 0, 0, 0, 0, 0, NopinionReqInputArchive_Post_Error_BadLongName,
    NopinionReqInputArchive_Post_Member_NotChecked }
};

static const uint8_t
NopinionReqInputArchive_Map[] = {
  3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 5, 0,
  1, 5, 0, 2, 5, 0, 1, 5, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4,
  0, 2, 3, 0, 1, 4, 0, 2, 5, 0, 1, 5, 0, 2, 5, 0, 1, 5, 0, 2, 3, 0, 1, 4, 0, 2,
  3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 5, 0, 1, 5, 0, 2, 5, 0,
  1, 5, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4, 0, 2, 3, 0, 1, 4,
  0, 2, 5, 0, 1, 5, 0, 2, 5, 0, 1, 5, 0, 2
};

/* clang-format on */

static size_t NopinionReqInputArchive_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqInputArchive_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqInputArchive_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqInputArchive_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqInputArchive_Scope,
  .initial_context = &NopinionReqInputArchive_Instance
};

static inline NopinionReqInputArchive_Entry NopinionReqInputArchive_PopEntry(
  NopinionReqInputArchive_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqInputArchive_Entries
    [ NopinionReqInputArchive_Map[ index ] ];
}

static void NopinionReqInputArchive_SetPreConditionStates(
  NopinionReqInputArchive_Context *ctx
)
{
  ctx->Map.pcs[ 0 ] = ctx->Map.pci[ 0 ];
  ctx->Map.pcs[ 1 ] = ctx->Map.pci[ 1 ];

  if ( ctx->Map.entry.Pre_Content_NA ) {
    ctx->Map.pcs[ 2 ] = NopinionReqInputArchive_Pre_Content_NA;
  } else {
    ctx->Map.pcs[ 2 ] = ctx->Map.pci[ 2 ];
  }

  ctx->Map.pcs[ 3 ] = ctx->Map.pci[ 3 ];
}

static void NopinionReqInputArchive_TestVariant(
  NopinionReqInputArchive_Context *ctx
)
{
  NopinionReqInputArchive_Pre_Before_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqInputArchive_Pre_Name_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqInputArchive_Pre_Content_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqInputArchive_Pre_Size_Prepare( ctx, ctx->Map.pcs[ 3 ] );
  NopinionReqInputArchive_Action( ctx );
  NopinionReqInputArchive_Post_Error_Check( ctx, ctx->Map.entry.Post_Error );
  NopinionReqInputArchive_Post_Member_Check( ctx, ctx->Map.entry.Post_Member );
}

/**
 * @fn void T_case_body_NopinionReqInputArchive( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqInputArchive,
  &NopinionReqInputArchive_Fixture
)
{
  NopinionReqInputArchive_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pci[ 0 ] = NopinionReqInputArchive_Pre_Before_None;
    ctx->Map.pci[ 0 ] < NopinionReqInputArchive_Pre_Before_NA;
    ++ctx->Map.pci[ 0 ]
  ) {
    for (
      ctx->Map.pci[ 1 ] = NopinionReqInputArchive_Pre_Name_Short;
      ctx->Map.pci[ 1 ] < NopinionReqInputArchive_Pre_Name_NA;
      ++ctx->Map.pci[ 1 ]
    ) {
      for (
        ctx->Map.pci[ 2 ] = NopinionReqInputArchive_Pre_Content_Elf;
        ctx->Map.pci[ 2 ] < NopinionReqInputArchive_Pre_Content_NA;
        ++ctx->Map.pci[ 2 ]
      ) {
        for (
          ctx->Map.pci[ 3 ] = NopinionReqInputArchive_Pre_Size_Valid;
          ctx->Map.pci[ 3 ] < NopinionReqInputArchive_Pre_Size_NA;
          ++ctx->Map.pci[ 3 ]
        ) {
          ctx->Map.entry = NopinionReqInputArchive_PopEntry( ctx );

          if ( ctx->Map.entry.Skip ) {
            continue;
          }

          NopinionReqInputArchive_SetPreConditionStates( ctx );
          NopinionReqInputArchive_Prepare( ctx );
          NopinionReqInputArchive_TestVariant( ctx );
        }
      }
    }
  }
}

/** @} */
