#pragma once

// ----- Pre-processor constants -----
#define ROWS 25
#define COLS 80
#define VIDMEM 0xb8000
// IDT_SIZE: Specific to x86 architecture
#define IDT_SIZE 256
// KERNEL_CODE_SEGMENT_OFFSET: the first segment after the null segment in gdt.asm
#define KERNEL_CODE_SEGMENT_OFFSET 0x8
// 32-bit Interrupt gate: 0x8E
// ( P=1, DPL=00b, S=0, type=1110b => type_attr=1000_1110b=0x8E) (thanks osdev.org)
#define IDT_INTERRUPT_GATE_32BIT 0x8e
// IO Ports for PICs
#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1
// IO Ports for Keyboard
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define COMMAND_BUFFER_SIZE 100
#define PROMPT "Type help for a list of commands, or type desktop to return to the desktop."
#define PROMPT_LENGTH 18

#define bool int
#define false 0
#define true 1

// ----- Includes -----
#include "keyboard_map.h"
#include "../DisplayDriver/vga.h"
#include "../../boot/boot.h"
#include "../../desktop.h"
#include "../../sys/desktop2.h"
#include "../../sys/StartMenu.h"
#include "../../lib/LibC/panic.h"
#include "../../module/module_list.h"
#include "../../kernel/ReadModule.h"
#include "../FileManager/ReadFile.h" 
#include "../FileManager/file_list.h" 

// ----- External functions -----
extern void print_char_with_asm(char c, int row, int col);
extern void load_gdt();
extern void keyboard_handler();
extern void keyboard_handler2();
extern void keyboard_handler3();
extern void keyboard_handler_login();
extern void keyboard_handler_christmas();
extern char ioport_in(unsigned short port);
extern void ioport_out(unsigned short port, unsigned char data);
extern void load_idt(unsigned int* idt_address);
extern void enable_interrupts();
extern char *module_name;
extern char *demo_string;
extern char array[10][100];
extern void (*functions[3])(void);
extern int module_name_length;
extern int module2_name_length;
extern int module3_name_length;

// ----- Structs -----
struct IDT_pointer {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));
struct IDT_entry {
	unsigned short offset_lowerbits; // 16 bits
	unsigned short selector; // 16 bits
	unsigned char zero; // 8 bits
	unsigned char type_attr; // 8 bits
	unsigned short offset_upperbits; // 16 bits
} __attribute__((packed));

// ----- Global variables -----
struct IDT_entry IDT[IDT_SIZE]; // This is our entire IDT. Room for 256 interrupts
int cursor_row = 0;
int cursor_col = 11;
int cursor_col2 = 0;

//char command_buffer[COMMAND_BUFFER_SIZE];
char *command_buffer;
char *command_buffer_file;
int command_len = 0;
int command_len_file = 0;

void disable_cursor() {
	ioport_out(0x3D4, 0x0A);
	ioport_out(0x3D5, 0x20);
}

bool streq(char* string1, int str1len, char* string2, int str2len) {
	if (str1len != str2len) return false;
	for (int i = 0; i < str1len; i++) {
		if (string1[i] != string2[i]) return false;
	}
	return true;
}

void println(char* string, int len) {
	print(string, len);
	cursor_row++;
}

void print(char* string, int len) {
	for (int i = 0; i < len; i++) {
		printchar(string[i], cursor_row, cursor_col);
		cursor_col++;
	}
}

void printchar(char c, int row, int col) {
	// OFFSET = (ROW * 80) + COL
	char* offset = (char*) (VIDMEM + 2*((row * COLS) + col));
	//char* offset = (unsigned char *)0xB8000;
	*offset = c;
}

void clear_screen() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printchar(' ', i, j);
		}
	}
}

void init_idt_christmas() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int offset = (unsigned int)keyboard_handler_christmas;
	
	IDT[0x21].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (offset & 0xFFFF0000) >> 16;
	
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);

	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);

	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);

	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);

	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned int) &IDT;
	load_idt(&idt_ptr);
}


void init_idt_login() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int offset = (unsigned int)keyboard_handler_login;
	
	IDT[0x21].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (offset & 0xFFFF0000) >> 16;
	
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);

	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);

	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);

	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);

	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned int) &IDT;
	load_idt(&idt_ptr);
}

void init_idt3() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int offset = (unsigned int)keyboard_handler3;
	
	IDT[0x21].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (offset & 0xFFFF0000) >> 16;
	
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);

	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);

	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);

	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);

	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned int) &IDT;
	load_idt(&idt_ptr);
}

void init_idt2() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int offset = (unsigned int)keyboard_handler2;
	// Populate the first entry of the IDT
	// TODO why 0x21 and not 0x0?
	// My guess: 0x0 to 0x2 are reserved for CPU, so we use the first avail
	IDT[0x21].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (offset & 0xFFFF0000) >> 16;
	// Program the PICs - Programmable Interrupt Controllers
	// Background:
		// In modern architectures, the PIC is not a separate chip.
		// It is emulated in the CPU for backwards compatability.
		// The APIC (Advanced Programmable Interrupt Controller)
		// is the new version of the PIC that is integrated into the CPU.
		// Default vector offset for PIC is 8
		// This maps IRQ0 to interrupt 8, IRQ1 to interrupt 9, etc.
		// This is a problem. The CPU reserves the first 32 interrupts for
		// CPU exceptions such as divide by 0, etc.
		// In programming the PICs, we move this offset to 0x2 (32) so that
		// we can handle all interrupts coming to the PICs without overlapping
		// with any CPU exceptions.

	// Send ICWs - Initialization Command Words
	// PIC1: IO Port 0x20 (command), 0xA0 (data)
	// PIC2: IO Port 0x21 (command), 0xA1 (data)
	// ICW1: Initialization command
	// Send a fixed value of 0x11 to each PIC to tell it to expect ICW2-4
	// Restart PIC1
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);
	// ICW2: Vector Offset (this is what we are fixing)
	// Start PIC1 at 32 (0x20 in hex) (IRQ0=0x20, ..., IRQ7=0x27)
	// Start PIC2 right after, at 40 (0x28 in hex)
	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);
	// ICW3: Cascading (how master/slave PICs are wired/daisy chained)
	// Tell PIC1 there is a slave PIC at IRQ2 (why 4? don't ask me - https://wiki.osdev.org/8259_PIC)
	// Tell PIC2 "its cascade identity" - again, I'm shaky on this concept. More resources in notes
	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);
	// ICW4: "Gives additional information about the environemnt"
	// See notes for some potential values
	// We are using 8086/8088 (MCS-80/85) mode
	// Not sure if that's relevant, but there it is.
	// Other modes appear to be special slave/master configurations (see wiki)
	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);
	// Voila! PICs are initialized

	// Mask all interrupts (why? not entirely sure)
	// 0xff is 16 bits that are all 1.
	// This masks each of the 16 interrupts for that PIC.
	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	// Last but not least, we fill out the IDT descriptor
	// and load it into the IDTR register of the CPU,
	// which is all we need to do to make it active.
	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned int) &IDT;
	// Now load this IDT
	load_idt(&idt_ptr);
}

void init_idt() {
	// Get the address of the keyboard_handler code in kernel.asm as a number
	unsigned int offset = (unsigned int)keyboard_handler;
	// Populate the first entry of the IDT
	// TODO why 0x21 and not 0x0?
	// My guess: 0x0 to 0x2 are reserved for CPU, so we use the first avail
	IDT[0x21].offset_lowerbits = offset & 0x0000FFFF; // lower 16 bits
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = IDT_INTERRUPT_GATE_32BIT;
	IDT[0x21].offset_upperbits = (offset & 0xFFFF0000) >> 16;
	// Program the PICs - Programmable Interrupt Controllers
	// Background:
		// In modern architectures, the PIC is not a separate chip.
		// It is emulated in the CPU for backwards compatability.
		// The APIC (Advanced Programmable Interrupt Controller)
		// is the new version of the PIC that is integrated into the CPU.
		// Default vector offset for PIC is 8
		// This maps IRQ0 to interrupt 8, IRQ1 to interrupt 9, etc.
		// This is a problem. The CPU reserves the first 32 interrupts for
		// CPU exceptions such as divide by 0, etc.
		// In programming the PICs, we move this offset to 0x2 (32) so that
		// we can handle all interrupts coming to the PICs without overlapping
		// with any CPU exceptions.

	// Send ICWs - Initialization Command Words
	// PIC1: IO Port 0x20 (command), 0xA0 (data)
	// PIC2: IO Port 0x21 (command), 0xA1 (data)
	// ICW1: Initialization command
	// Send a fixed value of 0x11 to each PIC to tell it to expect ICW2-4
	// Restart PIC1
	ioport_out(PIC1_COMMAND_PORT, 0x11);
	ioport_out(PIC2_COMMAND_PORT, 0x11);
	// ICW2: Vector Offset (this is what we are fixing)
	// Start PIC1 at 32 (0x20 in hex) (IRQ0=0x20, ..., IRQ7=0x27)
	// Start PIC2 right after, at 40 (0x28 in hex)
	ioport_out(PIC1_DATA_PORT, 0x20);
	ioport_out(PIC2_DATA_PORT, 0x28);
	// ICW3: Cascading (how master/slave PICs are wired/daisy chained)
	// Tell PIC1 there is a slave PIC at IRQ2 (why 4? don't ask me - https://wiki.osdev.org/8259_PIC)
	// Tell PIC2 "its cascade identity" - again, I'm shaky on this concept. More resources in notes
	ioport_out(PIC1_DATA_PORT, 0x0);
	ioport_out(PIC2_DATA_PORT, 0x0);
	// ICW4: "Gives additional information about the environemnt"
	// See notes for some potential values
	// We are using 8086/8088 (MCS-80/85) mode
	// Not sure if that's relevant, but there it is.
	// Other modes appear to be special slave/master configurations (see wiki)
	ioport_out(PIC1_DATA_PORT, 0x1);
	ioport_out(PIC2_DATA_PORT, 0x1);
	// Voila! PICs are initialized

	// Mask all interrupts (why? not entirely sure)
	// 0xff is 16 bits that are all 1.
	// This masks each of the 16 interrupts for that PIC.
	ioport_out(PIC1_DATA_PORT, 0xff);
	ioport_out(PIC2_DATA_PORT, 0xff);

	// Last but not least, we fill out the IDT descriptor
	// and load it into the IDTR register of the CPU,
	// which is all we need to do to make it active.
	struct IDT_pointer idt_ptr;
	idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
	idt_ptr.base = (unsigned int) &IDT;
	// Now load this IDT
	load_idt(&idt_ptr);
}

void kb_init() {
	// 0xFD = 1111 1101 in binary. enables only IRQ1
	// Why IRQ1? Remember, IRQ0 exists, it's 0-based
	ioport_out(PIC1_DATA_PORT, 0xFD);
}

void handle_keyboard_interrupt_login() {
	// Write end of interrupt (EOI)
	
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)

	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode == 28) {
			int file_count = 3;
			newline();

			// Store input in new file
			file_table[file_count++].name = "new";
			file_table[3].contents = command_buffer_file;
			//file_count++;

			newline();
			printk("Creating file...");
			sleep(0x01FFFFFF);
			textMode();

			//cursor_col = 11;
			//command_buffer_file = "                       ";
		}else if (keycode == 14) { // Backspace
			if (cursor_col2 <= 0) cursor_col2 = 1;
			print_char_with_asm(' ', cursor_row, --cursor_col2);

			if (cursor_col > PROMPT_LENGTH) {
				print_char_with_asm(' ', cursor_row, --cursor_col);
			}
		}else {
			if (command_len_file >= COMMAND_BUFFER_SIZE) return;
			command_buffer_file[command_len_file++] = keyboard_map[keycode];
			printchar(keyboard_map[keycode], cursor_row, cursor_col++);
			//print_to_screen(keyboard_map[keycode], 0, 7);
			if (cursor_col2 >= COLS) {
				cursor_col2 = cursor_col2 % COLS;
				cursor_row++;
			}
			//desktop();
			return;
		}
	}
}

void handle_keyboard_interrupt3() {
	// Write end of interrupt (EOI)
	
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)
	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode == 28) {
			// ENTER : Newline
			if (cursor_row >= 22) cursor_row = 0;
			cursor_row++;
			cursor_col2 = 0;
		}else if (keycode == 14) { // Backspace
			if (cursor_col2 <= 0) cursor_col2 = 1;
			print_char_with_asm(' ', cursor_row, --cursor_col2);

			if (cursor_col > PROMPT_LENGTH) {
				print_char_with_asm(' ', cursor_row, --cursor_col);
			}
		}else if (keycode == 15) { // Tab
			cursor_row = 0;
			textMode();
		}else if (keycode == 29) { // Ctrl
			cursor_row = 0;
			cursor_col2 = 0;
			textEditor();
		}else if (keycode == 42) { // Left Shift
			if (cursor_row <= 1) cursor_row = 1;
			cursor_row--;
			cursor_col2 = 0;
			//command_buffer[command_len--] = " ";
		} else {
			if (command_len >= COMMAND_BUFFER_SIZE) return;
			command_buffer[command_len++] = keyboard_map[keycode];
			printchar(keyboard_map[keycode], cursor_row, cursor_col2++);
			//print_to_screen(keyboard_map[keycode], 0, 7);
			if (cursor_col2 >= COLS) {
				cursor_col2 = cursor_col2 % COLS;
				cursor_row++;
			}
			//desktop();
			return;
		}
	}
}

extern int sizeofk;
void handle_keyboard_interrupt2() {
	// Write end of interrupt (EOI)
	
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)
	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode == 28) {
			// ENTER : 
			
			cursor_col = 11;
			//call_function("demo")();
			//read_file("new file");

			int x;
			char *y = "hi";

			// Handle commands
			if (streq(command_buffer, command_len, "ls", 2)) {
				clear_screen2(0);
				// clearstr(command_buffer); For whatever reason, this line of code messes up how th window gets drawn on screen.
				textMode();
				newline();
				newline();
				print_to_screen("Filesystem not yet implemented.", 4, 0);
				newline();
				
				if ( isWindowOpen == 1 ) {
					printk("Window Closed");
				}
			} else if (streq(command_buffer, command_len, "file", 4)) {
				command_buffer = "\0";
				cursor_col = 0;
				clear_screen2(0);
				input("File Name: ");
				cursor_col = 11;
			} else if (streq(command_buffer, command_len, "create file", 11)) {
				command_buffer = "\0";
				cursor_col = 0;
				textMode();
				call_function("create")();
				call_function("read")();
			} else if (streq(command_buffer, command_len, "list file", 9)) {
				command_buffer = "\0";
				command_buffer_file = "\0";
				textMode();
				newline();

				// Check if new file is created yet. If not
				// then we create it as an empty file.
				if (file_table[3].name != "new file") {
					if (file_table[3].name != "empty") {
						file_table[3].name = "empty";
						file_table[3].contents = "empty";
					}
				}

				for(int i=0; i<4; i++) {
					newline();
					printk(file_table[i].name);
					printk(" : ");
					printk(file_table[i].contents);
				}
			}  else if (streq(command_buffer, command_len, "delete file", 11)) {
				command_buffer = "\0";
				command_buffer_file = "\0";
				textMode();

				// Check if new file is created yet. If not
				// then we create it as an empty file.
				if (file_table[3].name != "new file") {
					if (file_table[3].name != "empty") {
						file_table[3].name = "empty";
						file_table[3].contents = "empty";
					}
				}

				// If file is already deleted or does not exist, 
				// return an error. If not, then delete the file.
				if (file_table[3].name == "empty") {
					newline();
					newline();
					print_to_screen("File not found or is empty.", 4, 0);
				} else {
					newline();
					newline();
					print_to_screen("File ", 4, 0);
					printk("'");
					printk(file_table[3].name);
					printk("'");
					print_to_screen(" deleted.", 4, 0);

					file_table[3].name = "empty";
					file_table[3].contents = "empty";	
				}
			} else if (streq(command_buffer, command_len, "help", 4)) {
				clear_screen2(0);
				textMode();
				newline();
				newline();
				print_to_screen("Commands:", 4, 0);
				newline();
				print_to_screen("desktop", 2, 0);
				newline();
				print_to_screen("desktop2", 2, 0);
				newline();
				print_to_screen("ls", 2, 0);
				newline();
				print_to_screen("edit", 2, 0);
				newline();
				print_to_screen("create file", 2, 0);
				newline();
				print_to_screen("delete file", 2, 0);
				newline();
				print_to_screen("list file", 2, 0);
				newline();
				print_to_screen("modules", 2, 0);
				newline();
				
				// Possibly remove to create space for other commands. It
				// will still be located under the 'modules' command.
				/*for (int i=0; i<5; i++) {
					print_to_screen(fn_table[i].name, 6, 0);
					newline();
				}*/

				print_to_screen("reboot", 2, 0);
				newline();
				print_to_screen("help", 2, 0);
				newline();
				print_to_screen("help desktop", 2, 0);
			} else if (streq(command_buffer, command_len, "help desktop", 12)) {
				clear_screen2(0);
				textMode();
				newline();
				newline();
				print_to_screen("At your desktop:", 4, 0);
				newline();
				print_to_screen("Press R to reboot", 2, 0);
				newline();
				print_to_screen("Press X to close window", 2, 0);
				newline();
				print_to_screen("Press C to show window", 2, 0);
				newline();
				print_to_screen("Press S to show Quick Menu", 2, 0);
				newline();
				print_to_screen("Press B for a test BSOD", 2, 0);
				newline();
				print_to_screen("Press T for text mode", 2, 0);
				newline();
				print_to_screen("Press 1 for desktop mode 1", 2, 0);
				newline();
				print_to_screen("Press 2 for desktop mode 2", 2, 0);
				newline();
				print_to_screen("You need to access your desktop to try these. Type 'desktop'", 4, 0);
			} else if (streq(command_buffer, command_len, "reboot", 6)) {
				command_buffer[0] = 0;
				bootScreen();
				cursor_row = 0;
			} else if (streq(command_buffer, command_len, "edit", 4)) {
				command_buffer = "\0";
				textMode();
				textEditor();
				cursor_row = 0;
			} /*else if (streq(command_buffer, command_len, "taya", 4)) {
				textMode();
				newline();
				//printk(command_buffer);
				call_function("taya");
				//clearstr(command_buffer);
			}*/ else if (streq(command_buffer, command_len, "modules", 7)) {
				clear_screen2(0);
				textMode();
				newline();
				newline();
				//print_to_screen(module_name, 4, 0);
				int q = 0;
				/*while (q<3) {
					print_to_screen(array[q], 4, 0);
					newline();
					q++;
				}*/
				for (int i=0; i<5; i++) {
					print_to_screen(fn_table[i].name, 6, 0);
					newline();
				}

				newline();
				newline();
				print_to_screen("NOTE: Type the name of the module to run it.", 3, 0);
			} else if (streq(command_buffer, command_len, array[0], module_name_length)) {
				module_init();
				sleep(0x10FFFFFF);
				textMode();
			} else if (streq(command_buffer, command_len, array[1], module2_name_length)) {
				//module_init();
				clear_screen2(0);
				textMode();
				newline();
				newline();
				//print_to_screen(functions[0], 4, 0);
				print_to_screen("hello", 4, 0);
				//functions[0];
			} else if (streq(command_buffer, command_len, array[2], module3_name_length)) {
				//module_init();
				clear_screen2(0);
				textMode();
				newline();
				newline();
				print_to_screen("hello2", 4, 0);
			} else if (streq(command_buffer, command_len, "desktop", 7)) {
				textMode();
				//command_buffer = "\0";
				command_buffer[0] = 0;
				main("desktop1");
				cursor_row = 0;
			}  else if (streq(command_buffer, command_len, "desktop2", 8)) {
				textMode();
				command_buffer[0] = 0;
				main("desktop2");
				cursor_row = 0;
			} else if (streq(command_buffer, command_len, " ", 1)) {
				textMode();
				cursor_row = 0;
			} else if (command_len < 1) {
				// do nothing
			} else {
				textMode();
				/*newline();
				newline();
				print_to_screen("Command not found: ", 4, 0);
				print_to_screen(command_buffer, 4, 0);
				newline();*/
			}
			command_len = 0;
			//print_prompt();
			//desktop();
		}else if (keycode == 14) {
			// BACKSPACE: Move back one unless on prompt
			/*if (cursor_col > PROMPT_LENGTH) {
				//print_char_with_asm(' ', cursor_row, --cursor_col);
				cursor_col--;
				print_to_screen("A", 0, 2);
			}*/
			back();
			//command_buffer[command_len--] = " ";
		} else {
			if (command_len >= COMMAND_BUFFER_SIZE) return;
			command_buffer[command_len++] = keyboard_map[keycode];
			printchar(keyboard_map[keycode], cursor_row, cursor_col++);
			//print_to_screen(keyboard_map[keycode], 0, 7);
			if (cursor_col >= COLS) {
				cursor_col = cursor_col % COLS;
				cursor_row++;
			}
			//desktop();
			return;
		}
	}
}

void handle_keyboard_interrupt_christmas() {
	// Write end of interrupt (EOI)
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)
	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode == 28) {
			// ENTER : do nothing as we don't need this key at this stage
		}else if (keycode == 19) { // 'r'
			clear_screen2(0);
			bootScreen();
		}else if (keycode == 48) { // 'b'
			//clear_screen2(0);
			ERR("TEST_OS_CRASH");
			main();
		}else if (keycode == 20) { // 't'
			textMode();
		}else if (keycode == 45) { // 'x'
			closeWindowChristmas();
		}else if (keycode == 46) { // 'c'
			desktopChristmas();
		}else if (keycode == 2) { // '1'
			main("desktop1");
		}else if (keycode == 31) { // 's'
			DrawStartMenu2();
		}else if (keycode == 14) {
			// BACKSPACE: Move back one unless on prompt
			if (cursor_col > PROMPT_LENGTH) {
				//print_char_with_asm(' ', cursor_row, --cursor_col);
				cursor_col--;
				print_to_screen(" ", 0, 0);
			}
		} else {
			// nothing
		}
	}
}

void handle_keyboard_interrupt() {
	// Write end of interrupt (EOI)
	ioport_out(PIC1_COMMAND_PORT, 0x20);

	unsigned char status = ioport_in(KEYBOARD_STATUS_PORT);
	// Lowest bit of status will be set if buffer not empty
	// (thanks mkeykernel)
	if (status & 0x1) {
		char keycode = ioport_in(KEYBOARD_DATA_PORT);
		if (keycode < 0 || keycode >= 128) return;
		if (keycode == 28) {
			// ENTER : do nothing as we don't need this key at this stage
		}else if (keycode == 19) { // 'r'
			clear_screen2(0);
			bootScreen();
		}else if (keycode == 48) { // 'b'
			//clear_screen2(0);
			ERR("TEST_OS_CRASH");
			main();
		}else if (keycode == 20) { // 't'
			textMode();
		}else if (keycode == 45) { // 'x'
			closeWindow();
		}else if (keycode == 46) { // 'c'
			desktop();
		}else if (keycode == 3) { // '2'
			main("desktop2");
		}else if (keycode == 31) { // 's'
			DrawStartMenu();
		}else if (keycode == 14) {
			// BACKSPACE: Move back one unless on prompt
			if (cursor_col > PROMPT_LENGTH) {
				//print_char_with_asm(' ', cursor_row, --cursor_col);
				cursor_col--;
				print_to_screen(" ", 0, 0);
			}
		} else {
			/*if (command_len >= COMMAND_BUFFER_SIZE) return;
			command_buffer[command_len++] = keyboard_map[keycode];
			//printchar(keyboard_map[keycode], cursor_row, cursor_col++);
			print_to_screen(keyboard_map[keycode], 0, 7);
			if (cursor_col >= COLS) {
				cursor_col = cursor_col % COLS;
				cursor_row++;
			}
			//desktop();
			return;*/
		}
	}
}

void print_prompt() {
	cursor_col = 11;
	//print(PROMPT, PROMPT_LENGTH);
	print_to_screen(PROMPT, 3, 0);
	//cursor_col = PROMPT_LENGTH;
}

void print_message() {
	// Fill the screen with 'x'
	int i, j;
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			if (j < 4) {
				print_char_with_asm('*',j,i);
			} else {
				print_char_with_asm(' ',j,i);
			}
		}
	}
	print("-PKOS-", 6);
	cursor_row = 4;
}

// ----- Entry point -----

