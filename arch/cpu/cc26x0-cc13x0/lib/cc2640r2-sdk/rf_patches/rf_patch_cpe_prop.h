/******************************************************************************
*  Filename:       rf_patch_cpe_prop.h
*  Revised:        $Date: 2018-04-23 13:50:59 +0200 (ma, 23 apr 2018) $
*  Revision:       $Revision: 18402 $
*
*  Description: RF core patch for proprietary radio support ("PROP" API command set) in CC2640R2F
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
#ifndef _RF_PATCH_CPE_PROP_H
#define _RF_PATCH_CPE_PROP_H

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


CPE_PATCH_TYPE patchImageProp[] = {
   0x21000491,
   0x21000459,
   0x210004b1,
   0x210004c5,
   0x1b094904,
   0x2988d003,
   0x3438d102,
   0x4c02e000,
   0x47084902,
   0x0000828c,
   0x2100050c,
   0x000061e7,
   0x4801b510,
   0x00004700,
   0x000009d5,
   0x01c0b570,
   0x47204c00,
   0x000046d5,
   0x4905b672,
   0x22206808,
   0x600a4302,
   0x69924a03,
   0xb6626008,
   0x4770b250,
   0x40040000,
   0x40046040,
   0x4c03b510,
   0xffe0f7ff,
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
   0xbd10ffc5,
   0x40045080,
   0x40040000,
   0x40044000,
   0x21000280,
   0x08c360c0,
   0x0013130c,
   0x107601ac,
   0xa05b48a9,
   0xe759d88e,
   0xe904e8f2,
   0xe904e904,
   0x0000e904,
};
#define _NWORD_PATCHIMAGE_PROP 57

#define _NWORD_PATCHSYS_PROP 0



#ifndef _PROP_SYSRAM_START
#define _PROP_SYSRAM_START 0x20000000
#endif

#ifndef _PROP_CPERAM_START
#define _PROP_CPERAM_START 0x21000000
#endif

#define _PROP_SYS_PATCH_FIXED_ADDR 0x20000000

#define _PROP_PARSER_PATCH_TAB_OFFSET 0x0350
#define _PROP_PATCH_TAB_OFFSET 0x0358
#define _PROP_IRQPATCH_OFFSET 0x03E8
#define _PROP_PATCH_VEC_OFFSET 0x0448

PATCH_FUN_SPEC void enterPropCpePatch(void)
{
#if (_NWORD_PATCHIMAGE_PROP > 0)
   uint32_t *pPatchVec = (uint32_t *) (_PROP_CPERAM_START + _PROP_PATCH_VEC_OFFSET);

   memcpy(pPatchVec, patchImageProp, sizeof(patchImageProp));
#endif
}

PATCH_FUN_SPEC void enterPropSysPatch(void)
{
}

PATCH_FUN_SPEC void configurePropPatch(void)
{
   uint8_t *pPatchTab = (uint8_t *) (_PROP_CPERAM_START + _PROP_PATCH_TAB_OFFSET);


   pPatchTab[83] = 0;
   pPatchTab[99] = 1;
   pPatchTab[28] = 2;
   pPatchTab[64] = 3;
}

PATCH_FUN_SPEC void applyPropPatch(void)
{
   enterPropSysPatch();
   enterPropCpePatch();
   configurePropPatch();
}

PATCH_FUN_SPEC void refreshPropPatch(void)
{
   enterPropCpePatch();
   configurePropPatch();
}

PATCH_FUN_SPEC void rf_patch_cpe_prop(void)
{
   applyPropPatch();
}


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  _RF_PATCH_CPE_PROP_H

