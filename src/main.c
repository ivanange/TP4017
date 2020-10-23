#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    Graph *graph = makeGraph("graph1.txt");
    printf("%d\n", graph->sommets[1]->tete->valeur);
        int i = 0; 
        int n = graph->taille;

    for( i = 0; i < n;  i++ ) {

        Element *next = graph->sommets[i]->tete;
        printf("\n taille: %d \n", graph->sommets[i]->taille);
        // printf("%d",graph->sommets[1]->tete->valeur);
        // Element *next = NULL;
        while (next != NULL)
        {
            printf("\nvaleur: %d, poids: %d \n", next->valeur, next->poids);
            next = next->suivant;
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