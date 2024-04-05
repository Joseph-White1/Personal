// Joseph White
// 12/15/2023
// CSCI 320: Week 7 Programming Assignment 5.2

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function to generate a random double between -1.0 and 1.0
double random_double()
{
    return 2.0 * (rand() / (double)RAND_MAX) - 1.0;
}

int main()
{
    long long int number_of_tosses, number_in_circle = 0;
    int thread_count;

    printf("Enter the number of tosses: ");
    if (scanf("%lld", &number_of_tosses) != 1 || number_of_tosses <= 0)
    {
        fprintf(stderr, "Invalid input for the number of tosses. Please enter a positive integer.\n");
        return 1;
    }

    printf("Enter the number of threads: ");
    if (scanf("%d", &thread_count) != 1 || thread_count <= 0)
    {
        fprintf(stderr, "Invalid input for the number of threads. Please enter a positive integer.\n");
        return 1;
    }

    // Seed the random number generator
    srand((unsigned)time(NULL));
    if (RAND_MAX == 0)
    {
        fprintf(stderr, "Random number generator not properly seeded.\n");
        return 1;
    }

    #pragma omp parallel num_threads(thread_count) reduction(+: number_in_circle)
    {
        double x, y, distance_squared;
        unsigned int my_seed = rand(); // Each thread gets a different seed

        #pragma omp for
        for (long long int toss = 0; toss < number_of_tosses; toss++)
        {
            x = random_double();
            y = random_double();
            distance_squared = x * x + y * y;
            if (distance_squared <= 1)
            {
                number_in_circle++;
            }
        }
    }

    double pi_estimate = 4 * number_in_circle / ((double)number_of_tosses);
    printf("Estimated value of π: %f\n", pi_estimate);

    return 0;
}