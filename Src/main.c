#include "includes.h"

int main(void){
	/*uint8_t src[10]="1234567891";
	uint8_t dst[10]="abcdefghia";
	dma_memmove(src,dst,7,0);
	dma_memzero(src,10,0);
	dma_memzero(dst,5,0);
	*/
	uint8_t tem[3]="123";
	volatile uint8_t wtf;
	uint8_t i=0;
	/* Enable system interrupt */                                     
	//__enable_irq();
	
	/* Enable the clock gate to ALL the Port module */
	PORT_ENABLE_CLK(A);		
	PORT_ENABLE_CLK(B);
	PORT_ENABLE_CLK(C);
	PORT_ENABLE_CLK(D);
	PORT_ENABLE_CLK(E);
	
	/* Initialize uart0 */
	uart0_Init(9600,0,0,8,1);
	
	log_Str("NRF testing...\n");
	nrf_Init();
	//check CE pin
	//check IRQ pin
	//nrf_Write_Reg(W_REGISTER+CONFIG, 0x08);
	//nrf_Write_Reg(W_REGISTER+CONFIG, 0x0A);
	//tem = nrf_Read_Reg(CONFIG);
	//while(nrf_Check()!=NRF_DETECTED);
	
	while(i<5){
	  nrf_Write_Reg(W_REGISTER|STATUS, 0x1E);
	  wtf = nrf_Read_Reg(STATUS);
	  i++;
	}
	//nrf_Write_Reg(W_REGISTER+STATUS, status);
	//status = nrf_Read_Reg(STATUS);
	nrf_TxMode();
	//tem = nrf_Read_Reg(CONFIG);
	if(nrf_TxPacket(tem)==TX_DS)
		tem[1]=0;
	/* Initialize PIT */
	//pit_Init();
	
	//time_Profiler();
	while (1);
	
	
}
