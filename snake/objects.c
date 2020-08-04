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
        // 1 v area = SRDCE
    {"\x03", RED, AREA_BGCOLOR, 100},
        // 2 = LISTEK
    {"\x04", LIGHTGREEN, AREA_BGCOLOR, 400},
        // 3 = SLUNICKO
    {"\x0F", YELLOW, BROWN, 300},
        // 4 = STAR
    {"*", BLUE, AREA_BGCOLOR, 200}
};
