
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include "mm_accelerator.h"
#include "monitor.h"

int main()
{
	//unsigned int *base_monitor = (unsigned int*)0x43C10000; // base monitor
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

	    //inzialize monitor
		inizialize(322,0x0,0xFFFFFFFF);

		//start monitor
		start_monitor(290);


		mm_accelerator_no_parallel(
				1, data_dout_0,
				1, data_dout_1,
				1, data_dout_2,
				48, data_din
		);
		printf("%d %d %d\n\r",data_dout_0[0],data_dout_1[0],data_dout_2[0]);


		// end monitor
		stop_monitor(258);


    	//print monitor 1,2 and 3
    	print_monitor();


	printf("End!\n\r");

    //cleanup_platform();
    return 0;
}
