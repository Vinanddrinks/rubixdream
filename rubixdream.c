//
// Created by vinanddrinks on 30/04/2021.
//
#include "rubixdream.h"
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <time.h>

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
int opposite_index(int Face){
    switch (Face) {
        case 0:
            return 5;
        case 5:
            return 0;
        case 1:
            return 3;
        case 3:
            return 1;
        case 2:
            return 4;
        case 4:
            return 2;
        default:
            break;
    }
}

int left_index(int Face){
        switch (Face) {
            case 0:
                return 1;
            case 5:
                return 1;
            case 1:
                return 4;
            case 3:
                return 2;
            case 2:
                return 1;
            case 4:
                return 3;
            default:
                break;


        }
}
int right_index(int Face){
    switch (Face) {
        case 0:
            return 3;
        case 5:
            return 3;
        case 1:
            return 2;
        case 3:
            return 4;
        case 2:
            return 3;
        case 4:
            return 1;
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
void half_turn(struct FACE* rubiks,Type_SIDE Rface){
    turn_rubiks(rubiks,Rface,Clockwise);
    turn_rubiks(rubiks,Rface,Clockwise);
}
void turn_rubiks(struct FACE* rubiks,Type_SIDE face,T_SENSE sense){
    turn_face(rubiks,face,sense);
    turn_crown(rubiks,face,sense);

}

// Solving Algorithms

// 1. White Daisy

void WhiteDaisy(struct FACE* rubiks) {
    int face_in_pos = 0;
    Type_SIDE orderedface[5]={LEFT,FRONT,RIGHT,BACK,UP};
    // Until all blocks are positioned in the dow face, forming the daisy, we repeat this algorithm
    do{
        // We place every white space that is in the middle of a row/col in position [1][0] of the face they're in
        // We check that by doing so we do not affect any already place in the down face white middle of row/col.
        for(int i = 0; i<5;i++){
            if(rubiks[side_to_index(orderedface[i],rubiks)].BLOCK[0][1]==W){
                if (orderedface[i]==LEFT){
                    while(rubiks[5].BLOCK[1][0]== W){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Anticlockwise);
                }else if (orderedface[i]==FRONT){
                    while(rubiks[5].BLOCK[0][1]== W){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Anticlockwise);
                }else if (orderedface[i]==RIGHT){
                    while(rubiks[5].BLOCK[1][2]== W){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Anticlockwise);
                }else if (orderedface[i]==BACK){
                    while(rubiks[5].BLOCK[2][1]== W){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Anticlockwise);
                }else{
                    turn_rubiks(rubiks,orderedface[i],Anticlockwise);

                }
            }
            if(rubiks[side_to_index(orderedface[i],rubiks)].BLOCK[1][2]==W){
                if(orderedface[i]==LEFT) {
                    while (rubiks[5].BLOCK[1][0] == W) {
                        turn_rubiks(rubiks, DOWN, Clockwise);
                    }half_turn(rubiks, orderedface[i]);
                }else if(orderedface[i] == FRONT){
                    while (rubiks[5].BLOCK[0][1] == W ){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }half_turn(rubiks, orderedface[i]);
                }else if(orderedface[i] == RIGHT){
                    while (rubiks[5].BLOCK[1][2] == W ){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }half_turn(rubiks, orderedface[i]);
                }else if(orderedface[i] == BACK){
                    while (rubiks[5].BLOCK[2][1] == W ){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }half_turn(rubiks, orderedface[i]);
                }else{
                    half_turn(rubiks, orderedface[i]);
                }
            }
            if(rubiks[side_to_index(orderedface[i],rubiks)].BLOCK[2][1]==W){
                if (orderedface[i] == LEFT){
                    while (rubiks[5].BLOCK[1][0] == W) {
                        turn_rubiks(rubiks, DOWN, Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Clockwise);
                }else if (orderedface[i] == FRONT){
                    while (rubiks[5].BLOCK[0][1] == W ){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Clockwise);
                }else if (orderedface[i] == RIGHT){
                    while (rubiks[5].BLOCK[1][2] == W ){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Clockwise);
                }else if (orderedface[i] == BACK){
                    while (rubiks[5].BLOCK[2][1] == W ){
                        turn_rubiks(rubiks,DOWN,Clockwise);
                    }turn_rubiks(rubiks,orderedface[i],Clockwise);
                }else{
                    turn_rubiks(rubiks,orderedface[i],Clockwise);
                }
            }
        }
        // Now we can just rotate the face to the left of the placed white middle row/col clockwise to place them in
        // the down face. If the position they are going to take is already taken, we rotate the down face until there
        // is a free space for them.
        if (rubiks[0].BLOCK[1][0] == W){
            while (rubiks[5].BLOCK[1][0] == W ){
                turn_rubiks(rubiks,DOWN,Clockwise);
            }
            half_turn(rubiks,LEFT);
        }

        if (rubiks[1].BLOCK[1][0] == W){
            while (rubiks[5].BLOCK[2][1] == W ){
                turn_rubiks(rubiks,DOWN,Clockwise);
            }
            turn_rubiks(rubiks,BACK,Clockwise);
        }
        if (rubiks[2].BLOCK[1][0] == W){
            while (rubiks[5].BLOCK[1][0] == W ){
                turn_rubiks(rubiks,DOWN,Clockwise);
            }
            turn_rubiks(rubiks,LEFT,Clockwise);
        }

        if (rubiks[3].BLOCK[1][0] == W){
            while (rubiks[5].BLOCK[0][1] == W){
                turn_rubiks(rubiks,DOWN,Clockwise);
            }
            turn_rubiks(rubiks,FRONT,Clockwise);

        }

        if (rubiks[4].BLOCK[1][0] == W){
            while (rubiks[5].BLOCK[1][2] == W ){
                turn_rubiks(rubiks,DOWN,Clockwise);
            }
            turn_rubiks(rubiks,RIGHT,Clockwise);

        }
        face_in_pos = 0;
        for (int i =0; i<3; i++){
            for (int j = 0; j<3; j++){
                if ((rubiks[5].BLOCK[i][j] == W) && ((i == 1)||(j==1))){
                    face_in_pos++;
                }
            }
        }
    }while(face_in_pos != 4);
}

// 2. White Cross

void WhiteCross(struct FACE* rubiks){
    int face_in_pos = 0;
    int down_coo[4][2] = {{1,0},{0,1},{1,2},{2,1}};
    do{
        for (int face=1; face <5; face++){
            if ((rubiks[face].BLOCK[2][1]==rubiks[face].BLOCK[1][1])&&(rubiks[5].BLOCK[down_coo[face-1][0]][down_coo[face-1][1]]== W)){
                half_turn(rubiks, rubiks[face].SIDE);
            }
        }
        turn_rubiks(rubiks, DOWN, Clockwise);
        face_in_pos = 0;
        for (int i =0; i<3; i++){
            for (int j = 0; j<3; j++){
                if ((rubiks[0].BLOCK[i][j] == W) && ((i == 1)||(j==1))){
                    face_in_pos++;
                }
            }
        }
    }while(face_in_pos != 5);
}

Boolean WhiteCrownDone (struct FACE* rubiks){
    int count=0;
    for (int i = 1; i<5; i++){
        for (int col = 0; col  <3 ; col ++){
            if (rubiks[i].BLOCK[0][col] == rubiks[i].BLOCK[1][1]){
                count++;
            }
        }
    }
    if (count==12){
        return True;
    }else{
        return False;
    }
}

Boolean FaceDone(struct FACE* rubiks,Type_SIDE face) {
    int count = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (rubiks[side_to_index(face, rubiks)].BLOCK[1][1] == rubiks[side_to_index(face, rubiks)].BLOCK[x][y]) {
                ++count;
            }
        }
    }
    if (count == 9) {
        return True;
    } else {
        return False;
    }
}


// 3. First Crown

void FirstCrown(struct FACE* rubiks) {
    Type_SIDE left[4] = {BACK,LEFT,FRONT,RIGHT};
    Type_SIDE right[4] = {FRONT,RIGHT,BACK,LEFT};
    Type_SIDE front[4] = {LEFT,FRONT,RIGHT,BACK};
    Type_SIDE adj_face[4] = {LEFT, BACK, RIGHT, FRONT};

    int cnst;
    //check for all corner where white stickers are on the white edge
    do {
        cnst=1;
        if (rubiks[5].BLOCK[0][0] == W) {
            if (rubiks[2].BLOCK[2][0] == G && rubiks[1].BLOCK[2][2] == R) {
                turn_rubiks(rubiks, DOWN, Clockwise);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,RIGHT);
            }
            if (rubiks[2].BLOCK[2][0] == R && rubiks[1].BLOCK[2][2] == B) {
                half_turn(rubiks, DOWN);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,BACK);
            }
            if (rubiks[2].BLOCK[2][0] == B && rubiks[1].BLOCK[2][2] == O) {
                turn_rubiks(rubiks, DOWN, Anticlockwise);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,LEFT);
            }
            if (rubiks[2].BLOCK[2][0] == O && rubiks[1].BLOCK[2][2] == G){
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,FRONT);
            }
        }
        if (rubiks[5].BLOCK[0][2] == W) {
            if (rubiks[3].BLOCK[2][0] == G && rubiks[2].BLOCK[2][2] == R) {
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,RIGHT);
            }
            if (rubiks[3].BLOCK[2][0] == R && rubiks[2].BLOCK[2][2] == B) {
                turn_rubiks(rubiks, DOWN, Clockwise);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,BACK);
            }
            if (rubiks[3].BLOCK[2][0] == B && rubiks[2].BLOCK[2][2] == O) {
                half_turn(rubiks, DOWN);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,LEFT);
            }
            if (rubiks[3].BLOCK[2][0] == O && rubiks[2].BLOCK[2][2] == G) {
                turn_rubiks(rubiks, DOWN, Anticlockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,FRONT);
            }
        }
        if (rubiks[5].BLOCK[2][2] == W) {
            if (rubiks[4].BLOCK[2][0] == G && rubiks[3].BLOCK[2][2] == R) {
                turn_rubiks(rubiks, DOWN, Anticlockwise);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,RIGHT);
            }
            if (rubiks[4].BLOCK[2][0] == R && rubiks[3].BLOCK[2][2] == B) {
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,BACK);
            }
            if (rubiks[4].BLOCK[2][0] == B && rubiks[3].BLOCK[2][2] == O) {
                half_turn(rubiks, DOWN);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,LEFT);
            }
            if (rubiks[4].BLOCK[2][0] == O && rubiks[3].BLOCK[2][2] == G) {
                turn_rubiks(rubiks, DOWN, Clockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,FRONT);
            }
        }
        if (rubiks[5].BLOCK[2][0] == W) {
            if (rubiks[1].BLOCK[2][0] == G && rubiks[4].BLOCK[2][2] == R) {
                half_turn(rubiks, DOWN);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,RIGHT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,RIGHT);
            }
            if (rubiks[1].BLOCK[2][0] == R && rubiks[4].BLOCK[2][2] == B) {
                turn_rubiks(rubiks, DOWN, Anticlockwise);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,BACK);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,BACK);
            }
            if (rubiks[1].BLOCK[2][0] == B && rubiks[4].BLOCK[2][2] == O) {
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,LEFT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,LEFT);
            }
            if (rubiks[1].BLOCK[2][0] == O && rubiks[4].BLOCK[2][2] == G) {
                turn_rubiks(rubiks, DOWN, Clockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Anticlockwise);
                half_turn(rubiks,FRONT);
                turn_rubiks(rubiks,DOWN,Clockwise);
                half_turn(rubiks,FRONT);
            }
        }
        //Now we check the left and right cases
        //Left case:
        for(int facel = 1; facel<5;facel++){
            if(rubiks[facel].BLOCK[2][2]==W){
                if(rubiks[side_to_index(right[facel-1],rubiks)].BLOCK[2][0] == rubiks[side_to_index(right[facel-1],rubiks)].BLOCK[1][1]){
                    turn_rubiks(rubiks,front[facel-1],Clockwise);
                    turn_rubiks(rubiks,DOWN,Clockwise);
                    turn_rubiks(rubiks,front[facel-1],Anticlockwise);

                }else turn_rubiks(rubiks,DOWN,Clockwise),cnst=0;
            }
        }
        //Right case:
        for(int facer = 1; facer<5;facer++){
            if(rubiks[facer].BLOCK[2][0]==W) {
                if (rubiks[side_to_index(left[facer - 1], rubiks)].BLOCK[2][2] ==
                    rubiks[side_to_index(left[facer - 1], rubiks)].BLOCK[1][1]) {
                    turn_rubiks(rubiks, front[facer - 1], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Anticlockwise);
                    turn_rubiks(rubiks, front[facer - 1], Clockwise);
                } else if (cnst == 1) {
                    turn_rubiks(rubiks, DOWN, Clockwise);
                }
            }
        }
        //Case white stuck on top of sideface:
        for(int i =1; i<5; i++){
            if (rubiks[i].BLOCK[0][0] == W){
                turn_rubiks(rubiks, rubiks[i].SIDE,Anticlockwise);
                turn_rubiks(rubiks,DOWN,Clockwise);
                turn_rubiks(rubiks,rubiks[i].SIDE,Clockwise);
            }
            if (rubiks[i].BLOCK[0][2] == W){
                turn_rubiks(rubiks, rubiks[i].SIDE,Clockwise);
                turn_rubiks(rubiks,DOWN,Clockwise);
                turn_rubiks(rubiks,rubiks[i].SIDE,Anticlockwise);
            }
        }
        // If the face is done but the crown is wrong (misplaced white corners)
        if((FaceDone(rubiks, UP) == True) && (WhiteCrownDone(rubiks) == False)){
            for (int i=0; i<4; i++){
                if (rubiks[side_to_index( adj_face[i],rubiks)].BLOCK[0][0] != rubiks[side_to_index( adj_face[i],rubiks)].BLOCK[1][1]){
                    if ( (i==0)  || (i==3)){
                        turn_rubiks(rubiks, adj_face[i], Anticlockwise);
                        turn_rubiks(rubiks,DOWN,Clockwise);
                        turn_rubiks(rubiks, adj_face[i], Clockwise);
                    }
                    if ((i==1)|| (i==2)) {
                        turn_rubiks(rubiks, adj_face[i], Clockwise);
                        turn_rubiks(rubiks,DOWN,Clockwise);
                        turn_rubiks(rubiks, adj_face[i], Anticlockwise);
                    }
                }
            }
        }
    }while ((FaceDone(rubiks, UP) == False) || (WhiteCrownDone(rubiks) == False));
}

// 4. Second Crown

Boolean SecondCrownDone(struct FACE* rubiks){
    int count=0;
    for (int i = 1; i<5; i++){
        if (rubiks[i].BLOCK[1][0] == rubiks[i].BLOCK[1][1]){
            count ++;
        }
        if (rubiks[i].BLOCK[1][2] == rubiks[i].BLOCK[1][1]){
            count ++;
        }
    }
    if (count==8){
        return True;
    }else{
        return False;
    }
}

void SecondCrown(struct FACE* rubiks){
    int coord_down[4][2] = {{1,0},{0,1},{1,2},{2,1}}; // Coordinates of the blocks in the yellow face from left to back
    Type_SIDE left[4] = {BACK,LEFT,FRONT,RIGHT};
    Type_SIDE right[4] = {FRONT,RIGHT,BACK,LEFT};
    Type_SIDE front[4] = {LEFT,FRONT,RIGHT,BACK};
    Type_SIDE back[4] = {RIGHT, BACK, LEFT, FRONT};
    int unstuck1_2p = 0, unstuck3_4p = 0;
    do{
        unstuck1_2p = 0,unstuck3_4p = 0;
        // We place the blocks we can on the crown
        for (int face = 1 ; face <5; face ++){
           for(int i=0; i<4; i++){
               if (rubiks[face].BLOCK[2][1] == rubiks[face].BLOCK[1][1]){
                   if (rubiks[5].BLOCK[coord_down[0][0]][coord_down[0][1]] != Y){
                       if(face == 1){
                           //bring it to right
                           if (rubiks[5].BLOCK[coord_down[0][0]][coord_down[0][1]] == G){
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, left[2], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, left[2], Clockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, left[1], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, left[1], Anticlockwise);
                           }
                           //bring it to left
                           if (rubiks[5].BLOCK[coord_down[0][0]][coord_down[0][1]] == B){
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, left[0], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, left[0], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, left[1], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, left[1], Clockwise);
                           }
                       }
                       if (face == 2){
                           // Bring it to right
                           if (rubiks[5].BLOCK[coord_down[1][0]][coord_down[1][1]] == R){
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, front[2], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, front[2], Clockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, front[1], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, front[1], Anticlockwise);
                           }
                           // Bring it to left
                           if (rubiks[5].BLOCK[coord_down[1][0]][coord_down[1][1]] == O){
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, front[0], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, front[0], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, front[1], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, front[1], Clockwise);
                           }
                       }
                       if (face == 3){
                           // Bring it to right
                           if (rubiks[5].BLOCK[coord_down[2][0]][coord_down[2][1]] == B){
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, right[2], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, right[2], Clockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, right[1], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, right[1], Anticlockwise);
                           }
                           // Bring it to left
                           if (rubiks[5].BLOCK[coord_down[2][0]][coord_down[2][1]] == G){
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, right[0], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, right[0], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, right[1], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, right[1], Clockwise);
                           }
                       }
                       if (face == 4){
                           // Bring it to right
                           if (rubiks[5].BLOCK[coord_down[3][0]][coord_down[3][1]] == O){
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, back[2], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, back[2], Clockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, back[1], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, back[1], Anticlockwise);
                           }
                           // Bring it to left
                           if (rubiks[5].BLOCK[coord_down[3][0]][coord_down[3][1]] == R){
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, back[0], Clockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, back[0], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Anticlockwise);
                               turn_rubiks(rubiks, back[1], Anticlockwise);
                               turn_rubiks(rubiks, DOWN, Clockwise);
                               turn_rubiks(rubiks, back[1], Clockwise);
                           }
                       }
                   }
               }
               turn_rubiks(rubiks, DOWN, Clockwise);
           }
        }
        // Case it is badly placed and place them in the pos (2,1) to place it using the next algorithm
        for (int face = 1; face<5; face++){
            if (rubiks[face].BLOCK[1][2] != rubiks[face].BLOCK[1][1]){
                if (face == 1){
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, left[2],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, left[2],Clockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, left[1],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, left[1],Anticlockwise);
                    unstuck1_2p = 1;
                }
                if (face == 2){
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, front[2],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, front[2],Clockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, front[1],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, front[1],Anticlockwise);

                }
                if (face == 3 && unstuck1_2p == 0){
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, right[2],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, right[2],Clockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, right[1],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, right[1],Anticlockwise);
                    unstuck3_4p = 1;

                }
                if (face == 4){
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, back[2],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, back[2],Clockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, back[1],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, back[1],Anticlockwise);

                }
            }
        }

        // We placed the blocks we moved above

        for (int face = 1 ; face <5; face ++){
            for(int i=0; i<4; i++){
                if (rubiks[face].BLOCK[2][1] == rubiks[face].BLOCK[1][1]){
                    if (rubiks[5].BLOCK[coord_down[0][0]][coord_down[0][1]] != Y){
                        if(face == 1){
                            //bring it to right
                            if (rubiks[5].BLOCK[coord_down[0][0]][coord_down[0][1]] == G){
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, left[2], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, left[2], Clockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, left[1], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, left[1], Anticlockwise);
                            }
                            //bring it to left
                            if (rubiks[5].BLOCK[coord_down[0][0]][coord_down[0][1]] == B){
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, left[0], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, left[0], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, left[1], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, left[1], Clockwise);
                            }
                        }
                        if (face == 2){
                            // Bring it to right
                            if (rubiks[5].BLOCK[coord_down[1][0]][coord_down[1][1]] == R){
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, front[2], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, front[2], Clockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, front[1], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, front[1], Anticlockwise);
                            }
                            // Bring it to left
                            if (rubiks[5].BLOCK[coord_down[1][0]][coord_down[1][1]] == O){
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, front[0], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, front[0], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, front[1], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, front[1], Clockwise);
                            }
                        }
                        if (face == 3){
                            // Bring it to right
                            if (rubiks[5].BLOCK[coord_down[2][0]][coord_down[2][1]] == B){
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, right[2], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, right[2], Clockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, right[1], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, right[1], Anticlockwise);
                            }
                            // Bring it to left
                            if (rubiks[5].BLOCK[coord_down[2][0]][coord_down[2][1]] == G){
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, right[0], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, right[0], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, right[1], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, right[1], Clockwise);
                            }
                        }
                        if (face == 4){
                            // Bring it to right
                            if (rubiks[5].BLOCK[coord_down[3][0]][coord_down[3][1]] == O){
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, back[2], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, back[2], Clockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, back[1], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, back[1], Anticlockwise);
                            }
                            // Bring it to left
                            if (rubiks[5].BLOCK[coord_down[3][0]][coord_down[3][1]] == R){
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, back[0], Clockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, back[0], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Anticlockwise);
                                turn_rubiks(rubiks, back[1], Anticlockwise);
                                turn_rubiks(rubiks, DOWN, Clockwise);
                                turn_rubiks(rubiks, back[1], Clockwise);
                            }
                        }
                    }
                }
                turn_rubiks(rubiks, DOWN, Clockwise);
            }
        }
        // We replace the blocks that are not placed correctly
        for (int face = 1; face <5 ; face ++){
            if (rubiks[face].BLOCK[1][0] == Y){
                if (face == 1){
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, left[0],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, left[0],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, left[1],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, left[1],Clockwise);
                    unstuck1_2p = 1;
                }
                if (face == 2 && unstuck1_2p == 0){
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, front[0],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, front[0],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, front[1],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, front[1],Clockwise);

                }
                if (face == 3){
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, right[0],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, right[0],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, right[1],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, right[1],Clockwise);
                    unstuck3_4p = 1;

                }
                if (face == 4  && unstuck3_4p == 0){
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, back[0],Clockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, back[0],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Anticlockwise);
                    turn_rubiks(rubiks, back[1],Anticlockwise);
                    turn_rubiks(rubiks, DOWN,Clockwise);
                    turn_rubiks(rubiks, back[1],Clockwise);

                }
            }
        }
        display_rubiks(rubiks);
    }while(SecondCrownDone(rubiks)==False);
}


// 5. Yellow Cross

Boolean YellowCrossDone(struct FACE* rubiks) {
    if ((rubiks[5].BLOCK[0][1] == Y) && (rubiks[5].BLOCK[1][0]==Y) && (rubiks[5].BLOCK[1][2]==Y) && (rubiks[5].BLOCK[2][1] == Y)){
        return True;
    }
    return False;
}
Boolean YellowL(struct FACE* rubiks){

    if ((rubiks[5].BLOCK[0][1] == Y && rubiks[5].BLOCK[1][0] == Y)){
            return True;
    }
    return False;
}

Boolean YellowLine(struct FACE* rubiks){
    if ((rubiks[5].BLOCK[0][1] == Y && rubiks[5].BLOCK[2][1] == Y) ||(rubiks[5].BLOCK[1][0] == Y && rubiks[5].BLOCK[1][2] == Y)  ){
        return True;
    }
    return False;
}

void YellowCross(struct FACE* rubiks) {
    do{
        // Case we only have a dot
        if (YellowL(rubiks)==False && YellowLine(rubiks) == False) {
            do {
                turn_rubiks(rubiks, FRONT, Clockwise);
                turn_rubiks(rubiks, LEFT, Clockwise);
                turn_rubiks(rubiks, DOWN, Clockwise);
                turn_rubiks(rubiks, LEFT, Anticlockwise);
                turn_rubiks(rubiks, DOWN, Anticlockwise);
                turn_rubiks(rubiks, FRONT, Anticlockwise);

                for (int test = 0; test < 4; test++) {
                    if (YellowL(rubiks) == False && YellowLine(rubiks) == False) {
                        turn_rubiks(rubiks, DOWN, Clockwise);
                    }
                }

            } while (YellowL(rubiks) == False && YellowLine(rubiks) == False);
        }
        // Case we have a yellow L
        if (YellowLine(rubiks) == False){
            turn_rubiks(rubiks, FRONT, Clockwise);
            turn_rubiks(rubiks, LEFT, Clockwise);
            turn_rubiks(rubiks, DOWN, Clockwise);
            turn_rubiks(rubiks, LEFT, Anticlockwise);
            turn_rubiks(rubiks, DOWN, Anticlockwise);
            turn_rubiks(rubiks, FRONT, Anticlockwise);
        }
        // Case we have a line
        if (YellowCrossDone(rubiks) == False){
            if ((rubiks[5].BLOCK[0][1] == Y)  && (rubiks[5].BLOCK[2][1] == Y)){
                turn_rubiks(rubiks, DOWN, Clockwise);
            }
            turn_rubiks(rubiks, FRONT, Clockwise);
            turn_rubiks(rubiks, LEFT, Clockwise);
            turn_rubiks(rubiks, DOWN, Clockwise);
            turn_rubiks(rubiks, LEFT, Anticlockwise);
            turn_rubiks(rubiks, DOWN, Anticlockwise);
            turn_rubiks(rubiks, FRONT, Anticlockwise);
        }

    }while(YellowCrossDone(rubiks) == False);
}

// 6. Yellow Edges

Boolean YellowEdgesDone(struct FACE* rubiks){
    if ( (rubiks[1].BLOCK[2][1] == O) && (rubiks[2].BLOCK[2][1] == G) && (rubiks[3].BLOCK[2][1] == R) && (rubiks[4].BLOCK[2][1] == B)){
        return True;
    }
    return False;
}

int howManyEdgesInPos(struct FACE* rubiks){
    // This function checks how many edges are in position and places the yellow face such that the most yellow edges are in place
    int edge_in_pos = 0, max;
    max = edge_in_pos;
    for (int test = 0; test <4; test++){
        edge_in_pos = 0;
        for (int i = 1; i<5; i++) {
            if (rubiks[i].BLOCK[2][1] == rubiks[i].BLOCK[1][1]) {
                edge_in_pos++;
            }
        }
        if (edge_in_pos>max){
            max = edge_in_pos;
        }
        turn_rubiks(rubiks, DOWN, Clockwise);
    }
    edge_in_pos = 0;
    while(edge_in_pos != max){
        turn_rubiks(rubiks, DOWN, Clockwise);
        edge_in_pos = 0;
        for (int i = 1; i<5; i++) {
            if (rubiks[i].BLOCK[2][1] == rubiks[i].BLOCK[1][1]) {
                edge_in_pos++;
            }
        }
    }
    return max;
}

void YellowEdges(struct FACE* rubiks) {
    Type_SIDE left[4] = {BACK,LEFT,FRONT,RIGHT};
    Type_SIDE right[4] = {FRONT,RIGHT,BACK,LEFT};
    Type_SIDE front[4] = {LEFT,FRONT,RIGHT,BACK};
    Type_SIDE back[4] = {LEFT, BACK, RIGHT, FRONT};
    int in_pos;
    in_pos = howManyEdgesInPos(rubiks);
    do{
        for (int face = 1; face < 5; face ++) {
            if (rubiks[face].BLOCK[2][1] == rubiks[opposite_index(face)].BLOCK[1][1]){
                if (face == 1){
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
                if (face == 2){
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
                if (face == 3){
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
                if (face == 4){
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[2], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[2], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[3], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[3], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                }
            }
        }
        in_pos = howManyEdgesInPos(rubiks);
        for (int face = 1; face < 5; face++){
            if (rubiks[face].BLOCK[2][1] == rubiks[right_index(face)].BLOCK[1][1]){
                if (face == 1){
                    turn_rubiks(rubiks, left[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, left[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
                if (face == 2){
                    turn_rubiks(rubiks, front[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, front[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
                if (face == 3) {
                    turn_rubiks(rubiks, right[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, right[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
                if (face == 4){
                    turn_rubiks(rubiks, back[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[0], Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);
                    turn_rubiks(rubiks, back[0], Anticlockwise);
                    turn_rubiks(rubiks, DOWN, Clockwise);

                }
            }
        }
        in_pos = howManyEdgesInPos(rubiks);
    }while(YellowEdgesDone(rubiks)==False);
}

// Yellow Corners
Boolean corner_in_place(struct FACE* rubiks, int face){
    if(face == 1){
        if (((rubiks[face].BLOCK[2][0] == rubiks[left_index(face)].BLOCK[1][1]) || (rubiks[face].BLOCK[2][0] == rubiks[face].BLOCK[1][1])) && ((rubiks[left_index(face)].BLOCK[2][2] == rubiks[face].BLOCK[1][1]) || (rubiks[left_index(face)].BLOCK[2][2] == rubiks[left_index(face)].BLOCK[1][1])) && ((rubiks[5].BLOCK[2][0] == rubiks[face].BLOCK[1][1]) || (rubiks[5].BLOCK[2][0] == rubiks[left_index(face)].BLOCK[1][1]))){
            return True;
        }
    }
    if (face == 2){
        if (((rubiks[face].BLOCK[2][0] == rubiks[left_index(face)].BLOCK[1][1]) || (rubiks[face].BLOCK[2][0] == rubiks[face].BLOCK[1][1])) && ((rubiks[left_index(face)].BLOCK[2][2] == rubiks[face].BLOCK[1][1]) || (rubiks[left_index(face)].BLOCK[2][2] == rubiks[left_index(face)].BLOCK[1][1])) && ((rubiks[5].BLOCK[0][0] == rubiks[face].BLOCK[1][1]) || (rubiks[5].BLOCK[0][0] == rubiks[left_index(face)].BLOCK[1][1]))){
            return True;
        }
    }
    if (face == 3){
        if (((rubiks[face].BLOCK[2][0] == rubiks[left_index(face)].BLOCK[1][1]) || (rubiks[face].BLOCK[2][0] == rubiks[face].BLOCK[1][1])) && ((rubiks[left_index(face)].BLOCK[2][2] == rubiks[face].BLOCK[1][1]) || (rubiks[left_index(face)].BLOCK[2][2] == rubiks[left_index(face)].BLOCK[1][1])) && ((rubiks[5].BLOCK[2][2] == rubiks[face].BLOCK[1][1]) || (rubiks[5].BLOCK[2][2] == rubiks[left_index(face)].BLOCK[1][1]))){
            return True;
        }
    }
    if (face == 4){
        if (((rubiks[face].BLOCK[2][0] == rubiks[left_index(face)].BLOCK[1][1]) || (rubiks[face].BLOCK[2][0] == rubiks[face].BLOCK[1][1])) && ((rubiks[left_index(face)].BLOCK[2][2] == rubiks[face].BLOCK[1][1]) || (rubiks[left_index(face)].BLOCK[2][2] == rubiks[left_index(face)].BLOCK[1][1])) && ((rubiks[5].BLOCK[0][2] == rubiks[face].BLOCK[1][1]) || (rubiks[5].BLOCK[0][2] == rubiks[left_index(face)].BLOCK[1][1]))){
            return True;
        }
    }
    return False;
}

void place_yellow_corners(struct FACE* rubiks){
    int placed_faces = 0;
    for (int face = 1; face <5; face ++){
        if (corner_in_place(rubiks, face) == True){
            placed_faces ++;
        }
    }
    printf("placed faces: %d\n", placed_faces);
}


// Free rubiks

void free_rubiks(struct FACE* rubiks){
    free(rubiks);
}
//random function
void random_rubiks(struct FACE* rubik,int nbrmove){
    Type_SIDE side;
    T_SENSE sense;
    srand(time(NULL));

    for(int i = 0; i < nbrmove; i ++){
        side = (Type_SIDE)(rand()%6);
        sense = (T_SENSE)(rand()%2);
        turn_rubiks(rubik,side,sense);
    }
}
