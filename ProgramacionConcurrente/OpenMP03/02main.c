#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

int main(int argc, char *argv[]){
    printf("Hello World\n");
    srand(1);
    int x=0;
    omp_lock_t c;
    omp_init_lock(&c);
    #pragma omp parallel shared(x)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for(int i=0;i<100;i++){
                    omp_set_lock(&c);
                    printf("Consumiendo: %i\n",x);
                    x=0;
                }
            }
            #pragma omp section
            {
                for(int i=0;i<100;i++){
                    x=rand()%100;
                    printf("Produciendo: %i\n", x);
                    omp_unset_lock(&c);
                }
            }
        }
    }
    omp_destroy_lock(&c);
}
        