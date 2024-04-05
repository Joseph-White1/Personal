// Joseph White
// 12/9/2023
// CSCI 320: Week 6 Programming Assignment 4.1


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct
{
    int thread_id;
    long long my_n;
} thread_arg;

int thread_count;
int bin_count;
int data_count;
float min_meas, max_meas;
float* data;
float* bin_maxes;
int* bin_counts;
int* local_bin_counts;
void Print_histo(int bin_counts[], int bin_count, float bin_maxes[]);
void* Thread_work(void* rank);
int Find_bin(float data);


int main(int argc, char* argv[])
{
    long thread;
    pthread_t* thread_handles;

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < data_count; i++)
    {
        // Generate random floats in the range [min_meas, max_meas)
        data[i] = min_meas + (max_meas - min_meas) * rand() / (RAND_MAX + 1.0);
    }

    printf("Enter the number of data points: ");
    scanf("%d", &data_count);
    printf("Enter the number of bins: ");
    scanf("%d", &bin_count);
    printf("Enter the min and max values (e.g., 0.0 5.0): ");
    scanf("%f %f", &min_meas, &max_meas);
    printf("Enter the number of threads: ");
    scanf("%d", &thread_count);

    if (thread_count <= 0 || bin_count <= 0 || data_count <= 0 || min_meas >= max_meas)
    {
        fprintf(stderr, "Invalid input values.\n");
        return 1;
    }

    data = malloc(data_count * sizeof(float));
    bin_maxes = malloc(bin_count * sizeof(float));
    bin_counts = calloc(bin_count, sizeof(int));
    local_bin_counts = calloc(thread_count * bin_count, sizeof(int));
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    if (data == NULL || bin_maxes == NULL || bin_counts == NULL || local_bin_counts == NULL || thread_handles == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return 2;
    }

    // Assuming the data array is populated with values
    // Populate the data array with random values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < data_count; i++)
    {
        data[i] = min_meas + (max_meas - min_meas) * rand() / (RAND_MAX + 1.0);
    }

    float bin_width = (max_meas - min_meas) / bin_count;
    for (int b = 0; b < bin_count; b++)
    {
        bin_maxes[b] = min_meas + bin_width * (b + 1);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        thread_arg* arg = malloc(sizeof(thread_arg));
        if (arg == NULL)
        {
            fprintf(stderr, "Memory allocation for thread_arg failed.\n");
            return 3;
        }
        arg->thread_id = thread;
        arg->my_n = data_count / thread_count;
        if (pthread_create(&thread_handles[thread], NULL, Thread_work, (void*)arg))
        {
            fprintf(stderr, "Error creating thread %ld\n", thread);
            return 4;
        }
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        if (pthread_join(thread_handles[thread], NULL))
        {
            fprintf(stderr, "Error joining thread %ld\n", thread);
            return 5;
        }
    }

    for (int i = 0; i < thread_count; i++)
    {
        for (int j = 0; j < bin_count; j++)
        {
            bin_counts[j] += local_bin_counts[i * bin_count + j];
        }
    }

    // Print the histogram
    Print_histo(bin_counts, bin_count, bin_maxes);

    free(data);
    free(bin_maxes);
    free(bin_counts);
    free(local_bin_counts);
    free(thread_handles);

    return 0;
}

void* Thread_work(void* rank)
{
    thread_arg* my_rank = (thread_arg*)rank;
    int my_thread = my_rank->thread_id;
    int my_first_i = my_thread * my_rank->my_n;
    int my_last_i = my_first_i + my_rank->my_n;

    for (int i = my_first_i; i < my_last_i; i++)
    {
        int bin = Find_bin(data[i]);
        local_bin_counts[my_thread * bin_count + bin]++;
    }

    free(rank);
    return NULL;
}

void Print_histo(int bin_counts[], int bin_count, float bin_maxes[])
{
    printf("Histogram:\n");
    for (int b = 0; b < bin_count; b++)
    {
        printf("Bin %d (%.2f - %.2f): ", b, b == 0 ? min_meas : bin_maxes[b-1], bin_maxes[b]);
        for (int j = 0; j < bin_counts[b]; j++)
        {
            printf("X");
        }
        printf("\n");
    }
}

int Find_bin(float data)
{
    int bottom = 0, top = bin_count - 1;
    int mid;
    while (bottom <= top)
    {
        mid = (bottom + top) / 2;
        if (data >= bin_maxes[mid]) bottom = mid + 1;
        else top = mid - 1;
    }
    return top;
}