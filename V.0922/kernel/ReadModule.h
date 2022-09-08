////////////////////////////////////////////
// File name: ReadModule.c                //
//                                        //
// Author:       Jakob Long.              //
// Date created: 12/17/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#pragma once

#include "../lib/LibC/tools.h"
#include "../module/module_list.h"

void (*call_function(char *fn_name))() {
    int i;
    for (int i=0; i < 15; ++i) { // Limit to only 15 modules for now
        if (!strcompk(fn_name, fn_table[i].name)) {
            return fn_table[i].fn;
        }
    }
}