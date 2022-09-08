////////////////////////////////////////////
// File name: kernel.c                    //
//                                        //
// Author:       Jakob Long.              //
// Date created: 02/08/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#pragma once

#include "drivers/DisplayDriver/windowManager.h"
#include "drivers/KeyboardDriver/keyboard.h"
#include "boot/boot.h"
#include "lib/LibC/sleep.h"
#include "lib/LibC/panic.h"
#include "sys/StartMenu.h"

//#include "include/panic.h"
extern void main();

int isWindowOpen;  // 0 = Window Open, 1 = Window Closed
extern int isMenuOpen;

void taskbarClose(int space) {
    for (int i=0; i<space; i++) {
        newline();
    }
    
    print_to_screen(" Quick Start ", 0, 6);

    int CenterStartMenu = ((80 - 5) / 2) - 13;

    for ( int i=0; i<CenterStartMenu; i++) {
        print_to_screen(" ", 6, 6);
    }
    print_to_screen("Start", 0, 6);

    for ( int i=0; i<160; i++ ) {
        print_to_screen(" ", 8, 6); // Print the bottom bar/taskbar
    }
}

void taskbar(int space) {
    for (int i=0; i<space; i++) {
        newline();
    }

    int CenterStartMenu = (80 - 5) / 2;

    for ( int i=0; i<CenterStartMenu; i++) {
        print_to_screen(" ", 6, 6);
    }
    print_to_screen("Start", 0, 6);

    for ( int i=0; i<160; i++ ) {
        print_to_screen(" ", 8, 6); // Print the bottom bar/taskbar
    }
}

void closeWindow() {
    isWindowOpen = 1; // Window Closed

    if ( isMenuOpen == 0 ) {
        DrawStartMenu();
        taskbarClose(23);
    } else {
        clear_screen2(0); // 9
        taskbarClose(23);
    }
}

void desktop() {
    //if ( isWindowOpen == 1) isWindowOpen = 0; // If window is not closed, set it as open
    if ( isWindowOpen == 1) { // If window is closed, draw desktop with closed window
        closeWindow();
    } else {
        if ( isMenuOpen == 0 ) {
            sleep(0x9FFFFFFF);
            DrawStartMenu();
            drawWindow("       Press T for text mode       ", "            Quick Start           ");
            taskbar(14);
        }/* else if ( isMenuOpen2 == 0 ) {
            sleep(0x9FFFFFFF);
            DrawStartMenu();
            drawWindow("       Press T for text mode       ", "            Quick Start           ");
            taskbar(14);
        }*/ else {
            sleep(0x9FFFFFFF);
            clear_screen2(0); // 9
            drawWindow("       Press T for text mode       ", "            Quick Start           ");
            taskbar(14);
        }
    }

    disable_cursor();
	init_idt();
	kb_init();
	enable_interrupts();
}