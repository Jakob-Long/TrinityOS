////////////////////////////////////////////
// File name: ReadModule.c                //
//                                        //
// Author:       Jakob Long.              //
// Date created: 01/30/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#pragma once

typedef struct file_table_entry {
    char *name;
    char *contents;
} file_table_entry_t;




// This is where you write add the file names and file contents of your files
file_table_entry_t file_table[15] = {
    {"file", "hello world :)"}, // File name, file contents
    {"file name", "file contents"},
    {"file2", "hello2"},
    //{"empty", "empty"}
};
