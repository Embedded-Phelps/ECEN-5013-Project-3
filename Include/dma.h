/***************************************************************************
 *
 *	Filename: 		dma.h
 *  Description:  	memory manipulation functions prototype header file
 *  Author: 		ShuTing Guo  
 *  Date: 			Oct. 2016
 *
 *****************************************************************************/
 
#ifndef __DMA_H__
#define __DMA_H__

#include "includes.h"

uint8_t dma_Init_Mem2mem(uint8_t dma_ch, 
						 uint8_t * source_addr,
						 uint8_t * destination_addr,
						 uint32_t transfer_size);
						 
#endif

