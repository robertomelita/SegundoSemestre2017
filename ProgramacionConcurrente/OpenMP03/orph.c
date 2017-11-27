/**********************************************************************************
orf.c OPENMP
calculo de un producto escalar
reparto de tares tipo orphan
**********************************************************************************/
//// Ejecutar la versi�n serie (orf_ser) antes para ver lo que tiene que dar
#include <omp.h>
#include <stdio.h>
#define N 100
float A[N], B[N], pe;
void AporB()
{
    int j;
    #pragma omp for reduction(+:pe)
        for (j=0; j<N; j++) pe += A[j] * B[j];
}
int main ()
{
    int i;
    for (i=0; i<N; i++)
    {
        A[i] = i;
        B[i] = N-i;
    }
    pe = 0.0;
    #pragma omp parallel
    {
        AporB();
    }
    printf("\n\n >> PE = %10.0f\n\n", pe);
    return 0;
}