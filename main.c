#include <stdio.h>
#include <stdlib.h>




typedef struct Noeud Noeud;
struct Noeud
{
    int valeur;
    int cle;
    Noeud *parent;
};

typedef struct Arete Arete;
struct Arete
{
    Noeud *source;
    Noeud *destination;
    int poids;
};

typedef struct Element2 Element2;
struct Element2
{
    Noeud *sommet;
    Element2 *suivant;
};
typedef struct File File;
struct File
{
    Element2 *premier;
};




void enfiler(File *file, Noeud *nvNoeud);
Noeud* creer_ensemble(int x);
void afficherFile(File *file);
Noeud* extraireMin(File *file);

int main()
{
    Element2 *e1 = malloc(sizeof(Element2));
    //Element2 *e2 = malloc(sizeof(Element2));
    Noeud *n1 = creer_ensemble(2);
    Noeud *n2 = creer_ensemble(2);
    Noeud *n3 = creer_ensemble(2);
    n1->cle = 50;
    n2->cle = 1000;
    n3->cle = 500;
    e1->suivant = NULL;
    e1->sommet = n1;
    //e2->sommet = n2;
    File *fil = malloc(sizeof(File));
    fil->premier = e1;
    enfiler(fil,n2);
    enfiler(fil,n3);

    //extraireMin(fil);
    printf("%d\n\n", extraireMin(fil)->cle);
    afficherFile(fil);

    return 0;
}



void enfiler(File *file, Noeud *nvNoeud)
{
    Element2 *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
    exit(EXIT_FAILURE);
    }
    nouveau->sommet = nvNoeud;
    nouveau->suivant = NULL;
    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element2 *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
    file->premier = nouveau;
    }
}


Noeud* extraireMin(File *file)
{
    int min;
    Noeud *n1 = NULL;
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
/* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        Element2 *elementDefile = file->premier;
        Element2 *precedent = NULL;
        min = elementDefile->sommet->cle;
        //printf("%d\n", elementDefile->suivant);
        //printf("%d\n", min);
        Element2 *elementActuel = file->premier;
        n1 = elementActuel->sommet;
        while (elementActuel->suivant != NULL)
        {
            if(elementActuel->suivant->sommet->cle < min)
            {
                precedent = elementActuel;
                elementActuel = elementActuel->suivant;
                n1 = elementActuel->sommet;
                min = elementActuel->sommet->cle;

                printf("%d\n", min);
            }
            else elementActuel = elementActuel->suivant;
            //printf("yess");

        }


        if(precedent == NULL)
        {
            //printf("%d\n", precedent);
            file->premier = file->premier->suivant;
        }









    }
return n1;

}


void afficherFile(File *file)
{
    Element2 *elementActuel = file->premier;
    while(elementActuel != NULL)
    {
        printf("%d\n", elementActuel->sommet->cle);
        elementActuel = elementActuel->suivant;
    }
}



Noeud* creer_ensemble(int x)
{
    Noeud *noeud = malloc(sizeof(Noeud));

    if (noeud == NULL)
    {
        exit(EXIT_FAILURE);
    }
    noeud->valeur = x;
    noeud->cle = 0;
    noeud->parent = NULL;

    return noeud;

}
