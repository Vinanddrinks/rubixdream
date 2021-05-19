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
    fill_rubiks(Rubiks,0,0,0,R);
    fill_rubiks(Rubiks,0,0,1,G);
    fill_rubiks(Rubiks,0,0,2,B);
    fill_rubiks(Rubiks,0,1,0,B);
    fill_rubiks(Rubiks,0,0,2,O);
    fill_rubiks(Rubiks,0,2,0,G);
    fill_rubiks(Rubiks,0,2,1,W);
    fill_rubiks(Rubiks,0,2,2,Y);
    turn_clockwise(Rubiks, UP);
    display_rubiks(Rubiks);
    return 0;
}
