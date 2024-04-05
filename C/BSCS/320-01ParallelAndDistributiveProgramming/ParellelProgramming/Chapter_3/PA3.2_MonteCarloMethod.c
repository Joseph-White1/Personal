// Joseph White
// 12/6/2023
// CSCI 320: Week 5 Programming Assignment 3.2

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

/* Function Prototypes are correct */

void Get_input(long long int* number_of_tosses, int my_rank,
      MPI_Comm comm);
long long int Monte_carlo(long long number_of_tosses,
      int my_rank);

/*-------------------------------------------------------------------*/
int main(void) {
   long long int number_of_tosses;
   long long int local_number_of_tosses;
   long long int number_in_circle;
   long long int local_number_in_circle;

   double pi_estimate;
   int my_rank, comm_sz;
   MPI_Comm comm = MPI_COMM_WORLD;

   srand(time(NULL)); // Seed the random number generator

   // Initialize the MPI environment and get process rank and communicator size
   MPI_Init(NULL, NULL);
   MPI_Comm_rank(comm, &my_rank);
   MPI_Comm_size(comm, &comm_sz);

   // Call Get_input method, number_of_tosses will be returned as a pointer.
   Get_input(&number_of_tosses, my_rank, comm);

   // Figure out the local_number_of_tosses by dividing number_of_tosses by the number of processes
   local_number_of_tosses = number_of_tosses / comm_sz;

   // Call the Monte_carlo method, using local_number_of_tosses and my_rank;
   local_number_in_circle = Monte_carlo(local_number_of_tosses, my_rank);

   // Call MPI_Reduce to get number_in_circle from the sum of the local_number_in_circle
   MPI_Reduce(&local_number_in_circle, &number_in_circle, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, comm);

   // Print out pi only if I am process 0.
   if (my_rank == 0) {
      pi_estimate = 4 * number_in_circle / ((double) number_of_tosses);
      printf("pi estimate = %f\n", pi_estimate);
   }

   MPI_Finalize();
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void Get_input(
      long long int* number_of_tosses  /* out */,
      int my_rank                      /* in  */,
      MPI_Comm comm                    /* in  */) {

   // If I am process 0, ask the user for the number of tosses and put it in number_of_tosses variable.
   if (my_rank == 0) {
      printf("Enter the total number of tosses: ");
      scanf("%lld", number_of_tosses);
   }

   // Broadcast number_of_tosses to all processes
   MPI_Bcast(number_of_tosses, 1, MPI_LONG_LONG_INT, 0, comm);

}  /* Get_input */


/*-------------------------------------------------------------------*/
// Below code is fine and doesn't need to be changed.
long long int Monte_carlo(long long local_number_of_tosses, int my_rank) {
   long long int i;
   double x, y;
   double distance_squared;
   long long int number_in_circle = 0;

   for (i = 0; i < local_number_of_tosses; i++) {
      x = 2 * rand() / ((double)RAND_MAX) - 1.0;
      y = 2 * rand() / ((double)RAND_MAX) - 1.0;

      distance_squared = x * x + y * y;
#     ifdef DEBUG
      printf("Proc %d > x = %f, y = %f, dist squared = %f\n",
            my_rank, x, y, distance_squared);
#     endif
      if (distance_squared <= 1) {
         number_in_circle++;
      }
   }

   return number_in_circle;
}  /* Monte_carlo */