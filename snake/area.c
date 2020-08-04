//
//  DONOTarea.c
//  snake
//
//  Created by Honza on 21/07/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

#include "objects.c"

struct areaSize {
  int w;
  int h;
};

//prints out the area and needs the WIDTH parameter because in memory, the numbers are one behind another so it can see how far it needs to go for a new line
void printArea(int a[][WIDTH], int w, int h) {
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
                printf("#");
            }
            else if (a[i][j] == HEAD) {
                setBackgroundColor(AREA_BGCOLOR);
                setColor(WHITE);
                printf("~");
            }
            else if (a[i][j] >= OBJ_FROM && a[i][j] <= OBJ_TO) {
                int oi; // object index
                
                oi = a[i][j] - OBJ_FROM;
                
                setBackgroundColor(objects[oi].bgcolor);
                setColor(objects[oi].color);
                printf("%s", objects[oi].c);
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
    printf("Score: %d", score);
    
    if (debug.print) {
        printf("\n\nMax. score: %d\n", debug.maxscore);
        printf("Objektu: %d\n", debug.objects);
    }
}
//gets the size of the area and returns it. it can be accessed in the function main() and be passed to other functions
struct areaSize getAreaSize(int a[][WIDTH]) {
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

//movement of the head
//dx, dy = direction of movement. dx, dy = deltax, deltay - change in x and y
//  -1  = left/up
//  0   = stay
//  1   = right/down
void moveHead(int a[][WIDTH], int w, int h, int dx, int dy) {
    int x, y;
    
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (a[y][x] == HEAD) {
                if (y + dy >= 0 && y + dy < h && x + dx >= 0 && x + dx < w) {
                    if (a[y + dy][x + dx] == FREE)
                        ;
                    else if (a[y + dy][x + dx] >= OBJ_FROM && a[y + dy][x + dx] <= OBJ_TO) {
                        score += objects[ a[y + dy][x + dx] - OBJ_FROM].points;
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
