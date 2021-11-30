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

int len;
char conv;
char strConv[5];

int stringLength(char *usr) {

    while ( usr[len] != '\0' ) {
        len++;
    }

    // Due to the loop above, I cannot declare len as anything.
    // I will get this bug fixed in a bit by trying to return out
    // of the loop and then declaring len.
    //if ( len >= 10 ) errorPop();

    conv = len + '0';
    strConv[0] = conv;

    return len;
}

int alignTextCenter(char *usr) {
    int m = 79;
    int _len = 0;

    _len = stringLength(usr);
    
    int al = (m - _len) / 2;

    return al;
}

#endif