//////////////////////////////////////////
// Library name: strcopy.h              //
//                                      //
// Date created: 12/25/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

#pragma once
char *strcopy(char original[100], char copy[100]) {
    int i;
    for (i=0; original[i] != '\0'; i++) {
        copy[i] = original[i];
    }
    copy[i] = '\0';
    return copy;
}