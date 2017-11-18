#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#define N 64

int i, j, tid, nth, A[N], s = 0,suma = 0;

int main(int argc, char *argv[]){ 
    srand(1);
    for(i=0; i<N; i++){
            A[i]=rand()%10;
            suma+=A[i];
            printf("A[%i] = %i\n",i,A[i]);
        }
    #pragma omp parallel  
        #pragma omp for reduction(+:s)
        for(i=0;i<N;i++){
                s = A[i]+s;
                if(i%(N/omp_get_num_threads())==(N/omp_get_num_threads())-1) printf("Soy el thread %i y estoy sumé.. %i\n",omp_get_thread_num(),s);
            }
    
    printf("La suma es: %i con paralel y en realidad es %i\n",s,suma);
}