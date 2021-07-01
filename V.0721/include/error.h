//////////////////////////////////////////
// Module name: error.h                 //
//                                      //
// Date created: 04/19/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

#ifndef ERROR_H
#define ERROR_H

#include "print.h"
#include "../boot/boot.h"
#include "../OS/dsktp.h"

void errorPop() {
    // Code to pop up an error box
    cls();

    for ( int i=0; i<5; i++ ) {
        newline();
    }

    print(" Window Manager has encountered an error ", "Error");

    sleep(0x10FFFFFF);
    bootld(0721);
}

#endif