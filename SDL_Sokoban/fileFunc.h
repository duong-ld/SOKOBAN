/*
 fileFunc.h
 
 Luong Duc Duong
 
 last change: 28/02/2020
 */


#ifndef _FILEFUNC_H
#define _FILEFUNC_H

#include "constain.h"
#include <stdlib.h>
#include <stdio.h>

int loadLevel(int level[][NB_BLOCK_WIDTH], int mapNum, char fileName[81]);
int updateLevel(int level[][NB_BLOCK_WIDTH], char fileName[81]);

#endif


