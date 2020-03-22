/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "mm_accelerator.h"
#include "xil_cache.h"



int main()
{
	unsigned int *base_monitor = (unsigned int*)0x43C10000; // base monitor
    init_platform();
    Xil_DCacheDisable();


    print("Start Application\n\r");
    volatile int* config = (int*) XPAR_MM_ACCELERATOR_0_CFG_BASEADDR;

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
    printf("%x\n\r",data_dout_0);
    int data_dout_1[1];
    int data_dout_2[1];


    mm_accelerator_no_parallel(
    	1, data_dout_0,
    	1, data_dout_1,
    	1, data_dout_2,
    	48, data_din
    	);
    printf("%d %d %d\n\r",data_dout_0[0],data_dout_1[0],data_dout_2[0]);

    printf(" Monitor result is %d \n\r", *(config + 6));


	// end monitor
	//*base_monitor = 258; // range monitor e stop

	//printf("The result is %u \n\r", *(base_monitor+3));

	printf("End!\n\r");

    cleanup_platform();
    return 0;
}
