/***************************************************************************
 *
 *	Filename: 		nRF24L01.h
 *  Description:  	nRF24L01 driver function prototype header file
 *  Author: 		ShuTing Guo  
 *  Date: 			Oct. 2016
 *
 *****************************************************************************/
#ifndef __MESSAGE_H
#define __MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "includes.h"

#define MAX_DATA_SIZE (10)

#define RED_LED	(0x01)
#define GREEN_LED (0x02)
#define BLUE_LED (0X03)

typedef enum Cmds_t {
	LED_ON = 0x00,
	LED_OFF = 0xFF,
	SET_RLED = 0x01,
	SET_GLED = 0X02,
	SET_BLED = 0x03
	//more command IDs
}Cmds;

typedef enum Msg_Sta_t{
	NEW_MSG, NO_MSG,
	MSG_DECODED, MSG_CORRUPTED, CMD_ERROR,
	DATA_SIZE_OVERFLOW, MESSAGE_SENT
	//more to come
}Msg_Sta;

typedef struct ST_Msg_t{
	Cmds command;							// Commands			
	uint8_t length;							// Length of the data, excluding the command
	uint8_t data[MAX_DATA_SIZE];			// array that stores the data
	uint16_t checksum;						// checksum with a adding algorithm
}ST_Msg;

/*********************************************************************
* @name: send_ST_Msg
*
* @description: calculate the checksum of the message and send the packet 
*               through UART
*               
* @param: command -- command to send
*         data -- data to send
*         length -- number of data bytes
*
* @return: DATA_OVERFLOW / MESSAGE_SENT 
*/
Msg_Sta send_ST_Msg(Cmds * command, uint8_t * data, uint32_t data_length);

/***********************************************************************
* @name: receive_ST_Msg
*
* @description: receive serial data from the UART circular buffer 
*               and wrap up the data received into a ST_Msg type message
*               
* @return: NEW_MSG / NO_MSG 
*/
Msg_Sta receive_ST_Msg(void);

/***********************************************************************
* @name: decode_ST_Msg
*
* @description: decode a ST_Msg type message and call functions according  
*               to the command received
*               
* @param: msg -- a ST_Msg message
*
* @return: MSG_CORRUPTED / CMD_ERROR / MSG_DECODED
*/
Msg_Sta decode_ST_Msg(ST_Msg * msg);

/***********************************************************************
* @name: config_LED
*
* @description: initialize the RGB LEDs and turn them on  
*
*/
void config_LED(void);

/***********************************************************************
* @name: set_LED
*
* @description: set the selected LED with certain brightness  
*               
*/
void set_LED(uint8_t led, uint8_t brightness);


#ifdef __cplusplus
}
#endif


#endif
