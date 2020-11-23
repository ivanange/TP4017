#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "headers/utils.h"
#include "headers/main.h"


int main(int argc, char **argv)
{
    char *path = "data/mknap1.txt";
    char *outpath = NULL;
    int opt;
    double optimumValue;

    while((opt = getopt(argc, argv, ":af:s:")) != -1)  
    {  
        switch(opt)  
        {  

            case 'f':  
                path = optarg;
                break;
            case 's':  
                outpath = optarg;
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
        fclose(file);

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
        Solution *optimum = TabulistHead(tabulist);
        optimumValue = scalaire(optimum->value, objectiveFunction.value, N);
        printf("optimal solution: (%d", optimum->value[0]);
        for (int i = 1; i < N; i++)
        {
            printf(" %d", optimum->value[i]);
        }
        printf(")\n");
        printf("optimal value: %lf\n", optimumValue);

        if(outpath != NULL) {
            file = fopen(outpath, "a+");
            if(file) {
                fprintf(file, "%d", optimum->value[0]);
                for (int i = 1; i < N; i++)
                {
                    fprintf(file, " %d", optimum->value[i]);
                }
                fprintf(file, "\n");
                fprintf(file, "%lf\n", optimumValue);
                fclose(file);

            }
            else
            {
                 printf("Could not open output file");
            }
            
        }
        
    }
    else {
        printf("Could not open file with MKP instance");
    }
    
}

