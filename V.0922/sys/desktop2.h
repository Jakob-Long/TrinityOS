////////////////////////////////////////////
// File name: kernel.c                    //
//                                        //
// Author:       Jakob Long.              //
// Date created: 02/08/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#include "../drivers/DisplayDriver/windowManager.h"
#include "../drivers/KeyboardDriver/keyboard.h"
#include "../boot/boot.h"
#include "../lib/LibC/sleep.h"
#include "StartMenu.h"

//#include "include/panic.h"
extern void main();

int isWindowOpen2; // 0 = Window Open, 1 = Window Closed
extern int isMenuOpen2;

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
    isWindowOpen2 = 1;

    if ( isMenuOpen2 == 0 ) {
        DrawStartMenu2();
        taskbarCloseChristmas(23);
    } else {
        clear_screen2(0); // 9
        taskbarCloseChristmas(23);
    }
}

void desktopChristmas() {
    //isWindowOpen2 = 0;

    if ( isWindowOpen2 == 1 ) {
        closeWindowChristmas();
    } else {
        clear_screen2(0);
        if ( isMenuOpen2 == 0 ) {
            sleep(0x9FFFFFFF);
            DrawStartMenu2();
            drawWindowChristmas("       Press T for text mode       ", "            Quick Start           ");
            taskbarChristmas(14);
        } /*else if ( isMenuOpen == 0 ) {
            sleep(0x9FFFFFFF);
            DrawStartMenu2();
            drawWindowChristmas("       Press T for text mode       ", "            Quick Start           ");
            taskbarChristmas(14);
        }*/ else {
            sleep(0x9FFFFFFF);
            clear_screen2(0); // 9
            drawWindowChristmas("       Press T for text mode       ", "            Quick Start           ");
            taskbarChristmas(14);
        }
    }
}