////////////////////////////////////////////
// File name: kernel.c                    //
//                                        //
// Author:       Jakob Long.              //
// Date created: 02/08/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#include "drivers/DisplayDriver/windowManager.h"
#include "boot/boot.h"
#include "lib/LibC/sleep.h"
#include "drivers/KeyboardDriver/keyboard.h"
//#include "include/panic.h"
extern void main();
void taskbar(int space) {
    for (int i=0; i<space; i++) {
        newline();
    }

    for ( int i=0; i<160; i++ ) {
        print_to_screen(" ", 8, 6); // Print the bottom bar/taskbar
    }
}

void closeWindow() {
    clear_screen2(0); // 9
    taskbar(23);
}

void desktop() {
    sleep(0x9FFFFFFF);
    clear_screen2(0); // 9
    //drawWindow("       Version  1121       ", "   TrinityOS Development   ");
    drawWindow("       Press T for text mode       ", "            Quick Start            ");
    taskbar(14);
    /*while(1){
        sleep(0x9FFFFFFF);
        clear_screen2(0); // 9
        drawWindow("       Version  1121       ", "   TrinityOS Development   ");
        taskbar();
        sleep(0x09FFFFFF);
        sleep(0x09FFFFFF);
        sleep(0x09FFFFFF);
        clear_screen2(0);
        main();

    }*/
}

int kmain() {
    bootld(1);
}
