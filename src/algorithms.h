//
// Created by Afonso Lucas on 13/11/24.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <stddef.h>

// Ordena a lista com algorítimo mergesort `"inplace"`
void msort(unsigned int arr[], const size_t n);
// Ordena a lista com algorítimo quicksort `"inplace"`
void quicksort(unsigned int arr[], const size_t n);
// Ordena a lista com algorítimo heapsort `"inplace"`
void hsort(unsigned int arr[], const size_t n);

#endif //ALGORITHMS_H
