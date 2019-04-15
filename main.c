/*
 * copyright 2019 Aspeed Technology Inc
 * Ashok Reddy Soma <ashok.soma@aspeedtech.com>
*/

#include "pilot.h"
#include "flash.h"

unsigned char readbyte (tPVU32 uartBase);
void flash_uboot(void);
extern flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS];/* FLASH chips info */

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

		option = readbyte (dbg_uart_base);
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

unsigned char readbyte (tPVU32 uartBase)
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

void flash_uboot(void)
{
	unsigned int size = 0;
	unsigned int spi_addr = 0x0;
	unsigned int flash_size = 0;
	unsigned int erase_sectors = 0;
	volatile unsigned int chk = 0;

	flash_init();
//	flash_print_info (&flash_info[0]);

	nc_printf ("Send binary file\r\n");
	size = receive_file (DDR_READ_ADDR, UART);

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
	write_buff (&flash_info[0], DDR_READ_ADDR, AST_FMC_CS0_BASE, size);
	nc_printf("done\n");

	nc_printf("\nReading");

	for(chk=0; chk< size; chk++){

		if(*((tPVU8)(DDR_READ_ADDR+chk)) != (*((tPVU8)(AST_FMC_CS0_BASE + chk))))
		{
			nc_printf("ERROR at "); print_reg(chk);
			nc_printf("data is"); print_reg(*((tPVU8)(AST_FMC_CS0_BASE + chk)));
			break;
		}
		if (chk%4096 == 0) nc_printf(".");
	}

	nc_printf("\nSUCCESS\n");
}
