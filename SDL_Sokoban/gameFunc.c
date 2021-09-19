#include "gameFunc.h"


int join(SDL_Window *window, SDL_Surface *wdSurface, int level, char fileName[81]) {
    // init surface
    SDL_Surface *mario[4] = {NULL};    // 4 state mario
    SDL_Surface *street = NULL, *wall = NULL, *box = NULL, *boxOk = NULL, *obj = NULL, *marioNow = NULL, *win = NULL;
    SDL_Surface *empty[3] = {NULL}; // 3 state empty
    SDL_Rect marioPos, position;
    // check mario in map
    int isHadMario = 0;
    // event
    SDL_Event event;
    int continuer = 1, objRemain = 0;
    int map[NB_BLOCK_WIDTH][NB_BLOCK_LENGTH] = {0};
    // Undo event
    node *top = NULL;
    initStack(&top);
    // load surface
    mario[UP]       = IMG_Load("source_image/mario_up.jpg");
    mario[DOWN]     = IMG_Load("source_image/mario_down.jpg");
    mario[LEFT]     = IMG_Load("source_image/mario_left.jpg");
    mario[RIGHT]    = IMG_Load("source_image/mario_right.jpg");
    marioNow        = mario[DOWN];
    for (int i = 0; i < 4; i++) {// 4 state of mario
        SDL_SetColorKey(mario[i], SDL_TRUE, SDL_MapRGB(mario[i]->format, 160, 206, 142));
    }
    empty[EMPTY]    = IMG_Load("source_image/empty.png");
    empty[WALL]     = IMG_Load("source_image/empty_wall.png");
    empty[STREET]   = IMG_Load("source_image/empty_street.png");
    box             = IMG_Load("source_image/box.jpeg");
    boxOk           = IMG_Load("source_image/box_ok.jpeg");
    wall            = IMG_Load("source_image/wall.jpeg");
    obj             = IMG_Load("source_image/obj.jpeg");
    win             = IMG_Load("source_image/win.png");
    street          = IMG_Load("source_image/street.jpeg");
    if (mario[UP] == NULL || mario[DOWN] == NULL || mario[LEFT] == NULL || mario[RIGHT] == NULL || box == NULL || boxOk == NULL || wall == NULL || obj == NULL || win == NULL || street == NULL || empty[WALL] == NULL || empty[EMPTY] == NULL || empty[STREET] == NULL) {
        fprintf(stderr, "Cannot load surface! ERROR: %s", SDL_GetError());
        return -1;
    }
    // Load map
    if (!loadLevel(map, level, fileName)) {
        fprintf(stderr, "Load map not successed!");
    }
    // Load Mario position
    for (int i = 0; i < NB_BLOCK_LENGTH; i++) {
        for (int j = 0; j < NB_BLOCK_WIDTH; j++) {
            if (map[i][j] == MARIO) {
                marioPos.x = j;
                marioPos.y = i;
                map[i][j] = STREET;
                isHadMario = 1;
            }
        }
    }
    // if dont have mario, then create one
    if (!isHadMario) {
        int x = 0, y = 0;
        do {
            x = rand() % NB_BLOCK_WIDTH;
            y = rand() % NB_BLOCK_LENGTH;
        } while (map[y][x] != STREET);
        marioPos.x = x;
        marioPos.y = y;
    }
    // start event
    while(continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                // Free surfect
                SDL_FreeSurface(win);
                SDL_FreeSurface(wall);
                SDL_FreeSurface(boxOk);
                SDL_FreeSurface(box);
                SDL_FreeSurface(obj);
                for (int i = 0; i < 4; i ++) {
                    SDL_FreeSurface(mario[i]);
                }
                for (int i = 0; i < 3; i ++) {
                    SDL_FreeSurface(empty[i]);
                }
                freeStack(top);
                return QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP: case SDLK_w:
                        marioNow = mario[UP];
                        replaceMario(map, &marioPos, UP, &top);
                        break;
                    case SDLK_DOWN: case SDLK_s:
                        marioNow = mario[DOWN];
                        replaceMario(map, &marioPos, DOWN, &top);
                        break;
                    case SDLK_LEFT: case SDLK_a:
                        marioNow = mario[LEFT];
                        replaceMario(map, &marioPos, LEFT, &top);
                        break;
                    case SDLK_RIGHT: case SDLK_d:
                        marioNow = mario[RIGHT];
                        replaceMario(map, &marioPos, RIGHT, &top);
                        break;
                    case SDLK_BACKSPACE:
                        undoAction(map, &top, &marioPos);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        // Clean window surface
        SDL_FillRect(wdSurface, NULL, SDL_MapRGB(wdSurface->format, 255, 255, 255));
        // print map
        objRemain = 0;
        for (int i = 0; i < NB_BLOCK_LENGTH; i++) {
            for (int j = 0; j < NB_BLOCK_WIDTH; j++) {
                position.x = j * BLOCK;
                position.y = i * BLOCK;
                switch (map[i][j]) {
                    case EMPTY:
                        if (i >= 1 && (map[i - 1][j] == STREET || map[i - 1][j] == BOX || map[i - 1][j] == BOX_OK || map[i - 1][j] == OBJ))
                            SDL_BlitSurface(empty[STREET], NULL, wdSurface, &position);
                        else if (i >= 1 && map[i - 1][j] == WALL)
                            SDL_BlitSurface(empty[WALL], NULL, wdSurface, &position);
                        else
                            SDL_BlitSurface(empty[EMPTY], NULL, wdSurface, &position);
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
                        objRemain = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        // Blit mario
        position.x = marioPos.x * BLOCK;
        position.y = marioPos.y * BLOCK;
        SDL_BlitSurface(marioNow, NULL, wdSurface, &position);
        // update surfect
        SDL_UpdateWindowSurface(window);
        
        // if objRemain = 0 done
        // Load win surface
        if (!objRemain) {
            while (1) {
                // 400 * 400 is size of win image
                position.x = WIDTH / 2 - 400 / 2;
                position.y = LENGTH / 2 - 400 / 2;
                SDL_BlitSurface(win, NULL, wdSurface, &position);
                // Update surfect
                SDL_UpdateWindowSurface(window);
                // comfirm quit game
                SDL_WaitEvent(&event);
                if (event.type == SDL_QUIT) {
                    // Free surfect
                    SDL_FreeSurface(win);
                    SDL_FreeSurface(wall);
                    SDL_FreeSurface(boxOk);
                    SDL_FreeSurface(box);
                    SDL_FreeSurface(obj);
                    for (int i = 0; i < 4; i ++) {
                        SDL_FreeSurface(mario[i]);
                    }
                    for (int i = 0; i < 3; i ++) {
                        SDL_FreeSurface(empty[i]);
                    }
                    freeStack(top);
                    return QUIT;
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    continuer = 0;
                    break;
                }
            }
        }
    }
    
    // Free surfect
    SDL_FreeSurface(win);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(boxOk);
    SDL_FreeSurface(box);
    SDL_FreeSurface(obj);
    for (int i = 0; i < 4; i ++) {
        SDL_FreeSurface(mario[i]);
    }
    for (int i = 0; i < 3; i ++) {
        SDL_FreeSurface(empty[i]);
    }
    freeStack(top);
    return 0;
}

void replaceMario(int map[][NB_BLOCK_WIDTH], SDL_Rect *marioPos, int direction, node **top) {
    // switch direction
    switch (direction) {
        case UP:
            // if check map successed don't take action
            if (checkMap(map, marioPos, UP)) break;
            marioPos->y--;
            // push action to undo
            cache up;
            up.direc = UP;
            replaceBox(&map[marioPos->y][marioPos->x], &map[marioPos->y - 1][marioPos->x], &up);
            push(top, up);
            break;
        case DOWN:
            if (checkMap(map, marioPos, DOWN)) break;
            marioPos->y++;
            cache down;
            down.direc = DOWN;
            replaceBox(&map[marioPos->y][marioPos->x], &map[marioPos->y + 1][marioPos->x], &down);
            push(top, down);
            break;
        case LEFT:
            if (checkMap(map, marioPos, LEFT)) break;
            marioPos->x--;
            cache left;
            left.direc = LEFT;
            replaceBox(&map[marioPos->y][marioPos->x], &map[marioPos->y][marioPos->x - 1], &left);
            push(top, left);
            break;
        case RIGHT:
            if (checkMap(map, marioPos, RIGHT)) break;
            marioPos->x++;
            cache right;
            right.direc = RIGHT;
            replaceBox(&map[marioPos->y][marioPos->x], &map[marioPos->y][marioPos->x + 1], &right);
            push(top, right);
            break;
        default:
            break;
    }
}
/*
 Check map check position mario :
 1. mario can't through the wall
 2. mario can't move 2 block
 3. mario can't move block through the wall
 4. mario can't go outside the map
 5. mario can't move the block outside the map
 */
int checkMap(int map[][NB_BLOCK_WIDTH], SDL_Rect *marioPos, int direction) {
    switch (direction) {
        case UP:
            if (marioPos->y - 1 < 0) return 1;
            if (map[marioPos->y - 1][marioPos->x] == WALL || map[marioPos->y - 1][marioPos->x] == EMPTY) return 1;
            if (((map[marioPos->y - 1][marioPos->x] == BOX) || (map[marioPos->y - 1][marioPos->x] == BOX_OK)) && ((map[marioPos->y - 2][marioPos->x] == BOX) || (map[marioPos->y - 2][marioPos->x] == BOX_OK) || (marioPos->y - 2 < 0) || (map[marioPos->y - 2][marioPos->x] == WALL) || (map[marioPos->y - 2][marioPos->x] == EMPTY)))
                    return 1;
            break;
        case DOWN:
            if (marioPos->y + 1 == NB_BLOCK_LENGTH) return 1;
            if (map[marioPos->y + 1][marioPos->x] == WALL || map[marioPos->y + 1][marioPos->x] == EMPTY) return 1;
            if (((map[marioPos->y + 1][marioPos->x] == BOX) || (map[marioPos->y + 1][marioPos->x] == BOX_OK)) && ((map[marioPos->y + 2][marioPos->x] == BOX) || (map[marioPos->y + 2][marioPos->x] == BOX_OK) || (marioPos->y + 2 == NB_BLOCK_LENGTH) || (map[marioPos->y + 2][marioPos->x] == WALL) || (map[marioPos->y + 2][marioPos->x] == EMPTY)))
                    return 1;
            break;
        case LEFT:
            if (marioPos->x - 1 < 0) return 1;
            if (map[marioPos->y][marioPos->x - 1] == WALL || map[marioPos->y][marioPos->x - 1] == EMPTY) return 1;
            if (((map[marioPos->y][marioPos->x - 1] == BOX) || (map[marioPos->y][marioPos->x - 1] == BOX_OK)) && ((map[marioPos->y][marioPos->x - 2] == BOX) || (map[marioPos->y][marioPos->x - 2] == BOX_OK) || (marioPos->x - 2 < 0) || (map[marioPos->y][marioPos->x - 2] == WALL) || (map[marioPos->y][marioPos->x - 2] == EMPTY)))
                    return 1;
            break;
        case RIGHT:
            if (marioPos->x + 1 == NB_BLOCK_WIDTH) return 1;
            else if (map[marioPos->y][marioPos->x + 1] == WALL || map[marioPos->y][marioPos->x + 1] == EMPTY) return 1;
            else if (((map[marioPos->y][marioPos->x + 1] == BOX) || (map[marioPos->y][marioPos->x + 1] == BOX_OK)) && ((map[marioPos->y][marioPos->x + 2] == BOX) || (map[marioPos->y][marioPos->x + 2] == BOX_OK) || (marioPos->x + 2 == NB_BLOCK_WIDTH) || (map[marioPos->y][marioPos->x + 2] == WALL) || (map[marioPos->y][marioPos->x + 2] == EMPTY))) return 1;
            break;
            
    }
    return 0;
}
void replaceBox(int *premierCase, int *secondCase, cache *direc) {
    if (*premierCase == BOX_OK || *premierCase == BOX) {
        direc->boxMove = 1;
        if (*secondCase == OBJ)
            *secondCase = BOX_OK;
        else *secondCase = BOX;
        
        if (*premierCase == BOX_OK)
            *premierCase = OBJ;
        else *premierCase = STREET;
    } else direc->boxMove = 0;
}
void undoAction(int map[][NB_BLOCK_WIDTH], node **top, SDL_Rect *marioPos) {
    cache action = pop(top);
    cache tmp;
    tmp.direc = -1;
    switch (action.direc) {
        case UP:
            if (action.boxMove) {
                replaceBox(&map[marioPos->y - 1][marioPos->x], &map[marioPos->y][marioPos->x], &tmp);
            }
            marioPos->y++;
            break;
        case DOWN:
            if (action.boxMove) {
                replaceBox(&map[marioPos->y + 1][marioPos->x], &map[marioPos->y][marioPos->x], &tmp);
            }
            marioPos->y--;
            break;
        case LEFT:
            if (action.boxMove) {
                replaceBox(&map[marioPos->y][marioPos->x - 1], &map[marioPos->y][marioPos->x], &tmp);
            }
            marioPos->x++;
            break;
        case RIGHT:
            if (action.boxMove) {
                replaceBox(&map[marioPos->y][marioPos->x + 1], &map[marioPos->y][marioPos->x], &tmp);
            }
            marioPos->x--;
            break;
        default:
            break;
    }
}
