////////////////////////////////////////////
// Module name: module.c                  //
//                                        //
// Author:       Jakob Long.              //
// Date created: 12/21/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

// Test module 
#include "module.h"

extern char array[10][100];
extern char *copytest;

void modi() {
    newlineK();
    printK("DEMO");
}

void module_init() {
    clearC(0);
    printK(" MERRY CHRISTMAS 2021! ");
    newlineK();
    initiate("mod"); // Store module name so it can be run later :^)

    module_start();
}