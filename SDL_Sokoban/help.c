//
//  help.c
//  SDL_Sokoban
//
//  Created by Lương Dương on 3/6/20.
//  Copyright © 2020 Lương Dương. All rights reserved.
//

#include "help.h"

int help(SDL_Window *window, SDL_Surface *wdSurface) {
    SDL_Surface *helpSur = IMG_Load("source_image/help.png");
    if (helpSur == NULL) {
        fprintf(stderr, "Cannot create surface! ERROR: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;
    //start event
    int continuer = 1;
    SDL_Event event;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        SDL_FillRect(wdSurface, NULL, SDL_MapRGB(wdSurface->format, 255, 255, 255));
        SDL_BlitSurface(helpSur, NULL, wdSurface, &pos);
        SDL_UpdateWindowSurface(window);
    }
    return 0;
}
