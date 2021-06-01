OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS 
{
    . = 2M;

    .text : {
	 *(.text)
	 *(.multiboot)
     }

    .data : { *(.data)}
    .bss  : { *(.bss) }
}
