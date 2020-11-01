#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include "utils.h"

int main(int argc, char **argv)
{
    char *file = "graph1.txt";
    int opt;

        while((opt = getopt(argc, argv, ":sf:")) != -1)  
    {  
        switch(opt)  
        {  

            case 'f':  
                file = optarg;
                break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    } 

    Noeud *u;
    Graph *graph = makeGraph(file);
    int i, j, k = 0, ns = graph->taille, na = countArcs(graph), *poids = calloc(ns,sizeof(int));
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
            aret->destination = u;
            aret->source = u->parent;
            aret->poids = poids[u->valeur];
            arbre[k] = *aret;
            k++;
        }

        Element *v = adj[u->valeur];
        while ( v != NULL)
        {
            if ( G[v->valeur]->rang  > G[u->valeur]->rang  + v->poids )
            {
                G[v->valeur]->parent = u;
                G[v->valeur]->rang = G[u->valeur]->rang  + v->poids;
                poids[v->valeur] = v->poids;
            }
            
            v = v->suivant;
        }

        
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
    noeud->rang = INFINITE;
    noeud->parent = NULL;

    return noeud;
}
