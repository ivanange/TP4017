#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "headers/utils.h"
#include "headers/main.h"


int main(int argc, char **argv)
{
    char *path = "graph1.txt";
    int opt;

        while((opt = getopt(argc, argv, ":sf:")) != -1)  
    {  
        switch(opt)  
        {  

            case 'f':  
                path = optarg;
                break;  
            case ':':  
                printf("option needs a value\n");  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }  
    }

    FILE *file = fopen(path, "r");

    if(file) {
        init(file);

        while(curIter < maxIter) {

            if(curIter%(2*TabuTenure) == 0) {
                K = K == KMAX ? 1 : K+1;
            }

            span = getSpan();
            
            if(constructive) {
                construct();
            }
            else{
                destroy();
            }

            curIter++;
        }

        // print optimal solution
    }
    else {
        // error
    }
    
}

