///////////////////////////////////////////
// App name: lock.h                      //
//                                       //
// Date made: 12/12/21                   //
// Author:    Jakob Long                 //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////


#pragma once


#include "../drivers/DisplayDriver/vga.h"
#include "../drivers/KeyboardDriver/keyboard.h"


extern int cursor_row;
extern int cursor_col2;


void lockScreen() {
    clear_screen2(0);

    cursor_row++;
    cursor_col2 = 0;
    if (cursor_row >= 2) cursor_row = 1;    

    print_to_screen("Login:", 0, 7);
    newline();
    for (int i=0; i<79; i++) {
        print_to_screen(" ", 7, 0);
    }

    disable_cursor();
    init_idt_login();
    kb_init();
    enable_interrupts();
    while(1);
}