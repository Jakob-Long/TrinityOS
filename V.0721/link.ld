OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS 
{
    . = 0x100000;

    .text : {
	 *(.text)
	 *(.multiboot)
     }

    .data : { *(.data)}
    .bss  : { *(.bss) }
}
