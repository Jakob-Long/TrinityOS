#pragma once

#include "file_list.h"
#include "ReadFile.h"

// This is a test module using the TrinityOS
// module subsystem that works with the temporary
// file system (TFS) and creates a new file. :^)

// Create file
void createNewFile() {
    //clear_screen2(0);
    //char *testFile = input("File Name: ");
    //char yummy[] = "oopss";
    file_table[3].name = "new file";
	file_table[3].contents = "Hello, World!";
}

// Read file
void readNewFile() {
    read_file("new file");
}