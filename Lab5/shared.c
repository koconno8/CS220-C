/* shared.c */
#include <stdio.h>
#include <stdlib.h>
#include <shared.h>

void *logger_malloc(unsigned int size){
    void *ret;
    printf("Alternating %u bytes...\n", size);
    ret = malloc(size);
    if(ret == 0){
        printf("Allocation Failed! :(\n)");
    }
    else{
        printf("Successfully allocated %p\n", ret);
    }
    return ret;
}

void logger_free(void *p){
    printf("free()ing memory at %p...",p);
    free(p);
    printf("DONE\n");
}