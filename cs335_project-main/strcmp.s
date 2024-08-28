mystrcmp:
    pushq	%rbp
    mov	%rsp,	%rbp
    pushq	%rbx
    pushq	%rdi
    pushq	%rsi
    pushq	%r12
    pushq	%r13
    pushq	%r14
    pushq	%r15

    testq $15, %rsp
    jz is_print_aligned_cmp

    pushq $0                 # align to 16 bytes

    movq  24(%rbp), %rdi
    movq  16(%rbp), %rsi      
    xor %rax, %rax          
    call strcmp

    add $8, %rsp
    jmp cmp_done

is_print_aligned_cmp:

    movq  24(%rbp), %rdi
    movq  16(%rbp), %rsi      
    xor %rax, %rax          
    call strcmp
    
cmp_done: 

    movq	$0,	%rcx
	cmp	%rax,	%rcx
    je	make_non_zero

    movq	$0,	%rax
	jmp    end_strcmp

make_non_zero:
    movq	$1,	%rax

end_strcmp:
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rsi
    popq %rdi
    popq %rbx
    popq %rbp

    ret

mystrcmpN:
    pushq	%rbp
    mov	%rsp,	%rbp
    pushq	%rbx
    pushq	%rdi
    pushq	%rsi
    pushq	%r12
    pushq	%r13
    pushq	%r14
    pushq	%r15

    testq $15, %rsp
    jz is_print_aligned_cmpN

    pushq $0                 # align to 16 bytes

    movq  24(%rbp), %rdi
    movq  16(%rbp), %rsi      
    xor %rax, %rax          
    call strcmp

    add $8, %rsp
    jmp end_strcmp

is_print_aligned_cmpN:

    movq  24(%rbp), %rdi
    movq  16(%rbp), %rsi      
    xor %rax, %rax          
    call strcmp
    jmp end_strcmp