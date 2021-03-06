//
//  area.c
//  snake
//
//  Created by Honza on 21/07/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

/*
 Reserved variable names
 ----------------------------
 
 a[ROW][COLOUMN] = area = game area
 a[i][j]
 a[height][width]
 w = width = width of the game area
 h = height = height of the game area
 0 <= i < h
 0 <= j < w
 */



#define  WIDTH    80
#define  HEIGHT   25

    // DONT CHANGE FREE!!
    // In the definition of the game array, we rely on 0
#define  FREE   0
#define  WALL   100
#define  W      WALL
#define  DOOR   200
#define  WALL_FIRE   6   // index do pole objects[]
#define  D      DOOR
#define  HEAD   300
#define  H      HEAD

#define  OBJ_FROM  1
#define  OBJ_TO    99

#define BODY_FROM   1000    // body of the snake. it therefore has a maximum of 100 spots it can be at the same time
#define BODY_TO     1099
#define MAX_BODY_LENGTH (BODY_TO - BODY_FROM)

#define   END      999999

#define  AREA_BGCOLOR    CYAN
#define  PRG_BGCOLOR     BLACK

#define OPENDOOR    7   // index in objects[]


#include "objects.c"


struct areaSize {
    int w;
    int h;
    int objects;
    int maxscore;
    int door_x, door_y;
};


struct piece {
    int x;
    int y;
    int pos;
};
struct {
    struct piece pieces[MAX_BODY_LENGTH];
} body;


void printnl() {
    printf("\n");
}

void printArea(int a[][WIDTH], int w, int h, int save) {
    int i, j;
    
    gotoxy(1, 1);
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            if (a[i][j] >= OBJ_FROM && a[i][j] <= OBJ_TO) {
                int oi; // object index
                int fi; // frame index
                
                oi = a[i][j] - OBJ_FROM;
                    // objects[oi].delay
                fi = (timer / objects[oi].delay) % objects[oi].num;
                
                setBackgroundColor(objects[oi].frames[fi].bgcolor);
                setColor(objects[oi].frames[fi].color);
                if (save)
                    gotoxy(j + 1, i + 1);
                printf("%s", objects[oi].frames[fi].c);
            }
            else {
                if (save)
                    continue;
                
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
                    if (game.rem_objects > 0)
                        printf("#");
                    else
                        printf(" ");
                }
                else if (a[i][j] == HEAD) {
                    setBackgroundColor(AREA_BGCOLOR);
                    setColor(WHITE);
                    printf("~");
                }
                else {
                    setBackgroundColor(AREA_BGCOLOR);
                    setColor(WHITE);
                    printf("?");
                }
            }
        }
        if (!save)
            printf("\n");
    }
    
    if (save)
        gotoxy(1, h + 1);
    
    setColor(GREY);
    setBackgroundColor(PRG_BGCOLOR);
    printf("Score: %d\n", game.score);
    printnl();
    
    if (state == ST_WIN) {
        debug.print = 0;
        cls();
        printf("Vitezstvi! Hra skoncila.\n");
        printf("Stiskni ENTER pro konec.\n");
        printnl();
    }
    else if (state == ST_GAMEOVER) {
        printf("Pozor zed! Hra skoncila.\n");
        printf("Stiskni ENTER pro konec.\n");
        printnl();
    }
    
    if (debug.print) {
        printnl();
        printnl();
        printf("Max. score: %3d\n", debug.maxscore);
        printf("Celkem objektu: %3d\n", debug.objects);
        printf("Zbyva objektu: %3d  \n", game.rem_objects);
        printf("State: %d\n", state);
        printf("Timer: %ld s %ld ms.\n", timer / 1000, timer % 1000);
        printf("Clock: %ld, CPS: %d\n", timer, CLOCKS_PER_SEC);
    }
}


struct areaSize getAreaSize(int a[][WIDTH]) {
    struct areaSize size;
    int i, j, end = 0;
    
    size.objects = 0;
    size.maxscore = 0;
    size.door_y = 1;
    size.door_x = 1;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (a[i][j] >= END) {
                size.w = j + 1;
                size.h = i + 1;
                a[i][j] -= END;
                end = 1;
            }
            if (a[i][j] >= OBJ_FROM && a[i][j] <= OBJ_TO) {
                size.objects++;
                size.maxscore += objects[ a[i][j] - OBJ_FROM ].points;
            }
            if (a[i][j] == DOOR) {
                size.door_x = j;
                size.door_y = i;
            }
            if (end)
                return size;
        }
    }
    return size;
}


void moveHead(int a[][WIDTH], int w, int h, int dx, int dy) {
    /*
     If possible, the function moves with the head of the snake
     0 = TOP
     1 = RIGHT
     2 = BOTTOM
     3 = LEFT
     */
    int x, y;
    
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            if (a[y][x] == HEAD) {
                if (y + dy >= 0 && y + dy < h && x + dx >= 0 && x + dx < w) {
                    if (a[y + dy][x + dx] == FREE)
                        ;
                    else if (a[y + dy][x + dx] == OPENDOOR) {
                        state = ST_WIN;
                    }
                    else if (a[y + dy][x + dx] >= OBJ_FROM && a[y + dy][x + dx] <= OBJ_TO) {
                        game.score += objects[ a[y + dy][x + dx] - OBJ_FROM].points;
                        game.rem_objects--;
                        if (game.rem_objects == 0) {
                            a[game.door_y][game.door_x] = OPENDOOR;
                        }
                    }
                    else if (a[y + dy][x + dx] == WALL || a[y + dy][x + dx] == DOOR) {
                        a[y + dy][x + dx] = WALL_FIRE;
                        state = ST_GAMEOVER;
                        return;
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


void moveBody(int a[][WIDTH], int w, int h, int add) {
    /*
     This function moves the body, re-numbering it.
     If add is 1, it will add a piece to the end of the snake.
     If add is 0, it will just move the snake along
    */
    
    int head_x = -1, head_y = -1;
    for (int i = 0; i < game.length; i++) { // find the body
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (a[x][y] <= BODY_FROM && a[x][y] <= BODY_TO) {
                    body.pieces[i].x = x;
                    body.pieces[i].y = y;
                    body.pieces[i].pos = i;
                }
                else if (a[x][y] == HEAD) {
                    head_x = x;
                    head_y = y;
                }
            }
        }
    }
    
    for (int i = 0; i < game.length + add; i++) {
        body.pieces[i].x = body.pieces[i+1].x;
        body.pieces[i].y = body.pieces[i+1].y;
        body.pieces[i].pos = body.pieces[i+1].pos;
    }
    
    return;
}
