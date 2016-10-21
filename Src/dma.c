#include "includes.h"

uint8_t dma_Init_Mem2mem(uint8_t dma_ch, 
						 uint8_t * source_addr,
						 uint8_t * destination_addr,
						 uint32_t transfer_size)
{
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;										// Enable DMA clock gate
	DMA_SAR_REG(DMA_BASE_PTR, dma_ch) = (uint32_t) source_addr; 				// Load SAR with source(read) address
	DMA_DAR_REG(DMA_BASE_PTR, dma_ch) = (uint32_t) destination_addr;			// Load DAR with destination(write) address
	DMA_DSR_BCR_REG(DMA_BASE_PTR, dma_ch) |= DMA_DSR_BCR_DONE_MASK;			// Clear DONE bit
	DMA_DSR_BCR_REG(DMA_BASE_PTR, dma_ch) = DMA_DSR_BCR_BCR(transfer_size);	// Setting number of bytes to transfer
	DMA_DCR_REG(DMA_BASE_PTR, dma_ch) = DMA_DCR_SINC_MASK |					// Enable source increment
										DMA_DCR_SSIZE(1)  |					// Setting source size (0:32bit/1:8bit/2:16bit)
										DMA_DCR_DINC_MASK |					// Enable destination increment	
										DMA_DCR_DSIZE(1)  ;					// setting destination size (0:32bit/1:8bit/2:16bit)
#if DMA_ISR_ENABLE
	DMA_DCR_REG(DMA_BASE_PTR, dma_ch) |= DMA_DCR_EINT_MASK;					// Enable DMA interrupt
#endif
	
	if (DMA_DSR_BCR_REG(DMA_BASE_PTR, dma_ch) & DMA_DSR_BCR_CE_MASK){				// Check for configuration error
		return ERROR;
	}
	else{
		return SUCCESS;
	}
}

