
    #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>

    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);

        // Get the number of processes and check only 4 are used.
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);


        // Determine root's rank
        int root_rank = 0;

        // Get my rank
        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        // Each MPI process sends its rank to reduction, root MPI process collects the result
        int reduction_result = 0;
        MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("La suma de todos los ranks %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }

