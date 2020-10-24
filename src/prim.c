#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main()
{

    Noeud *u, *p;
    Graph *graph = makeGraph("graph1.txt");
    int i, j, k = 0, ns = graph->taille, na = countArcs(graph);
    Noeud **G = makeSommets(graph);
    Arete *arbre = calloc(na, sizeof(Arete)), *aret;
    Element **adj = calloc(ns, sizeof(Element)); 

    for( i = 0; i < ns;  i++ ) {
        adj[graph->sommets[i]->tete->valeur] = graph->sommets[i]->tete->suivant;
    }


    File *fil = malloc(sizeof(File));
    Cellule *c1 = malloc(sizeof(Cellule));
    c1->sommet = G[1];
    c1->suivant = NULL;
    fil->premier = c1;

    for ( i = 2; i <= ns; i++)
    {
        enfiler(fil, G[i]);
    }

    fil->premier->sommet->rang = 0;

    while ((u = extraireMin(fil)) != NULL) {

        // crée abreacouvrant minimum
        if( u->parent != NULL ) {
            aret = malloc(sizeof(Arete));
            aret->destination = u->parent;
            aret->source = u;
            aret->poids = u->rang;
            arbre[k] = *aret;
            k++;
            aret = malloc(sizeof(Arete));
            aret->destination = u;
            aret->source = u->parent;
            aret->poids = u->rang;
            arbre[k] = *aret;
            k++;
        }

        Element *v = adj[u->valeur];
        while ( v != NULL)
        {
            if ( rechercheFile(fil, v->valeur) > 0 && v->poids < G[v->valeur]->rang )
            {
                G[v->valeur]->parent = u;
                G[v->valeur]->rang = v->poids;
            }
            
            v = v->suivant;
        }

        p = u;
        
    }

    for(j = 0; j < k; j++ )
    {
        printf("%d-%d->%d\n", arbre[j].source->valeur, arbre[j].poids, arbre[j].destination->valeur);
    }

    return 0;
}



void enfiler(File *file, Noeud *nvNoeud)
{
    Cellule *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
    exit(EXIT_FAILURE);
    }

    nouveau->sommet = nvNoeud;
    nouveau->suivant = NULL;
    if (file->premier != NULL) /* La file n'est pas vide */
    {
        Cellule *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else 
    {
        file->premier = nouveau;
    }
}


Noeud* extraireMin(File *file)
{
    int min;
    Noeud *n1 = NULL;
    if (file->premier == NULL)
    {
        return NULL;
    }

    if (file->premier != NULL)
    {
        
        Cellule *precedent = NULL, *elementActuel = file->premier;
        
        min = file->premier->sommet->rang;
        n1 = elementActuel->sommet;

        while (elementActuel->suivant != NULL)
        {
            if(elementActuel->suivant->sommet->rang < min)
            {
                precedent = elementActuel;
                elementActuel = elementActuel->suivant;
                n1 = elementActuel->sommet;
                min = elementActuel->sommet->rang;
            }
            else elementActuel = elementActuel->suivant;
            
        }


        if(precedent == NULL)
        {
            file->premier = file->premier->suivant;
        }
        else {
            precedent->suivant = precedent->suivant->suivant;
        }

    }

return n1;

}


void afficherFile(File *file)
{
    Cellule *elementActuel = file->premier;
    while(elementActuel != NULL)
    {
        elementActuel = elementActuel->suivant;
    }
}

int rechercheFile(File *file, int n)
{
    Cellule *elementActuel = file->premier;
    while(elementActuel != NULL)
    {
        if (elementActuel->sommet->valeur == n )
        {
           return 1;
        }
        
        elementActuel = elementActuel->suivant;
    }

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
    noeud->rang = INFINITY;
    noeud->parent = NULL;

    return noeud;
}
