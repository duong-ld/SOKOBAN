
#include "editor.h"

int editMap(SDL_Window *window, SDL_Surface *wdSurface) {
    //init map
    int map[NB_BLOCK_LENGTH][NB_BLOCK_WIDTH] = {0};
    //init surface
    SDL_Surface *wall = NULL, *box = NULL, *boxOk = NULL, *obj = NULL, *mario = NULL, *street = NULL;
    int objNow = STREET;
    SDL_Surface *objNowSurface = NULL;
    //load surface
    box             = IMG_Load("source_image/box.jpeg");
    boxOk           = IMG_Load("source_image/box_ok.jpeg");
    wall            = IMG_Load("source_image/wall.jpeg");
    obj             = IMG_Load("source_image/obj.jpeg");
    mario           = IMG_Load("source_image/mario_down.jpg");
    street          = IMG_Load("source_image/street.jpeg");
    if (wall == NULL || box == NULL || boxOk == NULL || obj == NULL || mario == NULL || street == NULL) {
        fprintf(stderr, "Cannot init surface! ERROR: %s", SDL_GetError());
        return -1;
    }
    //init event
    SDL_Event event;
    int continuer = 1, mouseClick = 0;
    SDL_Rect posMouse, position;
    //start event
    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return 1;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_1:
                        objNow = WALL;
                        objNowSurface = wall;
                        break;
                    case SDLK_2:
                        objNow = BOX;
                        objNowSurface = box;
                        break;
                    case SDLK_3:
                        objNow = OBJ;
                        objNowSurface = obj;
                        break;
                    case SDLK_4:
                        objNow = BOX_OK;
                        objNowSurface = boxOk;
                        break;
                    case SDLK_5:
                        objNowSurface = mario;
                        objNow = MARIO;
                        break;
                    case SDLK_RETURN:
                        updateLevel(map);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                posMouse.x = event.button.x;
                posMouse.y = event.button.y;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseClick = 1;
                    map[posMouse.y/BLOCK][posMouse.x/BLOCK] = objNow;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    mouseClick = 2;
                    map[posMouse.y/BLOCK][posMouse.x/BLOCK] = STREET;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouseClick = 0;
                break;
            case SDL_MOUSEMOTION:
                posMouse.x = event.button.x;
                posMouse.y = event.button.y;
                if (mouseClick == 1) {
                    map[posMouse.y/BLOCK][posMouse.x/BLOCK] = objNow;
                } else if (mouseClick == 2)
                    map[posMouse.y/BLOCK][posMouse.x/BLOCK] = STREET;
                break;
            default:
                break;
        }
        //Clean window surface
        SDL_FillRect(wdSurface, NULL, SDL_MapRGB(wdSurface->format, 255, 255, 255));
        //print map
        for (int i = 0; i < NB_BLOCK_LENGTH; i++) {
            for (int j = 0; j < NB_BLOCK_WIDTH; j++) {
                position.x = j * BLOCK;
                position.y = i * BLOCK;
                switch (map[i][j]) {
                    case STREET:
                        SDL_BlitSurface(street, NULL, wdSurface, &position);
                        break;
                    case WALL:
                        SDL_BlitSurface(wall, NULL, wdSurface, &position);
                        break;
                    case BOX:
                        SDL_BlitSurface(box, NULL, wdSurface, &position);
                        break;
                    case BOX_OK:
                        SDL_BlitSurface(boxOk, NULL, wdSurface, &position);
                        break;
                    case OBJ:
                        SDL_BlitSurface(obj, NULL, wdSurface, &position);
                        break;
                    case MARIO:
                        SDL_BlitSurface(mario, NULL, wdSurface, &position);
                        break;
                    default:
                        break;
                }
            }
        }
        position.x = posMouse.x - BLOCK/2;
        position.y = posMouse.y - BLOCK/2;
        SDL_BlitSurface(objNowSurface, NULL, wdSurface, &position);
        SDL_UpdateWindowSurface(window);
    }
    
    return 0;
}
