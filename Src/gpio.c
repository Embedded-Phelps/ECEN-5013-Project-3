/***************************************************************************
 *
 *	Filename: 		gpio.c
 *  Description:  	KL25Z GPIO functions implementation
 *  Author: 		ShuTing Guo  
 *  Date: 			Oct. 2016
 *
 *****************************************************************************/
 
#include "includes.h"

void led_Gpio_Init(void) 
{

    PORTB_PCR18 |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);               /* Red LED: GPIO, digital output */
    PORTB_PCR19 |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);               /* GREENLED: GPIO, digital output*/
    PORTD_PCR1  |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);               /* BLUE LED: GPIO, digital output*/

    FGPIOB_PSOR |= 1<<18;                                               /* Port output set to logic 1   */
    FGPIOB_PDDR |= 1<<18;                                               /* Pin set for GPIO function    */
    FGPIOB_PSOR |= 1<<19;                                               
    FGPIOB_PDDR |= 1<<19;                                               
    FGPIOD_PSOR |= 1<<1;                                            
    FGPIOD_PDDR |= 1<<1;                                              
}

void spi_Gpio_Init(void)
{
	/* Set PTC5 pin to SPI0 SCK function */	
	PORTC_PCR5 |= PORT_PCR_MUX(2);	
	/* Set PTC6 pin to SPI0 MOSI function */
	PORTC_PCR6 |= PORT_PCR_MUX(2);
	/* Set PTC7 pin to SPI0 MISO function */						
	PORTC_PCR7 |= PORT_PCR_MUX(2);	
	/* Set PTC12 pin to GPIO function, serve as CS */
	PORTC_PCR12|= PORT_PCR_MUX(1);
	FGPIOC_PSOR|= 1<<12;
	FGPIOC_PDDR|= 1<<12;
	
	/* Set PTC4 pin to SPI0 CS0 function */
	//PORTC_PCR4 |= PORT_PCR_MUX(2);									
	//FGPIOC_PSOR |= 1<<4;												/* Set CS0 */
	//FGPIOC_PDDR |= 1<<4;												/* Set CS0 as output */
}

void nrf_Gpio_Init(void)
{
	PORTC_PCR13|= PORT_PCR_MUX(1);		// Set PCR13 as a GPIO output pin
	FGPIOC_PCOR|= 1<<13;				// Serves as CE
	FGPIOC_PDDR|= 1<<13;				// Low at default
	PORTC_PCR16|= PORT_PCR_MUX(1);		// Set PCR16 as a GPIO input pin
	FGPIOC_PDDR|= 0<<16;				// Serves as IRQ
}
