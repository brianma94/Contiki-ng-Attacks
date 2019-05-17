/******************************************************************************
*  Filename:       rf_patch_rfe_tof.h
*  Revised:        $Date: 2018-05-14 22:40:22 +0200 (ma, 14 mai 2018) $
*  Revision:       $Revision: 18459 $
*
*  Description: RF core patch for supporting time-of-flight radio measurements in CC2640R2F
*
*  Copyright (c) 2015-2017, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/


#ifndef _RF_PATCH_RFE_TOF_H
#define _RF_PATCH_RFE_TOF_H

#include <stdint.h>
#include "../inc/hw_types.h"

#ifndef RFE_PATCH_TYPE
#define RFE_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC static inline
#endif

#ifndef RFC_RFERAM_BASE
#define RFC_RFERAM_BASE 0x2100C000
#endif

#ifndef RFE_PATCH_MODE
#define RFE_PATCH_MODE 0
#endif

RFE_PATCH_TYPE patchTofRfe[423] = { 
   0x00006168,
   0x004535aa,
   0x0421a355,
   0x1f40004c,
   0x0000003f,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x40004030,
   0x40034001,
   0x400f4007,
   0x40cf404f,
   0x43cf41cf,
   0x4fcf47cf,
   0x2fcf3fcf,
   0x0fcf1fcf,
   0x00000000,
   0x00000000,
   0x000f0000,
   0x00000008,
   0x0000003f,
   0x003f0040,
   0x00040000,
   0x000e0068,
   0x000600dc,
   0x001a0043,
   0x00000005,
   0x00020000,
   0x00000000,
   0x00000000,
   0x00c00004,
   0x00040000,
   0x000000c0,
   0x00000007,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x40004030,
   0x40034001,
   0x400f4007,
   0x40cf404f,
   0x6fcf7fcf,
   0x4fcf5fcf,
   0x2fcf3fcf,
   0x0fcf1fcf,
   0x00000000,
   0x00000000,
   0x9100c050,
   0xc0707000,
   0x70009100,
   0x00213182,
   0xb1109131,
   0x81017000,
   0xa100b101,
   0x91323182,
   0x9101b110,
   0x81411011,
   0x40772241,
   0x700006f1,
   0x9101c051,
   0x39101830,
   0xd0083183,
   0x6f413118,
   0x91310031,
   0x1483b110,
   0x68831614,
   0x10257000,
   0x9100c050,
   0xc140c3f4,
   0x6f031420,
   0x04411031,
   0x22f08250,
   0x26514098,
   0x3182c022,
   0x91310021,
   0x3963b110,
   0x04411031,
   0x3182c082,
   0x91310021,
   0x3963b110,
   0xc0a21031,
   0x00213182,
   0xb1109131,
   0x31151050,
   0x92051405,
   0x64677000,
   0x1031c052,
   0x31610631,
   0x646a02c1,
   0x1031c112,
   0x06713921,
   0x02e13151,
   0x7000646a,
   0x9101c051,
   0x3182c0e2,
   0x00028260,
   0xb1109132,
   0x64677000,
   0xc122c101,
   0xc101646a,
   0x646ac0c2,
   0x64b18253,
   0x64677000,
   0xc081c272,
   0xc122646a,
   0x646ac111,
   0xc111c002,
   0xc062646a,
   0x646ac331,
   0xc111c362,
   0xc302646a,
   0x646ac111,
   0x39538253,
   0xc3e264b1,
   0x2211646f,
   0xc24240e9,
   0x646ac881,
   0xc111c252,
   0xc272646a,
   0x646acee1,
   0xc881c202,
   0xc202646a,
   0x646ac801,
   0x68fdc0b0,
   0x64677000,
   0xc801c242,
   0xc252646a,
   0x646ac011,
   0xc0e1c272,
   0xc002646a,
   0x646ac101,
   0xc301c062,
   0xc122646a,
   0x646ac101,
   0xc101c362,
   0xc302646a,
   0x646ac101,
   0x64b18253,
   0x80817000,
   0x41291e11,
   0xb054b050,
   0x80407100,
   0x412a2240,
   0xb064a054,
   0x220180f1,
   0x7000451e,
   0x411e2200,
   0x611bb060,
   0xc1116467,
   0x646ac0c2,
   0x64677000,
   0xc0c2c101,
   0x7000646a,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x72057306,
   0x720e720b,
   0x7100b050,
   0xa050b060,
   0x80928081,
   0x45872241,
   0xc1f18080,
   0x16300410,
   0x14011101,
   0x619a6c01,
   0x619a619a,
   0x619a619a,
   0x61be619a,
   0x61be619a,
   0x619a619a,
   0x8091619a,
   0x0421c0f2,
   0x80823121,
   0x14122a42,
   0x11011632,
   0x6c011421,
   0x619a61a3,
   0x619a61a7,
   0x619a619a,
   0x619a619a,
   0x619c619c,
   0x619fb0b0,
   0x7306b0b1,
   0xb0307205,
   0xc284616c,
   0xc3c0c003,
   0x7820647c,
   0x78427831,
   0x78547873,
   0x78667885,
   0x92219210,
   0x92439232,
   0x92659254,
   0xc01f9156,
   0x394091ff,
   0x100106f0,
   0x14103110,
   0x619c9200,
   0x64d3b060,
   0xb0e164c0,
   0xb054b050,
   0x8212b064,
   0x39823182,
   0x648b3942,
   0x7100b0e1,
   0x22008040,
   0xb06445f0,
   0x225280f2,
   0x222245e2,
   0x223245d9,
   0x653345e0,
   0x653361cb,
   0xb06465f3,
   0x225080f0,
   0x61cb45e2,
   0x61cb652e,
   0xb064a054,
   0xb060a050,
   0xb062a052,
   0xb063a053,
   0x64c964ff,
   0x6747cff0,
   0x619c720e,
   0x6747cfe0,
   0xc80061e2,
   0x81599160,
   0x8091b050,
   0x46642241,
   0x31828212,
   0x39423982,
   0x8212648b,
   0x102f06f2,
   0x142f311f,
   0x22d68216,
   0xc1404609,
   0xc500620a,
   0x6f0d1420,
   0x10de396d,
   0x044ec3f4,
   0x3182c082,
   0x396d002e,
   0x3182c0a2,
   0x821a002d,
   0x06fa398a,
   0x31808220,
   0xc00b3980,
   0x10bc180b,
   0x820318ac,
   0x149b1439,
   0x06f08210,
   0x31101001,
   0x81511410,
   0x140c1410,
   0x469e22c6,
   0x39408230,
   0x100206f0,
   0x3001c011,
   0x1801c010,
   0x31821802,
   0x26c10021,
   0xb0039191,
   0xb063b013,
   0x8041b053,
   0x46952201,
   0x91c481b4,
   0x1cb581d5,
   0x18954e4d,
   0x80f09165,
   0x423f2240,
   0x913d6262,
   0x913eb110,
   0x80e0b110,
   0x46572200,
   0x425722e6,
   0x1895b0e0,
   0x920f9165,
   0x14f98159,
   0x225080f0,
   0x22404695,
   0x632a4662,
   0x6747cfd0,
   0xa052b063,
   0xc0f28230,
   0x10020420,
   0x3001c011,
   0x1801c010,
   0x31821802,
   0x26c10021,
   0x720e9191,
   0xb0139191,
   0xb063b003,
   0xb064b053,
   0x7100b054,
   0x22018041,
   0xb0634695,
   0x80f0b064,
   0x42952220,
   0x91c181b1,
   0x189181d1,
   0xb0319161,
   0x6702627b,
   0x8159a0e0,
   0x14598205,
   0x7100c080,
   0x6a91b063,
   0xb0e6623f,
   0xa053a052,
   0x81628201,
   0x3d823182,
   0x7000a003,
   0x39478237,
   0x82303987,
   0x06f03980,
   0xc0111002,
   0xc0103001,
   0x18021801,
   0x00213182,
   0x918126c1,
   0xb012b002,
   0x39408230,
   0x100206f0,
   0x3001c011,
   0x1801c010,
   0x31821802,
   0x26c10021,
   0xb0039191,
   0xb063b013,
   0x7100b053,
   0xb062a053,
   0x8041b052,
   0x46952201,
   0x91c481a4,
   0x81b481d5,
   0x4ed41cb5,
   0x91651895,
   0x224080f0,
   0x626242c5,
   0x91c481b4,
   0x104081d4,
   0x91601890,
   0x1c751845,
   0x80f04ee1,
   0x42c52240,
   0x913d6262,
   0x913eb110,
   0x80e0b110,
   0x46eb2200,
   0x42eb22e6,
   0x9165b0e0,
   0x8159920f,
   0x80f014f9,
   0x45f32250,
   0x46622240,
   0x67026309,
   0x8159a0e0,
   0x14598205,
   0x7100c140,
   0x6afbb062,
   0x80a262c5,
   0x619c648b,
   0x39428212,
   0x608b06f2,
   0x7100b050,
   0x8240619c,
   0x22018041,
   0x81a44695,
   0x81d591c4,
   0x91651895,
   0x224180f1,
   0x6b0a4662,
   0x31818161,
   0xdfc03d81,
   0x674792f1,
   0x22018041,
   0x81a44695,
   0x81d591c4,
   0x4af51cc5,
   0x91651895,
   0x224080f0,
   0x62624316,
   0x6747cfb0,
   0x80418240,
   0x46952201,
   0x91c481b4,
   0x189581d5,
   0x80f19165,
   0x46622241,
   0x80416b2d,
   0x46952201,
   0x91c481b4,
   0x1cc581d5,
   0x18954a8b,
   0x80f09165,
   0x43392240,
   0x92e06262,
   0x220082d0,
   0xb2c04748,
   0x00007000
};

PATCH_FUN_SPEC void rf_patch_rfe_tof(void)
{
#ifdef __PATCH_NO_UNROLLING
   uint32_t i;
   for (i = 0; i < 423; i++) {
      HWREG(RFC_RFERAM_BASE + 4 * i) = patchTofRfe[i];
   }
#else
   const uint32_t *pS = patchTofRfe;
   volatile unsigned long *pD = &HWREG(RFC_RFERAM_BASE);
   uint32_t t1, t2, t3, t4, t5, t6, t7, t8;
   uint32_t nIterations = 52;

   do {
      t1 = *pS++;
      t2 = *pS++;
      t3 = *pS++;
      t4 = *pS++;
      t5 = *pS++;
      t6 = *pS++;
      t7 = *pS++;
      t8 = *pS++;
      *pD++ = t1;
      *pD++ = t2;
      *pD++ = t3;
      *pD++ = t4;
      *pD++ = t5;
      *pD++ = t6;
      *pD++ = t7;
      *pD++ = t8;
   } while (--nIterations);

   t1 = *pS++;
   t2 = *pS++;
   t3 = *pS++;
   t4 = *pS++;
   t5 = *pS++;
   t6 = *pS++;
   t7 = *pS++;
   *pD++ = t1;
   *pD++ = t2;
   *pD++ = t3;
   *pD++ = t4;
   *pD++ = t5;
   *pD++ = t6;
   *pD++ = t7;
#endif
}

#endif
