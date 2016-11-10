#include "includes.h"

extern CircBuf_t * rx_buf;

Msg_Sta send_ST_Msg(Cmds * command, uint8_t * data, uint32_t data_length){
	uint8_t i;
	uint16_t checksum=0;
	if (data_length > MAX_DATA_SIZE){
		return DATA_SIZE_OVERFLOW;
	}
	checksum += * command;
	for (i=0;i<data_length;i++){
		checksum += data[i];
	}
	log_Mem(command, 1);
	log_Int("", data_length);
	log_Mem(data, data_length);
	log_Int("", checksum);
	return MESSAGE_SENT;
}


Msg_Sta receive_ST_Msg(void){
	ST_Msg * msg = (ST_Msg *)malloc(sizeof(ST_Msg));
	uint8_t i;
	uint8_t temp;
	if(cb_IsEmpty(rx_buf)!=EMPTY){
		cb_Dequeue(rx_buf, &temp);
		msg->command = temp;
		cb_Dequeue(rx_buf, &(msg->length));
		if (msg->length > MAX_DATA_SIZE){
			return DATA_SIZE_OVERFLOW;
		}
		for(i = 0; i < msg->length; i++){
			cb_Dequeue(rx_buf, &(msg->data[i]));
		}
		cb_Dequeue(rx_buf, &temp);
		msg->checksum |= ((uint16_t) temp) << 8;
		cb_Dequeue(rx_buf, &temp);
		msg->checksum |= temp;
		decode_ST_Msg(msg);
		free(msg);
		return NEW_MSG;
	}
	else{
		free(msg);
		return NO_MSG;
	}
}

Msg_Sta decode_ST_Msg(ST_Msg * msg){
	uint16_t check=0;
	uint8_t i;
	//Perform checksum
	check += msg->command;
	for(i = 0; i < msg->length; i++){
		check += msg->data[i];
	}
	if(check != msg->checksum){
		return MSG_CORRUPTED;
	}
	//decode message
	switch (msg->command){
		case (LED_ON): 		config_LED();
							break;
		case (LED_OFF): 	set_LED(RED_LED, 0);
							set_LED(GREEN_LED, 0);
							set_LED(BLUE_LED, 0);
							break;
		case (SET_RLED): 	set_LED(RED_LED, msg->data[0]);
							break;
		case (SET_GLED): 	set_LED(GREEN_LED, msg->data[0]);
							break;
		case (SET_BLED): 	set_LED(BLUE_LED, msg->data[0]);
							break;
		default: 			return CMD_ERROR;
	}
	return MSG_DECODED;
}

void config_LED(){
	led_Gpio_Init();
	tpm_Init();
}

void set_LED(uint8_t led, uint8_t brightness){
	switch(led){
		case (RED_LED):	SET_LED_RED(brightness);
							break;
		case (GREEN_LED):	SET_LED_GREEN(brightness);
							break;
		case (BLUE_LED):	SET_LED_BLUE(brightness);
							break;							
		default:;
	}
}
