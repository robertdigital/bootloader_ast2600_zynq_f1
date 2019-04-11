/*
 * copyright 2019 Aspeed Technology Inc
 * Ashok Reddy Soma <ashok.soma@aspeedtech.com>
*/

#include "pilot.h"
#include "flash.h"

#define FLASH_SECTOR_SIZE	(64*1024)

tU8 p_readbyte (tPVU32 uartBase);
extern flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS];/* FLASH chips info */

void flash_uboot(void)
{
	unsigned int size = 0;
	tU32 spi_addr = 0x0, flash_size = 0;
	tU32 erase_sectors = 0;


	flash_init();
//	flash_print_info (&flash_info[0]);

	nc_printf ("Send binary file\r\n");
	size = receive_file (0x87000000, UART);

	if(size > FLASH_SECTOR_SIZE)
	{
		erase_sectors=(size/FLASH_SECTOR_SIZE);

		if ((size % FLASH_SECTOR_SIZE) != 0)
			erase_sectors++;
	} else {
		erase_sectors=1;
	}

//	nc_printf("sectors to erase ");
//	print_reg(erase_sectors);

	nc_printf("Erasing");
	flash_erase(&flash_info[0], 0, erase_sectors);

	nc_printf("Flashing..");
	write_buff (&flash_info[0], 0x87000000, 0x70000000, size);
	nc_printf("done\n");
}

void main(void)
{
	char option;
	tU32 dst_addrs=0x0;
	tVU32 dbg_uart_base = UART;
	tU32 strapsts;

	nc_printf("\n\n[AST2600] ASPEED TECHNOLOGY\n");

	while(1) {
		nc_printf("\nBootloader Version %s %s\n",__DATE__,__TIME__);
		nc_printf("1 Flash Boot spi(send .bin)\n");
		nc_printf("2 Dbg Monitor Mode\n");
		nc_printf("3 Erase Entire Spi Flash\n\n");

		option = p_readbyte (dbg_uart_base);
		switch(option){
			case '1':
				nc_printf("option 1. Flash boot spi selected\n\n");
				flash_uboot();
				break;
			case '2':
				nc_printf("option 2. Dbg Monitor Mode selected\n\n");
				break;
			case '3':
				nc_printf("option 3. Erase entire SPI Flash selected\n\n");
				break;
			default:
				break;
		}

	}
}

tU8 p_readbyte (tPVU32 uartBase)
{
	volatile unsigned char  val;
	while(1)
	{
		val = *(tPVU8)(UART + 0x14); 
		if(val&0x1)
		{
			*uartBase=UART;
			return(*(tPVU8)(UART));

		}
	}
}
