#include "includes.h"

int main(void){
	uint8_t src[5]="12345";
	uint8_t dst[5];
	dma_memmove(src,dst,5,0);
	dma_memzero(src,5,0);
	return 0;
	
	
}
