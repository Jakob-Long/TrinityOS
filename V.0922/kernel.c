#include "drivers/KeyboardDriver/keyboard.h"
#include "drivers/DisplayDriver/vga.h"
#include "drivers/DisplayDriver/windowManager.h"

#include "sys/textMode.h"
#include "sys/lock.h"
//#include "sys/desktop2.h"

#include "boot/boot.h"

#include "lib/LibC/sleep.h"
//#include "lib/LibPython/python.h"
//#include "lib/LibC/strcopy.h"

// VGA functions for modules or other .c files

isMenuOpen = 1;

void draw_window_K(char *text, char *title) {
	drawWindow(text, title);
}

void clearC(int color) {
	clear_screen2(color);
}

void newlineK() {
	newline();
}

void printK(char *usr) {
	printk(usr);
}

void bootScreen() {
	// Load boot screen, load/initiate modules, and load desktop
	bootld();
	module_init();
	main("desktop1");
}

void textMode() {
	textModeRun();
}

void main(char *selectDesktop) {
	clear_screen2(0);

	//char *test = strcopy("hi", "hello");
	//printK(test);

	if (selectDesktop == "desktop1"){
		desktop();
		disable_cursor();
		init_idt();
		kb_init();
		enable_interrupts();
	}
	// Christmas theme
	else if (selectDesktop == "desktop2") {
		desktopChristmas();
		disable_cursor();
		init_idt_christmas();
		kb_init();
		enable_interrupts();
	}
	// Finish main execution, but don't halt the CPU. Same as `jmp $` in assembly
	while(1);
}
