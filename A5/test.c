#include <stdio.h>
#include <time.h>

#define SIZE 800

void matrixMultiplicationBest(float W[SIZE][SIZE], float X[SIZE][SIZE], float Y[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            float sum = 0.0;
            for (int k = 0; k < SIZE; k++) {
                sum += W[i][k] * X[k][j];
            }
            Y[i][j] = sum;
        }
    }
}

void matrixMultiplicationWorst(float W[SIZE][SIZE], float X[SIZE][SIZE], float Y[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            float sum = 0.0;
            for (int k = 0; k < SIZE; k++) {
                sum += W[k][i] * X[j][k];
            }
            Y[i][j] = sum;
        }
    }
}

int main() {
    float W[SIZE][SIZE];
    float X[SIZE][SIZE];
    float Y[SIZE][SIZE];

    // Initialize W and X matrices with values

    // Measure time for best cache-friendly access
    clock_t startBest = clock();

    matrixMultiplicationBest(W, X, Y);

    clock_t endBest = clock();
    double cpu_time_used_best = ((double) (endBest - startBest)) / CLOCKS_PER_SEC;

    // Measure time for worst cache-friendly access
    clock_t startWorst = clock();

    matrixMultiplicationWorst(W, X, Y);

    clock_t endWorst = clock();
    double cpu_time_used_worst = ((double) (endWorst - startWorst)) / CLOCKS_PER_SEC;

    printf("Matrix size: %dx%d\n", SIZE, SIZE);
    printf("Time taken for best cache-friendly access: %f seconds\n", cpu_time_used_best);
    printf("Time taken for worst cache-friendly access: %f seconds\n", cpu_time_used_worst);

    return 0;
}