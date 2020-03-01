/*
 gameFunc.h
 
 Luong Duc Duong
 
 last change: 29/02/2020
 */


#ifndef _GAMEFUNC_H
#define _GAMEFUNC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constain.h"
#include "stack.h"
#include "fileFunc.h"

int join(SDL_Window *window, SDL_Surface *wdSurface);
void replaceMario(int map[][NB_BLOCK_WIDTH], SDL_Rect *posJoin, int direction, node **top);
int checkMap(int map[][NB_BLOCK_WIDTH], SDL_Rect *posJoin, int direction);
void replaceBox(int *premierCase, int *secondCase);
void undoAction(int map[][NB_BLOCK_WIDTH], node **top, SDL_Rect *posJoin);

#endif
