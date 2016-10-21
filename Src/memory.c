/***************************************************************************
 *
 *	Filename: 		memory.c
 *  Description:  	memory manipulation functions implementation
 *  Author: 		ShuTing Guo  
 *  Date: 			Oct. 2016
 *
 *****************************************************************************/

#include "includes.h"

/****************************************************
* @name: my_memmove
*
* @description: copy data from one memory to the other 
*               
* @param: src -- pointer to the source address
*         dst -- pointer to the destination address
*         length -- lenth of memory bytes to copy
*
* @return:SUCCESS/ERROR 
*/
int8_t my_memmove(uint8_t * src, uint8_t * dst, int32_t length){
    uint32_t i;
    uint8_t * psrc = (uint8_t *) src; 	
    uint8_t * pdst = (uint8_t *) dst;
	if (length == 0)
        return ERROR;
    if((NULL==src)||(NULL==dst))
	return ERROR;
    
    if ((pdst <= psrc) || (pdst > (psrc+length))){ //forward copy
	for (i=0;i<length;i++){
	    *pdst = *psrc;
	    pdst++;
	    psrc++;
	}
    }
    else{				//backward copy
        psrc += length-1;
	pdst += length-1;
	for (i=0;i<length;i++){
	    *pdst = *psrc;
            pdst--;
	    psrc--;
	}
    }
    return SUCCESS;
}

/****************************************************
* @name: dma_memmove
*
* @description: copy data from one memory to the other using DMA
*               for KL25Z only
*               
* @param: src -- pointer to the source address
*         dst -- pointer to the destination address
*         length -- lenth of memory bytes to copy
*		  ch -- DMA channel
*
* @return:SUCCESS/ERROR 
*/
int8_t dma_memmove(uint8_t * src, uint8_t * dst, uint32_t length, uint8_t ch){
	if(!dma_Init_Mem2mem(ch, src, dst, length)){
		DMA_DCR_REG(DMA_BASE_PTR, ch) |= DMA_DCR_START_MASK;
		return SUCCESS;
	}
	else
		return ERROR;
}

/****************************************************
* @name: my_memzero
*
* @description: zero out memory 
*               
* @param: src -- pointer to the memory address
*         length -- lenth of memory bytes to zero out
*
* @return:SUCCESS/ERROR 
*/
int8_t my_memzero(uint8_t * src, uint32_t length){
    uint32_t i;
	if(src == NULL)
        return ERROR;
    
    for(i = 0;i < length;i ++)
        *(src + i) = 0;
    return SUCCESS;
}

/****************************************************
* @name: dma_memzero
*
* @description: zero out memory using DMA
*				for KL25Z only 
*               
* @param: src -- pointer to the memory address
*         length -- lenth of memory bytes to zero out
*		  ch -- DMA channel
*
* @return:SUCCESS/ERROR 
*/
int8_t dma_memzero(uint8_t * src, uint32_t length, uint8_t ch){
	uint8_t temp=0;
	if(!dma_Init_Mem2mem(ch, &temp, src, length)){
		DMA_DCR_REG(DMA_BASE_PTR, ch) &= ~DMA_DCR_SINC_MASK;
		DMA_DCR_REG(DMA_BASE_PTR, ch) |= DMA_DCR_START_MASK;
		return SUCCESS;
	}
	else
		return ERROR;
}

/****************************************************
* @name: my_reverse
*
* @description: reverse the order of certain bytes 
*               starting from a memory location 
*               
* @param: src -- pointer to the starting memory address
*         length -- lenth of memory bytes to reverse
*
* @return:SUCCESS/ERROR 
*/
int8_t my_reverse(uint8_t * str, uint32_t length){
    uint8_t temp;
    uint32_t i=0;
    if (str == NULL)
        return ERROR;
    while((i) < (length-1-i)){
        temp = *(str+i);
        *(str+i) = *(str+length-1-i);
        *(str+length-1-i) = temp;
        i++;
    }
    return SUCCESS;
}
