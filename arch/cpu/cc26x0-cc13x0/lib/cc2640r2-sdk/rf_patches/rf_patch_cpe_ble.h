/******************************************************************************
*  Filename:       rf_patch_cpe_ble.h
*  Revised:        $Date: 2018-05-07 15:02:01 +0200 (ma, 07 mai 2018) $
*  Revision:       $Revision: 18438 $
*
*  Description: RF core patch for Bluetooth 4.2 support in CC2640R2F
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
#ifndef _RF_PATCH_CPE_BLE_H
#define _RF_PATCH_CPE_BLE_H

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


CPE_PATCH_TYPE patchImageBle[] = {
   0x210004b9,
   0x210004e1,
   0x210004f5,
   0x4801b510,
   0x00004700,
   0x000009d5,
   0x01c0b570,
   0x47204c00,
   0x000046d5,
   0x4c18b5f8,
   0x46254818,
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
   0x31404905,
   0x28087108,
   0x4905d004,
   0x18400080,
   0x477068c0,
   0x47704803,
   0x21000144,
   0x0000a767,
   0x0000df80,
   0x2100046d,
   0x4c03b510,
   0xffb6f7ff,
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
   0xbd10ff9b,
   0x40045080,
   0x40040000,
   0x40044000,
   0x21000280,
};
#define _NWORD_PATCHIMAGE_BLE 61

#define _NWORD_PATCHSYS_BLE 0



#ifndef _BLE_SYSRAM_START
#define _BLE_SYSRAM_START 0x20000000
#endif

#ifndef _BLE_CPERAM_START
#define _BLE_CPERAM_START 0x21000000
#endif

#define _BLE_SYS_PATCH_FIXED_ADDR 0x20000000

#define _BLE_PARSER_PATCH_TAB_OFFSET 0x0350
#define _BLE_PATCH_TAB_OFFSET 0x0358
#define _BLE_IRQPATCH_OFFSET 0x03E8
#define _BLE_PATCH_VEC_OFFSET 0x0448

PATCH_FUN_SPEC void enterBleCpePatch(void)
{
#if (_NWORD_PATCHIMAGE_BLE > 0)
   uint32_t *pPatchVec = (uint32_t *) (_BLE_CPERAM_START + _BLE_PATCH_VEC_OFFSET);

   memcpy(pPatchVec, patchImageBle, sizeof(patchImageBle));
#endif
}

PATCH_FUN_SPEC void enterBleSysPatch(void)
{
}

PATCH_FUN_SPEC void configureBlePatch(void)
{
   uint8_t *pPatchTab = (uint8_t *) (_BLE_CPERAM_START + _BLE_PATCH_TAB_OFFSET);


   pPatchTab[1] = 0;
   pPatchTab[28] = 1;
   pPatchTab[64] = 2;
}

PATCH_FUN_SPEC void applyBlePatch(void)
{
   enterBleSysPatch();
   enterBleCpePatch();
   configureBlePatch();
}

PATCH_FUN_SPEC void refreshBlePatch(void)
{
   enterBleCpePatch();
   configureBlePatch();
}

PATCH_FUN_SPEC void rf_patch_cpe_ble(void)
{
   applyBlePatch();
}


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  _RF_PATCH_CPE_BLE_H

