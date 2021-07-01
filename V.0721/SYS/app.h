///////////////////////////////////////////
// App name: app.h                       //
//                                       //
// Date made: 04/01/21                   //
// Author:    Jakob Long                 //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////

// NOTE: I could not finish keyboard support in time for the April (0421) update.
// Keyboard support should be introduced in the May (0521) update.

#ifndef APP_H
#define APP_H

#include "../include/print.h"
// #include "../keyboard/keyboard.h"

void test() {
    print(" Shhh, lets not leak our hard work ;)  ", "Developers Note");
    //print(" Shhh, lets not leak our hard work ;) ");
    newline();
    // test_input();
    // print("hi");
}

#endif
