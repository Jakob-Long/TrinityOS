#pragma once

#include "taya.h"
#include "test_module.h"
#include "../drivers/FileManager/createNewFile.h"

typedef struct fn_table_entry {
    char *name;
    void (*fn)();
} fn_table_entry_t;




// This is where you write add the names and functions of your modules
fn_table_entry_t fn_table[] = {
    {"taya", taya}, // Module name, functon
    {"name", /*function*/},
    {"demo", test_module},
    {"create", createNewFile},
    {"read", readNewFile}
};