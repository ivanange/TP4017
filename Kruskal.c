#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


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


int main()
{
    const int na, ns;
    Arete a1, A[na]; // IL FAUT LE NOMBRE D'ARRET
    Noeud *S[ns]; // IL FAUT LE NOMBRE DE SOMMET
    //Arete *mini;
    for(int i = 0; i<ns; i++)
    {
        S[i] = Noeud *e1 = creer_ensemble(1)
    }
    //Noeud *e1 = creer_ensemble(1);
    for(int i = 0; i<na; i++)
    {
        a.destination = e3;
        a.source = e1;
        a.poids = 1;
        A[i] = a;
    }
    //a1.destination = e3;
    //a1.source = e1;
    //a1.poids = 1;


    int  j;
    Kruskal(A, na);
    //Tri(t, 6);
    for(j = 0; j <= 5; j++ )
    {
        printf("%d\n", A[j].poids);
    }

    return 0;
}







void Kruskal(Arete *tab, int taille)
{
    int i = 0, j = 0;
    Tri(tab, taille);

    for(i=0; i<taille; i++)
    {
        if(Trouver_ensemble(tab[i].destination)->valeur != Trouver_ensemble(tab[i].source)->valeur )
        {
            tab[j] = tab[i];
            j = j + 1;
            Unifier(tab[i].destination, tab[i].source);
        }
    }

    while(j<taille)
    {
        tab[j].poids = 0;
        j = j + 1;
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

