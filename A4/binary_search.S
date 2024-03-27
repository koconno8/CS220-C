.section .text
.global binary_search
binary_search:
    cmp $0, %rsi # if length = 0  
    je .not_found

    # mov $0, %rax # result (index), initialize to 0
    mov $0, %r8 # low = 0  
    
    mov %rsi, %rbx
    dec %rbx # high = len - 1

search_loop:
    cmp %rbx, %r8 # while low <= high  
    jg .not_found # jump to not_found if low > high  

    mov %r8, %r9 # calculate mid: mid = (low + high) / 2
    add %rbx, %r9 
    sar $1, %r9 # middle index is %r9d

    movl (%rdi, %r9, 4), %ecx # arr[mid]  
    cmpl %ecx, %edx # compare arr[mid] and target
    je .found # jump to found if arr[mid] == target
    jae .search_low # jump to search_low if arr[mid] >= target 
    jbe .search_high # jump to search_high if arr[mid] <= target

.search_low:
    inc %r9d # move to the right half 
    movl %r9d, %r8d # update low to mid + 1  
    jmp search_loop

.search_high:
   dec %r9d # move to the left half  
   movl %r9d, %ebx # update high to mid - 1
   jmp search_loop
   
.found:
    movl %r9d, %eax # update result with the index of the found element 
    ret

.not_found:
    movl $-1, %eax # result = -1 if not found
    ret
