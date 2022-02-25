#ifndef DEF_JEU
#define DEF_JEU

struct Element
{
    int i;
    int j;
    struct Element *next;
};typedef struct Element Element;

struct Pile
{
    Element *premier;
};typedef struct Pile Pile;

void randomizedItem(int **map, int weak_monster, int strong_monster, int nblines, int nbcolumns, int currentMap);
void labyrinthe(int** map,int nblines, int nbcolumns, int lv);
void empiler(Pile *pile, int i, int j);
void depiler(Pile *pile);
void display(int **map, int nblines, int nbcolumns);
int **mallocMap(int height, int width);
int **copyMap(int **map, int height, int width);
void freeMap(int **map, int nbLines);

#endif