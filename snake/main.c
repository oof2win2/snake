//
//  main.c
//  had
//
//  Created by Honza on 7/07/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "rlutil.h"

//the default variables for width and height are default sizes of the Terminal app on Mac where this was coded
//width of array available, everything unused gets set to 0
#define WIDTH           80
//height of array available, everything unused gets set to 0
#define HEIGHT          24

//in the definition of the array, we assume that 0 is used to increase visibility in most editors
#define FREE            0       //free piece of land in game
#define WALL            1       //wall
#define W               WALL    //wall
#define DOOR            2       //door to exit level
#define D               DOOR    //door
#define OBJ_FROM        100     //number from which objects start
#define OBJ_TO          199     //number from which objects end
//  common things (walls, doors etc.) ->  00-09
//  objects to collect                ->  10-99
//  snake parts                       ->  100-119
#define H               100     //snake head
#define HEAD            H
//      reserved variable names:
//  a   = area
//      a[i][j]     -   a[HEIGHT][WIDTH]
//      a[i][j]     -   i is smaller than 24, width is smaller than 80 (size of default terminal window
//  w   = width
//  h   = height
//  a[row][coloumn]
#define AREA_BGCOLOR    CYAN
#define END             8191    //end of line. if value in end searcher is 8192, it realises that it is the end of the line/coloumn

int score = 0;

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
    {W, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, D},
    {W, 0, 0, W, 0, 0, 0, 0, 0, W, 0, W},
    {W, 0, 0, W, 0, 0, 0, 0, 0, W, 0, W},
    {W, 0, 0, W, 0, W, W, 0, 0, W, 0, W},
    {W, 0, 0, W, 0, 0, W, 0, 0, W, 0, W},
    {W, 0, 0, 0, 0, 0, W, W, W, W, 0, W},
    {W, 0, 0, 0, 0, W, W, 0, 0, W, 0, W},
    {W, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, W},
    {W, 0, 0, W, 0, 0, 0, 0, 0, 0, 0, W},
    {W, H, 0, W, 0, 0, W, W, 0, 0, 0, W},
    {W, W, W, W, W, W, W, W, W, W, W, W+END},
};

struct {
    int key;
    int dx;
    int dy;
} arrow_move[4] = {
    {KEY_UP, 0, -1},
    {KEY_DOWN, 0, 1},
    {KEY_LEFT, -1, 0},
    {KEY_RIGHT, 1, 0},
};

void testing() {    //just to test features before putting them into run(), where they are in the 'temporary final' state
    cls();          //clears screen, useful to 'preset' the cmd window
    hidecursor();   //hides the cursor from the terminal window (only the pointer to where you're typing
    printArea(area, 12, 12);
    return;
}
void run() {
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
    
    printArea(area, size.w, size.h);
    while (1) {
        msleep(10);
        if (kbhit()) {
            int key, i;
            
            key = getkey();
            for (i = 0; i < 4; i++) {
                if (arrow_move[i].key == key) {
                    moveHead(area, size.w, size.h, arrow_move[i].dx, arrow_move[i].dy);
                    printArea(area, size.w, size.h);
                    break;
                }
            }
                // if int i is 4, the key was not a number
            if (i == 4) {
                if (key == KEY_ESCAPE) {
                    break; // end while(1)
                }
            }
        }
    }
    
    //some lines just for compat reaasons on Windows, as that does weird things when clearing the Terminal window
    setBackgroundColor(BLACK);
    cls();
    resetColor();
    showcursor();
    
    //just for debug
    setColor(GREY);
    setBackgroundColor(BLACK);
    return;
}


int main(int argc, const char * argv[]) {
    saveDefaultColor();
    testing();
    
    run();
    //resetColor();
    return 0;
}
