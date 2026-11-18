/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

/*
 * This header file provides the runner of a validation test suite.  The
 * source file of the test suite defines NOPINION_TEST_NAME and includes this
 * header file.
 */

#ifndef TS_DEFAULT_H
#define TS_DEFAULT_H

#include <stdio.h>
#include <stdlib.h>

#include <rtems/bspIo.h>
#include <rtems/test-info.h>
#include <rtems/test.h>

const char rtems_test_name[] = NOPINION_TEST_NAME;

static char buffer[ 512 ];

static void OutputChar( char c )
{
  (void) putchar( c );
}

BSP_output_char_function_type BSP_output_char = OutputChar;

void rtems_putc( char c )
{
  ( *BSP_output_char )( c );
}

void rtems_put_char( int c, void *arg )
{
  (void) arg;
  rtems_putc( (char) c );
}

static const T_action actions[] = { T_report_hash_sha256 };

static const T_config config = {
  .name = rtems_test_name,
  .buf = buffer,
  .buf_size = sizeof( buffer ),
  .putchar = rtems_put_char,
  .verbosity = T_NORMAL,
  .now = T_now_clock,
  .allocate = malloc,
  .deallocate = free,
  .action_count = T_ARRAY_SIZE( actions ),
  .actions = actions
};

int main( void )
{
  int exit_code;

  (void) setvbuf( stdout, NULL, _IOLBF, 0 );
  rtems_test_begin( rtems_test_name, RTEMS_TEST_STATE_PASS );
  T_register();
  exit_code = T_main( &config );

  if ( exit_code == 0 ) {
    rtems_test_end( rtems_test_name );
  }

  return exit_code;
}

#endif /* TS_DEFAULT_H */
