//
//  DONOTarea.c
//  snake
//
//  Created by Honza on 21/07/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

//  common things (walls, doors etc.) ->  00-09
//  objects to collect                ->  10-99
//  snake parts                       ->  100-119
#define  WIDTH  80
#define  HEIGHT 25

#define  FREE   0
#define  WALL   100
#define  W      WALL
#define  DOOR   200
#define  D      DOOR
#define  HEAD   300
#define  H      HEAD

#define  OBJ_FROM  1
#define  OBJ_TO    99

#include "objects.c"

struct areaSize {
  int w;
  int h;
};

void printArea(int a[][WIDTH], int w, int h) {
    //prints out the area and needs the WIDTH parameter because in memory, the numbers are one behind another so it can see how far it needs to go for a new line
    int i, j;
    
    cls();
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if (a[i][j] == FREE) {
                setBackgroundColor(AREA_BGCOLOR);
                printf(" ");
            }
            else if (a[i][j] == WALL) {
                setBackgroundColor(RED);
                printf(" ");
            }
            else if (a[i][j] == DOOR) {
                setBackgroundColor(GREEN);
                setColor(WHITE);
                if (rem_objects > 0)
                    printf("#");
                else
                    printf("\xE2\x98\xA2");
            }
            else if (a[i][j] == HEAD) {
                setBackgroundColor(AREA_BGCOLOR);
                setColor(WHITE);
                printf("~");
            }
            else if (a[i][j] >= OBJ_FROM && a[i][j] <= OBJ_TO) {
                int oi; // object index
                
                oi = a[i][j] - OBJ_FROM;
                
                setBackgroundColor(objects[oi].frames[0].bgcolor);
                setColor(objects[oi].frames[0].color);
                printf("%s", objects[oi].frames[0].c);
            }
            else {
                setBackgroundColor(AREA_BGCOLOR);
                setColor(WHITE);
                printf("?");
            }
        }
        printf("\n");
    }
    
    setColor(GREY);
    setBackgroundColor(BLACK);
    printf("Score: %d\n", score);
    
    if (debug.print) {  //if debug output is set to true do:
        printf("\n\n\n");
        printf("Max. score achievable      : %3d\n", debug.maxscore);
        printf("Number of objects          : %3d\n", debug.objects);
        printf("Number of remaining objects: %3d\n", rem_objects);
        printf("Finish:                    : %3d\n", finish);
    }
    if (finish == 1) {
        printf("\n\n");
        printf("\xF0\x9F\xA7\xA8");
        printf("\xF0\x9F\xA7\xA8");
        printf("\xF0\x9F\xA7\xA8");
        printf("\n");
        printf("YOU WON!!!");
        printf("\n");
        printf("\xF0\x9F\xA7\xA8");
        printf("\xF0\x9F\xA7\xA8");
        printf("\xF0\x9F\xA7\xA8");
        printf("\n\n");
        printf("Press ENTER to continue");
    }
    printf("\n");
}


struct areaSize getAreaSize(int a[][WIDTH]) {
    //gets the size of the area and returns it. it can be accessed in the function main() and be passed to other functions
    struct areaSize size;
    int i, j;
    
    debug.objects = 0;
    debug.maxscore = 0;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (a[i][j] >= OBJ_FROM && a[i][j] <= OBJ_TO) {
                debug.objects++;
                debug.maxscore += objects[ a[i][j] - OBJ_FROM ].points;
            }
            if (a[i][j] >= END) {
                size.w = j + 1;
                size.h = i + 1;
                a[i][j] -= END;
                return size;
            }
        }
    }
    
    size.w = WIDTH;
    size.h = HEIGHT;
    return size;
}

void moveHead(int a[][WIDTH], int w, int h, int dx, int dy) {
        //movement of the head
        //dx, dy = direction of movement. dx, dy = deltax, deltay - change in x and y
        //  -1  = left/up
        //  0   = stay
        //  1   = right/down
    int x, y;
    
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (a[y][x] == HEAD) {
                if (y + dy >= 0 && y + dy < h && x + dx >= 0 && x + dx < w) {
                    if (a[y + dy][x + dx] == FREE)  //if goto is free
                        ;
                    else if (a[y + dy][x + dx] >= OBJ_FROM && a[y + dy][x + dx] <= OBJ_TO) {    //if goto is a point/collectible
                        score += objects[ a[y + dy][x + dx] - OBJ_FROM].points;
                        rem_objects--;
                    }
                    else if (a[y + dy][x + dx] == DOOR && rem_objects == 0) {   //if goto is a door and remaining objects is zero
                        finish = 1; //the reason of finishing is game is won, then moves on to move the body
                    }
                    else
                        return;
                    
                    a[y + dy][x + dx] = HEAD;
                    a[y][x] = FREE;
                }
                
                return;
            }
        }
    }
}
