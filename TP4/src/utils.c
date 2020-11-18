#include "headers/utils.h"
#include "headers/vars.h"


void construct(){
    if(spanCount < span) {

        // increment span counter
        spanCount++;

        // get moves in descending order
        Selection selection = select();
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
                curSolution = *move;
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
                curSolution = moves[0];
                construct();
            }

        }

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
        Selection selection = select();
        Solution *moves = selection.moves;
        Solution *move;
        Solution *infeasible;

        if(!feasible) {
            // if solution is not feasible ( step D1)

            // retain infeasible move
            infeasible = &curSolution;

            // do a move
            curSolution = *(move = moves);

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
                curSolution = moves[0];
                destroy();
            }

        }

    }
    else {
        transfer();
    }
}
