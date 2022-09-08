////////////////////////////////////////////
// Driver name: vga.h                     //
//                                        //
// Date created: 04/27/21                 //
// Author:       Jakob Long               //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

// New, more organized VGA driver. Old one had memory bugs
#pragma once

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES
#define CHARS_PER_LINE 79

#include "../../lib/LibC/tools.h"

// TODO: add support for letter colors (F = white, etc.)

int current_loc = 0;
int textLoc;
int reLoc;
char *video; // This may be a bug, not too sure yet

void update(char *text, char text_color, char background_color) {
    video = (unsigned char *)0xB8000;
    int attribute = (background_color << 4) | (text_color & 0x0F);
    int n = 0;

    current_loc--;
    while ( text[n] != '\0' ) {
        video[textLoc++] = text[n++];
        video[textLoc++] = attribute;
    }

    textLoc = reLoc;
}

void printq(char *text) {
    // Code
    video = (unsigned char *)0xB8000;
    const char *str = text;

    int n = 0;
    int lengthofstr = stringLength(text);

	while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
        video[current_loc++] = 07;
    }
}

void printk(char *text) {
    // Code
    video = (unsigned char *)0xB8000;
    const char *str = text;

    int n = 0;
	while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
        video[current_loc++] = 07;
    }
}

void print_to_screen2(char *text, char text_color, char background_color) {
    textLoc = current_loc;
    reLoc = textLoc;

    video = (unsigned char *)0xB8000;
    int attribute = (background_color << 4) | (text_color & 0x0F);
    const char *str = text;

    int n = 0;
	while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
        video[current_loc++] = attribute;
    }
}

void print_to_screen(char *text, char text_color, char background_color) {
    video = (unsigned char *)0xB8000;
    int attribute = (background_color << 4) | (text_color & 0x0F);
    const char *str = text;

    int n = 0;
	while ( str[n] != '\0' ) {
		video[current_loc++] = str[n++];
        video[current_loc++] = attribute;
    }
}

void back() {
    video = (unsigned char *)0xB8000;
	video[current_loc--] = " ";
    video[current_loc--] = 00;
}

void newline(void)
{
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void clear_screen2(char color) {
    video = (unsigned char *)0xB8000;
    // unsigned int j = 0;

    int attributeColor = (color << 4) | (color & 0x0F);

    int j = 0;
    int i = 0;
    current_loc = 0;

	while(j < SCREENSIZE) {
		video[j] = 178;    // 178
		video[j+1] = attributeColor; // 0xf9
		j = j + 2;
	}
    return;
}