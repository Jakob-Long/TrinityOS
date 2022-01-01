/////////////////////////////////////////
// Module name: panic.h                //
//                                     //
// Date created: 02/09/21              //
// Author:       Jakob Long            //
//                                     //
// Copyright (c) Jakob Long, 2021-2023 //
/////////////////////////////////////////

#ifndef PANIC_H
#define PANIC_H

#define CHARS 79

#include "../../drivers/DisplayDriver/vga.h"
#include "../../boot/boot.h"
#include "sleep.h"
void ERR(char *);

int center = (CHARS - 5) / 2;
int strErrLen = 0;
int errLen = 0;
int helpLen = 0;

char *str = "The following system error has occured: ";
char *help = "We will restart your computer shortly...";

void ERR(char *err) {
    strErrLen = 0;
    errLen = 0;
    helpLen = 0;

    clear_screen2(1);
    newline();

    // Center "ERROR"
    for ( int i=0; i<center; i++ ) {
        print_to_screen(" ", 1, 1);
    }
    print_to_screen(" ERROR ", 1, 7);
    newline();
    newline();

    // Get length of string and error, and add them together. Take the sum, and use it to center error text
    while ( str[strErrLen] != '\0' ) {
        strErrLen++;
    }
    while ( err[errLen] != '\0' ) {
        errLen++;
    }

    int sum = strErrLen + errLen;
    int errCenter = (CHARS - sum) / 2;

    for ( int i=0; i<errCenter; i++ ) {
        print_to_screen(" ", 1, 1);
    }
    print_to_screen(" The following system error has occured ", 7, 1);
    print_to_screen(err, 7, 1);


    // Get length of help string and calculate center
    while ( help[helpLen] != '\0' ) {
        helpLen++;
    }

    int hCenter = (76 - helpLen);

    // Print help information
    for ( int i=0; i<hCenter; i++ ) {
        print_to_screen(" ", 1, 1);
    }
    print_to_screen(help, 7, 1);

    // Pause, and then reboot to the desktop.
    sleep(0x10FFFFFF);
    sleep(0x10FFFFFF);
    sleep(0x10FFFFFF);
    sleep(0x10FFFFFF);
    bootScreen();
}

#endif