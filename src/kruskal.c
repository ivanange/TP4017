#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main()
{
    Graph *graph = makeGraph("graph1.txt");
    const int na = countArcs(graph), ns = graph->taille;
    Arete *a, A[na]; // IL FAUT LE NOMBRE D'ARRET
    Noeud *S[ns]; // IL FAUT LE NOMBRE DE SOMMET
    int valeur, i, j=0;
    // printf("sommets: %d arrets: %d\n", ns, na);

    //Crée tableau des sommets
    for( i = 0; i < ns;  i++ ) {
        valeur = graph->sommets[i]->tete->valeur;
        S[valeur] = creer_ensemble(valeur);
    }

    // crée tableau d'arrets
    for( i = 0; i < ns;  i++ ) {

        Element *next = graph->sommets[i]->tete->suivant;

        while (next != NULL)
        {
            a = malloc(sizeof(Arete));
            a->destination = S[next->valeur];
            a->source = S[graph->sommets[i]->tete->valeur];
            a->poids = next->poids;
            // printf("souce: %d, destination: %d, poids: %d", a.source->valeur, );
            A[j] = *a;
            next = next->suivant;
            j++;
        }
    }

    Kruskal(A, na);

    return 0;
}







void Kruskal(Arete *tab, int taille)
{
    int i = 0, j = 0;
    Arete *S = calloc(taille, sizeof(Arete));

    Tri(tab, taille);

    for(i=0; i<taille; i++)
    {
        if(Trouver_ensemble(tab[i].destination)->valeur != Trouver_ensemble(tab[i].source)->valeur )
        {
            Arete a;
            a.destination = tab[i].source;
            a.source = tab[i].destination;
            a.poids = tab[i].poids;

            S[j] = tab[i];
            S[j+1] = a;
            j = j + 2;
            Unifier(tab[i].destination, tab[i].source);
        }
    }

    // printf("\n%d, taille: %d \n", j, taille);

    for(int k = 0; k < j; k++ )
    {
        printf("%d-%d->%d\n", S[k].source->valeur, S[k].poids, S[k].destination->valeur);
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
    noeud->rang = 0;
    noeud->parent = noeud;

    return noeud;
}


Noeud* Trouver_ensemble(Noeud* n)
{
    while(n->valeur != n->parent->valeur)
    {
        n = n->parent;
    }
    //if(n->valeur == n->parent->valeur)
    //{
       // n->parent = Trouver_ensemble(n->parent);
    //}
    return n->parent;
}


void Lier(Noeud* x,Noeud* y)
{
    if(x->rang > y->rang)
    { 
        y->parent = x;
    }
    else x->parent = y;
    if(x->rang == y->rang)
    {
        y->rang = y->rang + 1;
    }
}

void Unifier(Noeud* x,Noeud* y)
{
    Lier(Trouver_ensemble(x), Trouver_ensemble(y));
}

void Tri(Arete *tableau, int taille)
{
    Arete cle;
    int k, i;

    for (i = 1 ; i < taille  ; i++)
    {
        cle = tableau[i];
        k = i - 1;

        while(k>=0 && tableau[k].poids > cle.poids)
        {
            tableau[k+1] = tableau[k];
            k = k - 1;
        }
        tableau[k+1] = cle;
    }

}

