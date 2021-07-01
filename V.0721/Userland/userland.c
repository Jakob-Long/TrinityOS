///////////////////////////////////////////
// Module name: useland.h                //
//                                       //
// Date made: 05/20/21                   //
// Author:    Jakob Long                 //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023 //
///////////////////////////////////////////


// TODO: Work on making most Userland type files in the
// Userland directory, and transition to using .c and .cpp
// files instead of primarily using .h files.

#include "../Lib/LibTest/add.h"
#include "../Lib/LibC/types.h"

extern int sum();
void UserLand()
{
    // Provides control for all Userland files.
    int LibDemo;
    LibDemo = sum(1, 1);

    kstring demo = "h";
}