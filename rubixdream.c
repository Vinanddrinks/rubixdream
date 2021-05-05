//
// Created by vinanddrinks on 30/04/2021.
//
#include "rubixdream.h"
#include <stdio.h>
#include <stdlib.h>

struct FACE* CreateRubiks()
{
    struct FACE* Rubiks;
    Rubiks= calloc( 6, sizeof(struct FACE));
    return Rubiks;
}

