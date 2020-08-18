//
//  objects.c
//  snake
//
//  Created by Honza on 04/08/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

struct frame {
    char c[4];
    int color;
    int bgcolor;
};

struct object {
    int  num;  // number of frames
    struct frame frames[10];
    int delay;  // delay in ms between frames
    int  points;  // points for object collection
} objects[] = {
    {
        2, // 1 - BLINKING HEART
        {
            {"\xE2\x99\xA5", RED, AREA_BGCOLOR},
            {" ", RED, AREA_BGCOLOR}
        },
        500,
        100
    },
    {
        2, // 2 -heart
        {
            {"\xE2\x99\xA5", RED, AREA_BGCOLOR},
            {"\xE2\x99\xA1", RED, AREA_BGCOLOR},
        },
        100,
        500,
    },
    {
        2,  // 3 - leaf
        {
            {"\xE2\x99\xA6", LIGHTBLUE, AREA_BGCOLOR},
            {"\xE2\x99\xA2", BLUE, AREA_BGCOLOR},
        },
        250,
        500,
    },
    {
        4,  // 4 - dashes
        {
            {"-", YELLOW, AREA_BGCOLOR},
            {"\\", YELLOW, AREA_BGCOLOR},
            {"|", YELLOW, AREA_BGCOLOR},
            {"/", YELLOW, AREA_BGCOLOR},
        },
        500,
        250,
    },
    {
        6,  // 5 - dice
        {
            {"\xE2\x9A\x80", GREEN, AREA_BGCOLOR},
            {"\xE2\x9A\x81", GREEN, AREA_BGCOLOR},
            {"\xE2\x9A\x82", GREEN, AREA_BGCOLOR},
            {"\xE2\x9A\x83", GREEN, AREA_BGCOLOR},
            {"\xE2\x9A\x84", GREEN, AREA_BGCOLOR},
            {"\xE2\x9A\x85", GREEN, AREA_BGCOLOR},
        },
        600,
        200
    },
    {
        5,  // 6 = HOĹĂŤCĂŤ ZEÄŽ (nedĂˇvat do hernĂ­ho plĂˇnu)
        {
            {"F",     RED,     YELLOW},
            {"I",  YELLOW,  RED},
            {"R",  YELLOW, RED},
            {"E",  YELLOW,  RED},
            {" ", RED, RED}
        },
        250,
        0
    },
    {
        2,  // 7 = OTEVĹENĂ‰ DVEĹE
        {
            {"\\",  WHITE,  GREEN},
            {"/",  WHITE,  GREEN},
        },
        500,
        0
    }
    
};
