#include "includes.h"

int main(void){
	uint8_t src[21]="123456789122323";
	//uint8_t dst[10]="abcdefghia";
	//my_memmove(src,dst,10);
	my_memzero(src,10);
	return 0;
	
	
}
