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

//#include "../include/print.h"
//#include "../security/activate.h"
#include "../lib/LibC/sleep.h"
#include "../drivers/DisplayDriver/vga.h"
//#include "../security/defender.h"
//#include "../OS/OS.h"

char *txt = "TrinityOS Version 1121";
char *txt2 = "Loading OS. This might take a minute...";
int activationForSecurity = 07032021; // Variable for if TrinityOS is activated or not.

extern void desktop();
void loop() {
    clear_screen2(0);

    int txtLen = 0;
    int txtLen2 = 0;
    int chars = 79;

    // Center boot text
    while ( txt[txtLen] != '\0' ) {
        txtLen++;
    }

    while ( txt2[txtLen2] != '\0' ) {
        txtLen2++;
    }

    int space = (chars - txtLen) / 2;
    int space2 = (chars - txtLen2) / 2;

    for (int i=0; i<space; i++) {
        print_to_screen(" ", 0, 0);
    }
    print_to_screen(txt, 7, 0);
    newline();

    for ( int j=0; j<space2; j++ ) {
        print_to_screen(" ", 0, 0);
    }
    print_to_screen(txt2, 7, 0);

    for (int i=0; i<23; i++) {
        newline();
    }

    for ( int i=0; i<=79; i++ ) {
        print_to_screen("|", 7, 7);
        sleep(0x01FFFFF);
    }
}

void bootld() {
    // I made a loop in case somone wants this to repeat more than once.
    //appCheck(callCheck, activationForSecurity);

    clear_screen2(0);
    loop();
    clear_screen2(0);

    // Load main OS
    // sleep(0x01FFFFFF);
    //desktop();
    //activateTrinityOS(activationForSecurity);
}

#endif
