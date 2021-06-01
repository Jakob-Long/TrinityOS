////////////////////////////////////////////
// File name: kernel.c                    //
//                                        //
// Author:       Jakob Long.              //
// Date created: 02/08/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

//Kernel header files
#include "include/print.h"

// Boot files
#include "boot/boot.h"

int kmain();
extern void UserLand();

int kmain() {
    UserLand();
    bootld();
}