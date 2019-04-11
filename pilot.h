/*
 * copyright 2019 Aspeed Technology Inc
 * Ashok Reddy Soma <ashok.soma@aspeedtech.com>
*/
#ifndef __PILOT_H__
#define __PILOT_H__

typedef unsigned int              tU32;
typedef unsigned int              u32;
typedef unsigned int              uint;
typedef unsigned long			  ulong;
typedef unsigned short            tU16;
typedef unsigned short            ushort;
typedef unsigned char             tU8;
typedef unsigned char             u8;
typedef unsigned char             uchar;

typedef unsigned int *            tPU32;
typedef unsigned short *          tPU16;
typedef unsigned char *           tPU8;

typedef volatile unsigned int     tVU32;
typedef volatile unsigned short   tVU16;
typedef volatile unsigned char    tVU8;

typedef volatile unsigned int *   tPVU32;
typedef volatile unsigned short * tPVU16;
typedef volatile unsigned char *  tPVU8;

int nc_printf(const char *format, ...);
extern void print_reg(unsigned int reg);

#define NULL          0

#define HW_ENV		1


//#if defined (ZYNQ)
#if 1
#define BASE_OFFSET	0x40000000
#else 
#define BASE_OFFSET	0x00000000
#endif

#define UART			(BASE_OFFSET | 0x1E784000)
	#define LSROff		(0x5<<2)
	#define THROff		(0x0<<2)
#define LMEMSTART		(BASE_OFFSET | 0x1E720000)
#define HW_TRAPPINGS    (BASE_OFFSET | 0x1E6E2070)


#define AST_FMC_BASE			(BASE_OFFSET | 0x1E620000)
#define AST_FMC_CS0_BASE		0x70000000 /* CS0 */
#define AST_FMC_CS1_BASE		0x28000000 /* CS1 */
#define AST_FMC_CS2_BASE		0x2a000000 /* CS2 */

#define CONFIG_FMC_CS			1
#define FLASH_UNKNOWN			0xFFFF	/* unknown flash type*/
#define CONFIG_AST_SPI_NOR    	1/* AST SPI NOR Flash */
#define CONFIG_FMC_CS                   1
#define CONFIG_SYS_MAX_FLASH_BANKS      (CONFIG_FMC_CS)
#define CONFIG_SYS_MAX_FLASH_SECT       (8192)          /* max number of sectors on one chip */


#endif /*__PILOT_H__*/
