
#include "editor.h"

int editMap(SDL_Window *window, SDL_Surface *wdSurface) {
    //init map
    int map[NB_BLOCK_LENGTH][NB_BLOCK_WIDTH] = {0};
    //init surface
    SDL_Surface *wall = NULL, *box = NULL, *boxOk = NULL, *obj = NULL, *mario = NULL, *street = NULL, *emp = NULL, *save = NULL, *done = NULL, *start = NULL;
    int objNow = STREET;
    SDL_Surface *objNowSurface = NULL;
    //load surface
    box             = IMG_Load("source_image/box.jpeg");
    boxOk           = IMG_Load("source_image/box_ok.jpeg");
    wall            = IMG_Load("source_image/wall.jpeg");
    obj             = IMG_Load("source_image/obj.jpeg");
    mario           = IMG_Load("source_image/mario_down.jpg");
    street          = IMG_Load("source_image/street.jpeg");
    emp             = IMG_Load("source_image/empty.png");
    save            = IMG_Load("source_image/save.png");
    done            = IMG_Load("source_image/done.png");
    start           = IMG_Load("source_image/start.png");
    if (wall == NULL || box == NULL || boxOk == NULL || obj == NULL || mario == NULL || street == NULL || emp == NULL || save == NULL || done == NULL || start == NULL) {
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
                SDL_FreeSurface(box);
                SDL_FreeSurface(boxOk);
                SDL_FreeSurface(wall);
                SDL_FreeSurface(emp);
                SDL_FreeSurface(done);
                SDL_FreeSurface(mario);
                SDL_FreeSurface(obj);
                SDL_FreeSurface(street);
                SDL_FreeSurface(save);
                SDL_FreeSurface(start);
                return QUIT;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        SDL_FreeSurface(box);
                        SDL_FreeSurface(boxOk);
                        SDL_FreeSurface(wall);
                        SDL_FreeSurface(emp);
                        SDL_FreeSurface(done);
                        SDL_FreeSurface(mario);
                        SDL_FreeSurface(obj);
                        SDL_FreeSurface(street);
                        SDL_FreeSurface(save);
                        SDL_FreeSurface(start);
                        continuer = 0;
                        break;
                    case SDLK_0:
                        objNow = EMPTY;
                        objNowSurface = emp;
                        break;
                    case SDLK_1:
                        objNow = STREET;
                        objNowSurface = street;
                        break;
                    case SDLK_2:
                        objNow = WALL;
                        objNowSurface = wall;
                        break;
                    case SDLK_3:
                        objNow = BOX;
                        objNowSurface = box;
                        break;
                    case SDLK_4:
                        objNow = OBJ;
                        objNowSurface = obj;
                        break;
                    case SDLK_5:
                        objNow = BOX_OK;
                        objNowSurface = boxOk;
                        break;
                    case SDLK_6:
                        objNowSurface = mario;
                        objNow = MARIO;
                        break;
                    case SDLK_RETURN:
                        updateLevel(map, "source_level/levelCustom.lvl");
                        position.x = WIDTH/2 - 300/2;
                        position.y = LENGTH/2 - 135/2;
                        SDL_BlitSurface(save, NULL, wdSurface, &position);
                        SDL_UpdateWindowSurface(window);
                        SDL_Delay(200);
                        continuer = 0;
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
                    map[posMouse.y/BLOCK][posMouse.x/BLOCK] = EMPTY;
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
                    map[posMouse.y/BLOCK][posMouse.x/BLOCK] = EMPTY;
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
                    case EMPTY:
                        SDL_BlitSurface(emp, NULL, wdSurface, &position);
                        break;
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
        // if continuer == 0 print done
        // icon size 115*115
        if (continuer == 0) {
            position.x = WIDTH/2 - 115/2;
            position.y = LENGTH/2 - 115/2;
            SDL_BlitSurface(done, NULL, wdSurface, &position);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(300);
            SDL_BlitSurface(start, NULL, wdSurface, &position);
            SDL_UpdateWindowSurface(window);
            continuer = 1;
            while (continuer) {
                SDL_WaitEvent(&event);
                switch (event.type) {
                    case SDL_MOUSEBUTTONDOWN:
                        // 115*115 is size of button
                        if (position.x < event.button.x && event.button.x < position.x + 115
                            && position.y < event.button.y && event.button.y < position.y + 115)
                            continuer = 0;
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
    SDL_FreeSurface(box);
    SDL_FreeSurface(boxOk);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(emp);
    SDL_FreeSurface(done);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(obj);
    SDL_FreeSurface(street);
    SDL_FreeSurface(save);
    
    return 0;
}
