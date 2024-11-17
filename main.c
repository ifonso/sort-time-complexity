#include "src/algorithms.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include<unistd.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#define MAX_STRING_SIZE 128
#define NUMBER_OF_TESTS 5
#define SAMPLE_SIZE 50

enum ALGO {
    MERGE_SORT,
    QUICK_SORT,
    HEAP_SORT
};

// Utility -------------------------------------------------------

const char *get_algorithm_name(const enum ALGO a) {
    switch (a) {
        case MERGE_SORT:
            return "Mergesort";
        case QUICK_SORT:
            return "Quicksort";
        case HEAP_SORT:
            return "Heapsort";
        default:
            return "Unknown";
    }
}

double get_mean_time_in_seconds(const clock_t *times, const int n) {
    double total = 0;
    for (int i = 0; i < n; i++) total += ((double)times[i]/CLOCKS_PER_SEC);
    return total/(double)n;
}

double get_std_dev_in_seconds(const clock_t *times, const int n, double mean) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double diff = ((double)times[i] / CLOCKS_PER_SEC) - mean;
        sum += diff * diff;
    }
    return sqrt(sum / (n - 1));
}

// ---------------------------------------------------------------

unsigned int *create_array_from_file(const char *filename, int *array_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open file [%s] for reading.\n", filename);
        exit(EXIT_FAILURE);
    }

    int count = 0;
    unsigned int temp;

    while (fscanf(file, "%d", &temp) == 1)
        count++;

    unsigned int *numbers = (unsigned int *)malloc(count * sizeof(unsigned int));
    if (!numbers) {
        fprintf(stderr, "Memory allocation failed while creating [%s].\n", filename);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    rewind(file);
    for (int i = 0; i < count; i++) {
        fscanf(file, "%d", &numbers[i]);
    }
    fclose(file);

    *array_size = count;
    return numbers;
}

void measure_sort_time(unsigned int *arr, const int n, clock_t *time_spent, const enum ALGO al) {
    const clock_t tick = clock();
    if (al == MERGE_SORT) {
        msort(arr, n);
    }
    const clock_t toc = clock();
    *time_spent = (toc - tick);
}

void calculate_mean_time_sort(const char* base_path, const char* n, const int num_files, const enum ALGO alg, double *mean, double *std_dev) {
    clock_t *measures = (clock_t *) malloc(num_files * sizeof(clock_t));
    if (!measures) {
        fprintf(stderr, "Memory allocation failed while creating measures.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_files; i++) {
        // Limpar a tela
        clrscr();

        // filepath do arquivo (é mais rápido fazer na stack)
        char c_filepath[MAX_STRING_SIZE];
        snprintf(c_filepath, MAX_STRING_SIZE, "%s%s%d%s", base_path, "numbers_", i+1, ".txt");

        int current_n;
        unsigned int *current_array = create_array_from_file(c_filepath, &current_n);
        measure_sort_time(current_array, current_n, &measures[i], alg);

        printf("Ordenando arrays...\n");
        printf("N = %s | %d/%d\n", n, i+1, num_files);
        printf("tempo médio -> %.4f\n s", get_mean_time_in_seconds(measures, i+1));
    }

    *mean = get_mean_time_in_seconds(measures, num_files);
    *std_dev = get_std_dev_in_seconds(measures, num_files, *mean);

    free(measures);
}

int main(int argc, char ** argv) {
    enum ALGO current_algo = MERGE_SORT;
    struct {
        double mean_time;
        double std_dev;
        const char *label;
    } results[NUMBER_OF_TESTS] = {
        {0, 0, "10_000"},
        {0, 0, "100_000"},
        {0, 0, "1_000_000"},
        {0, 0, "10_000_000"},
        {0, 0, "100_000_000"}
    };

    const char *basepath = "./generated/";

    for (int t = 0; t < NUMBER_OF_TESTS; t++) {
        char base_test_path[MAX_STRING_SIZE];
        snprintf(base_test_path, MAX_STRING_SIZE, "%s%s%s", basepath, results[t].label, "/");

        calculate_mean_time_sort(base_test_path, results[t].label, SAMPLE_SIZE, current_algo,
                                 &results[t].mean_time, &results[t].std_dev);
    }

    // print final results
    clrscr();
    printf("Resultado do %s...\n\n", get_algorithm_name(current_algo));

    for (int r = 0; r < NUMBER_OF_TESTS; r++) {
        printf("N = %s\n", results[r].label);
        printf("(média) T = %.4f s\n", results[r].mean_time);
        printf("(desvio padrão) σ = %.4f s\n\n", results[r].std_dev);
    }

    return 0;
}
