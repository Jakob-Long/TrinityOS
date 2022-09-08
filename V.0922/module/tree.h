#pragma once

void tree() {
    newline();
    for ( int i=1; i<9; ++i ) {
        for ( int j=1; j<i; ++j ) {
            printk("* ");
        }
        newline();
    }
}