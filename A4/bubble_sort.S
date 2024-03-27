.section .text
.global bubble_sort

bubble_sort:
  cmp $0, %rsi # if length = 0
  je .end_outer_loop

  mov $0, %r8    # i = 0
  sub $1, %rsi

outer_loop:
  cmp %rsi, %r8  # compare i to len
  jae .end_outer_loop # jump to end_outer_loop if i >= len  CHECK HERE IF NOT WORKING

  mov $0, %r9    # reset j to 0 for the inner loop

inner_loop:
  cmp %rsi, %r9  # compare j to len
  jae .end_inner_loop # jump to end_inner_loop if j >= len

  movl (%rdi, %r9, 4), %ebx   # arr[j]
  movl 4(%rdi, %r9, 4), %ecx  # arr[j + 1]

  cmp %ebx, %ecx   # compare arr[j] and arr[j + 1]
  jge .no_swap    # jump to no_swap if arr[j] <= arr[j + 1]

  # Swap arr[j] and arr[j + 1] in the original array pointed by %rsi
  movl %ebx, 4(%rdi, %r9, 4)  # arr[j + 1] = arr[j]
  movl %ecx, (%rdi, %r9, 4)    # arr[j] = arr[j + 1]

.no_swap:
  inc %r9        # increment j by 1
  jmp inner_loop  # jump to inner_loop

.end_inner_loop:
  inc %r8        # increment i by 1
  jmp outer_loop  # jump to outer_loop

.end_outer_loop:
  mov $0, %rax
  ret
