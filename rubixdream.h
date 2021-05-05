//
// Created by vinanddrinks on 30/04/2021.
//
#include <stdio.h>
#include <stdlib.h>
#ifndef RUBIXDREAM_RUBIXDREAM_H
#define RUBIXDREAM_RUBIXDREAM_H

typedef enum{FRONT, BACK,UP,DOWN,RIGHT,LEFT }T_SIDE;
typedef enum{R, B, G, W, Y, O, LG}T_COLOR;
struct FACE{
    T_SIDE SIDE;
    T_COLOR BLOCK[3][3];
};



#endif //RUBIXDREAM_RUBIXDREAM_H
