#include "fileFunc.h"


int loadLevel(int level[][NB_BLOCK_WIDTH]) {
    FILE *fichi = NULL;
    if ((fichi = fopen("level.lvl", "r")) == NULL) {
        fprintf(stderr, "Load level not successed! ERROR: Cannot open level.lvl file");
        return 0;
    }
    char lineFichi[NB_BLOCK_WIDTH * NB_BLOCK_LENGTH + 1] = {0};
    fgets(lineFichi, NB_BLOCK_WIDTH * NB_BLOCK_LENGTH + 1, fichi);
    for (int i = 0; i < NB_BLOCK_LENGTH; i++) {
        for (int j = 0; j < NB_BLOCK_WIDTH; j++) {
            switch (lineFichi[i * NB_BLOCK_WIDTH + j]) {
                case '0':
                    level[i][j] = 0;
                    break;
                case '1':
                    level[i][j] = 1;
                    break;
                case '2':
                    level[i][j] = 2;
                    break;
                case '3':
                    level[i][j] = 3;
                    break;
                case '4':
                    level[i][j] = 4;
                    break;
                case '5':
                    level[i][j] = 5;
                    break;
                case '6':
                    level[i][j] = 6;
                    break;
                default:
                    level[i][j] = 0;
                    break;
            }
        }
    }
    fclose(fichi);
    return 1;
}
int updateLevel(int level[][NB_BLOCK_WIDTH]) {
    FILE *fichi = NULL;
    if ((fichi = fopen("level.lvl", "w")) == NULL) {
        fprintf(stderr, "Cannot update level! ERROR: Cannot open level.lv file");
        return 0;
    }
    for (int i =  0; i < NB_BLOCK_LENGTH; i++) {
        for (int j = 0; j < NB_BLOCK_WIDTH; j++) {
            fprintf(fichi, "%d", level[i][j]);
        }
    }
    fclose(fichi);
    return 1;
}
