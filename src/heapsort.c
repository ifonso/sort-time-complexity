#include "algorithms.h"

#include <stddef.h>

static inline void SWAP(unsigned int *a, unsigned int *b) {
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

static void __heapify(unsigned int arr[], const size_t n, const unsigned int i) {
    unsigned int largest = i;
    unsigned int left = 2 * i + 1;
    unsigned int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        SWAP(&arr[i], &arr[largest]);
        __heapify(arr, n, largest);
    }
}

void hsort(unsigned int arr[], const size_t n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        __heapify(arr, n, i);
    }

    for (unsigned int i = n - 1; i > 0; i--) {
        SWAP(&arr[0], &arr[i]);
        __heapify(arr, i, 0);
    }
}
