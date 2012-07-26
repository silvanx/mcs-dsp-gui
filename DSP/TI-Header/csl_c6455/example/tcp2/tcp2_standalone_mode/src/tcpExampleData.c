/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004 , 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  tcpExampleData.c
 *
 *   @path  $(CSLPATH)\example\c6455\tcp2\tcp2_standalone_mode\src
 *
 *   @desc  Example file for the TCP2 CSL
 *
 */
#include <tistdtypes.h>

Uint32 sysParData [] = {
 0x14029f,
 0x4c0530,
 0x20037a,
 0x180434,
 0xc80bc1,
 0x200b42,
 0xd80fc7,
 0xc0cdf,
 0xbc0cd6,
 0xa407fd,
 0x440d2f,
 0xf40110,
 0x2803be,
 0xc0203,
 0xd80fc4,
 0xc00c65,
 0x500e4a,
 0x80b41,
 0xbc0e88,
 0x40c40,
 0xd40eb7,
 0xc52,
 0xdc0231,
 0xbc012d,
 0x28093c,
 0xd4008c,
 0x4001b8,
 0x540537,
 0x400cfc,
 0xd40ff6,
 0x4407a9,
 0x180f49,
 0x2005b4,
 0xec0b7e,
 0x200465,
 0x500a18,
 0x180f41,
 0x6c0d45,
 0xc4099a,
 0x400e71,
 0x000000
};

Uint32 interleaverTbl [] = {
    0x190027,
    0x90011,
    0x230001,
    0x15001b,
    0x5000b,
    0x1a0022,
    0xa0014,
    0x260004,
    0x16001e,
    0x6000e,
    0x1c0024,
    0xc0012,
    0x250002,
    0x13001d,
    0x3000d,
    0x180020,
    0x80010,
    0x210000,
    0x17001f,
    0x7000f,
    0x290028,
    0x2b002a
};

Int8	tailData []= {
                        0x2f, 0x31, 0x30,  0x20,
                        0x32, 0x27, 0x30, 0x0d,
                        0x10, 0x3f, 0x18, 0x3b 
                     };


/* hard decisions expected */
Uint32 hdRefBuff [] = {0x082336bc1, 0x0ea};

Uint32 frameLength = 40;
