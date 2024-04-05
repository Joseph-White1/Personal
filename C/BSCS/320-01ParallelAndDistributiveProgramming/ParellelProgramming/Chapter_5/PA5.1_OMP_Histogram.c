// Joseph White
// 12/15/2023
// CSCI 320: Week 7 Programming Assignment 5.1

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void find_bin(float data, float* bin_maxes, int bin_count, float min_meas, int* bin)
{
    for (int i = 0; i < bin_count; i++)
    {
        if (data < bin_maxes[i])
        {
            *bin = i;
            return;
        }
    }
    *bin = bin_count - 1;
}

void print_histo(int* bin_counts, int bin_count, int max_bin_count)
{
    for (int i = 0; i < bin_count; i++)
    {
        printf("Bin %d: ", i);
        float ratio = (float)bin_counts[i] / max_bin_count;
        int height = (int)(ratio * 50); // Scaling factor for histogram height, adjust as necessary
        for (int j = 0; j < height; j++)
        {
            printf("X");
        }
        printf("\n");
    }
}

int main()
{
    int data_count, bin_count;
    float min_meas, max_meas;

    // Initialize random number generator
    srand(time(NULL));

    // Prompt the user for input
    printf("Enter the number of data points: ");
    if (scanf("%d", &data_count) != 1 || data_count <= 0)
    {
        fprintf(stderr, "Invalid number of data points.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the minimum measurement: ");
    if (scanf("%f", &min_meas) != 1)
    {
        fprintf(stderr, "Invalid input for minimum measurement.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the maximum measurement: ");
    if (scanf("%f", &max_meas) != 1 || max_meas <= min_meas)
    {
        fprintf(stderr, "Invalid input for maximum measurement.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the number of bins: ");
    if (scanf("%d", &bin_count) != 1 || bin_count <= 0)
    {
        fprintf(stderr, "Invalid number of bins.\n");
        return EXIT_FAILURE;
    }

    // Dynamically allocate memory for data, bin_maxes, and bin_counts
    float* data = malloc(sizeof(float) * data_count);
    float* bin_maxes = malloc(sizeof(float) * bin_count);
    int* bin_counts = calloc(bin_count, sizeof(int)); // Using calloc to initialize to 0

    if (data == NULL || bin_maxes == NULL || bin_counts == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for data points or histogram bins.\n");
        free(data);
        free(bin_maxes);
        free(bin_counts);
        return EXIT_FAILURE;
    }

    // Generate random data points within the specified range
    for (int i = 0; i < data_count; i++)
    {
        data[i] = min_meas + (max_meas - min_meas) * ((float)rand() / RAND_MAX);
    }

    // Calculate the bin_maxes
    float bin_width = (max_meas - min_meas) / bin_count;
    for (int i = 0; i < bin_count; i++)
    {
        bin_maxes[i] = min_meas + bin_width * (i + 1);
    }

    // Parallel computation of the histograms
    #pragma omp parallel for default(none) shared(data, bin_maxes, bin_counts, data_count, bin_count, min_meas)
    for (int i = 0; i < data_count; i++)
    {
        int bin;
        find_bin(data[i], bin_maxes, bin_count, min_meas, &bin);
        #pragma omp atomic
        bin_counts[bin]++;
    }

    int max_bin_count = 0;
    for (int i = 0; i < bin_count; i++)
    {
        if (bin_counts[i] > max_bin_count) {
            max_bin_count = bin_counts[i];
        }
    }

    // Print the histogram
    print_histo(bin_counts, bin_count, max_bin_count);

    // Cleanup
    free(data);
    free(bin_maxes);
    free(bin_counts);
    return 0;
}