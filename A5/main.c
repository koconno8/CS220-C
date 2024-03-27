#include <time.h>
#include <stdio.h>

long long time_diff_in_picoseconds(struct timespec start, struct timespec end) 
{
    long long start_ns = (long long)start.tv_sec * 1000000000 + start.tv_nsec;
    long long end_ns = (long long)end.tv_sec * 1000000000 + end.tv_nsec;
    return end_ns - start_ns;
}

struct timespec start_time, end_time;

// Cache-friendly code
void best_code(int SIZE, float W[SIZE][SIZE], float X[SIZE][SIZE], float Y[SIZE][SIZE]) 
{    
    //struct timespec start, end;
    //clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            float var = 0.0;
            for (int k = 0; k < SIZE; k++) 
            {
                var += W[i][k] * X[k][j];
            }
            Y[i][j] = var;
        }
    }
    
    //clock_gettime(CLOCK_MONOTONIC, &end); 
    //return time_diff_in_picoseconds(start, end);
}

// Not cache friendly code
void worst_code(int SIZE, float W[SIZE][SIZE], float X[SIZE][SIZE], float Y[SIZE][SIZE]) 
{
    //struct timespec start, end;
    //clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            float sum = 0.0;
            for (int k = 0; k < SIZE; k++) 
            {
                sum += W[k][i] * X[j][k];
            }
            Y[i][j] = sum;
        }
    }
    //clock_gettime(CLOCK_MONOTONIC, &end);
    //return time_diff_in_picoseconds(start, end);   
}


int main() 
{
    int sizeArr[] = {10,200,800};
    for(int i = 0; i <= 2; i++)
    {
        int SIZE = sizeArr[i];
        
        float W[SIZE][SIZE];
        float X[SIZE][SIZE];
        float Y[SIZE][SIZE];

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        //... perfrm the operations
        worst_code(SIZE, W, X, Y);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        long long time_diff_worst_ps = time_diff_in_picoseconds(start_time, end_time);

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        //... perfrm the operations
        best_code(SIZE, W, X, Y);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        long long time_diff_best_ps = time_diff_in_picoseconds(start_time, end_time);

        long long time_diff_ps = time_diff_worst_ps - time_diff_best_ps;
        //long long time_diff_ps = time_diff_in_picoseconds(start_time, end_time);
        printf("Time for worst case %d x %d: %lld picoseconds \n", SIZE, SIZE, time_diff_worst_ps);
        printf("Time for best case %d x %d: %lld picoseconds \n", SIZE, SIZE, time_diff_best_ps);
        printf("Time difference: %lld picoseconds\n", time_diff_ps);
    }
}

