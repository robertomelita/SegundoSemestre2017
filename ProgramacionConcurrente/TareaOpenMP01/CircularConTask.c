#include <stdio.h>
#include <omp.h>

#define N 10

int tid, x = 0, y = 0;

int main (){
    int A[N];
    srand(1);
    omp_lock_t sem[N];
    for(int i = 0; i<N;i++){
        omp_init_lock(&sem[i]);
        omp_set_lock(&sem[i]);
    }
    #pragma omp parallel private(tid) shared(A)
    {
        #pragma omp single
        {
            //Consumidor
            #pragma omp task
            {
                while(1){
                    omp_set_lock(&sem[x]);
                    printf("Consumiendo. %i en el puesto %i \n",A[x],x);
                    A[x] = 0;
                    usleep(15000);
                    x = (x + 1) % N;
                }
            }
            //Productor
            #pragma omp task
            {
                while(1){
                    A[y] = (rand()%9)+1;
                    printf("Produciendo %i en el puesto %i \n",A[y],y);
                    usleep(15000);
                    omp_unset_lock(&sem[y]);
                    y = (y + 1) % N;
                }
            }
        }
            
        
    }
 return 0;
}