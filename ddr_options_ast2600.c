//#include "pilot_II.h"
#define MMCR_PASSWORD       0xFC600309

#define CONFIG_ZYNQ_F1	1

#ifdef CONFIG_ZYNQ_F1
#define MMC_BASE_ADR        0x5E6E0000
#define UART_BASE           0x5E784000
#else
#define MMC_BASE_ADR        0x1E6E0000
#define UART_BASE           0x1E784000
#endif

#define DDR3               1 //RR temp define
#define DRAM_2GB           1
#define FPGA_MMC           1
#define sg25E              1
#define DEBUG_PRINTS       1
#define FPGA_DUT 1
#define HW_ENV  1
#include "ddr_options_ast2600.h"


#if defined ECC
   #define  SCRA_PAT         0x00000280;
#else 
   #define  SCRA_PAT         0x00000000;
#endif

typedef unsigned int tU32;
typedef volatile unsigned int tVU32;
typedef volatile unsigned int * tPVU32;
typedef unsigned char tU8;

inline void WRITE_REG32(tU32 addr, tU32 data)
{
	*(volatile unsigned int *)addr=data;
}
#define READ_REG32(addr)            (*(volatile unsigned int *)addr)

extern void wait_for_previous_print(void);
extern void write_simulator(tU32 CMD);
#if 0
#if !defined (HW_ENV)
void wait_for_previous_print(void)
{
   while(*(tPVU32)(DDR_WRITE_SIMULATOR_FLAG)==0xa5a5a5a5 );
}

void write_simulator(tU32 CMD)
{
   tU32 temp;
   wait_for_previous_print();
   *(tPVU32)(DDR_WRITE_SIMULATOR_OPCODE)=CMD;
   *(tPVU32)(DDR_WRITE_SIMULATOR_FLAG)=0xa5a5a5a5;
   temp =  *(tPVU32)(DDR_WRITE_SIMULATOR_OPCODE);
   temp =  *(tPVU32)(DDR_WRITE_SIMULATOR_FLAG);
}
#endif
#endif

#define SERIAL_LSR_THRE     0x20    /* THR Empty */
#define SERIAL_THR          0x00
#define SERIAL_LSR          0x14

static void putc (const char c)
{
#ifdef DEBUG_PRINTS
	volatile unsigned int status=0;

	do
	{
		status = *(volatile unsigned char *)(UART_BASE+SERIAL_LSR);
	}
	while (!((status & SERIAL_LSR_THRE)==SERIAL_LSR_THRE) );

	*(volatile unsigned char *)(UART_BASE+SERIAL_THR) = c;
#endif
}

void print_reg(unsigned int reg)
{
	int i =0, shift = 24;
	int val;

	for(i=0;i<8;i++)
	{
		shift = 28 - (i *4);
		val = (reg >> shift);
		val = val & 0xF;
		if(val == 0)
			putc('0');
		if(val == 1)
			putc('1');
		if(val == 2)
			putc('2');
		if(val == 3)
			putc('3');
		if(val == 4)
			putc('4');
		if(val == 5)
			putc('5');
		if(val == 6)
			putc('6');
		if(val == 7)
			putc('7');
		if(val == 8)
			putc('8');
		if(val == 9)
			putc('9');
		if(val == 0xa)
			putc('a');
		if(val == 0xb)
			putc('b');
		if(val == 0xc)
			putc('c');
		if(val == 0xd)
			putc('d');
		if(val == 0xE)
			putc('e');
		if(val == 0xf)
			putc('f');
	}
	putc('\n');
	putc('\r');
}

void init_common(tU8 input){
   tU32  tmpd,dllv;  //RR; variables not used
   WRITE_REG32(MMC_BASE_ADR+0x34,0x000000C0);      // PWRCTL, disable reset and disable REQ
   WRITE_REG32(MMC_BASE_ADR+0x38,0x00100000);      // ARBCTL
   WRITE_REG32(MMC_BASE_ADR+0x3C,0xFFBBFFF4);      // LATMASK
   WRITE_REG32(MMC_BASE_ADR+0x40,0x44444444);      // GNTLEN0
   WRITE_REG32(MMC_BASE_ADR+0x44,0x44444444);      // GNTLEN1
   WRITE_REG32(MMC_BASE_ADR+0x48,0x44444444);      // GNTLEN2
   WRITE_REG32(MMC_BASE_ADR+0x4C,0x44444444);      // GNTLEN3
   WRITE_REG32(MMC_BASE_ADR+0x50,0x80000000);      // ECC
#if defined DRAM_16G
   WRITE_REG32(MMC_BASE_ADR+0x54,0x3FF00000);      // ECC
#elif DRAM_8G
   WRITE_REG32(MMC_BASE_ADR+0x54,0x1FF00000);      // ECC
#elif DRAM_4G
   WRITE_REG32(MMC_BASE_ADR+0x54,0x0FF00000);      // ECC
#else
   WRITE_REG32(MMC_BASE_ADR+0x54,0x07F00000);      // ECC
#endif
   WRITE_REG32(MMC_BASE_ADR+0x50,0x00000000);      // ECC
   WRITE_REG32(MMC_BASE_ADR+0x70,0x00000000);      // TESTC
   WRITE_REG32(MMC_BASE_ADR+0x74,0x00000000);      // TESTADRS
   WRITE_REG32(MMC_BASE_ADR+0x78,0x00000000);      // TESTADRE
   WRITE_REG32(MMC_BASE_ADR+0x7C,0x00000000);      // TESTV
   WRITE_REG32(MMC_BASE_ADR+0x80,0xFFFFFFFF);      // REQENA
   WRITE_REG32(MMC_BASE_ADR+0x84,0x00000000);      // REQHIGH

   WRITE_REG32(MMC_BASE_ADR+0x10,REG_MCR10);          // ACTIME1
   WRITE_REG32(MMC_BASE_ADR+0x14,REG_MCR14);          // ACTIME2
   WRITE_REG32(MMC_BASE_ADR+0x18,REG_MCR18);          // ACTIME3
   WRITE_REG32(MMC_BASE_ADR+0x1C,REG_MCR1C);          // ACTIME4
   WRITE_REG32(MMC_BASE_ADR+0x20,REG_MCR20);          // MR0/1
   WRITE_REG32(MMC_BASE_ADR+0x24,REG_MCR24);          // MR2/3
   WRITE_REG32(MMC_BASE_ADR+0x28,REG_MCR28);          // MR4/5
   WRITE_REG32(MMC_BASE_ADR+0x2C,REG_MCR2C);          // MR6

}

void ddrinit_ast2600(void){

   tU32 ddrd;
   tU32 padr;
   tVU32 tRFC,delay,i;

    putc('\r');putc('D'); putc('D'); putc('R'); putc(' '); 
	putc('I'); putc('N'); putc('I'); putc('T'); putc('\n');putc('\r');

static unsigned int ECCdata[88] = {
0x00000000,
0x00080080,
0x00100B80,
0x58000100,
0x58084180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0x58100100,
0x58184180,
0xB8000000,
0xF8000000,
0xF8000000,
0xd898c296,
0xf4a13945,
0x2deb33a0,
0x77037d81,
0x63a440f2,
0xf8bce6e5,
0xe12c4247,
0x6b17d1f2,
0x37bf51f5,
0xcbb64068,
0x6b315ece,
0x2bce3357,
0x7c0f9e16,
0x8ee7eb4a,
0xfe1a7f9b,
0x4fe342e2,
0xFFFFFFFF,
0xFFFFFFFF,
0xFFFFFFFF,
0x00000000,
0x00000000,
0x00000000,
0x00000001,
0xFFFFFFFF
};



   WRITE_REG32(MMC_BASE_ADR+0x00,MMCR_PASSWORD);
   init_common(1);
   #if defined DDR3
      #if defined DRAM_16G
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000007);
      #elif DRAM_8G
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000006);
      #elif DRAM_4G
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000005);
      #else
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000004);
      #endif

	putc('I');

      #if defined FPGA_MMC
          WRITE_REG32(MMC_BASE_ADR+0x034,0x000000c1);
          //WRITE_REG32(MMC_BASE_ADR+0x100,0x00000026);
          WRITE_REG32(MMC_BASE_ADR+0x100,0x0000000C);
          //delay 1000ns 
          for ( i = 0 ; i< 200; i++);
      #else
      #endif

	putc('J');

      WRITE_REG32(MMC_BASE_ADR+0x0C,0x00000040);      // Enable ZQCL
          for ( i = 0 ; i< 200000; i++);
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000005);      // MODESET MR2
          for ( i = 0 ; i< 200; i++);
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000007);      // MODESET MR3
          for ( i = 0 ; i< 200; i++);
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000003);      // MODESET MR1
          for ( i = 0 ; i< 200; i++);
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000011);      // MODESET MR0 DLL_RESET
          for ( i = 0 ; i< 200; i++);
      WRITE_REG32(MMC_BASE_ADR+0x0C,0x00005D41);      // REFSET
          for ( i = 0 ; i< 200; i++);

	putc('K');
      do {
//         ddrd= READ_REG32(MMC_BASE_ADR+0x34);
         ddrd= *(tPVU32)(MMC_BASE_ADR+0x34);
      }while((ddrd & 0x70000000) != 0);
         
	putc('L');

      WRITE_REG32(MMC_BASE_ADR+0x0C,0x00105DA1);      // REFSET
      WRITE_REG32(MMC_BASE_ADR+0x34,0x000003A3);      // PWRCTL

      #if defined DRAM_16G
         tRFC = (REG_MCRFC >>24);
      #elif DRAM_8G
         tRFC = (REG_MCRFC >> 16);
      #elif DRAM_4G
         tRFC = (REG_MCRFC >> 8);
      #else
         tRFC = REG_MCRFC ;
      #endif

      ddrd  = READ_REG32(MMC_BASE_ADR+0x04);
      ddrd |= SCRA_PAT;
      WRITE_REG32(MMC_BASE_ADR+0x04,ddrd);      

      ddrd  = READ_REG32(MMC_BASE_ADR+0x14);
//	  print_reg(*(tPVU32)(0x5E6E0014));
	  ddrd  = *(volatile unsigned int *)(MMC_BASE_ADR + 0x14);
//	  print_reg(ddrd);
      ddrd  &= 0xFFFFFF00;
      ddrd  |= (tRFC&0xFF);
//	  print_reg(tRFC);
//	  print_reg(ddrd);
      WRITE_REG32(MMC_BASE_ADR+0x14,ddrd);      

      for ( i = 0 ; i< 0x300; i++);

	  putc('M');


	  for(i=0; i<10; i++)
	  {
	  	*(tPVU32)(0x80000000 + (i*4)) = i;
	  }

	  for(i=0; i<10; i++)
	  {
	  	if(i==*(tPVU32)(0x80000000 + (i*4)))
			putc('Y');
		else 
			putc('N');
	  }


#if 0
      WRITE_REG32(MMC_BASE_ADR+0xC,0xEFDDBE82);      
      for ( i = 0 ; i< 10; i++);
      WRITE_REG32(MMC_BASE_ADR+0x4,0xF6A51680);      
      for ( i = 0 ; i< 2; i++);
      WRITE_REG32(MMC_BASE_ADR+0x8,0x3F20300);      
      for ( i = 0 ; i< 2; i++);
      WRITE_REG32(MMC_BASE_ADR+0x88,0xFF000000);      
      for ( i = 0 ; i< 2; i++);
      WRITE_REG32(MMC_BASE_ADR+0x8c,0x000000FF);      
      for ( i = 0 ; i< 2; i++);
      WRITE_REG32(MMC_BASE_ADR+0xA4,0x00FFFF00);      
      for ( i = 0 ; i< 2; i++);
      WRITE_REG32(MMC_BASE_ADR+0xF0,0x2000DEEA);      
      for ( i = 0 ; i< 2; i++);
      WRITE_REG32(MMC_BASE_ADR+0x94,0x00000001);      
      for ( i = 0 ; i< 10; i++);
      WRITE_REG32(MMC_BASE_ADR+0x1c,0x00000088);      
      for ( i = 0 ; i< 10; i++);
      ddrd  = READ_REG32(MMC_BASE_ADR+0x1c);
#endif

   #else  //DDR4
      #if defined DRAM_16G
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000017);
      #elif DRAM_8G
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000016);
      #elif DRAM_4G
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000015);
      #else
         WRITE_REG32(MMC_BASE_ADR+0x04,0x00000014);
      #endif

      #if defined FPGA_MMC
          WRITE_REG32(MMC_BASE_ADR+0x034,0x000000c1);
          //WRITE_REG32(MMC_BASE_ADR+0x100,0x00000026);
          WRITE_REG32(MMC_BASE_ADR+0x100,0x0000000C);
          //delay 1000ns 
          for ( i = 0 ; i< 200; i++)
      #else
      #endif

      WRITE_REG32(MMC_BASE_ADR+0x0C,0x00000040);      // Enable ZQCL
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000007);      // MODESET MR3
      WRITE_REG32(MMC_BASE_ADR+0x30,0x0000000D);      // MODESET MR6
      WRITE_REG32(MMC_BASE_ADR+0x30,0x0000000B);      // MODESET MR5
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000009);      // MODESET MR4
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000005);      // MODESET MR2
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000003);      // MODESET MR1
      WRITE_REG32(MMC_BASE_ADR+0x30,0x00000011);      // MODESET MR0 DLL_RESET
      WRITE_REG32(MMC_BASE_ADR+0x0C,0x00005F41);      // REFSET

      do {
         ddrd= READ_REG32(MMC_BASE_ADR+0x34);
      }while((ddrd & 0x70000000) != 0);
         
      WRITE_REG32(MMC_BASE_ADR+0x0C,0x42AA5FA1);      // REFSET
      WRITE_REG32(MMC_BASE_ADR+0x34,0x000007A3);      // PWRCTL

      #if defined DRAM_16G
         tRFC = (REG_MCRFC >>24);
      #elif DRAM_8G
         tRFC = (REG_MCRFC >> 16);
      #elif DRAM_4G
         tRFC = (REG_MCRFC >> 8);
      #else
         tRFC = REG_MCRFC ;
      #endif

      ddrd  = READ_REG32(MMC_BASE_ADR+0x04);
      ddrd |= SCRA_PAT;
      WRITE_REG32(MMC_BASE_ADR+0x04,ddrd);      

      ddrd  = READ_REG32(MMC_BASE_ADR+0x14);
      ddrd  &= 0xFFFFFF00;
      ddrd  |= (tRFC&0xFF);
      WRITE_REG32(MMC_BASE_ADR+0x14,ddrd);      

/*
//============================================//
// ECC init
// DRAM_ADDR = 0x02000000 (32MB)
//============================================//
      WRITE_REG32(0x1E6E2000 , 0x1688a8a8);
      READ_REG32(0x1E6E2010);
      WRITE_REG32(0x1E6E2084 , 0x01000000);
      WRITE_REG32(0x1E6E2044 , 0x00000010);

      for (i=0; i<88; i++)
            WRITE_REG32(0x82000000+4*i, ECCdata[i]);

//============================================//
// Instruction Data (Total Size = 256 Bytes)
// DRAM_ADDR = 0x02000000 (32MB)
//============================================//

      WRITE_REG32(0x1E6FA3FC , 0x00000007);
      WRITE_REG32(0x1E6FA048 , 0x00000020);
      WRITE_REG32(0x1E6FA04C , 0x02000000);
      WRITE_REG32(0x1E6FA050 , 0x00000100);
      WRITE_REG32(0x1E6FA054 , 0x00000004);
      WRITE_REG32(0x1E6FA000 , 0x00000020);
      WRITE_REG32(0x1E6FA010 , 0x00000001);
      WRITE_REG32(0x1E6FA014 , 0x00000012);
      WRITE_REG32(0x1E6FA018 , 0x00000123);
      WRITE_REG32(0x1E6FA01C , 0x00001234);

      //polling 1E6F_A3FC[2] == 1'b1;
      do {
         ddrd= READ_REG32(0x1E6FA3FC);
      }while((ddrd & 0x00000004) == 0);


//============================================//
// Parameter Data (Total Size = 96 Bytes)
// DRAM_ADDR = 0x02000100 (32MB+256B)
//============================================//

      WRITE_REG32(0x1E6FA3FC , 0x00000007);
      WRITE_REG32(0x1E6FA04C , 0x02000100);
      WRITE_REG32(0x1E6FA050 , 0x00000600);
      WRITE_REG32(0x1E6FA000 , 0x00000040);
      WRITE_REG32(0x1E6FA010 , 0x00012345);
      WRITE_REG32(0x1E6FA014 , 0x00123456);
      WRITE_REG32(0x1E6FA018 , 0x01234567);
      WRITE_REG32(0x1E6FA01C , 0x12345678);

      //polling 1E6F_A3FC[2] == 1'b1;
      do {
         ddrd= READ_REG32(0x1E6FA3FC);
      }while((ddrd & 0x00000004) == 0);

//============================================//
// ECC Start
//============================================//
      WRITE_REG32(0x1E6FA004 , 0x00000000);
      WRITE_REG32(0x1E6FA044 , 0x00000020);
      WRITE_REG32(0x1E6FA000 , 0x00000010);
*/
   #endif //DDR4
#if 0
	  putc('\n'); putc('\r'); putc('R');putc('E');putc('G'); putc(' ');
	  putc('D');putc('U');putc('M');putc('P');putc('\n'); putc('\r');
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x00));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x04));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x08));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x0C));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x10));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x14));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x18));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x1C));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x20));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x24));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x28));
	  print_reg(*(tPVU32)(MMC_BASE_ADR+0x2C));
#endif
//  nc_printf("DRAM Init Done!");
// write_simulator(0xFFFF006C);

}
