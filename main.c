#include "src/algorithms.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include<unistd.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

enum ALGO {
    MERGE_SORT,
    QUICK_SORT,
    HEAP_SORT
};

int *create_array_from_file(const char *filename, int *out_size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open file [%s] for reading.\n", filename);
        exit(EXIT_FAILURE);
    }

    int count = 0;
    int temp;

    while (fscanf(file, "%d", &temp) == 1)
        count++;

    int *numbers = (int *)malloc(count * sizeof(int));
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

    *out_size = count;
    return numbers;
}

void sort_numbers_from_file(const char *filename, clock_t *time_spent, const enum ALGO al) {
    int n;
    int *arr = create_array_from_file(filename, &n);

    const clock_t tick = clock();
    if (al == MERGE_SORT) {
        msort(arr, n);
    }
    const clock_t toc = clock();
    *time_spent = (toc - tick);
    free(arr);
}

double get_time_mean_in_secods(const clock_t *times, const int n) {
    double total = 0;
    for (int i = 0; i < n; i++) total += ((double)times[i]/CLOCKS_PER_SEC);
    return total/(double)n;
}

// imprimir a média de tempo e o progresso
int main() {

    clock_t *measures = (clock_t *) malloc(50 * sizeof(clock_t));
    size_t current_iteration = 0;

    const char *file = "./generated/1_000_000/numbers_";

    for (int i = 0; i < 50; i++) {
        // Limpar a tela
        clrscr();

        // string do arquivo (é mais rápido fazer na stack)
        size_t b_size = strlen(file) + 20;
        char *c_filepath = (char *)malloc(b_size);
        snprintf(c_filepath, b_size, "%s%d%s", file, i+1, ".txt");

        // faz o cálculo
        sort_numbers_from_file(c_filepath, &measures[i], MERGE_SORT);

        // imprime resultados
        printf("progress: %d/50\nmean... %.4f\n", i+1, get_time_mean_in_secods(measures, i+1));

        free(c_filepath);
    }

    // clock_t time;
    // sort_numbers_from_file(file, &time, MERGE_SORT);
    // printf("tt sort: %f\n", ((double)time)/CLOCKS_PER_SEC);

    return 0;
}
