/*
 * Filename: character.h
 *
 * Made by: Erwan on 11/10/2021
 *
 * Description: this present file is used in order to create, modify and check some characteristics of the character.
 * It can:
 * Create a character from nothing.
 * Manage the leveling up by checking the current experience and level.
 * Display the inventory.
 * Free the malloc of the inventory.
 * Check how many items when given an ID.
 * Give a new item only if there is enough space.
 * Taking of a quantity of a given ID's item.
 * Find the emplacement of an item.
 * Check if an ID is a tool, a weapon, an armor or a resource.
 * Repair all the items that needs to be repaired.
 */


#ifndef CODE_C_LION_CHARACTER_H
#define CODE_C_LION_CHARACTER_H

#endif //CODE_C_LION_CHARACTER_H
#include <stdlib.h>
#include <stdio.h>
#include "Chest.h"

struct Character {
    int hp;
    int hpMax;
    int exp;
    int expMax;
    int lvl;
    int numberOfItem;
    Items* inventory[10];
};typedef struct Character Character;

Character* createCharacter();
int isLevelingUp(Character* hero);
Character* levelingUp(Character* hero);
void printInventory(Character* hero);
void freeInventory(Character* hero);
int howManyItemsInInventory(Character* hero, int idItem);
int newItem(Character* hero, int idItem, int quantity);
void takeOffItem(Character* hero, int idItem, int quantity);
int findTheItem(Character* hero, int id);
int isATool(int id);
int isAWeapon(int id);
int isAnArmor(int id);
int isARessource(int id);
void repair(Character* hero);