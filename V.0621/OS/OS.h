//////////////////////////////////////////
// Module name: OS.h                    //
//                                      //
// Date created: 02/09/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

#ifndef OS_H
#define OS_H

// Kernel include files
#include "../include/print.h"
#include "../include/panic.h" 
#include "../include/GUI.h"
#include "../include/sleep.h"
#include "../drivers/vgaAlign/align.h"

#include "../dev/tools.h"
#include "../dev/tostr.h"

// System program include files
#include "../SYS/app.h"
#include "../SYS/trm.h"
#include "../SYS/help.h"

// Programs include files
#include "../program_files_x86/brandon.h"

// OS include files
#include "dsktp.h"

void _BOOT(void);

static int _VERIFY = 0;
const int _MAX = 3;

char conv2;
char strConv2[50];

void _BOOT(void) {
    // Loop through the programs constantly

    while(1) {
        cls();
        LD_DSKTP();
        sleep(0x03FFFFFF);
        _help();
        newline();
        sleep(0x03FFFFFF);
        _help();
        sleep(0x07FFFFFF);
    }
}

#endif