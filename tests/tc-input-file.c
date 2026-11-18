/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqInputFile
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nopinion.h"
#include "tx-support.h"

#include <rtems/test.h>

/**
 * @defgroup NopinionReqInputFile spec:/nopinion/req/input-file
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqInputFile_Pre_File_Elf,
  NopinionReqInputFile_Pre_File_Archive,
  NopinionReqInputFile_Pre_File_Thin,
  NopinionReqInputFile_Pre_File_Short,
  NopinionReqInputFile_Pre_File_Empty,
  NopinionReqInputFile_Pre_File_Missing,
  NopinionReqInputFile_Pre_File_NoStatus,
  NopinionReqInputFile_Pre_File_NoMapping,
  NopinionReqInputFile_Pre_File_NA
} NopinionReqInputFile_Pre_File;

typedef enum {
  NopinionReqInputFile_Post_Error_None,
  NopinionReqInputFile_Post_Error_Message,
  NopinionReqInputFile_Post_Error_NA
} NopinionReqInputFile_Post_Error;

typedef enum {
  NopinionReqInputFile_Post_Checked_Yes,
  NopinionReqInputFile_Post_Checked_No,
  NopinionReqInputFile_Post_Checked_NA
} NopinionReqInputFile_Post_Checked;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_File_NA : 1;
  uint8_t Post_Error : 2;
  uint8_t Post_Checked : 2;
} NopinionReqInputFile_Entry;

/**
 * @brief Test context for spec:/nopinion/req/input-file test case.
 */
typedef struct {
  /**
   * @brief This member contains the image of the ELF file.
   */
  TxImage image;

  /**
   * @brief This member contains the archive.
   */
  TxArchive archive;

  /**
   * @brief This member contains the content of the file.
   */
  uint8_t buf[ 8192 ];

  /**
   * @brief This member contains the size of the file.
   */
  size_t size;

  /**
   * @brief This member is true, if the file does not exist.
   */
  bool missing;

  /**
   * @brief This member specifies the functions which shall fail.
   */
  unsigned int fail;

  /**
   * @brief This member contains the expected error message.
   */
  const char *message;

  /**
   * @brief This member contains the temporary directory.
   */
  char dir[ 32 ];

  /**
   * @brief This member contains the path of the file.
   */
  char path[ 64 ];

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
    NopinionReqInputFile_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqInputFile_Context;

static NopinionReqInputFile_Context NopinionReqInputFile_Instance;

static const char *const NopinionReqInputFile_PreDesc_File[] = {
  "Elf",
  "Archive",
  "Thin",
  "Short",
  "Empty",
  "Missing",
  "NoStatus",
  "NoMapping",
  "NA"
};

static const char *const *const NopinionReqInputFile_PreDesc[] = {
  NopinionReqInputFile_PreDesc_File,
  NULL
};

static void NopinionReqInputFile_Pre_File_Prepare(
  NopinionReqInputFile_Context *ctx,
  NopinionReqInputFile_Pre_File state
)
{
  switch ( state ) {
    case NopinionReqInputFile_Pre_File_Elf: {
      /*
       * While the file is a valid ELF file.
       */
      ctx->size = TxBuildElf( &ctx->image, ctx->buf, sizeof( ctx->buf ) );
      break;
    }

    case NopinionReqInputFile_Pre_File_Archive: {
      /*
       * While the file is an archive with a valid ELF file.
       */
      TxArchive *ar = &ctx->archive;
      size_t size = TxBuildElf( &ctx->image, ctx->buf, sizeof( ctx->buf ) );

      TxArchiveInit( ar );
      TxArchiveAdd( ar, "a.o/", ctx->buf, size, 0 );
      memcpy( ctx->buf, ar->buf, ar->size );
      ctx->size = ar->size;
      break;
    }

    case NopinionReqInputFile_Pre_File_Thin: {
      /*
       * While the file is a thin archive.
       */
      memcpy( ctx->buf, "!<thin>\n", 8 );
      ctx->size = 8;
      ctx->message = "thin archives are not supported";
      break;
    }

    case NopinionReqInputFile_Pre_File_Short: {
      /*
       * While the file is shorter than the magic string of an archive.
       */
      memcpy( ctx->buf, "\177ELF", 4 );
      ctx->size = 4;
      ctx->message = "not an ELF file";
      break;
    }

    case NopinionReqInputFile_Pre_File_Empty: {
      /*
       * While the file is empty.
       */
      ctx->size = 0;
      ctx->message = "empty file";
      break;
    }

    case NopinionReqInputFile_Pre_File_Missing: {
      /*
       * While the file does not exist.
       */
      ctx->missing = true;
      ctx->message = "No such file or directory";
      break;
    }

    case NopinionReqInputFile_Pre_File_NoStatus: {
      /*
       * While the file is a valid ELF file, while the query of its status
       * fails.
       */
      ctx->size = TxBuildElf( &ctx->image, ctx->buf, sizeof( ctx->buf ) );
      ctx->fail = TX_FAIL_FSTAT;
      ctx->message = "Cannot allocate memory";
      break;
    }

    case NopinionReqInputFile_Pre_File_NoMapping: {
      /*
       * While the file is a valid ELF file, while the mapping of its content
       * fails.
       */
      ctx->size = TxBuildElf( &ctx->image, ctx->buf, sizeof( ctx->buf ) );
      ctx->fail = TX_FAIL_MMAP;
      ctx->message = "Cannot allocate memory";
      break;
    }

    case NopinionReqInputFile_Pre_File_NA:
      break;
  }
}

static void NopinionReqInputFile_Post_Error_Check(
  NopinionReqInputFile_Context   *ctx,
  NopinionReqInputFile_Post_Error state
)
{
  switch ( state ) {
    case NopinionReqInputFile_Post_Error_None: {
      /*
       * The errata checker shall report no error.
       */
      T_eq_str( TxErrors(), "" );
      break;
    }

    case NopinionReqInputFile_Post_Error_Message: {
      /*
       * The errata checker shall report the error message of the file for the
       * file.
       */
      char expected[ 128 ];

      (void) snprintf(
        expected,
        sizeof( expected ),
        "nopinion: %s: %s\n",
        ctx->path,
        ctx->message
      );
      T_eq_str( TxErrors(), expected );
      break;
    }

    case NopinionReqInputFile_Post_Error_NA:
      break;
  }
}

static void NopinionReqInputFile_Post_Checked_Check(
  NopinionReqInputFile_Context     *ctx,
  NopinionReqInputFile_Post_Checked state
)
{
  switch ( state ) {
    case NopinionReqInputFile_Post_Checked_Yes: {
      /*
       * The errata checker shall check the code section of the file.
       */
      T_not_null( strstr( ctx->report, ": TN-0009 back-to-back-store\n" ) );
      break;
    }

    case NopinionReqInputFile_Post_Checked_No: {
      /*
       * The errata checker shall check no code section.
       */
      T_eq_str( ctx->report, "" );
      break;
    }

    case NopinionReqInputFile_Post_Checked_NA:
      break;
  }
}

static void NopinionReqInputFile_Setup( NopinionReqInputFile_Context *ctx )
{
  strcpy( ctx->dir, "tx-file-XXXXXX" );
  T_assert_not_null( mkdtemp( ctx->dir ) );
  (void) snprintf( ctx->path, sizeof( ctx->path ), "%s/t.o", ctx->dir );
}

static void NopinionReqInputFile_Setup_Wrap( void *arg )
{
  NopinionReqInputFile_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqInputFile_Setup( ctx );
}

static void NopinionReqInputFile_Teardown( NopinionReqInputFile_Context *ctx )
{
  T_eq_int( rmdir( ctx->dir ), 0 );
}

static void NopinionReqInputFile_Teardown_Wrap( void *arg )
{
  NopinionReqInputFile_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqInputFile_Teardown( ctx );
}

static void NopinionReqInputFile_Prepare( NopinionReqInputFile_Context *ctx )
{
  TxImageInit( &ctx->image );
  TxAppend( &ctx->image, TxSt() );
  TxAppend( &ctx->image, TxAdd() );
  TxAppend( &ctx->image, TxSt() );
  ctx->missing = false;
  ctx->fail = 0;
  ctx->message = "";
}

static void NopinionReqInputFile_Action( NopinionReqInputFile_Context *ctx )
{
  if ( !ctx->missing ) {
    FILE *f = fopen( ctx->path, "wb" );

    T_assert_not_null( f );
    T_assert_eq_sz( fwrite( ctx->buf, 1, ctx->size, f ), ctx->size );
    T_assert_eq_int( fclose( f ), 0 );
  }

  TxFailNext( ctx->fail );
  ctx->report = TxCheckFile( ctx->path, NOTE_0009 );
  TxFailNext( 0 );
  (void) unlink( ctx->path );
}

/* clang-format off */

static const NopinionReqInputFile_Entry
NopinionReqInputFile_Entries[] = {
  { 0, 0, NopinionReqInputFile_Post_Error_Message,
    NopinionReqInputFile_Post_Checked_No },
  { 0, 0, NopinionReqInputFile_Post_Error_None,
    NopinionReqInputFile_Post_Checked_Yes }
};

static const uint8_t
NopinionReqInputFile_Map[] = {
  1, 1, 0, 0, 0, 0, 0, 0
};

/* clang-format on */

static size_t NopinionReqInputFile_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqInputFile_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqInputFile_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqInputFile_Fixture = {
  .setup = NopinionReqInputFile_Setup_Wrap,
  .stop = NULL,
  .teardown = NopinionReqInputFile_Teardown_Wrap,
  .scope = NopinionReqInputFile_Scope,
  .initial_context = &NopinionReqInputFile_Instance
};

static inline NopinionReqInputFile_Entry NopinionReqInputFile_PopEntry(
  NopinionReqInputFile_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqInputFile_Entries[ NopinionReqInputFile_Map[ index ] ];
}

static void NopinionReqInputFile_TestVariant(
  NopinionReqInputFile_Context *ctx
)
{
  NopinionReqInputFile_Pre_File_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqInputFile_Action( ctx );
  NopinionReqInputFile_Post_Error_Check( ctx, ctx->Map.entry.Post_Error );
  NopinionReqInputFile_Post_Checked_Check( ctx, ctx->Map.entry.Post_Checked );
}

/**
 * @fn void T_case_body_NopinionReqInputFile( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqInputFile, &NopinionReqInputFile_Fixture )
{
  NopinionReqInputFile_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqInputFile_Pre_File_Elf;
    ctx->Map.pcs[ 0 ] < NopinionReqInputFile_Pre_File_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    ctx->Map.entry = NopinionReqInputFile_PopEntry( ctx );
    NopinionReqInputFile_Prepare( ctx );
    NopinionReqInputFile_TestVariant( ctx );
  }
}

/** @} */
