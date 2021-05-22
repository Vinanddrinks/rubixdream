//
// Created by vinanddrinks on 30/04/2021.
//
#include "rubixdream.h"
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"

// Initializing functions

struct FACE* CreateRubiks()
{
    struct FACE* Rubiks;
    Rubiks= calloc( 6, sizeof(struct FACE));
    return Rubiks;
}

void init_rubiks(struct FACE* rubiks) {
    T_COLOR color;
    rubiks[0].SIDE = UP;
    rubiks[1].SIDE = LEFT;
    rubiks[2].SIDE = FRONT;
    rubiks[3].SIDE = RIGHT;
    rubiks[4].SIDE = BACK;
    rubiks[5].SIDE = DOWN;
    for (int i = 0; i <= 5; i++) {
        color = W + i;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                rubiks[i].BLOCK[j][k] = color;
            }
        }
    }
}

// Select Functions

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
void crown_namegiver(Type_SIDE* CRlist,Type_SIDE center_face) {
    switch (center_face) {
        case UP:
            CRlist[0] = BACK, CRlist[1] = FRONT, CRlist[2] = LEFT, CRlist[3] = RIGHT;
            break;
        case DOWN:
            CRlist[0] = FRONT, CRlist[1] = BACK, CRlist[2] = LEFT, CRlist[3] = RIGHT;
            break;
        case LEFT:
            CRlist[0] = UP, CRlist[1] = DOWN, CRlist[2] = BACK, CRlist[3] = FRONT;
            break;
        case RIGHT:
            CRlist[0] = UP, CRlist[1] = DOWN, CRlist[2] = FRONT, CRlist[3] = BACK;
            break;
        case BACK:
            CRlist[0] = DOWN, CRlist[1] = UP, CRlist[2] = LEFT, CRlist[3] = RIGHT;
            break;
        case FRONT:
            CRlist[0] = UP, CRlist[1] = DOWN, CRlist[2] = LEFT, CRlist[3] = RIGHT;
            break;
        default:
            break;
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
            return "V";
        default:
            break;
    }
}

int side_to_index(Type_SIDE face,struct FACE* rubiks){

    for(int i = 0;i<=5;i++){
        if(rubiks[i].SIDE == face){
            return i;
        }
    }
}

// Display functions

void display_line(struct FACE* rubiks, int face, int row){
    for (int i = 0; i < 3; i++) {
        c_textcolor(select_color(rubiks[face].BLOCK[row][i]));
        printf("%s ", select_caption(rubiks[face].BLOCK[row][i]));
    }
}

void display_middleline(struct FACE* rubiks,int line_number){
    for(int i = 1;i<5;i++){
        display_line(rubiks ,i,line_number);
         printf("    ");
    }
    printf("\n");
}

void display_middleFaces(struct FACE* rubiks){
    for (int i = 0; i<3; i++){
        display_middleline(rubiks,i);
    }
    printf("\n");
}

void display_singleFace(struct FACE* rubiks, int face){
    for (int i = 0; i < 3; i++){
        printf("          ");
        display_line(rubiks, face, i);
        printf("\n");
    }
    printf("\n");
}

void display_rubiks(struct FACE* rubiks) {
    display_singleFace(rubiks, 0);
    display_middleFaces(rubiks);
    display_singleFace(rubiks, 5);
    c_textcolor(LIGHTGRAY);
}

// Rubiks customization

void blank_rubiks(struct FACE* rubiks){
    for (int face = 0; face <=5; face ++){
        for (int row = 0; row <3; row++){
            for (int line = 0; line<3; line++){
                if ((row != 1)||(line!=1)) {
                    rubiks[face].BLOCK[row][line] = LG;
                }
            }
        }
    }
}

void fill_rubiks(struct FACE* rubiks, int face,int row,int collumn, T_COLOR color){
    rubiks[face].BLOCK[row][collumn]=color;
}

// Movement funtions


void turn_face(struct FACE* rubiks, Type_SIDE Rotatedface,T_SENSE sense){
    struct FACE old_rubiks;
    old_rubiks = rubiks[side_to_index(Rotatedface,rubiks)];
    if (sense == Clockwise){
        for (int row = 0; row<3; row++) {
            for (int col = 0; col < 3; col++){
                rubiks[side_to_index(Rotatedface,rubiks)].BLOCK[col][2-row] = old_rubiks.BLOCK[row][col];
            }
        }

    }
    if(sense == Anticlockwise){
        for (int row = 0; row<3; row++) {
            for (int col = 0; col < 3; col++){
                rubiks[side_to_index(Rotatedface,rubiks)].BLOCK[2-col][row] = old_rubiks.BLOCK[row][col];
            }
        }
    }
}

void turn_crown(struct FACE* rubiks, Type_SIDE Rotatedface,T_SENSE sense){
    struct FACE old_rubiks[4];
    Type_SIDE* crowns_names;// crowns faces name in the following order 0: up 1: down 2: left 3: right
    crowns_names= calloc( 4, sizeof(Type_SIDE));
    crown_namegiver(crowns_names,Rotatedface);
    for(int i = 0; i<4;i++){
        old_rubiks[i] = rubiks[side_to_index(crowns_names[i],rubiks)];
    }

    if(sense == Clockwise){
        for(int i=0;i<3;i++){
            switch (Rotatedface) {
                default:
                    break;
                case UP:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[0][i] = old_rubiks[2].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[0][i] = old_rubiks[0].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[0][i] = old_rubiks[3].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[0][i] = old_rubiks[1].BLOCK[0][i];
                    break;
                case DOWN:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2][i] = old_rubiks[2].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[2][i] = old_rubiks[0].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[2][i] = old_rubiks[3].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[2][i] = old_rubiks[1].BLOCK[2][i];
                    break;
                case FRONT:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2][2-i] = old_rubiks[2].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[i][0] = old_rubiks[0].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[0][2-i] = old_rubiks[3].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[i][2] = old_rubiks[1].BLOCK[0][i];
                    break;
                case BACK:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2][i] = old_rubiks[2].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[2-i][2] = old_rubiks[0].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[0][i] = old_rubiks[3].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[2-i][0] = old_rubiks[1].BLOCK[0][i];
                    break;
                case LEFT:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2-i][0] = old_rubiks[2].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[i][0] = old_rubiks[0].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[i][0] = old_rubiks[3].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[2-i][2] = old_rubiks[1].BLOCK[i][0];
                    break;
                case RIGHT:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[i][2] = old_rubiks[2].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[2-i][0] = old_rubiks[0].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[2-i][2] = old_rubiks[3].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[i][2] = old_rubiks[1].BLOCK[i][2];
                    break;
            }
        }
    }
    if(sense == Anticlockwise){
        for(int i=0;i<3;i++){
            switch (Rotatedface) {
                default:
                    break;
                case UP:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[0][i] = old_rubiks[3].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[0][i] = old_rubiks[1].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[0][i] = old_rubiks[2].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[0][i] = old_rubiks[0].BLOCK[0][i];
                    break;
                case DOWN:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2][i] = old_rubiks[3].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[2][i] = old_rubiks[1].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[2][i] = old_rubiks[2].BLOCK[2][i];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[2][i] = old_rubiks[0].BLOCK[2][i];
                    break;
                case FRONT:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2][i] = old_rubiks[3].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[i][0] = old_rubiks[1].BLOCK[0][2-i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[0][i] = old_rubiks[2].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[i][2] = old_rubiks[0].BLOCK[2][2-i];
                    break;
                case BACK:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2][2-i] = old_rubiks[3].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[i][2] = old_rubiks[1].BLOCK[0][i];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[0][2-i] = old_rubiks[2].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[i][0] = old_rubiks[0].BLOCK[2][i];
                    break;
                case LEFT:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[i][0] = old_rubiks[3].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[i][0] = old_rubiks[1].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[2-i][0] = old_rubiks[2].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[2-i][2] = old_rubiks[0].BLOCK[i][0];
                    break;
                case RIGHT:
                    rubiks[side_to_index(crowns_names[0],rubiks)].BLOCK[2-i][2] = old_rubiks[3].BLOCK[i][0];
                    rubiks[side_to_index(crowns_names[3],rubiks)].BLOCK[2-i][0] = old_rubiks[1].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[1],rubiks)].BLOCK[i][2] = old_rubiks[2].BLOCK[i][2];
                    rubiks[side_to_index(crowns_names[2],rubiks)].BLOCK[i][2] = old_rubiks[0].BLOCK[i][2];
                    break;
            }
        }
    }
    free(crowns_names);


}
void turn_rubiks(struct FACE* rubiks,Type_SIDE face,T_SENSE sense){
    turn_face(rubiks,face,sense);
    turn_crown(rubiks,face,sense);

}

// Free rubiks

void free_rubiks(struct FACE* rubiks){
    free(rubiks);
}


