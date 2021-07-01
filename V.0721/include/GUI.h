////////////////////////////////////////////
// Module name: GUI.h                     //
//                                        //
// Date created: 02/16/2021               //
// Author:       Jakob Long               //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#ifndef GUI_H
#define GUI_H

#include "print.h"

char *video = (unsigned char *)0xB8000;
unsigned int currentLoc = 0;

void _BOX(char *str, int H) {
    // Get length of string.
    int len = 0;
    while ( str[len] != 0 ) {
        len++;
    }

    // We need to print the string first, the draw the width, then the height.
    unsigned int i = 0;
	while ( str[i] != '\0' ) {
		video[currentLoc++] = str[i++];
		video[currentLoc++] = 0x70; // 0x087 
    }
}

#endif