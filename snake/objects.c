//
//  objects.c
//  snake
//
//  Created by Honza on 04/08/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

#include <stdio.h>
struct object {
    char c[4];       // znak objektu
    int  color;   // barva znaku
    int  bgcolor; // barva pozadí
    int  points;  // body za sebrání
} objects[] = {
        // 1 in area[][] = HEART
    {"\xE2\x99\xA5", RED, AREA_BGCOLOR, 100},
        // 2 = LEAF
    {"\xE2\x99\xA6", LIGHTGREEN, AREA_BGCOLOR, 400},
        // 3 = SUN
    {"\xE2\x98\xBC", YELLOW, BROWN, 300},
        // 4 = STAR/CROSS
    {"\xC3\x93", BLUE, AREA_BGCOLOR, 200}
};
