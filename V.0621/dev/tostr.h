#ifndef TOSTR_H
#define TOSTR_H

#include "../include/panic.h"

char i2s;

char _toStr(int num) {
    

    i2s = num + '0';
    return i2s;
}

#endif