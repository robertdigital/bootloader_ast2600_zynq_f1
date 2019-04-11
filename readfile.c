/*
 * copyright 2019 Aspeed Technology Inc
 * Ashok Reddy Soma <ashok.soma@aspeedtech.com>
 */

#include "pilot.h"

unsigned int receive_file (unsigned int bufferaddrs,tVU32 dbg_uart_base)
{
	int size = 0;							//Number of words to be programmed to flash
	unsigned char *program_store_add;		//Starting Address to store binary data read through UART3
	char data;
	char status;
	unsigned long int timer;

	program_store_add = (unsigned char *)(bufferaddrs);

	//flush uart rx buffer
	*(volatile int *)(dbg_uart_base+0x8)|=(0x2);              //(~0x2);

	//Read binary data from UART3 and write to ddr
	timer = 0x8fffff;

	// Wait for first character to come  before time out            
	status =0x0;
	while(!(status&0x1))
	{
		status=(char)(*(tPVU32)(dbg_uart_base+0x14));
	}


	while(timer)
	{

		while(status&0x1)
		{
			data=(char)(*(tPVU32)(dbg_uart_base));
			size++;
			*program_store_add= data;
			program_store_add++;

			status=(char)(*(tPVU32)(dbg_uart_base+0x14));
#if defined (ASIC_DUT)
			timer = 0xffffff;
#else
#if defined (ZYNQ)
			timer = 0xffffff;
#else
			timer = 0x2fff;
#endif
#endif
		}

		timer--;
		status=(char)(*(tPVU32)(dbg_uart_base+0x14));
	}

	// Print the size after the file has been read
	return size;
}
