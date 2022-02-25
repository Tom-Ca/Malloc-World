/*
 * Filename: craft.h
 *
 * Made by: Erwan on 19/10/2021
 *
 * Description: this present file is used in order to craft and search if there is enough Item to craft.
 * It can:
 * Create an item and give it to the hero.
 * Check if the conditions of a craft are met.
 */

#ifndef CODE_C_LION_CRAFT_H
#define CODE_C_LION_CRAFT_H

#endif //CODE_C_LION_CRAFT_H
#include "character.h"

int crafting(Character* hero, int id);
int searchInInventory(Character* hero, int id, int quantity);
