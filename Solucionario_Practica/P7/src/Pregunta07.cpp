
#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;
 
int main(int argc, char *argv[]) {

	int n;
	int rank;
	int size;
	int input_fac = 1;
	int res_fac = 1;
	int each_n;
	int p;

	bool resultImprimir = true;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		printf("Digite un número -> ");
		cin>>n;
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(n == 0 || n == 1)
	{
		res_fac = 1;
	}
	else
	{
		if(n%size == 0){
			each_n = n / size;
			for(int i=0; i < each_n; i++){
			   p= 1 + rank + i * size;
			   input_fac = input_fac * (p);
			}

			MPI_Reduce(&input_fac, &res_fac, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
		}
		else
		{
			resultImprimir = false;
		}
	}

	if(rank == 0)
	{
		if(!resultImprimir)
		{
			printf("El número ingresado \"%d\" no es divisible por la cantidad de procesos  \"%d\"",n,size);
		}
		else
		{
			printf("El factorial del número %d es %d", n, res_fac);
		}
	}

	MPI_Finalize();
	return 0;
}

