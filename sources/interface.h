//
// Created by erwan on 03/11/2021.
//

#ifndef CODE_C_LION_INTERFACE_H
#define CODE_C_LION_INTERFACE_H

#endif //CODE_C_LION_INTERFACE_H
#include "map.h"
#include "save.h"
#include <time.h>

void mainMenu();
void loadGame(int choice);
void coreGame(int width1, int width2, int width3, int height1, int height2, int height3, int **map1, int **map2, int **map3, int **copyMap1, int **copyMap2, int **copyMap3, Character *hero, Chest *chest, Monster *monster, int currentMap);
void pnj(Character *hero, Chest *chest, int **map,int **copyMap, int currentMap, int height, int width);
void craftingInterface(Character *hero, int currentMap);
void putInChest(Character *hero, Chest *chest);
void takeFromChest(Character *hero, Chest *chest);
int harvest(Character *hero, int ressourceID);
int exitMenu(int width1, int width2, int width3, int height1, int height2, int height3, int **map1, int **map2, int **map3, Character *hero, Chest *chest, int currentMap);
void save(int width1, int width2, int width3, int height1, int height2, int height3, int **map1, int **map2, int **map3, Character *hero, Chest *chest, int currentMap);
void find_character(int ** map, int nblines, int nbcolumns, int* pos);
char track_movement();
int shifting(int **map, int **copyMap, int height, int width, char movement, int *pos, int currentMap, Character *hero, Chest *chest, Monster *monster);        //allows you to move
int fight(Character *hero,int monsterID, Monster *monster);
void monsterAttack(Character* hero, Monster monster);
void freeGame(int **map1, int **map2, int **map3, int **copyMap1, int **copyMap2, int **copyMap3, int height1, int height2, int height3, Character *hero, Chest *chest);