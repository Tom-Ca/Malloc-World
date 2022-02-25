/*
 * Filename: items.h
 *
 * Made by: Erwan on 11/10/2021
 *
 * Description: this present file is used in order to define the items of the game.
 * It can:
 * Free the malloc of the items.
 * Set a NULL Item.
 * Give an item to the Hero.
 */

#ifndef CODE_C_LION_ITEMS_H
#define CODE_C_LION_ITEMS_H

#endif //CODE_C_LION_ITEMS_H

#include <stdio.h>
#include <stdlib.h>

struct Items{
    int id;
    int number;
    int damageArmorHealth;
    int durability;
    char* name;
};
typedef struct Items Items;

void freeItem(Items* item);
void setItemNull(Items* item);
Items* giveItemToHero(int i, int number);