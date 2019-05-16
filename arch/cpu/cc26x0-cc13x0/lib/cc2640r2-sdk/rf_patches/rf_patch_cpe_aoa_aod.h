/******************************************************************************
*  Filename:       rf_patch_cpe_aoa_aod.h
*  Revised:        $Date: 2018-05-07 15:02:01 +0200 (ma, 07 mai 2018) $
*  Revision:       $Revision: 18438 $
*
*  Description: RF core patch for Bluetooth 4.2 support and proprietary angle of arrival/angle of departure measurements in CC2640R2F
*
*  Copyright (c) 2015-2018, Texas Instruments Incorporated
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
#ifndef _RF_PATCH_CPE_AOA_AOD_H
#define _RF_PATCH_CPE_AOA_AOD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#ifndef CPE_PATCH_TYPE
#define CPE_PATCH_TYPE static const uint32_t
#endif

#ifndef SYS_PATCH_TYPE
#define SYS_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC static inline
#endif

#ifndef _APPLY_PATCH_TAB
#define _APPLY_PATCH_TAB
#endif


CPE_PATCH_TYPE patchImageAoaAod[] = {
   0x210005f7,
   0x2100068d,
   0x210006d9,
   0x210006ed,
   0x4801b510,
   0x00004700,
   0x000009d5,
   0x01c0b570,
   0x47204c00,
   0x000046d5,
   0x4865b510,
   0x28004780,
   0x4964d107,
   0x5c522278,
   0xd0022a00,
   0x5c522252,
   0xbd10624a,
   0x4605b5f8,
   0x9000485e,
   0x460e6a84,
   0x2100485d,
   0x21076341,
   0xe0186301,
   0x6b88495a,
   0xd5100782,
   0x4f596a88,
   0x68ba2108,
   0x69394790,
   0x47882008,
   0x7030b2c0,
   0x2c001c76,
   0x7020d001,
   0x1e6d1c64,
   0x0680e003,
   0x2001d501,
   0x2d00bdf8,
   0x9800dce4,
   0x20006284,
   0xb5febdf8,
   0x494c4c49,
   0x46252000,
   0x35407248,
   0x6a667c28,
   0xd16d2800,
   0x90024848,
   0x6bc04948,
   0x28004788,
   0x4627d166,
   0x7b783720,
   0xd1612800,
   0x73782001,
   0xdb5d2e10,
   0x28017da8,
   0x7ce8d15a,
   0xd4570780,
   0x20014669,
   0xffb0f7ff,
   0xd10a2800,
   0x78004668,
   0x280f1e76,
   0x4669d34b,
   0xf7ff2004,
   0x2800ffa5,
   0x2001d001,
   0x4668bdfe,
   0x1f367800,
   0xd13e28ff,
   0x46862000,
   0x78814668,
   0x020b7840,
   0x98024303,
   0x20006bc1,
   0x4694884a,
   0x0042e005,
   0x88921852,
   0xd005429a,
   0x45841c40,
   0x4670dcf7,
   0xd0262800,
   0x88094668,
   0xb2ca78c0,
   0xd0024282,
   0x42810a09,
   0x4923d11d,
   0x2320680a,
   0x600a431a,
   0x780a4921,
   0x00d27849,
   0x430a0209,
   0x634a491f,
   0x21024a17,
   0x4a1863d1,
   0x20007250,
   0x481c7378,
   0x02c06840,
   0x2003d505,
   0x80e802c0,
   0x20037229,
   0x6266bdfe,
   0x64204817,
   0xbdfe4780,
   0x480eb510,
   0x7a404c11,
   0xd0012800,
   0x70a02001,
   0x47804812,
   0x70a12100,
   0x480cbd10,
   0x28007880,
   0x2000d001,
   0x480e4770,
   0x00004700,
   0x0000ae55,
   0x21000144,
   0x40045040,
   0x21000300,
   0x210000e0,
   0x210000a8,
   0x00003d57,
   0x40048000,
   0x21000734,
   0x40045280,
   0x40091040,
   0x0000c251,
   0x0000c459,
   0x00005a9b,
   0x4c1eb5f8,
   0x4625481e,
   0x7b2f3560,
   0x732e2600,
   0x732f4780,
   0x43017b69,
   0x2f00d117,
   0x7e61d015,
   0xd00e2900,
   0x31204621,
   0x08537c0a,
   0xd10007db,
   0x6a237626,
   0x2b007b49,
   0x2304d101,
   0x42114319,
   0x7d21d002,
   0xd40006c9,
   0xbdf875e6,
   0x3140490b,
   0x28087108,
   0x280ed00a,
   0x2822d00a,
   0x2823d00a,
   0x4908d00a,
   0x18400080,
   0x477068c0,
   0x47704806,
   0x47704806,
   0x47704806,
   0x47704806,
   0x21000144,
   0x0000a767,
   0x0000df80,
   0x21000641,
   0x21000471,
   0x210004e3,
   0x210005dd,
   0x4c03b510,
   0xfebcf7ff,
   0x28006820,
   0xbd10d1fa,
   0x40041100,
   0x480db510,
   0x6b406b84,
   0x04e00141,
   0x43010ec0,
   0x4b0ab672,
   0xb2826818,
   0x43101558,
   0x48086018,
   0x601a6880,
   0x4a07b662,
   0x22907953,
   0x07224353,
   0xf7ff0f12,
   0xbd10fea1,
   0x40045080,
   0x40040000,
   0x40044000,
   0x21000280,
   0x00002015,
};
#define _NWORD_PATCHIMAGE_AOA_AOD 188

#define _NWORD_PATCHSYS_AOA_AOD 0



#ifndef _AOA_AOD_SYSRAM_START
#define _AOA_AOD_SYSRAM_START 0x20000000
#endif

#ifndef _AOA_AOD_CPERAM_START
#define _AOA_AOD_CPERAM_START 0x21000000
#endif

#define _AOA_AOD_SYS_PATCH_FIXED_ADDR 0x20000000

#define _AOA_AOD_PARSER_PATCH_TAB_OFFSET 0x0350
#define _AOA_AOD_PATCH_TAB_OFFSET 0x0358
#define _AOA_AOD_IRQPATCH_OFFSET 0x03E8
#define _AOA_AOD_PATCH_VEC_OFFSET 0x0448

PATCH_FUN_SPEC void enterAoaAodCpePatch(void)
{
#if (_NWORD_PATCHIMAGE_AOA_AOD > 0)
   uint32_t *pPatchVec = (uint32_t *) (_AOA_AOD_CPERAM_START + _AOA_AOD_PATCH_VEC_OFFSET);

   memcpy(pPatchVec, patchImageAoaAod, sizeof(patchImageAoaAod));
#endif
}

PATCH_FUN_SPEC void enterAoaAodSysPatch(void)
{
}

PATCH_FUN_SPEC void configureAoaAodPatch(void)
{
   uint8_t *pPatchTab = (uint8_t *) (_AOA_AOD_CPERAM_START + _AOA_AOD_PATCH_TAB_OFFSET);


   pPatchTab[81] = 0;
   pPatchTab[1] = 1;
   pPatchTab[28] = 2;
   pPatchTab[64] = 3;
}

PATCH_FUN_SPEC void applyAoaAodPatch(void)
{
   enterAoaAodSysPatch();
   enterAoaAodCpePatch();
   configureAoaAodPatch();
}

PATCH_FUN_SPEC void refreshAoaAodPatch(void)
{
   enterAoaAodCpePatch();
   configureAoaAodPatch();
}

PATCH_FUN_SPEC void rf_patch_cpe_aoa_aod(void)
{
   applyAoaAodPatch();
}


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  _RF_PATCH_CPE_AOA_AOD_H

