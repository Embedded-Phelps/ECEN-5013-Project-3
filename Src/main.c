#include "includes.h"

int main(void){
	uint8_t src[10]="1234567891";
	uint8_t dst[10]="abcdefghia";
	dma_memmove(src,dst,7,0);
	dma_memzero(src,10,0);
	dma_memzero(dst,5,0);
	return 0;
	
	
}
