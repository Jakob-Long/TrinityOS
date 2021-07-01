//////////////////////////////////////////
// Module name: align.h                 //
//                                      //
// Date created: 04/28/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

#ifndef ALIGN_H
#define ALIGN_H

#include "../../include/print.h"
#include "../../dev/tools.h"

// TODO: Add suppport for ints to print ASCII characters

char *_msg = "This is a test message";

void align_right(char *usr) {
    int m = 79;
    int _len = 0;

    _len = _strLen(usr); // Using the new working _strLen function. Might be a bit buggy LOL
    /*while ( usr[_len] != '\0' ) {
        _len++;
    }*/
    
    int al = m - _len;

    for ( int i=0; i<al + 1; i++ ) {
        OUT(" ");
    }

    OUT(_msg);
}

void align_left(char *usr) {
    OUT(usr);
}

void align_center(char *usr) {
    int m = 79;
    int _len = 0;

    _len = _strLen(usr);

    /*while ( usr[_len] != '\0' ) {
        _len++;
    }*/
    
    int al = (m - _len) / 2;

    for ( int i=0; i<al+2; i++ ) {
        OUT(" ");
    }

    OUT(usr);
}

#endif