#pragma once

#include "file_list.h"
#include "ReadFile.h"

// This is a test module using the TrinityOS
// module subsystem that works with the temporary
// file system (TFS) and creates a new file. :^)

// Create file
static int RandomNumber;
static int FileIndex = 0;

char FileNumber;
char FileName[];

char RandomNumberChar;
char NumberName[];

void createNewFile() {
    RandomNumber = random();
    RandomNumberChar = IntToString(RandomNumber);
    NumberName[0] = RandomNumberChar;

    newline();
    printk(NumberName);

    FileNumber = IntToString(FileIndex);
    FileName[0] = FileNumber;

    file_table[FileIndex].name = FileName;
	file_table[FileIndex].contents = "Hello, World!";

    FileIndex++;

    // If current file name in the file index is the same as the file name
    // in the previous index, change the new file name to be different. 
    if ( file_table[FileIndex].name == file_table[FileIndex--].name ) 
        FileIndex++; // jump to current file
        
}

// Read file
void readNewFile() {
    read_file(FileName);
}