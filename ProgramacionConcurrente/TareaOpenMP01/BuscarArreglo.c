#include <stdio.h>
#include <omp.h>

#define N 16

int i;

int main (){
    int A[N];
    for(int i = 0; i<N;i++){
        A[i] = i;
    }
    #pragma omp parallel for private(i)
        for(int i = 0; i<N; i++){
            printf("%i encontrado en el Thread %i\n",omp_get_thread_num(),A[i]);
        }
 return 0;
}