#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    Graph *graph = makeGraph("graph1.txt");
    int i = 0;
    int j = 1; 
    int n = graph->taille;

    for( i = 0; i < n;  i++ ) {

        Element *next = graph->sommets[0]->tete;
        printf("\n taille: %d \n", graph->sommets[i]->taille);
        while (next != NULL && j<=graph->sommets[i]->taille)
        {
            printf("\nvaleur: %d, poids: %d \n", next->valeur, next->poids);
            next = next->suivant;
            j = j + 1;
        }

        printf("\n\n");
    }
    return 0;
}

// print list
// Element *next = (sommets[i-1])->tete;
// while (next != NULL)
// {
//     printf("\nvaleur: %d, poids: %d \n", next->valeur, next->poids);
//     next = next->suivant;
// }