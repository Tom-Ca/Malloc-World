/*
 * Filename: interface.c
 *
 * Made by: Erwan and tom on 11/10/2021
 *
 * Description: this file handles all interactions with the user.
 */

#include "interface.h"

// main menu of the game
void mainMenu(){
    int choice=0;
    srand(time(NULL));

    do{
        printf("1. Nouvelle partie\n2. Continuer\n3. Quitter\n");
        scanf("%d",&choice);
        fflush(stdin);
        switch (choice) {
            case 1:
                loadGame(1);
                choice=3;
                break;
            case 2:
                loadGame(2);
                choice=3;
                break;
            case 3:
            default:
                break;
        }
    }while(choice!=3);
}

// generation of the games via either a backup or from the start
void loadGame(int choice){
    int width1;
    int width2;
    int width3;
    int height1;
    int height2;
    int height3;
    int **map1;
    int **map2;
    int **map3;
    int **copyMap1;
    int **copyMap2;
    int **copyMap3;
    int currentMap=0;
    Character *hero = malloc(sizeof(Character) * 1);
    Chest *chest = newItemChest(-1, 1);
    Monster* monster = malloc(87 * sizeof *monster);
    FILE *fp = fopen("../resources/save.txt", "rb");
    if(fgetc(fp)==EOF){
        choice = 1;
        printf("Pas de sauvegarde, chargement d'une nouvelle partie.\n");
    }
    if(choice==1){
        width1 = 15;
        width2 = 15;
        width3 = 15;
        height1 = 15;
        height2 = 15;
        height3 = 15;
        map1 = mallocMap(height1,width1);
        map2 = mallocMap(height2,width2);
        map3 = mallocMap(height3,width3);
        labyrinthe(map1, height1, width1, 1);
        labyrinthe(map2, height2, width2, 2);
        labyrinthe(map3, height3, width3, 3);

        hero = createCharacter();
        currentMap=1;
    }else{
        width1 = retrieveWidth(1);
        width2 = retrieveWidth(2);
        width3 = retrieveWidth(3);
        height1 = retrieveHeight(1);
        height2 = retrieveHeight(2);
        height3 = retrieveHeight(3);
        map1 = mallocMap(height1,width1);
        map2 = mallocMap(height2,width2);
        map3 = mallocMap(height3,width3);

        map1 = retrieveMap(1, height1, width1);
        map2 = retrieveMap(2, height2, width2);
        map3 = retrieveMap(3, height3, width3);
        hero = retrieveInventory();
        retrieveStat(hero);
        chest = retrieveChest();
        hero->numberOfItem = 10 - howManyItemsInInventory(hero,0);

        for(int i = 0; i<height1;i+=1){
            for(int j = 0; j<width1;j+=1){
                if(map1[i][j]==1){
                    currentMap = 1;
                }
            }
        }
        if(currentMap==0){
            for(int i = 0; i<height2;i+=1){
                for(int j = 0; j<width2;j+=1){
                    if(map2[i][j]==1){
                        currentMap = 2;
                    }
                }
            }
        }
        if(currentMap==0){
            currentMap = 3;
        }

    }
    creatMonster(monster);
    copyMap1 = copyMap(map1,height1,width1);
    copyMap2 = copyMap(map2,height2,width2);
    copyMap3 = copyMap(map3,height3,width3);
    coreGame(width1,width2,width3,height1,height2,height3,map1,map2,map3,copyMap1,copyMap2,copyMap3,hero,chest,monster,currentMap);
    freeGame(map1, map2, map3, copyMap1, copyMap2, copyMap3, height1, height2, height3, hero, chest);
}

// main loop of the game with the possible actions which the corresponding functions
void coreGame(int width1, int width2, int width3, int height1, int height2, int height3, int **map1, int **map2, int **map3, int **copyMap1, int **copyMap2, int **copyMap3, Character *hero, Chest *chest, Monster *monster, int currentMap){
    char movement;
    int quit = 0;
    int* pos = malloc(2*sizeof(int));

    while(quit == 0){
        if(currentMap == 1){
            display(map1,height1,width1);
        }else if(currentMap == 2){
            display(map2,height2,width2);
        }else if(currentMap == 3){
            display(map3,height3,width3);
        }else if(currentMap==-1){
            FILE *fp = fopen("save.txt", "w+");
            fclose(fp);
            printf("Vous Ãªtes mort.\n");
            break;
        }else if(currentMap==-2){
            break;
        }

        movement = track_movement();
        if(movement == 'm'){
            quit = exitMenu(width1, width2, width3, height1, height2, height3, copyMap1, copyMap2, copyMap3, hero, chest, currentMap);
        }else if(movement == 'e'){
            printInventory(hero);
        }else{
            if(currentMap == 1){
                currentMap = shifting(map1, copyMap1, height1, width1, movement, pos, currentMap, hero, chest, monster);
                if(currentMap==2){
                    map2[1][1]=1;
                    for(int i = 0; i<height1;i+=1){
                        for(int j = 0; j<width1;j+=1){
                            if(map1[i][j]==1){
                                map1[i][j]=0;
                            }
                        }
                    }
                }
            }else if(currentMap == 2){
                currentMap = shifting(map2, copyMap2, height2, width2, movement, pos, currentMap, hero, chest, monster);
                if(currentMap==3){
                    map3[1][1]=1;
                    for(int i = 0; i<height2;i+=1){
                        for(int j = 0; j<width2;j+=1){
                            if(map2[i][j]==1){
                                map2[i][j]=0;
                            }
                        }
                    }
                }else if(currentMap==1){
                    for(int i = 0; i<height2;i+=1){
                        for(int j = 0; j<width2;j+=1){
                            if(map2[i][j]==1){
                                map2[i][j]=0;
                            }
                        }
                    }
                    for(int i = 0; i<height1;i+=1){
                        for(int j = 0; j<width1;j+=1){
                            if(map1[i][j]==-3){
                                if(map1[i+1][j]!=-1){
                                    map1[i+1][j] = 1;
                                }else if(map1[i-1][j]!=-1){
                                    map1[i-1][j] = 1;
                                }else if(map1[i][j+1]!=-1){
                                    map1[i][j+1] = 1;
                                }else{
                                    map1[i][j-1] = 1;
                                }
                            }
                        }
                    }
                }
            }else if(currentMap == 3){
                currentMap = shifting(map3, copyMap3, height3, width3, movement, pos, currentMap, hero, chest, monster);
                if(currentMap==2){
                    for(int i = 0; i<height3;i+=1){
                        for(int j = 0; j<width3;j+=1){
                            if(map3[i][j]==1){
                                map3[i][j]=0;
                            }
                        }
                    }
                    for(int i = 0; i<height2;i+=1){
                        for(int j = 0; j<width2;j+=1){
                            if(map2[i][j]==-3){
                                if(map2[i+1][j]!=-1){
                                    map2[i+1][j] = 1;
                                }else if(map2[i-1][j]!=-1){
                                    map2[i-1][j] = 1;
                                }else if(map2[i][j+1]!=-1){
                                    map2[i][j+1] = 1;
                                }else{
                                    map2[i][j-1] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    free(pos);
}

// menu of the NPC which called the corresponding functions
void pnj(Character *hero, Chest *chest, int **map,int **copyOfTheMap, int currentMap, int height, int width){
    int choice;
    do {
        printf("0. Quitter\n1. Reparer\n2. Creer un objet\n3. Mettre dans le coffre\n4. Retirer du coffre\n5. Recharger la map\n");
        scanf("%d",&choice);
        switch (choice) {
            case 0:
                choice = 0;
                break;
            case 1:
                repair(hero);
                break;
            case 2:
                craftingInterface(hero,currentMap);
                break;
            case 3:
                putInChest(hero, chest);
                break;
            case 4:
                takeFromChest(hero, chest);
                break;
            case 5:
                for(int i = 0; i<height;i+=1){
                    for(int j = 0; j<width; j+=1){
                        map[i][j] = copyOfTheMap[i][j];
                    }
                }
                break;
            default:
                break;
        }
    } while (choice);
}

// craft menu
void craftingInterface(Character *hero, int currentMap){
    char* itemName[25] = {"Epee en bois // 3 sapins", "Pioche en bois // 3 sapins", "Serpe en bois // 3 sapins", "Hache en bois // 3 sapins",
                          "Epee en pierre // 2 sapins 3 pierres", "Lance en pierre // 3 sapins 4 pierres", "Marteau en pierre // 2 sapins 6 pierres", "Plastron en pierre // 10 pierres",
                          "Pioche en pierre // 2 sapins 3 pierres", "Serpe en pierre // 2 sapins 3 pierres", "Hache en pierre // 2 sapins 3 pierres", "Potion de vie I // 2 plantes I",
                          "Epee en fer // 2 hetres 4 minerais de fer", "Lance en fer // 3 hetres 5 minerais de fer", "Marteau en fer // 2 hetres 7 minerais de fer", "Plastron en fer // 12 fer",
                          "Pioche en fer // 2 hetres 4 minerais de fer", "Serpe en fer // 2 hetres 4 minerais de fer", "Hache en fer // 2 hetres 4 minerais de fer", "Potion de vie II // 2 plantes II",
                          "Epee en diamant // 2 chenes 5 minerais de diamant", "Lance en diamant // 3 chenes 6 minerais de diamant", "Marteau en diamant // 2 chenes 8 minerais de diamant", "Plastron en diamant // 16 minerais de diamants",
                          "Potion de vie III // 2 plantes III"};
    unsigned short id[25] = {1,2,3,4,8,9,10,11,12,13,14,15,19,20,21,22,23,24,25,26,30,31,32,33,34};
    int choice=4;
    int limit;

    if(currentMap==1){
        limit = 13;
    }else if(currentMap==2){
        limit = 21;
    }else{
        limit = 26;
    }

    do {
        printInventory(hero);
        printf("Craft:\n0. Quitter\n");
        for(int i=1;i<limit;i++){
            printf("%d. %s\n",i,itemName[i-1]);
        }
        scanf("%d",&choice);
        if(choice==0){
            break;
        }else if(currentMap==1&&choice>12){
            printf("Choix incorrect!\n");
        }else if(currentMap==2&&choice>20){
            printf("Choix incorrect!\n");
        }else if(choice<25&&choice>0){
            if(crafting(hero,id[choice-1])){
                printf("%s cree!\n",itemName[choice-1]);
            }else{
                printf("Choix incorrect!\n");
            }
        }else{
            printf("Choix incorrect.\n");
        }
    }while(1);
}

// menu to add items to the chest
void putInChest(Character *hero, Chest *chest){
    int choice = 1;
    int quantity;

    while (1){
        printf("0. Quitter\n");
        for(int i=0; i<10; i+=1){
            printf("%d. Quantite: %d Valeur: %d Durabilite: %d %s\n", i+1 ,hero->inventory[i]->number,hero->inventory[i]->damageArmorHealth,hero->inventory[i]->durability, hero->inventory[i]->name);
        }
        scanf("%d",&choice);
        if(choice==0){
            break;
        }else if(hero->inventory[choice-1]->id==0){
            printf("Choix incorrect.\n");
        }else if(choice<0||choice>10){
            printf("Choix incorrect.\n");
        }else{
            printf("Choisisez la quantite a mettre dans le coffre:\n");
            scanf("%d",&quantity);
            if(quantity>hero->inventory[choice-1]->number || quantity<1){
                printf("Choix incorrect.\n");
            }else{
                if(searchInChest(chest, hero->inventory[choice - 1]->id) &&
                   checkQtyItemInChest(chest, hero->inventory[choice - 1]->id)) {
                    appendQtyChoseItemInChest(chest, hero->inventory[choice - 1]->id, quantity);
                } else {
                    appendChest(chest, newItemChest(hero->inventory[choice - 1]->id, quantity));
                }
                takeOffItem(hero,hero->inventory[choice-1]->id,quantity);
            }
        }
    }
}

// menu to remove items from the chest
void takeFromChest(Character *hero, Chest *chest){
    Chest *copyChest = chest;
    int choice = 1;
    int counter = 1;
    int itemIdUndefined[34]={0};
    char* itemName[34] = {"Epee en bois", "Pioche en bois", "Serpe en bois", "Hache en bois", "Sapin", "Pierre",
                          "Herbe", "Epee en pierre", "Lance en pierre", "Marteau en pierre", "Plastron en pierre",
                          "Pioche en pierre", "Serpe en pierre", "Hache en pierre", "Potion de vie I", "Hetre", "Fer",
                          "Lavande", "Epee en fer", "Lance en fer", "Marteau en fer", "Plastron en fer",
                          "Pioche en fer", "Serpe en fer", "Hache en fer", "Potion de vie II", "Chene", "Diamant",
                          "Chanvre", "Epee en diamant", "Lance en diamant", "Marteau en diamant", "Plastron en diamant",
                          "Potion de vie III"};

    printf("Inventaire:\n");
    printInventory(hero);
    printf("0. Quitter\n");
    copyChest = copyChest->next;
    if(copyChest!=NULL){
        while (copyChest != NULL) {
            printf("%d. %s %d\n", counter, itemName[copyChest->id-1], copyChest->qty);
            itemIdUndefined[counter-1] = copyChest->id;
            counter+=1;
            copyChest = copyChest->next;
        }
    }else{
        printf("Coffre vide!\n");
    }

    while (1){
        scanf("%d",&choice);
        if(choice==0){
            break;
        }else if(choice>=counter || choice<0){
            printf("Choix incorrect.\n");
        }else{
            if(hero->numberOfItem==10 && howManyItemsInInventory(hero,itemIdUndefined[choice-1])%20==0&& isARessource(itemIdUndefined[choice-1])){
                printf("Pas assez de place dans l'inventaire.\n");
            }else if(hero->numberOfItem==10 && !(isARessource(itemIdUndefined[choice-1]))){
                printf("Pas assez de place dans l'inventaire.\n");
            }else{
                deleteAnItem(chest, itemIdUndefined[choice - 1]);
                newItem(hero,itemIdUndefined[choice-1],1);
                break;
            }
        }
    }
}

// harvest of resourse
int harvest(Character *hero, int ressourceID){
    int counter = 0;
    int choice;
    int itemIdUndefined[10] = {0};
    char *nameRessource;
    int idTool1;
    int idTool2;
    int idTool3;
    int neededDurability;

    if(ressourceID==7){
        nameRessource = "de l'herbe (1 d'usure).\n";
        idTool1 = 3;
        idTool2 = 13;
        idTool3 = 24;
        neededDurability = 1;
    }else if(ressourceID==6){
        nameRessource = "de la pierre (1 d'usure).\n";
        idTool1 = 2;
        idTool2 = 12;
        idTool3 = 23;
        neededDurability = 1;
    }else if(ressourceID==5){
        nameRessource = "un sapin (1 d'usure).\n";
        idTool1 = 4;
        idTool2 = 14;
        idTool3 = 25;
        neededDurability = 1;
    }else if(ressourceID==18){
        nameRessource = "de la lavande (2 d'usure).\n";
        idTool1 = 13;
        idTool2 = 13;
        idTool3 = 24;
        neededDurability = 2;
    }else if(ressourceID==17){
        nameRessource = "du fer (2 d'usure).\n";
        idTool1 = 12;
        idTool2 = 12;
        idTool3 = 13;
        neededDurability = 2;
    }else if(ressourceID==16){
        nameRessource = "de l'hÃªtre (2 d'usure).\n";
        idTool1 = 14;
        idTool2 = 14;
        idTool3 = 25;
        neededDurability = 2;
    }else if(ressourceID==29){
        nameRessource = "du chanvre (4 d'usure).\n";
        idTool1 = 24;
        idTool2 = 24;
        idTool3 = 24;
        neededDurability = 4;
    }else if(ressourceID==28){
        nameRessource = "du diamant (4 d'usure).\n";
        idTool1 = 23;
        idTool2 = 23;
        idTool3 = 23;
        neededDurability = 4;
    }else{
        nameRessource = "du chene (4 d'usure).\n";
        idTool1 = 25;
        idTool2 = 25;
        idTool3 = 25;
        neededDurability = 4;
    }

    printf("Vous etes tombe sur %s", nameRessource);
    if (!(searchInInventory(hero, idTool1, 1) || searchInInventory(hero, idTool2, 1) || searchInInventory(hero, idTool3, 1))) {
        printf("Vous n'avez pas les outils pour recolter la ressource.\n");
    } else {
        printf("Choisissez votre outils:\n");
        for (int i = 0; i < 10; i += 1) {
            if (hero->inventory[i]->id == idTool1 || hero->inventory[i]->id == idTool2 || hero->inventory[i]->id == idTool3) {
                if (hero->inventory[i]->durability >= neededDurability) {
                    itemIdUndefined[counter] = i;
                    counter += 1;
                    printf("%d %s durabilite: %d\n", counter, hero->inventory[i]->name,
                           hero->inventory[i]->durability);
                }
            }
        }
        if (counter == 0) {
            printf("Vous n'avez pas les outils necessaires!\n");
            return 0;
        }
        printf("0. Quitter\n");
        while (1) {
            scanf("%d", &choice);
            if (choice == 0) {
                break;
            } else if (choice > counter || choice < 0) {
                printf("Choix incorrect.\n");
            } else {
                hero->inventory[itemIdUndefined[choice - 1]]->durability = hero->inventory[itemIdUndefined[choice - 1]]->durability - neededDurability;
                newItem(hero,ressourceID,rand()%4+1);
                break;
            }
        }
    }
    return 0;
}

// menu to quit the game and save
int exitMenu(int width1, int width2, int width3, int height1, int height2, int height3, int **map1, int **map2, int **map3, Character *hero, Chest *chest, int currentMap){
    int choice;
    int sure;
    do {
        printf("1. Continue\n2. Save\n3. Save and Exit\n");
        scanf("%d",&choice);
        fflush(stdin);
        switch (choice) {
            case 1:
                return 0;
            case 2:
                save(width1, width2, width3, height1, height2, height3, map1, map2, map3, hero, chest, currentMap);
                return 0;
            case 3:
                printf("Etes-vous sur de vouloir quitter?\n1. Oui\n2. Non\n");
                scanf("%d", &sure);
                fflush(stdin);
                if(sure==1){
                    save(width1, width2, width3, height1, height2, height3, map1, map2, map3, hero, chest, currentMap);
                    return 1;
                }else{
                    break;
                }
            default:
                break;
        }
    } while (choice);
    return 1;
}

// save party in the file
void save(int width1, int width2, int width3, int height1, int height2, int height3, int **map1, int **map2, int **map3, Character *hero, Chest *chest, int currentMap){
    if(currentMap==1){
        map1[1][1] = 1;
        for(int i = 0; i<height2;i+=1) {
            for (int j = 0; j < width2; j += 1) {
                if (map2[i][j] == 1) {
                    map2[i][j] = 0;
                }
            }
        }
        for(int i = 0; i<height3;i+=1) {
            for (int j = 0; j < width3; j += 1) {
                if (map3[i][j] == 1) {
                    map3[i][j] = 0;
                }
            }
        }
    }else if(currentMap==2){
        for(int i = 0; i<height1;i+=1) {
            for (int j = 0; j < width1; j += 1) {
                if (map1[i][j] == 1) {
                    map1[i][j] = 0;
                }
            }
        }
        map2[1][1] = 1;
        for(int i = 0; i<height3;i+=1) {
            for (int j = 0; j < width3; j += 1) {
                if (map3[i][j] == 1) {
                    map3[i][j] = 0;
                }
            }
        }
    }else{
        for(int i = 0; i<height1;i+=1) {
            for (int j = 0; j < width1; j += 1) {
                if (map1[i][j] == 1) {
                    map1[i][j] = 0;
                }
            }
        }
        for(int i = 0; i<height2;i+=1) {
            for (int j = 0; j < width2; j += 1) {
                if (map2[i][j] == 1) {
                    map2[i][j] = 0;
                }
            }
        }
        map3[1][1] = 1;
    }
    if(saveMap(map1, map2, map3, height1, height2, height3, width1, width2, width3)){
        if(savePlayer(hero)){
            if(saveChest(chest)){

            }else{
                printf("Erreur sauvegarde coffre. Sauvegarde corrompue!\n");
            }
        }else{
            printf("Erreur sauvegarde joueur. Sauvegarde corrompue!\n");
        }
    }else{
        printf("Erreur sauvegarde carte. Sauvegarde corrompue!\n");
    }
}

// find the location of the character in the map
void find_character(int ** map, int nblines, int nbcolumns, int* pos)   //find the position of the character (1) in the map (the array)
{
    for(int i = 0; i < nblines; i++)
    {
        for(int j = 0; j < nbcolumns; j++)
        {
            if(map[i][j] == 1)
            {
                pos[0] = i;     //the X is in the first position of the array pos
                pos[1] = j;     //the y is in the second position of the array pos
            }
        }
    }
}

//asks for the movement to be made and verifies it
char track_movement()
{
    char movement = ' ';

    do{
        printf("\nDeplacez-vous\nz. Haut q. Gauche s. Bas d. Droite m. Quitter e. Inventaire\n");
        scanf("%c", &movement);
        fflush(stdin);
    }while (movement != 'z' && movement != 'q' && movement != 's' && movement != 'd' && movement !='m' && movement !='e');

    return movement;
}

// determinations of events according to the element on which we fall
int shifting(int **map, int **copyMap, int height, int width, char movement, int *pos, int currentMap, Character *hero, Chest *chest, Monster *monster)        //allows you to move
{
    find_character(map, height, width, pos);
    int x = pos[0];
    int y = pos[1];
    int resFight;

    if(movement == 'z'){        // put in x and y the new position of the character
        x-=1;
    }
    else if(movement == 'q')
    {
        y-=1;
    }
    else if(movement == 's')
    {
        x+=1;
    }
    else if(movement == 'd')
    {
        y+=1;
    }

    switch (map[x][y]) {        //check what we come across when we are moved
        case -3:
            // Portail entre zones || & |||
            if(currentMap==2){
                if(hero->lvl<7){
                    printf("Vous n'etes pas niveau 7 minimum.\n");
                    break;
                }else {
                    return 3;
                }
            }else{
                return 2;
            }
        case -2:
            // Portail entre zones | & ||
            if(currentMap==1){
                if(hero->lvl<3){
                    printf("Vous n'etes pas niveau 3 minimum.\n");
                    break;
                }else {
                    return 2;
                }
            }else{
                return 1;
            }
        case -1:
            printf("\nCase infranchissable\n");
            break;
        case 0:
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            printf("\nVous vous etes deplace\n");
            break;
        case 1:
            printf("\nJoueur, il y a un pb si ca fait :(\n");
            break;
        case 2:
            printf("\nPNJ\n");
            pnj(hero,chest,map,copyMap,currentMap,height,width);
            break;
        case 3:
            printf("\nPlante zone I\n");
            harvest(hero,7);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 4:
            printf("\nRocher zone I\n");
            harvest(hero,6);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 5:
            printf("\nBois zone I\n");
            harvest(hero,5);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 6:
            printf("\nPlante zone II\n");
            harvest(hero,18);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 7:
            printf("\nRocher zone II\n");
            harvest(hero,17);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 8:
            printf("\nBois zone II\n");
            harvest(hero,16);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 9:
            printf("\nPlante zone III\n");
            harvest(hero,29);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 10:
            printf("\nRocher zone III\n");
            harvest(hero,28);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 11:
            printf("\nBois zone III\n");
            harvest(hero,27);
            map[x][y] = 1;
            map[pos[0]][pos[1]] = 0;
            break;
        case 99:
            printf("\nBoss de fin\n");
            resFight = fight(hero,map[x][y],monster);
            if(resFight==-1){
                return -1;
            }else if(resFight==0){
                break;
            }else{
                printf("Vous avez vaincu THOR! FÃ©licitations!!!\n");
                return -2;
            }
            break;
        default:
            printf("\nMonster\n");
            resFight = fight(hero,map[x][y], monster);
            if(resFight==-1){
                return -1;
            }else if(resFight==0){
                break;
            }else{
                map[x][y] = 1;
                map[pos[0]][pos[1]] = 0;
            }
            break;
    }
    return currentMap;
}

// fight management
int fight(Character *hero, int monsterID, Monster *monster){
    Monster theMonster = monster[monsterID-12];
    int itemIdUndefined[10] = {0};
    int choice;
    int counter = 0;
    int fly = 1;

    while(hero->hp>0&&theMonster.hp>0&&fly){
        printf("Vous combattez %s\n%d points de vies\n%d d'attaque\n",theMonster.name,theMonster.hp,theMonster.dps);
        printf("Vous avez:\n%d/%d de points de vies\n",hero->hp,hero->hpMax);
        printf("Que voulez-vous faire?\n0. Fuir (30%% de chance)\n1. Potion\n2. Attaquer\n");
        scanf("%d",&choice);
        switch (choice) {
            case 0:
                if(rand()%10+1<=3){
                    fly = 0;
                    printf("Vous prenez la fuite!\n");
                    break;
                }else{
                    printf("Vous n'avez pas reussi a fuir!\n");
                    monsterAttack(hero,theMonster);
                }
                break;
            case 1:
                if((findTheItem(hero,15)!=-1 || findTheItem(hero,26)!=-1 || findTheItem(hero,34)!=-1)&&(hero->hp<hero->hpMax)){
                    counter = 0;
                    printf("Voulez-vous prendre une potion?\n0.Non\n1.Oui\n");
                    scanf("%d",&choice);
                    if(choice){
                        for (int i = 0; i < 10; i += 1) {
                            if (hero->inventory[i]->id == 15 || hero->inventory[i]->id == 26 || hero->inventory[i]->id == 34) {
                                itemIdUndefined[counter] = hero->inventory[i]->id;
                                counter += 1;
                                printf("%d. %s quantite: %d\n", counter, hero->inventory[i]->name, hero->inventory[i]->number);
                            }
                        }
                        printf("0. Quitter\n");
                        while (1) {
                            scanf("%d", &choice);
                            if (choice == 0) {
                                break;
                            } else if (choice > counter || choice < 0) {
                                printf("Choix incorrect.\n");
                            } else {
                                for(int i = 0; i<10; i++){
                                    if(hero->inventory[i]->id==itemIdUndefined[choice - 1]){
                                        hero->hp = hero->hp + hero->inventory[i]->damageArmorHealth;
                                    }
                                }
                                takeOffItem(hero,itemIdUndefined[choice - 1],1);
                                if(hero->hp>hero->hpMax){
                                    hero->hp = hero->hpMax;
                                }
                                monsterAttack(hero,theMonster);
                            }
                            break;
                        }
                    }
                }else{
                    printf("Vous n'avez pas de potions!\n");
                }
                break;
            case 2:
                counter = 0;
                for (int i = 0; i < 10; i += 1) {
                    if (isAWeapon(hero->inventory[i]->id)) {
                        itemIdUndefined[counter] = i;
                        counter += 1;
                        printf("%d. %s durabilite: %d degats: %d\n", counter, hero->inventory[i]->name, hero->inventory[i]->durability, hero->inventory[i]->damageArmorHealth);
                    }
                }
                printf("0. Quitter\n");
                while (1) {
                    scanf("%d", &choice);
                    if (choice == 0) {
                        break;
                    } else if (choice > counter || choice < 0) {
                        printf("Choix incorrect.\n");
                    } else {
                        if(hero->inventory[choice-1]->durability==0){
                            printf("Pas assez de durabilite!\n");
                        }else{
                            theMonster.hp = theMonster.hp - hero->inventory[itemIdUndefined[choice-1]]->damageArmorHealth;
                            hero->inventory[itemIdUndefined[choice-1]]->durability -= 1;
                        }
                        monsterAttack(hero,theMonster);
                    }
                    break;
                }
                break;
            default:
                break;
        }
    }
    if(fly==0){
        return fly;
    }else if(hero->hp==0){
        return -1;
    }else{
        hero->exp += theMonster.exp;
        if(isLevelingUp(hero)){
            levelingUp(hero);
        }
        return 1;
    }
}

//monstre turn
void monsterAttack(Character* hero, Monster monster){
    int armorValue=0;
    float valueArmor;

    for(int i=0; i<10; i+=1){
        if(isAnArmor(hero->inventory[i]->id)){
            if(hero->inventory[i]->damageArmorHealth>armorValue){
                armorValue = hero->inventory[i]->damageArmorHealth;
            }
        }
    }
    valueArmor = (float)(1-((float)armorValue/100));
    hero->hp = hero->hp - (monster.dps*(valueArmor));
    if (hero->hp<0){
        hero->hp = 0;
    }
}

// free the memory of all mallocs
void freeGame(int **map1, int **map2, int **map3, int **copyMap1, int **copyMap2, int **copyMap3, int height1, int height2, int height3, Character *hero, Chest *chest){
    freeInventory(hero);
    free(hero);
    freeMap(map1, height1);
    freeMap(map2, height2);
    freeMap(map3, height3);
    freeChest(chest);
}