.section .text
.global fib_seq

fib_seq:
    cmpq $0, %rdi
    je .zero_case

    cmpq $1, %rdi
    je .one_case

    mov $0, %rbx    # int a = 0 first
    mov $1, %rcx    # int b = 1 second
    mov $0, %rdx    # int i = 2
    mov $0, %r8     # int temp = 0

    jmp .loop

    
    
.loop:
    cmpq %rdx, %rdi # compare i to n
    jl .end_loop       # resets the loop
    
    add %rbx, %rcx    # add a to b
    mov %rcx, %r8     # temp = b
    mov %rbx, %rcx    # b = a (previous b)
    mov %r8, %rbx     # a = temp (previous sum)
    
    inc %rdx       # increments i by 1
    
    jmp .loop
    
.end_loop:
    mov %rcx, %rax # move the value from b into return register
    ret

.zero_case:
    mov $0, %rax
    ret

.one_case:
    mov $1, %rax
    ret
