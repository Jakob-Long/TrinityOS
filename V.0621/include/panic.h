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

#include "print.h"
#include "../OS/OS.h"
#include "../boot/boot.h"
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

    BSOD();
    newline();

    // Center "ERROR"
    for ( int i=0; i<center; i++ ) {
        printERR(" ");
    }
    bsodTitle(" ERROR ");
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
        printERR(" ");
    }
    printERR(" The following system error has occured: ");
    printERR(err);


    // Get length of help string and calculate center
    while ( help[helpLen] != '\0' ) {
        helpLen++;
    }

    int hCenter = (CHARS - helpLen) / 2;

    // Print help information
    for ( int i=0; i<hCenter; i++ ) {
        printERR(" ");
    }
    printERR(help);

    // Pause, and then reboot to the desktop.
    //__asm__("hlt");
    sleep(0x10FFFFFF);
    bootld();
}

#endif