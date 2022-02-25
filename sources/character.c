/*
 * Filename: character.c
 *
 * Made by: Erwan on 11/10/2021
 *
 * Description: this present file is used in order to create, modify and check some characteristics of the character.
 */
#include "character.h"

// This function will give a new character
Character* createCharacter(){
    Character* hero;

    hero = malloc(sizeof(Character)*1);
    hero->hp = 100;
    hero->hpMax = 100;
    hero->exp = 0;
    hero->expMax = 60;
    hero->lvl = 1;
    hero->numberOfItem = 4;
    for(int i=1; i<11;i+=1){
        if(i<5){
            hero->inventory[i-1] = giveItemToHero(i,1);
        }else{
            hero->inventory[i - 1] = giveItemToHero(0, 0);
        }
    }
    return hero;
}

// This function will check if the character will level up and return 1 if so, 0 if not.
int isLevelingUp(Character* hero){
    if(hero->exp>=hero->expMax){
        return 1;
    }
    return 0;
}

// This function will make take care off the leveling up of a hero by modifying his characteristics.
Character* levelingUp(Character* hero){
    if(hero->lvl<10) {
        hero->exp = ((hero->exp)-(hero->expMax));
        hero->lvl = hero->lvl+1;
        switch (hero->lvl) {
            case 2:
                hero->hpMax = hero->hpMax + 10;
                hero->hp = hero->hpMax;
                hero->expMax = 80;
                break;
            case 3:
                hero->hpMax = hero->hpMax + 20;
                hero->hp = hero->hpMax;
                hero->expMax = 100;
                break;
            case 4:
                hero->hpMax = hero->hpMax + 30;
                hero->hp = hero->hpMax;
                hero->expMax = 150;
                break;
            case 5:
                hero->hpMax = hero->hpMax + 40;
                hero->hp = hero->hpMax;
                hero->expMax = 200;
                break;
            case 6:
                hero->hpMax = hero->hpMax + 50;
                hero->hp = hero->hpMax;
                hero->expMax = 250;
            case 7:
                hero->hpMax = hero->hpMax + 50;
                hero->hp = hero->hpMax;
                hero->expMax = 300;
            case 8:
                hero->hpMax = hero->hpMax + 50;
                hero->hp = hero->hpMax;
                hero->expMax = 380;
                break;
            case 9:
                hero->hpMax = hero->hpMax + 50;
                hero->hp = hero->hpMax;
                hero->expMax = 460;
            case 10:
                hero->hpMax = hero->hpMax + 75;
                hero->hp = hero->hpMax;
                break;
        }
    }
    return hero;
}

// This function will print all the characteristics of an inventory.
void printInventory(Character* hero){
    for(int i=0; i<10; i+=1){
        printf("%d %d %d %d %s\n", hero->inventory[i]->id,hero->inventory[i]->number,hero->inventory[i]->damageArmorHealth,hero->inventory[i]->durability, hero->inventory[i]->name);
    }
}

// This function will free the allocation of the inventory.
void freeInventory(Character* hero){
    for(int i=0; i<10; i+=1){
        freeItem(hero->inventory[i]);
    }
}

// This function will return the sum of a given ID's item. 0 is returned by default if there is no given ID's item in
// the inventory.
int howManyItemsInInventory(Character* hero, int idItem){
    int sum=0;
    for(int i=0; i<10;i+=1){
        if(hero->inventory[i]->id==idItem){
            sum+=1;
        }
    }
    return sum;
}

// This function will check if it can give an item and it's quantity. If so, it will give the said Item and return 1.
// If not, it will return 0.
int newItem(Character* hero, int idItem, int quantity){
    Items* newItem;
    int total = quantity;
    // Check if it's a resource. If so, it will check if it can add the quantity to the current stack. If it can add
    // the total quantity, it will complete the current stack and add another stack if the maximum number of item
    // in the inventory isn't reached yet.
    if(isARessource(idItem)){
        for(int i=9; i>=0;i-=1){
            if(idItem==hero->inventory[i]->id){
                if(total+hero->inventory[i]->number<=20){
                    hero->inventory[i]->number+=total;
                    return 1;
                }else{
                    total = (hero->inventory[i]->number+total)%20;
                    hero->inventory[i]->number = 20;
                    if(hero->numberOfItem>=10){
                        return 1;
                    }
                    newItem = malloc(sizeof(Items) * 1);
                    newItem = giveItemToHero(idItem, total);
                    hero->inventory[hero->numberOfItem] = newItem;
                    hero->numberOfItem += 1;
                    return 1;
                }
            }
        }
        newItem = malloc(sizeof(Items) * 1);
        newItem = giveItemToHero(idItem, quantity);
        hero->inventory[hero->numberOfItem] = newItem;
        hero->numberOfItem += 1;
        return 1;
    }else{
        if(hero->numberOfItem>=10){
            return 0;
        }
        newItem = malloc(sizeof(Items) * 1);
        newItem = giveItemToHero(idItem, quantity);
        hero->inventory[hero->numberOfItem] = newItem;
        hero->numberOfItem += 1;
    }
    return 0;
}

// This function will take of the given quantity of the given item's ID. The function will take care of all the item
// above that one and they will be moved to the previous space.
void takeOffItem(Character* hero, int idItem, int quantity){
    int total = quantity;
    for(int i=9; i>=0;i-=1){
        if(idItem==hero->inventory[i]->id){
            if(i+1==hero->numberOfItem){
                if(hero->inventory[i]->number>=total){
                    hero->inventory[i]->number-=total;
                    if(hero->inventory[i]->number==0){
                        setItemNull(hero->inventory[i]);
                        for(i;i<hero->numberOfItem;i+=1){
                            hero->inventory[i]=hero->inventory[i+1];
                        }
                        hero->numberOfItem-=1;
                    }
                    break;
                }else{
                    total -= hero->inventory[i]->number;
                    setItemNull(hero->inventory[i]);
                    hero->numberOfItem-=1;
                }
            }else{
                if(hero->inventory[i]->number>=total){
                    hero->inventory[i]->number-=total;
                    if(hero->inventory[i]->number==0){
                        setItemNull(hero->inventory[i]);
                        for(i;i<hero->numberOfItem;i+=1){
                            hero->inventory[i]=hero->inventory[i+1];
                        }
                        hero->numberOfItem -= 1;
                    }
                    break;
                }else{
                    total -= hero->inventory[i]->number;
                    setItemNull(hero->inventory[i]);
                    for(i;i<hero->numberOfItem;i+=1){
                        hero->inventory[i]=hero->inventory[i+1];
                    }
                    hero->numberOfItem -= 1;
                }
            }
        }
    }
}

// This function will find the given item's ID and return its location. Return -1 if not founded.
int findTheItem(Character* hero, int id){
    for(int i=9; i>=0;i-=1){
        if(hero->inventory[i]->id==id){
            return i;
        }
    }
    return -1;
}

// This function will return 1 if it's a tool, 0 if not.
int isATool(int id){
    if((id>1&&id<5)||(id>11&&id<15)||(id>22&&id<26)){
        return 1;
    }
    return 0;
}

// This function will return 1 if it's a weapon, 0 if not.
int isAWeapon(int id){
    if((id==1)||(id>7&&id<11)||(id>18&&id<22)||(id>29&&id<33)){
        return 1;
    }
    return 0;
}

// This function will return 1 if it's an armor, 0 if not.
int isAnArmor(int id){
    if(id==11||id==22||id==33){
        return 1;
    }
    return 0;
}

// This function will return 1 if it's a resource, 0 if not.
int isARessource(int id){
    if((id>4&&id<8)||(id>15&&id<19)||(id>26&&id<30)){
        return 1;
    }
    return 0;
}

// This function will repair all the item of a hero.
void repair(Character* hero){
    unsigned short itemDurability[34] = {10, 10, 10, 10, 0, 0, 0, 10, 8, 5, 0, 10, 10, 10, 0, 0, 0, 0, 10, 8, 5, 0, 10, 10, 10, 0, 0,
                                         0, 0, 10, 8, 5, 0, 0};
    for(int i=0; i<10; i+=1){
        if(isATool(hero->inventory[i]->id)||isAWeapon(hero->inventory[i]->id)||isAnArmor(hero->inventory[i]->id)){
            hero->inventory[i]->durability=itemDurability[(hero->inventory[i]->id)-1];
        }
    }
}