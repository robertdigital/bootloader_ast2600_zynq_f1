ELF=bootloader
ELFREADER   = $(PWD)/elfreader

S_OBJS    = $(patsubst %.s,%.o,$(wildcard *.s))
C_OBJS    = $(patsubst %.c,%.o,$(wildcard *.c))
ASM_OBJS    = $(patsubst %.S,%.o,$(wildcard *.S))
build_obj = $(C_OBJS) $(S_OBJS) $(ASM_OBJS)
CROSS_COMPILE=/elx/sandbox/pilot_fw/pilot/ashok/x-tool-linux-4-9-armv7a-472-hf/bin/arm-aspeed-linux-gnueabi-
CC        = $(CROSS_COMPILE)gcc
AS        = $(CROSS_COMPILE)as
LD        = $(CROSS_COMPILE)ld
AR        = $(CROSS_COMPILE)ar
LIST      = $(CROSS_COMPILE)objdump
OBJCOPY   = $(CROSS_COMPILE)objcopy
ARM_IS    = armv7-a
INCLUDE = include/
CFLAGS += -D__ASSEMBLY__
ASFLAGS += -mfpu=softfpa
#ASFLAGS += -mfpu=vfpv4-d16
GCCLIB=/elx/sandbox/pilot_fw/pilot/ashok/x-tool-linux-4-9-armv7a-472-hf/lib/gcc/arm-aspeed-linux-gnueabi/4.7.2
LDLIB=--library-path=$(GCCLIB) --library=gcc
LDOPT     = -T $(ELF).ld -Map $(ELF).map
CCOPT = -I $(INCLUDE) -g  -Os -fno-common -ffixed-r8 -mfloat-abi=hard -mfpu=vfpv4-d16 -gdwarf-2 -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -mcpu=cortex-a7 -Wall -Wstrict-prototypes -fno-stack-protector $(CFLAGS)

#CCOPT = -I $(INCLUDE) -g  -Os -fno-common -ffixed-r8 -msoft-float  -gdwarf-2 -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=$(ARM_IS) -Wall -Wstrict-prototypes -fno-stack-protector $(CFLAGS)
ASOPT     = -I $(INCLUDE) -march=$(ARM_IS) $(ASFLAGS)

export  ASFLAGS CFLAGS

all:clean message $(ELF) $(ELF).bin $(ELF).D $(ELF).lod

message:
	@echo "Building $(ELF) image"
	@echo $(build_obj)

%.o: %.c
	$(CC) $(CCOPT) -c $< -o $@

%.o: %.s
	$(CC) $(CCOPT) -c $< -o $@

%.o: %.S
	$(AS) $(ASOPT) $< -o $@
	
$(ELF): $(build_obj)
	echo "ELF=" $(ELF)
	echo $(LDOPT)
	$(LD) $(LDOPT) $(build_obj) -o $@ $(LDLIB)

$(ELF).bin: $(ELF)
	$(OBJCOPY) --gap-fill=0xff -O binary $< $@

$(ELF).D: $(ELF)
	$(LIST) -D $< > $@


$(ELF).lod: $(ELF).bin
	$(ELFREADER) --fmt=skbinsize --start-address=$(ELF_START_ADDR) --objname=$< > $@

clean:
	rm -f *.o $(ELF) $(ELF).bin $(ELF).D $(ELF).map $(ELF).lod


