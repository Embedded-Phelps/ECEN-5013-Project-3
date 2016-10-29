/***************************************************************************
 *
 *	Filename: 		profiler.c
 *  Description:  	Time profiling a series of function
 *  Author: 		ShuTing Guo  
 *  Date: 			Oct. 2016
 *
 *****************************************************************************/
 
#include "includes.h"

#ifndef _BBB
int32_t num_pit_overflow=0;

void PIT_IRQHandler(void){
    PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;					// Disable PIT Timer
		PIT_TFLG0 |= PIT_TFLG_TIF_MASK;             	// Clear Timer Interrupt Flag */
		num_pit_overflow++;
    PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;					//Enable PIT Timer
}
#endif

void time_Profiler_Memmove(int32_t bytes){
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	uint8_t *destination = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	uint8_t n;
	
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		my_memmove(source, destination, bytes);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("Time of my_memmove(): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;
	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		memmove(source, destination, bytes);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of memmove(): ", nsec);
	log_Str(" microsec\r\n");
	
#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_memmove(source, destination, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("CPU cycles of my_memmove(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of my_memmove(): ", time);
	log_Str(" ns\r\n");
	cycle_avg = 0;
	time=0.0;
	
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		memmove(source, destination, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("CPU cycles of memmove(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of memmove(): ", time);
	log_Str(" ns\r\n")
	;
#endif
	free(source);
	free(destination);
}

void time_Profiler_Memset(int32_t bytes){
	uint8_t n;
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		my_memzero(source, bytes);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("Time of my_memzero(): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;
	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		memset(source, 0, bytes);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of memset(): ", nsec);
	log_Str(" microsec\r\n");
	
#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_memzero(source, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("CPU cycles of my_memzero(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of my_memzero(): ", time);
	log_Str(" ns\r\n");
	cycle_avg = 0;
	time=0.0;
	
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		memset(source, 0, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("CPU cycles of memset(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of memset(): ", time);
	log_Str(" ns\r\n");
#endif
	free(source);
}

void time_Profiler_Reverse(int32_t bytes){
	uint8_t n;
	uint8_t *source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);

#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		my_reverse(source, bytes);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("Time of my_reverse(): ", nsec);
	log_Str(" microsec\r\n");
	
#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_reverse(source, bytes);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("CPU cycles of my_reverse(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of my_reverse(): ", time);
	log_Str(" ns\r\n");

#endif
	free(source);
}

void time_Profiler_itoa(int32_t data){
	uint8_t n;
	uint8_t *str = (uint8_t *)malloc(sizeof(uint8_t)*20);	
	
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		my_itoa(source, data, 10);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of my_itoa(): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;
	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		itoa(source, data, 10);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of itoa(): ", nsec);
	log_Str(" microsec\r\n");
	
#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_itoa(str, data, 10);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("CPU cycles of my_itoa(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of my_itoa(): ", time);
	log_Str(" ns\r\n");

#endif
	free(str);
}

void time_Profiler_ftoa(float data){
	uint8_t n;	
	uint8_t *str = (uint8_t *)malloc(sizeof(uint8_t)*32);

#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		my_ftoa(source, data);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of my_ftoa(): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;
	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		sprintf(source,"%f", data);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of sprintf(): ", nsec);
	log_Str(" microsec\r\n");
	
#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_ftoa(str, data);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("CPU cycles of my_ftoa(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of my_ftoa(): ", time);
	log_Str(" ns\r\n");
#endif	
	free(str);
}

void time_Profiler_atoi(uint8_t * str){
	uint8_t n;
	
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		my_atoi(str);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of my_atoi(): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;
	
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		atoi(str);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of atoi(): ", nsec);
	log_Str(" microsec\r\n");
	
#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		my_atoi(str);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
			
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;

	log_Int("CPU cycles of my_atoi(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of my_atoi(): ", time);
	log_Str(" ns\r\n");
#endif
}

void time_Profiler_MallocFree_Empty(int32_t bytes){
	uint8_t * source;

#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	gettimeofday(&start, NULL);
	source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	Log_Int("Time of malloc(): ", nsec);
	log_Str(" microsec\r\n");
	
	nsec=0;
	gettimeofday(&start, NULL);
	free(source);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);

	log_Int("Time of free(): ", nsec);
	log_Str(" microsec\r\n");

#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	cycle += PIT_CVAL0;
	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	cycle += (num_pit_overflow*240);
	cycle_avg += cycle;	
	num_pit_overflow=0;
	cycle=0;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("CPU cycles of malloc(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of malloc(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	free(source);
	cycle += PIT_CVAL0;
	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	cycle += (num_pit_overflow*240);
	cycle_avg += cycle;	
	num_pit_overflow=0;
	cycle=0;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Int("CPU cycles of free(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of free(): ", time);
	log_Str(" ns\r\n");
#endif
}

void time_Profiler_MallocFree_Nonempty(int32_t bytes){
	uint8_t * source;
	uint8_t * temp;
	
#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	temp = (uint8_t *)malloc(sizeof(uint8_t)*10);
	gettimeofday(&start, NULL);
	source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	gettimeofday(&finish, NULL);
	nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("Time of malloc() with non-empty heap: ", nsec);
	log_Str(" microsec\r\n");
	free(source);

#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	temp = (uint8_t *)malloc(sizeof(uint8_t)*10);
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	source = (uint8_t *)malloc(sizeof(uint8_t)*bytes);
	cycle += PIT_CVAL0;
	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	cycle += (num_pit_overflow*240);
	cycle_avg += cycle;		
	num_pit_overflow=0;
	cycle=0;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Int("Number of bytes: ", bytes);
	log_Str("\r\n");
	log_Int("CPU cycles of malloc() with non-empty heap: ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of malloc() with non-empty heap: ", time);
	log_Str(" ns\r\n");
	free(source);

#endif
	free(temp);
}

void time_Profiler_cb_EnDequeue(){
	uint8_t n;
	uint8_t temp;
	CircBuf_t * cb;

#ifdef _BBB
	struct timeval start, finish;
	int32_t nsec=0;
	cb=cb_Init(cb,5);
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		cb_Enqueue(cb,1);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of cb_Enqueue(): ", nsec);
	log_Str(" microsec\r\n");
	
	nsec=0;
	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		cb_Dequeue(cb,&temp);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of cb_Dequeue(): ", nsec);
	log_Str(" microsec\r\n");

#else 
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	cb=cb_Init(cb,5);
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		cb_Enqueue(cb,1);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Int("CPU cycles of cb_Enqueue(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of cb_Enqueue(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		cb_Dequeue(cb,&temp);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Int("CPU cycles of cb_Dequeue(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of cb_Dequeue(): ", time);
	log_Str(" ns\r\n");
#endif
	cb_Destroy(cb);
}

void time_Profiler_Log(){
	uint8_t n;
	uint8_t temp[16]="log_Mem testing";
	int32_t cycle_avg=0;
	int32_t cycle=0;
	float time=0.0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		log_Str("1");
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Str("\r\n");
	log_Int("CPU cycles of log_Str(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of cb_log_Str(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		log_Str("1111");
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Str("\r\n");
	log_Int("CPU cycles of log_Str(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of cb_log_Str(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		log_Str("111111111111");
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Str("\r\n");
	log_Int("CPU cycles of log_Str(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of cb_log_Str(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		log_Mem(temp, 15);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Str("\r\n");
	log_Int("CPU cycles of log_Mem(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of log_Mem(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		log_Int("log_Int testing:", 1);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Str("\r\n");
	log_Int("CPU cycles of log_Int(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of log_Int(): ", time);
	log_Str(" ns\r\n");
	
	time=0.0;
	cycle_avg=0;
	for(n=0;n<3;n++){
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		log_Float("log_Float testing:", 3.333);
		cycle += PIT_CVAL0;
		PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
		cycle += (num_pit_overflow*240);
		cycle_avg += cycle;	
		num_pit_overflow=0;
		cycle=0;
	}
	cycle_avg /= 3;
	time = cycle_avg * TIME_PER_CYCLE;
	log_Str("\r\n");
	log_Int("CPU cycles of log_Float(): ", cycle_avg);
	log_Str("\r\n");
	log_Float("Time of log_Float(): ", time);
	log_Str(" ns\r\n");
}

#ifdef _BBB
void time_Profiler_Printf(){
	uint8_t n;
	struct timeval start, finish;
	int32_t nsec=0;;

	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		printf("20 character string!\n");
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of printf(str): ", nsec);
	log(" microsec\r\n");
	nsec=0;

	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		printf("%d\n",30);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of printf(%d,x): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;

	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		printf("%d %d\n",30,40);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of printf(%d %d,x,y): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;

	for(n=0;n<2;n++){
		gettimeofday(&start, NULL);
		printf("%d %d %d\n",30,40,50);
		gettimeofday(&finish, NULL);
		nsec +=(finish.tv_sec-start.tv_sec)*1000000+(finish.tv_usec-start.tv_usec);
	}
	nsec /= 2;
	log_Int("Time of printf(%d %d %d,x,y,z): ", nsec);
	log_Str(" microsec\r\n");
	nsec=0;
}
#endif

void time_Profiler(){
	time_Profiler_Memmove(10);			
	time_Profiler_Memmove(100);
	time_Profiler_Memmove(1000);
	time_Profiler_Memmove(5000);
	/*time_Profiler_Memset(10);
	time_Profiler_Memset(100);
	time_Profiler_Memset(500);
	time_Profiler_Memset(1000);
	time_Profiler_Reverse(10);
	time_Profiler_Reverse(100);
	time_Profiler_Reverse(500);
	time_Profiler_Reverse(1000);
	time_Profiler_itoa(100);
	time_Profiler_ftoa(100.123);
	time_Profiler_atoi("12345");
	time_Profiler_MallocFree_Empty(10);
	time_Profiler_MallocFree_Empty(100);
	time_Profiler_MallocFree_Empty(500);
	time_Profiler_MallocFree_Empty(1000);
	time_Profiler_MallocFree_Nonempty(10);
	time_Profiler_MallocFree_Nonempty(100);
	time_Profiler_MallocFree_Nonempty(500);
	time_Profiler_MallocFree_Nonempty(1000);
	time_Profiler_cb_EnDequeue();

#ifndef _BBB
	time_Profiler_Log();
#endif*/

#ifdef _BBB
	time_Profiler_Printf();
#endif
}
