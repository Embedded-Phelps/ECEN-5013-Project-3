#include "includes.h"

void spi0_Init(uint8_t mode){
	spi_Gpio_Init();
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;					// Enable SPI0 clock gate
	SPI0->C1 = SPI_C1_SPE_MASK;						// Enable SPI0 system
	SPI0->C1 |= SPI_C1_MSTR_MASK;
	//SPI0->C1 |= mode << SPI_C1_MSTR_SHIFT;				// Select Master/Slave mode
	//SPI0->C1 &= ~SPI_C1_CPHA_MASK;
	SPI0->BR |= SPI_BR_SPPR(3);							// Set SPI baud rate to 4MHz
	SPI_DESELECT;
}

uint8_t spi0_Sendbyte(uint8_t data){
	uint8_t temp;
	while( ! (SPI0_S & SPI_S_SPTEF_MASK) );	// Wait until the transmit buffer is empty
	//SPI_SELECT;
	SPI0_D = data;
	while( ! (SPI0_S & SPI_S_SPRF_MASK) );
	temp = SPI0_D;
	//SPI_DESELECT;
	return temp;
}

uint8_t spi0_getbyte(void){
	uint8_t temp;
	while((SPI0_S &= SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);	// Wait until the transmit buffer is empty
	//SPI_SELECT;
	SPI0_D = 0xFF;
	while((SPI0_S &= SPI_S_SPRF_MASK) != SPI_S_SPTEF_MASK);
	temp = SPI0_D;
	//SPI_DESELECT;
	return temp;
}
