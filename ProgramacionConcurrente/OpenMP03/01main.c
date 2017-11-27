#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int main(int argc, char *argv[]){
    printf("Hello World\n");
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("HLE1\n");
            }
            #pragma omp section
            {
                printf("HLE2\n");
            }
            #pragma omp section
            {
                printf("HLE3\n");
            }
            #pragma omp section
            {
                printf("HLE4\n");
            }
            #pragma omp section
            {
                printf("HLE5\n");
            }
            #pragma omp section
            {
                printf("HLE6\n");
            }
            #pragma omp section
            {
                printf("HLE7\n");
            }
            #pragma omp section
            {
                printf("HLE8\n");
            }
        }
    }
}