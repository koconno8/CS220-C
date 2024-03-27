// complete the lines 15-16 and lines 20-24

.section .note.GNU-stack,"",%progbits

.text
	.global reverse_list_asm

reverse_list_asm:
	push %rbp;			    // move rbp to stack
	mov %rsp, %rbp;			// move rsp to rbp
	mov %rdi, %rax;			// move head
	cmpq $0x0, %rax;		// see if head == null
	jne next;
	jmp final;
next:
	// curr = %rax, curr->next = (%rax), prev = %r8 ----- don't need to implement
	movq $0x0, %r8;           // init prev to null *****
	cmpq $0x0, (%rax);      // see if curr->next == null *****
	jne loop;
	jmp end_loop;
loop:
	movq (%rax), %rcx;      // set temp = cur->next **What is temp %rcx**
	movq %r8, (%rax);       // set curr->next = prev ****
	movq %rax, %r8;         // set prev = curr ****
	movq %rcx, %rax;        // set curr = temp ****
	cmpq $0x0, (%rax);      // see if curr->next == null ****
	jne loop;
	jmp end_loop;
end_loop:
	movq %r8, (%rax); 		// set curr->next = prev
	jmp final;
final:
	pop %rbp;
	ret;
