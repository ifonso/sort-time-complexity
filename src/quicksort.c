#include "algorithms.h"

#include <stddef.h>

static inline void SWAP(unsigned int *a, unsigned int *b) {
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

static unsigned int __partition(unsigned int arr[], const int l, const int r) {
    unsigned int pivot = arr[r];
    int temp = l;

    for (int k = l; k < r; k++) {
        if (arr[k] <= pivot) {
            SWAP(&arr[temp], &arr[k]);
            temp++;
        }
    }
    SWAP(&arr[temp], &arr[r]);
    return temp;
}

static void __quicksort(unsigned int arr[], int left, int right) {
    if (left < right) {
        unsigned int p = __partition(arr, left, right);

        __quicksort(arr, left, p-1);
        __quicksort(arr, p+1, right);
    }
}

void quicksort(unsigned int arr[], const size_t n) {
    __quicksort(arr, 0, n-1);
}
