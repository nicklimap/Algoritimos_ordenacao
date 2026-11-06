#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilarray.h"
#include "elapsedRunningTime.h"
#include "mergesort.h"
#include "quicksort.h"
#include "platforminfo.h"

extern clock_t begin;
extern clock_t end;

int main() {
    // Array de testes com crescimento progressivo de N
    long int tamanhos[] = {
        1000L, 
        10000L, 
        100000L, 
        1000000L, 
        5000000L, 
        10000000L, 
        20000000L,
        50000000L
    };
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=====================================================================================\n");
    printf("MERGE SORT vs QUICK SORT\n");
    printf("CPU: %s\n", CPU);
    printf("OS:  %s\n", OS);
    printf("=====================================================================================\n\n");
    
    printf("%-12s | %-16s | %-16s | %-14s | %-6s\n", 
           "Tamanho (N)", "Merge Sort (s)", "Quick Sort (s)", "Diferenca (s)", "Status");
    printf("-------------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_tamanhos; i++) {
        long int N = tamanhos[i];
        
        Array arrMerge = alocaArray(N);
        Array arrQuick = alocaArray(N);

        // Verificação de segurança para limite de memória RAM
        if (arrMerge.length == 0 || arrQuick.length == 0) {
            printf("%-12ld | ESTOURO DE MEMORIA (RAM INSUFICIENTE PARA ALOCAR N)\n", N);
            if (arrMerge.length > 0) dealocaArray(arrMerge);
            if (arrQuick.length > 0) dealocaArray(arrQuick);
            break; // Interrompe o teste antes do sistema congelar
        }

        // Copia os mesmos dados aleatorios para ambos os arrays
        randArray(arrMerge);
        for (long int j = 0; j < N; j++) {
            arrQuick.A[j] = arrMerge.A[j];
        }

        //  MERGE SORT
        start();
        mergeSort(arrMerge.A, 0, arrMerge.length - 1);
        stop();
        double tempo_merge = (double)(end - begin) / CLOCKS_PER_SEC;

        // QUICK SORT   
        start();
        quickSort(arrQuick.A, 0, arrQuick.length - 1);
        stop();
        double tempo_quick = (double)(end - begin) / CLOCKS_PER_SEC;

        // Validacao dos resultados
        long int rMerge = crescente(arrMerge);
        long int rQuick = crescente(arrQuick);
        char* status = (rMerge == N && rQuick == N) ? "OK" : "ERRO";

        double dif = tempo_merge - tempo_quick;

        printf("%12ld | %16.6f | %16.6f | %14.6f | %s\n", 
               N, tempo_merge, tempo_quick, dif, status);

        dealocaArray(arrMerge);
        dealocaArray(arrQuick);
    }

    return 0;
}