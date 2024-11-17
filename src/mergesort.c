#include "algorithms.h"

#include <stdlib.h>
#include <stddef.h>

// s -> índice inicial do segundo array ordenado
static void __merge(unsigned int arr[], const int l, const int s, const int r) {
    unsigned int *_temp = malloc((r-l) * sizeof(unsigned int));
    int i = l, j = s, k = 0;

    while (i < s && j < r) {
        if (arr[i] <= arr[j])
        _temp[k++] = arr[i++];
        else
        _temp[k++] = arr[j++];
    }

    while (i < s)
        _temp[k++] = arr[i++];

    while (j < r)
        _temp[k++] = arr[j++];

    for (i = l; i < r; i++)
        arr[i] = _temp[i-l];

    free(_temp);
}

static void __mergesort(unsigned int arr[], const int left, const int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        __mergesort(arr, left, mid);
        __mergesort(arr, mid + 1, right);
        __merge(arr, left, mid, right);
    }
}

void msort(unsigned int arr[], const size_t n) {
    __mergesort(arr, 0, n-1);
}
