#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct node { 
    int val; 
    struct node *next;
};
typedef struct node Node;


//QUESTION 1
unsigned int count_nodes(struct node *head){
    struct node *ptr = head; //creates a copy of the address of head to see the first node
    int count = 0;
    while(ptr != NULL){
        count++;
        ptr = ptr -> next; //points to the next node in the linked list
    }
    //printf("Total Nodes: %d\n", count);
    return count;
}

//QUESTION 2
Node **split_list(Node *head, unsigned int num){
    Node** ret = malloc(num * sizeof(Node*));

    //initialize all elements to null
    for (int i = 0; i < num; i++) 
    {
        ret[i] = NULL; 
    }

    Node* current = head; //pointer initialized at original list
    int i = 0; //keeps track of current list

    //go through the list splitting it into num sub lists
    while (current != NULL){
        Node* next = current -> next; //set a node to the next node in the original list
        current -> next = ret[i]; //the original lists next node points at the ith value of the linked list
        ret[i] = current; // the ith node is now the current node
        current = next; //move to the next node in the list

        i = (i+1) % num; //increment i using modulo to go through split the lists
    }
    
    /*printing
    for (int j = 0; j < num; j++) {
        printf("Split List %d: ", j);
        Node *list = ret[j];
        while (list != NULL) {
            printf("%d -> ", list->val); 
            list = list->next;
        }
        printf("NULL\n");
    }*/

    return ret;
}

//QUESTION 3
Node *interleave_list(Node *head1, Node *head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Node *head = head1;  // Initialize the head of the result list with head1
    Node *tail = head1;

    head1 = head1->next;

    while (head1 != NULL || head2 != NULL) {
        if (head2 != NULL) {
            tail->next = head2;
            tail = head2;
            head2 = head2->next;
        }

        if (head1 != NULL) {
            tail->next = head1;
            tail = head1;
            head1 = head1->next;
        }
    }
    return head;
}


//QUESTION 4
int get_float_exponent(float f){
    union{
        float f;
        int i;
    } u;
    int exp;

    u.f = f;
    if(u.i == 0){
        exp = 0;
    }
    else{exp = (u.i >> 23) & 0xFF;
    exp -= 127;
}
    //printf("Exponent: %d\n", exp); 

    return exp;
       
}