////////////////////////////////////////////
// File name: ModuleList.c                //
//                                        //
// Author:       Jakob Long.              //
// Date created: 12/21/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////


// This file stores the name and name length of the 
// module that was loaded into the kernel during boot.


// If no module ID is passed via 'initiate()', display this
char *module_name = " No Module ID Found ";
int module_name_length = 0;
int module2_name_length = 0;
int module3_name_length = 0;

char array[10][100] = {"NULL", "NULL", "NULL"}; // Support a max of 3 modules
char *copytest;

static int i = 0;

void test() {
    printK("DEMO");
}
void (*functions[3])(void) = {&test};

void initiate(char *module) {
    module_name = module;

    copytest = strcopy(module_name, array[i]);

    i++;
    if (i>2) {
        if (array[i] == array[i--]) i--;
    }

    while ( array[0][module_name_length] != '\0' ) {
        module_name_length++;
    }

    while ( array[1][module2_name_length] != '\0' ) {
        module2_name_length++;
    }

    while ( array[2][module3_name_length] != '\0' ) {
        module3_name_length++;
    }
}