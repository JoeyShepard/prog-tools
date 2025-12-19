	.file	"foo.c"
	.text
	.text
	.align 1
	.align 2
	.global	foo_tail
	.type	foo_tail, @function
foo_tail:
	mov.l	.L4,r1
	cmp/gt	r1,r4
	bt	.L2
	jmp	@r5
	add	#1,r4
	.align 1
.L2:
	rts	
	mov	r4,r0
.L5:
	.align 2
.L4:
	.long	1000000
	.size	foo_tail, .-foo_tail
	.ident	"GCC: (GNU) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
