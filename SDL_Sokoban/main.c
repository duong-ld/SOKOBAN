//
//  main.c
//  SDL_Sokoban
//
//  Created by Lương Dương on 2/28/20.
//  Copyright © 2020 Lương Dương. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constain.h"
#include "gameFunc.h"
#include "editor.h"

int main(int argc, const char * argv[]) {
    
    //SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Cannot init SDL! ERROR: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    //create window
    SDL_Window *window = SDL_CreateWindow("SOKOBAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, LENGTH, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL) {
        fprintf(stderr, "Cannot create Window! ERROR: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    //Add icon
    SDL_SetWindowIcon(window, IMG_Load("source_image/icon.jpg"));
    
    //create window surfect
    SDL_Surface *wdSurface = SDL_GetWindowSurface(window);
    if (wdSurface == NULL) {
        fprintf(stderr, "Cannot create window surfect! ERROR: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    //Load menu
    SDL_Surface *menu = IMG_Load("source_image/menu.png");
    SDL_Surface *menu1 = IMG_Load("source_image/menu1.png");
    SDL_Surface *menu2 = IMG_Load("source_image/menu2.png");
    SDL_Surface *menu3 = IMG_Load("source_image/menu3.png");
    SDL_Rect posMenu;
    posMenu.x = 0; posMenu.y = 0;
    
    //start even
    SDL_Event event;
    int continuer = 1;
    while (continuer) {
        //MENU
        SDL_BlitSurface(menu, NULL, wdSurface, &posMenu);
        
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_1:
                        //menu seclect 1
                        SDL_BlitSurface(menu1, NULL, wdSurface, &posMenu);
                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(500);
                        if (join(window, wdSurface)) {
                            continuer = 0;
                        }
                        break;
                    case SDLK_2:
                        //menu seclect 2
                        SDL_BlitSurface(menu2, NULL, wdSurface, &posMenu);
                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(500);
                        if (editMap(window, wdSurface)) {
                            continuer = 0;
                        }
                        break;
                    case SDLK_3:
                        SDL_BlitSurface(menu3, NULL, wdSurface, &posMenu);
                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(500);
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
        SDL_FillRect(wdSurface, NULL, SDL_MapRGB(wdSurface->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, wdSurface, &posMenu);
        SDL_UpdateWindowSurface(window);
    }
    
    //Quit game
    SDL_FreeSurface(menu);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

