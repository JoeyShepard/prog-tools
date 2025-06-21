	.file	"test.c"
	.text
	.text
	.align 1
	.align 2
	.global	_asm_test
	.type	_asm_test, @function
_asm_test:
	rts	
	mov	#43,r0
	.size	_asm_test, .-_asm_test
	.ident	"GCC: (GNU) 15.1.0"
