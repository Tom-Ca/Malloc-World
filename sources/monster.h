//
// Created by tomca on 28/10/2021.
//

#ifndef UNTITLED_MONSTER_H
#define UNTITLED_MONSTER_H

#endif //UNTITLED_MONSTER_H
#include <stdlib.h>
#include <stdio.h>
#include "craft.h"
struct Monster {
    int hp;
    int exp;
    int lvl;
    int dps;
    char* name;
};typedef struct Monster Monster;


void creatMonster(Monster* monster);