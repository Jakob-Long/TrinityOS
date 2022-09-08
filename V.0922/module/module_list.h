#pragma once

// Include the file that contains your module's code
#include "taya.h"
#include "test_module.h"
#include "aboutTrinityOS.h"
#include "tree.h"
#include "../drivers/FileManager/createNewFile.h"
#include "../boot/boot.h"

// Do not worry about this part, this just 
// lays out the module structure
typedef struct fn_table_entry {
    char *name;
    void (*fn)();
} fn_table_entry_t;




// This is where you write add the names and functions of your modules
// Limit of only 4 modules for now :/
fn_table_entry_t fn_table[] = {
    {"taya", taya}, // {"Module name", functon}
    {"demo", test_module},
    {"about", aboutOS},
    {"tree", tree},
};