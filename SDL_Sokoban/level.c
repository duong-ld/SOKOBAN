//
//  level.c
//  SDL_Sokoban
//
//  Created by Lương Dương on 3/7/20.
//  Copyright © 2020 Lương Dương. All rights reserved.
//

#include "level.h"

int chooseLevel(SDL_Window *window, SDL_Surface *wdSurface) {
    SDL_Surface *lev[MAX_LEVEL];
    SDL_Surface *map[MAX_LEVEL];
    SDL_Surface *backgr = NULL;
    //create level button surface
    lev[0] = IMG_Load("source_image/button_level/lev1.png");
    lev[1] = IMG_Load("source_image/button_level/lev2.png");
    lev[2] = IMG_Load("source_image/button_level/lev3.png");
    lev[3] = IMG_Load("source_image/button_level/lev4.png");
    lev[4] = IMG_Load("source_image/button_level/lev5.png");
    lev[5] = IMG_Load("source_image/button_level/lev6.png");
    lev[6] = IMG_Load("source_image/button_level/lev7.png");
    lev[7] = IMG_Load("source_image/button_level/lev8.png");
    lev[8] = IMG_Load("source_image/button_level/lev9.png");
    lev[9] = IMG_Load("source_image/button_level/lev10.png");
    //create map surface
    map[0] = IMG_Load("source_image/map/map1.png");
    map[1] = IMG_Load("source_image/map/map2.png");
    map[2] = IMG_Load("source_image/map/map3.png");
    map[3] = IMG_Load("source_image/map/map4.png");
    map[4] = IMG_Load("source_image/map/map5.png");
    map[5] = IMG_Load("source_image/map/map6.png");
    map[6] = IMG_Load("source_image/map/map7.png");
    map[7] = IMG_Load("source_image/map/map8.png");
    map[8] = IMG_Load("source_image/map/map9.png");
    map[9] = IMG_Load("source_image/map/map10.png");
    backgr = IMG_Load("source_image/button_level/backGround.jpg");
    for (int i = 0; i < MAX_LEVEL; i ++) {
        if (lev[i] == NULL || map[i] == NULL) {
            fprintf(stderr, "Cannot load surface! ERROR: %s", SDL_GetError());
            return -1;
        }
    }
    if (backgr == NULL) {
        fprintf(stderr, "Cannot load surface! ERROR: %s", SDL_GetError());
        return -1;
    }
    SDL_Rect pos, posMap;
    //mini map position
    posMap.x = 50;
    posMap.y = 125
    ;
    //event
    SDL_Event event;
    int continuer = 1;
    while (continuer) {
        pos.x = 0; pos.y = 0;
        SDL_FillRect(wdSurface, NULL, SDL_MapRGB(wdSurface->format, 255, 255, 255));
        SDL_BlitSurface(backgr, NULL, wdSurface, &pos);
        for (int i = 0; i < MAX_LEVEL; i++) {
            pos.x = WIDTH - 150; pos.y = 50 * i;
            SDL_BlitSurface(lev[i], NULL, wdSurface, &pos);
        }
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                for (int i = 0; i < MAX_LEVEL; i++) {
                    SDL_FreeSurface(lev[i]);
                    SDL_FreeSurface(map[i]);
                }
                SDL_FreeSurface(backgr);
                return QUIT;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                        
                    default:
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                pos.x = 0; pos.y = 0;
                SDL_BlitSurface(backgr, NULL, wdSurface, &pos);
                for (int i = 0; i < MAX_LEVEL; i++) {
                    pos.x = WIDTH - 150;
                    pos.y = 50 * i;
                    if (WIDTH - 138 < event.button.x && event.button.x < WIDTH - 12
                        && 50 + i*50 < event.button.y && event.button.y < 100 + i*50) {
                        pos.x = WIDTH - 175;
                        SDL_BlitSurface(lev[i], NULL, wdSurface, &pos);
                        SDL_BlitSurface(map[i], NULL, wdSurface, &posMap);
                    } else {
                        SDL_BlitSurface(lev[i], NULL, wdSurface, &pos);
                    }
                        
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < MAX_LEVEL; i++) {
                    pos.x = WIDTH - 150;
                    pos.y = 50 * i;
                    if (WIDTH - 138 < event.button.x && event.button.x < WIDTH - 12
                        && 50 + i*50 < event.button.y && event.button.y < 100 + i*50) {
                        pos.x = WIDTH - 175;
                        for (int i = 0; i < MAX_LEVEL; i++) {
                            SDL_FreeSurface(lev[i]);
                            SDL_FreeSurface(map[i]);
                        }
                        SDL_FreeSurface(backgr);
                        return i;
                    }
                }
                break;
            default:
                break;
        }
        SDL_UpdateWindowSurface(window);
    }
    for (int i = 0; i < MAX_LEVEL; i++) {
        SDL_FreeSurface(lev[i]);
        SDL_FreeSurface(map[i]);
    }
    SDL_FreeSurface(backgr);
    return -1;
}
