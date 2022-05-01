////////////////////////////////////////////
// Module name: module.c                  //
//                                        //
// Author:       Jakob Long.              //
// Date created: 12/21/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////

char *demo_string = "Hello, World!";

void TEST() {
    printK("Hello :)");
}

void module_init() {
    clearC(0);
    printK(" I love you TayTay <3 ");
    newlineK();
    initiate("mataya"); // Store module name so it can be run later :^)
}