#include <stdio.h>

// Returns n-th term in fibonacci sequence using iteration
extern int fib_seq(unsigned n);
// Modifies arr in-place to sort it using bubble sort
extern int bubble_sort(int *arr, unsigned len);
// Returns index of target in arr using binary search
extern int binary_search(int *arr, unsigned len, unsigned target);


int main() {
    // Test fib_seq
    printf("Fibonacci sequence:\n");
    for (unsigned i = 0; i < 10; ++i) {
        printf("fib(%u) = %d\n", i, fib_seq(i));
    }

    // Test bubble_sort
    int arr1[] = {5, 2, 9, 1, 5};
    unsigned len1 = sizeof(arr1) / sizeof(arr1[0]);
    bubble_sort(arr1, len1);

    printf("\nSorted array after bubble sort:\n");
    for (unsigned i = 0; i < len1; ++i) {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    // Test binary_search
    int arr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 44};
    unsigned len2 = sizeof(arr2) / sizeof(arr2[0]);
    int target = 44;

    int result = binary_search(arr2, len2, target);

    if (result != -1) {
        printf("\n%d found at index %d\n", target, result+1);
    } else {
        printf("\n%d not found in the array\n", target);
    }

    return 0;
}

//fibonacci
/*int fib_seq(unsigned n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int a = 0, b = 1, temp;
    int i = 2;
    while(i <= n) {
        temp = a + b;
        a = b;
        b = temp;
        i++;
    }
    return temp;
}g*/

//binary
/*int binary_search(int arr[], unsigned len, int target) {
    int lower = 0;
    int upper = len - 1;

    while (lower <= upper) {
        int middle = (lower + upper) / 2;
        if (arr[middle] == target) {
            return middle;
        } else if (arr[middle] < target) {
            lower = middle + 1;
        } else {
            upper = middle - 1;
        }
    }

    return -1;
}*/

//bubble
/*void bubble_sort(int arr[], unsigned len) {
    unsigned i = 0;
    while (i < len) {
        unsigned j = 0;
        while (j < len - i - 1) {
            if (arr[j] > arr[j + 1]) {
                // swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++
        }
        i++;
    }
}*/

//new bubble
/*void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    void bubbleSort(int arr[], int n) {
    int i = 0;
    while (i < n - 1) {
        int j = 0;
        int swapped = 0;  // Use integer to represent boolean (0 for false, 1 for true)

        while (j < n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                // Inline swap logic
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                swapped = 1;  // Set to true
            }
            j++;
        }

        // If no two elements were swapped by inner loop, then break
        if (!swapped)
            break;

        i++;
    }
}

}*/