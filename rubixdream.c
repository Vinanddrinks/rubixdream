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
    for (int i = 0; i <= 5; ++i) {
        color = W + i;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
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

    for(int i;i<=5;++i){
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

void turn_clockwise(struct FACE* rubiks, Type_SIDE Rotatedface){
    struct FACE old_rubiks, old_rubiks_bis;
    switch(Rotatedface){
        case UP:
            // rotating the values inside the main face
            old_rubiks = rubiks[0];
            for (int row = 0; row<3; row++) {
                for (int col = 0; col < 3; col++){
                    rubiks[0].BLOCK[col][2-row] = old_rubiks.BLOCK[row][col];
                }
            }
            // rotating the other faces that also turn with the front
            old_rubiks_bis = rubiks[1];
            for (int face = 1; face <5; face++){
              for (int col = 0; col < 3; col++){
                  if (face+1 != 5){
                      old_rubiks = rubiks[face+1];
                      rubiks[face].BLOCK[0][col] = old_rubiks.BLOCK[0][col];
                  }
                  if (face+1 == 5){
                      rubiks[face].BLOCK[0][col] = old_rubiks_bis.BLOCK[0][col];
                  }
              }
          }

        case LEFT:
            break;
        case FRONT:
            break;
        case RIGHT:
            break;
        case DOWN:
            // rotating the values inside the main face
            old_rubiks = rubiks[5];
            for (int row = 0; row<3; row++) {
                for (int col = 0; col < 3; col++){
                    rubiks[5].BLOCK[col][2-row] = old_rubiks.BLOCK[row][col];
                }
            }
            // rotating the other faces that also turn with the front
            old_rubiks_bis = rubiks[4];
            for (int face = 4; face >= 1; face--){
                for (int col = 0; col < 3; col++){
                    if (face != 1){
                        old_rubiks = rubiks[face-1];
                        rubiks[face].BLOCK[2][col] = old_rubiks.BLOCK[2][col];
                    }
                    if (face == 1){
                        rubiks[face].BLOCK[2][col] = old_rubiks_bis.BLOCK[2][col];
                    }
                }
            }
        case BACK:
            break;
        default:
            break;
    }
}




// Free rubiks

void free_rubiks(struct FACE* rubiks){
    free(rubiks);
}


