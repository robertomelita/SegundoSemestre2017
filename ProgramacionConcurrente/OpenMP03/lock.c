#include <omp.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char const *argv[])
{
	srand(time(NULL));
	omp_lock_t l;
	omp_lock_t l2;
	omp_init_lock(&l);
	omp_init_lock(&l2);
	int comer;
	int x=rand()%100;
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				while(1){
					omp_set_lock(&l2);
					comer=x;
					x=0;
					usleep(10000);
					printf("estoy comiendo: %i\n",comer);
					omp_unset_lock(&l);
				}
			}
			#pragma omp section
			{
				while(1){
					omp_set_lock(&l);
						x=rand()%100+1;	
						usleep(10000);
						printf("estoy produciendo:  %i\n",x);
					omp_unset_lock(&l2);
				}
			}
		}
	}
	return 0;
}