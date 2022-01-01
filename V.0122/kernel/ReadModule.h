////////////////////////////////////////////
// File name: ReadModule.c                //
//                                        //
// Author:       Jakob Long.              //
// Date created: 12/17/21                 //
//                                        //
// Copyright (c) Jakob Long, 2021 - 2023. //
////////////////////////////////////////////


#pragma once

#define MODULE_EXIST
#define module_start init_modules

#define module_init(function) 
    function(); 