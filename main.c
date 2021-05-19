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
    if(Rubiks[0].BLOCK[0][0] == W){
        printf("c'est bon");
    }
    display_rubiks(Rubiks);
    return 0;

}
