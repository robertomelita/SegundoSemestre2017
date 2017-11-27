#include <stdio.h>
#include <omp.h>

#define N 12

int i;

int main (){
    int mult = 1;
    #pragma omp parallel for private(i) reduction(*:mult)
        for(int i = 1; i<=N; i++){
            mult*=i;
            printf("Parcial: %i \t %i \n",mult,omp_get_thread_num());
        }
    printf("Total: %i \n",mult);
 return 0;
}