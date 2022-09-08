//////////////////////////////////////////
// Module name: tools.h                 //
//                                      //
// Date created: 04/29/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

#ifndef TOOLS_H
#define TOOLS_H

//#include "../include/print.h"
//#include "../drivers/vgaAlign/align.h"
//#include "../include/error.h"
//#include "../../module/module_list.h"

//int len;
char conv;
char strConv[5];
unsigned long int next = 1;

int random(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next * 65536) % 32768;
}

char IntToString(int usr) {
    char IntToChar;
    char CharToStr[2];

    IntToChar = usr + '0';
    //CharToStr[0] = IntToChar;

    return IntToChar;
}

// TODO: Move this function to FileManager group
void input(char *input_text) {
    print_to_screen(input_text, 4, 0);
    print_to_screen("          ", 4, 0);

    disable_cursor();
	init_idt_login();
	kb_init();
	enable_interrupts();
}

void clearstr(char *str) {
    for(int i=0; i<stringLength(str); i++) str[i] = 0;
}

int strcompk(const char *a, const char *b) {
    while (*a && *a == *b) { ++a; ++b; };
    return (int)(unsigned char)(*a) - (int)(unsigned char)(*b);
}

int stringLength(char *usr) {
    unsigned int count = 0;

    while ( *usr != '\0' ) {
        count++;
        usr++;
    }
    return count;
}

int alignTextCenter(char *usr) {
    int m = 79;
    int _len = 0;

    _len = stringLength(usr);
    
    int al = (m - _len) / 2;

    return al;
}

#endif