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
#include "../include/GUI.h"
#include "../include/sleep.h"

// System program include files
#include "../SYS/clock.h"

// OS include files
#include "dsktp.h"

void _BOOT(void); // Function prototype (not even sure if I need this)
void _BOOT(void) {
    // Load desktop, then pause and loop 
    // through the programs constantly

    cls();
    LD_DSKTP();
    sleep(0x03FFFFFF);

    while(1) {
        cls();
        LD_DSKTP();
        _CLOCK();
    }
}

#endif