//
// Created by vinanddrinks on 30/04/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifndef RUBIXDREAM_RUBIXDREAM_H
#define RUBIXDREAM_RUBIXDREAM_H
//definitions

typedef enum{FRONT, BACK, UP, DOWN, RIGHT, LEFT }Type_SIDE;
typedef enum{W, O, G, R, B, Y, LG}T_COLOR;
typedef enum{Clockwise,Anticlockwise}T_SENSE;


//structures

struct FACE{
    Type_SIDE SIDE;
    T_COLOR BLOCK[3][3];
};

//functions headers

//Rubiks initialisation functions

struct FACE* CreateRubiks();
void init_rubiks(struct FACE* rubiks);

//Display functions

void display_rubiks(struct FACE* rubiks);
void display_line(struct FACE* rubiks, int face, int row);
void display_middleline(struct FACE* rubiks,int line_number);
void display_middleFaces(struct FACE* rubiks);
void display_singleFace(struct FACE* rubiks, int face);

//Rubiks manipulations functions

void blank_rubiks(struct FACE* rubiks);
void fill_rubiks(struct FACE* rubiks, int face,int row,int collumn, T_COLOR color);
void turn_face(struct FACE* rubiks, Type_SIDE Rotatedface,T_SENSE sense);
void turn_crown(struct FACE* rubiks, Type_SIDE Rotatedface,T_SENSE sense);
void turn_rubiks(struct FACE* rubiks,Type_SIDE face,T_SENSE sense);
void half_turn(struct FACE* rubiks,Type_SIDE Rface);

// structure manipulations fonction

int select_color(T_COLOR color);
char* select_caption(T_COLOR block_color);
int side_to_index(Type_SIDE face, struct FACE* rubiks);
void crown_namegiver(Type_SIDE* CRlist,Type_SIDE center_face);

// Solving Algorithms

void WhiteDaisy(struct FACE* rubiks);

// Free
void free_rubiks(struct FACE* rubiks);

//random function
void random_rubiks(struct FACE* rubik,int nbrmove);

#endif //RUBIXDREAM_RUBIXDREAM_H
