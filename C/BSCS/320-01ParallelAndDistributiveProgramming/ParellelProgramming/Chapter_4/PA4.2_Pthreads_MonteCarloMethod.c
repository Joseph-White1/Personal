// Joseph White
// 12/12/2023
// CSCI 320: Week 6 Programming Assignment 4.2

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    long long tosses_per_thread;
    long long number_in_circle;
} ThreadData;

void* throw_darts(void* arg)
{
    ThreadData* data = (ThreadData*) arg;
    double x, y, distance_squared;
    long long hits = 0;
    
    unsigned int seed = time(NULL) ^ pthread_self();

    for (long long toss = 0; toss < data->tosses_per_thread; toss++)
    {
        x = (double)rand() / RAND_MAX * 2 - 1;
        y = (double)rand() / RAND_MAX * 2 - 1;
        distance_squared = x * x + y * y;
        if (distance_squared <= 1) hits++;
    }

    data->number_in_circle = hits;
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    long long total_tosses;
    int thread_count;

    printf("Enter the total number of tosses: ");
    scanf("%lld", &total_tosses);

    printf("Enter the number of threads: ");
    scanf("%d", &thread_count);

    // Ensure the input values are valid
    if (total_tosses <= 0 || thread_count <= 0)
    {
        fprintf(stderr, "Error: Number of tosses and threads must be positive.\n");
        return EXIT_FAILURE;
    }

    pthread_t* threads = malloc(thread_count * sizeof(pthread_t));
    ThreadData* thread_data = malloc(thread_count * sizeof(ThreadData));

    long long tosses_per_thread = total_tosses / thread_count;
    long long total_hits = 0;

    // Create threads
    for (int i = 0; i < thread_count; i++)
    {
        thread_data[i].tosses_per_thread = tosses_per_thread;
        pthread_create(&threads[i], NULL, throw_darts, &thread_data[i]);
    }

    // Join threads and aggregate results
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
        total_hits += thread_data[i].number_in_circle;
    }

    // Estimate π
    double pi_estimate = 4 * (double)total_hits / total_tosses;

    printf("Estimated π = %.6f\n", pi_estimate);

    free(threads);
    free(thread_data);

    return 0;
}