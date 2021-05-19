//
// Created by vinanddrinks on 30/04/2021.
//
#include "rubixdream.h"
#include "conio.h"
#include <stdio.h>

int main (){
    //c_textcolor(4);
    //printf("hello world\n");
    //c_textcolor(12);
    //printf("welcome to Rubixdream\n");
      struct FACE* Rubiks = CreateRubiks();
    init_rubiks(Rubiks);
//    if(Rubiks[2].BLOCK[0][0] == G){
//        printf("c'est bon");
//    }
//    printf("%s", select_caption(Rubiks[0].BLOCK[0][0]));
    display_rubiks(Rubiks);
    blank_rubiks(Rubiks);
    fill_rubiks(Rubiks,0,0,0,O);
    fill_rubiks(Rubiks,0,0,1,B);
    fill_rubiks(Rubiks,0,0,2,R);
    fill_rubiks(Rubiks,0,1,0,G);
    fill_rubiks(Rubiks,0,1,2,Y);
    fill_rubiks(Rubiks,0,2,0,O);
    fill_rubiks(Rubiks,0,2,1,B);
    fill_rubiks(Rubiks,0,2,2,R);

    fill_rubiks(Rubiks,1,0,0,O);
    fill_rubiks(Rubiks,1,0,1,O);
    fill_rubiks(Rubiks,1,0,2,O);

    fill_rubiks(Rubiks,2,0,0,G);
    fill_rubiks(Rubiks,2,0,1,G);
    fill_rubiks(Rubiks,2,0,2,G);

    fill_rubiks(Rubiks,3,0,0,R);
    fill_rubiks(Rubiks,3,0,1,R);
    fill_rubiks(Rubiks,3,0,2,R);

    fill_rubiks(Rubiks,4,0,0,B);
    fill_rubiks(Rubiks,4,0,1,B);
    fill_rubiks(Rubiks,4,0,2,B);

    fill_rubiks(Rubiks,1,2,0,O);
    fill_rubiks(Rubiks,1,2,1,O);
    fill_rubiks(Rubiks,1,2,2,O);

    fill_rubiks(Rubiks,2,2,0,G);
    fill_rubiks(Rubiks,2,2,1,G);
    fill_rubiks(Rubiks,2,2,2,G);

    fill_rubiks(Rubiks,3,2,0,R);
    fill_rubiks(Rubiks,3,2,1,R);
    fill_rubiks(Rubiks,3,2,2,R);

    fill_rubiks(Rubiks,4,2,0,B);
    fill_rubiks(Rubiks,4,2,1,B);
    fill_rubiks(Rubiks,4,2,2,B);

    fill_rubiks(Rubiks,5,0,0,O);
    fill_rubiks(Rubiks,5,0,1,B);
    fill_rubiks(Rubiks,5,0,2,R);
    fill_rubiks(Rubiks,5,1,0,G);
    fill_rubiks(Rubiks,5,1,2,Y);
    fill_rubiks(Rubiks,5,2,0,O);
    fill_rubiks(Rubiks,5,2,1,B);
    fill_rubiks(Rubiks,5,2,2,R);

    display_rubiks(Rubiks);
    turn_clockwise(Rubiks, UP);
    turn_clockwise(Rubiks, DOWN);
    display_rubiks(Rubiks);
    return 0;
}
