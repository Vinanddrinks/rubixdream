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

char* select_caption(T_COLOR block_color){
    switch(block_color){
        case R:
            return "R";
        case G:
            return "G";
        case B:
            return "B";
        case W:
            return "W";
        case Y:
            return "Y";
        case O:
            return "O";
        case LG:
            return "LG";
        default:
            break;
    }
}
void display_line(struct FACE* rubiks, int face, int row){
    for (int i = 0; i < 3; i++) {
        c_textcolor(select_color(rubiks[face].BLOCK[row][i]));
        printf("%s ", select_caption(rubiks[face].BLOCK[row][i]));
    }
}

void display_rubiks(struct FACE* rubiks) {
    rubiks[4].BLOCK[2][0] = R;
    display_line(rubiks, 4, 2);
}


