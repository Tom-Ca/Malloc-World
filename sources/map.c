/*
 * Filename: map.h
 *
 * Made by: tom on 11/10/2021
 *
 * Description: this file groups the functions of the map.
 */
#include "map.h"
#include <time.h>


#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void display(int **map, int nblines, int nbcolumns)      //displays and formats the map (the array)
{
    for (int i = 0; i < nblines; i++) {
        for (int j = 0; j < nbcolumns; j++) {
            printf("-------");
        }
        printf("\n");
        printf("|");
        for (int j = 0; j < nbcolumns; j++) {
            printf("%4d  |", map[i][j]);
        }
        printf("\n-");
    }
    for (int j = 0; j < nbcolumns; j++) {
        printf("-------");
    }

}

int **mallocMap(int height, int width){     //malloc the map
    int **map;
    map = malloc(height * sizeof(int));
    for(int i = 0; i < height; ++i)
    {
        map[i] = malloc(width * sizeof(int));
    }
    return map;
}


//create a copy of the map
int **copyMap(int **map, int height, int width){
    int **copyMap;
    copyMap = mallocMap(height,width);
    for (int i = 0; i < height; i+=1) {
        for (int j=0; j < width; j+=1){
            copyMap[i][j] = map[i][j];
        }
    }
    return copyMap;
}

//add random items to the map where it is empty
void randomizedItem(int **map, int weak_monster, int strong_monster, int nblines, int nbcolumns, int currentMap) {
    int nb_opponent = 0;
    int nb_rocks = 0;
    int nb_plants = 0;
    int nb_trees = 0;
    while (nb_opponent <= 10 || nb_rocks <= 3 || nb_plants <= 3 || nb_trees <= 3) {
        nb_opponent = 0;
        nb_rocks = 0;
        nb_plants = 0;
        nb_trees = 0;
        for (int i = 0; i < nblines; i++) {
            for (int j = 0; j < nbcolumns; j++) {
                if (map[i][j] == 0) {
                    int rand_obstacle = rand() % 5;
                    if (rand_obstacle == 0) {
                        map[i][j] = (rand() % (strong_monster - weak_monster + 1)) + weak_monster;
                        nb_opponent++;
                    } else if (rand_obstacle == 1) {
                        if(currentMap==1){
                            map[i][j] = 4;
                        }else if(currentMap==2){
                            map[i][j] = 7;
                        }else if(currentMap==3){
                            map[i][j] = 10;
                        }
                        nb_rocks++;
                    } else if (rand_obstacle == 2) {
                        if(currentMap==1){
                            map[i][j] = 3;
                        }else if(currentMap==2){
                            map[i][j] = 6;
                        }else if(currentMap==3){
                            map[i][j] = 9;
                        }
                        nb_plants++;
                    } else if (rand_obstacle == 3) {
                        if(currentMap==1){
                            map[i][j] = 5;
                        }else if(currentMap==2){
                            map[i][j] = 8;
                        }else if(currentMap==3){
                            map[i][j] = 11;
                        }
                        nb_trees++;
                    } else if (rand_obstacle == 4) {
                        map[i][j] = 0;
                    }
                }
            }
        }
    }
}


void empiler(Pile *pile, int i, int j) {
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL) {
        exit(EXIT_FAILURE);
    }

    nouveau->i = i;
    nouveau->j = j;
    nouveau->next = pile->premier;
    pile->premier = nouveau;
}

void depiler(Pile *pile) {
    if (pile == NULL) {
        exit(EXIT_FAILURE);
    }

    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL) {
        pile->premier = elementDepile->next;
        free(elementDepile);
    }

}

//randomly generate the maze
void labyrinthe(int **map, int nblines, int nbcolumns, int lv) {
    for (int i = 0; i < nblines; i++) {
        for (int j = 0; j < nbcolumns; j++) {
            if (i % 2 == 0) {
                map[i][j] = -1;
            } else if (j % 2 == 0) {
                map[i][j] = -1;
            } else {
                map[i][j] = 0;
            }
        }
    }
    int i = 1, j = 1;

    Pile *maPile = malloc(sizeof(Pile));
    empiler(maPile, 0, 0);
    empiler(maPile, i, j);
    Element *actuel = maPile->premier;
    int k = 0, m = 0;
    int end[3] = {0, 0, 0};

    while (k == 0) { //

        //printf("%d\n",k);
        int nb_rand = 0;
        int gauche = 0, droite = 0, haut = 0, bas = 0;
        int i_g, j_g, i_d, j_d, i_h, j_h, i_b, j_b;
        int ca = 0;
        int good_case = 0;

        if (j > 2) {
            i_g = i;
            j_g = j - 2;
            if (map[i_g + 1][j_g] == -1 && map[i_g][j_g + 1] == -1 && map[i_g - 1][j_g] == -1 &&
                map[i_g][j_g - 1] == -1) {
                gauche = 1;
                nb_rand += 1;
            }
        }
        if (j < nblines - 2) {
            i_d = i;
            j_d = j + 2;
            if (map[i_d + 1][j_d] == -1 && map[i_d][j_d + 1] == -1 && map[i_d - 1][j_d] == -1 &&
                map[i_d][j_d - 1] == -1) {
                droite = 1;
                nb_rand += 1;
            }
        }
        if (i > 2) {
            i_h = i - 2;
            j_h = j;
            if (map[i_h + 1][j_h] == -1 && map[i_h][j_h + 1] == -1 && map[i_h - 1][j_h] == -1 &&
                map[i_h][j_h - 1] == -1) {
                haut = 1;
                nb_rand += 1;
            }
        }
        if (i < nbcolumns - 2) {
            i_b = i + 2;
            j_b = j;
            if (map[i_b + 1][j_b] == -1 && map[i_b][j_b + 1] == -1 && map[i_b - 1][j_b] == -1 &&
                map[i_b][j_b - 1] == -1) {
                bas = 1;
                nb_rand += 1;
            }
        }
        if (nb_rand != 0) {
            while (good_case == 0) {
                int r = rand() % (4);

                switch (r) {
                    case 0:
                        ca = 0; //gauche
                        if (gauche == 1) {
                            good_case = 1;
                        }
                        break;
                    case 1:
                        ca = 1; //droite
                        if (droite == 1) {
                            good_case = 1;
                        }
                        break;
                    case 2:
                        ca = 2; //bas
                        if (bas == 1) {
                            good_case = 1;
                        }
                        break;
                    case 3:
                        ca = 3; //haut
                        if (haut == 1) {
                            good_case = 1;
                        }
                        break;
                }
            }
            switch (ca) {
                case 0:
                    map[i][j - 1] = 0;
                    i = i_g;
                    j = j_g;
                    break;
                case 1:
                    map[i][j + 1] = 0;
                    i = i_d;
                    j = j_d;
                    break;
                case 2:
                    map[i + 1][j] = 0;
                    i = i_b;
                    j = j_b;
                    break;
                case 3:
                    map[i - 1][j] = 0;
                    i = i_h;
                    j = j_h;
                    break;
            }
            empiler(maPile, i, j);
            m += 1;
        } else {
            depiler(maPile);
            m -= 1;
            i = maPile->premier->i;
            j = maPile->premier->j;
            if (i == 0 && j == 0) {
                k = 1;
            }
        }
        if (m > end[0]) {
            end[0] = m;
            end[1] = i;
            end[2] = j;
        }
    }
    if (lv == 1) {
        map[1][1] = 1;
        map[0][1] = 2;
        map[end[1]][end[2]] = -2;
        randomizedItem(map, 12, 40, nblines, nbcolumns, lv);
    }
    if (lv == 2) {
        map[1][1] = 1;
        map[0][1] = 2;
        map[1][0] = -2;
        map[end[1]][end[2]] = -3;
        randomizedItem(map, 41, 70, nblines, nbcolumns, lv);
    }
    if (lv == 3) {
        map[1][1] = 1;
        map[0][1] = 2;
        map[1][0] = -3;
        map[end[1]][end[2]] = 99;
        randomizedItem(map, 71, 98, nblines, nbcolumns, lv);
    }
}

//free map
void freeMap(int **map, int nbLines){
    for(int i = 0; i < nbLines; i+=1)
    {
        free(map[i]);
    }
    free(map);
}