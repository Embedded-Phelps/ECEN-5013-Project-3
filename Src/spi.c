void spi0_Init(uint8_t mode){
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;					// Enable SPI0 clock gate
	SPI0->C1 |= SPI_C1_SPE_MASK;						// Enable SPI0 system
	SPI0->C1 |= mode << SPI_C1_MSTR_SHIFT;				// Select Master/Slave mode
	SPI->BR |= SPI_BR_SPPR(2);							// Set SPI baud rate to 4MHz
}

void spi0_Sendbyte(uint8_t data){
	uint8_t temp;
	while((SPI0_S &= SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);	// Wait until the transmit buffer is empty
	SPI0_D = data;
	While((SPI0_S &= SPI0_S_SPRF_MASK) != SPI_S_SPTEF_MASK);
	temp = SPI0_D;
}

uint8_t spi0_getbyte(void){
	uint8_t temp;
	while((SPI0_S &= SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);	// Wait until the transmit buffer is empty
	SPI0_D = 0xFF;
	While((SPI0_S &= SPI0_S_SPRF_MASK) != SPI_S_SPTEF_MASK);
	temp = SPI0_D;
	return (uint8_t) temp;
}