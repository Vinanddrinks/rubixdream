//
// Created by vinanddrinks on 30/04/2021.
//
#include "rubixdream.h"
#include "conio.h"
#include <stdio.h>

void movement(struct FACE* rubiks){
    int face,type,sense;
    Type_SIDE Face[6] ={UP,LEFT,FRONT,RIGHT,BACK,DOWN};
    T_SENSE Sense[2] = {Clockwise,Anticlockwise};
    printf("___________________________________________________________________________________\n");
    printf("|1. UP | 2. LEFT | 3. FRONT | 4. RIGHT | 5. BACK | 6. DOWN\n");
    printf("___________________________________________________________________________________\n");
    do{scanf("%d",&face);}while(0>face || face > 6);
    printf("___________________________________________________________________________________\n");
    printf("|1. SINGLE | 2. HALF\n");
    printf("___________________________________________________________________________________\n");
    do{scanf("%d",&type);}while(0>type || type > 2);
    if(type == 1){
        printf("___________________________________________________________________________________\n");
        printf("|1. CLOCKWISE | 2. COUNTERCLOCKWISE\n");
        printf("___________________________________________________________________________________\n");
        do{scanf("%d",&sense);}while(0>sense || sense > 2);
        turn_rubiks(rubiks,Face[face-1],Sense[sense-1]);
    }else{
        half_turn(rubiks,Face[face-1]);
    }

}
void solve(struct FACE* rubiks){
    printf("_____________________________________________________________________________________________________\n");
    printf("WHITE DAISY\n");
    WhiteDaisy(rubiks);
    display_rubiks(rubiks);
    printf("_____________________________________________________________________________________________________\n");
    printf("WHITE CROSS\n");
    WhiteCross(rubiks);
    display_rubiks(rubiks);
    printf("_____________________________________________________________________________________________________\n");
    printf("First Crown\n");
    FirstCrown(rubiks);
    display_rubiks(rubiks);
    printf("_____________________________________________________________________________________________________\n");
    printf("Second Crown\n");
    SecondCrown(rubiks);
    display_rubiks(rubiks);
    printf("_____________________________________________________________________________________________________\n");
    printf("Second Crown\n");
    SecondCrown(rubiks);
    display_rubiks(rubiks);
    printf("_____________________________________________________________________________________________________\n");
    printf("Yellow Cross\n");
    YellowCross(rubiks);
    display_rubiks(rubiks);
    printf("_____________________________________________________________________________________________________\n");
    printf("Yellow Face\n");
    YellowEdges(rubiks);
    display_rubiks(rubiks);

}
void fill(struct FACE* rubiks){
    int faces,row,col,color;
    T_COLOR Color[6] ={W,O,G,R,B,Y};
    printf("___________________________________________________________________________________\n");
    printf("|1. UP | 2. LEFT | 3. FRONT | 4. RIGHT | 5. BACK | 6. DOWN\n");
    printf("___________________________________________________________________________________\n");
    do{scanf("%d",&faces);}while(0>faces || faces > 6);
    printf("___________________________________________________________________________________\n");
    printf("|1. White | 2. Orange | 3. Green | 4. Red | 5. Blue | 6. Yellow\n");
    printf("___________________________________________________________________________________\n");
    do{scanf("%d",&color);}while(0>color || color > 6);
    printf("___________________________________________________________________________________\n");
    printf("Enter the row (0 --> 2)\n");
    printf("___________________________________________________________________________________\n");
    do{scanf("%d",&row);}while(-1>row || row > 2);
    printf("___________________________________________________________________________________\n");
    printf("Enter the column (0 --> 2)\n");
    printf("___________________________________________________________________________________\n");
    do{scanf("%d",&col);}while(-1>col || col > 2);
    fill_rubiks(rubiks,(faces -1),row,col,Color[color -1]);

}





int main (){
    c_textcolor(4);
    printf("Hello World !\n");
    c_textcolor(12);
    printf("welcome to Rubixdream\n");
    c_textcolor(LIGHTGRAY);
    struct FACE* Rubiks = CreateRubiks();
    init_rubiks(Rubiks);
    Boolean run = True,first = True;
    int opval = 0, rand;
    do{
        if(first == True) {
            printf("___________________________________________________________________________________________________________\n");
            printf("Welcome in the software RubixDream you can do operation by inputting their ID number as they appear\n");
            printf("___________________________________________________________________________________________________________\n");
            first = False;
        }
        printf("MENU display\n");
        display_rubiks(Rubiks);
        printf("______________________________________________________________________________________________________________________\n_______________________\n");
        printf("|1. Do a Rotation | 2. Blank The Rubik's | 3.quit | 4. Fill a case (can break rubik's) | 5. solve | 6. reset rubik's |\n7. shuffle the rubik's\n");
        printf("______________________________________________________________________________________________________________________\n_______________________\n");
        do {
            scanf("%d",&opval);
        } while (0 > opval || opval > 8);
        switch (opval) {
            case 1:
                movement(Rubiks);
                break;
            case 2:
                blank_rubiks(Rubiks);
                break;
            case 3:
                printf("Goodbye World !");
                run = False;
                break;
            case 4:
                fill(Rubiks);
                break;
            case 5:
                solve(Rubiks);
                break;
            case 6:
                init_rubiks(Rubiks);
                break;
            case 7:
                printf("____________________________________________________________________________\n");
                printf("|Enter the number of random rotation you want|\n");
                printf("____________________________________________________________________________\n");
                do{scanf("%d",&rand);}while(0>rand);
                random_rubiks(Rubiks,rand);
                break;
            default:
                break;


        }
    }while(run == True);

    return 0;
}
