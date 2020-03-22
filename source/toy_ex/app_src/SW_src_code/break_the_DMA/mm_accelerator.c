/*****************************************************************************
*  Filename:          mm_accelerator.c
*  Description:       Memory-Mapped Accelerator Driver
*  Date:              2018/11/08 13:25:28 (by Multi-Dataflow Composer - Platform Composer)
*****************************************************************************/

#include "mm_accelerator.h"

int mm_accelerator_no_parallel(
	// port dout_0
	int size_dout_0, int* data_dout_0,
	// port dout_1
	int size_dout_1, int* data_dout_1,
	// port dout_2
	int size_dout_2, int* data_dout_2,
	// port din
	int size_din, int* data_din
	) {
	
	volatile int* config = (int*) XPAR_MM_ACCELERATOR_0_CFG_BASEADDR;
	unsigned int *base_monitor = (unsigned int*)0x43C10000; // base monitor

	*base_monitor = 322; // range monitor e soft reset
	printf("control is %u \n\r", *(base_monitor));
	*(base_monitor+1) = 0x0; // low address
	printf("low is %u \n\r", *(base_monitor+1));
	*(base_monitor+2) = 0xFFFFFFFF; // high address
	printf("high is %u \n\r", *(base_monitor+2));
	*base_monitor = 290; // range monitor e run
	printf("control is %u \n\r", *(base_monitor));

	// configure I/O
	*(config + 2) = size_dout_2;
	*(config + 3) = size_dout_1;
	*(config + 1) = size_din;
	*(config + 4) = size_dout_0;
	
	// send data port din 32
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = (int) data_din; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_1_OFFSET; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = 32*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);

	*base_monitor = 258; // range monitor e stop
	printf("The result is %u \n\r", *(base_monitor+3));

	// send data port din 16
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = (int) (data_din+32); // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_1_OFFSET + 32; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = 16*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	


	// start execution
	*(config) = 0x1000001;
	
	// wait for completion
	while( ((*(config)) & 0x4) != 0x4 );
			
	// receive data port dout_2
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_2_OFFSET; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = (int) data_dout_2; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_dout_2*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	// receive data port dout_1
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_3_OFFSET; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = (int) data_dout_1; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_dout_1*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	// receive data port dout_0
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_4_OFFSET; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = (int) data_dout_0; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_dout_0*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	
	// stop execution
	//*(config) = 0x0;
	
	return 0;
}

int mm_accelerator_d0_parallel(
	// port dout_0
	int size_dout_0, int* data_dout_0,
	// port dout_1
	int size_dout_1, int* data_dout_1,
	// port dout_2
	int size_dout_2, int* data_dout_2,
	// port din
	int size_din, int* data_din
	) {
	
	volatile int* config = (int*) XPAR_MM_ACCELERATOR_0_CFG_BASEADDR;

	// configure I/O
	*(config + 2) = size_dout_2;
	*(config + 3) = size_dout_1;
	*(config + 1) = size_din;
	*(config + 4) = size_dout_0;
	
	// send data port din
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = (int) data_din; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_1_OFFSET; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_din*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	
	// start execution
	*(config) = 0x2000001;
	
	// wait for completion
	while( ((*(config)) & 0x4) != 0x4 );
			
	// receive data port dout_2
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_2_OFFSET; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = (int) data_dout_2; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_dout_2*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	// receive data port dout_1
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_3_OFFSET; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = (int) data_dout_1; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_dout_1*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	// receive data port dout_0
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) = 0x00000002; // verify idle
	//*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x00>>2)) = 0x00001000;	// irq en (optional)
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x18>>2)) = XPAR_MM_ACCELERATOR_0_MEM_BASEADDR + MM_ACCELERATOR_MEM_4_OFFSET; // src
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x20>>2)) = (int) data_dout_0; // dst
	*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x28>>2)) = size_dout_0*4; // size [B]
	while((*((volatile int*) XPAR_AXI_CDMA_0_BASEADDR + (0x04>>2)) & 0x2) != 0x2);
	
	// stop execution
	//*(config) = 0x0;
	
	return 0;
}

