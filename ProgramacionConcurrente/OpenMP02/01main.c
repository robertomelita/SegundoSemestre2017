#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int main(int argc, char *argv[]){
    printf("Hello World\n");
    int ntt;
    int ntr;
    int ntproc;
    int a;
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        ntt = omp_get_num_threads();
        ntproc = omp_get_num_procs();
       // a = omp_get_procs_num();
       #pragma omp barrier
        printf("numero total de thread %i, numero total de procesadores %i\n",ntt,ntproc);

    }
    printf("I am sequential now.\n");
}