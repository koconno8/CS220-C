.section .text
.global bubble_sort

bubble_sort:
    cmp $0, %rsi
    je .end

    mov $0, %r8
    sub $1, %rsi

.loop1:
    cmp %rsi, %r8
    jae .end

    mov $0, %r9

.loop2: 
    cmp %rsi, %r9
    jae .loop1edit

    movl (%rdi,%r9,4), %ebx
    movl 4(%rdi,%r9,4), %ecx

    cmpl %ecx, %ebx
    jle .noif

    mov %ebx, 4(%rdi, %r9,4)
    mov %ecx, (%rdi,%r9,4)

.noif:
    inc %r9
    jmp .loop2

.loop1edit:
    inc %r8
    jmp .loop1

.end: 
    mov $0, %rax
    ret