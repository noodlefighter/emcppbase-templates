//***************************************************************
//------------<02.Dec.2010 by Peter Reiser>----------------------
//***************************************************************

#ifndef _SPI_H_
#define _SPI_H_

//================================================================

#include <stdint.h>
#include "embase_macros_bits.h"

//===============================================================

void SpiDirectCommand(uint8_t *pbuf);
void SpiDirectMode(void);
void SpiRawWrite(uint8_t *pbuf, uint8_t length);
void SpiReadCont(uint8_t *pbuf, uint8_t length);
void SpiReadSingle(uint8_t *pbuf, uint8_t length);
void SpiSetup(void);
void SpiUsciExtClkSet(void);
void SpiWriteCont(uint8_t *pbuf, uint8_t length);
void SpiWriteSingle(uint8_t *pbuf, uint8_t length);

//===============================================================

#endif
