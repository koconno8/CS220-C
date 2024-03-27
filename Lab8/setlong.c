/* setlong.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

#define SIZE 10

/*Task 2a*/
struct var_state{
    void *addr;
    unsigned int size;
    struct var_state *next;
    char data[0];
};

struct var_state *var_state_head = NULL;

/*The buffer to hold the program state*/
jmp_buf env; 

/* g is a global variable*/
int g = 10;

/*Task 1a: Implement signal handler called "handler"*/
void handler(int signum){
    if(signum == SIGSEGV){
        longjmp(env,signum);
    }
}

/*Task 2b*/
void save_state(void *var_addr, unsigned int var_size){
    struct var_state *new_node = malloc(sizeof(struct var_state) + var_size);
    //struct var_state *new_node = (struct var_state *)malloc(sizeof(struct var_state)+var_size);
    new_node->addr = var_addr;
    new_node->size = var_size;
    memcpy(new_node->data, var_addr, var_size);
    new_node->next = var_state_head;
    var_state_head = new_node;
}

void restore_state(){
    while (var_state_head != NULL) {
        struct var_state *node = var_state_head;
        memcpy(node->addr, node->data, node->size);
        var_state_head = node->next;
        free(node);
    }
}

int main(){
    int x;
    char *p;
    x = 11;
    p = (char *) malloc (SIZE);
    p[0] = p[1] = 'x';

    //Task 2c
    save_state(&g, sizeof(g));
    save_state(&x, sizeof(x));
    save_state(&p, sizeof(p));
    save_state(&p, SIZE);

    /* Task 1b: Using the signal function, register a "handler" function as the handler for SIGSEGV*/
    signal(SIGSEGV, handler);

    if(setjmp(env) == 0){
        /*This is the "risky" block*/
        g = 30;
        x = 100;
        p = 0;
        p[0] = p[1] = p[2] = 'x'; 
    } else
    {
        restore_state();
        printf("%d, %d, %c, %c\n", g, x, p[0],p[1]);
    }
    return 0;
}
