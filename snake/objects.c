//
//  objects.c
//  snake
//
//  Created by Honza on 04/08/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

#include <stdio.h>
/*
        // 1 in area[][] = HEART
    {"\xE2\x99\xA5", RED, AREA_BGCOLOR, 100},
        // 2 = LEAF
    {"\xE2\x99\xA6", LIGHTGREEN, AREA_BGCOLOR, 400},
        // 3 = SUN
    {"\xE2\x98\xBC", YELLOW, BROWN, 300},
        // 4 = STAR/CROSS
    {"\xC3\x93", BLUE, AREA_BGCOLOR, 200}
*/

struct frame {
    char c[4];      //unicode character of frame/object
    int color;      //foreground color of frame
    int bgcolor;    //background color of frame
    int length;     //length of frame
};

struct object {
    int num;                    //number of frames in object
    struct frame frames[10];    //max number of frames, 10
    int points;                 //points recieved for collection of object
} objects[] = {
    {
        2, //heart
        {
            {"\xE2\x99\xA5", RED, AREA_BGCOLOR, 500},
            {"\xE2\x99\xA1", RED, AREA_BGCOLOR, 500},
        },
        100
    },
    {
        2,  //leaf
        {
            {"\xE2\x99\xA6", LIGHTBLUE, AREA_BGCOLOR, 250},
            {"\xE2\x99\xA2", BLUE, AREA_BGCOLOR, 750},
        },
        250
    },
    {
        4,  //dashes
        {
            {"-", YELLOW, AREA_BGCOLOR, 250},
            {"\\", YELLOW, AREA_BGCOLOR, 250},
            {"|", YELLOW, AREA_BGCOLOR, 250},
            {"/", YELLOW, AREA_BGCOLOR, 250},
        },
        500
    },
    {
        6,  //dice
        {
            {"\xE2\x9A\x80", GREEN, AREA_BGCOLOR, 200},
            {"\xE2\x9A\x81", GREEN, AREA_BGCOLOR, 200},
            {"\xE2\x9A\x82", GREEN, AREA_BGCOLOR, 200},
            {"\xE2\x9A\x83", GREEN, AREA_BGCOLOR, 200},
            {"\xE2\x9A\x84", GREEN, AREA_BGCOLOR, 200},
            {"\xE2\x9A\x85", GREEN, AREA_BGCOLOR, 200},
        },
        600
    },
};
