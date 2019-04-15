MEMORY
        {
        vectors : ORIGIN = 0x5E720000, LENGTH = 0x0029FF 
        ram     : ORIGIN = 0x5E722A00, LENGTH = 0x00A6FF    }
 
SECTIONS
{
        .vectors :
        {
        *(.vectors)
        } > vectors

        startup :
        {
			start.o	(startup)
        *(startup)
        } > vectors

        .text :
        {
        *(.text)
        } > vectors

        .data :
        {
        *(.data)
        } > ram

        .rodata :
        {
        *(.rodata)
        } > ram

        .rodata.str1.1 :
        {
        *(.rodata)
        } > ram

		. = ALIGN(4);
		__bss_start = .;
        .bss :
        {
        *(.bss)
        } > ram
		__bss_end = .;

        .stack :
        {
        *(.stack)
        _src_addr = .;
        } > ram
}

