/******************************************************************************
*  Filename:       rf_patch_cpe_bt5.h
*  Revised:        $Date: 2018-05-07 15:02:01 +0200 (ma, 07 mai 2018) $
*  Revision:       $Revision: 18438 $
*
*  Description: RF core patch for Bluetooth 5 support in CC2640R2F
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
#ifndef _RF_PATCH_CPE_BT5_H
#define _RF_PATCH_CPE_BT5_H

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


CPE_PATCH_TYPE patchImageBt5[] = {
   0x21000515,
   0x210006cb,
   0x21000723,
   0x21000475,
   0x21000481,
   0x21000499,
   0x21000809,
   0x2100081d,
   0x461db570,
   0x47204c00,
   0x0000b287,
   0x0a004670,
   0x28c44a05,
   0x4710d004,
   0x32e44a03,
   0x90042001,
   0x20004902,
   0x47107008,
   0x0000679d,
   0x210001dc,
   0x88084903,
   0x46714a03,
   0xd0004290,
   0x47081c89,
   0x2100018a,
   0x00001404,
   0x4801b510,
   0x00004700,
   0x000009d5,
   0x01c0b570,
   0x47204c00,
   0x000046d5,
   0x4cb7b5f8,
   0x462548b7,
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
   0x4aa68801,
   0x29031889,
   0x48a5d806,
   0x8501217c,
   0x624149a4,
   0x47702001,
   0x470849a3,
   0xb430489d,
   0x31404601,
   0x2a027c0a,
   0x6802d116,
   0x754a79d2,
   0x68936802,
   0x32804602,
   0x7d486093,
   0xd00b2802,
   0xd0092800,
   0x2c061ec4,
   0x4995d809,
   0x18400080,
   0x6b803840,
   0x60901818,
   0xbc304894,
   0x20034700,
   0x80c802c0,
   0x72082002,
   0x2003bc30,
   0xb5704770,
   0x46044888,
   0x7da53440,
   0xd0122d01,
   0x06497d01,
   0x21800fca,
   0x7c21540a,
   0xd10a2900,
   0x78403060,
   0x07c00880,
   0x7ce0d002,
   0xd5020700,
   0x75a02001,
   0x2000e000,
   0x488273a0,
   0x75a54780,
   0xb570bd70,
   0x48804c78,
   0x35504625,
   0x28024780,
   0x3440d109,
   0x4a7d88e1,
   0xd1044291,
   0x06897ce9,
   0x1d91d401,
   0xbd7080e1,
   0x496fb570,
   0x4608890a,
   0xb2d23050,
   0xd1072a28,
   0x68d2680a,
   0x7a936142,
   0x02127ad2,
   0x8302189a,
   0x4a717803,
   0xd0102b00,
   0x2b017983,
   0x7c03d10d,
   0x07db095b,
   0x7d09d009,
   0x74c14d6c,
   0x20207f6c,
   0x77684320,
   0x776c4790,
   0x21ffbd70,
   0x479074c1,
   0xb510bd70,
   0x4c5a4866,
   0x28024780,
   0x4621d10e,
   0x88ca3140,
   0x429a4b5f,
   0x7ccad108,
   0x07d20952,
   0x7d22d004,
   0xd4010692,
   0x80ca1d9a,
   0xb570bd10,
   0x495c484f,
   0x7cc03040,
   0x07c00940,
   0x4d57d007,
   0x8b2c4859,
   0x83284320,
   0x832c4788,
   0x4788bd70,
   0xb570bd70,
   0x49554c46,
   0x36404626,
   0x00a87935,
   0x68c01840,
   0x2d0a4780,
   0xd0104621,
   0x780a3154,
   0x07db0993,
   0x73b2d004,
   0x2303780a,
   0x700a431a,
   0xb2ca8921,
   0xd3012a2b,
   0x81213928,
   0x3153bd70,
   0x4937e7ed,
   0x71083140,
   0xd022281e,
   0x2808dc08,
   0x280ad013,
   0x280bd013,
   0x2818d013,
   0xe012d108,
   0xd0122825,
   0xd012282a,
   0xd008283c,
   0xd012283d,
   0x0080493a,
   0x68c01840,
   0x48394770,
   0x48394770,
   0x48394770,
   0x48394770,
   0x48394770,
   0x48394770,
   0x48394770,
   0x48394770,
   0xb5f84770,
   0x4c204607,
   0x5d00204e,
   0x07ee0985,
   0x2e0025fb,
   0x7d26d017,
   0x0f240734,
   0xd0032c05,
   0x42202401,
   0xe012d002,
   0xe7fa2402,
   0xd00509c0,
   0xd5030670,
   0x0f806848,
   0xd0082801,
   0x005b085b,
   0x00520852,
   0x2800e003,
   0x402bd001,
   0x2b06402a,
   0x2010d003,
   0xd0102b02,
   0x2302e010,
   0x4638402a,
   0xfe72f7ff,
   0xda072800,
   0x1ab900c2,
   0x7e493920,
   0x42112214,
   0x2000d100,
   0x4302bdf8,
   0x46384303,
   0xfe62f7ff,
   0x0000bdf8,
   0x21000144,
   0x0000a767,
   0xffffe7d5,
   0x210000ec,
   0x00009657,
   0x00009663,
   0x0000d575,
   0x0000bcf3,
   0x0000cb37,
   0x00001404,
   0x0000c8eb,
   0x210000a8,
   0x0000b4f5,
   0x0000ad53,
   0x00002020,
   0x0000df80,
   0x210004c9,
   0x2100068b,
   0x21000667,
   0x2100063b,
   0x210005e9,
   0x210005c3,
   0x21000583,
   0x21000531,
   0x4c03b510,
   0xfe50f7ff,
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
   0xbd10fe35,
   0x40045080,
   0x40040000,
   0x40044000,
   0x21000280,
};
#define _NWORD_PATCHIMAGE_BT5 263

#define _NWORD_PATCHSYS_BT5 0



#ifndef _BT5_SYSRAM_START
#define _BT5_SYSRAM_START 0x20000000
#endif

#ifndef _BT5_CPERAM_START
#define _BT5_CPERAM_START 0x21000000
#endif

#define _BT5_SYS_PATCH_FIXED_ADDR 0x20000000

#define _BT5_PARSER_PATCH_TAB_OFFSET 0x0350
#define _BT5_PATCH_TAB_OFFSET 0x0358
#define _BT5_IRQPATCH_OFFSET 0x03E8
#define _BT5_PATCH_VEC_OFFSET 0x0448

PATCH_FUN_SPEC void enterBt5CpePatch(void)
{
#if (_NWORD_PATCHIMAGE_BT5 > 0)
   uint32_t *pPatchVec = (uint32_t *) (_BT5_CPERAM_START + _BT5_PATCH_VEC_OFFSET);

   memcpy(pPatchVec, patchImageBt5, sizeof(patchImageBt5));
#endif
}

PATCH_FUN_SPEC void enterBt5SysPatch(void)
{
}

PATCH_FUN_SPEC void configureBt5Patch(void)
{
   uint8_t *pParserPatchTab = (uint8_t *) (_BT5_CPERAM_START + _BT5_PARSER_PATCH_TAB_OFFSET);
   uint8_t *pPatchTab = (uint8_t *) (_BT5_CPERAM_START + _BT5_PATCH_TAB_OFFSET);


   pParserPatchTab[1] = 0;
   pPatchTab[1] = 1;
   pPatchTab[18] = 2;
   pPatchTab[105] = 3;
   pPatchTab[108] = 4;
   pPatchTab[22] = 5;
   pPatchTab[28] = 6;
   pPatchTab[64] = 7;
}

PATCH_FUN_SPEC void applyBt5Patch(void)
{
   enterBt5SysPatch();
   enterBt5CpePatch();
   configureBt5Patch();
}

PATCH_FUN_SPEC void refreshBt5Patch(void)
{
   enterBt5CpePatch();
   configureBt5Patch();
}

PATCH_FUN_SPEC void rf_patch_cpe_bt5(void)
{
   applyBt5Patch();
}


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  _RF_PATCH_CPE_BT5_H

