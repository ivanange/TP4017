#include "headers/data_structures.h"

/* Constrains */

Constrains *ConstrainsInit(int m, int n) {
	Constrains *constrains = malloc(sizeof(Constrains));
	constrains->rhs = malloc(sizeof(double)*m);
	constrains->lhs = malloc(sizeof(double*)*m);
	for(int i = 0; i < m; i++) {
		constrains->lhs[i] = malloc(sizeof(double)*n);
	}
	return constrains;
}



/* Tabu List */
Tabulist *TabulistInit(int size) {
	Tabulist *q = malloc(sizeof(Tabulist));
	q->list = malloc(sizeof(Solution*) * size);
	q->max_size = size;
	q->size = -1;
	return q;
}

void TabulistPush(Tabulist *q, Solution *a) {
	q->size = (q->size + 1) % q->max_size;
	q->list[q->size] = a;
}

Solution *TabulistHead(Tabulist *q) {
	return q->list[q->size];
}

void TabulistFree(Tabulist *q) {
	
	for (int i = 0; i < q->max_size; i++)
	{
		free(q->list[i]);
	}
	free(q->list);
	free(q);
}