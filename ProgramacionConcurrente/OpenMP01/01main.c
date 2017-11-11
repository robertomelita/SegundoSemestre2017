#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int main(int argc, char *argv[]){
    printf("Hello World\n");
    #pragma omp parallel
    {
        printf("Hello from a thread %i.    %i\n",omp_get_thread_num(),omp_get_num_threads());
    }
    printf("I am sequential now.\n");
}