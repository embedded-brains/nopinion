/* SPDX-License-Identifier: BSD-2-Clause */

/* Copyright (C) 2026 embedded brains GmbH & Co. KG */

#include "nopinion.h"

static uint32_t fp_regs( uint32_t reg, uint32_t size )
{
  switch ( size ) {
    case 1:
      return 1U << reg;
    case 2:
      return 3U << ( reg & ~1U );
    case 4:
      return 0xfU << ( reg & ~3U );
    default:
      return 0;
  }
}

/*
 * Returns the register sizes of an FPop1 or FPop2 instruction as a value
 * 0xSSTTDD with the size of rs1 in SS, of rs2 in TT and of rd in DD.
 */
static uint32_t fpop_sizes( uint32_t opf )
{
  switch ( opf ) {
    case 0x001: /* FMOVs */
    case 0x005: /* FNEGs */
    case 0x009: /* FABSs */
    case 0x029: /* FSQRTs */
    case 0x0c4: /* FiTOs */
    case 0x0d1: /* FsTOi */
      return 0x000101;
    case 0x02a: /* FSQRTd */
      return 0x000202;
    case 0x02b: /* FSQRTq */
      return 0x000404;
    case 0x041: /* FADDs */
    case 0x045: /* FSUBs */
    case 0x049: /* FMULs */
    case 0x04d: /* FDIVs */
      return 0x010101;
    case 0x042: /* FADDd */
    case 0x046: /* FSUBd */
    case 0x04a: /* FMULd */
    case 0x04e: /* FDIVd */
      return 0x020202;
    case 0x043: /* FADDq */
    case 0x047: /* FSUBq */
    case 0x04b: /* FMULq */
    case 0x04f: /* FDIVq */
      return 0x040404;
    case 0x069: /* FsMULd */
      return 0x010102;
    case 0x06e: /* FdMULq */
      return 0x020204;
    case 0x0c6: /* FdTOs */
    case 0x0d2: /* FdTOi */
      return 0x000201;
    case 0x0c7: /* FqTOs */
    case 0x0d3: /* FqTOi */
      return 0x000401;
    case 0x0c8: /* FiTOd */
    case 0x0c9: /* FsTOd */
      return 0x000102;
    case 0x0cb: /* FqTOd */
      return 0x000402;
    case 0x0cc: /* FiTOq */
    case 0x0cd: /* FsTOq */
      return 0x000104;
    case 0x0ce: /* FdTOq */
      return 0x000204;
    case 0x051: /* FCMPs */
    case 0x055: /* FCMPEs */
      return 0x010100;
    case 0x052: /* FCMPd */
    case 0x056: /* FCMPEd */
      return 0x020200;
    case 0x053: /* FCMPq */
    case 0x057: /* FCMPEq */
      return 0x040400;
    default:
      return 0xffffffff;
  }
}

static bool is_icc_set( uint32_t op3 )
{
  switch ( op3 ) {
    case 0x10: /* ADDcc */
    case 0x11: /* ANDcc */
    case 0x12: /* ORcc */
    case 0x13: /* XORcc */
    case 0x14: /* SUBcc */
    case 0x15: /* ANDNcc */
    case 0x16: /* ORNcc */
    case 0x17: /* XNORcc */
    case 0x18: /* ADDXcc */
    case 0x1a: /* UMULcc */
    case 0x1b: /* SMULcc */
    case 0x1c: /* SUBXcc */
    case 0x1e: /* UDIVcc */
    case 0x1f: /* SDIVcc */
    case 0x20: /* TADDcc */
    case 0x21: /* TSUBcc */
    case 0x22: /* TADDccTV */
    case 0x23: /* TSUBccTV */
    case 0x24: /* MULScc */
    case 0x31: /* WRPSR */
      return true;
    default:
      return false;
  }
}

static void decode_format_2( insn_info *info, uint32_t w )
{
  uint32_t op2 = ( w >> 22 ) & 0x7;
  uint32_t cond = ( w >> 25 ) & 0xf;

  if ( op2 != 2 && op2 != 6 && op2 != 7 ) {
    return;
  }

  info->flags |= F_BRANCH;

  if ( ( w & ( 1U << 29 ) ) != 0 ) {
    info->flags |= F_ANNUL;
  }

  if ( op2 == 2 && cond != 0x0 && cond != 0x8 ) {
    info->flags |= F_BRANCH_ICC;
  }

  if ( op2 == 6 ) {
    info->flags |= F_FBFCC;
  }
}

static void decode_format_3_alu( insn_info *info, uint32_t w )
{
  uint32_t op3 = ( w >> 19 ) & 0x3f;
  uint32_t rd = ( w >> 25 ) & 0x1f;
  uint32_t rs1 = ( w >> 14 ) & 0x1f;
  uint32_t rs2 = w & 0x1f;
  uint32_t opf = ( w >> 5 ) & 0x1ff;
  uint32_t sizes;

  if ( is_icc_set( op3 ) ) {
    info->flags |= F_ICC_SET;
    return;
  }

  switch ( op3 ) {
    case 0x34: /* FPop1 */
      info->flags |= F_FPOP1;
      sizes = fpop_sizes( opf );

      if ( sizes == 0xffffffff ) {
        info->fp_src = 0xffffffff;
        info->fp_dst = 0xffffffff;
      } else {
        info->fp_src = fp_regs( rs1, sizes >> 16 ) |
                       fp_regs( rs2, ( sizes >> 8 ) & 0xff );
        info->fp_dst = fp_regs( rd, sizes & 0xff );
      }

      if (
        ( opf >= 0x029 && opf <= 0x02b ) || ( opf >= 0x04d && opf <= 0x04f )
      ) {
        info->flags |= F_FDIV_FSQRT;
      }
      break;
    case 0x35: /* FPop2 */
      info->flags |= F_FPOP2;
      sizes = fpop_sizes( opf );

      if ( sizes == 0xffffffff ) {
        info->fp_src = 0xffffffff;
      } else {
        info->fp_src = fp_regs( rs1, sizes >> 16 ) |
                       fp_regs( rs2, ( sizes >> 8 ) & 0xff );
      }
      break;
    case 0x30: /* WRASR */
      if ( rd == 19 ) {
        info->flags |= F_POWER_DOWN;
      }
      break;
    case 0x38: /* JMPL */
      info->flags |= F_INDIRECT | F_JMPL;
      break;
    case 0x39: /* RETT */
      info->flags |= F_INDIRECT | F_RETT;
      break;
    case 0x3a: /* Ticc */
      if ( ( rd & 0xf ) == 0x8 ) {
        info->flags |= F_TICC | F_TRAP_ALWAYS;
      } else if ( ( rd & 0xf ) != 0x0 ) {
        info->flags |= F_TICC;
      }
      break;
    default:
      break;
  }
}

static void decode_format_3_mem( insn_info *info, uint32_t w )
{
  uint32_t op3 = ( w >> 19 ) & 0x3f;
  uint32_t rd = ( w >> 25 ) & 0x1f;
  bool     asi_1c = ( w & 0x3fe0 ) == ( 0x1cU << 5 );

  info->flags |= F_MEM;

  switch ( op3 ) {
    case 0x0d: /* LDSTUB */
    case 0x0f: /* SWAP */
      info->flags |= F_ATOMIC;
      break;
    case 0x1d: /* LDSTUBA */
    case 0x1f: /* SWAPA */
    case 0x3c: /* CASA */
      info->flags |= F_ATOMIC | ( asi_1c ? F_ATOMIC_ASI_1C : 0 );
      break;
    case 0x14: /* STA */
    case 0x15: /* STBA */
    case 0x16: /* STHA */
      info->flags |= F_STORE | ( asi_1c ? F_STORE_ASI_1C : 0 );
      break;
    case 0x25: /* STFSR */
      info->flags |= F_STORE | F_STFSR;
      break;
    case 0x04: /* ST */
    case 0x05: /* STB */
    case 0x06: /* STH */
    case 0x34: /* STC */
    case 0x35: /* STCSR */
      info->flags |= F_STORE;
      break;
    case 0x24: /* STF */
      info->flags |= F_STORE | F_FSTORE;
      info->fp_src = fp_regs( rd, 1 );
      break;
    case 0x17: /* STDA */
      info->flags |= F_STORE | F_STORE_DOUBLE |
                     ( asi_1c ? F_STORE_ASI_1C : 0 );
      break;
    case 0x07: /* STD */
    case 0x26: /* STDFQ */
    case 0x36: /* STDCQ */
    case 0x37: /* STDC */
      info->flags |= F_STORE | F_STORE_DOUBLE;
      break;
    case 0x27: /* STDF */
      info->flags |= F_STORE | F_STORE_DOUBLE | F_FSTORE;
      info->fp_src = fp_regs( rd, 2 );
      break;
    case 0x20: /* LDF */
      info->flags |= F_FLOAD;
      info->fp_dst = fp_regs( rd, 1 );
      break;
    case 0x23: /* LDDF */
      info->flags |= F_FLOAD;
      info->fp_dst = fp_regs( rd, 2 );
      break;
    default:
      break;
  }
}

void decode( section_context *ctx )
{
  long i;

  for ( i = 0; i < ctx->count; ++i ) {
    uint32_t   w = insn_word( ctx, i );
    insn_info *info = &ctx->info[ i ];
    long       target = UNKNOWN;

    info->flags &= F_RELOC | F_TARGET;
    info->fp_src = 0;
    info->fp_dst = 0;

    switch ( w >> 30 ) {
      case 0:
        decode_format_2( info, w );

        if ( ( info->flags & F_BRANCH ) != 0 ) {
          int32_t disp = (int32_t) ( w << 10 ) >> 10;
          target = i + disp;
        }
        break;
      case 1:
        info->flags |= F_CALL;
        target = i + ( (int32_t) ( w << 2 ) >> 2 );
        break;
      case 2:
        decode_format_3_alu( info, w );
        break;
      default:
        decode_format_3_mem( info, w );
        break;
    }

    if (
      ( info->flags & F_RELOC ) != 0 || target < 0 || target >= ctx->count
    ) {
      target = UNKNOWN;
    }

    ctx->target[ i ] = target;

    if ( target != UNKNOWN ) {
      ctx->info[ target ].flags |= F_TARGET;
    }
  }
}
