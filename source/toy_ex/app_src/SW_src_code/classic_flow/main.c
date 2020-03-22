
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include "mm_accelerator.h"



int main()
{
	unsigned int *base_monitor = (unsigned int*)0x43C10000; // base monitor
    init_platform();
    Xil_DCacheDisable();

    print("Start Application\n\r");

	int data_din[48];
	    int i;
	    for(i=0;i<48;i++) {
	    	if(i<16)
	    		data_din[i] = 1;
	    	else if(i<32)
	    		data_din[i] = 10;
	    	else
	    		data_din[i] = -1;
	    }
	    Xil_DCacheFlush();
	    int data_dout_0[1];
	    int data_dout_1[1];
	    int data_dout_2[1];

	    print("Start Application\n\r");

	    // initialize monitor
		*base_monitor = 322; // range monitor e soft reset
		printf("control is %u \n\r", *(base_monitor));
		*(base_monitor+1) = 0x0; // low address
		printf("low is %u \n\r", *(base_monitor+1));
		*(base_monitor+2) = 0xFFFFFFFF; // high address
		printf("high is %u \n\r", *(base_monitor+2));
		*base_monitor = 290; // range monitor e run
		printf("control is %u \n\r", *(base_monitor));



    mm_accelerator_no_parallel(
    	1, data_dout_0,
    	1, data_dout_1,
    	1, data_dout_2,
    	48, data_din
    	);
    printf("%d %d %d\n\r",data_dout_0[0],data_dout_1[0],data_dout_2[0]);


	// end monitor
	*base_monitor = 258; // range monitor e stop
//
	printf("primo livello %x \n\r", *(base_monitor+3));
	printf("secondo livello %x \n\r", *(base_monitor+4));
	printf("secondo livello %x \n\r", *(base_monitor+5));
	printf("terzo livello %x \n\r", *(base_monitor+6));

	printf("End!\n\r");

    //cleanup_platform();
    return 0;
}
