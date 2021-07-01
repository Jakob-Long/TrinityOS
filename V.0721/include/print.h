///////////////////////////////////////////
// Module name: print.h                  //
//                                       //
// Date created: 02/08/21                //
// Author:       Jakob Long              //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2023.//
///////////////////////////////////////////

#ifndef PRINT_H
#define PRINT_H

#include "panic.h"
#include "sleep.h"
#include "error.h"

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES
#define CHARS_PER_LINE 79

unsigned int current_loc = 0;

// Function prorotypes
//void print(char *, char[]);
void printInt(int);
void printERR(char *);
void cls(void);
void newLine(void);
void printGUI(char *);

static unsigned int i = 0;
static unsigned int j = 0;

// Global vars for the window manager
int strLen = 0;
int tLen = 0;
//char *title;

// Print function for the boot file
void bootPrint(char *usr) {
    char *video = (unsigned char *)0xB8000;
    const char *str = usr;

    int n = 0;
	while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
		video[current_loc++] = 0x0F; // 0x6F
    }
}

// Print function for the loading bar
void ldbar(char *usr) {
    char *video = (unsigned char *)0xB8000;
    const char *str = usr;

    int n = 0;
	/*while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
		video[current_loc++] = 0xFF; // 0x66
    }*/
    video[current_loc++] = 179;
    video[current_loc++] = 0xf0;
}

// Clear screen for boot
void clsBoot(void) {
    char *video = (unsigned char *)0xB8000;
    // unsigned int j = 0;

    j = 0;
    i = 0;
    current_loc = 0;

	while(j < SCREENSIZE) {
		video[j] = ' ';
		video[j+1] = 0x00; // 0x66
		j = j + 2;
	}
    return;
}

// All text that is printed is put into a window.
void print(char *usr, char *title) {
    char *video = (unsigned char *)0xB8000;
    const char *str = usr;
    strLen =0;
    tLen = 0;

    // Get length of string.
    while ( str[strLen] != '\0' ) {
        strLen++;
    }

    int center = (CHARS_PER_LINE - strLen) / 2;

    // Print title bar
    unsigned int n = 0;

    for ( int s=0; s<center; s++ ) {
        video[current_loc++] = ' '; // 178
        video[current_loc++] = 0x99; // 0xf9
    }

    tBar(title, str);
    newline();

    for ( int c=0; c<center; c++ ) {
        // Code to center window
        video[current_loc++] = ' '; // 178
        video[current_loc++] = 0x99; // 0xf9
    }
    
    // Print text in the window body
    n = 0;
	while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
		video[current_loc++] = 0x8F; // 0x80
    }

    // Create window height.
    for ( int i=0; i<5; i++ ) {
        newline();
        width(strLen);
    }

    return;
}

// Create title bar
void tBar(char *title, char *str) {
    // Account for if title is unknown
    if ( title[0] != '\0' ) {
         // Get length of title
        while ( title[tLen] != '\0' ) {
            tLen++;
        }

        // I need to check strLen and see if it is odd. If it is, make the title one char more
        if ( strLen % 2 != 0) {
            //title[tLen] = "A";
        }
    }

    /*else {
        title = "Window Manager";

        if ( strLen % 2 != 0) {
            title = "Window Manager ";
        }

        // Get length of title
        while ( title[tLen] != '\0' ) {
            tLen++;
        }
    }*/
    
    unsigned int n = 0;

    // Get length of string
    while ( str[strLen] != '\0' ) {
        strLen++;
    }

    // Check if strLen is less than tLen
    if ( strLen < tLen ) {
        //ERR("MINIMAL_TXT_EXCEPTION"); // Call kernel panic until bug is fixed
        errorPop();
    }

    // Check if strLen is greater than CHARS_PER_LINE
    if ( strLen > CHARS_PER_LINE ) {
        //ERR("MAX_TXT_EXCEPTION"); // Call kernel panic until bug is fixed
        errorPop();
    }

    // If strLen is odd, than it is one space shorts
    int space = (strLen - tLen) / 2;

    // Write title bar
    for (int s=0; s<space; s++ ) {
        video[current_loc++] = 205;
		video[current_loc++] = 0xFF;
    }

    //video[current_loc++] = 179;
    //video[current_loc++] = 0xF0;

    while ( title[n] != '\0' ) {
		video[current_loc++] = title[n++];
		video[current_loc++] = 0xF0; // 0x70
    }

    //video[current_loc++] = 179;
    //video[current_loc++] = 0xF0;

    for (int s=0; s<space; s++ ) {
        video[current_loc++] = 205;
		video[current_loc++] = 0xFF;
    }

    // Draw buttons
    current_loc -= 4;
    video[current_loc++] = 0x18; // 0x11
    video[current_loc++] = 0xCF; // 0x4f;
    video[current_loc++] = 0x19; // 0x16 0x18
    video[current_loc++] = 0xCF; // 0x4f;
    //video[current_loc++] = 254; // 0x09
    //video[current_loc++] = 0xcf; // 0x4f;
}

// Create window width.
void width(int w) {
    char *video = (unsigned char *)0xB8000;
    int space = (CHARS_PER_LINE - strLen) / 2;

    for ( int c=0; c<space; c++ ) {
        // Code to center window
        video[current_loc++] = ' '; // 178
        video[current_loc++] = 0x99; // 0x88
    }

    for ( int i=0; i<w; i++ ) {
        printGUI(" ");
    }
}

// The only reason I made ths function was so that the kernel panic text was white with a blue background ;)
void printERR(char *usr) {
    const char *str = usr;
    char *video = (unsigned char *)0xB8000;

    unsigned int i = 0;
    while ( str[i]  != '\0' ) {
        video[current_loc++] = str[i++];
        video[current_loc++] = 0x1F; // 0x04 = red
    }
    return;
}

// The only reason I made ths function was so that the kernel panic title was white with a white highlight ;)
void bsodTitle(char *usr) {
    const char *str = usr;
    char *video = (unsigned char *)0xB8000;

    unsigned int i = 0;
    while ( str[i]  != '\0' ) {
        video[current_loc++] = str[i++];
        video[current_loc++] = 0xF1; // 0x04 = red
    }
    return;
}

// TODO: Add suppport for ints to print ASCII characters
void OUT(char *usr) {
    char *video = (unsigned char *)0xB8000;

    unsigned int i = 0;
    while ( usr[i]  != '\0' ) {
        video[current_loc++] = usr[i++];
        video[current_loc++] = 0x9F; // 0x04 = red
    }
}

void newline(void)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void cls(void) {
    char *video = (unsigned char *)0xB8000;
    // unsigned int j = 0;

    j = 0;
    i = 0;
    current_loc = 0;

	while(j < SCREENSIZE) {
		video[j] = 178;    // 178
		video[j+1] = 0x99; // 0xf9
		j = j + 2;
	}
    return;
}

// When an error occurs, this clears the screen to a blue color
void BSOD(void) {
    char *video = (unsigned char *)0xB8000;
    // unsigned int j = 0;

    j = 0;
    i = 0;
    current_loc = 0;

	while(j < SCREENSIZE) {
		video[j] = ' ';
		video[j+1] = 0x11;
		j = j + 2;
	}
    return;
}

// I made this instead of using regular print so that I can fill int the box with color instead of text.
void printGUI(char *box) {
    const char *str = box;
    char *video = (unsigned char *)0xB8000;

    unsigned int i = 0;
	while ( str[i] != '\0' ) {
		video[current_loc++] = str[i++];
		video[current_loc++] = 0x88; // Gray fill. 0x70
    }
    return;
}

// A special function meant only to write the taskbar at the top of the screen.
// This is a test to see if I can control what I draw (basically practice for the final UI)
void printTaskbar(char *txt) {
    // I have to get the length of the string, and subtrack that by 79(how many chars can fit on one line)
    // and then write the text, followed by that many spaces.
    const char *str = " ";
    char *video = (unsigned char *)0xB8000;

    int len = 0;

    while ( txt[len] != '\0' ) {
        len++;
    }

    int space = CHARS_PER_LINE - len; // Get the ammount of empty chars left
    int middle = (CHARS_PER_LINE - len) / 2; // Get the position of the middle of the line.

    unsigned int i = 0;
    for (int s=0; s<=middle; s++ ) {
        video[current_loc++] = 205; // 205
        video[current_loc++] = 0x33; // Orange blanks 0x66
    }
	while ( txt[i] != '\0' ) {
		video[current_loc++] = txt[i++];
		video[current_loc++] = 0x30; // Orange background, white text
    }
    for ( int s=0; s<=middle; s++ ) {
        video[current_loc++] = 205;
        video[current_loc++] = 0x33; // Orange blanks
    }

    return;
}

void tskbar(char *title) {
    // Taskbar code
    printTaskbar(title);
}

#endif
