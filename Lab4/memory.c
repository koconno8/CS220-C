#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS1 10
#define COLS1 10
#define ROWS2 10
#define COLS2 10

int matrix1[ROWS1][COLS1];
int matrix2[ROWS2][COLS2] = {4};

char* str = "Hello World!";

#define COUNT 10
#define COUNT2 10000
#define COUNT3 10

void foo(){
    int arr[COUNT2];
    void *p = malloc(COUNT3);
}

int main()
{
    static int x1[COUNT];
    static int x2[COUNT] = {8};
    foo();
    printf("sizeof(matrix1) == %d\n", sizeof(matrix1));
    return 0;
}


