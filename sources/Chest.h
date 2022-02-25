//
// Created by tomca on 28/10/2021.
//

#ifndef UNTITLED_CHEST_H
#define UNTITLED_CHEST_H

#endif //UNTITLED_CHEST_H
#include <stdlib.h>
#include <stdio.h>
#include "items.h"
struct Chest {
    int id;
    int qty;
    struct Chest* next;
};typedef struct Chest Chest;

void freeChest(Chest* l1);
void printChest(Chest* l1);
void appendQtyItemInChest(Chest* l1, int id_search);
int searchInChest(Chest* l1, int id_search);
int checkQtyItemInChest(Chest *l1, int id_search);
void appendChest(Chest* head, Chest* last);
Chest *deleteAnItem(Chest *l1, int id_search);
void creatChest();
Chest* newItemChest(int id, int qty);
void appendQtyChoseItemInChest(Chest *l1, int id_search, int qty);
Chest *deleteQtyAnItem(Chest *l1, int id_search, int qty);