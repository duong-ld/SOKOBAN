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
#include "help.h"
#include "level.h"

void printMenu(SDL_Window *window, SDL_Surface *wdSurface, int type);

int main(int argc, const char * argv[]) {
    
    //SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Cannot init SDL! ERROR: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    //create window
    SDL_Window *window = SDL_CreateWindow("DUTY OF SOKOBAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, LENGTH, SDL_WINDOW_ALLOW_HIGHDPI);
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
    SDL_Rect posMenu;
    posMenu.x = 0; posMenu.y = 0;
    
    //start even
    SDL_Event event;
    int continuer = 1;
    while (continuer) {
        //MENU
        printMenu(window, wdSurface, 0);
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
                        printMenu(window, wdSurface, 1);
                        SDL_Delay(150);
                        int level = chooseLevel(window, wdSurface);
                        if (level == QUIT) {
                            continuer = 0;
                        }
                        if (level >= 0) {
                            if (join(window, wdSurface, level, "source_level/levelDefault.lvl") == QUIT)
                                continuer = 0;
                        }
                        break;
                    case SDLK_2:
                        //menu seclect 2
                        printMenu(window, wdSurface, 2);
                        SDL_Delay(150);
                        if (editMap(window, wdSurface) == QUIT) {
                            continuer = 0;
                        }
                        if (join(window, wdSurface, 0, "source_level/levelCustom.lvl") == QUIT)
                            continuer = 0;
                        break;
                    case SDLK_3:
                        printMenu(window, wdSurface, 3);
                        SDL_Delay(150);
                        if (help(window, wdSurface) == QUIT) {
                            continuer = 0;
                        }
                        break;
                    default:
                        break;
                }
            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < 3; i ++) {
                    /*
                     220 & 380 is position x of button join, help, edit_map
                     280 + i * 105 & 320 + i * 105
                     is position y of button
                     */
                    if (220 < event.button.x && event.button.x < 380
                        && 260 + i * 105 < event.button.y && event.button.y < 335 + i * 105) {
                        printMenu(window, wdSurface, i + 1);
                        SDL_Delay(150);
                        if (i == 0) {
                            int level = chooseLevel(window, wdSurface);
                            if (level == QUIT) {
                                continuer = 0;
                            }
                            if (level >= 0) {
                                if (join(window, wdSurface, level, "source_level/levelDefault.lvl") == QUIT)
                                    continuer = 0;
                            }
                        }
                        if (i == 1) {
                            if (editMap(window, wdSurface) == QUIT) continuer = 0;
                            if (join(window, wdSurface, 0, "source_level/levelCustom.lvl") == QUIT)
                                continuer = 0;
                        }
                        if (i == 2) if (help(window, wdSurface) == QUIT) continuer = 0;
                    }
                }
                break;
            default:
                break;
            }
        SDL_FillRect(wdSurface, NULL, SDL_MapRGB(wdSurface->format, 0, 0, 0));
        printMenu(window, wdSurface, 0);
        SDL_UpdateWindowSurface(window);
    }
    
    //Quit game
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
/*
 type 0: MENU with no choose
 type 1: MENU with choose join
 type 2: MENU with choose edit map
 type 3: MENU with choose help
 */
void printMenu(SDL_Window *window, SDL_Surface *wdSurface, int type) {
    SDL_Surface *menu = IMG_Load("source_image/menu.png");
    SDL_Surface *join[2];
    join[UP] = IMG_Load("source_image/button_menu/menu_join.png");
    join[DOWN] = IMG_Load("source_image/button_menu/menu_join_down.png");
    SDL_Surface *help[2];
    help[UP] = IMG_Load("source_image/button_menu/menu_help.png");
    help[DOWN] = IMG_Load("source_image/button_menu/menu_help_down.png");
    SDL_Surface *edit[2];
    edit[UP] = IMG_Load("source_image/button_menu/menu_editmap.png");
    edit[DOWN] = IMG_Load("source_image/button_menu/menu_editmap_down.png");
    SDL_Rect pos;
    pos.x = 0; pos.y = 0;
    SDL_BlitSurface(menu, NULL, wdSurface, &pos);
    for (int i = 0; i < 3; i++) {
        pos.x = WIDTH / 2 - 200 / 2;
        pos.y = LENGTH / 2 - 200 / 2 + (i) * 105;
        if (i == 0) SDL_BlitSurface(join[UP], NULL, wdSurface, &pos);
        if (i == 1) SDL_BlitSurface(edit[UP], NULL, wdSurface, &pos);
        if (i == 2) SDL_BlitSurface(help[UP], NULL, wdSurface, &pos);
    }
    if (type == 1) {
        for (int i = 0; i < 3; i++) {
            pos.x = WIDTH / 2 - 200 / 2;
            pos.y = LENGTH / 2 - 200 / 2 + (i) * 105;
            if (i == 0) SDL_BlitSurface(join[DOWN], NULL, wdSurface, &pos);
            if (i == 1) SDL_BlitSurface(edit[UP], NULL, wdSurface, &pos);
            if (i == 2) SDL_BlitSurface(help[UP], NULL, wdSurface, &pos);
        }
    }
    if (type == 2) {
        for (int i = 0; i < 3; i++) {
            pos.x = WIDTH / 2 - 200 / 2;
            pos.y = LENGTH / 2 - 200 / 2 + (i) * 105;
            if (i == 0) SDL_BlitSurface(join[UP], NULL, wdSurface, &pos);
            if (i == 1) SDL_BlitSurface(edit[DOWN], NULL, wdSurface, &pos);
            if (i == 2) SDL_BlitSurface(help[UP], NULL, wdSurface, &pos);
        }
    }
    if (type == 3) {
        for (int i = 0; i < 3; i++) {
            pos.x = WIDTH / 2 - 200 / 2;
            pos.y = LENGTH / 2 - 200 / 2 + (i) * 105;
            if (i == 0) SDL_BlitSurface(join[UP], NULL, wdSurface, &pos);
            if (i == 1) SDL_BlitSurface(edit[UP], NULL, wdSurface, &pos);
            if (i == 2) SDL_BlitSurface(help[DOWN], NULL, wdSurface, &pos);
        }
    }
    SDL_UpdateWindowSurface(window);
}
