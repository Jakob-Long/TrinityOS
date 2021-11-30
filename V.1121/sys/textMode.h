#pragma once

#include "../drivers/DisplayDriver/vga.h"
#include "../drivers/KeyboardDriver/keyboard.h"

// Code to run TrinityOS in text/command 

extern int cursor_col2;
void textEditor() {
    clear_screen2(0);

    cursor_col2 = 0;
    int screenCalc = 1920;
    float centerEditorTitle = (79 - 10) / 2;

    for(int i=0; i<screenCalc; i++) {
        print_to_screen(" ", 1, 2);
    }

    for(int i=0; i<centerEditorTitle; i++) {
        print_to_screen(" ", 6, 6);
    }
    print_to_screen(" Text Edit ", 7, 1);
    for(int i=-1; i<centerEditorTitle; i++) {
        print_to_screen(" ", 6, 6);
    }

    disable_cursor();
    init_idt3();
    kb_init();
    enable_interrupts();

}

void textModeRun() {
    //clear_screen2(0);
	//print_to_screen("TrinityOS> ", 2, 0);
	//print_to_screen("Add typing support :^)", 4, 0);
    clear_screen2(0);
    print_to_screen("TrinityOS> ", 6, 0);
    print_to_screen("                                                              ", 6, 0);

    disable_cursor();
    init_idt2();
    kb_init();
    enable_interrupts();

    newline();
    newline();
    print_prompt();
    newline();
    print_to_screen("Type 'help desktop' to learn how to use the desktop environment.", 3, 0);
    newline();
    newline();
    print_to_screen("NOTE: You have to press enter before you type a command to ensure it runs", 3, 0);
}