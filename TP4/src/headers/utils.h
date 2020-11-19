#ifndef utils
#define utils

#include "data_structures.h"
#include "vars.h"

/*
* Initialise algorithm
*/
void init();

/*
* Evaluates the S(j)s
*/
void eval();

/*
* Tinker around to find other trial solutions at critical events
*/
void tinker();

/*
* Construct new solution from current solution by inveting given variable
* @param Variable* variable 
*/
Solution makeMove(Variable *variable);

/*
* Get a value for span
*/
int getSpan();

/*
* Check if specified solution is feasible
* @param Solution* move 
*/
int admissible(Solution *move);

/*
* Evaluate specified solution
* @param Solution* move 
*/
float evalObjective(Solution *move);

/*
* Add solution to Tabu list and update variables accordingly
* @param Solution solution 
*/
void addSolution(Solution solution);

/*
* Returns possible moves in order of their potential value in ASC or DESC order 
* depending on current phase ( contructive or destruvtive)
* @return Selection 
*/
Selection select();

/*
* Procedure representing construcive phase
*/
void construct();

/*
* Procedure representing destrucive phase
*/
void destroy();

/*
* Procedure representing transfer phase
*/
void transfer();

/*
* Performs dot product of 2 vectors, one made of INTs the other of FLOATs
* @param int* v1
* @param int* v2
* @param int size
* @return float
*/
float scalaire( int *v1, float *v2, int size);

#endif