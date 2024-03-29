#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

Noeud **makeSommets(Graph *graph) {
    int i, valeur, ns = graph->taille;
    Noeud **S = calloc(ns, sizeof(Noeud));
        //Crée tableau des sommets
    for( i = 0; i < ns;  i++ ) {
        valeur = graph->sommets[i]->tete->valeur;
        S[valeur] = creer_ensemble(valeur);
    }
    return S;
}


int countArcs( Graph *graph) {
    int i, sum = 0, n = graph->taille;

    for( i = 0; i < n;  i++ ) {
        sum+= graph->sommets[i]->taille;
    }
    return sum;
}

int countLines( FILE *file ) {
    int i = 0;
    char string[TAILLE_MAX];
    while (fgets(string, TAILLE_MAX, file) != NULL) {i++;}

    rewind(file);

    return i;
}


Liste *parseLine( char *line ) {

    char *token;
    char *rest; 
    
    token = strtok_r(line, ",", &rest);

    Liste *liste = malloc(sizeof(Liste));

    liste->tete = makeElement(token);

    Element *next = liste->tete;

    token = strtok_r(NULL, ",", &rest);

    int i = 1;
    while( token != NULL) {
        next->suivant = makeElement(token);
        next = next->suivant;
        token = strtok_r(NULL, ",", &rest);
        i++;
    }

    liste->taille = i-1;
    return liste;
}

Element *makeElement( char *item ) {
    char *token;
    char *rest;

    Element *element = malloc(sizeof(Element));
   
    // valeur
    token = strtok_r(item," ", &rest);
    element->valeur = atoi(token); // convertir en int 

    // poids
    token = strtok_r(NULL," ", &rest);
    if(token != NULL) element->poids = atoi(token); // convertir en int

    return element;
}

Graph *makeGraph(const char *filename) {

    char path[FILENAME_MAX] = "./graphs/";
    strcat(path, filename);
    FILE* fichier  = fopen(path, "r");
    Graph *graph = malloc(sizeof(Graph));
    char chaine[TAILLE_MAX];
    int i = 0;

    if (fichier != NULL)
    {
        graph->sommets = calloc( countLines(fichier), sizeof(Liste));
        while (fgets(chaine, TAILLE_MAX, fichier) != NULL) 
        {
            //printf("%s", chaine);
            graph->sommets[i] = parseLine(chaine);
            i++;
        }

        graph->taille = i;
    }

    fclose(fichier);

    return graph;
}

int convert( int v, int r) {
    int remainder = 0, i = 1;
    while(v > 0){
        remainder += (v%r) * i;
        v /= r;
        i*=10;
    }
    return (int)remainder; 
}
