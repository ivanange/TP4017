#include "headers/data_structures.h"

/* Constrains */

Constrains *ConstrainsInit(int m, int n) {
	Constrains *contrains = malloc(sizeof(Constrains));
	contrains->rhs = malloc(sizeof(float)*m);
	contrains->lhs = malloc(sizeof(float)*m);
	for(int i = 0; i < m; i++) {
		contrains->lhs[i] = malloc(sizeof(float)*n);
	}
	return contrains;
}



/* Tabu List */
Tabulist *TabulistInit(int size) {
	Tabulist *q = malloc(sizeof(Tabulist));
	q->list = malloc(sizeof(int) * size);
	q->max_size = size;
	q->size = 0;
	return q;
}

void TabulistPush(Tabulist *q, Solution a) {
	q->list[q->size] = a;
	q->size = (q->size + 1) % q->max_size;
}

Solution *TabulistHead(Tabulist *q) {
	return q->list + (q->size-1);
}

void TabulistFree(Tabulist *q) {
	free(q->list);
	free(q);
}