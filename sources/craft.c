/*
 * Filename: craft.h
 *
 * Made by: Erwan on 19/10/2021
 *
 * Description: this present file is used in order to craft and search if there is enough Item to craft.
 */

#include "craft.h"

// This function will craft the given item's ID by taking off the resources needed. It will return 1 if it is done, 0
// if not.
int crafting(Character* hero, int id) {
    if (id >= 1 && id <= 4) {
        if (searchInInventory(hero, 5, 3)) {
            takeOffItem(hero, 5, 3);
            newItem(hero, id, 1);
            return 1;
        }
        return 0;
    } else if (id==8||(id>=12&&id<=14)) {
        if (searchInInventory(hero, 5, 2)&& searchInInventory(hero,6,3)) {
            takeOffItem(hero, 5, 2);
            takeOffItem(hero, 6, 3);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==19||(id>=23&&id<=25)){
        if (searchInInventory(hero, 16, 2)&& searchInInventory(hero,17,4)) {
            takeOffItem(hero, 16, 2);
            takeOffItem(hero, 17, 4);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==30){
        if (searchInInventory(hero, 27, 2)&& searchInInventory(hero,28,5)) {
            takeOffItem(hero, 27, 2);
            takeOffItem(hero, 28, 5);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==9){
        if (searchInInventory(hero, 5, 3)&& searchInInventory(hero,6,4)) {
            takeOffItem(hero, 5, 3);
            takeOffItem(hero, 6, 4);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==20){
        if (searchInInventory(hero, 16, 3)&& searchInInventory(hero,17,5)) {
            takeOffItem(hero, 16, 3);
            takeOffItem(hero, 17, 5);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==31){
        if (searchInInventory(hero, 27, 3)&& searchInInventory(hero,28,6)) {
            takeOffItem(hero, 27, 3);
            takeOffItem(hero, 28, 6);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==10){
        if (searchInInventory(hero, 5, 2)&& searchInInventory(hero,6,6)) {
            takeOffItem(hero, 5, 2);
            takeOffItem(hero, 6, 6);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==21){
        if (searchInInventory(hero, 16, 2)&& searchInInventory(hero,17,7)) {
            takeOffItem(hero, 16, 2);
            takeOffItem(hero, 17, 7);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==32){
        if (searchInInventory(hero, 27, 2)&& searchInInventory(hero,28,8)) {
            takeOffItem(hero, 27, 2);
            takeOffItem(hero, 28, 8);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==11){
        if (searchInInventory(hero, 6, 10)) {
            takeOffItem(hero, 6, 10);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==22){
        if (searchInInventory(hero, 17, 12)) {
            takeOffItem(hero, 17, 12);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==33){
        if (searchInInventory(hero, 28, 16)) {
            takeOffItem(hero, 28, 16);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==15){
        if (searchInInventory(hero, 7, 2)) {
            takeOffItem(hero, 7, 2);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==26){
        if (searchInInventory(hero, 18, 2)) {
            takeOffItem(hero, 18, 2);
            newItem(hero, id, 1);
            return 1;
        }
    }else if(id==34){
        if (searchInInventory(hero, 29, 2)) {
            takeOffItem(hero, 29, 2);
            newItem(hero, id, 1);
            return 1;
        }
    }
    return 0;
}

// This function will check in the inventory if there is enough quantity of an item in the inventory. It will return 1
// if so, 0 if not.
int searchInInventory(Character* hero, int id, int quantity){
    for(int i=0;i<hero->numberOfItem;i+=1){
        if(id==hero->inventory[i]->id){
            if(hero->inventory[i]->number>=quantity){
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
/*
int searchInInventoryWithDurability(Character* hero, int id){
    for(int i=0;i<hero->numberOfItem;i+=1){
        if(id==hero->inventory[i]->id){
            return hero->inventory[i]->durability;
        }
    }
    return 0;
}
 */