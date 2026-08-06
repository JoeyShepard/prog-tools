	.file	"foo.c"
	.text
	.text
	.align 1
	.align 2
	.global	foo
	.type	foo, @function
foo:
	rts	
	mov	#42,r0
	.size	foo, .-foo
	.ident	"GCC: (GNU) 14.1.0"
