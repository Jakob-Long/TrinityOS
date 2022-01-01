///////////////////////////////////////////
// Module name : terminal.h (aka trm.h)  //
//                                       //
// Date created: 03/03/21                //
// Author      : Jakob Long              //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////

#ifndef TRM_H
#define TRM_H

#include "../include/print.h"

void TRM_BEGIN() {
    newline();
    print(" #> OpenOS Terminal ", "Terminal");
    //print("hi");
}

#endif