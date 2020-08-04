//
//  main.c
//  had
//
//  Created by Honza on 7/07/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

//TODO:
//  -Allow the objects to animate

#include <stdio.h>
#include <stdlib.h>
#include "rlutil.h"

//to fix the library not working on linux
#undef  KEY_ENTER
#define KEY_ENTER 10

//  a   = area
//      a[i][j]     -   a[HEIGHT][WIDTH]
//      a[i][j]     -   i is smaller than 24, width is smaller than 80 (size of default terminal window
//  w   = width
//  h   = height
//  a[row][coloumn]
#define AREA_BGCOLOR    CYAN
#define END             8191    //end of line. if value in end searcher is 8192, it realises that it is the end of the line/coloumn

int score = 0;
int rem_objects;    //remaining number of objects on current level

//  0 = game is running, 1 = game ended with a win, 2 = game ended with a loss, 3 = user wants to exit
int finish = 0;


struct {
    int print;
    int maxscore;
    int objects;
    int w;
    int h;
} debug;

#include "area.c"

//  a = area
//  a[coloumn][row]
//  program uses [HEIGHT][WIDTH] because double arrays when entered in (every array on 2nd level has a new line) means that the second must be rows and the first variable must be columns

int area[HEIGHT][WIDTH] = {
    {W, W, W, W, W, W, W, W, W, W, W, W},
    {W, 1, 1, W, 1, 1, 1, 1, 1, 1, 1, D},
    {W, 1, 1, W, 1, 0, 0, 0, 0, W, 1, W},
    {W, 1, 1, W, 1, 0, 0, 0, 0, W, 1, W},
    {W, 1, 1, W, 1, W, W, 0, 0, W, 1, W},
    {W, 2, 1, W, 1, 0, W, 0, 0, W, 1, W},
    {W, 3, 1, 1, 1, 0, W, W, W, W, 1, W},
    {W, 4, 0, 0, 0, W, W, 0, 0, W, 1, W},
    {W, 0, 0, W, 0, 0, 0, 0, 0, 0, 1, W},
    {W, 0, 0, W, 0, 0, 0, 0, 0, 0, 1, W},
    {W, H, 0, W, 0, 0, 0, 0, 0, 0, 1, W},
    {W, W, W, W, W, W, W, W, W, W, W, W+END},
};

struct {
    int key;
    int dx;
    int dy;
} arrow_move[4] = {
    {KEY_UP, 0, -1},
    {KEY_DOWN, 0, 1},
    {KEY_RIGHT, 1, 0},
    {KEY_LEFT, -1, 0}
};


int main()
{
    struct areaSize size;
    saveDefaultColor();
    
    setBackgroundColor(BLACK);
    cls();
    hidecursor();
    
    size = getAreaSize(area);
    debug.print = 1;
    debug.maxscore = debug.maxscore;
    debug.objects = debug.objects;
    debug.w = size.w;
    debug.h = size.h;
    
    rem_objects = debug.objects;
    
    printArea(area, size.w, size.h);
    
    while (1) {
        msleep(5);
        if (kbhit()) {
            int key, i;
            
            key = getkey();
            for (i = 0; i < 4; i++) {
                if (!finish) {
                    if (arrow_move[i].key == key) {
                        moveHead(area, size.w, size.h, arrow_move[i].dx, arrow_move[i].dy);
                        printArea(area, size.w, size.h);
                        break;
                    }
                }
            }
                // pokud je v i 4, tak v key nebyla sipka
            if (i == 4) {
                if (key == KEY_ESCAPE) {
                    break; // end while loop
                }
                else if (key == KEY_ENTER) {
                    debug.print = !debug.print;
                    printArea(area, size.w, size.h);
                }
            }
            
            if (finish == 1){
                if (key == KEY_ENTER){
                    break;
                }
            }
        }
    }
    
    setBackgroundColor(BLACK);
    cls();
    resetColor();
    showcursor();
    
    //Only for debug
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}
