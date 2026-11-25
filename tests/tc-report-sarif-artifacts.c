/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqReportSarifArtifacts
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
#include <sys/stat.h>

#include "nopinion.h"
#include "tx-support.h"

#include <rtems/test.h>

/**
 * @defgroup NopinionReqReportSarifArtifacts \
 *   spec:/nopinion/req/report-sarif-artifacts
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqReportSarifArtifacts_Pre_Operands_One,
  NopinionReqReportSarifArtifacts_Pre_Operands_Twice,
  NopinionReqReportSarifArtifacts_Pre_Operands_Two,
  NopinionReqReportSarifArtifacts_Pre_Operands_Based,
  NopinionReqReportSarifArtifacts_Pre_Operands_NA
} NopinionReqReportSarifArtifacts_Pre_Operands;

typedef enum {
  NopinionReqReportSarifArtifacts_Pre_Members_Distinct,
  NopinionReqReportSarifArtifacts_Pre_Members_Duplicate,
  NopinionReqReportSarifArtifacts_Pre_Members_NA
} NopinionReqReportSarifArtifacts_Pre_Members;

typedef enum {
  NopinionReqReportSarifArtifacts_Post_Artifacts_OneDistinct,
  NopinionReqReportSarifArtifacts_Post_Artifacts_OneDuplicate,
  NopinionReqReportSarifArtifacts_Post_Artifacts_TwoDistinct,
  NopinionReqReportSarifArtifacts_Post_Artifacts_TwoDuplicate,
  NopinionReqReportSarifArtifacts_Post_Artifacts_BasedDistinct,
  NopinionReqReportSarifArtifacts_Post_Artifacts_BasedDuplicate,
  NopinionReqReportSarifArtifacts_Post_Artifacts_NA
} NopinionReqReportSarifArtifacts_Post_Artifacts;

typedef enum {
  NopinionReqReportSarifArtifacts_Post_Indices_OneDistinct,
  NopinionReqReportSarifArtifacts_Post_Indices_OneDuplicate,
  NopinionReqReportSarifArtifacts_Post_Indices_TwiceDistinct,
  NopinionReqReportSarifArtifacts_Post_Indices_TwiceDuplicate,
  NopinionReqReportSarifArtifacts_Post_Indices_TwoDistinct,
  NopinionReqReportSarifArtifacts_Post_Indices_TwoDuplicate,
  NopinionReqReportSarifArtifacts_Post_Indices_NA
} NopinionReqReportSarifArtifacts_Post_Indices;

typedef struct {
  uint16_t Skip : 1;
  uint16_t Pre_Operands_NA : 1;
  uint16_t Pre_Members_NA : 1;
  uint16_t Post_Artifacts : 3;
  uint16_t Post_Indices : 3;
} NopinionReqReportSarifArtifacts_Entry;

/**
 * @brief Test context for spec:/nopinion/req/report-sarif-artifacts test case.
 */
typedef struct {
  /**
   * @brief This member contains the temporary directory.
   */
  char dir[ 32 ];

  /**
   * @brief This member contains the path of the first archive.
   */
  char a[ 48 ];

  /**
   * @brief This member contains the path of the second archive.
   */
  char b[ 48 ];

  /**
   * @brief This member contains the path of the archive x/a.a.
   */
  char x[ 48 ];

  /**
   * @brief This member contains the path of the archive y/a.a.
   */
  char y[ 48 ];

  /**
   * @brief This member contains the argument of the option -b X=DIR/x.
   */
  char base_x[ 48 ];

  /**
   * @brief This member contains the argument of the option -b W=DIR.
   */
  char base_w[ 48 ];

  /**
   * @brief This member contains the argument of the option -b Y=DIR/y.
   */
  char base_y[ 48 ];

  /**
   * @brief This member is true, if the options -b X=DIR/x, -b W=DIR and -b
   *   Y=DIR/y are given.
   */
  bool based;

  /**
   * @brief This member contains the file operands.
   */
  const char *files[ 2 ];

  /**
   * @brief This member contains the name field of the second member of an
   *   archive.
   */
  const char *second;

  /**
   * @brief This member contains the exit status.
   */
  int status;

  /**
   * @brief This member references the standard output.
   */
  const char *out;

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
    NopinionReqReportSarifArtifacts_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqReportSarifArtifacts_Context;

static NopinionReqReportSarifArtifacts_Context
  NopinionReqReportSarifArtifacts_Instance;

static const char *const NopinionReqReportSarifArtifacts_PreDesc_Operands[] =
  { "One", "Twice", "Two", "Based", "NA" };

static const char *const NopinionReqReportSarifArtifacts_PreDesc_Members[] =
  { "Distinct", "Duplicate", "NA" };

static const char *const *const NopinionReqReportSarifArtifacts_PreDesc[] = {
  NopinionReqReportSarifArtifacts_PreDesc_Operands,
  NopinionReqReportSarifArtifacts_PreDesc_Members,
  NULL
};

/*
 * Checks that the last line of the log holds the artifacts.  Each %s of the
 * format, if any, stands for the temporary directory.
 */
static void CheckArtifacts(
  const NopinionReqReportSarifArtifacts_Context *ctx,
  const char                                    *format
)
{
  char        artifacts[ 512 ];
  char        expected[ 640 ];
  const char *last = ctx->out + strlen( ctx->out ) - 1;

  while ( last > ctx->out && last[ -1 ] != '\n' ) {
    --last;
  }

  (void)
    snprintf( artifacts, sizeof( artifacts ), format, ctx->dir, ctx->dir );
  (void) snprintf(
    expected,
    sizeof( expected ),
    "],\"artifacts\":[%s],\"invocations\":[{\"executionSuccessful\":true}]}]}\n",
    artifacts
  );
  T_eq_str( last, expected );
}

typedef struct {
  const char  *member;
  unsigned int index;
} TxSarifIndex;

/*
 * Checks the artifact location of each result in the order of the results
 */
static void CheckIndices(
  const NopinionReqReportSarifArtifacts_Context *ctx,
  const TxSarifIndex                            *indices,
  size_t                                         count
)
{
  const char *s = ctx->out;
  size_t      i;

  for ( i = 0; i < count; ++i ) {
    char expected[ 64 ];

    (void) snprintf(
      expected,
      sizeof( expected ),
      "\"artifactLocation\":{\"uri\":\"%s\",\"index\":%u}",
      indices[ i ].member,
      indices[ i ].index
    );
    s = strstr( s, expected );
    T_assert_not_null( s );
    ++s;
  }

  T_null( strstr( s, "\"artifactLocation\"" ) );
}

static void NopinionReqReportSarifArtifacts_Pre_Operands_Prepare(
  NopinionReqReportSarifArtifacts_Context     *ctx,
  NopinionReqReportSarifArtifacts_Pre_Operands state
)
{
  switch ( state ) {
    case NopinionReqReportSarifArtifacts_Pre_Operands_One: {
      /*
       * While the file operand names an archive.
       */
      ctx->files[ 0 ] = ctx->a;
      ctx->files[ 1 ] = NULL;
      break;
    }

    case NopinionReqReportSarifArtifacts_Pre_Operands_Twice: {
      /*
       * While two file operands name the same archive.
       */
      ctx->files[ 0 ] = ctx->a;
      ctx->files[ 1 ] = ctx->a;
      break;
    }

    case NopinionReqReportSarifArtifacts_Pre_Operands_Two: {
      /*
       * While two file operands name two archives with the same members.
       */
      ctx->files[ 0 ] = ctx->a;
      ctx->files[ 1 ] = ctx->b;
      break;
    }

    case NopinionReqReportSarifArtifacts_Pre_Operands_Based: {
      /*
       * While the options -b X=DIR/x, -b W=DIR and -b Y=DIR/y are given in
       * this order, while two file operands name the archives x/a.a and y/a.a
       * of the directory DIR with the same members.
       */
      ctx->files[ 0 ] = ctx->x;
      ctx->files[ 1 ] = ctx->y;
      (void)
        snprintf( ctx->base_x, sizeof( ctx->base_x ), "X=%s/x", ctx->dir );
      (void) snprintf( ctx->base_w, sizeof( ctx->base_w ), "W=%s", ctx->dir );
      (void)
        snprintf( ctx->base_y, sizeof( ctx->base_y ), "Y=%s/y", ctx->dir );
      ctx->based = true;
      break;
    }

    case NopinionReqReportSarifArtifacts_Pre_Operands_NA:
      break;
  }
}

static void NopinionReqReportSarifArtifacts_Pre_Members_Prepare(
  NopinionReqReportSarifArtifacts_Context    *ctx,
  NopinionReqReportSarifArtifacts_Pre_Members state
)
{
  switch ( state ) {
    case NopinionReqReportSarifArtifacts_Pre_Members_Distinct: {
      /*
       * While each archive holds the members m.o and nn.o, each with one
       * finding.
       */
      ctx->second = "nn.o/";
      break;
    }

    case NopinionReqReportSarifArtifacts_Pre_Members_Duplicate: {
      /*
       * While each archive holds two members with the name m.o, each with one
       * finding.
       */
      ctx->second = "m.o/";
      break;
    }

    case NopinionReqReportSarifArtifacts_Pre_Members_NA:
      break;
  }
}

static void NopinionReqReportSarifArtifacts_Post_Artifacts_Check(
  NopinionReqReportSarifArtifacts_Context       *ctx,
  NopinionReqReportSarifArtifacts_Post_Artifacts state
)
{
  switch ( state ) {
    case NopinionReqReportSarifArtifacts_Post_Artifacts_OneDistinct: {
      /*
       * The artifacts of the run shall be the archive, the member m.o with the
       * parent index 0 and the member nn.o with the parent index 0.
       */
      CheckArtifacts(
        ctx,
        "{\"location\":{\"uri\":\"%s/a.a\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"nn.o\"},\"parentIndex\":0}"
      );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Artifacts_OneDuplicate: {
      /*
       * The artifacts of the run shall be the archive and the member m.o with
       * the parent index 0.
       */
      CheckArtifacts(
        ctx,
        "{\"location\":{\"uri\":\"%s/a.a\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":0}"
      );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Artifacts_TwoDistinct: {
      /*
       * The artifacts of the run shall be the first archive, its members m.o
       * and nn.o with the parent index 0, the second archive, and its members
       * m.o and nn.o with the parent index 3.
       */
      CheckArtifacts(
        ctx,
        "{\"location\":{\"uri\":\"%s/a.a\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"nn.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"%s/b.a\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":3},"
        "{\"location\":{\"uri\":\"nn.o\"},\"parentIndex\":3}"
      );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Artifacts_TwoDuplicate: {
      /*
       * The artifacts of the run shall be the first archive, its member m.o
       * with the parent index 0, the second archive, and its member m.o with
       * the parent index 2.
       */
      CheckArtifacts(
        ctx,
        "{\"location\":{\"uri\":\"%s/a.a\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"%s/b.a\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":2}"
      );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Artifacts_BasedDistinct: {
      /*
       * The artifacts of the run shall be the archive a.a of the URI base id
       * X, its members m.o and nn.o with the parent index 0, the archive a.a
       * of the URI base id Y, and its members m.o and nn.o with the parent
       * index 3.
       */
      CheckArtifacts(
        ctx,
        "{\"location\":{\"uri\":\"a.a\",\"uriBaseId\":\"X\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"nn.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"a.a\",\"uriBaseId\":\"Y\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":3},"
        "{\"location\":{\"uri\":\"nn.o\"},\"parentIndex\":3}"
      );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Artifacts_BasedDuplicate: {
      /*
       * The artifacts of the run shall be the archive a.a of the URI base id
       * X, its member m.o with the parent index 0, the archive a.a of the URI
       * base id Y, and its member m.o with the parent index 2.
       */
      CheckArtifacts(
        ctx,
        "{\"location\":{\"uri\":\"a.a\",\"uriBaseId\":\"X\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":0},"
        "{\"location\":{\"uri\":\"a.a\",\"uriBaseId\":\"Y\"}},"
        "{\"location\":{\"uri\":\"m.o\"},\"parentIndex\":2}"
      );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Artifacts_NA:
      break;
  }
}

static void NopinionReqReportSarifArtifacts_Post_Indices_Check(
  NopinionReqReportSarifArtifacts_Context     *ctx,
  NopinionReqReportSarifArtifacts_Post_Indices state
)
{
  switch ( state ) {
    case NopinionReqReportSarifArtifacts_Post_Indices_OneDistinct: {
      /*
       * The results shall name the member m.o of the artifact 1 and the member
       * nn.o of the artifact 2.
       */
      static const TxSarifIndex indices[] = { { "m.o", 1 }, { "nn.o", 2 } };

      CheckIndices( ctx, indices, 2 );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Indices_OneDuplicate: {
      /*
       * The results shall name the member m.o of the artifact 1 twice.
       */
      static const TxSarifIndex indices[] = { { "m.o", 1 }, { "m.o", 1 } };

      CheckIndices( ctx, indices, 2 );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Indices_TwiceDistinct: {
      /*
       * The results shall name the member m.o of the artifact 1, the member
       * nn.o of the artifact 2, the member m.o of the artifact 1 and the
       * member nn.o of the artifact 2.
       */
      static const TxSarifIndex indices[] =
        { { "m.o", 1 }, { "nn.o", 2 }, { "m.o", 1 }, { "nn.o", 2 } };

      CheckIndices( ctx, indices, 4 );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Indices_TwiceDuplicate: {
      /*
       * The results shall name the member m.o of the artifact 1 four times.
       */
      static const TxSarifIndex indices[] =
        { { "m.o", 1 }, { "m.o", 1 }, { "m.o", 1 }, { "m.o", 1 } };

      CheckIndices( ctx, indices, 4 );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Indices_TwoDistinct: {
      /*
       * The results shall name the member m.o of the artifact 1, the member
       * nn.o of the artifact 2, the member m.o of the artifact 4 and the
       * member nn.o of the artifact 5.
       */
      static const TxSarifIndex indices[] =
        { { "m.o", 1 }, { "nn.o", 2 }, { "m.o", 4 }, { "nn.o", 5 } };

      CheckIndices( ctx, indices, 4 );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Indices_TwoDuplicate: {
      /*
       * The results shall name the member m.o of the artifact 1 twice and the
       * member m.o of the artifact 3 twice.
       */
      static const TxSarifIndex indices[] =
        { { "m.o", 1 }, { "m.o", 1 }, { "m.o", 3 }, { "m.o", 3 } };

      CheckIndices( ctx, indices, 4 );
      break;
    }

    case NopinionReqReportSarifArtifacts_Post_Indices_NA:
      break;
  }
}

static void NopinionReqReportSarifArtifacts_Setup(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  char path[ 48 ];

  strcpy( ctx->dir, "tx-artifacts-XXXXXX" );
  T_assert_not_null( mkdtemp( ctx->dir ) );
  (void) snprintf( ctx->a, sizeof( ctx->a ), "%s/a.a", ctx->dir );
  (void) snprintf( ctx->b, sizeof( ctx->b ), "%s/b.a", ctx->dir );
  (void) snprintf( ctx->x, sizeof( ctx->x ), "%s/x/a.a", ctx->dir );
  (void) snprintf( ctx->y, sizeof( ctx->y ), "%s/y/a.a", ctx->dir );
  (void) snprintf( path, sizeof( path ), "%s/x", ctx->dir );
  T_assert_eq_int( mkdir( path, 0700 ), 0 );
  (void) snprintf( path, sizeof( path ), "%s/y", ctx->dir );
  T_assert_eq_int( mkdir( path, 0700 ), 0 );
}

static void NopinionReqReportSarifArtifacts_Setup_Wrap( void *arg )
{
  NopinionReqReportSarifArtifacts_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqReportSarifArtifacts_Setup( ctx );
}

static void NopinionReqReportSarifArtifacts_Teardown(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  char path[ 48 ];

  (void) snprintf( path, sizeof( path ), "%s/x", ctx->dir );
  T_eq_int( rmdir( path ), 0 );
  (void) snprintf( path, sizeof( path ), "%s/y", ctx->dir );
  T_eq_int( rmdir( path ), 0 );
  T_eq_int( rmdir( ctx->dir ), 0 );
}

static void NopinionReqReportSarifArtifacts_Teardown_Wrap( void *arg )
{
  NopinionReqReportSarifArtifacts_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqReportSarifArtifacts_Teardown( ctx );
}

static void NopinionReqReportSarifArtifacts_Prepare(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  ctx->based = false;
}

static void NopinionReqReportSarifArtifacts_Action(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  TxImage     image;
  uint8_t     buf[ 4096 ];
  size_t      size;
  char       *argv[ 14 ];
  int         argc = 0;
  size_t      i;
  const char *names[ 2 ];

  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxAdd() );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxLd() );
  size = TxBuildElf( &image, buf, sizeof( buf ) );
  names[ 0 ] = ctx->files[ 0 ];
  names[ 1 ] = ctx->files[ 1 ];

  for ( i = 0; i < 2 && names[ i ] != NULL; ++i ) {
    TxArchive archive;
    FILE     *f;

    TxArchiveInit( &archive );
    TxArchiveAdd( &archive, "m.o/", buf, size, 0 );
    TxArchiveAdd( &archive, ctx->second, buf, size, 0 );
    f = fopen( names[ i ], "wb" );
    T_assert_not_null( f );
    T_assert_eq_sz( fwrite( archive.buf, 1, archive.size, f ), archive.size );
    T_assert_eq_int( fclose( f ), 0 );
  }

  argv[ argc++ ] = "nopinion";
  argv[ argc++ ] = "-f";
  argv[ argc++ ] = "sarif";
  argv[ argc++ ] = "-t0009";

  if ( ctx->based ) {
    argv[ argc++ ] = "-b";
    argv[ argc++ ] = ctx->base_x;
    argv[ argc++ ] = "-b";
    argv[ argc++ ] = ctx->base_w;
    argv[ argc++ ] = "-b";
    argv[ argc++ ] = ctx->base_y;
  }

  for ( i = 0; i < 2 && ctx->files[ i ] != NULL; ++i ) {
    argv[ argc++ ] = (char *) ctx->files[ i ];
  }

  argv[ argc ] = NULL;
  ctx->out = TxMain( argc, argv, &ctx->status );
}

static void NopinionReqReportSarifArtifacts_Cleanup(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  T_eq_int( unlink( ctx->files[ 0 ] ), 0 );

  if ( ctx->files[ 1 ] != NULL && ctx->files[ 1 ] != ctx->files[ 0 ] ) {
    T_eq_int( unlink( ctx->files[ 1 ] ), 0 );
  }
}

/* clang-format off */

static const NopinionReqReportSarifArtifacts_Entry
NopinionReqReportSarifArtifacts_Entries[] = {
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_OneDistinct,
    NopinionReqReportSarifArtifacts_Post_Indices_OneDistinct },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_OneDuplicate,
    NopinionReqReportSarifArtifacts_Post_Indices_OneDuplicate },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_OneDistinct,
    NopinionReqReportSarifArtifacts_Post_Indices_TwiceDistinct },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_OneDuplicate,
    NopinionReqReportSarifArtifacts_Post_Indices_TwiceDuplicate },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_TwoDistinct,
    NopinionReqReportSarifArtifacts_Post_Indices_TwoDistinct },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_TwoDuplicate,
    NopinionReqReportSarifArtifacts_Post_Indices_TwoDuplicate },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_BasedDistinct,
    NopinionReqReportSarifArtifacts_Post_Indices_TwoDistinct },
  { 0, 0, 0, NopinionReqReportSarifArtifacts_Post_Artifacts_BasedDuplicate,
    NopinionReqReportSarifArtifacts_Post_Indices_TwoDuplicate }
};

static const uint8_t
NopinionReqReportSarifArtifacts_Map[] = {
  0, 1, 2, 3, 4, 5, 6, 7
};

/* clang-format on */

static size_t NopinionReqReportSarifArtifacts_Scope(
  void  *arg,
  char  *buf,
  size_t n
)
{
  NopinionReqReportSarifArtifacts_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope(
      NopinionReqReportSarifArtifacts_PreDesc,
      buf,
      n,
      ctx->Map.pcs
    );
  }

  return 0;
}

static T_fixture NopinionReqReportSarifArtifacts_Fixture = {
  .setup = NopinionReqReportSarifArtifacts_Setup_Wrap,
  .stop = NULL,
  .teardown = NopinionReqReportSarifArtifacts_Teardown_Wrap,
  .scope = NopinionReqReportSarifArtifacts_Scope,
  .initial_context = &NopinionReqReportSarifArtifacts_Instance
};

static inline NopinionReqReportSarifArtifacts_Entry
NopinionReqReportSarifArtifacts_PopEntry(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqReportSarifArtifacts_Entries
    [ NopinionReqReportSarifArtifacts_Map[ index ] ];
}

static void NopinionReqReportSarifArtifacts_TestVariant(
  NopinionReqReportSarifArtifacts_Context *ctx
)
{
  NopinionReqReportSarifArtifacts_Pre_Operands_Prepare(
    ctx,
    ctx->Map.pcs[ 0 ]
  );
  NopinionReqReportSarifArtifacts_Pre_Members_Prepare(
    ctx,
    ctx->Map.pcs[ 1 ]
  );
  NopinionReqReportSarifArtifacts_Action( ctx );
  NopinionReqReportSarifArtifacts_Post_Artifacts_Check(
    ctx,
    ctx->Map.entry.Post_Artifacts
  );
  NopinionReqReportSarifArtifacts_Post_Indices_Check(
    ctx,
    ctx->Map.entry.Post_Indices
  );
}

/**
 * @fn void T_case_body_NopinionReqReportSarifArtifacts( void )
 */
T_TEST_CASE_FIXTURE(
  NopinionReqReportSarifArtifacts,
  &NopinionReqReportSarifArtifacts_Fixture
)
{
  NopinionReqReportSarifArtifacts_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqReportSarifArtifacts_Pre_Operands_One;
    ctx->Map.pcs[ 0 ] < NopinionReqReportSarifArtifacts_Pre_Operands_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqReportSarifArtifacts_Pre_Members_Distinct;
      ctx->Map.pcs[ 1 ] < NopinionReqReportSarifArtifacts_Pre_Members_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      ctx->Map.entry = NopinionReqReportSarifArtifacts_PopEntry( ctx );
      NopinionReqReportSarifArtifacts_Prepare( ctx );
      NopinionReqReportSarifArtifacts_TestVariant( ctx );
      NopinionReqReportSarifArtifacts_Cleanup( ctx );
    }
  }
}

/** @} */
