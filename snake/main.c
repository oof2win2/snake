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

/*
 TODO::
 -Change area from global array to local array, as more levels would fuck this up
 */

#pragma mark default/reserved variables
//the default variables for width and height are default sizes of the Terminal app on Mac where this was coded
//width of array available, everything unused gets set to 0
#define WIDTH       80
//height of array available, everything unused gets set to 0
#define HEIGHT      24

//in the definition of the array, we assume that 0 is used to increase visibility in most editors
#define FREE        0       //free piece of land in game
#define WALL        1       //wall
#define W           WALL    //wall
#define DOOR        2       //door to exit level
#define D           DOOR    //door
#define OBJ_FROM    100     //number from which objects start
#define OBJ_TO      199     //number from which objects end
//  common things (walls, doors etc.) ->  00-09
//  objects to collect                ->  10-99
//  snake parts                       ->  100-119
#define H           100     //snake head
#define HEAD        H
//      reserved variable names:
//  a   = area
//      a[i][j]     -   a[HEIGHT][WIDTH]
//      a[i][j]     -   i is smaller than 24, width is smaller than 80 (size of default terminal window
//  w   = width
//  h   = height
//  a[row][coloumn]


//  a = area
//  a[coloumn][row]
//  program uses [HEIGHT][WIDTH] because double arrays when entered in (every array on 2nd level has a new line) means that the second must be rows and the first variable must be columns
#pragma mark setting area
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
    {W, W, W, W, W, W, W, W, W, W, W, W},
};

//  prints out the area and needs the WIDTH parameter because in memory, the numbers are one behind another so it can see how far it needs to go for a new line
#pragma mark printArea() function
void printArea(int a[][WIDTH], int w, int h) {
    saveDefaultColor(); //saves color that has been used before to set it back later
    int c;  //current point going through
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            c = a[i][j];
            if (c == WALL) {
                setColor(LIGHTCYAN);
                printf("# ");
            }
            else if (c == FREE) {
                setColor(LIGHTGREEN);
                printf("  ");
            }
            else if (c == HEAD) {
                setColor(LIGHTRED);
                printf("~ ");
            }
            else if (c == DOOR) {
                printf("\\ ");
                setColor(LIGHTMAGENTA);
            }
            else {
                printf("? ");
                setColor(WHITE);
            }
        }
        printf("\n");
    }
    resetColor();   //resets color to the colors saved on the start of printArea()
}
#pragma mark testing()
void testing() {
    hidecursor();   //hides the cursor from the terminal window (only the pointer to where you're typing
    printArea(area, 12, 12);
}
void run() {
    hidecursor();   //hides the cursor from the terminal window (only the pointer to where you're typing
    
}
#pragma mark main()
int main(int argc, const char * argv[]) {
    testing();
    
    //run();
    return 0;
}
