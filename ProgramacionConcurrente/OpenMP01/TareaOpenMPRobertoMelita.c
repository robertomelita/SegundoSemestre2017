//Roberto Melita

#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define N 3*8

int i, j, tid, nth, A[N], s = 0;

int main(int argc, char *argv[]){ 
    srand(1);
    for(i=0; i<N; i++){
        A[i]=rand()%10;
        printf("A[%i]= %i\n",i,A[i]);
    }
    #pragma omp parallel private(j,tid,nth,s) shared(A)
    {
        nth = omp_get_num_threads();
        tid = omp_get_thread_num();
        for(int j=0; j<3; j++){
            s+=A[3*tid+j];
        }
//        printf("Thread %d de %d en marcha \n",tid,nth);
        printf("Thread %i sumó %i\n",tid,s);
//        printf("El thread %d ha terminado \n\n",tid);
    }
}
