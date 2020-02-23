#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define MASTER 0
#define RECV 1
#define SUM 2

/* Functions */
void fillArray(int VECTOR[], int MAX);
void printArray(int VECTOR[], int MAX);

int main(int argc, char *argv[])
{
	int rank, size;
	int MAX = atoi(argv[1]); //convert string to integer
	int VECTOR_A[MAX], VECTOR_B[MAX];

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == MASTER)
	{
		fillArray(VECTOR_A, MAX);
		fillArray(VECTOR_B, MAX);

		/* Sent messages */
		MPI_Send(VECTOR_A, MAX, MPI_INT, RECV, 2, MPI_COMM_WORLD);
		MPI_Send(VECTOR_B, MAX, MPI_INT, RECV, 3, MPI_COMM_WORLD);
	}
	else
	{
		if (rank == RECV)
		{
			/* For the node that will recieve the arrays */
			MPI_Recv(VECTOR_A, MAX, MPI_INT, MASTER, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(VECTOR_B, MAX, MPI_INT, MASTER, 3, MPI_COMM_WORLD, &status);

			printf("VECTOR A\n");
			printArray(VECTOR_A, MAX);
			printf("VECTOR B\n");
			printArray(VECTOR_B, MAX);

			MPI_Send(VECTOR_A, MAX, MPI_INT, SUM, 2, MPI_COMM_WORLD);
			MPI_Send(VECTOR_B, MAX, MPI_INT, SUM, 3, MPI_COMM_WORLD);
		}
		else
		{
			if (rank == SUM)
			{
				/* For the node that will add the arrays */
				MPI_Recv(VECTOR_A, MAX, MPI_INT, RECV, 2, MPI_COMM_WORLD, &status);
				MPI_Recv(VECTOR_B, MAX, MPI_INT, RECV, 3, MPI_COMM_WORLD, &status);

				int VECTOR_RES[MAX];

				for(int i = 0; i < MAX; i++)
				{
					VECTOR_RES[i] = (VECTOR_A[i] + VECTOR_B[i]);
				}
				printf("VECTOR RESULTANTE\n");
				printArray(VECTOR_RES, MAX);
			}
		}
	}

	MPI_Finalize();
	return EXIT_SUCCESS;
}

void fillArray(int VECTOR[], int MAX)
{
	// For generate a series of pseudorandom integers
	srand(time(NULL));

	for(int i = 0; i < MAX; i++)
	{
		VECTOR[i] = (rand()%120) + 1;
	}
}

void printArray(int VECTOR[], int MAX)
{
	for(int i = 0; i < MAX; i++)
	{
		printf("%d\n", VECTOR[i]);
	}
}
