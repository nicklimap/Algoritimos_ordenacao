#include "quicksort.h"

static long int particiona(long int A[], long int inicio, long int fim) {
    long int pivo = A[fim];
    long int i = inicio - 1;
    
    for (long int j = inicio; j < fim; j++) {
        if (A[j] <= pivo) {
            i++;
            long int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    long int temp = A[i + 1];
    A[i + 1] = A[fim];
    A[fim] = temp;
    
    return i + 1;
}

void quickSort(long int A[], long int inicio, long int fim) {
    if (inicio < fim) {
        long int p = particiona(A, inicio, fim);
        quickSort(A, inicio, p - 1);
        quickSort(A, p + 1, fim);
    }
}