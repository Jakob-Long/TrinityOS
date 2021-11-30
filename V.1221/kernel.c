#include "drivers/KeyboardDriver/keyboard.h"
#include "drivers/DisplayDriver/vga.h"
#include "boot/boot.h"
#include "sys/textMode.h"

void bootScreen() {
	bootld();
	main();
}

void textMode() {
	textModeRun();
}

void main() {
	clear_screen2(0);
	desktop();

	disable_cursor();
	init_idt();
	kb_init();
	enable_interrupts();

	// Finish main execution, but don't halt the CPU. Same as `jmp $` in assembly
	while(1);
}
