////////////////////////////////////////////
// File name: kernel.c                    //
//                                        //
// Author:       Jakob Long.              //
// Date created: 02/08/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#include "../drivers/DisplayDriver/windowManager.h"
#include "../boot/boot.h"
#include "../lib/LibC/sleep.h"
#include "../drivers/KeyboardDriver/keyboard.h"
//#include "include/panic.h"
extern void main();

void taskbarChristmas(int space) {
    for (int i=0; i<space; i++) {
        newline();
    }

    int CenterStartMenu = (80 - 5) / 2;

    for ( int i=0; i<CenterStartMenu; i++) {
        print_to_screen(" ", 4, 4);
    }
    print_to_screen("Start", 0, 4);

    for ( int i=0; i<160; i++ ) {
        print_to_screen(" ", 8, 4); // Print the bottom bar/taskbar
    }
}

void taskbarCloseChristmas(int space) {
    for (int i=0; i<space; i++) {
        newline();
    }
    
    print_to_screen(" Quick Start ", 0, 4);

    int CenterStartMenu = ((80 - 5) / 2) - 13;

    for ( int i=0; i<CenterStartMenu; i++) {
        print_to_screen(" ", 4, 4);
    }
    print_to_screen("Start", 0, 4);

    for ( int i=0; i<160; i++ ) {
        print_to_screen(" ", 8, 4); // Print the bottom bar/taskbar
    }
}

void closeWindowChristmas() {
    isWindowOpen = 1;

    clear_screen2(0); // 9
    taskbarCloseChristmas(23);
}

void desktopChristmas() {
    isWindowOpen = 0;

    sleep(0x9FFFFFFF);
    clear_screen2(0); // 9
    drawWindowChristmas("       Press T for text mode       ", "            Quick Start           ");
    taskbarChristmas(14);
}