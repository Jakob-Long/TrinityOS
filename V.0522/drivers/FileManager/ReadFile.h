////////////////////////////////////////////
// File name: ReadModule.c                //
//                                        //
// Author:       Jakob Long.              //
// Date created: 01/30/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////


#pragma once

#include "../../lib/LibC/tools.h"
#include "../DisplayDriver/vga.h"
#include "file_list.h"

void read_file(char *file_name) {
    int i;

    /*if (file_name != file_table[0].name) {
        newline();
        printk("File not found");
    }*/
    
    for (int i=0; i < 15; ++i) { // Limit to only 15 files for now
        if (!strcompk(file_name, file_table[i].name)) {
            newline();
            printk(file_table[i].contents);
        }
    }
}