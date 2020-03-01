/*
 constain.h
 
 Luong Duc Duong
 
 define constain use in program
 
 last change : 28/02/2020
 */

#ifndef _CONSTAIN_H
#define _CONSTAIN_H

#define BLOCK               50
#define NB_BLOCK_WIDTH      12
#define NB_BLOCK_LENGTH     12
#define WIDTH               BLOCK * NB_BLOCK_WIDTH
#define LENGTH              BLOCK * NB_BLOCK_LENGTH

enum {
    UP, DOWN, LEFT, RIGHT
};
enum {
    EMPTY, STREET, WALL, BOX, OBJ, BOX_OK, MARIO
};



#endif



