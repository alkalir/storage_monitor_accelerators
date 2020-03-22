#include <stdio.h>
#include "xil_printf.h"



unsigned int *base_monitor = (unsigned int*)0x43C10000; // base monitor


void inizialize(bm,la,ha){
	*base_monitor = bm; // range monitor e soft reset
	printf("control is %u \n\r", *(base_monitor));
	*(base_monitor+1) = la; // low address
	printf("low is %u \n\r", *(base_monitor+1));
	*(base_monitor+2) = ha; // high address
	printf("high is %u \n\r", *(base_monitor+2));

}

void start_monitor(bm){
	*base_monitor = bm; // range monitor e run
	printf("control is %u \n\r", *(base_monitor));
}

void stop_monitor(bm){
	*base_monitor = bm; // range monitor e stop
}

void print_monitor(){
	printf("primo livello %x \n\r", *(base_monitor+3));
	printf("secondo livello %x \n\r", *(base_monitor+4));
	printf("secondo livello %x \n\r", *(base_monitor+5));
	printf("terzo livello %x \n\r", *(base_monitor+6));
}
