#include "../OS/OS.h"
#pragma once

// Check if app has rights to access system calls.
// If not, close app and reload to desktop. :^)
void appCheck(int accessNumber) {
    const int accessNumberCheck = 0721;
    if ( accessNumber != accessNumberCheck ) _BOOT();
}