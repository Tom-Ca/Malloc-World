/*
 * Filename: save.h
 *
 * Made by: Erwan on 24/10/2021
 *
 * Description: this present file is used in order to save and retrieve the save file in the game.
 * It can:
 * Save all the maps, the hero with his inventory, the chest even if it's empty.
 * Retrieve the map with its width and its height, retrieve the hero with his inventory, retrieve the chest.
 */

#ifndef CODE_C_LION_FILE_H
#define CODE_C_LION_FILE_H
#include "monster.h"

#include <string.h>
#endif //CODE_C_LION_FILE_H
int saveMap(int** map1, int** map2, int** map3, int height1, int height2, int height3, int width1, int width2, int width3);
int saveMapBis(int** map,int height,int width, int number);
int savePlayer(Character* hero);
int saveInventory(Character* hero, FILE* fp);
int saveChest(Chest* chest);
Character* retrieveInventory();
void retrieveStat(Character* hero);
int** retrieveMap(int map, int height, int width);
int retrieveWidth(int map);
int retrieveHeight(int map);
Chest *retrieveChest();
