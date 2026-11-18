/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

/*
 * This file provides the link time wrappers which let a call of a function
 * of the C library fail.  The validation program links with --wrap for each
 * of these functions.
 */

#include "tx-support.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

void *__real_calloc( size_t nmemb, size_t size );

void *__wrap_calloc( size_t nmemb, size_t size );

void *__real_malloc( size_t size );

void *__wrap_malloc( size_t size );

int __real_fstat( int fd, struct stat *st );

int __wrap_fstat( int fd, struct stat *st );

void *__real_mmap(
  void  *addr,
  size_t length,
  int    prot,
  int    flags,
  int    fd,
  off_t  offset
);

void *__wrap_mmap(
  void  *addr,
  size_t length,
  int    prot,
  int    flags,
  int    fd,
  off_t  offset
);

static unsigned int fail_next;

static unsigned int skip_malloc;

void TxFailNext( unsigned int functions )
{
  fail_next = functions;
  skip_malloc = 0;
}

void TxFailMallocAfter( unsigned int skip )
{
  fail_next = TX_FAIL_MALLOC;
  skip_malloc = skip;
}

static bool Fail( unsigned int function )
{
  if ( ( fail_next & function ) == 0 ) {
    return false;
  }

  if ( function == TX_FAIL_MALLOC && skip_malloc > 0 ) {
    --skip_malloc;
    return false;
  }

  fail_next &= ~function;
  errno = ENOMEM;
  return true;
}

void *__wrap_calloc( size_t nmemb, size_t size )
{
  if ( Fail( TX_FAIL_CALLOC ) ) {
    return NULL;
  }

  return __real_calloc( nmemb, size );
}

void *__wrap_malloc( size_t size )
{
  if ( Fail( TX_FAIL_MALLOC ) ) {
    return NULL;
  }

  return __real_malloc( size );
}

int __wrap_fstat( int fd, struct stat *st )
{
  if ( Fail( TX_FAIL_FSTAT ) ) {
    return -1;
  }

  return __real_fstat( fd, st );
}

void *__wrap_mmap(
  void  *addr,
  size_t length,
  int    prot,
  int    flags,
  int    fd,
  off_t  offset
)
{
  if ( Fail( TX_FAIL_MMAP ) ) {
    return MAP_FAILED;
  }

  return __real_mmap( addr, length, prot, flags, fd, offset );
}
