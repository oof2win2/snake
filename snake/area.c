//
//  DONOTarea.c
//  snake
//
//  Created by Honza on 21/07/2020.
//  Copyright © 2020 Honza. All rights reserved.
//

struct areaSize {
  int w;
  int h;
};

#pragma mark printArea() function
void printArea(int a[][WIDTH], int w, int h) {
    saveDefaultColor(); //saves color that has been used before to set it back later
    gotoxy(1, 1);   //uses gotoxy instead of cls to prevent flickering on windows computers
    int c;  //current point going through
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            c = a[i][j];
            if (c == WALL) {
                setColor(LIGHTCYAN);
                setBackgroundColor(RED);
                printf("# ");
            }
            else if (c == FREE) {
                setColor(LIGHTGREEN);
                setBackgroundColor(BLUE);
                printf("  ");
            }
            else if (c == HEAD) {
                setColor(LIGHTRED);
                setBackgroundColor(MAGENTA);
                printf("~ ");
            }
            else if (c == DOOR) {
                setColor(LIGHTMAGENTA);
                setBackgroundColor(DARKGREY);
                printf("\\ ");
            }
            else {
                setColor(WHITE);
                setBackgroundColor(BLACK);
                printf("? ");
            }
        }
        printf("\n");
    }
    resetColor();   //resets color to the colors saved on the start of printArea()
}


struct areaSize getAreaSize(int a[][WIDTH]) {
    struct areaSize size;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (a[i][j] >= END) {
                size.w = j+1;
                size.h = i+1;
                a[i][j] -= END;
                return size;
            }
        }
    }
    size.h = HEIGHT;
    size.w = WIDTH;
    return size;
}

//moving head. x, y = direction of movement
//  -1  = left/up
//  0   = stay
//  1   = right/down
//dx, dy = deltax, deltay - change in x and y
void moveHead(int a[][WIDTH], int dx, int dy, int w, int h) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (a[y][x] == HEAD) {
                if (y + dy >= 0 && y + dy < h && x + dx >= 0 && x+dx < w && a[y+dy][x+dx] == FREE) {
                    a[y][x] = FREE;
                    a[y+dy][x+dx] = HEAD;
                }
            }
        }
    }
}
