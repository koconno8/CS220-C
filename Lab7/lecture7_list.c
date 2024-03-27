#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	struct node *next; 
	int data; //can be anything else including (and often) void *
};

extern struct node *reverse_list_asm(struct node *head);

// Creates a list with length of num_nodes, with all nodes' data fields 
// initialized to the order it is in (i.e. first node->data = 1, second = 2, etc)
// Returns head of that new list
struct node *create_rand_list(int num_nodes)
{
	struct node *head = NULL; 
	struct node *new_node = NULL; 

	int i; 
	for(i = 0; i < num_nodes; i++) {
		new_node = (struct node *) malloc (sizeof(struct node)); 
		if(new_node == NULL) exit(-1); 
		// Sets all fields of new node to 0
		memset(new_node, 0, sizeof(struct node)); 
		new_node->data = i+1; 
		if(head != NULL)
			new_node->next = head; 
		head = new_node; 
	}

	return head; 
}

struct node *reverse_list(struct node *head)
{
	// Reverse of an empty list is empty
	if(head == NULL) return NULL; 
	
	struct node *curr, *prev; 
	prev = NULL; 
	curr = head; 

	// Iterate head, set cur's next to cur
	// Update previous node and cur
	// Basically, just reverses the connection between the next two nodes
	// When all the connections are reversed, the list is reversed
	while(head->next != NULL) {
		head = head->next; 
		curr->next = prev; 
		prev = curr; 
		curr = head; 
	}
	head->next = prev; 
	return head;
}

// Free all nodes in a list, with the first node in that list = head
void destroy_list(struct node *head)
{
	struct node *temp; 
	while(head != NULL) {
		// Need temp node to preserve the next element after free
		temp = head->next;
		free(head); 
		head = temp; 
	}
}

void print_list(struct node *head)
{
	while(head != NULL) {
		printf("%d -> ", head->data); 
		head = head->next; 
	}
	printf("NULL\n"); 
}

struct node *add_new_node_at_head(struct node *head, struct node *node)
{
	node->next = head; 
	return node; 
}

// Adds new node at tail
// Sicne tail isn't tracked, we need to iterate to the end of the list to add the new node
struct node *add_node_at_end(struct node *head, struct node *node)
{
	struct node *new_head = head; 
	if(head == NULL) {
		return add_new_node_at_head(head, node); 
	}

	while(head->next != NULL) {
		head = head->next; 
	}
	head->next = node; 
	node->next = NULL; 
	return new_head; 
}

// Implementation of a tortoise and hare algorithm
// Sometimes asked on LeetCode problems and interview questions.
// It can be applied to almost any problem where you want to find a loop/circle, 
// so it's a good algorithm to learn about, when/if you have time
int is_loop(struct node *head)
{
	// Two tracker nodes, one fast and one slow
	struct node *fast, *slow; 
	slow = fast = head; 

	// If fast and slow meet before the end of the list, that is only possible if there is a loop.
	// This is because the fast one is moving fast, 
	// so the slow one can't catch up unless fast lapped it
	while(fast != NULL && fast->next != NULL) {
		// Iterate slow by 1
		slow = slow->next; 
		// Iterate fast by 2
		fast = fast->next->next; 
		if(slow == fast) //found the loop
			return 1; 
	}
	return 0; 
}



int main()
{
	struct node *head = create_rand_list(3); 
	print_list(head); 

	//head->next->next = head; 
	int loop = is_loop(head); 
	printf("%d\n", loop); 
	head = reverse_list_asm(head);
	print_list(head); 
	destroy_list(head); 
	return 0; 
}

