/*
 * Filename: save.h
 *
 * Made by: Erwan on 24/10/2021
 *
 * Description: this present file is used in order to save and retrieve the save file in the game.
 */

#include "save.h"

// This function will return 1 if it achieves to save all the maps. 0 if not.
int
saveMap(int **map1, int **map2, int **map3, int height1, int height2, int height3, int width1, int width2, int width3) {
    FILE *fp = fopen("../resources/save.txt", "w+");
    if (fp != NULL) {
        fputs("=== MAP ===\n", fp);
        fclose(fp);
        if (saveMapBis(map1, height1, width1, 1)) {
            if (saveMapBis(map2, height2, width2, 2)) {
                if (saveMapBis(map3, height3, width3, 3)) {
                    return 1;
                }
                return 0;
            }
            return 0;
        }
    }
    return 0;
}

// This function will save all the maps by taking the height, the width and the number of the give map.
int saveMapBis(int **map, int height, int width, int number) {
    FILE *fp = fopen("../resources/save.txt", "ab");
    if (fp != NULL) {
        switch (number) {
            case 1:
                fputs("-- ZONE 1 --\n", fp);
                break;
            case 2:
                fputs("-- ZONE 2 --\n", fp);
                break;
            case 3:
                fputs("-- ZONE 3 --\n", fp);
                break;
            default:
                break;
        }
        for (int i = 0; i < height; i += 1) {
            for (int j = 0; j < width; j += 1) {
                if (j != width - 1) {
                    fprintf(fp, "%d ", map[i][j]);
                } else {
                    fprintf(fp, "%d", map[i][j]);
                }
            }
            fputs("\n", fp);
        }
        fclose(fp);
        return 1;
    }
    return 0;
}

// This function will save the characteristics of a hero and will save the inventory later.
int savePlayer(Character *hero) {
    FILE *fp = fopen("../resources/save.txt", "ab");
    if (fp != NULL) {
        fputs("=== PLAYER ===\n", fp);
        fprintf(fp, "{%d}\n{%d}/{%d}\n{%d}/{%d}\n", hero->lvl, hero->exp, hero->expMax, hero->hp, hero->hpMax);
        saveInventory(hero, fp);
        fclose(fp);
        return 1;
    }
    return 0;
}

// This function will save the inventory of a hero
int saveInventory(Character *hero, FILE *fp) {
    if (fp != NULL) {
        fputs("-- INVENTORY --\n", fp);
        for (int i = 0; i < 10; i += 1) {
            fprintf(fp, "{%d}@{%d}@{%d}\n", hero->inventory[i]->number, hero->inventory[i]->id,
                    hero->inventory[i]->durability);
        }
        return 1;
    }
    return 0;
}

// This function will save a chest by starting to the second item. The first one being -1 (null item mandatory for the
// good execution of the game).
int saveChest(Chest* chest){
    FILE *fp = fopen("../resources/save.txt", "ab");
    if (fp != NULL) {
        fputs("-- STORAGE --\n", fp);
        chest = chest->next;
        while (chest != NULL) {
            fprintf(fp, "{%d}@{%d}\n", chest->id, chest->qty);
            chest = chest->next;
        }
        fclose(fp);
        return 1;
    }
    return 0;
}

// This function will read the save and retrieve the inventory of the hero
Character *retrieveInventory() {
    Character *hero;
    FILE *fp = fopen("../resources/save.txt", "rb");
    int durability;
    int id;
    int number;
    char text[2000];
    char *sentence = "-- INVENTORY --\n";

    hero = malloc(sizeof(Character) * 1);
    if (fp != NULL) {
        while (fgets(text, 2000, fp) != NULL) {
            if ((strstr(text, sentence)) != NULL) {
                for (int i = 0; i < 10; i += 1) {
                    fscanf(fp, "{%d}@{%d}@{%d}\n", &number, &id, &durability);
                    hero->inventory[i] = giveItemToHero(id, number);
                    hero->inventory[i]->durability = durability;
                }
            }
        }
    }
    fclose(fp);
    return hero;
}

// This function will read the save and retrieve the statistics of the hero
void retrieveStat(Character* hero){
    FILE *fp = fopen("../resources/save.txt", "rb");
    char *sentence = "=== PLAYER ===\n";
    char text[2000];
    if (fp != NULL) {
        while (fgets(text, 2000, fp) != NULL) {
            if ((strstr(text, sentence)) != NULL) {
                fscanf(fp, "{%d}\n", &hero->lvl);
                fscanf(fp, "{%d}/{%d}\n", &hero->exp, &hero->expMax);
                fscanf(fp, "{%d}/{%d}\n", &hero->hp, &hero->hpMax);
            }
        }
    }
    fclose(fp);
}

// This function will retrieve the map if a number of the map, height and width are given.
int **retrieveMap(int map, int height, int width) {
    int **map_zone = malloc(height * sizeof(int *));
    FILE *fp = fopen("../resources/save.txt", "rb");
    char text[2000];
    char *sentence;
    if (map == 1) {
        sentence = "-- ZONE 1 --\n";
    } else if (map == 2) {
        sentence = "-- ZONE 2 --\n";
    } else if (map == 3) {
        sentence = "-- ZONE 3 --\n";
    } else {
        return 0;
    }
    if (fp != NULL) {
        while (fgets(text, 2000, fp) != NULL) {
            if ((strstr(text, sentence)) != NULL) {
                for (int i = 0; i < height; i += 1) {
                    map_zone[i] = malloc(width * sizeof(int));
                    for (int j = 0; j < width; j += 1) {
                        if (j == width - 1) {
                            fscanf(fp, "%d\n", &map_zone[i][j]);
                        } else {
                            fscanf(fp, "%d ", &map_zone[i][j]);
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    return map_zone;
}

// This function will retrieve the width of a saved map by only taking the number of the said map.
// It will not work if there is no map, and it only counts the spaces and stop when there is a chariot return.
int retrieveWidth(int map) {
    FILE *fp = fopen("../resources/save.txt", "rb");
    int width = 1;
    char currentCharacter = ' ';
    char text[2000];
    char *sentence;

    if (map == 1) {
        sentence = "-- ZONE 1 --\n";
    } else if (map == 2) {
        sentence = "-- ZONE 2 --\n";
    } else if (map == 3) {
        sentence = "-- ZONE 3 --\n";
    } else {
        return 0;
    }

    if (fp != NULL) {
        while (fgets(text, 2000, fp) != NULL) {
            if ((strstr(text, sentence)) != NULL) {
                while (currentCharacter != '\n') {
                    currentCharacter = fgetc(fp);
                    if (currentCharacter == ' ') {
                        width += 1;
                    }
                }
                break;
            }
        }
    }
    fclose(fp);
    return width;
}

// This function will retrieve the height of a saved map by only taking the number of the said map.
// It will not work if there is no map, and it only counts the carriage return and will stop if there is two minus
// consecutively.
int retrieveHeight(int map) {
    FILE *fp = fopen("../resources/save.txt", "rb");
    int height = 0;
    char text[2000];
    char *sentence;
    char currentCharacter = ' ';
    char nextCharacter = ' ';

    if (map == 1) {
        sentence = "-- ZONE 1 --\n";
    } else if (map == 2) {
        sentence = "-- ZONE 2 --\n";
    } else if (map == 3) {
        sentence = "-- ZONE 3 --\n";
    } else {
        return 0;
    }
    if (fp != NULL) {
        while (fgets(text, 2000, fp) != NULL) {
            if ((strstr(text, sentence)) != NULL) {
                while (currentCharacter != '=') {
                    currentCharacter = fgetc(fp);
                    if (currentCharacter == '\n') {
                        height += 1;
                        continue;
                    }
                    if (currentCharacter == '-') {
                        nextCharacter = fgetc(fp);
                        if (nextCharacter == '-') {
                            break;
                        } else {
                            fseek(fp, -1, SEEK_CUR);
                        }
                    }
                }
                break;
            }
        }
    }
    fclose(fp);
    return height;
}

// This function will retrieve the chest of a saved game.
// It will work if there is no chest, and it will stop at the end of a file.
Chest *retrieveChest(){
    Chest* chest = newItemChest(-1, 1);
    FILE *fp = fopen("../resources/save.txt", "rb");
    char *sentence = "-- STORAGE --\n";
    char text[2000];
    int idFound;
    int quantityFound;

    if (fp != NULL) {
        while (fgets(text, 2000, fp) != NULL) {
            if ((strstr(text, sentence)) != NULL) {
                while(fscanf(fp, "{%d}@{%d}\n", &idFound, &quantityFound) != EOF){
                    appendChest(chest, newItemChest(idFound, quantityFound));
                }
            }
        }
    }
    fclose(fp);
    return chest;
}
/*
 * Chest *newItemChest(int id) {
    Chest *l1 = malloc(sizeof(Chest));
    l1->id = id;
    l1->qty = 1;
    l1->next = NULL;
    return l1;
}
 * void appendChest(Chest *head, Chest *last) {
        while (head->next != NULL) {
            head = head->next;
        }
        head->next = last;
    }
 */