#include "headers/utils.h"
#include "headers/vars.h"



void construct(){
    if(spanCount < span) {

        // increment span counter
        spanCount++;

        // get moves in descending order
        Selection selection = getSelection();
        Solution *moves = selection.moves;
        Solution *move;
        Solution *infeasible;
        if(feasible) {
            // if solution still feasible ( step C1)

            // find a feasible move
            for(int i = 0; i < selection.size; i++) {
                if(admissible(moves+i)) {
                    move = moves+i;
                    break;
                }
                else if(infeasible == NULL) infeasible = moves+i;
            }

            if(move != NULL) {
                // found feasible move, update current solution
                changeSolution(move);
            }
            else {
                // no feasible move, check if current solution is a new best then go to C2

                Solution *lastBest = TabulistHead(tabulist);
                if(evalObjective(lastBest) < evalObjective(&curSolution)) {
                    // new best solution
                    addSolution(curSolution);
                }
                feasible = false;
                tinker(&curSolution, infeasible);
                construct();
            }
        }
        else {
            // if solution is no more feasible ( step C2)

            if(selection.size == 0) {
                // no moves posssible
                transfer();
            }
            else {
                // do a move, and continue construction
                changeSolution(moves);
                construct();
            }

        }
        free(selection.moves);

    }
    else {
        transfer();
    }
}

void transfer() {
    spanCount = 0;
    constructive = constructive ? false : true;
}

void destroy(){
   if(spanCount < span) {

        // increment span counter
        spanCount++;

        // get moves in ascending order of value 
        Selection selection = getSelection();
        Solution *moves = selection.moves;
        Solution *move;
        Solution *infeasible;

        if(!feasible) {
            // if solution is not feasible ( step D1)

            // retain infeasible move
            infeasible = &curSolution;

            // do a move
            changeSolution(move = moves);

            // if move is feasible go to D2, else continue in D1
            if(admissible(move)) {
                feasible = true;
                Solution *lastBest = TabulistHead(tabulist);
                if(evalObjective(lastBest) < evalObjective(move)) {
                    // new best solution
                    addSolution(*move);
                }
                tinker(move, infeasible);
            }
            destroy(); // move to D2 or D1 depending on above outcome
            
        }
        else {
            // if solution is feasible ( step D2)

            if(selection.size == 0) {
                // no moves posssible
                transfer();
            }
            else {
                // do a move, and continue destruction
                changeSolution(moves);
                destroy();
            }

        }
        free(selection.moves);

    }
    else {
        transfer();
    }
}

Solution makeMove(Variable *variable) {
    return makeMoveFromSolution(variable, &curSolution);
}


Solution makeMoveFromSolution(Variable *variable, Solution *move ) {
    move = move ? move : &curSolution;
    Solution newMove;
    float size = sizeof(move->value);
    newMove.value = malloc(size);
    memcpy(newMove.value, move->value, size);
    newMove.value[variable->index] = newMove.value[variable->index] ? 1 : 0;
    return newMove;
}

void tinker(Solution* feasible, Solution* infeasible ) {
    if (constructive)
    {
        // in constrcutive phase
        int size = count(curSolution.value, N, 1);
        int *candidates = malloc(sizeof(int)*size);
        int j = 0;
        for (int i = 0; i < N; i++)
        {
            if (curSolution.value[i] == 1)
            {
                candidates[j] = i;
                j++;
            }
        }

        // sort in ascending order of objective function coeficients
        int a, b, temp; 
        for (a = 0; a < size-1; a++) {
            for (b = 0; b < size-a-1; b++) {
                if (objectiveFunction.value[b] > objectiveFunction.value[b+1]) {
                    temp = objectiveFunction.value[b];
                    objectiveFunction.value[b] = objectiveFunction.value[b+1];
                    objectiveFunction.value[b+1] = temp; 
                    }
                }
        }       
    
        for (int i = 0; i < size; i++)
        {
            Solution move = makeMoveFromSolution(variables+i, infeasible);
            if(admissible(&move) && evalObjective(&move) > evalObjective(TabulistHead(tabulist))) {
                addSolution(move);
            }
        }

    }

                else {
        // destrcutive phase
                }
    
}
        

float evalObjective(Solution *move)
{
    return scalaire(move, &objectiveFunction.value, N);
}


int admissible(Solution *move)
{
    int result = 0, admi = true;

    for (int i = 0; i < M; ++i)
    {
        scalaire(move, constrains.lhs+i, N);

        // Une contrainte a été violé admi reçoit faux
        if (result > constrains.rhs[i])
        {
            admi = false;
            break;
        }
    }
    return admi;
}


int count( int *array, int size, int val) {
    int s = 0;
    for (int k = 0; k < size; k++)
    {
       if (array[k] == val)
       {
          s++;
       }
       
    }
    return s;
}

void changeSolution( Solution *move) {
    free(curSolution.value);
    curSolution = *move;
    for (int i = 0; i < N; i++)
    {
        variables[i].value = curSolution.value[i];
    }
}

float scalaire( int *v1, float *v2, int size) {
    int j,result = 0;
    for (int j = 0; j < size; ++j)
    {
        result = result + v1[j] * v2[j];
    }
    return result;
}

