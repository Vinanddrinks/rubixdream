//
// Created by vinanddrinks on 30/04/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifndef RUBIXDREAM_RUBIXDREAM_H
#define RUBIXDREAM_RUBIXDREAM_H
//definitions

typedef enum{FRONT, BACK,UP,DOWN,RIGHT,LEFT }Type_SIDE;
typedef enum{W, O, G, R, B, Y, LG}T_COLOR;

//structures

struct FACE{
    Type_SIDE SIDE;
    T_COLOR BLOCK[3][3];
};

//functions headers

struct FACE* CreateRubiks();
void init_rubiks(struct FACE* rubiks);
void display_rubiks(struct FACE* rubiks);
void display_line(struct FACE* rubiks, int face, int row);

int select_color(T_COLOR color);
char* select_caption(T_COLOR block_color);
int side_to_index(Type_SIDE face, struct FACE* rubiks);


#endif //RUBIXDREAM_RUBIXDREAM_H
