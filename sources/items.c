/*
 * Filename: items.h
 *
 * Made by: Erwan on 11/10/2021
 *
 * Description: this present file is used in order to define the items of the game.
 */
#include "items.h"


// This function will free the name and the item in the inventory.
void freeItem(Items* item){
    if(item->name!=NULL){
        free(item->name);
        free(item);
    }
}

//This function will reset a space in the inventory by making it "null" if it's not already done.
void setItemNull(Items* item){
    if(item->name!=NULL){
        free(item->name);
        item->name = "";
        item->durability = 0;
        item->damageArmorHealth = 0;
        item->number = 0;
        item->id = 0;
    }
}

//This function will return an item that correspond to a given ID and quantity.
Items* giveItemToHero(int i, int number){
    Items* item;
    char* itemName[34] = {"Epee en bois", "Pioche en bois", "Serpe en bois", "Hache en bois", "Sapin", "Pierre",
                       "Herbe", "Epee en pierre", "Lance en pierre", "Marteau en pierre", "Plastron en pierre",
                       "Pioche en pierre", "Serpe en pierre", "Hache en pierre", "Potion de vie I", "Hetre", "Fer",
                       "Lavande", "Epee en fer", "Lance en fer", "Marteau en fer", "Plastron en fer",
                       "Pioche en fer", "Serpe en fer", "Hache en fer", "Potion de vie II", "Chene", "Diamant",
                       "Chanvre", "Epee en diamant", "Lance en diamant", "Marteau en diamant", "Plastron en diamant",
                       "Potion de vie III"};
    unsigned short itemDamageArmorHealth[34] = {1, 0, 0, 0, 0, 0, 0, 2, 3, 4, 10, 0, 0, 0, 30, 0, 0, 0, 5, 7, 10, 20, 0, 0, 0, 80, 0,
                                 0, 0, 10, 15, 20, 40, 200};
    unsigned short itemDurability[34] = {10, 10, 10, 10, 0, 0, 0, 10, 8, 5, 0, 10, 10, 10, 0, 0, 0, 0, 10, 8, 5, 0, 10, 10, 10, 0, 0,
                                     0, 0, 10, 8, 5, 0, 0};
    item = malloc(sizeof(Items)*1);
    item->id=i;
    i-=1;
    if(i<0||i>33){
        item->name = "";
        item->damageArmorHealth = 0;
        item->durability = 0;
        item->number=0;
    }else{
        item->name = itemName[i];
        item->damageArmorHealth = itemDamageArmorHealth[i];
        item->durability = itemDurability[i];
        item->number = number;
    }
    return item;
}