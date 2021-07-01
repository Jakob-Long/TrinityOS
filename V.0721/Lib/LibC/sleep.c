///////////////////////////////////////////
// Library name: sleep.h                 //
//                                       //
// Date created: 03/03/21                //
// Author      : Jakob Long              //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////

#include "sleep.h"

void sleepC(int timer) {
    while(1) {
        timer--;
        if ( timer <= 0 ) {
            break;
        }
        asm volatile("nop");
    }
}

void HLT() {
    asm volatile("hlt");
}