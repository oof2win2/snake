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
