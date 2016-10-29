#include "includes.h"

int main(void){
	/*uint8_t src[10]="1234567891";
	uint8_t dst[10]="abcdefghia";
	dma_memmove(src,dst,7,0);
	dma_memzero(src,10,0);
	dma_memzero(dst,5,0);
	*/
	/* Enable system interrupt */                                     
	__enable_irq();
	
	/* Enable the clock gate to ALL the Port module */
	PORT_ENABLE_CLK(A);		
	PORT_ENABLE_CLK(B);
	PORT_ENABLE_CLK(C);
	PORT_ENABLE_CLK(D);
	PORT_ENABLE_CLK(E);
	
	/* Initialize uart0 */
	uart0_Init(9600,0,0,8,1);
	log_Str("Testing123, Serial Print Test, no params\n");
	/* Initialize PIT */
	pit_Init();
	
	time_Profiler();
	while (1);
	
	
}
