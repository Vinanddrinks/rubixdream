//
// Created by vinanddrinks on 30/04/2021.
//
#include "rubixdream.h"
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
struct FACE* CreateRubiks()
{
    struct FACE* Rubiks;
    Rubiks= calloc( 6, sizeof(struct FACE));
    return Rubiks;
}

int select_color(T_COLOR color){
    switch (color) {
        case R:
            return 12;
        case G:
            return 2;
        case B:
            return 1;
        case W:
            return 15;
        case Y:
            return 14;
        case O:
            return 4;
        case LG:
            return 7;
        default:
            break;
    }
}

int side_to_index(Type_SIDE face,struct FACE* rubiks){

    for(int i;i<=5;++i){
        if(rubiks[i].SIDE == face){
            return i;
        }
    }
}

void init_rubiks(struct FACE* rubiks) {
    T_COLOR color;
    rubiks[0].SIDE = UP;
    rubiks[1].SIDE = LEFT;
    rubiks[2].SIDE = FRONT;
    rubiks[3].SIDE = RIGHT;
    rubiks[4].SIDE = BACK;
    rubiks[5].SIDE = DOWN;
    for (int i = 0; i <= 5; ++i) {
        color = W + i;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                rubiks[i].BLOCK[j][k] = color;
            }
        }
    }
}

void display_rubiks(struct FACE* rubiks){
    for (int i = 0; i<=3; i++){
        c_textcolor(select_color(rubiks[0].BLOCK[0][i]));
        printf("%s", rubiks[0].BLOCK[0][i]);
    }
}


