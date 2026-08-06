	.file	"forth-primitives.c"
	.text
	.p2align 4
	.globl	prim_body_store
	.type	prim_body_store, @function
prim_body_store:
.LFB48:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %eax
	andl	$1023, %edx
	orq	%rcx, %rax
	orq	%rcx, %rdx
	movq	64(%rdi), %rcx
	movl	(%rax), %esi
	movl	(%rdx), %edx
	andl	88(%rdi), %edx
	movl	%esi, (%rcx,%rdx)
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE48:
	.size	prim_body_store, .-prim_body_store
	.p2align 4
	.globl	prim_body_c_store
	.type	prim_body_c_store, @function
prim_body_c_store:
.LFB49:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rdx
	movq	(%rdi), %rsi
	movq	%rdi, %rax
	leaq	4(%rdx), %rcx
	addq	$8, %rdx
	andl	$1023, %ecx
	andl	$1023, %edx
	orq	%rsi, %rcx
	orq	%rsi, %rdx
	movl	(%rcx), %ecx
	movl	(%rdx), %edx
	andl	80(%rdi), %ecx
	movq	64(%rdi), %rdi
	movb	%dl, (%rdi,%rcx)
	movq	8(%rax), %rsi
	leaq	8(%rsi), %rdx
	andl	$1023, %edx
	orq	(%rax), %rdx
	movq	%rdx, 8(%rax)
	ret
	.cfi_endproc
.LFE49:
	.size	prim_body_c_store, .-prim_body_c_store
	.p2align 4
	.globl	prim_body_w_store
	.type	prim_body_w_store, @function
prim_body_w_store:
.LFB50:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %eax
	andl	$1023, %edx
	orq	%rcx, %rax
	orq	%rcx, %rdx
	movq	64(%rdi), %rcx
	movl	(%rax), %esi
	movl	(%rdx), %edx
	andl	84(%rdi), %edx
	movw	%si, (%rcx,%rdx)
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE50:
	.size	prim_body_w_store, .-prim_body_w_store
	.p2align 4
	.globl	prim_immediate_tick
	.type	prim_immediate_tick, @function
prim_immediate_tick:
.LFB51:
	.cfi_startproc
	endbr64
	movl	$32, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE51:
	.size	prim_immediate_tick, .-prim_immediate_tick
	.p2align 4
	.globl	prim_compile_tick
	.type	prim_compile_tick, @function
prim_compile_tick:
.LFB52:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE52:
	.size	prim_compile_tick, .-prim_compile_tick
	.p2align 4
	.globl	prim_immediate_paren
	.type	prim_immediate_paren, @function
prim_immediate_paren:
.LFB53:
	.cfi_startproc
	endbr64
	movl	$23, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE53:
	.size	prim_immediate_paren, .-prim_immediate_paren
	.p2align 4
	.globl	prim_body_star
	.type	prim_body_star, @function
prim_body_star:
.LFB55:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rdx), %ecx
	imull	(%rax), %ecx
	movl	%ecx, (%rdx)
	ret
	.cfi_endproc
.LFE55:
	.size	prim_body_star, .-prim_body_star
	.p2align 4
	.globl	prim_body_star_slash
	.type	prim_body_star_slash, @function
prim_body_star_slash:
.LFB56:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	movq	%rdi, %r8
	leaq	4(%rax), %rdx
	leaq	8(%rax), %rdi
	andl	$1023, %edx
	leaq	12(%rax), %rcx
	andl	$1023, %edi
	movl	$1, %eax
	orq	%rsi, %rdx
	andl	$1023, %ecx
	orq	%rsi, %rdi
	movl	(%rdx), %edx
	orq	%rsi, %rcx
	movslq	(%rcx), %rsi
	testl	%edx, %edx
	cmove	%eax, %edx
	movslq	(%rdi), %rax
	imulq	%rsi, %rax
	movslq	%edx, %rsi
	cqto
	idivq	%rsi
	movl	%eax, (%rcx)
	movq	%rdi, 8(%r8)
	ret
	.cfi_endproc
.LFE56:
	.size	prim_body_star_slash, .-prim_body_star_slash
	.p2align 4
	.globl	prim_body_star_slash_mod
	.type	prim_body_star_slash_mod, @function
prim_body_star_slash_mod:
.LFB57:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %r9
	movq	%rdi, %r8
	leaq	4(%rax), %rsi
	leaq	8(%rax), %rdi
	leaq	12(%rax), %rcx
	andl	$1023, %esi
	andl	$1023, %edi
	andl	$1023, %ecx
	orq	%r9, %rsi
	orq	%r9, %rdi
	orq	%r9, %rcx
	movslq	(%rdi), %rax
	movl	(%rsi), %edx
	movslq	(%rcx), %r9
	imulq	%r9, %rax
	testl	%edx, %edx
	je	.L12
	movslq	%edx, %r9
	cqto
	idivq	%r9
.L12:
	movl	%edx, (%rcx)
	movl	%eax, (%rdi)
	movq	%rsi, 8(%r8)
	ret
	.cfi_endproc
.LFE57:
	.size	prim_body_star_slash_mod, .-prim_body_star_slash_mod
	.p2align 4
	.globl	prim_body_plus
	.type	prim_body_plus, @function
prim_body_plus:
.LFB58:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	addl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE58:
	.size	prim_body_plus, .-prim_body_plus
	.p2align 4
	.globl	prim_body_comma
	.type	prim_body_comma, @function
prim_body_comma:
.LFB59:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	76(%rdi), %edx
	andl	88(%rdi), %edx
	addq	$4, %rax
	movl	%edx, 76(%rdi)
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %ecx
	movq	%rax, 8(%rdi)
	movq	64(%rdi), %rax
	movl	%ecx, (%rax,%rdx)
	movl	76(%rdi), %eax
	addl	$4, %eax
	andl	88(%rdi), %eax
	movl	%eax, 76(%rdi)
	ret
	.cfi_endproc
.LFE59:
	.size	prim_body_comma, .-prim_body_comma
	.p2align 4
	.globl	prim_body_c_comma
	.type	prim_body_c_comma, @function
prim_body_c_comma:
.LFB60:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	76(%rdi), %edx
	andl	80(%rdi), %edx
	movq	64(%rdi), %rcx
	addq	$4, %rax
	movl	%edx, 76(%rdi)
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	movb	%al, (%rcx,%rdx)
	movl	76(%rdi), %eax
	addl	$1, %eax
	andl	80(%rdi), %eax
	movl	%eax, 76(%rdi)
	ret
	.cfi_endproc
.LFE60:
	.size	prim_body_c_comma, .-prim_body_c_comma
	.p2align 4
	.globl	prim_body_w_comma
	.type	prim_body_w_comma, @function
prim_body_w_comma:
.LFB61:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	76(%rdi), %edx
	movl	84(%rdi), %ecx
	movq	64(%rdi), %r8
	addq	$4, %rax
	andl	%ecx, %edx
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	%edx, 76(%rdi)
	movl	%edx, %esi
	addl	$2, %edx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	%ecx, %edx
	movw	%ax, (%r8,%rsi)
	movl	%edx, 76(%rdi)
	ret
	.cfi_endproc
.LFE61:
	.size	prim_body_w_comma, .-prim_body_w_comma
	.p2align 4
	.globl	prim_body_minus
	.type	prim_body_minus, @function
prim_body_minus:
.LFB62:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	subl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE62:
	.size	prim_body_minus, .-prim_body_minus
	.p2align 4
	.globl	prim_immediate_backslash
	.type	prim_immediate_backslash, @function
prim_immediate_backslash:
.LFB63:
	.cfi_startproc
	endbr64
	movl	$8, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE63:
	.size	prim_immediate_backslash, .-prim_immediate_backslash
	.p2align 4
	.globl	prim_immediate_dot_quote
	.type	prim_immediate_dot_quote, @function
prim_immediate_dot_quote:
.LFB68:
	.cfi_startproc
	endbr64
	movl	$12, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE68:
	.size	prim_immediate_dot_quote, .-prim_immediate_dot_quote
	.p2align 4
	.globl	prim_body_slash
	.type	prim_body_slash, @function
prim_body_slash:
.LFB70:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rsi
	movq	(%rdi), %rax
	leaq	4(%rsi), %rdx
	andl	$1023, %edx
	orq	%rax, %rdx
	leaq	4(%rdx), %rcx
	movl	(%rdx), %esi
	movq	%rdx, 8(%rdi)
	andl	$1023, %ecx
	orq	%rax, %rcx
	movl	(%rcx), %eax
	testl	%esi, %esi
	je	.L24
	cltd
	idivl	%esi
.L24:
	movl	%eax, (%rcx)
	ret
	.cfi_endproc
.LFE70:
	.size	prim_body_slash, .-prim_body_slash
	.p2align 4
	.globl	prim_body_slash_mod
	.type	prim_body_slash_mod, @function
prim_body_slash_mod:
.LFB71:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rcx
	movq	(%rdi), %rax
	leaq	4(%rcx), %rsi
	addq	$8, %rcx
	andl	$1023, %esi
	andl	$1023, %ecx
	orq	%rax, %rsi
	orq	%rax, %rcx
	movl	(%rsi), %edx
	movl	(%rcx), %eax
	testl	%edx, %edx
	je	.L29
	movl	%edx, %edi
	cltd
	idivl	%edi
.L29:
	movl	%eax, (%rsi)
	movl	%edx, (%rcx)
	ret
	.cfi_endproc
.LFE71:
	.size	prim_body_slash_mod, .-prim_body_slash_mod
	.p2align 4
	.globl	prim_immediate_colon
	.type	prim_immediate_colon, @function
prim_immediate_colon:
.LFB72:
	.cfi_startproc
	endbr64
	movl	$7, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE72:
	.size	prim_immediate_colon, .-prim_immediate_colon
	.p2align 4
	.globl	prim_immediate_semicolon
	.type	prim_immediate_semicolon, @function
prim_immediate_semicolon:
.LFB74:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE74:
	.size	prim_immediate_semicolon, .-prim_immediate_semicolon
	.p2align 4
	.globl	prim_compile_semicolon
	.type	prim_compile_semicolon, @function
prim_compile_semicolon:
.LFB75:
	.cfi_startproc
	endbr64
	movl	$30, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE75:
	.size	prim_compile_semicolon, .-prim_compile_semicolon
	.p2align 4
	.globl	prim_body_less_than
	.type	prim_body_less_than, @function
prim_body_less_than:
.LFB76:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	setl	%al
	movzbl	%al, %eax
	negl	%eax
	movl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE76:
	.size	prim_body_less_than, .-prim_body_less_than
	.p2align 4
	.globl	prim_body_equals
	.type	prim_body_equals, @function
prim_body_equals:
.LFB77:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	sete	%al
	movzbl	%al, %eax
	negl	%eax
	movl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE77:
	.size	prim_body_equals, .-prim_body_equals
	.p2align 4
	.globl	prim_body_greater_than
	.type	prim_body_greater_than, @function
prim_body_greater_than:
.LFB78:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	setg	%al
	movzbl	%al, %eax
	negl	%eax
	movl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE78:
	.size	prim_body_greater_than, .-prim_body_greater_than
	.p2align 4
	.globl	prim_body_to_number
	.type	prim_body_to_number, @function
prim_body_to_number:
.LFB79:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r8
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	8(%rdi), %r12
	movq	(%rdi), %r15
	movl	72(%rdi), %r9d
	leaq	4(%r12), %rax
	leaq	8(%r12), %rbp
	andl	$1023, %eax
	andl	$1023, %ebp
	orq	%r15, %rax
	orq	%r15, %rbp
	movl	(%rax), %ecx
	movl	0(%rbp), %edx
	cmpl	%ecx, %r9d
	cmova	%ecx, %r9d
	testl	%r9d, %r9d
	je	.L47
	subl	$1, %r9d
	movl	80(%rdi), %r11d
	movq	64(%rdi), %r10
	xorl	%ebx, %ebx
	movq	%r12, -16(%rsp)
	movl	%r9d, %edi
	xorl	%esi, %esi
	movl	$2147483648, %r14d
	movabsq	$6442450943, %r13
	movq	%r15, -8(%rsp)
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L54:
	leal	-48(%rcx), %r12d
	cmpb	$9, %r12b
	ja	.L51
	leaq	(%rsi,%rsi,4), %rsi
	subl	$48, %ecx
	addq	%rsi, %rsi
	movslq	%ecx, %rcx
	testb	%bl, %bl
	jne	.L43
	addq	%rcx, %rsi
	leaq	(%rsi,%r14), %rcx
	cmpq	%rcx, %r13
	jb	.L52
.L41:
	addl	$1, %edx
	subl	$1, %edi
	jb	.L53
.L46:
	andl	%r11d, %edx
	movl	%edx, %ecx
	movzbl	(%r10,%rcx), %ecx
	cmpb	$45, %cl
	sete	%r12b
	cmpl	%r9d, %edi
	sete	%r15b
	andb	%r15b, %r12b
	je	.L54
	movl	%r12d, %ebx
	addl	$1, %edx
	subl	$1, %edi
	jnb	.L46
.L53:
	movq	-16(%rsp), %r12
	movq	-8(%rsp), %r15
	xorl	%r9d, %r9d
.L40:
	movl	%edx, (%rax)
	subq	$4, %r12
	movl	%esi, 0(%rbp)
	movl	%r9d, 4(%r12)
	andl	$1023, %r12d
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	movq	%r12, %rbp
	orq	%r15, %rbp
	movq	%rbp, 8(%r8)
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L43:
	.cfi_restore_state
	subq	%rcx, %rsi
	leaq	(%rsi,%r14), %rcx
	cmpq	%rcx, %r13
	jnb	.L41
.L52:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	movq	%rbp, 8(%r8)
	movl	$3, 144(%r8)
	popq	%rbp
	.cfi_def_cfa_offset 40
	movb	$0, 104(%r8)
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
	movq	-16(%rsp), %r12
	movq	-8(%rsp), %r15
	leal	1(%rdi), %r9d
	jmp	.L40
.L47:
	xorl	%esi, %esi
	jmp	.L40
	.cfi_endproc
.LFE79:
	.size	prim_body_to_number, .-prim_body_to_number
	.p2align 4
	.globl	prim_body_to_hex
	.type	prim_body_to_hex, @function
prim_body_to_hex:
.LFB80:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	movq	%rdi, %r10
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	8(%rdi), %r12
	movq	(%rdi), %r13
	movl	72(%rdi), %esi
	leaq	4(%r12), %r11
	leaq	8(%r12), %r9
	andl	$1023, %r11d
	andl	$1023, %r9d
	orq	%r13, %r11
	orq	%r13, %r9
	movl	(%r11), %edx
	movl	(%r9), %eax
	cmpl	%edx, %esi
	cmova	%edx, %esi
	testl	%esi, %esi
	je	.L79
	movl	80(%rdi), %edi
	movq	64(%r10), %r8
	andl	%edi, %eax
	movl	%eax, %edx
	cmpb	$45, (%r8,%rdx)
	je	.L85
	xorl	%ecx, %ecx
	cmpl	$1, %esi
	je	.L75
.L58:
	movl	%edi, %edx
	andl	%eax, %edx
	movl	%edx, %ebx
	cmpb	$48, (%r8,%rbx)
	je	.L86
.L60:
	testb	%cl, %cl
	je	.L75
.L59:
	xorl	%edx, %edx
	movl	$2147483648, %ebp
	movabsq	$6442450943, %rbx
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L87:
	subl	$48, %ecx
.L69:
	movslq	%ecx, %rcx
	salq	$4, %rdx
	subq	%rcx, %rdx
	leaq	(%rdx,%rbp), %rcx
	cmpq	%rcx, %rbx
	jb	.L65
	addl	$1, %eax
	subl	$1, %esi
	je	.L67
.L74:
	andl	%edi, %eax
	movl	%eax, %ecx
	movzbl	(%r8,%rcx), %ecx
	leal	-48(%rcx), %r14d
	cmpb	$9, %r14b
	jbe	.L87
	leal	-97(%rcx), %r14d
	cmpb	$5, %r14b
	ja	.L70
	subl	$87, %ecx
	jmp	.L69
	.p2align 4,,10
	.p2align 3
.L86:
	addl	$1, %edx
	andl	%edi, %edx
	movl	%edx, %ebx
	cmpb	$120, (%r8,%rbx)
	jne	.L60
	leal	1(%rdx), %eax
	subl	$2, %esi
	jne	.L60
	.p2align 4,,10
	.p2align 3
.L79:
	xorl	%edx, %edx
.L56:
	movl	%eax, (%r11)
	movl	%edx, (%r9)
	leaq	-4(%r12), %r9
	andl	$1023, %r9d
	movl	%esi, (%r12)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	orq	%r13, %r9
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	movq	%r9, 8(%r10)
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L70:
	.cfi_restore_state
	leal	-65(%rcx), %r14d
	cmpb	$5, %r14b
	ja	.L56
	subl	$55, %ecx
	jmp	.L69
	.p2align 4,,10
	.p2align 3
.L65:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	movb	$0, 104(%r10)
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	movq	%r9, 8(%r10)
	movl	$3, 144(%r10)
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L67:
	.cfi_restore_state
	xorl	%esi, %esi
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L75:
	xorl	%edx, %edx
	movl	$2147483648, %ebp
	movabsq	$6442450943, %rbx
	jmp	.L66
	.p2align 4,,10
	.p2align 3
.L88:
	leal	-97(%rcx), %r14d
	cmpb	$5, %r14b
	jbe	.L62
	leal	-65(%rcx), %r14d
	cmpb	$5, %r14b
	ja	.L56
	subl	$55, %ecx
.L64:
	movslq	%ecx, %rcx
	salq	$4, %rdx
	addq	%rcx, %rdx
	leaq	(%rdx,%rbp), %rcx
	cmpq	%rcx, %rbx
	jb	.L65
	addl	$1, %eax
	subl	$1, %esi
	je	.L67
.L66:
	andl	%edi, %eax
	movl	%eax, %ecx
	movzbl	(%r8,%rcx), %ecx
	leal	-48(%rcx), %r14d
	cmpb	$9, %r14b
	ja	.L88
	subl	$48, %ecx
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L62:
	subl	$87, %ecx
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L85:
	subl	$1, %esi
	addl	$1, %eax
	movl	$1, %ecx
	cmpl	$1, %esi
	ja	.L58
	testl	%esi, %esi
	je	.L79
	movl	$1, %esi
	jmp	.L59
	.cfi_endproc
.LFE80:
	.size	prim_body_to_hex, .-prim_body_to_hex
	.p2align 4
	.globl	prim_body_question_dupe
	.type	prim_body_question_dupe, @function
prim_body_question_dupe:
.LFB83:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	4(%rax), %rdx
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rdx), %edx
	testl	%edx, %edx
	je	.L89
	movl	%edx, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	movq	%rax, 8(%rdi)
.L89:
	ret
	.cfi_endproc
.LFE83:
	.size	prim_body_question_dupe, .-prim_body_question_dupe
	.p2align 4
	.globl	prim_body_fetch
	.type	prim_body_fetch, @function
prim_body_fetch:
.LFB84:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	64(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %edx
	andl	88(%rdi), %edx
	movl	(%rcx,%rdx), %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE84:
	.size	prim_body_fetch, .-prim_body_fetch
	.p2align 4
	.globl	prim_body_c_fetch
	.type	prim_body_c_fetch, @function
prim_body_c_fetch:
.LFB85:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	64(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %edx
	andl	80(%rdi), %edx
	movzbl	(%rcx,%rdx), %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE85:
	.size	prim_body_c_fetch, .-prim_body_c_fetch
	.p2align 4
	.globl	prim_body_w_fetch
	.type	prim_body_w_fetch, @function
prim_body_w_fetch:
.LFB86:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	64(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %edx
	andl	84(%rdi), %edx
	movzwl	(%rcx,%rdx), %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE86:
	.size	prim_body_w_fetch, .-prim_body_w_fetch
	.p2align 4
	.globl	prim_body_abs
	.type	prim_body_abs, @function
prim_body_abs:
.LFB87:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %edx
	testl	%edx, %edx
	js	.L99
	ret
	.p2align 4,,10
	.p2align 3
.L99:
	negl	%edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE87:
	.size	prim_body_abs, .-prim_body_abs
	.p2align 4
	.globl	prim_body_accept
	.type	prim_body_accept, @function
prim_body_accept:
.LFB88:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rdx
	movq	168(%rdi), %r8
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rdx, %rax
	movq	%rax, 8(%rdi)
	testq	%r8, %r8
	je	.L106
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	4(%rax), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	andl	$1023, %ebp
	movq	%rdi, %rbx
	orq	%rbp, %rdx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movl	80(%rdi), %ecx
	movl	(%rax), %eax
	movq	64(%rdi), %rsi
	movl	(%rdx), %edi
	movl	%eax, %edx
	andl	%ecx, %edi
	call	*%r8
	orq	(%rbx), %rbp
	movl	%eax, 0(%rbp)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L106:
	.cfi_restore 3
	.cfi_restore 6
	ret
	.cfi_endproc
.LFE88:
	.size	prim_body_accept, .-prim_body_accept
	.p2align 4
	.globl	prim_body_align
	.type	prim_body_align, @function
prim_body_align:
.LFB89:
	.cfi_startproc
	endbr64
	movl	76(%rdi), %eax
	movl	%eax, %edx
	andl	$3, %edx
	je	.L109
	addl	$4, %eax
	subl	%edx, %eax
	andl	88(%rdi), %eax
	movl	%eax, 76(%rdi)
.L109:
	ret
	.cfi_endproc
.LFE89:
	.size	prim_body_align, .-prim_body_align
	.p2align 4
	.globl	prim_body_aligned
	.type	prim_body_aligned, @function
prim_body_aligned:
.LFB90:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %edx
	movl	%edx, %esi
	leal	4(%rdx), %ecx
	andl	$3, %esi
	subl	%esi, %ecx
	testl	%esi, %esi
	cmovne	%ecx, %edx
	andl	88(%rdi), %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE90:
	.size	prim_body_aligned, .-prim_body_aligned
	.p2align 4
	.globl	prim_body_allot
	.type	prim_body_allot, @function
prim_body_allot:
.LFB91:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	addl	76(%rdi), %eax
	andl	80(%rdi), %eax
	movl	%eax, 76(%rdi)
	ret
	.cfi_endproc
.LFE91:
	.size	prim_body_allot, .-prim_body_allot
	.p2align 4
	.globl	prim_body_and
	.type	prim_body_and, @function
prim_body_and:
.LFB92:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	andl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE92:
	.size	prim_body_and, .-prim_body_and
	.p2align 4
	.globl	prim_compile_begin
	.type	prim_compile_begin, @function
prim_compile_begin:
.LFB94:
	.cfi_startproc
	endbr64
	movl	$2, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE94:
	.size	prim_compile_begin, .-prim_compile_begin
	.p2align 4
	.globl	prim_body_b_l
	.type	prim_body_b_l, @function
prim_body_b_l:
.LFB95:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	$32, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE95:
	.size	prim_body_b_l, .-prim_body_b_l
	.p2align 4
	.globl	prim_body_bounds
	.type	prim_body_bounds, @function
prim_body_bounds:
.LFB96:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %edx
	andl	$1023, %eax
	orq	%rsi, %rdx
	orq	%rsi, %rax
	movl	(%rdx), %ecx
	movl	(%rax), %esi
	movl	%esi, (%rdx)
	leal	(%rcx,%rsi), %edx
	andl	80(%rdi), %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE96:
	.size	prim_body_bounds, .-prim_body_bounds
	.p2align 4
	.globl	prim_body_cells
	.type	prim_body_cells, @function
prim_body_cells:
.LFB97:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	sall	$2, (%rax)
	ret
	.cfi_endproc
.LFE97:
	.size	prim_body_cells, .-prim_body_cells
	.p2align 4
	.globl	prim_immediate_char
	.type	prim_immediate_char, @function
prim_immediate_char:
.LFB98:
	.cfi_startproc
	endbr64
	movl	$6, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE98:
	.size	prim_immediate_char, .-prim_immediate_char
	.p2align 4
	.globl	prim_immediate_constant
	.type	prim_immediate_constant, @function
prim_immediate_constant:
.LFB100:
	.cfi_startproc
	endbr64
	movl	$9, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE100:
	.size	prim_immediate_constant, .-prim_immediate_constant
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\n"
	.text
	.p2align 4
	.globl	prim_body_c_r
	.type	prim_body_c_r, @function
prim_body_c_r:
.LFB102:
	.cfi_startproc
	endbr64
	movq	152(%rdi), %rax
	testq	%rax, %rax
	je	.L134
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	leaq	.LC0(%rip), %rdi
	call	*%rax
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L126
	xorl	%eax, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	jmp	*%rdx
	.p2align 4,,10
	.p2align 3
.L126:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L134:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE102:
	.size	prim_body_c_r, .-prim_body_c_r
	.p2align 4
	.globl	prim_immediate_create
	.type	prim_immediate_create, @function
prim_immediate_create:
.LFB103:
	.cfi_startproc
	endbr64
	movl	$10, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE103:
	.size	prim_immediate_create, .-prim_immediate_create
	.p2align 4
	.globl	prim_compile_do
	.type	prim_compile_do, @function
prim_compile_do:
.LFB107:
	.cfi_startproc
	endbr64
	movl	$11, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE107:
	.size	prim_compile_do, .-prim_compile_do
	.p2align 4
	.globl	prim_body_drop
	.type	prim_body_drop, @function
prim_body_drop:
.LFB108:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE108:
	.size	prim_body_drop, .-prim_body_drop
	.p2align 4
	.globl	prim_body_two_drop
	.type	prim_body_two_drop, @function
prim_body_two_drop:
.LFB109:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$8, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE109:
	.size	prim_body_two_drop, .-prim_body_two_drop
	.p2align 4
	.globl	prim_body_dupe
	.type	prim_body_dupe, @function
prim_body_dupe:
.LFB110:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	4(%rax), %rdx
	subq	$4, %rax
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rdx), %edx
	movl	%edx, 4(%rax)
	andl	$1023, %eax
	orq	%rcx, %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE110:
	.size	prim_body_dupe, .-prim_body_dupe
	.p2align 4
	.globl	prim_body_two_dupe
	.type	prim_body_two_dupe, @function
prim_body_two_dupe:
.LFB111:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	leaq	8(%rax), %rcx
	subq	$4, %rax
	andl	$1023, %ecx
	orq	%rsi, %rcx
	movl	(%rcx), %ecx
	movl	%ecx, 4(%rax)
	andl	$1023, %eax
	orq	%rsi, %rax
	leaq	8(%rax), %rcx
	subq	$4, %rax
	andl	$1023, %ecx
	orq	%rsi, %rcx
	movl	(%rcx), %ecx
	movl	%ecx, 4(%rax)
	andl	$1023, %eax
	orq	%rsi, %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE111:
	.size	prim_body_two_dupe, .-prim_body_two_dupe
	.p2align 4
	.globl	prim_compile_else
	.type	prim_compile_else, @function
prim_compile_else:
.LFB113:
	.cfi_startproc
	endbr64
	movl	$13, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE113:
	.size	prim_compile_else, .-prim_compile_else
	.p2align 4
	.globl	prim_body_emit
	.type	prim_body_emit, @function
prim_body_emit:
.LFB114:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	152(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	testq	%rdx, %rdx
	je	.L144
	movl	(%rax), %eax
	movq	%rdi, %rbx
	movb	$0, 7(%rsp)
	leaq	6(%rsp), %rdi
	movb	%al, 6(%rsp)
	call	*%rdx
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L144
	xorl	%eax, %eax
	call	*%rdx
.L144:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L155
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L155:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE114:
	.size	prim_body_emit, .-prim_body_emit
	.p2align 4
	.globl	prim_body_fill
	.type	prim_body_fill, @function
prim_body_fill:
.LFB115:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rcx
	movq	(%rdi), %rsi
	movq	%rdi, %rdx
	leaq	8(%rcx), %rax
	andl	$1023, %eax
	orq	%rsi, %rax
	movl	(%rax), %r8d
	leaq	12(%rcx), %rax
	andl	$1023, %eax
	orq	%rsi, %rax
	testl	%r8d, %r8d
	je	.L157
	movl	72(%rdi), %edi
	cmpl	%edi, %r8d
	cmova	%edi, %r8d
	testl	%r8d, %r8d
	je	.L157
	addq	$4, %rcx
	movl	(%rax), %eax
	andl	$1023, %ecx
	orq	%rsi, %rcx
	movzbl	(%rcx), %r9d
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L158:
	andl	80(%rdx), %eax
	movq	64(%rdx), %rdi
	addl	$1, %ecx
	movl	%eax, %esi
	addl	$1, %eax
	movb	%r9b, (%rdi,%rsi)
	cmpl	%ecx, %r8d
	jne	.L158
	movq	8(%rdx), %rax
	addq	$12, %rax
	andl	$1023, %eax
	orq	(%rdx), %rax
.L157:
	movq	%rax, 8(%rdx)
	ret
	.cfi_endproc
.LFE115:
	.size	prim_body_fill, .-prim_body_fill
	.p2align 4
	.globl	prim_body_here
	.type	prim_body_here, @function
prim_body_here:
.LFB116:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	76(%rdi), %edx
	subq	$4, %rax
	movl	%edx, 4(%rax)
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE116:
	.size	prim_body_here, .-prim_body_here
	.p2align 4
	.globl	prim_compile_i
	.type	prim_compile_i, @function
prim_compile_i:
.LFB118:
	.cfi_startproc
	endbr64
	movl	$17, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE118:
	.size	prim_compile_i, .-prim_compile_i
	.p2align 4
	.globl	prim_compile_if
	.type	prim_compile_if, @function
prim_compile_if:
.LFB120:
	.cfi_startproc
	endbr64
	movl	$18, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE120:
	.size	prim_compile_if, .-prim_compile_if
	.p2align 4
	.globl	prim_body_invert
	.type	prim_body_invert, @function
prim_body_invert:
.LFB121:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	notl	(%rax)
	ret
	.cfi_endproc
.LFE121:
	.size	prim_body_invert, .-prim_body_invert
	.p2align 4
	.globl	prim_compile_j
	.type	prim_compile_j, @function
prim_compile_j:
.LFB123:
	.cfi_startproc
	endbr64
	movl	$19, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE123:
	.size	prim_compile_j, .-prim_compile_j
	.p2align 4
	.globl	prim_body_key
	.type	prim_body_key, @function
prim_body_key:
.LFB124:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rdi), %rax
	movq	(%rdi), %rdx
	leaq	4(%rax), %rbx
	movq	176(%rdi), %rax
	andl	$1023, %ebx
	orq	%rbx, %rdx
	movl	(%rdx), %ecx
	testq	%rax, %rax
	je	.L178
	movq	%rdi, %rbp
	xorl	%edi, %edi
	testl	%ecx, %ecx
	setne	%dil
	call	*%rax
	movq	200(%rbp), %rdx
	orq	0(%rbp), %rbx
	movl	%eax, (%rbx)
	testq	%rdx, %rdx
	je	.L171
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	*%rdx
	.p2align 4,,10
	.p2align 3
.L178:
	.cfi_restore_state
	movl	$0, (%rdx)
.L171:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE124:
	.size	prim_body_key, .-prim_body_key
	.p2align 4
	.globl	prim_compile_literal
	.type	prim_compile_literal, @function
prim_compile_literal:
.LFB126:
	.cfi_startproc
	endbr64
	movl	$20, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE126:
	.size	prim_compile_literal, .-prim_compile_literal
	.p2align 4
	.globl	prim_compile_loop
	.type	prim_compile_loop, @function
prim_compile_loop:
.LFB128:
	.cfi_startproc
	endbr64
	movl	$21, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE128:
	.size	prim_compile_loop, .-prim_compile_loop
	.p2align 4
	.globl	prim_body_l_shift
	.type	prim_body_l_shift, @function
prim_body_l_shift:
.LFB129:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rax), %ecx
	sall	%cl, (%rdx)
	ret
	.cfi_endproc
.LFE129:
	.size	prim_body_l_shift, .-prim_body_l_shift
	.p2align 4
	.globl	prim_body_max
	.type	prim_body_max, @function
prim_body_max:
.LFB130:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	jge	.L182
	movl	%eax, (%rdx)
.L182:
	ret
	.cfi_endproc
.LFE130:
	.size	prim_body_max, .-prim_body_max
	.p2align 4
	.globl	prim_body_min
	.type	prim_body_min, @function
prim_body_min:
.LFB131:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	jle	.L184
	movl	%eax, (%rdx)
.L184:
	ret
	.cfi_endproc
.LFE131:
	.size	prim_body_min, .-prim_body_min
	.p2align 4
	.globl	prim_body_mod
	.type	prim_body_mod, @function
prim_body_mod:
.LFB132:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rsi
	movq	(%rdi), %rax
	leaq	4(%rsi), %rdx
	andl	$1023, %edx
	orq	%rax, %rdx
	leaq	4(%rdx), %rcx
	movq	%rdx, 8(%rdi)
	movl	(%rdx), %edx
	andl	$1023, %ecx
	orq	%rax, %rcx
	movl	(%rcx), %eax
	testl	%edx, %edx
	je	.L187
	movl	%edx, %esi
	cltd
	idivl	%esi
.L187:
	movl	%edx, (%rcx)
	ret
	.cfi_endproc
.LFE132:
	.size	prim_body_mod, .-prim_body_mod
	.p2align 4
	.globl	prim_body_negate
	.type	prim_body_negate, @function
prim_body_negate:
.LFB133:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	negl	(%rax)
	ret
	.cfi_endproc
.LFE133:
	.size	prim_body_negate, .-prim_body_negate
	.p2align 4
	.globl	prim_body_or
	.type	prim_body_or, @function
prim_body_or:
.LFB134:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	orl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE134:
	.size	prim_body_or, .-prim_body_or
	.p2align 4
	.globl	prim_body_over
	.type	prim_body_over, @function
prim_body_over:
.LFB135:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	8(%rax), %rdx
	subq	$4, %rax
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rdx), %edx
	movl	%edx, 4(%rax)
	andl	$1023, %eax
	orq	%rcx, %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE135:
	.size	prim_body_over, .-prim_body_over
	.p2align 4
	.globl	prim_body_two_over
	.type	prim_body_two_over, @function
prim_body_two_over:
.LFB136:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rdx
	leaq	12(%rax), %rcx
	andl	$1023, %ecx
	orq	%rdx, %rcx
	movl	(%rcx), %r8d
	leaq	16(%rax), %rcx
	subq	$8, %rax
	andl	$1023, %ecx
	andl	$1023, %eax
	orq	%rdx, %rax
	orq	%rdx, %rcx
	movl	(%rcx), %esi
	movq	%rax, 8(%rdi)
	leaq	4(%rax), %rcx
	addq	$8, %rax
	andl	$1023, %ecx
	andl	$1023, %eax
	orq	%rdx, %rcx
	orq	%rdx, %rax
	movl	%r8d, (%rcx)
	movl	%esi, (%rax)
	ret
	.cfi_endproc
.LFE136:
	.size	prim_body_two_over, .-prim_body_two_over
	.p2align 4
	.globl	prim_body_page
	.type	prim_body_page, @function
prim_body_page:
.LFB137:
	.cfi_startproc
	endbr64
	movq	208(%rdi), %rdx
	testq	%rdx, %rdx
	je	.L203
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	xorl	%eax, %eax
	call	*%rdx
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L195
	xorl	%eax, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	jmp	*%rdx
	.p2align 4,,10
	.p2align 3
.L195:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L203:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE137:
	.size	prim_body_page, .-prim_body_page
	.p2align 4
	.globl	prim_compile_repeat
	.type	prim_compile_repeat, @function
prim_compile_repeat:
.LFB139:
	.cfi_startproc
	endbr64
	movl	$26, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE139:
	.size	prim_compile_repeat, .-prim_compile_repeat
	.p2align 4
	.globl	prim_body_rote
	.type	prim_body_rote, @function
prim_body_rote:
.LFB140:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	leaq	4(%rax), %rcx
	leaq	8(%rax), %rdx
	addq	$12, %rax
	andl	$1023, %ecx
	andl	$1023, %edx
	andl	$1023, %eax
	orq	%rsi, %rcx
	orq	%rsi, %rdx
	orq	%rsi, %rax
	movl	(%rcx), %r8d
	movl	(%rdx), %edi
	movl	(%rax), %esi
	movl	%esi, (%rcx)
	movl	%r8d, (%rdx)
	movl	%edi, (%rax)
	ret
	.cfi_endproc
.LFE140:
	.size	prim_body_rote, .-prim_body_rote
	.p2align 4
	.globl	prim_body_minus_rote
	.type	prim_body_minus_rote, @function
prim_body_minus_rote:
.LFB141:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	leaq	4(%rax), %rcx
	leaq	8(%rax), %rdx
	addq	$12, %rax
	andl	$1023, %ecx
	andl	$1023, %edx
	andl	$1023, %eax
	orq	%rsi, %rcx
	orq	%rsi, %rdx
	orq	%rsi, %rax
	movl	(%rcx), %edi
	movl	(%rdx), %r8d
	movl	(%rax), %esi
	movl	%r8d, (%rcx)
	movl	%esi, (%rdx)
	movl	%edi, (%rax)
	ret
	.cfi_endproc
.LFE141:
	.size	prim_body_minus_rote, .-prim_body_minus_rote
	.p2align 4
	.globl	prim_body_r_shift
	.type	prim_body_r_shift, @function
prim_body_r_shift:
.LFB142:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rax), %ecx
	shrl	%cl, (%rdx)
	ret
	.cfi_endproc
.LFE142:
	.size	prim_body_r_shift, .-prim_body_r_shift
	.p2align 4
	.globl	prim_immediate_s_quote
	.type	prim_immediate_s_quote, @function
prim_immediate_s_quote:
.LFB143:
	.cfi_startproc
	endbr64
	movl	$27, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE143:
	.size	prim_immediate_s_quote, .-prim_immediate_s_quote
	.section	.rodata.str1.1
.LC1:
	.string	" "
	.text
	.p2align 4
	.globl	prim_body_space
	.type	prim_body_space, @function
prim_body_space:
.LFB145:
	.cfi_startproc
	endbr64
	movq	152(%rdi), %rax
	testq	%rax, %rax
	je	.L219
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	leaq	.LC1(%rip), %rdi
	call	*%rax
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L211
	xorl	%eax, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	jmp	*%rdx
	.p2align 4,,10
	.p2align 3
.L211:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L219:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE145:
	.size	prim_body_space, .-prim_body_space
	.p2align 4
	.globl	prim_body_swap
	.type	prim_body_swap, @function
prim_body_swap:
.LFB147:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %edx
	andl	$1023, %eax
	orq	%rcx, %rdx
	orq	%rcx, %rax
	movl	(%rdx), %esi
	movl	(%rax), %ecx
	movl	%ecx, (%rdx)
	movl	%esi, (%rax)
	ret
	.cfi_endproc
.LFE147:
	.size	prim_body_swap, .-prim_body_swap
	.p2align 4
	.globl	prim_body_two_swap
	.type	prim_body_two_swap, @function
prim_body_two_swap:
.LFB148:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rdi
	leaq	4(%rax), %rsi
	leaq	8(%rax), %rcx
	leaq	12(%rax), %rdx
	addq	$16, %rax
	andl	$1023, %esi
	andl	$1023, %ecx
	andl	$1023, %edx
	andl	$1023, %eax
	orq	%rdi, %rsi
	orq	%rdi, %rcx
	orq	%rdi, %rdx
	orq	%rdi, %rax
	movl	(%rsi), %r9d
	movl	(%rcx), %r8d
	movl	(%rdx), %r10d
	movl	(%rax), %edi
	movl	%r10d, (%rsi)
	movl	%edi, (%rcx)
	movl	%r9d, (%rdx)
	movl	%r8d, (%rax)
	ret
	.cfi_endproc
.LFE148:
	.size	prim_body_two_swap, .-prim_body_two_swap
	.p2align 4
	.globl	prim_compile_then
	.type	prim_compile_then, @function
prim_compile_then:
.LFB150:
	.cfi_startproc
	endbr64
	movl	$31, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE150:
	.size	prim_compile_then, .-prim_compile_then
	.p2align 4
	.globl	prim_body_type
	.type	prim_body_type, @function
prim_body_type:
.LFB151:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$16, %rsp
	.cfi_def_cfa_offset 64
	movq	8(%rdi), %rcx
	movq	(%rdi), %rsi
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	152(%rdi), %rax
	leaq	8(%rcx), %rdx
	andl	$1023, %edx
	orq	%rsi, %rdx
	testq	%rax, %rax
	je	.L226
	addq	$4, %rcx
	movl	(%rdx), %ebx
	movl	72(%rdi), %edx
	movb	$0, 7(%rsp)
	andl	$1023, %ecx
	orq	%rsi, %rcx
	movl	(%rcx), %r13d
	cmpl	%edx, %r13d
	cmova	%edx, %r13d
	testl	%r13d, %r13d
	je	.L227
	xorl	%r12d, %r12d
	leaq	6(%rsp), %r14
	jmp	.L228
	.p2align 4,,10
	.p2align 3
.L241:
	movq	152(%rbp), %rax
.L228:
	andl	80(%rbp), %ebx
	movq	64(%rbp), %rcx
	addl	$1, %r12d
	movq	%r14, %rdi
	movl	%ebx, %edx
	addl	$1, %ebx
	movzbl	(%rcx,%rdx), %edx
	movb	%dl, 6(%rsp)
	call	*%rax
	cmpl	%r12d, %r13d
	jne	.L241
.L227:
	movq	192(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L229
	xorl	%eax, %eax
	call	*%rdx
.L229:
	movq	8(%rbp), %rax
	leaq	8(%rax), %rdx
	andl	$1023, %edx
	orq	0(%rbp), %rdx
.L226:
	movq	%rdx, 8(%rbp)
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L242
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L242:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE151:
	.size	prim_body_type, .-prim_body_type
	.p2align 4
	.globl	prim_body_u_less_than
	.type	prim_body_u_less_than, @function
prim_body_u_less_than:
.LFB152:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	sbbl	%eax, %eax
	movl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE152:
	.size	prim_body_u_less_than, .-prim_body_u_less_than
	.p2align 4
	.globl	prim_body_u_greater_than
	.type	prim_body_u_greater_than, @function
prim_body_u_greater_than:
.LFB153:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	andl	$1023, %edx
	orq	%rcx, %rdx
	movl	(%rdx), %esi
	cmpl	%esi, (%rax)
	sbbl	%eax, %eax
	movl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE153:
	.size	prim_body_u_greater_than, .-prim_body_u_greater_than
	.p2align 4
	.globl	prim_compile_until
	.type	prim_compile_until, @function
prim_compile_until:
.LFB155:
	.cfi_startproc
	endbr64
	movl	$34, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE155:
	.size	prim_compile_until, .-prim_compile_until
	.p2align 4
	.globl	prim_immediate_variable
	.type	prim_immediate_variable, @function
prim_immediate_variable:
.LFB156:
	.cfi_startproc
	endbr64
	movl	$35, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE156:
	.size	prim_immediate_variable, .-prim_immediate_variable
	.p2align 4
	.globl	prim_compile_while
	.type	prim_compile_while, @function
prim_compile_while:
.LFB159:
	.cfi_startproc
	endbr64
	movl	$36, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE159:
	.size	prim_compile_while, .-prim_compile_while
	.p2align 4
	.globl	prim_body_x_or
	.type	prim_body_x_or, @function
prim_body_x_or:
.LFB160:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	xorl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE160:
	.size	prim_body_x_or, .-prim_body_x_or
	.p2align 4
	.globl	prim_compile_left_bracket
	.type	prim_compile_left_bracket, @function
prim_compile_left_bracket:
.LFB162:
	.cfi_startproc
	endbr64
	movl	$256, %eax
	movw	%ax, 136(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE162:
	.size	prim_compile_left_bracket, .-prim_compile_left_bracket
	.p2align 4
	.globl	prim_immediate_right_bracket
	.type	prim_immediate_right_bracket, @function
prim_immediate_right_bracket:
.LFB163:
	.cfi_startproc
	endbr64
	cmpb	$0, 137(%rdi)
	movl	$6, %eax
	je	.L250
	movb	$1, 136(%rdi)
	xorl	%eax, %eax
.L250:
	ret
	.cfi_endproc
.LFE163:
	.size	prim_immediate_right_bracket, .-prim_immediate_right_bracket
	.p2align 4
	.globl	prim_compile_bracket_tick
	.type	prim_compile_bracket_tick, @function
prim_compile_bracket_tick:
.LFB165:
	.cfi_startproc
	endbr64
	movl	$4, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE165:
	.size	prim_compile_bracket_tick, .-prim_compile_bracket_tick
	.p2align 4
	.globl	prim_compile_bracket_char
	.type	prim_compile_bracket_char, @function
prim_compile_bracket_char:
.LFB168:
	.cfi_startproc
	endbr64
	movl	$3, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE168:
	.size	prim_compile_bracket_char, .-prim_compile_bracket_char
	.p2align 4
	.globl	prim_body_not_equals
	.type	prim_body_not_equals, @function
prim_body_not_equals:
.LFB172:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	leaq	4(%rax), %rdx
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	andl	$1023, %edx
	orq	%rcx, %rdx
	cmpl	%eax, (%rdx)
	setne	%al
	movzbl	%al, %eax
	negl	%eax
	movl	%eax, (%rdx)
	ret
	.cfi_endproc
.LFE172:
	.size	prim_body_not_equals, .-prim_body_not_equals
	.p2align 4
	.globl	prim_compile_again
	.type	prim_compile_again, @function
prim_compile_again:
.LFB174:
	.cfi_startproc
	endbr64
	movl	$1, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE174:
	.size	prim_compile_again, .-prim_compile_again
	.p2align 4
	.globl	prim_body_false
	.type	prim_body_false, @function
prim_body_false:
.LFB175:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	$0, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE175:
	.size	prim_body_false, .-prim_body_false
	.p2align 4
	.globl	prim_body_nip
	.type	prim_body_nip, @function
prim_body_nip:
.LFB176:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rdx
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rdx, %rax
	movl	(%rax), %ecx
	movq	%rax, 8(%rdi)
	addq	$4, %rax
	andl	$1023, %eax
	orq	%rdx, %rax
	movl	%ecx, (%rax)
	ret
	.cfi_endproc
.LFE176:
	.size	prim_body_nip, .-prim_body_nip
	.p2align 4
	.globl	prim_immediate_s_backslash_quote
	.type	prim_immediate_s_backslash_quote, @function
prim_immediate_s_backslash_quote:
.LFB177:
	.cfi_startproc
	endbr64
	movl	$28, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE177:
	.size	prim_immediate_s_backslash_quote, .-prim_immediate_s_backslash_quote
	.p2align 4
	.globl	prim_body_true
	.type	prim_body_true, @function
prim_body_true:
.LFB179:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	$-1, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE179:
	.size	prim_body_true, .-prim_body_true
	.p2align 4
	.globl	prim_body_tuck
	.type	prim_body_tuck, @function
prim_body_tuck:
.LFB180:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	leaq	4(%rax), %rcx
	leaq	8(%rax), %rdx
	subq	$4, %rax
	andl	$1023, %ecx
	andl	$1023, %edx
	orq	%rsi, %rcx
	orq	%rsi, %rdx
	movl	(%rcx), %r8d
	movl	(%rdx), %r9d
	movl	%r9d, (%rcx)
	movl	%r8d, (%rdx)
	movl	%r8d, 4(%rax)
	andl	$1023, %eax
	orq	%rsi, %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE180:
	.size	prim_body_tuck, .-prim_body_tuck
	.p2align 4
	.globl	prim_body_unused
	.type	prim_body_unused, @function
prim_body_unused:
.LFB181:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	72(%rdi), %edx
	subl	76(%rdi), %edx
	movl	%edx, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE181:
	.size	prim_body_unused, .-prim_body_unused
	.p2align 4
	.globl	prim_body_within
	.type	prim_body_within, @function
prim_body_within:
.LFB182:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	%rdi, %rsi
	movq	(%rdi), %rdi
	leaq	8(%rax), %rdx
	leaq	12(%rax), %rcx
	addq	$4, %rax
	andl	$1023, %ecx
	andl	$1023, %eax
	andl	$1023, %edx
	orq	%rdi, %rcx
	orq	%rdi, %rax
	orq	%rdi, %rdx
	movl	(%rcx), %r8d
	cmpl	%r8d, (%rax)
	setge	%dil
	xorl	%eax, %eax
	cmpl	%r8d, (%rdx)
	setle	%al
	andl	%edi, %eax
	negl	%eax
	movl	%eax, (%rcx)
	movq	%rdx, 8(%rsi)
	ret
	.cfi_endproc
.LFE182:
	.size	prim_body_within, .-prim_body_within
	.p2align 4
	.globl	prim_immediate_words
	.type	prim_immediate_words, @function
prim_immediate_words:
.LFB186:
	.cfi_startproc
	endbr64
	movl	$37, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE186:
	.size	prim_immediate_words, .-prim_immediate_words
	.p2align 4
	.globl	prim_immediate_wordsize
	.type	prim_immediate_wordsize, @function
prim_immediate_wordsize:
.LFB188:
	.cfi_startproc
	endbr64
	movl	$38, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE188:
	.size	prim_immediate_wordsize, .-prim_immediate_wordsize
	.p2align 4
	.globl	prim_body_bye
	.type	prim_body_bye, @function
prim_body_bye:
.LFB190:
	.cfi_startproc
	endbr64
	movb	$1, 105(%rdi)
	movb	$0, 104(%rdi)
	ret
	.cfi_endproc
.LFE190:
	.size	prim_body_bye, .-prim_body_bye
	.p2align 4
	.globl	prim_body_reset
	.type	prim_body_reset, @function
prim_body_reset:
.LFB191:
	.cfi_startproc
	endbr64
	movl	16(%rdi), %eax
	leal	-4(,%rax,4), %eax
	addq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE191:
	.size	prim_body_reset, .-prim_body_reset
	.p2align 4
	.globl	prim_body_walign
	.type	prim_body_walign, @function
prim_body_walign:
.LFB192:
	.cfi_startproc
	endbr64
	movl	76(%rdi), %eax
	addl	$1, %eax
	andl	84(%rdi), %eax
	andl	$-2, %eax
	movl	%eax, 76(%rdi)
	ret
	.cfi_endproc
.LFE192:
	.size	prim_body_walign, .-prim_body_walign
	.p2align 4
	.globl	prim_body_waligned
	.type	prim_body_waligned, @function
prim_body_waligned:
.LFB193:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %ecx
	leal	1(%rcx), %edx
	andl	84(%rdi), %edx
	andl	$-2, %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE193:
	.size	prim_body_waligned, .-prim_body_waligned
	.p2align 4
	.globl	prim_body_printable
	.type	prim_body_printable, @function
prim_body_printable:
.LFB194:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	8(%rdi), %rax
	movq	184(%rdi), %rdx
	leaq	4(%rax), %rbx
	xorl	%eax, %eax
	andl	$1023, %ebx
	orq	(%rdi), %rbx
	testq	%rdx, %rdx
	je	.L271
	movl	(%rbx), %edi
	call	*%rdx
.L271:
	movl	%eax, (%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE194:
	.size	prim_body_printable, .-prim_body_printable
	.p2align 4
	.globl	prim_body_erase
	.type	prim_body_erase, @function
prim_body_erase:
.LFB195:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	(%rdi), %rsi
	movq	%rdi, %rdx
	leaq	4(%rax), %rcx
	addq	$8, %rax
	andl	$1023, %ecx
	andl	$1023, %eax
	orq	%rsi, %rcx
	orq	%rsi, %rax
	movl	(%rcx), %r8d
	testl	%r8d, %r8d
	je	.L277
	movl	72(%rdi), %ecx
	cmpl	%ecx, %r8d
	cmova	%ecx, %r8d
	testl	%r8d, %r8d
	je	.L277
	movl	(%rax), %eax
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L278:
	andl	80(%rdx), %eax
	movq	64(%rdx), %rdi
	addl	$1, %ecx
	movl	%eax, %esi
	addl	$1, %eax
	movb	$0, (%rdi,%rsi)
	cmpl	%ecx, %r8d
	jne	.L278
	movq	8(%rdx), %rax
	addq	$8, %rax
	andl	$1023, %eax
	orq	(%rdx), %rax
.L277:
	movq	%rax, 8(%rdx)
	ret
	.cfi_endproc
.LFE195:
	.size	prim_body_erase, .-prim_body_erase
	.p2align 4
	.globl	prim_body_cxt
	.type	prim_body_cxt, @function
prim_body_cxt:
.LFB196:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %ecx
	movl	%ecx, %esi
	movzbl	%cl, %edx
	orl	$-256, %esi
	andl	$128, %ecx
	cmovne	%esi, %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE196:
	.size	prim_body_cxt, .-prim_body_cxt
	.p2align 4
	.globl	prim_body_wxt
	.type	prim_body_wxt, @function
prim_body_wxt:
.LFB197:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %ecx
	movl	%ecx, %esi
	movzwl	%cx, %edx
	orl	$-65536, %esi
	andb	$-128, %ch
	cmovne	%esi, %edx
	movl	%edx, (%rax)
	ret
	.cfi_endproc
.LFE197:
	.size	prim_body_wxt, .-prim_body_wxt
	.p2align 4
	.globl	prim_immediate_primitives
	.type	prim_immediate_primitives, @function
prim_immediate_primitives:
.LFB198:
	.cfi_startproc
	endbr64
	movl	$25, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE198:
	.size	prim_immediate_primitives, .-prim_immediate_primitives
	.p2align 4
	.globl	prim_immediate_secondaries
	.type	prim_immediate_secondaries, @function
prim_immediate_secondaries:
.LFB200:
	.cfi_startproc
	endbr64
	movl	$29, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE200:
	.size	prim_immediate_secondaries, .-prim_immediate_secondaries
	.p2align 4
	.globl	prim_immediate_undefined
	.type	prim_immediate_undefined, @function
prim_immediate_undefined:
.LFB202:
	.cfi_startproc
	endbr64
	movl	$33, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE202:
	.size	prim_immediate_undefined, .-prim_immediate_undefined
	.p2align 4
	.globl	prim_body_dot
	.type	prim_body_dot, @function
prim_body_dot:
.LFB65:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$40, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	cmpq	$0, 152(%rdi)
	movq	%rax, 8(%rdi)
	je	.L295
	movq	%rdi, %rbx
	leaq	12(%rsp), %rbp
	movl	(%rax), %edi
	movq	%rbp, %rsi
	call	text_int32@PLT
	movq	%rbp, %rdi
	call	*152(%rbx)
	leaq	.LC1(%rip), %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L295
	xorl	%eax, %eax
	call	*%rdx
.L295:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L303
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L303:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE65:
	.size	prim_body_dot, .-prim_body_dot
	.p2align 4
	.globl	prim_body_question
	.type	prim_body_question, @function
prim_body_question:
.LFB184:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$40, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	cmpq	$0, 152(%rdi)
	movq	%rax, 8(%rdi)
	je	.L304
	movq	64(%rdi), %rdx
	movl	(%rax), %eax
	movq	%rdi, %rbx
	leaq	12(%rsp), %rbp
	andl	88(%rdi), %eax
	movq	%rbp, %rsi
	movl	(%rdx,%rax), %edi
	call	text_int32@PLT
	movq	%rbp, %rdi
	call	*152(%rbx)
	leaq	.LC1(%rip), %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L304
	xorl	%eax, %eax
	call	*%rdx
.L304:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L312
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L312:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE184:
	.size	prim_body_question, .-prim_body_question
	.p2align 4
	.globl	prim_body_u_dot
	.type	prim_body_u_dot, @function
prim_body_u_dot:
.LFB66:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$40, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	cmpq	$0, 152(%rdi)
	movq	%rax, 8(%rdi)
	je	.L313
	movq	%rdi, %rbx
	leaq	13(%rsp), %rbp
	movl	(%rax), %edi
	movq	%rbp, %rsi
	call	text_uint32@PLT
	movq	%rbp, %rdi
	call	*152(%rbx)
	leaq	.LC1(%rip), %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L313
	xorl	%eax, %eax
	call	*%rdx
.L313:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L321
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L321:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE66:
	.size	prim_body_u_dot, .-prim_body_u_dot
	.p2align 4
	.globl	prim_body_x_dot
	.type	prim_body_x_dot, @function
prim_body_x_dot:
.LFB67:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$40, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	cmpq	$0, 152(%rdi)
	movq	%rax, 8(%rdi)
	je	.L322
	movq	%rdi, %rbx
	leaq	15(%rsp), %rbp
	movl	(%rax), %edi
	movq	%rbp, %rsi
	call	text_hex32@PLT
	movq	%rbp, %rdi
	call	*152(%rbx)
	leaq	.LC1(%rip), %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L322
	xorl	%eax, %eax
	call	*%rdx
.L322:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L330
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L330:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE67:
	.size	prim_body_x_dot, .-prim_body_x_dot
	.p2align 4
	.globl	prim_body_number_to
	.type	prim_body_number_to, @function
prim_body_number_to:
.LFB81:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$32, %rsp
	.cfi_def_cfa_offset 64
	movq	(%rdi), %rcx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	movq	8(%rdi), %rax
	leaq	12(%rsp), %r12
	movq	%r12, %rsi
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %eax
	andl	$1023, %edx
	orq	%rcx, %rax
	orq	%rcx, %rdx
	movl	(%rax), %edi
	movl	(%rdx), %ebx
	call	text_int32@PLT
	movq	%r12, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	testq	%rax, %rax
	je	.L332
	movl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	12(%rsp), %edi
	andl	%ebx, %eax
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$1, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	13(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$2, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	14(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$3, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	15(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$4, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	16(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$5, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	17(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$6, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	18(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$7, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	19(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$8, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	20(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$9, %edx
	je	.L332
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	21(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$11, %edx
	jne	.L332
	movq	64(%rbp), %rcx
	movzbl	22(%rsp), %esi
	andl	80(%rbp), %eax
	movb	%sil, (%rcx,%rax)
.L332:
	movq	8(%rbp), %rax
	movq	0(%rbp), %rsi
	leaq	8(%rax), %rcx
	addq	$4, %rax
	andl	$1023, %ecx
	andl	$1023, %eax
	orq	%rsi, %rcx
	orq	%rsi, %rax
	movl	%edx, (%rcx)
	movq	%rax, 8(%rbp)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L339
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L339:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE81:
	.size	prim_body_number_to, .-prim_body_number_to
	.p2align 4
	.globl	prim_body_hex_to
	.type	prim_body_hex_to, @function
prim_body_hex_to:
.LFB82:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$32, %rsp
	.cfi_def_cfa_offset 64
	movq	(%rdi), %rcx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	movq	8(%rdi), %rax
	leaq	15(%rsp), %r12
	movq	%r12, %rsi
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %eax
	andl	$1023, %edx
	orq	%rcx, %rax
	orq	%rcx, %rdx
	movl	(%rax), %edi
	movl	(%rdx), %ebx
	call	text_hex32@PLT
	movq	%r12, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	testq	%rax, %rax
	je	.L341
	movl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	15(%rsp), %edi
	andl	%ebx, %eax
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$1, %edx
	je	.L341
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	16(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$2, %edx
	je	.L341
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	17(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$3, %edx
	je	.L341
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	18(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$4, %edx
	je	.L341
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	19(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$5, %edx
	je	.L341
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	20(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$6, %edx
	je	.L341
	andl	80(%rbp), %eax
	movq	64(%rbp), %rsi
	movzbl	21(%rsp), %edi
	movl	%eax, %ecx
	addl	$1, %eax
	movb	%dil, (%rsi,%rcx)
	cmpl	$8, %edx
	jne	.L341
	movq	64(%rbp), %rcx
	movzbl	22(%rsp), %esi
	andl	80(%rbp), %eax
	movb	%sil, (%rcx,%rax)
.L341:
	movq	8(%rbp), %rax
	movq	0(%rbp), %rsi
	leaq	8(%rax), %rcx
	addq	$4, %rax
	andl	$1023, %ecx
	andl	$1023, %eax
	orq	%rsi, %rcx
	orq	%rsi, %rax
	movl	%edx, (%rcx)
	movq	%rax, 8(%rbp)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L348
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L348:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE82:
	.size	prim_body_hex_to, .-prim_body_hex_to
	.p2align 4
	.globl	prim_body_dot_r
	.type	prim_body_dot_r, @function
prim_body_dot_r:
.LFB169:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %rdx
	movq	(%rdi), %rcx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rdx), %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	cmpq	$0, 152(%rdi)
	je	.L350
	addq	$4, %rdx
	movl	(%rax), %edi
	leaq	12(%rsp), %r14
	andl	$1023, %edx
	movq	%r14, %rsi
	orq	%rcx, %rdx
	movl	(%rdx), %ebp
	call	text_int32@PLT
	movq	%r14, %rdi
	call	strlen@PLT
	movl	%ebp, %edx
	cmpq	%rax, %rdx
	jnb	.L351
.L354:
	movq	%r14, %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L353
	xorl	%eax, %eax
	call	*%rdx
.L353:
	movq	8(%rbx), %rax
	addq	$8, %rax
	andl	$1023, %eax
	orq	(%rbx), %rax
.L350:
	movq	%rax, 8(%rbx)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L359
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L351:
	.cfi_restore_state
	movl	%ebp, %r12d
	movl	$1500, %edx
	subl	%eax, %r12d
	cmpl	%edx, %r12d
	cmova	%edx, %r12d
	cmpl	%ebp, %eax
	je	.L354
	xorl	%ebp, %ebp
	leaq	.LC1(%rip), %r13
	.p2align 4,,10
	.p2align 3
.L355:
	addl	$1, %ebp
	movq	%r13, %rdi
	call	*152(%rbx)
	cmpl	%r12d, %ebp
	jb	.L355
	jmp	.L354
.L359:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE169:
	.size	prim_body_dot_r, .-prim_body_dot_r
	.p2align 4
	.globl	prim_body_u_dot_r
	.type	prim_body_u_dot_r, @function
prim_body_u_dot_r:
.LFB170:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %rdx
	movq	(%rdi), %rcx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rdx), %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	cmpq	$0, 152(%rdi)
	je	.L361
	addq	$4, %rdx
	movl	(%rax), %edi
	leaq	13(%rsp), %r14
	andl	$1023, %edx
	movq	%r14, %rsi
	orq	%rcx, %rdx
	movl	(%rdx), %ebp
	call	text_uint32@PLT
	movq	%r14, %rdi
	call	strlen@PLT
	movl	%ebp, %edx
	cmpq	%rax, %rdx
	jnb	.L362
.L365:
	movq	%r14, %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L364
	xorl	%eax, %eax
	call	*%rdx
.L364:
	movq	8(%rbx), %rax
	addq	$8, %rax
	andl	$1023, %eax
	orq	(%rbx), %rax
.L361:
	movq	%rax, 8(%rbx)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L370
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L362:
	.cfi_restore_state
	movl	%ebp, %r12d
	movl	$1500, %edx
	subl	%eax, %r12d
	cmpl	%edx, %r12d
	cmova	%edx, %r12d
	cmpl	%ebp, %eax
	je	.L365
	xorl	%ebp, %ebp
	leaq	.LC1(%rip), %r13
	.p2align 4,,10
	.p2align 3
.L366:
	addl	$1, %ebp
	movq	%r13, %rdi
	call	*152(%rbx)
	cmpl	%r12d, %ebp
	jb	.L366
	jmp	.L365
.L370:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE170:
	.size	prim_body_u_dot_r, .-prim_body_u_dot_r
	.p2align 4
	.globl	prim_body_x_dot_r
	.type	prim_body_x_dot_r, @function
prim_body_x_dot_r:
.LFB171:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %rdx
	movq	(%rdi), %rcx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rdx), %rax
	andl	$1023, %eax
	orq	%rcx, %rax
	cmpq	$0, 152(%rdi)
	je	.L372
	addq	$4, %rdx
	movl	(%rax), %edi
	leaq	15(%rsp), %r14
	andl	$1023, %edx
	movq	%r14, %rsi
	orq	%rcx, %rdx
	movl	(%rdx), %ebp
	call	text_hex32@PLT
	movq	%r14, %rdi
	call	strlen@PLT
	movl	%ebp, %edx
	cmpq	%rax, %rdx
	jnb	.L373
.L376:
	movq	%r14, %rdi
	call	*152(%rbx)
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L375
	xorl	%eax, %eax
	call	*%rdx
.L375:
	movq	8(%rbx), %rax
	addq	$8, %rax
	andl	$1023, %eax
	orq	(%rbx), %rax
.L372:
	movq	%rax, 8(%rbx)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L381
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L373:
	.cfi_restore_state
	movl	%ebp, %r12d
	movl	$1500, %edx
	subl	%eax, %r12d
	cmpl	%edx, %r12d
	cmova	%edx, %r12d
	cmpl	%ebp, %eax
	je	.L376
	xorl	%ebp, %ebp
	leaq	.LC1(%rip), %r13
	.p2align 4,,10
	.p2align 3
.L377:
	addl	$1, %ebp
	movq	%r13, %rdi
	call	*152(%rbx)
	cmpl	%r12d, %ebp
	jb	.L377
	jmp	.L376
.L381:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE171:
	.size	prim_body_x_dot_r, .-prim_body_x_dot_r
	.p2align 4
	.globl	prim_body_depth
	.type	prim_body_depth, @function
prim_body_depth:
.LFB105:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rdi), %rbp
	call	forth_stack_count@PLT
	movl	%eax, 0(%rbp)
	movq	8(%rbx), %rax
	subq	$4, %rax
	andl	$1023, %eax
	orq	(%rbx), %rax
	movq	%rax, 8(%rbx)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE105:
	.size	prim_body_depth, .-prim_body_depth
	.section	.rodata.str1.1
.LC3:
	.string	": "
.LC4:
	.string	"  "
.LC5:
	.string	"   "
.LC6:
	.string	"\nOutput truncated"
	.text
	.p2align 4
	.globl	prim_body_dump
	.type	prim_body_dump, @function
prim_body_dump:
.LFB185:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpq	$0, 152(%rdi)
	je	.L385
	movq	8(%rdi), %rax
	movq	(%rdi), %rcx
	leaq	4(%rax), %rdx
	addq	$8, %rax
	andl	$1023, %edx
	andl	$1023, %eax
	orq	%rcx, %rdx
	orq	%rcx, %rax
	movl	(%rdx), %esi
	movl	(%rax), %ebp
	movl	%esi, 8(%rsp)
	testl	%esi, %esi
	je	.L387
	xorl	%r12d, %r12d
	xorl	%r15d, %r15d
	leaq	24(%rsp), %r14
	movl	$1, %edx
	movl	$0, 12(%rsp)
	jmp	.L386
	.p2align 4,,10
	.p2align 3
.L389:
	movl	8(%rsp), %eax
	movq	152(%rbx), %rdx
	leal	-1(%rax), %ecx
	cmpl	%r12d, %ecx
	je	.L454
	leaq	.LC1(%rip), %rdi
	addl	$1, %ebp
	addl	$1, %r12d
	call	*%rdx
	xorl	%edx, %edx
	cmpl	%r12d, 8(%rsp)
	je	.L387
.L386:
	andl	80(%rbx), %ebp
	testb	%dl, %dl
	je	.L388
	leaq	.LC0(%rip), %rdi
	call	*152(%rbx)
	movl	$6, %edx
	movq	%r14, %rsi
	movl	%ebp, %edi
	call	text_hex32_padded@PLT
	movq	%r14, %rdi
	call	*152(%rbx)
	leaq	.LC3(%rip), %rdi
	call	*152(%rbx)
.L388:
	movq	64(%rbx), %rcx
	movl	%ebp, %edx
	movq	%r14, %rsi
	movzbl	(%rcx,%rdx), %edi
	movl	$2, %edx
	movl	%edi, %r13d
	call	text_hex32_padded@PLT
	movq	%r14, %rdi
	call	*152(%rbx)
	movl	%r15d, %edx
	addl	$1, %r15d
	movb	%r13b, 31(%rsp,%rdx)
	cmpl	$8, %r15d
	jne	.L389
	cmpb	$31, 31(%rsp)
	movb	$0, 39(%rsp)
	jg	.L390
	movb	$46, 31(%rsp)
.L390:
	cmpb	$31, 32(%rsp)
	jg	.L411
	movb	$46, 32(%rsp)
	movq	152(%rbx), %rdx
.L412:
	cmpb	$31, 33(%rsp)
	jg	.L397
	movb	$46, 33(%rsp)
.L397:
	cmpl	$3, %r15d
	je	.L395
.L410:
	cmpb	$31, 34(%rsp)
	jg	.L398
	movb	$46, 34(%rsp)
.L398:
	cmpl	$4, %r15d
	je	.L395
	cmpb	$31, 35(%rsp)
	jg	.L399
	movb	$46, 35(%rsp)
.L399:
	cmpl	$5, %r15d
	je	.L395
	cmpb	$31, 36(%rsp)
	jg	.L400
	movb	$46, 36(%rsp)
.L400:
	cmpl	$6, %r15d
	je	.L395
	cmpb	$31, 37(%rsp)
	jg	.L401
	movb	$46, 37(%rsp)
.L401:
	cmpl	$7, %r15d
	je	.L395
	cmpb	$31, 38(%rsp)
	jg	.L453
	movb	$46, 38(%rsp)
.L453:
	cmpl	$8, %r15d
	je	.L404
	cmpb	$31, 39(%rsp)
	jg	.L395
	movb	$46, 39(%rsp)
	.p2align 4,,10
	.p2align 3
.L395:
	movl	$8, %r13d
	subl	%r15d, %r13d
	xorl	%r15d, %r15d
	.p2align 4,,10
	.p2align 3
.L393:
	addl	$1, %r15d
	leaq	.LC5(%rip), %rdi
	call	*%rdx
	movq	152(%rbx), %rdx
	cmpl	%r13d, %r15d
	jb	.L393
.L404:
	leaq	.LC4(%rip), %rdi
	call	*%rdx
	leaq	31(%rsp), %rdi
	call	*152(%rbx)
	addl	$1, 12(%rsp)
	movl	12(%rsp), %eax
	cmpl	$20, %eax
	je	.L406
.L415:
	xorl	%r15d, %r15d
	movl	$1, %edx
	addl	$1, %ebp
	addl	$1, %r12d
	cmpl	%r12d, 8(%rsp)
	jne	.L386
.L387:
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L385
	xorl	%eax, %eax
	call	*%rdx
.L385:
	movq	8(%rbx), %rax
	addq	$8, %rax
	andl	$1023, %eax
	orq	(%rbx), %rax
	movq	%rax, 8(%rbx)
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L455
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L454:
	.cfi_restore_state
	movl	%r15d, %ecx
	movb	$0, 31(%rsp,%rcx)
	testl	%r15d, %r15d
	je	.L395
	cmpb	$31, 31(%rsp)
	jg	.L394
	movb	$46, 31(%rsp)
.L394:
	cmpl	$1, %r15d
	je	.L395
	cmpb	$31, 32(%rsp)
	jg	.L396
	movb	$46, 32(%rsp)
.L396:
	cmpl	$2, %r15d
	jne	.L412
	jmp	.L395
	.p2align 4,,10
	.p2align 3
.L406:
	movl	8(%rsp), %eax
	subl	$1, %eax
	cmpl	%r12d, %eax
	je	.L415
	leaq	.LC6(%rip), %rdi
	call	*152(%rbx)
	jmp	.L387
	.p2align 4,,10
	.p2align 3
.L411:
	cmpb	$31, 33(%rsp)
	jg	.L452
	movb	$46, 33(%rsp)
.L452:
	movq	152(%rbx), %rdx
	jmp	.L410
.L455:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE185:
	.size	prim_body_dump, .-prim_body_dump
	.p2align 4
	.globl	prim_body_spaces
	.type	prim_body_spaces, @function
prim_body_spaces:
.LFB146:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movq	8(%rdi), %rax
	addq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movl	(%rax), %r12d
	movq	%rax, 8(%rdi)
	testl	%r12d, %r12d
	jle	.L456
	movq	152(%rdi), %rax
	movq	%rdi, %rbp
	testq	%rax, %rax
	je	.L456
	movl	216(%rdi), %edx
	cmpl	%edx, %r12d
	cmovg	%edx, %r12d
	testl	%r12d, %r12d
	jle	.L460
	xorl	%ebx, %ebx
	leaq	.LC1(%rip), %r13
	jmp	.L461
	.p2align 4,,10
	.p2align 3
.L469:
	movq	152(%rbp), %rax
.L461:
	addl	$1, %ebx
	movq	%r13, %rdi
	call	*%rax
	cmpl	%ebx, %r12d
	jne	.L469
.L460:
	movq	192(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L456
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	*%rdx
	.p2align 4,,10
	.p2align 3
.L456:
	.cfi_restore_state
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE146:
	.size	prim_body_spaces, .-prim_body_spaces
	.section	.rodata.str1.1
.LC7:
	.string	"<"
.LC8:
	.string	"> "
	.text
	.p2align 4
	.globl	prim_body_dot_s
	.type	prim_body_dot_s, @function
prim_body_dot_s:
.LFB183:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$32, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpq	$0, 152(%rdi)
	je	.L470
	movq	%rdi, %rbp
	leaq	12(%rsp), %r13
	call	forth_stack_count@PLT
	leaq	.LC7(%rip), %rdi
	movl	%eax, %r12d
	call	*152(%rbp)
	movq	%r13, %rsi
	movl	%r12d, %edi
	call	text_int32@PLT
	movq	%r13, %rdi
	call	*152(%rbp)
	leaq	.LC8(%rip), %rdi
	call	*152(%rbp)
	movq	8(%rbp), %r14
	movslq	%r12d, %rax
	leaq	(%r14,%rax,4), %rbx
	testl	%r12d, %r12d
	jle	.L472
	leaq	.LC1(%rip), %r12
	.p2align 4,,10
	.p2align 3
.L473:
	movl	(%rbx), %edi
	movq	%r13, %rsi
	subq	$4, %rbx
	call	text_int32@PLT
	movq	%r13, %rdi
	call	*152(%rbp)
	movq	%r12, %rdi
	call	*152(%rbp)
	cmpq	%rbx, %r14
	jne	.L473
.L472:
	movq	192(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L470
	xorl	%eax, %eax
	call	*%rdx
.L470:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L481
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L481:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE183:
	.size	prim_body_dot_s, .-prim_body_dot_s
	.p2align 4
	.globl	prim_immediate_again
	.type	prim_immediate_again, @function
prim_immediate_again:
.LFB265:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE265:
	.size	prim_immediate_again, .-prim_immediate_again
	.p2align 4
	.globl	prim_compile_secondaries
	.type	prim_compile_secondaries, @function
prim_compile_secondaries:
.LFB225:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE225:
	.size	prim_compile_secondaries, .-prim_compile_secondaries
	.p2align 4
	.globl	prim_compile_undefined
	.type	prim_compile_undefined, @function
prim_compile_undefined:
.LFB227:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE227:
	.size	prim_compile_undefined, .-prim_compile_undefined
	.p2align 4
	.globl	prim_compile_colon
	.type	prim_compile_colon, @function
prim_compile_colon:
.LFB207:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE207:
	.size	prim_compile_colon, .-prim_compile_colon
	.p2align 4
	.globl	prim_immediate_begin
	.type	prim_immediate_begin, @function
prim_immediate_begin:
.LFB235:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE235:
	.size	prim_immediate_begin, .-prim_immediate_begin
	.p2align 4
	.globl	prim_compile_char
	.type	prim_compile_char, @function
prim_compile_char:
.LFB209:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE209:
	.size	prim_compile_char, .-prim_compile_char
	.p2align 4
	.globl	prim_compile_constant
	.type	prim_compile_constant, @function
prim_compile_constant:
.LFB211:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE211:
	.size	prim_compile_constant, .-prim_compile_constant
	.p2align 4
	.globl	prim_compile_create
	.type	prim_compile_create, @function
prim_compile_create:
.LFB213:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE213:
	.size	prim_compile_create, .-prim_compile_create
	.p2align 4
	.globl	prim_immediate_do
	.type	prim_immediate_do, @function
prim_immediate_do:
.LFB237:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE237:
	.size	prim_immediate_do, .-prim_immediate_do
	.p2align 4
	.globl	prim_immediate_else
	.type	prim_immediate_else, @function
prim_immediate_else:
.LFB239:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE239:
	.size	prim_immediate_else, .-prim_immediate_else
	.p2align 4
	.globl	prim_immediate_i
	.type	prim_immediate_i, @function
prim_immediate_i:
.LFB241:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE241:
	.size	prim_immediate_i, .-prim_immediate_i
	.p2align 4
	.globl	prim_immediate_if
	.type	prim_immediate_if, @function
prim_immediate_if:
.LFB243:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE243:
	.size	prim_immediate_if, .-prim_immediate_if
	.p2align 4
	.globl	prim_immediate_j
	.type	prim_immediate_j, @function
prim_immediate_j:
.LFB245:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE245:
	.size	prim_immediate_j, .-prim_immediate_j
	.p2align 4
	.globl	prim_immediate_literal
	.type	prim_immediate_literal, @function
prim_immediate_literal:
.LFB247:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE247:
	.size	prim_immediate_literal, .-prim_immediate_literal
	.p2align 4
	.globl	prim_immediate_loop
	.type	prim_immediate_loop, @function
prim_immediate_loop:
.LFB249:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE249:
	.size	prim_immediate_loop, .-prim_immediate_loop
	.p2align 4
	.globl	prim_immediate_repeat
	.type	prim_immediate_repeat, @function
prim_immediate_repeat:
.LFB251:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE251:
	.size	prim_immediate_repeat, .-prim_immediate_repeat
	.p2align 4
	.globl	prim_immediate_then
	.type	prim_immediate_then, @function
prim_immediate_then:
.LFB253:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE253:
	.size	prim_immediate_then, .-prim_immediate_then
	.p2align 4
	.globl	prim_immediate_until
	.type	prim_immediate_until, @function
prim_immediate_until:
.LFB255:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE255:
	.size	prim_immediate_until, .-prim_immediate_until
	.p2align 4
	.globl	prim_compile_variable
	.type	prim_compile_variable, @function
prim_compile_variable:
.LFB215:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE215:
	.size	prim_compile_variable, .-prim_compile_variable
	.p2align 4
	.globl	prim_immediate_while
	.type	prim_immediate_while, @function
prim_immediate_while:
.LFB257:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE257:
	.size	prim_immediate_while, .-prim_immediate_while
	.p2align 4
	.globl	prim_immediate_left_bracket
	.type	prim_immediate_left_bracket, @function
prim_immediate_left_bracket:
.LFB259:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE259:
	.size	prim_immediate_left_bracket, .-prim_immediate_left_bracket
	.p2align 4
	.globl	prim_compile_right_bracket
	.type	prim_compile_right_bracket, @function
prim_compile_right_bracket:
.LFB217:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE217:
	.size	prim_compile_right_bracket, .-prim_compile_right_bracket
	.p2align 4
	.globl	prim_immediate_bracket_tick
	.type	prim_immediate_bracket_tick, @function
prim_immediate_bracket_tick:
.LFB261:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE261:
	.size	prim_immediate_bracket_tick, .-prim_immediate_bracket_tick
	.p2align 4
	.globl	prim_immediate_bracket_char
	.type	prim_immediate_bracket_char, @function
prim_immediate_bracket_char:
.LFB263:
	.cfi_startproc
	endbr64
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE263:
	.size	prim_immediate_bracket_char, .-prim_immediate_bracket_char
	.p2align 4
	.globl	prim_compile_words
	.type	prim_compile_words, @function
prim_compile_words:
.LFB219:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE219:
	.size	prim_compile_words, .-prim_compile_words
	.p2align 4
	.globl	prim_compile_wordsize
	.type	prim_compile_wordsize, @function
prim_compile_wordsize:
.LFB221:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE221:
	.size	prim_compile_wordsize, .-prim_compile_wordsize
	.p2align 4
	.globl	prim_compile_primitives
	.type	prim_compile_primitives, @function
prim_compile_primitives:
.LFB223:
	.cfi_startproc
	endbr64
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE223:
	.size	prim_compile_primitives, .-prim_compile_primitives
	.p2align 4
	.globl	prim_compile_s_backslash_quote
	.type	prim_compile_s_backslash_quote, @function
prim_compile_s_backslash_quote:
.LFB269:
	.cfi_startproc
	endbr64
	movl	$28, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE269:
	.size	prim_compile_s_backslash_quote, .-prim_compile_s_backslash_quote
	.p2align 4
	.globl	prim_compile_paren
	.type	prim_compile_paren, @function
prim_compile_paren:
.LFB229:
	.cfi_startproc
	endbr64
	movl	$23, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE229:
	.size	prim_compile_paren, .-prim_compile_paren
	.p2align 4
	.globl	prim_compile_s_quote
	.type	prim_compile_s_quote, @function
prim_compile_s_quote:
.LFB267:
	.cfi_startproc
	endbr64
	movl	$27, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE267:
	.size	prim_compile_s_quote, .-prim_compile_s_quote
	.p2align 4
	.globl	prim_compile_backslash
	.type	prim_compile_backslash, @function
prim_compile_backslash:
.LFB231:
	.cfi_startproc
	endbr64
	movl	$8, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE231:
	.size	prim_compile_backslash, .-prim_compile_backslash
	.p2align 4
	.globl	prim_compile_dot_quote
	.type	prim_compile_dot_quote, @function
prim_compile_dot_quote:
.LFB233:
	.cfi_startproc
	endbr64
	movl	$12, 140(%rdi)
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE233:
	.size	prim_compile_dot_quote, .-prim_compile_dot_quote
	.p2align 4
	.globl	prim_hidden_do
	.type	prim_hidden_do, @function
prim_hidden_do:
.LFB37:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rdx
	movq	(%rdi), %rsi
	leaq	4(%rdx), %rcx
	addq	$8, %rdx
	andl	$1023, %ecx
	andl	$1023, %edx
	orq	%rsi, %rdx
	orq	%rsi, %rcx
	movd	(%rdx), %xmm2
	movd	(%rcx), %xmm0
	movq	%rdx, 8(%rdi)
	movq	32(%rdi), %rdx
	cmpq	24(%rdi), %rdx
	jnb	.L515
	movl	$4, 144(%rdi)
	movb	$0, 104(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L515:
	movq	52(%rdi), %rcx
	movb	$2, 12(%rdx)
	punpckldq	%xmm2, %xmm0
	subq	$16, %rdx
	movq	%rcx, 16(%rdx)
	movd	44(%rdi), %xmm1
	movd	48(%rdi), %xmm3
	movl	108(%rdi), %ecx
	punpckldq	%xmm3, %xmm1
	movl	%ecx, 24(%rdx)
	punpcklqdq	%xmm1, %xmm0
	movq	%rdx, 32(%rdi)
	movups	%xmm0, 44(%rdi)
	ret
	.cfi_endproc
.LFE37:
	.size	prim_hidden_do, .-prim_hidden_do
	.p2align 4
	.globl	prim_hidden_done
	.type	prim_hidden_done, @function
prim_hidden_done:
.LFB38:
	.cfi_startproc
	endbr64
	movq	32(%rdi), %rax
	jmp	.L520
	.p2align 4,,10
	.p2align 3
.L518:
	testb	%dl, %dl
	je	.L522
.L520:
	movq	%rax, %rcx
	movzbl	28(%rax), %edx
	addq	$16, %rax
	cmpb	$1, %dl
	jne	.L518
	movq	%rax, 32(%rdi)
	movl	16(%rcx), %eax
	addq	120(%rdi), %rax
	movq	%rax, 96(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L522:
	movq	%rax, 32(%rdi)
	movb	$0, 104(%rdi)
	ret
	.cfi_endproc
.LFE38:
	.size	prim_hidden_done, .-prim_hidden_done
	.section	.rodata.str1.1
.LC9:
	.string	"prim_hidden_dot_quote"
.LC10:
	.string	"engine->address: %p\n"
.LC11:
	.string	"length address: %p\n"
.LC12:
	.string	"quote_length: %u\n"
.LC13:
	.string	"text: %p\n"
.LC14:
	.string	"character: %c (%d)\n"
.LC15:
	.string	"printed: %s\n"
.LC16:
	.string	"text after printing: %p\n"
.LC17:
	.string	"ptr_len: %u\n"
.LC18:
	.string	"new text: %p\n"
.LC19:
	.string	"new engine->address: %p\n"
	.text
	.p2align 4
	.globl	prim_hidden_dot_quote
	.type	prim_hidden_dot_quote, @function
prim_hidden_dot_quote:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	.LC9(%rip), %rsi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	96(%rdi), %r12
	movl	$14, %edi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movl	8(%r12), %r15d
	leaq	12(%r12), %rbp
	call	log_push@PLT
	movq	96(%rbx), %rsi
	leaq	.LC10(%rip), %rdi
	xorl	%eax, %eax
	call	log_text@PLT
	movq	96(%rbx), %rax
	leaq	.LC11(%rip), %rdi
	leaq	8(%rax), %rsi
	xorl	%eax, %eax
	call	log_text@PLT
	movl	%r15d, %esi
	leaq	.LC12(%rip), %rdi
	xorl	%eax, %eax
	call	log_text@PLT
	movq	%rbp, %rsi
	leaq	.LC13(%rip), %rdi
	xorl	%eax, %eax
	call	log_text@PLT
	movb	$0, 23(%rsp)
	testl	%r15d, %r15d
	je	.L524
	movl	%r15d, %eax
	movq	%rbp, %r15
	movq	%rax, 8(%rsp)
	leaq	12(%r12,%rax), %r13
	leaq	.LC14(%rip), %r12
	.p2align 4,,10
	.p2align 3
.L526:
	movsbl	(%r15), %esi
	xorl	%eax, %eax
	movq	%r12, %rdi
	movl	%esi, %edx
	call	log_text@PLT
	movq	152(%rbx), %rax
	testq	%rax, %rax
	je	.L525
	movzbl	(%r15), %edx
	leaq	22(%rsp), %r14
	movq	%r14, %rdi
	movb	%dl, 22(%rsp)
	call	*%rax
	movq	%r14, %rsi
	leaq	.LC15(%rip), %rdi
	xorl	%eax, %eax
	call	log_text@PLT
.L525:
	addq	$1, %r15
	cmpq	%r13, %r15
	jne	.L526
	movq	8(%rsp), %rax
	addq	%rax, %rbp
.L524:
	movq	192(%rbx), %rdx
	testq	%rdx, %rdx
	je	.L527
	xorl	%eax, %eax
	call	*%rdx
.L527:
	movq	%rbp, %rsi
	xorl	%eax, %eax
	leaq	.LC16(%rip), %rdi
	call	log_text@PLT
	movq	%rbp, %rax
	movl	$8, %esi
	leaq	.LC17(%rip), %rdi
	negq	%rax
	andl	$7, %eax
	addq	%rax, %rbp
	leaq	-8(%rbp), %rax
	movq	%rax, 96(%rbx)
	xorl	%eax, %eax
	call	log_text@PLT
	xorl	%eax, %eax
	movq	%rbp, %rsi
	leaq	.LC18(%rip), %rdi
	call	log_text@PLT
	movq	96(%rbx), %rsi
	xorl	%eax, %eax
	leaq	.LC19(%rip), %rdi
	call	log_text@PLT
	xorl	%eax, %eax
	call	log_pop@PLT
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L540
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L540:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE39:
	.size	prim_hidden_dot_quote, .-prim_hidden_dot_quote
	.p2align 4
	.globl	prim_hidden_i
	.type	prim_hidden_i, @function
prim_hidden_i:
.LFB40:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	44(%rdi), %edx
	subq	$4, %rax
	movl	%edx, 4(%rax)
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE40:
	.size	prim_hidden_i, .-prim_hidden_i
	.p2align 4
	.globl	prim_hidden_if
	.type	prim_hidden_if, @function
prim_hidden_if:
.LFB41:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movq	96(%rdi), %rcx
	addq	$4, %rax
	leaq	4(%rcx), %rdx
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L544
	movslq	8(%rcx), %rdx
	addq	%rcx, %rdx
.L544:
	movq	%rdx, 96(%rdi)
	ret
	.cfi_endproc
.LFE41:
	.size	prim_hidden_if, .-prim_hidden_if
	.p2align 4
	.globl	prim_hidden_j
	.type	prim_hidden_j, @function
prim_hidden_j:
.LFB42:
	.cfi_startproc
	endbr64
	movq	8(%rdi), %rax
	movl	52(%rdi), %edx
	subq	$4, %rax
	movl	%edx, 4(%rax)
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE42:
	.size	prim_hidden_j, .-prim_hidden_j
	.p2align 4
	.globl	prim_hidden_jump
	.type	prim_hidden_jump, @function
prim_hidden_jump:
.LFB43:
	.cfi_startproc
	endbr64
	movq	96(%rdi), %rax
	movslq	8(%rax), %rdx
	addq	%rdx, %rax
	movq	%rax, 96(%rdi)
	ret
	.cfi_endproc
.LFE43:
	.size	prim_hidden_jump, .-prim_hidden_jump
	.p2align 4
	.globl	prim_hidden_loop
	.type	prim_hidden_loop, @function
prim_hidden_loop:
.LFB44:
	.cfi_startproc
	endbr64
	movl	44(%rdi), %eax
	movq	96(%rdi), %rdx
	addl	$1, %eax
	movl	%eax, 44(%rdi)
	cmpl	48(%rdi), %eax
	je	.L548
	movslq	8(%rdx), %rax
	addq	%rax, %rdx
	movq	%rdx, 96(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L548:
	movq	32(%rdi), %rax
	movd	52(%rdi), %xmm0
	addq	$4, %rdx
	movd	56(%rdi), %xmm3
	movd	16(%rax), %xmm1
	movd	20(%rax), %xmm2
	leaq	16(%rax), %rcx
	movq	%rdx, 96(%rdi)
	punpckldq	%xmm3, %xmm0
	movq	%rcx, 32(%rdi)
	punpckldq	%xmm2, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, 44(%rdi)
	ret
	.cfi_endproc
.LFE44:
	.size	prim_hidden_loop, .-prim_hidden_loop
	.p2align 4
	.globl	prim_hidden_push
	.type	prim_hidden_push, @function
prim_hidden_push:
.LFB45:
	.cfi_startproc
	endbr64
	movq	96(%rdi), %rax
	movl	8(%rax), %edx
	addq	$4, %rax
	movq	%rax, 96(%rdi)
	movq	8(%rdi), %rax
	movl	%edx, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	(%rdi), %rax
	movq	%rax, 8(%rdi)
	ret
	.cfi_endproc
.LFE45:
	.size	prim_hidden_push, .-prim_hidden_push
	.section	.rodata.str1.1
.LC20:
	.string	"prim_hidden_s_quote"
	.text
	.p2align 4
	.globl	prim_hidden_s_quote
	.type	prim_hidden_s_quote, @function
prim_hidden_s_quote:
.LFB46:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	.LC20(%rip), %rsi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	96(%rdi), %rbp
	movl	76(%rdi), %eax
	movl	$15, %edi
	movl	8(%rbp), %r13d
	movl	%eax, 4(%rsp)
	leaq	12(%rbp), %rbx
	call	log_push@PLT
	movq	96(%r14), %rsi
	xorl	%eax, %eax
	leaq	.LC10(%rip), %rdi
	call	log_text@PLT
	movq	96(%r14), %rax
	leaq	.LC11(%rip), %rdi
	leaq	8(%rax), %rsi
	xorl	%eax, %eax
	call	log_text@PLT
	xorl	%eax, %eax
	movl	%r13d, %esi
	leaq	.LC12(%rip), %rdi
	call	log_text@PLT
	xorl	%eax, %eax
	movq	%rbx, %rsi
	leaq	.LC13(%rip), %rdi
	call	log_text@PLT
	testl	%r13d, %r13d
	je	.L552
	movl	%r13d, %eax
	movq	%rbx, %r15
	movq	%rax, 8(%rsp)
	leaq	12(%rbp,%rax), %r12
	leaq	.LC14(%rip), %rbp
	.p2align 4,,10
	.p2align 3
.L553:
	movsbl	(%r15), %esi
	xorl	%eax, %eax
	movq	%rbp, %rdi
	addq	$1, %r15
	movl	%esi, %edx
	call	log_text@PLT
	movl	76(%r14), %eax
	movzbl	-1(%r15), %esi
	movq	64(%r14), %rdx
	movb	%sil, (%rdx,%rax)
	movl	76(%r14), %eax
	addl	$1, %eax
	andl	80(%r14), %eax
	movl	%eax, 76(%r14)
	cmpq	%r12, %r15
	jne	.L553
	movq	8(%rsp), %rax
	addq	%rax, %rbx
.L552:
	movq	%rbx, %rsi
	leaq	.LC13(%rip), %rdi
	xorl	%eax, %eax
	call	log_text@PLT
	movq	%rbx, %rax
	movl	$8, %esi
	leaq	.LC17(%rip), %rdi
	negq	%rax
	andl	$7, %eax
	addq	%rax, %rbx
	leaq	-8(%rbx), %rax
	movq	%rax, 96(%r14)
	xorl	%eax, %eax
	call	log_text@PLT
	movq	%rbx, %rsi
	leaq	.LC18(%rip), %rdi
	xorl	%eax, %eax
	call	log_text@PLT
	movq	96(%r14), %rsi
	xorl	%eax, %eax
	leaq	.LC19(%rip), %rdi
	call	log_text@PLT
	movq	8(%r14), %rax
	movl	4(%rsp), %ecx
	movq	(%r14), %rdx
	movl	%ecx, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	%rdx, %rax
	movl	%r13d, (%rax)
	subq	$4, %rax
	andl	$1023, %eax
	orq	%rdx, %rax
	movq	%rax, 8(%r14)
	addq	$24, %rsp
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	log_pop@PLT
	.cfi_endproc
.LFE46:
	.size	prim_hidden_s_quote, .-prim_hidden_s_quote
	.p2align 4
	.globl	prim_hidden_secondary
	.type	prim_hidden_secondary, @function
prim_hidden_secondary:
.LFB47:
	.cfi_startproc
	endbr64
	movq	96(%rdi), %rax
	movl	8(%rax), %edx
	addq	$4, %rax
	movq	%rax, 96(%rdi)
	leaq	(%rdx,%rdx,4), %rcx
	movq	112(%rdi), %rdx
	leaq	(%rdx,%rcx,8), %rcx
	cmpb	$4, 34(%rcx)
	je	.L563
	movq	32(%rdi), %rdx
	cmpq	24(%rdi), %rdx
	jnb	.L562
	movl	$4, 144(%rdi)
	movb	$0, 104(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L562:
	movl	108(%rdi), %esi
	subq	120(%rdi), %rax
	subq	$16, %rdx
	addl	$1, %esi
	movl	%esi, 108(%rdi)
	movl	%eax, 16(%rdx)
	movb	$1, 28(%rdx)
	movq	(%rcx), %rax
	movl	%esi, 24(%rdx)
	subq	$8, %rax
	movq	%rdx, 32(%rdi)
	movq	%rax, 96(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L563:
	movl	$5, 144(%rdi)
	movq	24(%rcx), %rax
	movb	$0, 104(%rdi)
	movq	%rax, 128(%rdi)
	ret
	.cfi_endproc
.LFE47:
	.size	prim_hidden_secondary, .-prim_hidden_secondary
	.globl	forth_primitives_len
	.section	.rodata
	.align 4
	.type	forth_primitives_len, @object
	.size	forth_primitives_len, 4
forth_primitives_len:
	.long	127
	.globl	forth_primitives
	.section	.rodata.str1.1
.LC21:
	.string	"!"
.LC22:
	.string	"C!"
.LC23:
	.string	"W!"
.LC24:
	.string	"'"
.LC25:
	.string	"("
.LC26:
	.string	"*"
.LC27:
	.string	"*/"
.LC28:
	.string	"*/MOD"
.LC29:
	.string	"+"
.LC30:
	.string	","
.LC31:
	.string	"C,"
.LC32:
	.string	"W,"
.LC33:
	.string	"-"
.LC34:
	.string	"\\"
.LC35:
	.string	"."
.LC36:
	.string	"U."
.LC37:
	.string	"X."
.LC38:
	.string	".\""
.LC39:
	.string	"/"
.LC40:
	.string	"/MOD"
.LC41:
	.string	":"
.LC42:
	.string	";"
.LC43:
	.string	"="
.LC44:
	.string	">"
.LC45:
	.string	">NUMBER"
.LC46:
	.string	">NUM"
.LC47:
	.string	"NUMBER>"
.LC48:
	.string	"NUM>"
.LC49:
	.string	">HEX"
.LC50:
	.string	"HEX>"
.LC51:
	.string	"?DUP"
.LC52:
	.string	"@"
.LC53:
	.string	"C@"
.LC54:
	.string	"W@"
.LC55:
	.string	"ABS"
.LC56:
	.string	"ACCEPT"
.LC57:
	.string	"ALIGN"
.LC58:
	.string	"ALIGNED"
.LC59:
	.string	"ALLOT"
.LC60:
	.string	"AND"
.LC61:
	.string	"BEGIN"
.LC62:
	.string	"BL"
.LC63:
	.string	"BOUNDS"
.LC64:
	.string	"CELLS"
.LC65:
	.string	"CHAR"
.LC66:
	.string	"CONSTANT"
.LC67:
	.string	"CONST"
.LC68:
	.string	"CR"
.LC69:
	.string	"CREATE"
.LC70:
	.string	"DEPTH"
.LC71:
	.string	"DO"
.LC72:
	.string	"DROP"
.LC73:
	.string	"2DROP"
.LC74:
	.string	"DUP"
.LC75:
	.string	"2DUP"
.LC76:
	.string	"ELSE"
.LC77:
	.string	"EMIT"
.LC78:
	.string	"ERASE"
.LC79:
	.string	"FILL"
.LC80:
	.string	"HERE"
.LC81:
	.string	"I"
.LC82:
	.string	"IF"
.LC83:
	.string	"INVERT"
.LC84:
	.string	"J"
.LC85:
	.string	"KEY"
.LC86:
	.string	"LITERAL"
.LC87:
	.string	"LIT"
.LC88:
	.string	"LOOP"
.LC89:
	.string	"LSHIFT"
.LC90:
	.string	"MAX"
.LC91:
	.string	"MIN"
.LC92:
	.string	"MOD"
.LC93:
	.string	"NEGATE"
.LC94:
	.string	"OR"
.LC95:
	.string	"OVER"
.LC96:
	.string	"2OVER"
.LC97:
	.string	"PAGE"
.LC98:
	.string	"REPEAT"
.LC99:
	.string	"ROT"
.LC100:
	.string	"-ROT"
.LC101:
	.string	"RSHIFT"
.LC102:
	.string	"S\""
.LC103:
	.string	"SPACE"
.LC104:
	.string	"SPACES"
.LC105:
	.string	"SWAP"
.LC106:
	.string	"2SWAP"
.LC107:
	.string	"THEN"
.LC108:
	.string	"TYPE"
.LC109:
	.string	"U<"
.LC110:
	.string	"U>"
.LC111:
	.string	"UNTIL"
.LC112:
	.string	"VARIABLE"
.LC113:
	.string	"VAR"
.LC114:
	.string	"WHILE"
.LC115:
	.string	"XOR"
.LC116:
	.string	"["
.LC117:
	.string	"]"
.LC118:
	.string	"[']"
.LC119:
	.string	"[CHAR]"
.LC120:
	.string	".R"
.LC121:
	.string	"U.R"
.LC122:
	.string	"X.R"
.LC123:
	.string	"<>"
.LC124:
	.string	"AGAIN"
.LC125:
	.string	"FALSE"
.LC126:
	.string	"NIP"
.LC127:
	.string	"S\\\""
.LC128:
	.string	"TRUE"
.LC129:
	.string	"TUCK"
.LC130:
	.string	"UNUSED"
.LC131:
	.string	"WITHIN"
.LC132:
	.string	".S"
.LC133:
	.string	"?"
.LC134:
	.string	"DUMP"
.LC135:
	.string	"WORDS"
.LC136:
	.string	"WORDSIZE"
.LC137:
	.string	"BYE"
.LC138:
	.string	"RESET"
.LC139:
	.string	"WALIGN"
.LC140:
	.string	"WALIGNED"
.LC141:
	.string	"PRINTABLE"
.LC142:
	.string	"CXT"
.LC143:
	.string	"WXT"
.LC144:
	.string	"PRIMITIVES"
.LC145:
	.string	"SECONDARIES"
.LC146:
	.string	"UNDEFINED"
	.section	.data.rel.ro.local,"aw"
	.align 32
	.type	forth_primitives, @object
	.size	forth_primitives, 5080
forth_primitives:
	.quad	.LC21
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_store
	.quad	.LC22
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_c_store
	.quad	.LC23
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_w_store
	.quad	.LC24
	.byte	1
	.zero	7
	.quad	prim_immediate_tick
	.quad	prim_compile_tick
	.quad	0
	.quad	.LC25
	.byte	1
	.zero	7
	.quad	prim_immediate_paren
	.quad	prim_compile_paren
	.quad	0
	.quad	.LC26
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_star
	.quad	.LC27
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_star_slash
	.quad	.LC28
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_star_slash_mod
	.quad	.LC29
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_plus
	.quad	.LC30
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_comma
	.quad	.LC31
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_c_comma
	.quad	.LC32
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_w_comma
	.quad	.LC33
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_minus
	.quad	.LC34
	.byte	1
	.zero	7
	.quad	prim_immediate_backslash
	.quad	prim_compile_backslash
	.quad	0
	.quad	.LC35
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_dot
	.quad	.LC36
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_u_dot
	.quad	.LC37
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_x_dot
	.quad	.LC38
	.byte	2
	.zero	7
	.quad	prim_immediate_dot_quote
	.quad	prim_compile_dot_quote
	.quad	0
	.quad	.LC39
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_slash
	.quad	.LC40
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_slash_mod
	.quad	.LC41
	.byte	1
	.zero	7
	.quad	prim_immediate_colon
	.quad	prim_compile_colon
	.quad	0
	.quad	.LC42
	.byte	1
	.zero	7
	.quad	prim_immediate_semicolon
	.quad	prim_compile_semicolon
	.quad	0
	.quad	.LC7
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_less_than
	.quad	.LC43
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_equals
	.quad	.LC44
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_greater_than
	.quad	.LC45
	.byte	7
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_to_number
	.quad	.LC46
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_to_number
	.quad	.LC47
	.byte	7
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_number_to
	.quad	.LC48
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_number_to
	.quad	.LC49
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_to_hex
	.quad	.LC50
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_hex_to
	.quad	.LC51
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_question_dupe
	.quad	.LC52
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_fetch
	.quad	.LC53
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_c_fetch
	.quad	.LC54
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_w_fetch
	.quad	.LC55
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_abs
	.quad	.LC56
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_accept
	.quad	.LC57
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_align
	.quad	.LC58
	.byte	7
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_aligned
	.quad	.LC59
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_allot
	.quad	.LC60
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_and
	.quad	.LC61
	.byte	5
	.zero	7
	.quad	prim_immediate_begin
	.quad	prim_compile_begin
	.quad	0
	.quad	.LC62
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_b_l
	.quad	.LC63
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_bounds
	.quad	.LC64
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_cells
	.quad	.LC65
	.byte	4
	.zero	7
	.quad	prim_immediate_char
	.quad	prim_compile_char
	.quad	0
	.quad	.LC66
	.byte	8
	.zero	7
	.quad	prim_immediate_constant
	.quad	prim_compile_constant
	.quad	0
	.quad	.LC67
	.byte	5
	.zero	7
	.quad	prim_immediate_constant
	.quad	prim_compile_constant
	.quad	0
	.quad	.LC68
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_c_r
	.quad	.LC69
	.byte	6
	.zero	7
	.quad	prim_immediate_create
	.quad	prim_compile_create
	.quad	0
	.quad	.LC70
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_depth
	.quad	.LC71
	.byte	2
	.zero	7
	.quad	prim_immediate_do
	.quad	prim_compile_do
	.quad	0
	.quad	.LC72
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_drop
	.quad	.LC73
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_two_drop
	.quad	.LC74
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_dupe
	.quad	.LC75
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_two_dupe
	.quad	.LC76
	.byte	4
	.zero	7
	.quad	prim_immediate_else
	.quad	prim_compile_else
	.quad	0
	.quad	.LC77
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_emit
	.quad	.LC78
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_erase
	.quad	.LC79
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_fill
	.quad	.LC80
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_here
	.quad	.LC81
	.byte	1
	.zero	7
	.quad	prim_immediate_i
	.quad	prim_compile_i
	.quad	0
	.quad	.LC82
	.byte	2
	.zero	7
	.quad	prim_immediate_if
	.quad	prim_compile_if
	.quad	0
	.quad	.LC83
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_invert
	.quad	.LC84
	.byte	1
	.zero	7
	.quad	prim_immediate_j
	.quad	prim_compile_j
	.quad	0
	.quad	.LC85
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_key
	.quad	.LC86
	.byte	7
	.zero	7
	.quad	prim_immediate_literal
	.quad	prim_compile_literal
	.quad	0
	.quad	.LC87
	.byte	3
	.zero	7
	.quad	prim_immediate_literal
	.quad	prim_compile_literal
	.quad	0
	.quad	.LC88
	.byte	4
	.zero	7
	.quad	prim_immediate_loop
	.quad	prim_compile_loop
	.quad	0
	.quad	.LC89
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_l_shift
	.quad	.LC90
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_max
	.quad	.LC91
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_min
	.quad	.LC92
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_mod
	.quad	.LC93
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_negate
	.quad	.LC94
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_or
	.quad	.LC95
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_over
	.quad	.LC96
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_two_over
	.quad	.LC97
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_page
	.quad	.LC98
	.byte	6
	.zero	7
	.quad	prim_immediate_repeat
	.quad	prim_compile_repeat
	.quad	0
	.quad	.LC99
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_rote
	.quad	.LC100
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_minus_rote
	.quad	.LC101
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_r_shift
	.quad	.LC102
	.byte	2
	.zero	7
	.quad	prim_immediate_s_quote
	.quad	prim_compile_s_quote
	.quad	0
	.quad	.LC103
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_space
	.quad	.LC104
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_spaces
	.quad	.LC105
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_swap
	.quad	.LC106
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_two_swap
	.quad	.LC107
	.byte	4
	.zero	7
	.quad	prim_immediate_then
	.quad	prim_compile_then
	.quad	0
	.quad	.LC108
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_type
	.quad	.LC109
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_u_less_than
	.quad	.LC110
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_u_greater_than
	.quad	.LC111
	.byte	5
	.zero	7
	.quad	prim_immediate_until
	.quad	prim_compile_until
	.quad	0
	.quad	.LC112
	.byte	8
	.zero	7
	.quad	prim_immediate_variable
	.quad	prim_compile_variable
	.quad	0
	.quad	.LC113
	.byte	3
	.zero	7
	.quad	prim_immediate_variable
	.quad	prim_compile_variable
	.quad	0
	.quad	.LC114
	.byte	5
	.zero	7
	.quad	prim_immediate_while
	.quad	prim_compile_while
	.quad	0
	.quad	.LC115
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_x_or
	.quad	.LC116
	.byte	1
	.zero	7
	.quad	prim_immediate_left_bracket
	.quad	prim_compile_left_bracket
	.quad	0
	.quad	.LC117
	.byte	1
	.zero	7
	.quad	prim_immediate_right_bracket
	.quad	prim_compile_right_bracket
	.quad	0
	.quad	.LC118
	.byte	3
	.zero	7
	.quad	prim_immediate_bracket_tick
	.quad	prim_compile_bracket_tick
	.quad	0
	.quad	.LC119
	.byte	6
	.zero	7
	.quad	prim_immediate_bracket_char
	.quad	prim_compile_bracket_char
	.quad	0
	.quad	.LC120
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_dot_r
	.quad	.LC121
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_u_dot_r
	.quad	.LC122
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_x_dot_r
	.quad	.LC123
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_not_equals
	.quad	.LC124
	.byte	5
	.zero	7
	.quad	prim_immediate_again
	.quad	prim_compile_again
	.quad	0
	.quad	.LC125
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_false
	.quad	.LC126
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_nip
	.quad	.LC127
	.byte	3
	.zero	7
	.quad	prim_immediate_s_backslash_quote
	.quad	prim_compile_s_backslash_quote
	.quad	0
	.quad	.LC128
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_true
	.quad	.LC129
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_tuck
	.quad	.LC130
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_unused
	.quad	.LC131
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_within
	.quad	.LC132
	.byte	2
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_dot_s
	.quad	.LC133
	.byte	1
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_question
	.quad	.LC134
	.byte	4
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_dump
	.quad	.LC135
	.byte	5
	.zero	7
	.quad	prim_immediate_words
	.quad	prim_compile_words
	.quad	0
	.quad	.LC136
	.byte	8
	.zero	7
	.quad	prim_immediate_wordsize
	.quad	prim_compile_wordsize
	.quad	0
	.quad	.LC137
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_bye
	.quad	.LC138
	.byte	5
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_reset
	.quad	.LC139
	.byte	6
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_walign
	.quad	.LC140
	.byte	8
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_waligned
	.quad	.LC141
	.byte	9
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_printable
	.quad	.LC142
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_cxt
	.quad	.LC143
	.byte	3
	.zero	7
	.quad	0
	.quad	0
	.quad	prim_body_wxt
	.quad	.LC144
	.byte	10
	.zero	7
	.quad	prim_immediate_primitives
	.quad	prim_compile_primitives
	.quad	0
	.quad	.LC145
	.byte	11
	.zero	7
	.quad	prim_immediate_secondaries
	.quad	prim_compile_secondaries
	.quad	0
	.quad	.LC146
	.byte	9
	.zero	7
	.quad	prim_immediate_undefined
	.quad	prim_compile_undefined
	.quad	0
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
