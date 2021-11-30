////////////////////////////////////////////
// Driver name: vga.h                     //
//                                        //
// Date created: 08/14/21                 //
// Author:       Jakob Long               //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

#pragma once

#include "vga.h"
#include "../../lib/LibC/tools.h"

void drawWindowTitle(char *text, char *title) {
    // Figure out math for title bar
    int titleLength = stringLength(title);
    int textLength = stringLength(text);
    float centerWindowTitle = (textLength - titleLength) / 2;

    // Write title bar
    for ( int i=0; i<centerWindowTitle; i++ ) {
        print_to_screen(" ", 6, 6);
    }

    print_to_screen(title, 0, 6);

    for ( int i=0; i<centerWindowTitle; i++ ) {
        print_to_screen(" ", 6, 6);
    }
}

void centerWindow(int num) {
    for ( int i=0; i<num; i++ ) {
        print_to_screen(" ", 0, 0); // 9
    }
}

void drawHeight(int widthOfHeight) {
    for ( int i=0; i<widthOfHeight; i++ ) {
        print_to_screen(" ", 7, 7); // 8
    }
}

void drawWindow(char *windowContents, char *windowTitle) {
    int windowLength = stringLength(windowContents);
    newline();
    newline();
    newline();

    int centerWindowInt = alignTextCenter(windowContents);
    centerWindow(centerWindowInt);

    drawWindowTitle(windowContents, windowTitle);
    newline();

    centerWindow(centerWindowInt);
    print_to_screen(windowContents, 7, 7); // 8
    newline();
    centerWindow(centerWindowInt);
    print_to_screen(windowContents, 0, 7);

    for ( int i=0; i<4; i++ ) {
        newline();
        centerWindow(centerWindowInt);
        drawHeight(windowLength); // Length of strong
    }
}