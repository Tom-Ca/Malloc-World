/*
 * Filename: Chest.c
 *
 * Made by: Tom on 11/10/2021
 *
 * Description: this file groups the functions of the chest.
 */


#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Chest.h"

Chest *newItemChest(int id, int qty) {      // allows you to create an item for the chest
    Chest *l1 = malloc(sizeof(Chest));
    l1->id = id;
    l1->qty = qty;
    l1->next = NULL;
    return l1;
}

void freeChest(Chest *l1) {     // free the memory of the whole chest
    if (l1->next != NULL) {
        freeChest(l1->next);
    }
    free(l1);
}

void printChest(Chest *l1) {        // allows to display the whole chest

    l1 = l1->next;
    while (l1 != NULL) {
        printf("%d %d\n",l1->id, l1->qty);
        l1 = l1->next;
    }
}

void appendChest(Chest *head, Chest *last) {        // allows you to add an item at the end of the chest
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = last;
}

Chest *deleteAnItem(Chest *l1, int id_search) {     // remove 1 item from the list, if it is the last one it removes it from the chest
    Chest *l2 = l1;
    while (l1->id != id_search) {
        l1 = l1->next;
    }
    if (l1->qty > 1) {
        l1->qty -= 1;
    } else{
        while (l2->next != l1) {
            l2 = l2->next;
        }
        l2->next = l1->next;
        free(l1);
    }
}

int searchInChest(Chest *l1, int id_search) {       // check if the item is in the chest

    while (l1 != NULL) {
        if (l1->id == id_search) {
            return 1;
        } else {
            l1 = l1->next;
        }
    }
    return 0;
}

int checkQtyItemInChest(Chest *l1, int id_search) {     //check if the item does not have too many occurrences
    while (l1 != NULL) {
        if (l1->id == id_search) {
            if (l1->qty <= 32766) {
                return 1;
            } else {
                return 0;
            }
        } else {
            l1 = l1->next;
        }
    }

}

void appendQtyItemInChest(Chest *l1, int id_search) {       //adds a 1 quantity to the chest of an item
    while (l1->id != id_search && l1->qty < 32766) {
        l1 = l1->next;
    }
    l1->qty += 1;
}


void appendQtyChoseItemInChest(Chest *l1, int id_search, int qty) {     //adds a desired quantity to the chest of an item
    while (l1->id != id_search && l1->qty < 32766) {
        l1 = l1->next;
    }
    l1->qty += qty;
}

Chest *deleteQtyAnItem(Chest *l1, int id_search, int qty) {     //delete a desired quantity to the chest of an item
    Chest *l2 = l1;
    while (l1->id != id_search) {
        l1 = l1->next;
    }
    if (l1->qty > qty) {
        l1->qty -= qty;
    } else if(l1->qty == qty){
        while (l2->next != l1) {
            l2 = l2->next;
        }
        l2->next = l1->next;
        free(l1);
    }
}