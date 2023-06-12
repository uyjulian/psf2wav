/***************************************************************************
                            dma.c  -  description
                             -------------------
    begin                : Wed May 15 2002
    copyright            : (C) 2002 by Pete Bernert
    email                : BlackDove@addcom.de
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version. See also the license.txt file for *
 *   additional informations.                                              *
 *                                                                         *
 ***************************************************************************/

#include "stdafx.h"

#define _IN_DMA

#if 0
#include "externals.h"
#endif
#include "registers.h"

////////////////////////////////////////////////////////////////////////
// READ DMA (one value)
////////////////////////////////////////////////////////////////////////

#if 0
unsigned short CALLBACK SPUreadDMA(void)
{
 unsigned short s=spuMem[spuAddr>>1];
 spuAddr+=2;
 if(spuAddr>0x7ffff) spuAddr=0;

 iSpuAsyncWait=0;

 return s;
}
#endif

////////////////////////////////////////////////////////////////////////
// READ DMA (many values)
////////////////////////////////////////////////////////////////////////

#if 0
void CALLBACK SPUreadDMAMem(unsigned short * pusPSXMem,int iSize)
#endif
void CALLBACK SPUreadDMAMem(u32 usPSXMem,int iSize)
{
 int i;
 unsigned char crc=0;

 spuStat |= STAT_DATA_BUSY;

 for(i=0;i<iSize;i++)
  {
   Check_IRQ( spuAddr, 0 );

#if 0
   crc|=*pusPSXMem++=spuMem[spuAddr>>1]; // spu addr got by writeregister
#endif
   *(u16 *)PSXM(usPSXMem)=spuMem[spuAddr>>1];    // spu addr got by writeregister
   usPSXMem+=2;
   spuAddr+=2;                           // inc spu addr
#if 0
   spuMem[spuAddr>>1];
#endif

   // guess based on Vib Ribbon (below)
   if(spuAddr>0x7ffff) break;
  }

 iSpuAsyncWait=0;

#if 0
 /*
 /* Toshiden Subaru "story screen" hack.
 /*
 /* After character selection screen, the game checks values inside returned
 /* SPU buffer and all values cannot be 0x0.
 /* Due to XA timings(?) we return buffer that has only NULLs.
 /* Setting little lag to MixXA() causes buffer to have some non-NULL values,
 /* but causes garbage sound so this hack is preferable.
 /*
 /* Note: When messing with xa.c like fixing Suikoden II's demo video sound issue
 /* this should be handled as well.
 */
 if (crc == 0) *--pusPSXMem=0xFF;
#endif

 spuStat &= ~STAT_DATA_BUSY;
 spuStat &= ~STAT_DMA_NON;
 spuStat &= ~STAT_DMA_W;
 spuStat |= STAT_DMA_R;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// to investigate: do sound data updates by writedma affect spu
// irqs? Will an irq be triggered, if new data is written to
// the memory irq address?

////////////////////////////////////////////////////////////////////////
// WRITE DMA (one value)
////////////////////////////////////////////////////////////////////////
  
#if 0
void CALLBACK SPUwriteDMA(unsigned short val)
{
 spuMem[spuAddr>>1] = val;                             // spu addr got by writeregister

 spuAddr+=2;                                           // inc spu addr
 if(spuAddr>0x7ffff) spuAddr=0;                        // wrap

 iSpuAsyncWait=0;
}
#endif

////////////////////////////////////////////////////////////////////////
// WRITE DMA (many values)
////////////////////////////////////////////////////////////////////////

#if 0
void CALLBACK SPUwriteDMAMem(unsigned short * pusPSXMem,int iSize)
#endif
void CALLBACK SPUwriteDMAMem(u32 usPSXMem,int iSize)
{
 int i;

 spuStat |= STAT_DATA_BUSY;

 for(i=0;i<iSize;i++)
  {
	 Check_IRQ( spuAddr, 0 );

#if 0
	 spuMem[spuAddr>>1] = *pusPSXMem++;                  // spu addr got by writeregister
#endif
   spuMem[spuAddr>>1] = *(u16 *)PSXM(usPSXMem);
   usPSXMem+=2;                       // spu addr got by writeregister
   spuAddr+=2;                                         // inc spu addr

	 // Vib Ribbon - stop transfer (reverb playback)
   if(spuAddr>0x7ffff) break;
  }
 
 iSpuAsyncWait=0;


 spuStat &= ~STAT_DATA_BUSY;
 spuStat &= ~STAT_DMA_NON;
 spuStat &= ~STAT_DMA_R;
 spuStat |= STAT_DMA_W;
}

////////////////////////////////////////////////////////////////////////
