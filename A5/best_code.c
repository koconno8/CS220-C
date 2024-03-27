#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long time_diff_in_picoseconds(struct timespec start, struct timespec end) {
    long long start_ns = (long long)start.tv_sec * 1000000000 + start.tv_nsec;
    long long end_ns = (long long)end.tv_sec * 1000000000 + end.tv_nsec;
    return end_ns - start_ns;
}

int

int main() {
    const int size = 800;
    float w[size][size];
    float x[size][size];
    float y[size][size];

    // Initialize matrices W and X with random values
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            w[i][j] = (float)rand() / RAND_MAX;
            x[i][j] = (float)rand() / RAND_MAX;
        }
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Best code (cache-friendly access)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            y[i][j] = 0.0;
            for (int k = 0; k < size; ++k) {
                y[i][j] += w[i][k] * x[k][j];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    long long time_diff_ps = time_diff_in_picoseconds(start_time, end_time);
    printf("Time difference for best code (size %dx%d): %lld picoseconds\n", size, size, time_diff_ps);

    return 0;
}
