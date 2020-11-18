#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"
#include "headers/vars.h"

int main(int argc, char **argv)
{
    init();

    while(curIter < maxIter) {
        span = getSpan();
        
        if(constructive) {
            construct();
        }
        else{
            destroy();
        }

        curIter++;
    }
    
}

