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

// to fix the library not working on linux
#ifndef _WIN32
    #undef  KEY_ENTER
    #define KEY_ENTER 10
    #undef  CLOCKS_PER_SEC
    #define CLOCKS_PER_SEC 15000
#endif

int finish = 0; // 0 = game is running, 1 = game ended with a win, 2 = game ended with a loss, 3 = user wants to exit
time_t timer = 0;  // a thing from rlutil to allow us to get the time from program start

struct {
    int print;
    int maxscore;
    int objects;
    int w;
    int h;
} debug;

struct {
    int score;          // the score of the player
    int rem_objects;    // number of remaining objects
    int door_x, door_y; // xy position of the door
    int move_ms;        // delay in ms between movements of the snake
    int start;          // the value in timer when the first key is pressed
} game;

#include "area.c"

    // a = area
int area[HEIGHT][WIDTH] = { // 16, 10
    {W,W,W,W,W,D,W,W,W,W,W,W,W,W,W,W,W},
    {W,0,0,0,0,0,0,W,0,0,0,0,0,0,0,0,W},
    {W,W,W,W,W,5,0,W,0,W,W,W,W,W,0,0,W},
    {W,0,0,0,W,4,0,W,0,W,0,0,0,W,0,0,W},
    {W,0,0,0,W,3,0,W,0,0,0,W,0,W,0,0,W},
    {W,0,W,W,W,2,0,W,W,W,W,W,0,W,W,0,W},
    {W,0,0,0,W,1,0,0,0,W,0,0,0,0,0,0,W},
    {W,0,0,0,0,0,0,W,0,0,0,W,W,W,W,0,W},
    {W,0,W,0,0,H,0,W,0,0,0,W,0,0,0,0,W},
    {W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W+END},
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


int main() {
    struct areaSize size;
    saveDefaultColor();
    
    setBackgroundColor(PRG_BGCOLOR);
    cls();
    hidecursor();
    
    size = getAreaSize(area);
    debug.print = 0;
    debug.maxscore = size.maxscore;
    debug.objects = size.objects;
    debug.w = size.w;
    debug.h = size.h;
    game.rem_objects = size.objects;
    game.door_x = size.door_x;
    game.door_y = size.door_y;
    game.move_ms = 1000;
    
    printArea(area, size.w, size.h, 0);
    
    while (1) {
        msleep(10);
        timer = clock() * 1000 / CLOCKS_PER_SEC;   // idk hard maths makes it work for calculation of ms
        
        if (kbhit()) {
            int key, i; 
            
            key = getkey();
            
            for (i = 0; i < 4; i++) {
                if (arrow_move[i].key == key) {
                    if (!finish) {
                        moveHead(area, size.w, size.h, arrow_move[i].dx, arrow_move[i].dy);
                        printArea(area, size.w, size.h, 0);
                    }
                    break;
                }
            }
                // if i is 4, then the key pressed wasn't an arrow
            if (i == 4) {
                if (key == KEY_ESCAPE) {
                    break; // end while loop
                }
                else if (key == KEY_ENTER) {
                    if (finish == 1 || finish == 2) // ENTER after the end of the game ends the while loop
                        break;
                    
                    debug.print = !(debug.print);
                    if (!debug.print) {
                        setBackgroundColor(PRG_BGCOLOR);
                        cls();
                    }
                    printArea(area, size.w, size.h, 0);
                }
            }
        }
        else {
            printArea(area, size.w, size.h, 1);
        }
    }
    
    setBackgroundColor(BLACK);
    cls();
    resetColor();
    showcursor();
    
        // Only for debug purposes
    setColor(GREY);
    setBackgroundColor(BLACK);
    
    return 0;
}
