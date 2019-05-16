/******************************************************************************
*  Filename:       rf_patch_mce_aoa_aod.h
*  Revised:        $Date: 2018-05-07 15:02:01 +0200 (ma, 07 mai 2018) $
*  Revision:       $Revision: 18438 $
*
*  Description: RF core patch for Bluetooth 4.2 support and proprietary angle of arrival/angle of departure measurements in CC2640R2F
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

#ifndef _RF_PATCH_MCE_AOA_AOD_H
#define _RF_PATCH_MCE_AOA_AOD_H

#include <stdint.h>
#include "../inc/hw_types.h"

#ifndef MCE_PATCH_TYPE
#define MCE_PATCH_TYPE static const uint32_t
#endif

#ifndef PATCH_FUN_SPEC
#define PATCH_FUN_SPEC static inline
#endif

#ifndef RFC_MCERAM_BASE
#define RFC_MCERAM_BASE 0x21008000
#endif

#ifndef MCE_PATCH_MODE
#define MCE_PATCH_MODE 0
#endif

MCE_PATCH_TYPE patchAodAoaMce[242] = { 
   0x2dce6027,
   0x5f972fcf,
   0x000002d0,
   0x00070003,
   0x0000001f,
   0x40000000,
   0x0000000c,
   0x00091487,
   0x000105f9,
   0x808b8000,
   0x00000650,
   0x05900a1d,
   0x00050000,
   0x7b200400,
   0x000000c1,
   0x7f27000f,
   0x0000017f,
   0x00000000,
   0x005f0000,
   0x72200000,
   0x720d720c,
   0x7248720e,
   0xa475a32d,
   0x72047203,
   0x73067305,
   0x72767376,
   0x9010c7c0,
   0x7100b0c0,
   0xb0f0a0c0,
   0x81327218,
   0x39521020,
   0x00200670,
   0x11011630,
   0x6c011401,
   0x6059604c,
   0x60f06080,
   0x604c6103,
   0x604d604c,
   0x60506050,
   0x60511220,
   0x730f1210,
   0x73117310,
   0x00108181,
   0xb0709180,
   0xc0616036,
   0xc470c282,
   0x6f131820,
   0x16116e23,
   0x685d1612,
   0xc810c482,
   0x406a1820,
   0x6e231203,
   0x68671612,
   0x9ab07840,
   0x9ae08300,
   0x9220d3f0,
   0x00006050,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x00000000,
   0x7276b005,
   0x91c0c100,
   0xb100b108,
   0xb0f1b0f3,
   0x7100b0d8,
   0xa0d8b108,
   0xb760b200,
   0x97808ab0,
   0x8140b0f1,
   0x2a703980,
   0x16111001,
   0x84448432,
   0xc0f5c0f3,
   0x1e018171,
   0xc50040a0,
   0x9241689e,
   0x7100b0c1,
   0xb002b012,
   0xa0c1b0f1,
   0x72297276,
   0xb013b480,
   0xb0d0b003,
   0xb1007100,
   0x92908140,
   0x94908160,
   0xb1007100,
   0x94929293,
   0xb1007100,
   0x94949295,
   0x9862e030,
   0x65de9874,
   0xb1007100,
   0xa480a0d0,
   0xb0c3b483,
   0xb0f37100,
   0xc030a0c3,
   0xc0209760,
   0xb0c19780,
   0xb0f17100,
   0x7276a0c1,
   0xa0037248,
   0x7248a002,
   0x73067305,
   0x72767376,
   0xc7c0a200,
   0x60509010,
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
   0x1e028172,
   0xb0054102,
   0xb0cfb0ff,
   0x7100658f,
   0xa0cfb0ff,
   0x1c128261,
   0xe0404103,
   0x98729861,
   0x60f365de,
   0xb205658f,
   0xb011b06c,
   0xb475b089,
   0xa0c0a0c1,
   0xb0edb11d,
   0x7100b0f9,
   0xa760a182,
   0xb7607378,
   0x22108990,
   0xb1824116,
   0x3160b074,
   0x100f3d80,
   0x7311720e,
   0x8090b201,
   0x44392200,
   0x1e038153,
   0x87ab411d,
   0x10568795,
   0x312318b5,
   0xc3711853,
   0x97831813,
   0xb0f1a760,
   0xb0f9b760,
   0xb0c1b0c9,
   0x453a22f3,
   0x80907100,
   0x2290a0c9,
   0xb0f14562,
   0xc093956f,
   0x90f79783,
   0x7100a205,
   0xb078b32d,
   0xc243a475,
   0x90f79783,
   0x80907100,
   0xa0c1b0f1,
   0x7276a32d,
   0x72047202,
   0x72037206,
   0x73057204,
   0x72207306,
   0x73057248,
   0x73767306,
   0xa5947276,
   0x9010c7c0,
   0xe0508302,
   0x9872986f,
   0x605065de,
   0x8ad4b0f9,
   0x31841042,
   0x18543964,
   0x39821814,
   0x18243122,
   0x18608790,
   0x598c1840,
   0xb0c19784,
   0xb0f17100,
   0x1020b077,
   0x1880c238,
   0xb0c19780,
   0x83017100,
   0x161010f0,
   0x18013d10,
   0x93011a11,
   0x97881a18,
   0x7100b0f1,
   0xb594b0f1,
   0x18231843,
   0x61319783,
   0x65dec060,
   0x84406131,
   0x87d097c0,
   0x8470100e,
   0x419c2240,
   0x97c08430,
   0x140e87d0,
   0x180ec080,
   0x180ec080,
   0x97c08460,
   0x100f87d0,
   0x22408470,
   0x845041ab,
   0x87d097c0,
   0xc080140f,
   0xc080180f,
   0x8321180f,
   0x39613131,
   0x31113981,
   0x11001631,
   0x6c001410,
   0x311e311f,
   0x311e311f,
   0x318e318f,
   0x00ef398e,
   0x8210957f,
   0x45c72230,
   0x7100b0c5,
   0xa0c5b0f5,
   0xc10061bf,
   0x781091b0,
   0x8ae09760,
   0x13e79300,
   0x26ca120a,
   0xb01226ea,
   0xb016b014,
   0xb004b002,
   0x7820b006,
   0x90309050,
   0x90607830,
   0x70009040,
   0x88409850,
   0x45df2200,
   0x7000b830
};

PATCH_FUN_SPEC void rf_patch_mce_aoa_aod(void)
{
#ifdef __PATCH_NO_UNROLLING
   uint32_t i;
   for (i = 0; i < 242; i++) {
      HWREG(RFC_MCERAM_BASE + 4 * i) = patchAodAoaMce[i];
   }
#else
   const uint32_t *pS = patchAodAoaMce;
   volatile unsigned long *pD = &HWREG(RFC_MCERAM_BASE);
   uint32_t t1, t2, t3, t4, t5, t6, t7, t8;
   uint32_t nIterations = 30;

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
   *pD++ = t1;
   *pD++ = t2;
#endif
}

#endif
