//////////////////////////////////////////
// Module name: checkModule.h           //
//                                      //
// Date created: 07/07/22               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2024 //
//////////////////////////////////////////

#pragma once

#include "keyboard.h"
#include "../DisplayDriver/vga.h"
#include "../../module/module_list.h"
#include "../../kernel/ReadModule.h"
#include "../../lib/LibC/tools.h"

// What I want to do is dump the names of the modules 
// from the struct into an array, and loop through the
// new array to see if the user typed one of the module
// names.

char *ModuleNames[] = {"", "", "", ""};

extern int SizeOfArray;
extern char *command_buffer;
extern int command_len;

void addToArray() {
    for (int i=0; i<SizeOfArray; i++) {
        ModuleNames[i] = fn_table[i].name;
	}
}
 
void checkModule() {
    addToArray(); // Add module names from struct to array (simplifies everything I think)
}