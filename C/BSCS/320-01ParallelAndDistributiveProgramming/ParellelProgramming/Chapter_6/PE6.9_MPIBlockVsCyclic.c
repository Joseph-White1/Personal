// Joseph White
// 12/16/2023
// CSCI 320: Week 8 Programming Exercise 6.9

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Function to build cyclic MPI datatype
MPI_Datatype Build_cyclic_type(int n, int local_n) //local_n is the size of the array for each process (passed in by the user).  n is the total array size (comm_sz * local_n)
{
   int comm_sz;
   MPI_Datatype temp_mpi_t, temp1_mpi_t;
   MPI_Aint lb, extent;
   MPI_Type_vector(local_n, 1, comm_sz, MPI_DOUBLE, &temp_mpi_t);
   MPI_Type_get_extent(MPI_DOUBLE, &lb, &extent);
   MPI_Type_create_resized(temp_mpi_t, lb, extent, &temp1_mpi_t);
   MPI_Type_commit(&temp1_mpi_t);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   return temp1_mpi_t;
}

int main(int argc, char* argv[])
{
    int comm_sz, my_rank, err;
    MPI_Init(&argc, &argv);

    err = MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    if (err != MPI_SUCCESS)
    {
        fprintf(stderr, "Error in MPI_Comm_size\n");
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    err = MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (err != MPI_SUCCESS)
    {
        fprintf(stderr, "Error in MPI_Comm_rank\n");
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    int n, m;
    if (my_rank == 0)
    {
        printf("Enter the total array size (n): ");
        if (scanf("%d", &n) != 1)
        {
            fprintf(stderr, "Error reading input\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        else if (n <= 0)
        {
            fprintf(stderr, "Error: Please enter a positive integer greater than 0.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        printf("Enter the dimension (m): ");
        if (scanf("%d", &m) != 1)
        {
            fprintf(stderr, "Error reading input\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        else if (m <= 0)
        {
            fprintf(stderr, "Error: Please enter a positive integer greater than 0.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        if (n < m)
        {
            fprintf(stderr, "Array size (n) must be greater than or equal to dimension (m)\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        err = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Check for errors in MPI_Bcast
        if (err != MPI_SUCCESS)
        {
            fprintf(stderr, "Error broadcasting n\n");
            MPI_Abort(MPI_COMM_WORLD, err);
        }
        err = MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Check for errors in MPI_Bcast
        if (err != MPI_SUCCESS)
        {
            fprintf(stderr, "Error broadcasting m\n");
            MPI_Abort(MPI_COMM_WORLD, err);
        }
    }
    else
    {
        err = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Check for errors in MPI_Bcast
        if (err != MPI_SUCCESS)
        {
            fprintf(stderr, "Error receiving n\n");
            MPI_Abort(MPI_COMM_WORLD, err);
        }
        err = MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
        // Check for errors in MPI_Bcast
        if (err != MPI_SUCCESS)
        {
            fprintf(stderr, "Error receiving m\n");
            MPI_Abort(MPI_COMM_WORLD, err);
        }
    }

    int local_n = n / comm_sz; // Assuming n is divisible by comm_sz
    double *local_array = malloc(local_n * m * sizeof(double));
    // Initialize local array

    // Perform MPI Allgather with Block Distribution
    double *global_block_array = NULL;
    if (my_rank == 0)
    {
        global_block_array = malloc(n * m * sizeof(double));
        if (global_block_array == NULL)
        {
            fprintf(stderr, "Unable to allocate memory for global_block_array\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    double start_time = MPI_Wtime();
    err = MPI_Allgather(local_array, local_n * m, MPI_DOUBLE, global_block_array, local_n * m, MPI_DOUBLE, MPI_COMM_WORLD);
    if (err != MPI_SUCCESS)
    {
        fprintf(stderr, "MPI_Allgather failed in block distribution\n");
        MPI_Abort(MPI_COMM_WORLD, err);
    }
    double end_time = MPI_Wtime();
    if (my_rank == 0)
    {
        printf("Block Distribution Time: %f seconds\n", end_time - start_time);
        free(global_block_array);
    }

    // Perform MPI Allgather with Cyclic Distribution
    MPI_Datatype cyclic_mpi_t = Build_cyclic_type(n, local_n);
    double *global_cyclic_array = NULL;
    if (my_rank == 0)
    {
        global_cyclic_array = malloc(n * m * sizeof(double));
        if (global_cyclic_array == NULL)
        {
            fprintf(stderr, "Unable to allocate memory for global_cyclic_array\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // Check if local_array is allocated
    if (local_array == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for local_array\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    start_time = MPI_Wtime();
    err = MPI_Allgather(local_array, m, MPI_DOUBLE, global_cyclic_array, 1, cyclic_mpi_t, MPI_COMM_WORLD);
    // Error check for MPI_Allgather
    if (err != MPI_SUCCESS)
    {
        fprintf(stderr, "MPI_Allgather failed in cyclic distribution\n");
        char error_string[BUFSIZ];
        int length_of_error_string;
        MPI_Error_string(err, error_string, &length_of_error_string);
        fprintf(stderr, "%s\n", error_string);
        MPI_Abort(MPI_COMM_WORLD, err);
    }
    end_time = MPI_Wtime();

    if (my_rank == 0)
    {
        printf("Cyclic Distribution Time: %f seconds\n", end_time - start_time);
        free(global_cyclic_array);
    }

    free(local_array);
    MPI_Finalize();
    return 0;
}