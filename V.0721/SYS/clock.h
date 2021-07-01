//////////////////////////////////////////
// App name: clock.h                    //
//                                      //
// Date created: 06/09/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

#pragma once
#include "../include/print.h"

char FinalTime[50];

// Use this program as a stopwatch that counts up from 0
// but goes by seconds (or something roughly close) until
// I'm able to get the corect time displaying. Getting the
// time to display may have to wait until the 0821 update.

void _CLOCK() {
    int i;
    char TimeOfDay = 'A';

    static int time = 0;
    char time2 = time + '0';

    static int time3 = 0;
    char time4 = time3 + '0';

    FinalTime[0] = time4;
    FinalTime[1] = time2;
    
    for ( i=2; i<22; i++ ) FinalTime[i] = ' '; // i was originally 18

    newline();
    print(FinalTime, "Stopwatch ");
    
    if ( time3 == 6) {
        time3 = 0;
        time = 0;
        // bootld(0721);
    }

    if ( time == 9 ) {
        time = -1;
        time3++;
    }

    sleep(0x03FFFFFF);
    time++;
}