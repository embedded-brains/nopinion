/* SPDX-License-Identifier: BSD-2-Clause */

/**
 * @file
 *
 * @ingroup NopinionReqProgram
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
#include <sys/wait.h>

#include <rtems/test.h>

/**
 * @defgroup NopinionReqProgram spec:/nopinion/req/program
 *
 * @ingroup NopinionTestsuitesValidation
 *
 * @{
 */

typedef enum {
  NopinionReqProgram_Pre_Option_Help,
  NopinionReqProgram_Pre_Option_Unknown,
  NopinionReqProgram_Pre_Option_NA
} NopinionReqProgram_Pre_Option;

typedef enum {
  NopinionReqProgram_Post_Status_Success,
  NopinionReqProgram_Post_Status_Error,
  NopinionReqProgram_Post_Status_NA
} NopinionReqProgram_Post_Status;

typedef enum {
  NopinionReqProgram_Post_Output_Usage,
  NopinionReqProgram_Post_Output_Empty,
  NopinionReqProgram_Post_Output_NA
} NopinionReqProgram_Post_Output;

typedef struct {
  uint8_t Skip : 1;
  uint8_t Pre_Option_NA : 1;
  uint8_t Post_Status : 2;
  uint8_t Post_Output : 2;
} NopinionReqProgram_Entry;

/**
 * @brief Test context for spec:/nopinion/req/program test case.
 */
typedef struct {
  /**
   * @brief This member contains the option.
   */
  const char *option;

  /**
   * @brief This member contains the standard output of the program.
   */
  char out[ 2048 ];

  /**
   * @brief This member contains the exit status of the program.
   */
  int status;

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
    NopinionReqProgram_Entry entry;

    /**
     * @brief If this member is true, then the current transition variant
     *   should be skipped.
     */
    bool skip;
  } Map;
} NopinionReqProgram_Context;

static NopinionReqProgram_Context NopinionReqProgram_Instance;

static const char *const NopinionReqProgram_PreDesc_Option[] =
  { "Help", "Unknown", "NA" };

static const char *const *const NopinionReqProgram_PreDesc[] = {
  NopinionReqProgram_PreDesc_Option,
  NULL
};

static void NopinionReqProgram_Pre_Option_Prepare(
  NopinionReqProgram_Context   *ctx,
  NopinionReqProgram_Pre_Option state
)
{
  switch ( state ) {
    case NopinionReqProgram_Pre_Option_Help: {
      /*
       * While the option -h is given.
       */
      ctx->option = "-h";
      break;
    }

    case NopinionReqProgram_Pre_Option_Unknown: {
      /*
       * While an unknown option is given.
       */
      ctx->option = "-x";
      break;
    }

    case NopinionReqProgram_Pre_Option_NA:
      break;
  }
}

static void NopinionReqProgram_Post_Status_Check(
  NopinionReqProgram_Context    *ctx,
  NopinionReqProgram_Post_Status state
)
{
  switch ( state ) {
    case NopinionReqProgram_Post_Status_Success: {
      /*
       * The exit status of the program shall be 0.
       */
      T_eq_int( ctx->status, 0 );
      break;
    }

    case NopinionReqProgram_Post_Status_Error: {
      /*
       * The exit status of the program shall be 2.
       */
      T_eq_int( ctx->status, 2 );
      break;
    }

    case NopinionReqProgram_Post_Status_NA:
      break;
  }
}

static void NopinionReqProgram_Post_Output_Check(
  NopinionReqProgram_Context    *ctx,
  NopinionReqProgram_Post_Output state
)
{
  switch ( state ) {
    case NopinionReqProgram_Post_Output_Usage: {
      /*
       * The program shall write the usage text to its standard output.
       */
      T_eq_int( strncmp( ctx->out, "usage: nopinion ", 16 ), 0 );
      break;
    }

    case NopinionReqProgram_Post_Output_Empty: {
      /*
       * The program shall write nothing to its standard output.
       */
      T_eq_str( ctx->out, "" );
      break;
    }

    case NopinionReqProgram_Post_Output_NA:
      break;
  }
}

static void NopinionReqProgram_Action( NopinionReqProgram_Context *ctx )
{
  const char *program = getenv( "NOPINION" );
  char        command[ 512 ];
  FILE       *f;
  size_t      n;
  int         status;

  T_assert_not_null( program );
  (void) snprintf(
    command,
    sizeof( command ),
    "%s %s 2>/dev/null",
    program,
    ctx->option
  );
  f = popen( command, "r" );
  T_assert_not_null( f );
  n = fread( ctx->out, 1, sizeof( ctx->out ) - 1, f );
  ctx->out[ n ] = '\0';
  status = pclose( f );
  T_assert_true( WIFEXITED( status ) );
  ctx->status = WEXITSTATUS( status );
}

/* clang-format off */

static const NopinionReqProgram_Entry
NopinionReqProgram_Entries[] = {
  { 0, 0, NopinionReqProgram_Post_Status_Success,
    NopinionReqProgram_Post_Output_Usage },
  { 0, 0, NopinionReqProgram_Post_Status_Error,
    NopinionReqProgram_Post_Output_Empty }
};

static const uint8_t
NopinionReqProgram_Map[] = {
  0, 1
};

/* clang-format on */

static size_t NopinionReqProgram_Scope( void *arg, char *buf, size_t n )
{
  NopinionReqProgram_Context *ctx;

  ctx = arg;

  if ( ctx->Map.in_action_loop ) {
    return T_get_scope( NopinionReqProgram_PreDesc, buf, n, ctx->Map.pcs );
  }

  return 0;
}

static T_fixture NopinionReqProgram_Fixture = {
  .setup = NULL,
  .stop = NULL,
  .teardown = NULL,
  .scope = NopinionReqProgram_Scope,
  .initial_context = &NopinionReqProgram_Instance
};

static inline NopinionReqProgram_Entry NopinionReqProgram_PopEntry(
  NopinionReqProgram_Context *ctx
)
{
  size_t index;

  index = ctx->Map.index;
  ctx->Map.index = index + 1;
  return NopinionReqProgram_Entries[ NopinionReqProgram_Map[ index ] ];
}

static void NopinionReqProgram_TestVariant( NopinionReqProgram_Context *ctx )
{
  NopinionReqProgram_Pre_Option_Prepare( ctx, ctx->Map.pcs[ 0 ] );
  NopinionReqProgram_Action( ctx );
  NopinionReqProgram_Post_Status_Check( ctx, ctx->Map.entry.Post_Status );
  NopinionReqProgram_Post_Output_Check( ctx, ctx->Map.entry.Post_Output );
}

/**
 * @fn void T_case_body_NopinionReqProgram( void )
 */
T_TEST_CASE_FIXTURE( NopinionReqProgram, &NopinionReqProgram_Fixture )
{
  NopinionReqProgram_Context *ctx;

  ctx = T_fixture_context();
  ctx->Map.in_action_loop = true;
  ctx->Map.index = 0;

  for (
    ctx->Map.pcs[ 0 ] = NopinionReqProgram_Pre_Option_Help;
    ctx->Map.pcs[ 0 ] < NopinionReqProgram_Pre_Option_NA;
    ++ctx->Map.pcs[ 0 ]
  ) {
    ctx->Map.entry = NopinionReqProgram_PopEntry( ctx );
    NopinionReqProgram_TestVariant( ctx );
  }
}

/** @} */
