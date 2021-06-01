///////////////////////////////////////////
// Module name: boot.h                   //
//                                       //
// Date created: 03/08/21                //
// Author      : Jakob Long              //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////

#ifndef BOOT_H
#define BOOT_H

#include "../include/print.h"
#include "../OS/OS.h"
#include "../include/sleep.h"

char *txt = "TrinityOS Version 0621";
char *txt2 = "Loading OS. This might take a minute...";

void bootld() {
    // I made a loop in case somone wants this to repeat more than once.
    for ( int i=0; i<1; i++ ) {
        loop();
        clsBoot();
    }

    // Load main OS
    sleep(0x01FFFFFF);
    cls();
    _BOOT();
    //bootld();
}

void loop() {
    clsBoot();

    int txtLen = 0;
    int txtLen2 = 0;
    int chars = 79;

    // Center boot text
    while ( txt[txtLen] != '0' ) {
        txtLen++;
    }

    while ( txt2[txtLen2] != '\0' ) {
        txtLen2++;
    }

    int space = (chars - txtLen) / 2;
    int space2 = (chars - txtLen2) / 2;

    for (int i=0; i<space; i++) {
        bootPrint(" ");
    }
    bootPrint(txt);
    newline();

    for ( int j=0; j<space2; j++ ) {
        bootPrint(" ");
    }
    bootPrint(txt2);

    for (int i=0; i<23; i++) {
        newline();
    }

    for ( int i=0; i<=79; i++ ) {
        ldbar("|");
        sleep(0x01FFFFF);
    }
}

#endif
