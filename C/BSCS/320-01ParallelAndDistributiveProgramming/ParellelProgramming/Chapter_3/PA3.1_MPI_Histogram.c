// Joseph White
// 12/4/2023
// CSCI 320: Week 5 Programming Assignment 3.1


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
/*Function Prototypes..these don't need to be changed */

void Get_input(int* bin_count_p, float* min_meas_p, float* max_meas_p,
      int* data_count_p, int* local_data_count_p, int my_rank,
      int comm_sz, MPI_Comm comm);
void Check_for_error(int local_ok, char fname[], char message[],
      MPI_Comm  comm);
void Gen_data(float local_data[], int local_data_count, int data_count,
      float min_meas, float max_meas, int my_rank, MPI_Comm comm);
void Set_bins(float bin_maxes[], int loc_bin_cts[], float min_meas,
      float max_meas, int bin_count, int my_rank, MPI_Comm comm);
void Find_bins(int bin_counts[], float local_data[], int loc_bin_cts[],
      int local_data_count, float bin_maxes[],
      int bin_count, float min_meas, MPI_Comm comm);
int Which_bin(float data, float bin_maxes[], int bin_count,
      float min_meas);
void Print_histo(float bin_maxes[], int bin_counts[], int bin_count,
      float min_meas);

/*---------------------------------------------------------------------*/
int main(void)
{
   int bin_count;

   float min_meas, max_meas;
   float* bin_maxes;
   int* bin_counts;
   int* loc_bin_cts;

   int data_count;
   int local_data_count;

   float* data;
   float* local_data;

   int my_rank, comm_sz;
   MPI_Comm comm;

   // initializes the MPI environment
   MPI_Init(NULL, NULL);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   // Gathers input data from the user (if my_rank is 0)
   Get_input(&bin_count, &min_meas, &max_meas, &data_count, &local_data_count, my_rank, comm_sz, MPI_COMM_WORLD);


   // allocate arrays (this code is ok)
   bin_maxes = malloc(bin_count*sizeof(float));
   bin_counts = malloc(bin_count*sizeof(int));
   loc_bin_cts = malloc(bin_count*sizeof(int));
   data = malloc(data_count*sizeof(float));
   local_data = malloc(local_data_count*sizeof(float));

   //Call set_bins, gen_data,and find_bins for each process
   Set_bins(bin_maxes, loc_bin_cts, min_meas, max_meas, bin_count, my_rank, MPI_COMM_WORLD);
   Gen_data(local_data, local_data_count, data_count, min_meas, max_meas, my_rank, MPI_COMM_WORLD);
   Find_bins(bin_counts, local_data, loc_bin_cts, local_data_count, bin_maxes, bin_count, min_meas, MPI_COMM_WORLD);


   //Rest of code in main method is fine and doesn't need changes
   if (my_rank   == 0)
      Print_histo(bin_maxes, bin_counts, bin_count, min_meas);

   free(bin_maxes);
   free(bin_counts);
   free(loc_bin_cts);
   free(data);
   free(local_data);
   MPI_Finalize();
   return 0;

} /* main */


/*---------------------------------------------------------------------*/
void Print_histo(
      float bin_maxes[] /* in */,
      int bin_counts[]  /* in */,
      int bin_count     /* in */,
      float min_meas    /* in */)
{
   int i, j;
   float bin_max, bin_min;
   //print_histo method needs no changes

   for (i = 0; i < bin_count; i++)
   {
      bin_max = bin_maxes[i];
      bin_min = (i == 0) ? min_meas: bin_maxes[i-1];
      printf("%.3f-%.3f:\t", bin_min, bin_max);
      for (j = 0; j < bin_counts[i]; j++)
         printf("X");
      printf("\n");
   }
}  /* Print_histo */


/*---------------------------------------------------------------------*/
void Find_bins(
      int bin_counts[]      /* out */,
      float local_data[]    /* in  */,
      int loc_bin_cts[]     /* out */,
      int local_data_count  /* in  */,
      float bin_maxes[]     /* in  */,
      int bin_count         /* in  */,
      float min_meas        /* in  */,
      MPI_Comm comm)
{

   int i,bin;
   for (i = 0; i < local_data_count; i++)
   {
      bin = Which_bin(local_data[i], bin_maxes, bin_count, min_meas);
      loc_bin_cts[bin]++;
   }

   //Use MPI Reduce to take loc_bin_cts and sum into bin_counts
   MPI_Reduce(loc_bin_cts, bin_counts, bin_count, MPI_INT, MPI_SUM, 0, comm);
}  /* Find_bins */


/*---------------------------------------------------------------------*/
int Which_bin(float data, float bin_maxes[], int bin_count,
      float min_meas)
{
    //which_bin code is ok and needs no changes
   int bottom = 0, top =  bin_count-1;
   int mid;
   float bin_max, bin_min;

   while (bottom <= top)
   {
      mid = (bottom + top)/2;
      bin_max = bin_maxes[mid];
      bin_min = (mid == 0) ? min_meas: bin_maxes[mid-1];
      if (data >= bin_max)
         bottom = mid+1;
      else if (data < bin_min)
         top = mid-1;
      else
         return mid;
   }
   printf("Uh oh . . .\n");
   return 0;
}  /* Which_bin */


/*---------------------------------------------------------------------*/
void Set_bins(
      float bin_maxes[]  /* out */,
      int loc_bin_cts[]  /* out */,
      float min_meas     /* in  */,
      float max_meas     /* in  */,
      int bin_count      /* in  */,
      int my_rank        /* in  */,
      MPI_Comm comm      /* in  */)
{

   if (my_rank == 0)
   {
      int i;
      float bin_width;
      bin_width = (max_meas - min_meas) / bin_count;

      for (i = 0; i < bin_count; i++)
      {
         loc_bin_cts[i] = 0;
         bin_maxes[i] = min_meas + (i+1)*bin_width;
      }

   }
   // set bin_maxes for each proc using MPI_Bcast
   MPI_Bcast(bin_maxes, bin_count, MPI_FLOAT, 0, comm);

   // set loc_bin_cts of each proc using MPI_Bcast
   MPI_Bcast(loc_bin_cts, bin_count, MPI_INT, 0, comm);
}  /* Set_bins */


/*---------------------------------------------------------------------*/
void Gen_data(
      float local_data[]    /* out */,
      int local_data_count  /* in  */,
      int data_count        /* in  */,
      float min_meas        /* in  */,
      float max_meas        /* in  */,
      int my_rank           /* in  */,
      MPI_Comm comm         /* in  */)
{
   int i;
   float* data = NULL;

   if (my_rank ==0)
   {
      data = malloc(data_count*sizeof(float));
      srand(time(NULL));

      for (i = 0; i < data_count; i++)
         data[i] =
            min_meas + (max_meas - min_meas)*rand()/((double) RAND_MAX);

      //Call MPI_Scatter to send portions of the data array from process 0 to all the other processes.
      MPI_Scatter(data, local_data_count, MPI_FLOAT, local_data, local_data_count, MPI_FLOAT, 0, comm);
      free(data);
   }
   else
   {
      //Call MPI_Scatter to get portions of the data array from process 0.
      MPI_Scatter(data, local_data_count, MPI_FLOAT, local_data, local_data_count, MPI_FLOAT, 0, comm);
   }

}  /* Gen_data */

/*---------------------------------------------------------------------*/
void Get_input(int* bin_count_p, float* min_meas_p, float* max_meas_p,
      int* data_count_p, int* local_data_count_p, int my_rank,
      int comm_sz, MPI_Comm comm)
{

   int local_ok = 1;
   //Ask the user for the number of bins (bin_count_p), min measurement (min_meas_p), max measurement( max_meas_p),
   //and number of data (data_count_p) if my_rank is 0.
   if (my_rank == 0)
   {
    printf("Enter the number of bins, min measurement, max measurement, and total number of data points: ");
    scanf("%d %f %f %d", bin_count_p, min_meas_p, max_meas_p, data_count_p);
    }

   //Bcast variables above to all processes
   MPI_Bcast(bin_count_p, 1, MPI_INT, 0, comm);
   MPI_Bcast(min_meas_p, 1, MPI_FLOAT, 0, comm);
   MPI_Bcast(max_meas_p, 1, MPI_FLOAT, 0, comm);
   MPI_Bcast(data_count_p, 1, MPI_INT, 0, comm);

   if(*data_count_p % comm_sz != 0) local_ok = 0;

   Check_for_error(local_ok, "Get_input",
               "data_count must be evenly divisible by comm_sz",
               comm);
   *local_data_count_p = *data_count_p / comm_sz;

}  /* Get_input */


/*---------------------------------------------------------------------*/
void Check_for_error(
     int       local_ok   /* in */,
     char      fname[]    /* in */,
     char      message[]  /* in */,
     MPI_Comm  comm       /* in */)
{
   int ok;
   //check_for_error method needs no changes.
   MPI_Allreduce(&local_ok, &ok, 1, MPI_INT, MPI_MIN, comm);
   if (ok == 0)
   {
      int my_rank;
      MPI_Comm_rank(comm, &my_rank);
      if (my_rank == 0)
      {
         fprintf(stderr, "Proc %d > In %s, %s\n", my_rank, fname,
               message);
         fflush(stderr);
      }
      MPI_Finalize();
      exit(-1);
   }
}  /* Check_for_error */