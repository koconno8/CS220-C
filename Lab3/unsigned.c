#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long interleave (unsigned int i1, unsigned int i2){
    unsigned char* p1 = (unsigned char*) &i1;
    unsigned char* p2 = (unsigned char*) &i2;

    unsigned long result;
    unsigned char* point = (unsigned char*) &result;

    int counter = 0;
    for(int i = 0; i < sizeof(unsigned long); i++){
       
        point[i] = p1[counter];
        point[i+1] = p2[counter];
        i++;
        counter++;
    }

    return result;
}

void print_raw_bytes(unsigned char* start, unsigned int len){
    for(int i = 0; i<len; i++){
        printf("%p: 0x%2x\n", &start[i], (unsigned char)start[i]);
    }
}

void* allocate_heap(unsigned int size, int val) {
    void* ptr = malloc(size);

    if (ptr == NULL) {
        printf("Memory allocation failed");
        return 0;
    }

    memset(ptr, val, size);
    return ptr;
}

int main(){
    unsigned int i1 = 0xdeadbeef;
    unsigned int i2 = 0x12345678;
    interleave (i1, i2);

    unsigned long result = interleave(i1, i2);
    printf("%lx\n", result);

    print_raw_bytes((char *)&result, sizeof(result));

    void* vari = allocate_heap(8, 4);

    print_raw_bytes(vari, 8);



    return 0;


}