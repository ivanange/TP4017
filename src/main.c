#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    printf("%d\n",convert(5,2));
    return 0;
}

Noeud* creer_ensemble(int x)
{
    Noeud *noeud = malloc(sizeof(Noeud));

    if (noeud == NULL)
    {
        exit(EXIT_FAILURE);
    }
    noeud->valeur = x;
    noeud->rang = 0;
    noeud->parent = noeud;

    return noeud;
}