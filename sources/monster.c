/*
 * Filename: monster.h
 *
 * Made by: tom on 11/10/2021
 *
 * Description: created the monster tab.
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "monster.h"

void creatMonster(Monster* monster){
    char* nam_monster[88] = {"Suzanne Moreno de la Colin", "Emilie Blanchard", "Etienne Guillou de la Nguyen",
                             "Philippe du Chauvet", "Diane Martin", "Sebastien-Maurice Julien", "Nicolas Charpentier", "Henri Royer",
                             "Stephane Chauvet", "Guy Millet", "Charles Techer-Pelletier", "Marie Begue", "Pauline-Amelie Tanguy",
                             "Maryse de Nguyen", "Timothee Mary", "Elisabeth Pottier", "Alphonse Clerc du Delaunay", "Antoine-Benoit Lucas",
                             "Corinne Perrot", "Yves Moulin", "Astrid Le Camus", "Denis Le Fischer", "Thierry-Jules Royer", "Aimee Renaud",
                             "Margot Langlois", "Honore Meunier de Ferrand", "Lucie de Devaux", "Adrienne Riou de la Dufour", "Etienne-Franck Lacroix",
                             "Arnaude Bouchet", "Georges-Hugues Fischer", "William du Joubert","Jean Blanchet","Catherine du Chauvet",
                             "Adèle Lejeune","Thibaut Bruneau","Gerard-Andre Camus","Timothee Delmas","Geneviève Le Leclerc","Victor Da Silva",
                             "Olivier-Bertrand Payet","Theodore Lelievre","Nathalie Normand","Denis Leleu","Colette Chevalier","Frederic Adam",
                             "Penelope Barbier","Roger Evrard","Paulette Paris Le Langlois","Benjamin de Olivier","Olivier Levy",
                             "Jerome Philippe du Rossi","Pierre Bouvier","Alexandrie Etienne","Rene Bigot-Charrier","Augustin Bourdon","Olivie Barbe",
                             "Christophe-Alphonse Marty","Inès de la Collet","Sophie-Alix Letellier","daisy Chartier","Vincent Gomez","Astrid Dufour",
                             "Alice Pasquier","Laetitia Torres","Christelle Thierry","Raymond Bonnet-Fouquet","Denis Prevost",
                             "Raymond Hebert","Noel Bonnin","Astrid Dufour","Christiane Bigot du Pelletier","Christiane Bigot du Pelletier",
                             "Richard Fabre","Sophie Schmitt","Catherine Dupuis-Dubois","Honore Riou","Marguerite Colin",
                             "Sebastien Imbert","Yves Lejeune","Colette Leleu","Arnaude Lefebvre Le Bouchet","Henriette Ramos",
                             "Alain Buisson","Amelie-Constance Nicolas","Isaac Le Lenoir","Aimee Rocher","THOR"};

    int hp[87]={0};
    int dps[87]={0};
    int j = 0;
    for(float i = 1.098; exp(i) < 20; i = i + 0.07){
        //printf("%d : %f\n", j+1,exp(i)+1);
        hp[j] = exp(i)+1;
        j++;
    }
    for(float i = 2.999; exp(i) < 50; i = i + 0.031){
        //printf("%d : %f\n", j+1,exp(i)+1);
        hp[j] = exp(i)+1;
        j++;
    }
    for(float i = 3.93; exp(i) < 100; i = i + 0.024){
        //printf("%d : %f\n", j+1,exp(i)+1);
        hp[j] = exp(i)+1;
        //printf("hp%d : %d\n", j,hp[j]);
        j++;
    }

    j=0;
    for(float i = 0; exp(i) < 6; i = i + 0.066){
        if(j+1 != 28){
            dps[j] = exp(i);
        } else{
            dps[j] = exp(i)+1;
        }
        j++;
    }
    for(float i = 1.782; exp(i) < 17; i = i + 0.036){
        dps[j] = exp(i)+2;
        j++;
    }
    for(float i = 2.85; exp(i) < 31; i = i + 0.0205){
        if(j+1 != 27){
            dps[j] = exp(i)+2;
        } else{
            dps[j] = exp(i)+3;
        }
        j++;
    }

    for (int i = 0; i != 87; i++){
        monster[i].name = nam_monster[i];
        monster[i].hp = hp[i];
        monster[i].dps = dps[i];
        monster[i].lvl = i+12;
        monster[i].exp = i+1;
    }
    monster[87].name = nam_monster[87];
    monster[87].hp = 201;
    monster[87].dps = 200;
    monster[87].lvl = 99;
    monster[87].exp = 0;

}