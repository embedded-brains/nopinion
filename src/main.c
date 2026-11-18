/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

int main( int argc, char **argv )
{
  return nopinion_main( argc, argv, stdout, stderr );
}
