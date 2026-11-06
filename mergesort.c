#include <stdlib.h>
#include "mergesort.h"

void merge(int *A, long int left, long int mid, long int right) {
    long int n1 = mid - left + 1;
    long int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (long int i = 0; i < n1; i++)
        L[i] = A[left + i];
    for (long int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    long int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int *A, long int left, long int right) {
    if (left < right) {
        long int mid = left + (right - left) / 2;
        
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}