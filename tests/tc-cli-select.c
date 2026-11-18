/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqCliSelect
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
 * @defgroup NopinionReqCliSelect spec:/nopinion/req/cli-select
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqCliSelect_Pre_Part_None,
  NopinionReqCliSelect_Pre_Part_Gr712rc,
  NopinionReqCliSelect_Pre_Part_Gr740,
  NopinionReqCliSelect_Pre_Part_Leon3ftRtax,
  NopinionReqCliSelect_Pre_Part_Ut699,
  NopinionReqCliSelect_Pre_Part_Ut699e,
  NopinionReqCliSelect_Pre_Part_Ut700,
  NopinionReqCliSelect_Pre_Part_Unknown,
  NopinionReqCliSelect_Pre_Part_NA
} NopinionReqCliSelect_Pre_Part;

typedef enum {
  NopinionReqCliSelect_Pre_Errata_None,
  NopinionReqCliSelect_Pre_Errata_Tn0009,
  NopinionReqCliSelect_Pre_Errata_Tn0011,
  NopinionReqCliSelect_Pre_Errata_Tn0012,
  NopinionReqCliSelect_Pre_Errata_Tn0013,
  NopinionReqCliSelect_Pre_Errata_Tn0016,
  NopinionReqCliSelect_Pre_Errata_Tn0018,
  NopinionReqCliSelect_Pre_Errata_Gr712rc8,
  NopinionReqCliSelect_Pre_Errata_Gr712rc19,
  NopinionReqCliSelect_Pre_Errata_Gr740201,
  NopinionReqCliSelect_Pre_Errata_NA
} NopinionReqCliSelect_Pre_Errata;

typedef enum {
  NopinionReqCliSelect_Pre_Check_Tn0009,
  NopinionReqCliSelect_Pre_Check_Tn0011,
  NopinionReqCliSelect_Pre_Check_Tn0012,
  NopinionReqCliSelect_Pre_Check_Tn0013,
  NopinionReqCliSelect_Pre_Check_Tn0016,
  NopinionReqCliSelect_Pre_Check_Tn0018,
  NopinionReqCliSelect_Pre_Check_Asi,
  NopinionReqCliSelect_Pre_Check_PowerDown,
  NopinionReqCliSelect_Pre_Check_NA
} NopinionReqCliSelect_Pre_Check;

typedef enum {
  NopinionReqCliSelect_Post_Status_Success,
  NopinionReqCliSelect_Post_Status_Finding,
  NopinionReqCliSelect_Post_Status_Error,
  NopinionReqCliSelect_Post_Status_NA
} NopinionReqCliSelect_Post_Status;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Part_NA : 1;
  uint8_t Pre_Errata_NA : 1;
  uint8_t Pre_Check_NA : 1;
  uint8_t Post_Status : 2;
} NopinionReqCliSelect_Entry;

/**
 * @brief Test context for spec:/nopinion/req/cli-select test case.
 */
typedef struct {
  /**
   * @brief This member contains the argument of the option -p.
   */
  const char *part;

  /**
   * @brief This member contains the argument of the option -t.
   */
  const char *errata;

  /**
   * @brief This member contains the index of the file operand.
   */
  size_t file;

  /**
   * @brief This member contains the temporary directory.
   */
  char dir[ 32 ];

  /**
   * @brief This member contains the paths of the files.
   */
  char files[ 8 ][ 64 ];

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
    size_t pcs[ 3 ];

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
    NopinionReqCliSelect_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqCliSelect_Context;

static NopinionReqCliSelect_Context NopinionReqCliSelect_Instance;

static const char *const NopinionReqCliSelect_PreDesc_Part[] = {
  "None",
  "Gr712rc",
  "Gr740",
  "Leon3ftRtax",
  "Ut699",
  "Ut699e",
  "Ut700",
  "Unknown",
  "NA"
};

static const char *const NopinionReqCliSelect_PreDesc_Errata[] = {
  "None",
  "Tn0009",
  "Tn0011",
  "Tn0012",
  "Tn0013",
  "Tn0016",
  "Tn0018",
  "Gr712rc8",
  "Gr712rc19",
  "Gr740201",
  "NA"
};

static const char *const NopinionReqCliSelect_PreDesc_Check[] = {
  "Tn0009",
  "Tn0011",
  "Tn0012",
  "Tn0013",
  "Tn0016",
  "Tn0018",
  "Asi",
  "PowerDown",
  "NA"
};

static const char *const *const NopinionReqCliSelect_PreDesc[] = {
  NopinionReqCliSelect_PreDesc_Part,
  NopinionReqCliSelect_PreDesc_Errata,
  NopinionReqCliSelect_PreDesc_Check,
  NULL
};

static void NopinionReqCliSelect_Pre_Part_Prepare(
  NopinionReqCliSelect_Context *ctx,
  NopinionReqCliSelect_Pre_Part state
)
{
  switch ( state ) {
    case NopinionReqCliSelect_Pre_Part_None: {
      /*
       * While the option -p is not given.
       */
      ctx->part = NULL;
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Gr712rc: {
      /*
       * While the option -p names the GR712RC.
       */
      ctx->part = "gr712rc";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Gr740: {
      /*
       * While the option -p names the GR740.
       */
      ctx->part = "gr740";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Leon3ftRtax: {
      /*
       * While the option -p names the LEON3FT-RTAX.
       */
      ctx->part = "leon3ft-rtax";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Ut699: {
      /*
       * While the option -p names the UT699.
       */
      ctx->part = "ut699";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Ut699e: {
      /*
       * While the option -p names the UT699E.
       */
      ctx->part = "ut699e";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Ut700: {
      /*
       * While the option -p names the UT700.
       */
      ctx->part = "ut700";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_Unknown: {
      /*
       * While the option -p names an unknown part.
       */
      ctx->part = "leon3";
      break;
    }

    case NopinionReqCliSelect_Pre_Part_NA:
      break;
  }
}

static void NopinionReqCliSelect_Pre_Errata_Prepare(
  NopinionReqCliSelect_Context   *ctx,
  NopinionReqCliSelect_Pre_Errata state
)
{
  switch ( state ) {
    case NopinionReqCliSelect_Pre_Errata_None: {
      /*
       * While the option -t is not given.
       */
      ctx->errata = NULL;
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Tn0009: {
      /*
       * While the option -t selects GRLIB-TN-0009.
       */
      ctx->errata = "0009";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Tn0011: {
      /*
       * While the option -t selects GRLIB-TN-0011.
       */
      ctx->errata = "0011";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Tn0012: {
      /*
       * While the option -t selects GRLIB-TN-0012.
       */
      ctx->errata = "0012";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Tn0013: {
      /*
       * While the option -t selects GRLIB-TN-0013.
       */
      ctx->errata = "0013";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Tn0016: {
      /*
       * While the option -t selects GRLIB-TN-0016.
       */
      ctx->errata = "0016";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Tn0018: {
      /*
       * While the option -t selects GRLIB-TN-0018.
       */
      ctx->errata = "0018";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Gr712rc8: {
      /*
       * While the option -t selects GR712RC erratum 8.
       */
      ctx->errata = "gr712rc-8";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Gr712rc19: {
      /*
       * While the option -t selects GR712RC erratum 19.
       */
      ctx->errata = "gr712rc-19";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_Gr740201: {
      /*
       * While the option -t selects GR740 erratum 20-1.
       */
      ctx->errata = "gr740-20-1";
      break;
    }

    case NopinionReqCliSelect_Pre_Errata_NA:
      break;
  }
}

static void NopinionReqCliSelect_Pre_Check_Prepare(
  NopinionReqCliSelect_Context  *ctx,
  NopinionReqCliSelect_Pre_Check state
)
{
  switch ( state ) {
    case NopinionReqCliSelect_Pre_Check_Tn0009: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GRLIB-TN-0009.
       */
      ctx->file = 0;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_Tn0011: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GRLIB-TN-0011.
       */
      ctx->file = 1;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_Tn0012: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GRLIB-TN-0012.
       */
      ctx->file = 2;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_Tn0013: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GRLIB-TN-0013.
       */
      ctx->file = 3;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_Tn0016: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GRLIB-TN-0016.
       */
      ctx->file = 4;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_Tn0018: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GRLIB-TN-0018.
       */
      ctx->file = 5;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_Asi: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GR712RC erratum 19 and GR740 erratum 20-1.
       */
      ctx->file = 6;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_PowerDown: {
      /*
       * While the file operand names an ELF file with one definite finding of
       * GR712RC erratum 8.
       */
      ctx->file = 7;
      break;
    }

    case NopinionReqCliSelect_Pre_Check_NA:
      break;
  }
}

static void NopinionReqCliSelect_Post_Status_Check(
  NopinionReqCliSelect_Context    *ctx,
  NopinionReqCliSelect_Post_Status state
)
{
  switch ( state ) {
    case NopinionReqCliSelect_Post_Status_Success: {
      /*
       * The exit status shall be 0.
       */
      T_eq_int( ctx->status, 0 );
      T_eq_str( ctx->out, "" );
      break;
    }

    case NopinionReqCliSelect_Post_Status_Finding: {
      /*
       * The exit status shall be 1.
       */
      T_eq_int( ctx->status, 1 );
      T_ne_str( ctx->out, "" );
      break;
    }

    case NopinionReqCliSelect_Post_Status_Error: {
      /*
       * The errata checker shall write the usage text to the standard error
       * and exit with the status 2.
       */
      T_eq_int( ctx->status, 2 );
      T_eq_int( strncmp( TxErrors(), "usage: nopinion ", 16 ), 0 );
      break;
    }

    case NopinionReqCliSelect_Post_Status_NA:
      break;
  }
}

static void NopinionReqCliSelect_Setup( NopinionReqCliSelect_Context *ctx )
{
  TxImage image;
  size_t  i;

  strcpy( ctx->dir, "tx-select-XXXXXX" );
  T_assert_not_null( mkdtemp( ctx->dir ) );

  for ( i = 0; i < T_ARRAY_SIZE( ctx->files ); ++i ) {
    (void) snprintf(
      ctx->files[ i ],
      sizeof( ctx->files[ i ] ),
      "%s/%zu.o",
      ctx->dir,
      i
    );
  }

  TxImageInit( &image );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxAdd() );
  TxAppend( &image, TxSt() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 0 ], &image );

  TxImageInit( &image );
  image.alignment = 16;
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxSwap() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 1 ], &image );

  TxImageInit( &image );
  TxAppend( &image, TxSubcc() );
  TxAppend( &image, TxBicc( 9, true, 2 ) );
  TxAppend( &image, TxFadds() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 2 ], &image );

  TxImageInit( &image );
  TxAppend( &image, TxFpop1( TX_FDIVS, 3, 1, 2 ) );
  TxAppend( &image, TxFpop1( TX_FADDS, 5, 6, 7 ) );
  TxAppend( &image, TxFpop1( TX_FADDS, 8, 6, 7 ) );
  TxAppend( &image, TxFpop1( TX_FDIVS, 9, 6, 7 ) );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 3 ], &image );

  TxImageInit( &image );
  TxAppend( &image, TxFadds() );
  TxAppend( &image, TxStfsr() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxNop() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 4 ], &image );

  TxImageInit( &image );
  TxAppend( &image, TxTicc( 8 ) );
  TxAppend( &image, TxJmpl() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 5 ], &image );

  TxImageInit( &image );
  TxAppend( &image, TxFormat3Asi( 3, 0x14, TX_G1, TX_O0, 0x1c, TX_G0 ) );
  TxAppend( &image, TxLd() );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 6 ], &image );

  TxImageInit( &image );
  TxAppend( &image, TxWrasr( 19 ) );
  TxAppend( &image, TxNop() );
  TxWriteElf( ctx->files[ 7 ], &image );
}

static void NopinionReqCliSelect_Setup_Wrap( void *arg )
{
  NopinionReqCliSelect_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqCliSelect_Setup( ctx );
}

static void NopinionReqCliSelect_Teardown( NopinionReqCliSelect_Context *ctx )
{
  size_t i;

  for ( i = 0; i < T_ARRAY_SIZE( ctx->files ); ++i ) {
    T_eq_int( unlink( ctx->files[ i ] ), 0 );
  }

  T_eq_int( rmdir( ctx->dir ), 0 );
}

static void NopinionReqCliSelect_Teardown_Wrap( void *arg )
{
  NopinionReqCliSelect_Context *ctx;

  ctx = arg;
  ctx->Map.in_action_loop = false;
  NopinionReqCliSelect_Teardown( ctx );
}

static void NopinionReqCliSelect_Action( NopinionReqCliSelect_Context *ctx )
{
  char *argv[ 7 ];
  int   argc = 0;

  argv[ argc++ ] = "nopinion";

  if ( ctx->part != NULL ) {
    argv[ argc++ ] = "-p";
    argv[ argc++ ] = (char *) ctx->part;
  }

  if ( ctx->errata != NULL ) {
    argv[ argc++ ] = "-t";
    argv[ argc++ ] = (char *) ctx->errata;
  }

  argv[ argc++ ] = ctx->files[ ctx->file ];
  argv[ argc ] = NULL;
  ctx->out = TxMain( argc, argv, &ctx->status );
}

/* clang-format off */

static const NopinionReqCliSelect_Entry
NopinionReqCliSelect_Entries[] = {
  { 0, 0, 0, 0, NopinionReqCliSelect_Post_Status_Success },
  { 0, 0, 0, 0, NopinionReqCliSelect_Post_Status_Error },
  { 0, 0, 0, 0, NopinionReqCliSelect_Post_Status_Finding }
};

static const uint8_t
NopinionReqCliSelect_Map[] = {
  2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
  2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
  0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
  2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
  0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
  0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
  0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
  0, 0, 0, 0, 2, 0, 2, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
  2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
  0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
  0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0,
  0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0,
  0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

/* clang-format on */

static size_t NopinionReqCliSelect_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqCliSelect_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqCliSelect_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqCliSelect_Fixture = {
  .setup = NopinionReqCliSelect_Setup_Wrap,
  .stop = NULL,
  .teardown = NopinionReqCliSelect_Teardown_Wrap,
  .scope = NopinionReqCliSelect_Scope,
  .initial_context = &NopinionReqCliSelect_Instance
};

static inline NopinionReqCliSelect_Entry NopinionReqCliSelect_PopEntry(
  NopinionReqCliSelect_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqCliSelect_Entries[ NopinionReqCliSelect_Map[ index ] ];
}

static void NopinionReqCliSelect_TestVariant(
  NopinionReqCliSelect_Context *ctx
)
{
  NopinionReqCliSelect_Pre_Part_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqCliSelect_Pre_Errata_Prepare( ctx, ctx->Map.pcs[ 1 ] );
  NopinionReqCliSelect_Pre_Check_Prepare( ctx, ctx->Map.pcs[ 2 ] );
  NopinionReqCliSelect_Action( ctx );
  NopinionReqCliSelect_Post_Status_Check( ctx, ctx->Map.entry.Post_Status );
}

/**
 * @fn void T_case_body_NopinionReqCliSelect( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqCliSelect, &NopinionReqCliSelect_Fixture )
{
  NopinionReqCliSelect_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqCliSelect_Pre_Part_None;
    ctx->Map.pcs[ 0 ] < NopinionReqCliSelect_Pre_Part_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    for (
      ctx->Map.pcs[ 1 ] = NopinionReqCliSelect_Pre_Errata_None;
      ctx->Map.pcs[ 1 ] < NopinionReqCliSelect_Pre_Errata_NA;
      ++ctx->Map.pcs[ 1 ]
    ) {
      for (
        ctx->Map.pcs[ 2 ] = NopinionReqCliSelect_Pre_Check_Tn0009;
        ctx->Map.pcs[ 2 ] < NopinionReqCliSelect_Pre_Check_NA;
        ++ctx->Map.pcs[ 2 ]
      ) {
        ctx->Map.entry = NopinionReqCliSelect_PopEntry( ctx );
        NopinionReqCliSelect_TestVariant( ctx );
      }
    }
  }
}

/** @} */
