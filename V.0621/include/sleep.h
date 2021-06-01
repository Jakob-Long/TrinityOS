///////////////////////////////////////////
// Module name: sleep.h                  //
//                                       //
// Date created: 03/03/21                //
// Author      : Jakob Long              //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////

#ifndef SLEEP_H
#define SLEEP_H

void sleep(int timer) {
    while(1) {
        timer--;
        if ( timer <= 0 ) {
            break;
        }
        asm volatile("nop");
    }
}

#endif