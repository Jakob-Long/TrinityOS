///////////////////////////////////////////
// Module name : StartMenu.h             //
//                                       //
// Date created: 03/11/22                //
// Author      : Jakob Long              //
//                                       //
// Copyright (c) Jakob Long, 2021 - 2024 //
///////////////////////////////////////////

#pragma once

#include "../drivers/DisplayDriver/vga.h"
#include "../drivers/FileManager/file_list.h"
#include "../desktop.h"
#include "../lib/LibC/panic.h"

int isMenuOpen; // 0 = Menu Open, 1 = Menu Closed
int isMenuOpen2 = 1;
extern int isWindowOpen;
extern int isWindowOpen2;

// Start Menu for Christmas Theme
void drawItemsForClosedWindow2() {
    clear_screen2(0);
    for ( int i=0; i<16; i++) {
        newline();
    }
}

void drawItemsForOpenWindow2() {
    clear_screen2(0);
    drawWindowChristmas("       Press T for text mode       ", "            Quick Start           ");
    
    for ( int i=0; i<7; i++) {
        newline();
    }
}

void DrawStartMenu2() {
    // Draw start menu
    isMenuOpen2 = 0; // Menu is open

    // Draw start menu
    if ( isWindowOpen2 == 0 ) { // Draw quick menu to work with open window
        drawItemsForOpenWindow2(); // Clear screen and redraw window

        int CenterStartMenu = (80 - 24) / 2;

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }
        print_to_screen("       Quick Menu       ", 0, 4);
        
        newline();

        // Print user-created file info
        if (file_table[3].name != "new file") {
            if (file_table[3].name != "empty") {
                file_table[3].name = "empty";
                file_table[3].contents = "empty";
            }
        }

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }

        if ( file_table[3].name == "empty") {
            print_to_screen("      ", 4, 4);
            print_to_screen(file_table[3].name, 0, 4);
            print_to_screen(" : ", 0, 4);
            print_to_screen(file_table[3].contents, 0, 4);
            print_to_screen("     ", 4, 4);
        } else {
            //print_to_screen(" ", 6, 6);
            print_to_screen(file_table[3].name, 0, 4);
            print_to_screen(" : ", 0, 4);
            print_to_screen(file_table[3].contents, 0, 4);
        }

        // Draw rest of the start menu
        for ( int i=0; i<5; i++) {
            newline();
            for ( int i=0; i<CenterStartMenu; i++) {
                print_to_screen(" ", 0, 0);
            }
            print_to_screen("                        ", 4, 4);
        }

        // Draw Taskbar
        taskbarChristmas(1);
    } else if ( isWindowOpen2 == 1 ) { // Draw quick menu to work with closed window
        //ERR("HEHE_BROKEN");
        drawItemsForClosedWindow2();

        int CenterStartMenu = (80 - 24) / 2;

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }
        print_to_screen("       Quick Menu       ", 0, 4);
        
        newline();

        // Print user-created file info
        if (file_table[3].name != "new file") {
            if (file_table[3].name != "empty") {
                file_table[3].name = "empty";
                file_table[3].contents = "empty";
            }
        }

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }

        if ( file_table[3].name == "empty") {
            print_to_screen("      ", 4, 4);
            print_to_screen(file_table[3].name, 0, 4);
            print_to_screen(" : ", 0, 4);
            print_to_screen(file_table[3].contents, 0, 4);
            print_to_screen("     ", 4, 4);
        } else {
            //print_to_screen(" ", 6, 6);
            print_to_screen(file_table[3].name, 0, 4);
            print_to_screen(" : ", 0, 4);
            print_to_screen(file_table[3].contents, 0, 4);
        }

        // Draw rest of the start menu
        for ( int i=0; i<5; i++) {
            newline();
            for ( int i=0; i<CenterStartMenu; i++) {
                print_to_screen(" ", 0, 0);
            }
            print_to_screen("                        ", 4, 4);
        }

        // Draw Taskbar
        taskbarCloseChristmas(1);
    }
}

void drawItemsForClosedWindow() {
    clear_screen2(0);
    for ( int i=0; i<16; i++) {
        newline();
    }
}

// Start Menu for Default Theme
void drawItemsForOpenWindow() {
    clear_screen2(0);
    drawWindow("       Press T for text mode       ", "            Quick Start           ");
    
    for ( int i=0; i<7; i++) {
        newline();
    }
}

void DrawStartMenu() {
    isMenuOpen = 0; // Menu is open

    // Draw start menu
    if ( isWindowOpen == 0 ) { // Draw quick menu to work with open window
        drawItemsForOpenWindow(); // Clear screen and redraw window

        int CenterStartMenu = (80 - 24) / 2;

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }
        print_to_screen("       Quick Menu       ", 0, 6);
        
        newline();

        // Print user-created file info
        if (file_table[3].name != "new file") {
            if (file_table[3].name != "empty") {
                file_table[3].name = "empty";
                file_table[3].contents = "empty";
            }
        }

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }

        if ( file_table[3].name == "empty") {
            print_to_screen("      ", 6, 6);
            print_to_screen(file_table[3].name, 0, 6);
            print_to_screen(" : ", 0, 6);
            print_to_screen(file_table[3].contents, 0, 6);
            print_to_screen("     ", 6, 6);
        } else {
            //print_to_screen(" ", 6, 6);
            print_to_screen(file_table[3].name, 0, 6);
            print_to_screen(" : ", 0, 6);
            print_to_screen(file_table[3].contents, 0, 6);
        }

        // Draw rest of the start menu
        for ( int i=0; i<5; i++) {
            newline();
            for ( int i=0; i<CenterStartMenu; i++) {
                print_to_screen(" ", 0, 0);
            }
            print_to_screen("                        ", 6, 6);
        }

        // Draw Taskbar
        taskbar(1);
    } else if ( isWindowOpen == 1 ) { // Draw quick menu to work with closed window
        //ERR("HEHE_BROKEN");
        drawItemsForClosedWindow();

        int CenterStartMenu = (80 - 24) / 2;

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }
        print_to_screen("       Quick Menu       ", 0, 6);
        
        newline();

        // Print user-created file info
        if (file_table[3].name != "new file") {
            if (file_table[3].name != "empty") {
                file_table[3].name = "empty";
                file_table[3].contents = "empty";
            }
        }

        for ( int i=0; i<CenterStartMenu; i++) {
            print_to_screen(" ", 0, 0);
        }

        if ( file_table[3].name == "empty") {
            print_to_screen("      ", 6, 6);
            print_to_screen(file_table[3].name, 0, 6);
            print_to_screen(" : ", 0, 6);
            print_to_screen(file_table[3].contents, 0, 6);
            print_to_screen("     ", 6, 6);
        } else {
            //print_to_screen(" ", 6, 6);
            print_to_screen(file_table[3].name, 0, 6);
            print_to_screen(" : ", 0, 6);
            print_to_screen(file_table[3].contents, 0, 6);
        }

        // Draw rest of the start menu
        for ( int i=0; i<5; i++) {
            newline();
            for ( int i=0; i<CenterStartMenu; i++) {
                print_to_screen(" ", 0, 0);
            }
            print_to_screen("                        ", 6, 6);
        }

        // Draw Taskbar
        taskbarClose(1);
    }
}