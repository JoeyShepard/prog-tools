	.file	"forth-primitives.c"
	.text
	.text
	.align 1
	.align 2
	.global	prim_hidden_do
	.type	prim_hidden_do, @function
prim_hidden_do:
	mov.l	@r4,r2
	mov	#1,r1
	cmp/gt	r1,r2
	bf	.L7
	mov.l	.L8,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r7
	add	r0,r1
	add	#-4,r1
	add	#-2,r2
	mov.l	@r1,r3
	mov.l	@(24,r4),r1
	mov.l	r2,@r4
	mov.l	@(20,r4),r2
	cmp/hs	r2,r1
	bt/s	.L4
	mov	#7,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L4:
	mov.l	@(12,r4),r2
	mov	#2,r0
	mov.l	r2,@r1
	mov.l	@(48,r4),r2
	mov.b	r0,@(14,r1)
	mov.l	r2,@(4,r1)
	mov	r4,r2
	add	#64,r2
	mov.l	@(20,r2),r2
	mov.l	@(24,r4),r1
	mov.l	r2,@(8,r1)
	add	#-16,r1
	mov.l	r1,@(24,r4)
	mov.l	@(8,r4),r1
	mov.l	r7,@(8,r4)
	mov.l	r1,@(12,r4)
	mov.l	@(44,r4),r1
	mov.l	r3,@(44,r4)
	rts	
	mov.l	r1,@(48,r4)
	.align 1
.L7:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
.L9:
	.align 2
.L8:
	.long	1073741823
	.size	prim_hidden_do, .-prim_hidden_do
	.align 1
	.align 2
	.global	prim_hidden_done
	.type	prim_hidden_done, @function
prim_hidden_done:
	bra	.L13
	mov.l	@(24,r4),r1
	.align 1
.L11:
	tst	r0,r0
	bt	.L16
.L13:
	mov	r1,r3
	add	#16,r1
	mov.l	r1,@(24,r4)
	mov.b	@(14,r1),r0
	mov	r0,r2
	extu.b	r0,r0
	cmp/eq	#1,r0
	bf	.L11
	mov	r4,r2
	add	#64,r2
	mov.l	@(16,r3),r7
	mov.l	@(28,r2),r1
	mov.w	@(28,r3),r0
	add	r7,r1
	mov.l	r1,@(12,r2)
	extu.w	r0,r3
	mov.l	@(36,r4),r1
	shll2	r3
	add	r3,r1
	rts	
	mov.l	r1,@(36,r4)
	.align 1
.L16:
	add	#80,r4
	mov.b	r2,@r4
	rts	
	nop
	.size	prim_hidden_done, .-prim_hidden_done
	.align 1
	.align 2
	.global	prim_hidden_jump
	.type	prim_hidden_jump, @function
prim_hidden_jump:
	add	#64,r4
	mov.l	@(12,r4),r1
	mov.l	@(4,r1),r2
	add	r2,r1
	rts	
	mov.l	r1,@(12,r4)
	.size	prim_hidden_jump, .-prim_hidden_jump
	.align 1
	.align 2
	.global	prim_hidden_leave
	.type	prim_hidden_leave, @function
prim_hidden_leave:
	mov.l	@(12,r4),r1
	mov.l	@(24,r4),r2
	mov.l	r1,@(8,r4)
	mov.l	@(48,r4),r1
	mov.l	r1,@(44,r4)
	mov	r2,r1
	mov.l	@(16,r2),r2
	add	#16,r1
	mov.l	r2,@(12,r4)
	mov.l	r1,@(24,r4)
	mov.l	@(4,r1),r1
	mov.l	r1,@(48,r4)
	add	#64,r4
	mov.l	@(12,r4),r1
	mov.l	@(4,r1),r2
	add	r2,r1
	rts	
	mov.l	r1,@(12,r4)
	.size	prim_hidden_leave, .-prim_hidden_leave
	.align 1
	.align 2
	.global	prim_hidden_push
	.type	prim_hidden_push, @function
prim_hidden_push:
	mov	r4,r2
	add	#64,r2
	mov.l	@(12,r2),r1
	mov.l	@r4,r0
	mov.l	@(4,r1),r3
	add	#4,r1
	mov.l	r1,@(12,r2)
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r3,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_hidden_push, .-prim_hidden_push
	.align 1
	.align 2
	.global	prim_hidden_secondary
	.type	prim_hidden_secondary, @function
prim_hidden_secondary:
	mov	r4,r7
	add	#64,r7
	mov.l	@(12,r7),r2
	mov	#5,r3
	mov.l	@(4,r2),r1
	add	#4,r2
	mov.l	r2,@(12,r7)
	shld	r3,r1
	mov.l	@(24,r7),r3
	add	r3,r1
	mov	r1,r0
	add	#16,r0
	mov.b	@(12,r0),r0
	extu.b	r0,r0
	cmp/eq	#4,r0
	bt/s	.L28
	add	#-1,r0
	extu.b	r0,r0
	mov	#2,r3
	cmp/hi	r3,r0
	bt	.L23
	mov.l	@r4,r0
	mov.w	.L31,r2
	cmp/gt	r2,r0
	bt/s	.L29
	shll2	r0
	mov.l	@r1,r1
	mov.l	@(4,r1),r2
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.align 1
.L23:
	mov.l	@(24,r4),r3
	mov.l	@(20,r4),r6
	cmp/hs	r6,r3
	bf/s	.L30
	mov	#1,r0
	mov.l	@(20,r7),r6
	add	#1,r6
	mov.l	r6,@(20,r7)
	mov.l	@(28,r7),r6
	mov.b	r0,@(14,r3)
	sub	r6,r2
	mov.w	@(26,r1),r0
	mov.l	r2,@r3
	mov.l	@(20,r7),r3
	mov.l	@(24,r4),r2
	mov.l	@(32,r4),r6
	mov.l	r3,@(8,r2)
	mov.w	r0,@(12,r2)
	extu.w	r0,r0
	mov.l	@(36,r4),r3
	shll2	r0
	sub	r0,r3
	cmp/hs	r6,r3
	bt/s	.L26
	mov.l	r3,@(36,r4)
	mov	#5,r6
	mov	r4,r3
	add	#124,r3
	mov.l	r6,@(4,r3)
	mov	#0,r6
	mov	r4,r3
	add	#80,r3
	mov.b	r6,@r3
.L26:
	mov.l	@r1,r1
	add	#-16,r2
	mov.l	r2,@(24,r4)
	add	#-4,r1
	rts	
	mov.l	r1,@(12,r7)
	.align 1
.L28:
	mov.l	@(20,r1),r1
	mov	r4,r2
	mov	#9,r3
	add	#124,r2
	mov.l	r1,@(20,r2)
	add	#80,r4
	mov.l	r3,@(4,r2)
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L30:
	mov	r4,r1
	mov	#7,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L29:
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L31:
	.short	255
	.size	prim_hidden_secondary, .-prim_hidden_secondary
	.align 1
	.align 2
	.global	prim_store
	.type	prim_store, @function
prim_store:
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r3
	add	#-2,r2
	add	r0,r1
	mov.l	r2,@r4
	add	#-4,r1
	mov	r3,r0
	mov.l	@r1,r2
	mov	r4,r1
	add	#64,r1
	mov.l	@(8,r1),r1
	and	r1,r0
	mov.l	@(52,r4),r1
	rts	
	mov.l	r2,@(r0,r1)
	.size	prim_store, .-prim_store
	.align 1
	.align 2
	.global	prim_c_store
	.type	prim_c_store, @function
prim_c_store:
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r2
	shll2	r0
	mov.l	@(r0,r1),r3
	add	r0,r1
	mov.l	r2,@r4
	mov	r4,r2
	add	#64,r2
	mov.l	@(0,r2),r2
	add	#-4,r1
	mov.l	@r1,r1
	and	r3,r2
	mov.l	@(52,r4),r3
	mov	r2,r0
	rts	
	mov.b	r1,@(r0,r3)
	.size	prim_c_store, .-prim_c_store
	.align 1
	.align 2
	.global	prim_w_store
	.type	prim_w_store, @function
prim_w_store:
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r2
	shll2	r0
	mov.l	@(r0,r1),r3
	add	r0,r1
	mov.l	r2,@r4
	mov	r4,r2
	add	#64,r2
	mov.l	@(4,r2),r2
	add	#-4,r1
	mov.l	@r1,r1
	and	r3,r2
	mov.l	@(52,r4),r3
	mov	r2,r0
	rts	
	mov.w	r1,@(r0,r3)
	.size	prim_w_store, .-prim_w_store
	.align 1
	.align 2
	.global	prim_star
	.type	prim_star, @function
prim_star:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r2
	mov.l	@r1,r3
	mul.l	r2,r3
	sts	macl,r2
	rts	
	mov.l	r2,@r1
	.size	prim_star, .-prim_star
	.align 1
	.align 2
	.global	prim_star_slash
	.type	prim_star_slash, @function
prim_star_slash:
	mov.l	r8,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r7
	add	#-2,r2
	mov.l	r2,@r4
	mov	r1,r2
	add	r0,r2
	mov	r1,r8
	add	#-8,r0
	tst	r7,r7
	add	#-4,r2
	add	r0,r8
	mov.l	@r2,r2
	mov.l	@r8,r1
	bf	.L37
	mov	#1,r7
.L37:
	dmuls.l	r2,r1
	mov.l	.L39,r0
	mov	r7,r6
	shll	r6
	sts	macl,r5
	sts	mach,r4
	jsr	@r0
	subc	r6,r6
	mov.l	r1,@r8
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L40:
	.align 2
.L39:
	.long	__divdi3
	.size	prim_star_slash, .-prim_star_slash
	.align 1
	.align 2
	.global	prim_star_slash_mod
	.type	prim_star_slash_mod, @function
prim_star_slash_mod:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	add	#-20,r15
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r2),r3
	mov	r0,r9
	add	r2,r0
	add	#-4,r9
	tst	r3,r3
	add	r2,r9
	add	#-8,r0
	mov.l	@r9,r1
	mov.l	@r0,r7
	dmuls.l	r1,r7
	sts	mach,r1
	sts	macl,r10
	bt/s	.L42
	mov.l	r1,@(12,r15)
	mov.l	.L46,r0
	mov	r3,r1
	shll	r1
	mov	r3,r7
	subc	r1,r1
	mov.l	r3,@(8,r15)
	sts	mach,r4
	sts	macl,r5
	mov.l	r2,@r15
	mov	r1,r6
	jsr	@r0
	mov.l	r1,@(16,r15)
	mov.l	.L47,r0
	mov	r10,r5
	mov.l	@(12,r15),r4
	mov.l	@(16,r15),r6
	mov.l	@(8,r15),r7
	jsr	@r0
	mov.l	r1,@(4,r15)
	mov.l	@(4,r15),r3
	mov	r1,r10
	mov.l	@r15,r2
	mov.l	r0,@(12,r15)
.L42:
	mov.l	r10,@r9
	mov.l	@r8,r0
	mov.l	.L48,r1
	add	r1,r0
	shll2	r0
	mov.l	r3,@(r0,r2)
	add	#20,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L49:
	.align 2
.L46:
	.long	__moddi3
.L47:
	.long	__divdi3
.L48:
	.long	1073741822
	.size	prim_star_slash_mod, .-prim_star_slash_mod
	.align 1
	.align 2
	.global	prim_plus
	.type	prim_plus, @function
prim_plus:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	add	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_plus, .-prim_plus
	.align 1
	.align 2
	.global	prim_comma
	.type	prim_comma, @function
prim_comma:
	mov	r4,r2
	add	#64,r2
	mov.l	@(8,r2),r3
	mov.l	@(60,r4),r1
	mov.l	@r4,r0
	and	r3,r1
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r1,@(60,r4)
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r7
	mov	r1,r0
	mov.l	@(52,r4),r3
	mov.l	r7,@(r0,r3)
	mov.l	@(60,r4),r1
	mov.l	@(8,r2),r2
	add	#4,r1
	and	r2,r1
	rts	
	mov.l	r1,@(60,r4)
	.size	prim_comma, .-prim_comma
	.align 1
	.align 2
	.global	prim_c_comma
	.type	prim_c_comma, @function
prim_c_comma:
	mov	r4,r2
	add	#64,r2
	mov.l	@(0,r2),r3
	mov.l	@(60,r4),r1
	mov.l	@r4,r0
	and	r3,r1
	mov.l	@(4,r4),r7
	add	#-1,r0
	mov.l	r1,@(60,r4)
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r7),r7
	mov	r1,r0
	mov.l	@(52,r4),r3
	mov.b	r7,@(r0,r3)
	mov.l	@(60,r4),r1
	mov.l	@(0,r2),r2
	add	#1,r1
	and	r2,r1
	rts	
	mov.l	r1,@(60,r4)
	.size	prim_c_comma, .-prim_c_comma
	.align 1
	.align 2
	.global	prim_w_comma
	.type	prim_w_comma, @function
prim_w_comma:
	mov	r4,r1
	add	#64,r1
	mov.l	@(4,r1),r2
	mov.l	@(60,r4),r6
	mov.l	@r4,r1
	mov.l	@(4,r4),r7
	and	r2,r6
	add	#-1,r1
	mov.l	r6,@(60,r4)
	mov.l	r1,@r4
	shll2	r1
	mov	r1,r0
	mov.l	@(52,r4),r3
	mov.l	@(r0,r7),r1
	mov	r6,r0
	mov.w	r1,@(r0,r3)
	add	#1,r0
	and	r2,r0
	rts	
	mov.l	r0,@(60,r4)
	.size	prim_w_comma, .-prim_w_comma
	.align 1
	.align 2
	.global	prim_minus
	.type	prim_minus, @function
prim_minus:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	sub	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_minus, .-prim_minus
	.align 1
	.align 2
	.global	prim_slash
	.type	prim_slash, @function
prim_slash:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r2),r5
	add	#-4,r0
	add	r0,r2
	tst	r5,r5
	bt/s	.L61
	mov.l	@r2,r4
	mov.l	.L64,r0
	sts.l	pr,@-r15
	jsr	@r0
	nop
	mov.l	r0,@r2
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L61:
	rts	
	mov.l	r4,@r2
.L65:
	.align 2
.L64:
	.long	__sdivsi3_i4i
	.size	prim_slash, .-prim_slash
	.align 1
	.align 2
	.global	prim_slash_mod
	.type	prim_slash_mod, @function
prim_slash_mod:
	mov.l	r8,@-r15
	mov	r4,r7
	sts.l	pr,@-r15
	mov.l	.L72,r1
	mov.l	@r4,r2
	mov.l	@(4,r4),r8
	add	r1,r2
	shll2	r2
	add	r8,r2
	mov.l	@r2,r3
	mov	r2,r1
	add	#-4,r1
	tst	r3,r3
	bt/s	.L67
	mov.l	@r1,r6
	mov.l	.L73,r0
	mov	r6,r4
	jsr	@r0
	mov	r3,r5
	mul.l	r3,r0
	mov	r6,r3
	mov	r0,r6
	sts	macl,r1
	sub	r1,r3
.L67:
	mov.l	r6,@r2
	mov.l	@r7,r0
	mov.l	.L74,r1
	add	r1,r0
	shll2	r0
	mov.l	r3,@(r0,r8)
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L75:
	.align 2
.L72:
	.long	1073741823
.L73:
	.long	__sdivsi3_i4i
.L74:
	.long	1073741822
	.size	prim_slash_mod, .-prim_slash_mod
	.align 1
	.align 2
	.global	prim_less_than
	.type	prim_less_than, @function
prim_less_than:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	cmp/gt	r2,r3
	subc	r2,r2
	rts	
	mov.l	r2,@r1
	.size	prim_less_than, .-prim_less_than
	.align 1
	.align 2
	.global	prim_equals
	.type	prim_equals, @function
prim_equals:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	cmp/eq	r2,r3
	subc	r2,r2
	rts	
	mov.l	r2,@r1
	.size	prim_equals, .-prim_equals
	.align 1
	.align 2
	.global	prim_greater_than
	.type	prim_greater_than, @function
prim_greater_than:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r2
	mov.l	@r1,r3
	cmp/gt	r2,r3
	subc	r2,r2
	rts	
	mov.l	r2,@r1
	.size	prim_greater_than, .-prim_greater_than
	.align 1
	.align 2
	.global	prim_to_number
	.type	prim_to_number, @function
prim_to_number:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15
	mov.l	@r4,r1
	add	#-20,r15
	mov.l	r1,@(4,r15)
	mov	#1,r1
	mov.l	@(4,r15),r2
	cmp/gt	r1,r2
	bt/s	.L125
	mov	r4,r11
	bra	.L103
	mov	#10,r2
.L125:
	mov.w	.L108,r1
	mov.l	@(4,r15),r2
	cmp/gt	r1,r2
	bf	.L124
	bra	.L104
	mov	#6,r2
.L124:
	mov.l	@(4,r15),r13
	mov.l	.L112,r0
	mov.l	@(4,r4),r1
	add	r13,r0
	shll2	r0
	mov.l	r1,@(8,r15)
	add	r0,r1
	mov.l	@(8,r15),r2
	mov.l	r1,@(16,r15)
	add	#-4,r1
	mov.l	@r1,r1
	mov.l	@(r0,r2),r6
	mov.l	r1,@(12,r15)
	mov.l	@(56,r4),r1
	cmp/hi	r1,r6
	bf	.L83
	mov	r1,r6
.L83:
	tst	r6,r6
	bf	.L123
	bra	.L95
	mov	#0,r7
.L123:
	mov.l	@(52,r11),r9
	mov	r11,r1
	mov.l	@(12,r15),r3
	add	#64,r1
	mov.l	@(0,r1),r10
	mov	r6,r12
	mov	#0,r8
	mov.l	r11,@r15
	add	#-1,r12
	mov	#0,r1
	mov	r12,r5
	mov	#0,r7
	mov	#10,r4
	mov	#1,r14
	.align 2
.L94:
	and	r10,r3
	mov	r3,r0
	mov.b	@(r0,r9),r2
	extu.b	r2,r0
	cmp/eq	#45,r0
	movt	r11
	cmp/eq	r12,r5
	movt	r2
	and	r2,r11
	tst	r11,r11
	bf/s	.L96
	add	#-48,r0
	extu.b	r0,r2
	mov	#9,r13
	cmp/hi	r13,r2
	bf	.L122
	bra	.L105
	mov.l	@r15,r11
.L122:
	mul.l	r1,r4
	tst	r8,r8
	sts	macl,r1
	dmulu.l	r4,r7
	sts	mach,r2
	sts	macl,r7
	bf/s	.L87
	add	r1,r2
	cmp/gt	r0,r8
	subc	r1,r1
	clrt
	addc	r0,r7
	addc	r2,r1
.L88:
	mov.l	.L110,r0
	clrt
	mov	#0,r2
	addc	r7,r0
	addc	r1,r2
	cmp/hs	r14,r2
	bf/s	.L85
	cmp/hi	r14,r2
	bt	.L98
	bra	.L106
	nop
.L98:
	mov.l	@(12,r15),r1
.L126:
	mov.l	@r15,r11
	and	r10,r1
	mov.w	.L111,r3
	mov	r1,r0
	mov.b	@(r0,r9),r7
	add	r11,r3
	exts.b	r7,r0
	mov	r7,r2
	cmp/eq	#45,r0
	bf/s	.L93
	mov	#1,r7
.L90:
	mov.b	r0,@r3
	mov	#0,r0
	mov.b	r0,@(1,r3)
	mov	r7,r0
	cmp/eq	#11,r0
	bt	.L92
	add	#1,r1
.L127:
	and	r10,r1
	mov	r1,r0
	mov.b	@(r0,r9),r6
	add	#1,r3
	add	#1,r7
	mov	r6,r2
	mov	r6,r0
.L93:
	add	#-48,r2
	extu.b	r2,r2
	mov	#9,r6
	cmp/hi	r6,r2
	bf	.L90
	mov	r7,r0
	cmp/eq	#11,r0
	bf/s	.L127
	add	#1,r1
	add	#-1,r1
.L92:
	mov	#3,r2
	mov	r11,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	mov	#0,r2
	mov	r11,r1
	add	#80,r1
	mov.b	r2,@r1
	mov.l	@(4,r15),r1
	add	#-2,r1
	mov.l	r1,@r11
	add	#20,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L104:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r11
	mov	#0,r1
	mov.b	r1,@r11
	add	#20,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L96:
	mov	r11,r8
.L85:
	dt	r6
	add	#1,r3
	bf/s	.L94
	add	#-1,r5
	mov.l	@r15,r11
	mov	#0,r5
	mov.l	r3,@(12,r15)
.L84:
	mov.l	@(16,r15),r1
	mov.l	.L112,r2
	mov.l	r5,@(4,r1)
	mov.l	@r11,r0
	mov.l	@(12,r15),r1
	mov.l	@(8,r15),r13
	add	r2,r0
	shll2	r0
	mov.l	r1,@(r0,r13)
	add	#-1,r2
	mov.l	@r11,r0
	add	r2,r0
	shll2	r0
	mov.l	r7,@(r0,r13)
	mov.l	@r11,r1
	add	#1,r1
	mov.l	r1,@r11
	add	#20,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L87:
	cmp/gt	r0,r11
	mov	r2,r1
	subc	r11,r11
	clrt
	subc	r0,r7
	bra	.L88
	subc	r11,r1
	.align 1
.L103:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r11
	mov	#0,r1
	mov.b	r1,@r11
	add	#20,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L105:
	add	#1,r5
	bra	.L84
	mov.l	r3,@(12,r15)
	.align 1
.L108:
	.short	255
.L111:
	.short	132
.L113:
	.align 2
.L112:
	.long	1073741823
.L110:
	.long	-2147483648
	.align 1
.L95:
	bra	.L84
	mov	#0,r5
	.align 1
.L106:
	mov.l	.L114,r2
	cmp/hi	r2,r0
	bf	.L85
	bra	.L126
	mov.l	@(12,r15),r1
.L115:
	.align 2
.L114:
	.long	2147483647
	.size	prim_to_number, .-prim_to_number
	.align 1
	.align 2
	.global	prim_to_hex
	.type	prim_to_hex, @function
prim_to_hex:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15
	mov.l	@r4,r1
	add	#-24,r15
	mov.l	r1,@(4,r15)
	mov	#1,r1
	mov.l	@(4,r15),r2
	cmp/gt	r1,r2
	bt/s	.L210
	mov	r4,r12
	bra	.L168
	mov	#10,r2
.L210:
	mov.w	.L178,r1
	mov.l	@(4,r15),r14
	cmp/gt	r1,r14
	bf	.L209
	bra	.L169
	mov	#6,r2
.L209:
	mov.l	@(4,r15),r6
	mov.l	.L179,r0
	mov.l	@(4,r4),r1
	add	r6,r0
	mov.l	r1,@(8,r15)
	shll2	r0
	add	r0,r1
	mov.l	@(8,r15),r14
	mov.l	r1,@(12,r15)
	add	#-4,r1
	mov.l	@r1,r5
	mov.l	@(56,r4),r1
	mov.l	@(r0,r14),r4
	cmp/hi	r1,r4
	bf	.L132
	mov	r1,r4
.L132:
	tst	r4,r4
	bf	.L208
	bra	.L154
	mov	#0,r7
.L208:
	mov	r12,r1
	add	#64,r1
	mov.l	@(0,r1),r10
	mov.l	@(52,r12),r13
	mov.l	r5,@(20,r15)
	and	r10,r5
	mov	r5,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r1
	mov	r1,r0
	cmp/eq	#45,r0
	bf/s	.L207
	mov.l	r1,@(16,r15)
	bra	.L170
	add	#-1,r4
.L207:
	mov	r4,r0
	cmp/eq	#1,r0
	bf/s	.L206
	mov.l	@(16,r15),r3
	bra	.L171
	mov	#0,r1
.L206:
	mov	#0,r6
	mov	r5,r2
	mov.l	r6,@r15
.L153:
	mov	r3,r0
	cmp/eq	#48,r0
	bf/s	.L136
	and	r10,r5
	bra	.L172
	add	#1,r2
.L136:
	mov.l	.L180,r8
	mov	#0,r7
	mov	#9,r14
	mov	r4,r9
	mov	#1,r11
	mov	r5,r0
	mov	#0,r1
	.align 2
.L152:
	mov	r3,r6
	add	#-48,r6
	extu.b	r6,r2
	cmp/hi	r14,r2
	bf	.L139
	mov	r3,r2
	add	#-97,r2
	extu.b	r2,r2
	mov	#5,r6
	cmp/hi	r6,r2
	bf	.L204
	bra	.L140
	mov	r3,r2
.L204:
	mov	r3,r6
	add	#-87,r6
.L139:
	mov	#-28,r2
	mov	r7,r5
	shld	r2,r5
	mov	r1,r2
	shll2	r2
	mov	r5,r1
	shll2	r2
	mov	r7,r3
	or	r2,r1
	mov	#0,r2
	cmp/gt	r6,r2
	mov.l	@r15,r2
	subc	r5,r5
	shll2	r3
	tst	r2,r2
	bt/s	.L203
	shll2	r3
	bra	.L142
	mov	r3,r7
.L203:
	clrt
	mov	r3,r7
	addc	r6,r7
	addc	r5,r1
.L143:
	clrt
	mov	#0,r2
	mov	r7,r3
	addc	r8,r3
	addc	r1,r2
	cmp/hs	r11,r2
	bt	.L202
	bra	.L211
	dt	r9
.L202:
	cmp/hi	r11,r2
	bt	.L157
	bra	.L173
	nop
.L157:
	mov.w	.L181,r1
	mov	#9,r5
	mov.w	.L182,r7
	mov	#-33,r8
	mov.l	@(20,r15),r3
	add	r12,r1
	mov.l	@(16,r15),r11
	sub	r12,r7
	mov	#5,r4
	bra	.L150
	mov	#8,r2
	.align 1
.L174:
	mov	r9,r0
	cmp/eq	#45,r0
	bf/s	.L212
	mov	r11,r0
.L146:
	mov	#0,r0
	mov.b	r9,@r1
	mov.b	r0,@(1,r1)
	dt	r2
	bt/s	.L165
	add	#1,r1
.L175:
	and	r10,r3
	mov	r10,r0
	add	#1,r3
	and	r3,r0
	mov.b	@(r0,r13),r11
.L150:
	mov	r7,r0
	add	r1,r0
	tst	r0,r0
	bt/s	.L174
	exts.b	r11,r9
	mov	r11,r0
.L212:
	add	#-48,r0
	extu.b	r0,r0
	cmp/hi	r5,r0
	bf/s	.L146
	mov	r11,r0
	and	r8,r0
	add	#-65,r0
	extu.b	r0,r0
	cmp/hi	r4,r0
	bf	.L146
	dt	r2
	bf/s	.L175
	add	#1,r1
.L165:
	mov	#4,r2
	mov	r12,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	mov	#0,r2
	mov	r12,r1
	add	#80,r1
	mov.b	r2,@r1
	mov.l	@(4,r15),r1
	add	#-2,r1
	mov.l	r1,@r12
	add	#24,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L169:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r12
	mov	#0,r1
	mov.b	r1,@r12
	add	#24,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L168:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r12
	mov	#0,r1
	mov.b	r1,@r12
	add	#24,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L178:
	.short	255
.L181:
	.short	132
.L182:
	.short	-132
.L183:
	.align 2
.L179:
	.long	1073741823
.L180:
	.long	-2147483648
	.align 1
.L154:
	mov	#0,r4
.L133:
	mov.l	@(12,r15),r14
	mov.l	.L184,r1
	mov.l	r4,@(4,r14)
	mov.l	@r12,r0
	mov.l	@(8,r15),r2
	add	r1,r0
	mov.l	.L185,r6
	shll2	r0
	mov.l	r5,@(r0,r2)
	mov.l	@r12,r0
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r12,r1
	add	#1,r1
	mov.l	r1,@r12
	add	#24,r15
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L170:
	mov	#1,r1
	cmp/hi	r1,r4
	bf/s	.L155
	add	#1,r5
	mov	r10,r2
	and	r5,r2
	mov	r2,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r3
	mov	#1,r1
	bra	.L153
	mov.l	r1,@r15
	.align 1
.L173:
	mov.l	.L186,r6
	cmp/hi	r6,r3
	bf	.L144
	bra	.L157
	nop
	.align 2
.L144:
	dt	r9
	.align 2
.L211:
	add	#-1,r4
	bt/s	.L176
	add	#1,r0
	and	r10,r0
	mov.b	@(r0,r13),r3
	bra	.L152
	extu.b	r3,r3
	.align 1
.L142:
	subc	r6,r7
	bra	.L143
	subc	r5,r1
	.align 1
.L140:
	add	#-65,r2
	extu.b	r2,r2
	mov	#5,r6
	cmp/hi	r6,r2
	bt/s	.L177
	mov	r3,r6
	bra	.L139
	add	#-55,r6
	.align 1
.L176:
	mov	#0,r4
	bra	.L133
	mov	r0,r5
	.align 1
.L171:
	mov.l	r1,@r15
	bra	.L136
	and	r10,r5
	.align 1
.L177:
	bra	.L133
	mov	r0,r5
	.align 1
.L155:
	mov	#1,r2
	mov.l	r2,@r15
.L135:
	tst	r4,r4
	bt/s	.L133
	mov	#0,r7
	and	r10,r5
	mov	r5,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r3
.L199:
	bra	.L136
	nop
	.align 1
.L172:
	and	r10,r2
	mov	r2,r0
	mov.b	@(r0,r13),r0
	cmp/eq	#120,r0
	bf	.L199
	mov	r2,r5
	add	#-2,r4
	bra	.L135
	add	#1,r5
.L187:
	.align 2
.L184:
	.long	1073741823
.L185:
	.long	1073741822
.L186:
	.long	2147483647
	.size	prim_to_hex, .-prim_to_hex
	.align 1
	.align 2
	.global	prim_question_dupe
	.type	prim_question_dupe, @function
prim_question_dupe:
	mov.l	@r4,r1
	tst	r1,r1
	bt/s	.L221
	mov	r4,r2
	mov.l	.L223,r0
	mov.l	@(4,r4),r2
	add	r1,r0
	shll2	r0
	mov.l	@(r0,r2),r3
	tst	r3,r3
	bt	.L220
	mov.w	.L224,r7
	cmp/gt	r7,r1
	bt/s	.L222
	add	r0,r2
	mov.l	r3,@(4,r2)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
.L220:
	rts	
	nop
	.align 1
.L221:
	mov	#10,r3
	add	#124,r2
	mov.l	r3,@(4,r2)
	add	#80,r4
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L222:
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L224:
	.short	255
.L225:
	.align 2
.L223:
	.long	1073741823
	.size	prim_question_dupe, .-prim_question_dupe
	.align 1
	.align 2
	.global	prim_fetch
	.type	prim_fetch, @function
prim_fetch:
	mov.l	@r4,r1
	mov.l	.L227,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov	r4,r2
	add	#64,r2
	mov.l	@(8,r2),r0
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	@(r0,r2),r2
	rts	
	mov.l	r2,@r1
.L228:
	.align 2
.L227:
	.long	1073741823
	.size	prim_fetch, .-prim_fetch
	.align 1
	.align 2
	.global	prim_c_fetch
	.type	prim_c_fetch, @function
prim_c_fetch:
	mov.l	@r4,r1
	mov.l	.L230,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov	r4,r2
	add	#64,r2
	mov.l	@(0,r2),r0
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.b	@(r0,r2),r2
	extu.b	r2,r2
	rts	
	mov.l	r2,@r1
.L231:
	.align 2
.L230:
	.long	1073741823
	.size	prim_c_fetch, .-prim_c_fetch
	.align 1
	.align 2
	.global	prim_w_fetch
	.type	prim_w_fetch, @function
prim_w_fetch:
	mov.l	@r4,r1
	mov.l	.L233,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov	r4,r2
	add	#64,r2
	mov.l	@(4,r2),r0
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.w	@(r0,r2),r2
	extu.w	r2,r2
	rts	
	mov.l	r2,@r1
.L234:
	.align 2
.L233:
	.long	1073741823
	.size	prim_w_fetch, .-prim_w_fetch
	.align 1
	.align 2
	.global	prim_quit
	.type	prim_quit, @function
prim_quit:
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.size	prim_quit, .-prim_quit
	.align 1
	.align 2
	.global	prim_abs
	.type	prim_abs, @function
prim_abs:
	mov.l	.L240,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r2
	cmp/pz	r2
	bf	.L239
	rts	
	nop
	.align 1
.L239:
	neg	r2,r2
	rts	
	mov.l	r2,@r1
.L241:
	.align 2
.L240:
	.long	1073741823
	.size	prim_abs, .-prim_abs
	.align 1
	.align 2
	.global	prim_accept
	.type	prim_accept, @function
prim_accept:
	mov.l	@r4,r2
	mov	#1,r3
	cmp/gt	r3,r2
	bf/s	.L251
	mov	r4,r1
	mov.l	.L252,r6
	mov	r4,r3
	add	#124,r3
	mov	r2,r7
	mov.l	@(32,r3),r0
	add	r6,r2
	mov.l	@(4,r4),r3
	shll2	r2
	tst	r0,r0
	add	#-1,r7
	bt/s	.L245
	add	r3,r2
	sts.l	pr,@-r15
	mov	r4,r3
	add	#-4,r15
	add	#64,r3
	mov.l	r7,@r4
	mov.l	@(0,r3),r3
	mov.l	@r2,r4
	mov.l	@(4,r2),r6
	mov	r3,r7
	mov.l	@(52,r1),r5
	and	r3,r4
	jsr	@r0
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov	r0,r2
	mov.l	.L253,r3
	mov.l	@r1,r0
	mov.l	@(4,r1),r1
	add	r3,r0
	shll2	r0
	mov.l	r2,@(r0,r1)
	add	#4,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L251:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(4,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	rts	
	nop
	.align 1
.L245:
	mov.l	r7,@r4
	rts	
	mov.l	r0,@r2
.L254:
	.align 2
.L252:
	.long	1073741822
.L253:
	.long	1073741823
	.size	prim_accept, .-prim_accept
	.align 1
	.align 2
	.global	prim_align
	.type	prim_align, @function
prim_align:
	mov.l	@(60,r4),r1
	mov	#3,r2
	mov	r1,r0
	tst	#3,r0
	bt/s	.L260
	and	r1,r2
	add	#4,r1
	sub	r2,r1
	mov	r4,r2
	add	#64,r2
	mov.l	@(8,r2),r2
	and	r2,r1
	mov.l	r1,@(60,r4)
.L260:
	rts	
	nop
	.size	prim_align, .-prim_align
	.align 1
	.align 2
	.global	prim_aligned
	.type	prim_aligned, @function
prim_aligned:
	mov.l	.L266,r2
	mov.l	@r4,r1
	mov.l	@(4,r4),r3
	add	r2,r1
	shll2	r1
	add	r1,r3
	mov.l	@r3,r1
	mov	r1,r2
	shll	r2
	subc	r2,r2
	mov	r1,r0
	xor	r2,r0
	sub	r2,r0
	and	#3,r0
	mov	r0,r7
	xor	r2,r7
	cmp/eq	r2,r7
	mov	r7,r6
	bt/s	.L262
	sub	r2,r6
	add	#4,r1
	sub	r6,r1
.L262:
	add	#64,r4
	mov.l	@(8,r4),r2
	and	r2,r1
	rts	
	mov.l	r1,@r3
.L267:
	.align 2
.L266:
	.long	1073741823
	.size	prim_aligned, .-prim_aligned
	.align 1
	.align 2
	.global	prim_and
	.type	prim_and, @function
prim_and:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	and	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_and, .-prim_and
	.align 1
	.align 2
	.global	prim_b_l
	.type	prim_b_l, @function
prim_b_l:
	mov.l	@r4,r0
	mov	#32,r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_b_l, .-prim_b_l
	.align 1
	.align 2
	.global	prim_bounds
	.type	prim_bounds, @function
prim_bounds:
	mov.l	@r4,r1
	mov.l	.L271,r2
	mov.l	@(4,r4),r3
	add	r2,r1
	shll2	r1
	add	r3,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r7
	mov.l	@r1,r2
	mov.l	r7,@r1
	mov.l	.L272,r1
	mov.l	@r4,r0
	add	#64,r4
	add	r1,r0
	mov	r2,r1
	mov.l	@(0,r4),r2
	add	r7,r1
	shll2	r0
	and	r2,r1
	rts	
	mov.l	r1,@(r0,r3)
.L273:
	.align 2
.L271:
	.long	1073741823
.L272:
	.long	1073741822
	.size	prim_bounds, .-prim_bounds
	.align 1
	.align 2
	.global	prim_cells
	.type	prim_cells, @function
prim_cells:
	mov.l	@r4,r1
	mov.l	.L275,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r2
	shll2	r2
	rts	
	mov.l	r2,@r1
.L276:
	.align 2
.L275:
	.long	1073741823
	.size	prim_cells, .-prim_cells
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 2
.LC0:
	.string	"\n"
	.text
	.align 1
	.align 2
	.global	prim_c_r
	.type	prim_c_r, @function
prim_c_r:
	mov	r4,r1
	add	#124,r1
	mov.l	@(24,r1),r2
	tst	r2,r2
	bt	.L286
	sts.l	pr,@-r15
	add	#-4,r15
	mov.l	.L289,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	@(44,r1),r1
	tst	r1,r1
	bt	.L284
	add	#4,r15
	jmp	@r1
	lds.l	@r15+,pr
	.align 1
.L284:
	add	#4,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L286:
	rts	
	nop
.L290:
	.align 2
.L289:
	.long	.LC0
	.size	prim_c_r, .-prim_c_r
	.align 1
	.align 2
	.global	prim_drop
	.type	prim_drop, @function
prim_drop:
	mov.l	@r4,r1
	add	#-1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_drop, .-prim_drop
	.align 1
	.align 2
	.global	prim_two_drop
	.type	prim_two_drop, @function
prim_two_drop:
	mov.l	@r4,r1
	add	#-2,r1
	rts	
	mov.l	r1,@r4
	.size	prim_two_drop, .-prim_two_drop
	.align 1
	.align 2
	.global	prim_dupe
	.type	prim_dupe, @function
prim_dupe:
	mov.l	@r4,r0
	mov.l	.L294,r2
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(4,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
.L295:
	.align 2
.L294:
	.long	1073741823
	.size	prim_dupe, .-prim_dupe
	.align 1
	.align 2
	.global	prim_two_dupe
	.type	prim_two_dupe, @function
prim_two_dupe:
	mov.l	@r4,r0
	mov.l	.L297,r2
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov.l	r2,@(8,r0)
	mov.l	@r4,r0
	mov.l	.L298,r2
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(8,r1)
	mov.l	@r4,r1
	add	#2,r1
	rts	
	mov.l	r1,@r4
.L299:
	.align 2
.L297:
	.long	1073741822
.L298:
	.long	1073741823
	.size	prim_two_dupe, .-prim_two_dupe
	.align 1
	.align 2
	.global	prim_emit
	.type	prim_emit, @function
prim_emit:
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L311
	add	#-8,r15
	mov	r4,r2
	add	#124,r2
	mov.l	@(24,r2),r3
	add	#-1,r0
	tst	r3,r3
	bt/s	.L310
	mov.l	r0,@r4
	mov.l	@(4,r4),r7
	shll2	r0
	mov	r15,r1
	add	#4,r1
	mov.l	@(r0,r7),r7
	mov	#0,r0
	mov	r1,r4
	mov.b	r0,@(5,r15)
	mov.b	r7,@r1
	jsr	@r3
	mov.l	r2,@r15
	mov.l	@r15,r2
	mov.l	@(44,r2),r1
	tst	r1,r1
	bt	.L310
	jsr	@r1
	nop
.L310:
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L311:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov.b	r0,@(0,r4)
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	nop
	.size	prim_emit, .-prim_emit
	.align 1
	.align 2
	.global	prim_fill
	.type	prim_fill, @function
prim_fill:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf/s	.L324
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r1,r7
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r2),r3
	add	#-2,r7
	add	r0,r2
	mov.l	r7,@r4
	mov	r2,r7
	add	#-4,r7
	mov.l	@r7,r7
	add	#-3,r1
	tst	r7,r7
	bt/s	.L323
	mov.l	r1,@r4
	mov.l	@(56,r4),r1
	cmp/hi	r7,r1
	bt	.L325
.L316:
	tst	r1,r1
	bt/s	.L323
	add	#-8,r2
	mov	r4,r7
	mov.l	@r2,r0
	add	#64,r7
	.align 2
.L318:
	mov.l	@(0,r7),r2
	dt	r1
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.b	r3,@(r0,r2)
	bf/s	.L318
	add	#1,r0
.L323:
	rts	
	nop
	.align 1
.L324:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L325:
	bra	.L316
	mov	r7,r1
	.size	prim_fill, .-prim_fill
	.align 1
	.align 2
	.global	prim_here
	.type	prim_here, @function
prim_here:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	mov.l	@(60,r4),r2
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_here, .-prim_here
	.align 1
	.align 2
	.global	prim_i
	.type	prim_i, @function
prim_i:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	mov.l	@(8,r4),r2
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_i, .-prim_i
	.align 1
	.align 2
	.global	prim_invert
	.type	prim_invert, @function
prim_invert:
	mov.l	@r4,r1
	mov.l	.L329,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r2
	not	r2,r2
	rts	
	mov.l	r2,@r1
.L330:
	.align 2
.L329:
	.long	1073741823
	.size	prim_invert, .-prim_invert
	.align 1
	.align 2
	.global	prim_j
	.type	prim_j, @function
prim_j:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	mov.l	@(12,r4),r2
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_j, .-prim_j
	.align 1
	.align 2
	.global	prim_key
	.type	prim_key, @function
prim_key:
	sts.l	pr,@-r15
	mov.l	@r4,r1
	add	#-8,r15
	tst	r1,r1
	bt/s	.L340
	mov	r4,r2
	mov.l	.L343,r3
	add	r3,r1
	mov.l	@(4,r4),r3
	shll2	r1
	add	r3,r1
	mov	r4,r3
	add	#124,r3
	mov.l	@(36,r3),r0
	tst	r0,r0
	bt/s	.L341
	mov	#-1,r4
	mov.l	@r1,r1
	mov.l	r2,@r15
	tst	r1,r1
	mov.l	r3,@(4,r15)
	jsr	@r0
	negc	r4,r4
	mov.l	@r15,r2
	mov	r0,r7
	mov.l	.L343,r1
	mov.l	@r2,r0
	mov.l	@(4,r15),r3
	add	r1,r0
	mov.l	@(4,r2),r1
	shll2	r0
	mov.l	r7,@(r0,r1)
	mov.l	@(48,r3),r1
	tst	r1,r1
	bt	.L339
	add	#8,r15
	jmp	@r1
	lds.l	@r15+,pr
	.align 1
.L340:
	mov	#10,r7
	mov	r4,r3
	add	#124,r3
	mov.l	r7,@(4,r3)
	add	#80,r2
	mov.b	r1,@r2
.L339:
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L341:
	mov.l	r0,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	nop
.L344:
	.align 2
.L343:
	.long	1073741823
	.size	prim_key, .-prim_key
	.align 1
	.align 2
	.global	prim_l_shift
	.type	prim_l_shift, @function
prim_l_shift:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	shld	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_l_shift, .-prim_l_shift
	.align 1
	.align 2
	.global	prim_max
	.type	prim_max, @function
prim_max:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	add	#-4,r0
	mov.l	@(r0,r1),r3
	cmp/gt	r3,r2
	bf	.L348
	mov.l	r2,@(r0,r1)
.L348:
	rts	
	nop
	.size	prim_max, .-prim_max
	.align 1
	.align 2
	.global	prim_min
	.type	prim_min, @function
prim_min:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	add	#-4,r0
	mov.l	@(r0,r1),r3
	cmp/ge	r3,r2
	bt	.L351
	mov.l	r2,@(r0,r1)
.L351:
	rts	
	nop
	.size	prim_min, .-prim_min
	.align 1
	.align 2
	.global	prim_mod
	.type	prim_mod, @function
prim_mod:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r3
	add	#-4,r0
	mov	r1,r2
	tst	r3,r3
	bt/s	.L358
	add	r0,r2
	sts.l	pr,@-r15
	mov.l	.L361,r0
	mov	r3,r5
	mov.l	@r2,r7
	jsr	@r0
	mov	r7,r4
	mul.l	r3,r0
	mov	r7,r3
	sts	macl,r1
	sub	r1,r3
	mov.l	r3,@r2
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L358:
	rts	
	mov.l	r3,@r2
.L362:
	.align 2
.L361:
	.long	__sdivsi3_i4i
	.size	prim_mod, .-prim_mod
	.align 1
	.align 2
	.global	prim_negate
	.type	prim_negate, @function
prim_negate:
	mov.l	@r4,r1
	mov.l	.L364,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r2
	neg	r2,r2
	rts	
	mov.l	r2,@r1
.L365:
	.align 2
.L364:
	.long	1073741823
	.size	prim_negate, .-prim_negate
	.align 1
	.align 2
	.global	prim_or
	.type	prim_or, @function
prim_or:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	or	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_or, .-prim_or
	.align 1
	.align 2
	.global	prim_over
	.type	prim_over, @function
prim_over:
	mov.l	@r4,r0
	mov.l	.L368,r2
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(8,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
.L369:
	.align 2
.L368:
	.long	1073741822
	.size	prim_over, .-prim_over
	.align 1
	.align 2
	.global	prim_two_over
	.type	prim_two_over, @function
prim_two_over:
	mov.l	@r4,r0
	mov.l	.L371,r2
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov.l	r2,@(16,r0)
	mov.l	@r4,r0
	mov.l	.L372,r2
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(16,r1)
	mov.l	@r4,r1
	add	#2,r1
	rts	
	mov.l	r1,@r4
.L373:
	.align 2
.L371:
	.long	1073741820
.L372:
	.long	1073741821
	.size	prim_two_over, .-prim_two_over
	.align 1
	.align 2
	.global	prim_page
	.type	prim_page, @function
prim_page:
	add	#124,r4
	mov.l	@(52,r4),r1
	tst	r1,r1
	bt	.L383
	sts.l	pr,@-r15
	add	#-4,r15
	jsr	@r1
	mov.l	r4,@r15
	mov.l	@r15,r4
	mov.l	@(44,r4),r1
	tst	r1,r1
	bt	.L381
	add	#4,r15
	jmp	@r1
	lds.l	@r15+,pr
	.align 1
.L381:
	add	#4,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L383:
	rts	
	nop
	.size	prim_page, .-prim_page
	.align 1
	.align 2
	.global	prim_rote
	.type	prim_rote, @function
prim_rote:
	mov.l	@r4,r1
	mov.l	.L387,r3
	mov.l	@(4,r4),r2
	add	r3,r1
	shll2	r1
	add	r2,r1
	mov	r1,r6
	add	#-8,r6
	mov.l	@r6,r6
	mov	r1,r3
	add	#-4,r3
	mov.l	@r1,r7
	mov.l	@r3,r3
	mov.l	r6,@r1
	mov.l	@r4,r0
	mov.l	.L388,r6
	mov.l	.L389,r1
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	add	r1,r0
	shll2	r0
	rts	
	mov.l	r3,@(r0,r2)
.L390:
	.align 2
.L387:
	.long	1073741823
.L388:
	.long	1073741822
.L389:
	.long	1073741821
	.size	prim_rote, .-prim_rote
	.align 1
	.align 2
	.global	prim_minus_rote
	.type	prim_minus_rote, @function
prim_minus_rote:
	mov.l	@r4,r1
	mov.l	.L392,r3
	mov.l	@(4,r4),r2
	add	r3,r1
	shll2	r1
	add	r2,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r6
	mov	r1,r7
	add	#-8,r7
	mov.l	@r1,r3
	mov.l	@r7,r7
	mov.l	r6,@r1
	mov.l	@r4,r0
	mov.l	.L393,r6
	mov.l	.L394,r1
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	add	r1,r0
	shll2	r0
	rts	
	mov.l	r3,@(r0,r2)
.L395:
	.align 2
.L392:
	.long	1073741823
.L393:
	.long	1073741822
.L394:
	.long	1073741821
	.size	prim_minus_rote, .-prim_minus_rote
	.align 1
	.align 2
	.global	prim_r_shift
	.type	prim_r_shift, @function
prim_r_shift:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	neg	r3,r3
	shad	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_r_shift, .-prim_r_shift
	.section	.rodata.str1.4
	.align 2
.LC1:
	.string	" "
	.text
	.align 1
	.align 2
	.global	prim_space
	.type	prim_space, @function
prim_space:
	mov	r4,r1
	add	#124,r1
	mov.l	@(24,r1),r2
	tst	r2,r2
	bt	.L406
	sts.l	pr,@-r15
	add	#-4,r15
	mov.l	.L409,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	@(44,r1),r1
	tst	r1,r1
	bt	.L404
	add	#4,r15
	jmp	@r1
	lds.l	@r15+,pr
	.align 1
.L404:
	add	#4,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L406:
	rts	
	nop
.L410:
	.align 2
.L409:
	.long	.LC1
	.size	prim_space, .-prim_space
	.align 1
	.align 2
	.global	prim_spaces
	.type	prim_spaces, @function
prim_spaces:
	mov.l	@r4,r0
	mov	#1,r1
	cmp/gt	r1,r0
	bf/s	.L430
	add	#-1,r0
	mov.l	@(4,r4),r1
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	cmp/pl	r2
	bf	.L427
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#124,r8
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@(24,r8),r1
	tst	r1,r1
	bt	.L425
	mov.l	@(56,r8),r10
	cmp/gt	r2,r10
	bt	.L431
.L416:
	cmp/pl	r10
	bf	.L417
	bra	.L418
	mov	#0,r9
	.align 1
.L432:
	mov.l	@(24,r8),r1
.L418:
	mov.l	.L433,r4
	jsr	@r1
	add	#1,r9
	cmp/eq	r9,r10
	bf	.L432
.L417:
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L425
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L427:
	rts	
	nop
	.align 1
.L425:
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L430:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L431:
	bra	.L416
	mov	r2,r10
.L434:
	.align 2
.L433:
	.long	.LC1
	.size	prim_spaces, .-prim_spaces
	.align 1
	.align 2
	.global	prim_swap
	.type	prim_swap, @function
prim_swap:
	mov.l	@r4,r1
	mov.l	.L436,r3
	mov.l	@(4,r4),r2
	add	r3,r1
	shll2	r1
	add	r2,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r7
	mov.l	@r1,r3
	mov.l	r7,@r1
	mov.l	@r4,r0
	mov.l	.L437,r1
	add	r1,r0
	shll2	r0
	rts	
	mov.l	r3,@(r0,r2)
.L438:
	.align 2
.L436:
	.long	1073741823
.L437:
	.long	1073741822
	.size	prim_swap, .-prim_swap
	.align 1
	.align 2
	.global	prim_two_swap
	.type	prim_two_swap, @function
prim_two_swap:
	mov.l	@r4,r1
	mov.l	.L440,r0
	mov.l	@(4,r4),r2
	add	r0,r1
	shll2	r1
	add	r2,r1
	mov	r1,r6
	add	#-8,r6
	mov.l	@r6,r5
	mov	r1,r3
	mov	r1,r6
	add	#-4,r3
	add	#-12,r6
	mov.l	@r1,r7
	mov.l	@r6,r6
	mov.l	@r3,r3
	mov.l	r5,@r1
	mov.l	@r4,r0
	mov.l	.L441,r1
	mov.l	.L442,r5
	add	r1,r0
	shll2	r0
	mov.l	r6,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L443,r6
	add	r5,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	add	r6,r0
	shll2	r0
	rts	
	mov.l	r3,@(r0,r2)
.L444:
	.align 2
.L440:
	.long	1073741823
.L441:
	.long	1073741822
.L442:
	.long	1073741821
.L443:
	.long	1073741820
	.size	prim_two_swap, .-prim_two_swap
	.align 1
	.align 2
	.global	prim_type
	.type	prim_type, @function
prim_type:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov	r4,r13
	mov.l	r14,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L463
	add	#-4,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r12
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r12
	mov.l	@(r0,r2),r3
	mov.l	r1,@r4
	mov.l	@(24,r12),r1
	tst	r1,r1
	bt/s	.L461
	add	r0,r2
	mov.l	@(56,r4),r11
	add	#-4,r2
	cmp/hi	r3,r11
	bt/s	.L464
	mov.l	@r2,r8
	mov	#0,r0
	tst	r11,r11
	bt/s	.L449
	mov.b	r0,@(1,r15)
.L466:
	mov	r13,r14
	mov	#0,r9
	bra	.L450
	add	#64,r14
	.align 1
.L465:
	mov.l	@(24,r12),r1
	add	#1,r8
.L450:
	mov.l	@(0,r14),r2
	mov	r15,r4
	add	#1,r9
	and	r2,r8
	mov.l	@(52,r13),r2
	mov	r8,r0
	mov.b	@(r0,r2),r2
	jsr	@r1
	mov.b	r2,@r15
	cmp/eq	r9,r11
	bf	.L465
.L449:
	mov.l	@(44,r12),r1
.L467:
	tst	r1,r1
	bt	.L461
	jsr	@r1
	nop
.L461:
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L464:
	mov	#0,r0
	mov	r3,r11
	tst	r11,r11
	bf/s	.L466
	mov.b	r0,@(1,r15)
	bra	.L467
	mov.l	@(44,r12),r1
	.align 1
.L463:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r13
	mov	#0,r1
	mov.b	r1,@r13
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.size	prim_type, .-prim_type
	.align 1
	.align 2
	.global	prim_u_less_than
	.type	prim_u_less_than, @function
prim_u_less_than:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	cmp/hi	r2,r3
	subc	r2,r2
	rts	
	mov.l	r2,@r1
	.size	prim_u_less_than, .-prim_u_less_than
	.align 1
	.align 2
	.global	prim_u_greater_than
	.type	prim_u_greater_than, @function
prim_u_greater_than:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r2
	mov.l	@r1,r3
	cmp/hi	r2,r3
	subc	r2,r2
	rts	
	mov.l	r2,@r1
	.size	prim_u_greater_than, .-prim_u_greater_than
	.align 1
	.align 2
	.global	prim_x_or
	.type	prim_x_or, @function
prim_x_or:
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	xor	r3,r2
	rts	
	mov.l	r2,@r1
	.size	prim_x_or, .-prim_x_or
	.align 1
	.align 2
	.global	prim_not_equals
	.type	prim_not_equals, @function
prim_not_equals:
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	cmp/eq	r2,r3
	subc	r2,r2
	not	r2,r2
	rts	
	mov.l	r2,@r1
	.size	prim_not_equals, .-prim_not_equals
	.align 1
	.align 2
	.global	prim_false
	.type	prim_false, @function
prim_false:
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	shll2	r2
	add	r2,r1
	mov	#0,r2
	mov.l	r2,@r1
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_false, .-prim_false
	.align 1
	.align 2
	.global	prim_nip
	.type	prim_nip, @function
prim_nip:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	add	#-4,r1
	rts	
	mov.l	r2,@r1
	.size	prim_nip, .-prim_nip
	.align 1
	.align 2
	.global	prim_tuck
	.type	prim_tuck, @function
prim_tuck:
	mov.l	@r4,r0
	mov.l	.L476,r2
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L476,r7
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov	r0,r3
	add	#-4,r3
	mov.l	@r3,r3
	mov.l	r2,@(4,r0)
	mov.l	@r4,r0
	add	r7,r0
	shll2	r0
	mov.l	r3,@(r0,r1)
	mov.l	@r4,r0
	mov.l	.L477,r3
	add	r3,r0
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
.L478:
	.align 2
.L476:
	.long	1073741823
.L477:
	.long	1073741822
	.size	prim_tuck, .-prim_tuck
	.align 1
	.align 2
	.global	prim_unused
	.type	prim_unused, @function
prim_unused:
	mov.l	@r4,r0
	mov.w	.L484,r1
	cmp/gt	r1,r0
	bt/s	.L483
	shll2	r0
	mov.l	@(56,r4),r1
	mov.l	@(60,r4),r3
	mov.l	@(4,r4),r2
	sub	r3,r1
	mov.l	r1,@(r0,r2)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.align 1
.L483:
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L484:
	.short	255
	.size	prim_unused, .-prim_unused
	.align 1
	.align 2
	.global	prim_within
	.type	prim_within, @function
prim_within:
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r2
	shll2	r0
	mov.l	@(r0,r1),r7
	mov.l	r2,@r4
	mov	r0,r2
	add	#-8,r2
	add	r1,r2
	add	r0,r1
	mov.l	@r2,r3
	add	#-4,r1
	mov.l	@r1,r1
	cmp/ge	r1,r3
	movt	r1
	cmp/ge	r3,r7
	movt	r3
	and	r3,r1
	neg	r1,r1
	rts	
	mov.l	r1,@r2
	.size	prim_within, .-prim_within
	.align 1
	.align 2
	.global	prim_bye
	.type	prim_bye, @function
prim_bye:
	add	#80,r4
	mov	#1,r0
	mov	#0,r1
	mov.b	r0,@(1,r4)
	mov.b	r1,@r4
	rts	
	nop
	.size	prim_bye, .-prim_bye
	.align 1
	.align 2
	.global	prim_reset
	.type	prim_reset, @function
prim_reset:
	mov	#0,r1
	rts	
	mov.l	r1,@r4
	.size	prim_reset, .-prim_reset
	.align 1
	.align 2
	.global	prim_walign
	.type	prim_walign, @function
prim_walign:
	mov.l	@(60,r4),r1
	mov	r4,r2
	add	#64,r2
	mov.l	@(4,r2),r2
	add	#1,r1
	and	r2,r1
	mov	#-2,r2
	and	r2,r1
	rts	
	mov.l	r1,@(60,r4)
	.size	prim_walign, .-prim_walign
	.align 1
	.align 2
	.global	prim_waligned
	.type	prim_waligned, @function
prim_waligned:
	mov.l	@r4,r1
	mov.l	.L490,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r1,r2
	mov.l	@r2,r1
	add	#64,r4
	mov.l	@(4,r4),r3
	add	#1,r1
	and	r3,r1
	mov	#-2,r3
	and	r3,r1
	rts	
	mov.l	r1,@r2
.L491:
	.align 2
.L490:
	.long	1073741823
	.size	prim_waligned, .-prim_waligned
	.align 1
	.align 2
	.global	prim_printable
	.type	prim_printable, @function
prim_printable:
	mov.l	@r4,r1
	mov.l	.L499,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	add	#124,r4
	mov.l	@(40,r4),r0
	shll2	r1
	tst	r0,r0
	bt/s	.L494
	add	r2,r1
	sts.l	pr,@-r15
	add	#-4,r15
	mov.l	@r1,r4
	jsr	@r0
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	r0,@r1
	add	#4,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L494:
	mov	#0,r0
	rts	
	mov.l	r0,@r1
.L500:
	.align 2
.L499:
	.long	1073741823
	.size	prim_printable, .-prim_printable
	.align 1
	.align 2
	.global	prim_erase
	.type	prim_erase, @function
prim_erase:
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	mov	r1,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	mov.l	@(r0,r2),r3
	mov.l	r1,@r4
	mov.l	@(56,r4),r1
	cmp/hi	r3,r1
	bf	.L502
	mov	r3,r1
.L502:
	tst	r1,r1
	bt/s	.L509
	add	r0,r2
	mov	r4,r7
	add	#-4,r2
	mov.l	@r2,r0
	add	#64,r7
	mov	#0,r3
	.align 2
.L504:
	mov.l	@(0,r7),r2
	dt	r1
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.b	r3,@(r0,r2)
	bf/s	.L504
	add	#1,r0
.L509:
	rts	
	nop
	.size	prim_erase, .-prim_erase
	.align 1
	.align 2
	.global	prim_cxt
	.type	prim_cxt, @function
prim_cxt:
	mov.l	.L514,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r0
	tst	#128,r0
	bt/s	.L512
	extu.b	r0,r2
	mov.w	.L515,r2
	or	r0,r2
.L512:
	rts	
	mov.l	r2,@r1
	.align 1
.L515:
	.short	-256
.L516:
	.align 2
.L514:
	.long	1073741823
	.size	prim_cxt, .-prim_cxt
	.align 1
	.align 2
	.global	prim_wxt
	.type	prim_wxt, @function
prim_wxt:
	mov.l	.L521,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	.L522,r2
	mov.l	@r1,r3
	tst	r2,r3
	bt/s	.L519
	extu.w	r3,r2
	mov.l	.L523,r2
	or	r3,r2
.L519:
	rts	
	mov.l	r2,@r1
.L524:
	.align 2
.L521:
	.long	1073741823
.L522:
	.long	32768
.L523:
	.long	-65536
	.size	prim_wxt, .-prim_wxt
	.align 1
	.align 2
	.global	prim_perf
	.type	prim_perf, @function
prim_perf:
	mov.l	@r4,r0
	mov.w	.L530,r1
	cmp/gt	r1,r0
	bt/s	.L529
	mov	r4,r2
	add	#64,r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(52,r2),r2
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.align 1
.L529:
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L530:
	.short	255
	.size	prim_perf, .-prim_perf
	.align 1
	.align 2
	.global	prim_size
	.type	prim_size, @function
prim_size:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	mov.l	@(56,r4),r2
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_size, .-prim_size
	.section	.rodata.str1.4
	.align 2
.LC2:
	.string	"prim_hidden_dot_quote"
	.align 2
.LC3:
	.string	"engine->address: %p\n"
	.align 2
.LC4:
	.string	"length address: %p\n"
	.align 2
.LC5:
	.string	"quote_length: %u\n"
	.align 2
.LC6:
	.string	"text: %p\n"
	.align 2
.LC7:
	.string	"character: %c (%d)\n"
	.align 2
.LC8:
	.string	"printed: %s\n"
	.align 2
.LC9:
	.string	"text after printing: %p\n"
	.align 2
.LC10:
	.string	"ptr_size: %u\n"
	.align 2
.LC11:
	.string	"new text: %p\n"
	.align 2
.LC12:
	.string	"new engine->address: %p\n"
	.text
	.align 1
	.align 2
	.global	prim_hidden_dot_quote
	.type	prim_hidden_dot_quote, @function
prim_hidden_dot_quote:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov	r4,r11
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15
	mov	r4,r14
	sts.l	pr,@-r15
	add	#64,r14
	mov.l	.L548,r1
	mov.l	@(12,r14),r10
	add	#-8,r15
	mov.l	.L549,r5
	mov	#16,r4
	mov.l	@(4,r10),r2
	mov	r10,r13
	mov.l	.L550,r8
	add	#8,r13
	mov.l	r2,@r15
	jsr	@r1
	mov	r15,r9
	mov.l	@(12,r14),r5
	mov.l	.L551,r4
	jsr	@r8
	add	#4,r9
	mov.l	@(12,r14),r5
	mov.l	.L552,r4
	jsr	@r8
	add	#4,r5
	mov.l	.L553,r4
	jsr	@r8
	mov.l	@r15,r5
	mov.l	.L554,r4
	jsr	@r8
	mov	r13,r5
	mov.l	@r15,r1
	mov	#0,r0
	tst	r1,r1
	bt/s	.L547
	mov.b	r0,@(1,r9)
	mov.l	@r15,r2
	add	#124,r11
	mov	r13,r12
	add	r2,r10
	add	#8,r10
	.align 2
.L535:
	mov.b	@r12+,r5
	mov.l	.L555,r4
	jsr	@r8
	mov	r5,r6
	mov.l	@(24,r11),r2
	tst	r2,r2
	bt/s	.L534
	mov	r12,r0
	add	#-16,r0
	mov.b	@(15,r0),r0
	mov	r9,r4
	jsr	@r2
	mov.b	r0,@r9
	mov.l	.L556,r4
	jsr	@r8
	mov	r9,r5
.L534:
	cmp/eq	r12,r10
	bf/s	.L535
	mov.l	@r15,r2
	add	r2,r13
.L533:
	mov.l	@(44,r11),r1
	tst	r1,r1
	bt	.L536
	jsr	@r1
	nop
.L536:
	mov.l	.L557,r4
	jsr	@r8
	mov	r13,r5
	mov.l	@r15,r1
	mov	#4,r5
	mov.l	.L558,r4
	neg	r1,r0
	and	#3,r0
	add	r0,r13
	mov	r13,r1
	add	#-4,r1
	jsr	@r8
	mov.l	r1,@(12,r14)
	mov.l	.L559,r4
	jsr	@r8
	mov	r13,r5
	mov.l	.L560,r4
	jsr	@r8
	mov.l	@(12,r14),r5
	mov.l	.L561,r1
	jsr	@r1
	nop
	add	#8,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L547:
	bra	.L533
	add	#124,r11
.L562:
	.align 2
.L548:
	.long	log_push
.L549:
	.long	.LC2
.L550:
	.long	log_text
.L551:
	.long	.LC3
.L552:
	.long	.LC4
.L553:
	.long	.LC5
.L554:
	.long	.LC6
.L555:
	.long	.LC7
.L556:
	.long	.LC8
.L557:
	.long	.LC9
.L558:
	.long	.LC10
.L559:
	.long	.LC11
.L560:
	.long	.LC12
.L561:
	.long	log_pop
	.size	prim_hidden_dot_quote, .-prim_hidden_dot_quote
	.section	.rodata.str1.4
	.align 2
.LC13:
	.string	"allot"
	.align 2
.LC14:
	.string	"data_index: %d\n"
	.align 2
.LC15:
	.string	"new data_index: %d\n"
	.text
	.align 1
	.align 2
	.global	prim_allot
	.type	prim_allot, @function
prim_allot:
	mov.l	.L569,r1
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	.L570,r5
	sts.l	pr,@-r15
	jsr	@r1
	mov	#11,r4
	mov.l	.L571,r9
	mov.l	.L572,r4
	jsr	@r9
	mov.l	@(60,r8),r5
	mov.l	@r8,r0
	tst	r0,r0
	bf/s	.L564
	mov	#10,r2
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L564:
	mov.l	@(4,r8),r1
	add	#-1,r0
	mov.l	r0,@r8
	shll2	r0
	mov.l	@(r0,r1),r5
	mov.l	@(60,r8),r1
	mov.l	.L573,r4
	add	r1,r5
	mov	r8,r1
	add	#64,r1
	mov.l	@(0,r1),r1
	and	r1,r5
	jsr	@r9
	mov.l	r5,@(60,r8)
	mov.l	.L574,r1
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L575:
	.align 2
.L569:
	.long	log_push
.L570:
	.long	.LC13
.L571:
	.long	log_text
.L572:
	.long	.LC14
.L573:
	.long	.LC15
.L574:
	.long	log_pop
	.size	prim_allot, .-prim_allot
	.align 1
	.align 2
	.global	prim_dot
	.type	prim_dot, @function
prim_dot:
	mov.l	r8,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L587
	add	#-12,r15
	mov	r4,r8
	add	#124,r8
	mov.l	@(24,r8),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L586
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(r0,r1),r4
	mov.l	.L588,r1
	jsr	@r1
	mov	r15,r5
	mov.l	@(24,r8),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(24,r8),r1
	mov.l	.L589,r4
	jsr	@r1
	nop
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L586
	jsr	@r1
	nop
.L586:
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L587:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov.b	r0,@(0,r4)
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L590:
	.align 2
.L588:
	.long	text_int32
.L589:
	.long	.LC1
	.size	prim_dot, .-prim_dot
	.align 1
	.align 2
	.global	prim_question
	.type	prim_question, @function
prim_question:
	mov.l	r8,@-r15
	mov	r4,r8
	sts.l	pr,@-r15
	add	#124,r8
	mov.l	@r4,r0
	mov.l	@(24,r8),r1
	add	#-12,r15
	add	#-1,r0
	tst	r1,r1
	bt/s	.L600
	mov.l	r0,@r4
	mov.l	@(4,r4),r2
	mov	r4,r1
	shll2	r0
	add	#64,r1
	mov.l	@(r0,r2),r0
	mov.l	@(8,r1),r1
	and	r1,r0
	mov.l	@(52,r4),r1
	mov.l	@(r0,r1),r4
	mov.l	.L601,r1
	jsr	@r1
	mov	r15,r5
	mov.l	@(24,r8),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(24,r8),r1
	mov.l	.L602,r4
	jsr	@r1
	nop
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L600
	jsr	@r1
	nop
.L600:
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L603:
	.align 2
.L601:
	.long	text_int32
.L602:
	.long	.LC1
	.size	prim_question, .-prim_question
	.align 1
	.align 2
	.global	prim_u_dot
	.type	prim_u_dot, @function
prim_u_dot:
	mov.l	r8,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L615
	add	#-12,r15
	mov	r4,r8
	add	#124,r8
	mov.l	@(24,r8),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L614
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(r0,r1),r4
	mov.l	.L616,r1
	jsr	@r1
	mov	r15,r5
	mov.l	@(24,r8),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(24,r8),r1
	mov.l	.L617,r4
	jsr	@r1
	nop
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L614
	jsr	@r1
	nop
.L614:
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L615:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov.b	r0,@(0,r4)
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L618:
	.align 2
.L616:
	.long	text_uint32
.L617:
	.long	.LC1
	.size	prim_u_dot, .-prim_u_dot
	.align 1
	.align 2
	.global	prim_execute
	.type	prim_execute, @function
prim_execute:
	mov.l	@r4,r2
	tst	r2,r2
	bt/s	.L633
	mov	r4,r1
	mov.l	@(4,r4),r3
	add	#-1,r2
	mov.l	r2,@r4
	shll2	r2
	add	r3,r2
	mov.w	.L636,r3
	mov.l	@r2,r4
	cmp/hi	r3,r4
	bt/s	.L622
	mov	r1,r7
	mov.l	.L637,r2
	mov	#5,r6
	shld	r6,r4
	add	r4,r2
	mov.l	@(16,r2),r3
	tst	r3,r3
	bt/s	.L623
	add	#124,r7
	jmp	@r3
	mov	r1,r4
	.align 1
.L622:
	add	#64,r7
	mov.l	@(32,r7),r3
	mov.w	.L638,r5
	add	r5,r3
	cmp/hi	r4,r3
	bf/s	.L624
	mov	#5,r3
	mov.w	.L639,r6
	add	r6,r4
	shld	r3,r4
	mov.l	@(24,r7),r3
	add	r4,r3
	mov	r3,r0
	add	#16,r0
	mov.b	@(12,r0),r0
	extu.b	r0,r0
	cmp/eq	#4,r0
	bt/s	.L634
	add	#-1,r0
	extu.b	r0,r0
	mov	#2,r6
	cmp/hi	r6,r0
	bt	.L626
	mov.l	@r3,r3
	mov.l	@(4,r3),r3
	mov.l	r3,@r2
	mov.l	@r1,r2
	add	#1,r2
	rts	
	mov.l	r2,@r1
	.align 1
.L633:
	mov	#10,r7
	mov	r4,r3
	add	#124,r3
	mov.l	r7,@(4,r3)
	add	#80,r1
	mov.b	r2,@r1
	rts	
	nop
	.align 1
.L634:
	mov.l	@(20,r3),r3
	mov	r1,r2
	mov	#9,r7
	add	#124,r2
	mov.l	r7,@(4,r2)
	add	#80,r1
	mov.l	r3,@(20,r2)
	mov	#0,r2
	mov.b	r2,@r1
	rts	
	nop
	.align 1
.L624:
	sts.l	pr,@-r15
	mov.l	.L640,r2
	add	#-4,r15
	mov.w	.L641,r5
	mov.l	r1,@r15
	jsr	@r2
	add	r1,r5
	mov.l	@r15,r1
	mov	#1,r3
	mov	r1,r2
	add	#124,r2
	mov.l	r3,@(4,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#4,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L623:
	mov.l	@r2,r2
	mov	#2,r6
	mov.l	r6,@(4,r7)
	add	#80,r1
	mov.l	r2,@(20,r7)
	mov.b	r3,@r1
	rts	
	nop
	.align 1
.L626:
	mov.l	@(24,r1),r2
	mov.l	@(20,r1),r6
	cmp/hs	r6,r2
	bf/s	.L635
	mov	#1,r0
	mov.l	@(20,r7),r6
	mov.l	@(28,r7),r5
	add	#1,r6
	mov.l	r6,@(20,r7)
	mov.l	@(12,r7),r6
	mov.b	r0,@(14,r2)
	sub	r5,r6
	mov.w	@(26,r3),r0
	mov.l	r6,@r2
	mov.l	@(20,r7),r6
	mov.l	@(24,r1),r2
	mov.l	@(32,r1),r5
	mov.l	r6,@(8,r2)
	mov.w	r0,@(12,r2)
	extu.w	r0,r0
	mov.l	@(36,r1),r6
	shll2	r0
	sub	r0,r6
	cmp/hs	r5,r6
	bt/s	.L628
	mov.l	r6,@(36,r1)
	mov	#5,r5
	mov	r1,r6
	add	#124,r6
	mov.l	r5,@(4,r6)
	mov	#0,r5
	mov	r1,r6
	add	#80,r6
	mov.b	r5,@r6
.L628:
	add	#-16,r2
	mov.l	r2,@(24,r1)
	mov.l	@r3,r1
	add	#-4,r1
	rts	
	mov.l	r1,@(12,r7)
	.align 1
.L635:
	mov	r1,r2
	mov	#7,r3
	add	#124,r2
	mov.l	r3,@(4,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	rts	
	nop
	.align 1
.L636:
	.short	150
.L638:
	.short	151
.L639:
	.short	-151
.L641:
	.short	132
.L642:
	.align 2
.L637:
	.long	forth_primitives
.L640:
	.long	text_uint32
	.size	prim_execute, .-prim_execute
	.align 1
	.align 2
	.global	prim_x_dot
	.type	prim_x_dot, @function
prim_x_dot:
	mov.l	r8,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L654
	add	#-12,r15
	mov	r4,r8
	add	#124,r8
	mov.l	@(24,r8),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L653
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(r0,r1),r4
	mov.l	.L655,r1
	jsr	@r1
	mov	r15,r5
	mov.l	@(24,r8),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(24,r8),r1
	mov.l	.L656,r4
	jsr	@r1
	nop
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L653
	jsr	@r1
	nop
.L653:
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L654:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov.b	r0,@(0,r4)
	add	#12,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L657:
	.align 2
.L655:
	.long	text_hex32
.L656:
	.long	.LC1
	.size	prim_x_dot, .-prim_x_dot
	.align 1
	.align 2
	.global	prim_number_to
	.type	prim_number_to, @function
prim_number_to:
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov	#1,r1
	add	#-24,r15
	cmp/gt	r1,r0
	bf/s	.L681
	mov	r4,r2
	mov.l	@(4,r4),r7
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r7),r3
	add	r0,r7
	add	#-4,r7
	mov	r15,r1
	mov.l	@r7,r4
	add	#12,r1
	mov.l	.L682,r7
	mov	r1,r5
	mov.l	r1,@(4,r15)
	mov.l	r2,@r15
	jsr	@r7
	mov.l	r3,@(8,r15)
	mov.l	@(8,r15),r3
	mov	#0,r5
	mov.l	@r15,r2
	mov.l	@(4,r15),r1
	mov	r1,r7
.L663:
	mov.l	@r7+,r6
	cmp/str	r5,r6
	bf	.L663
	add	#-4,r7
	mov.b	@r7+,r6
	tst	r6,r6
	bt	.L661
	mov.b	@r7+,r6
	tst	r6,r6
	bt	.L661
	mov.b	@r7+,r6
	tst	r6,r6
	mov	#-1,r6
	subc	r6,r7
.L661:
	sett
	mov	r7,r6
	subc	r1,r6
	tst	r6,r6
	bt	.L665
	mov	r2,r4
	add	#64,r4
	mov	r1,r5
	mov	r6,r1
	.align 2
.L666:
	mov.l	@(0,r4),r0
	dt	r1
	mov.b	@r5+,r7
	and	r3,r0
	mov.l	@(52,r2),r3
	mov.b	r7,@(r0,r3)
	mov	r0,r3
	bf/s	.L666
	add	#1,r3
.L665:
	mov.l	@r2,r0
	mov.l	.L683,r1
	add	r1,r0
	mov.l	@(4,r2),r1
	shll2	r0
	mov.l	r6,@(r0,r1)
	add	#24,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L681:
	mov	#10,r3
	mov	r4,r1
	add	#124,r1
	mov.l	r3,@(4,r1)
	add	#80,r2
	mov	#0,r1
	mov.b	r1,@r2
	add	#24,r15
	lds.l	@r15+,pr
	rts	
	nop
.L684:
	.align 2
.L682:
	.long	text_int32
.L683:
	.long	1073741823
	.size	prim_number_to, .-prim_number_to
	.align 1
	.align 2
	.global	prim_hex_to
	.type	prim_hex_to, @function
prim_hex_to:
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov	#1,r1
	add	#-24,r15
	cmp/gt	r1,r0
	bf/s	.L708
	mov	r4,r2
	mov.l	@(4,r4),r7
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r7),r3
	add	r0,r7
	add	#-4,r7
	mov	r15,r1
	mov.l	@r7,r4
	add	#12,r1
	mov.l	.L709,r7
	mov	r1,r5
	mov.l	r1,@(4,r15)
	mov.l	r2,@r15
	jsr	@r7
	mov.l	r3,@(8,r15)
	mov.l	@(8,r15),r3
	mov	#0,r5
	mov.l	@r15,r2
	mov.l	@(4,r15),r1
	mov	r1,r7
.L690:
	mov.l	@r7+,r6
	cmp/str	r5,r6
	bf	.L690
	add	#-4,r7
	mov.b	@r7+,r6
	tst	r6,r6
	bt	.L688
	mov.b	@r7+,r6
	tst	r6,r6
	bt	.L688
	mov.b	@r7+,r6
	tst	r6,r6
	mov	#-1,r6
	subc	r6,r7
.L688:
	sett
	mov	r7,r6
	subc	r1,r6
	tst	r6,r6
	bt	.L692
	mov	r2,r4
	add	#64,r4
	mov	r1,r5
	mov	r6,r1
	.align 2
.L693:
	mov.l	@(0,r4),r0
	dt	r1
	mov.b	@r5+,r7
	and	r3,r0
	mov.l	@(52,r2),r3
	mov.b	r7,@(r0,r3)
	mov	r0,r3
	bf/s	.L693
	add	#1,r3
.L692:
	mov.l	@r2,r0
	mov.l	.L710,r1
	add	r1,r0
	mov.l	@(4,r2),r1
	shll2	r0
	mov.l	r6,@(r0,r1)
	add	#24,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L708:
	mov	#10,r3
	mov	r4,r1
	add	#124,r1
	mov.l	r3,@(4,r1)
	add	#80,r2
	mov	#0,r1
	mov.b	r1,@r2
	add	#24,r15
	lds.l	@r15+,pr
	rts	
	nop
.L711:
	.align 2
.L709:
	.long	text_hex32
.L710:
	.long	1073741823
	.size	prim_hex_to, .-prim_hex_to
	.align 1
	.align 2
	.global	prim_dot_r
	.type	prim_dot_r, @function
prim_dot_r:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L739
	add	#-16,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r8
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r8
	mov.l	@(r0,r2),r10
	mov.l	r1,@r4
	mov.l	@(24,r8),r1
	tst	r1,r1
	bt/s	.L738
	add	r0,r2
	mov.l	.L740,r1
	add	#-4,r2
	mov	r15,r3
	add	#4,r3
	mov.l	@r2,r4
	mov.l	r3,@r15
	jsr	@r1
	mov	r3,r5
	mov	r15,r1
	mov	#0,r3
	add	#4,r1
.L717:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L717
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L715
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L715
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L715:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r10,r1
	bt/s	.L722
	cmp/eq	r10,r1
	bt	.L722
	sub	r1,r10
	mov.w	.L741,r1
	cmp/hi	r1,r10
	bf	.L723
	mov	r1,r10
.L723:
	mov.l	.L742,r11
	mov	#0,r9
	.align 2
.L724:
	mov.l	@(24,r8),r1
	mov	r11,r4
	jsr	@r1
	add	#1,r9
	cmp/hi	r9,r10
	bt	.L724
.L722:
	mov.l	@(24,r8),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L738
	jsr	@r1
	nop
.L738:
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L739:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L741:
	.short	1500
.L743:
	.align 2
.L740:
	.long	text_int32
.L742:
	.long	.LC1
	.size	prim_dot_r, .-prim_dot_r
	.align 1
	.align 2
	.global	prim_u_dot_r
	.type	prim_u_dot_r, @function
prim_u_dot_r:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L771
	add	#-16,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r8
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r8
	mov.l	@(r0,r2),r10
	mov.l	r1,@r4
	mov.l	@(24,r8),r1
	tst	r1,r1
	bt/s	.L770
	add	r0,r2
	mov.l	.L772,r1
	add	#-4,r2
	mov	r15,r3
	add	#4,r3
	mov.l	@r2,r4
	mov.l	r3,@r15
	jsr	@r1
	mov	r3,r5
	mov	r15,r1
	mov	#0,r3
	add	#4,r1
.L749:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L749
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L747
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L747
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L747:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r10,r1
	bt/s	.L754
	cmp/eq	r10,r1
	bt	.L754
	sub	r1,r10
	mov.w	.L773,r1
	cmp/hi	r1,r10
	bf	.L755
	mov	r1,r10
.L755:
	mov.l	.L774,r11
	mov	#0,r9
	.align 2
.L756:
	mov.l	@(24,r8),r1
	mov	r11,r4
	jsr	@r1
	add	#1,r9
	cmp/hi	r9,r10
	bt	.L756
.L754:
	mov.l	@(24,r8),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L770
	jsr	@r1
	nop
.L770:
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L771:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L773:
	.short	1500
.L775:
	.align 2
.L772:
	.long	text_uint32
.L774:
	.long	.LC1
	.size	prim_u_dot_r, .-prim_u_dot_r
	.align 1
	.align 2
	.global	prim_x_dot_r
	.type	prim_x_dot_r, @function
prim_x_dot_r:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L803
	add	#-16,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r8
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r8
	mov.l	@(r0,r2),r10
	mov.l	r1,@r4
	mov.l	@(24,r8),r1
	tst	r1,r1
	bt/s	.L802
	add	r0,r2
	mov.l	.L804,r1
	add	#-4,r2
	mov	r15,r3
	add	#4,r3
	mov.l	@r2,r4
	mov.l	r3,@r15
	jsr	@r1
	mov	r3,r5
	mov	r15,r1
	mov	#0,r3
	add	#4,r1
.L781:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L781
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L779
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L779
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L779:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r10,r1
	bt/s	.L786
	cmp/eq	r10,r1
	bt	.L786
	sub	r1,r10
	mov.w	.L805,r1
	cmp/hi	r1,r10
	bf	.L787
	mov	r1,r10
.L787:
	mov.l	.L806,r11
	mov	#0,r9
	.align 2
.L788:
	mov.l	@(24,r8),r1
	mov	r11,r4
	jsr	@r1
	add	#1,r9
	cmp/hi	r9,r10
	bt	.L788
.L786:
	mov.l	@(24,r8),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(44,r8),r1
	tst	r1,r1
	bt	.L802
	jsr	@r1
	nop
.L802:
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L803:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L805:
	.short	1500
.L807:
	.align 2
.L804:
	.long	text_hex32
.L806:
	.long	.LC1
	.size	prim_x_dot_r, .-prim_x_dot_r
	.align 1
	.align 2
	.global	prim_depth
	.type	prim_depth, @function
prim_depth:
	mov.l	@r4,r2
	mov	r4,r1
	mov.w	.L812,r3
	sts.l	pr,@-r15
	cmp/gt	r3,r2
	bf/s	.L809
	add	#-8,r15
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(4,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L809:
	mov.l	@(4,r4),r3
	shll2	r2
	mov.l	.L813,r0
	add	r3,r2
	mov.l	r4,@r15
	jsr	@r0
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	@r15,r1
	mov.l	r0,@r2
	mov.l	@r1,r2
	add	#1,r2
	mov.l	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	nop
	.align 1
.L812:
	.short	255
.L814:
	.align 2
.L813:
	.long	forth_stack_count
	.size	prim_depth, .-prim_depth
	.align 1
	.align 2
	.global	prim_move
	.type	prim_move, @function
prim_move:
	mov.l	r8,@-r15
	mov	#2,r2
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L837
	mov	r4,r13
	mov.l	@(4,r4),r2
	mov	r1,r0
	add	#-1,r0
	mov	r1,r7
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r2),r3
	add	#-2,r7
	add	r0,r2
	mov.l	r7,@r4
	add	#-3,r1
	mov	r2,r7
	add	#-4,r7
	mov.l	@r7,r11
	mov.l	r1,@r4
	mov.l	@(56,r4),r1
	cmp/hi	r3,r1
	bt/s	.L838
	mov	r1,r12
.L818:
	tst	r12,r12
	bt/s	.L835
	mov	r13,r14
	add	#64,r14
	mov.l	@(0,r14),r9
	add	#-8,r2
	mov.l	@r2,r8
	and	r9,r11
	mov.l	.L841,r10
	mov	r11,r2
	add	r12,r2
	and	r8,r9
	cmp/hi	r1,r2
	mov	r9,r3
	bf/s	.L820
	add	r12,r3
	.align 2
.L839:
	cmp/hs	r3,r1
	mov	r1,r2
	mov	r12,r8
	bf/s	.L824
	sub	r11,r2
.L821:
	cmp/hi	r2,r8
	bf	.L822
	mov	r2,r8
.L822:
	mov.l	@(52,r13),r4
	mov	r8,r6
	sub	r8,r12
	mov	r4,r5
	add	r11,r4
	jsr	@r10
	add	r9,r5
	tst	r12,r12
	add	r8,r11
	bt/s	.L835
	add	r9,r8
	mov.l	@(0,r14),r9
	mov.l	@(56,r13),r1
	and	r9,r11
	mov	r11,r2
	add	r12,r2
	and	r8,r9
	cmp/hi	r1,r2
	mov	r9,r3
	bt/s	.L839
	add	r12,r3
.L820:
	cmp/hs	r3,r1
	bt/s	.L840
	mov	r12,r2
.L824:
	mov	r1,r8
	bra	.L821
	sub	r9,r8
	.align 1
.L840:
	mov.l	@(52,r13),r4
	mov	r12,r6
	mov	r10,r1
	mov	r4,r5
	add	r11,r4
	add	r9,r5
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L838:
	bra	.L818
	mov	r3,r12
	.align 1
.L837:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r13
	mov	#0,r1
	mov.b	r1,@r13
.L835:
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L842:
	.align 2
.L841:
	.long	memmove
	.size	prim_move, .-prim_move
	.section	.rodata.str1.4
	.align 2
.LC16:
	.string	": "
	.align 2
.LC17:
	.string	"  "
	.align 2
.LC18:
	.string	"   "
	.align 2
.LC19:
	.string	"\nOutput truncated"
	.text
	.align 1
	.align 2
	.global	prim_dump
	.type	prim_dump, @function
prim_dump:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#124,r9
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov	r4,r13
	mov.l	r14,@-r15
	sts.l	pr,@-r15
	mov.l	@(24,r9),r1
	tst	r1,r1
	bf/s	.L891
	add	#-36,r15
	bra	.L892
	mov.l	@r13,r1
.L891:
	mov.l	.L878,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	tst	r2,r2
	bf/s	.L890
	mov.l	r2,@(4,r15)
	bra	.L893
	mov.l	@(44,r9),r1
.L890:
	add	r0,r1
	mov	r4,r14
	add	#-4,r1
	add	#64,r14
	mov.l	@r1,r10
	mov.l	@(0,r14),r1
	mov	#0,r0
	mov	#0,r11
	mov.l	r0,@(8,r15)
	and	r1,r10
	mov	r15,r1
	add	#24,r1
	mov.l	r1,@r15
	mov.l	@(4,r15),r1
	add	#-1,r1
	mov.l	r1,@(12,r15)
.L847:
	mov.l	@(24,r9),r1
	mov.l	.L879,r4
	jsr	@r1
	mov	#0,r8
	mov.l	.L882,r2
	mov	#6,r6
	mov	r10,r4
	mov	r15,r5
	jsr	@r2
	add	#16,r5
	mov.l	@(24,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#16,r4
	mov.l	@(24,r9),r1
	mov.l	.L881,r4
	jsr	@r1
	nop
.L860:
	mov.l	@(52,r13),r1
	mov	r10,r0
	mov	#2,r6
	mov	r15,r5
	mov.b	@(r0,r1),r12
	add	#16,r5
	mov.l	.L882,r1
	jsr	@r1
	extu.b	r12,r4
	mov.l	@(24,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#16,r4
	mov	#24,r1
	mov	r8,r0
	add	r15,r1
	add	#1,r8
	mov.b	r12,@(r0,r1)
	mov	r8,r0
	cmp/eq	#8,r0
	bt/s	.L874
	mov.l	@(12,r15),r0
	cmp/eq	r11,r0
	bt	.L875
	mov.l	@(24,r9),r1
	mov.l	.L883,r4
	jsr	@r1
	add	#1,r11
	mov.l	@(4,r15),r0
	cmp/eq	r11,r0
	bt/s	.L846
	add	#1,r10
	mov.l	@(0,r14),r1
	bra	.L860
	and	r1,r10
	.align 1
.L874:
	mov.l	@r15,r1
	mov	#0,r0
	mov.b	r0,@(8,r1)
.L849:
	tst	r8,r8
	mov	r15,r2
	mov	#31,r7
	mov	r8,r1
	add	#24,r2
	bt/s	.L876
	mov	#46,r0
.L853:
	mov.b	@r2+,r3
	cmp/gt	r7,r3
	bt/s	.L852
	mov	r2,r3
	add	#-16,r3
	mov.b	r0,@(15,r3)
.L852:
	dt	r1
	bf	.L853
	mov	r8,r0
	cmp/eq	#8,r0
	bt	.L858
	neg	r8,r8
	add	#8,r8
	mov	#0,r12
	.align 2
.L851:
	mov.l	@(24,r9),r1
	mov.l	.L884,r4
	jsr	@r1
	add	#1,r12
	cmp/hs	r8,r12
	bf	.L851
.L858:
	mov.l	@(24,r9),r1
	mov.l	.L885,r4
	jsr	@r1
	nop
	mov.l	@(24,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#24,r4
	mov.l	@(8,r15),r0
	add	#1,r0
	cmp/eq	#20,r0
	bt/s	.L855
	mov.l	r0,@(8,r15)
	mov.l	@(4,r15),r0
	add	#1,r11
	cmp/eq	r11,r0
	bt/s	.L846
	add	#1,r10
	mov.l	@(0,r14),r1
	bra	.L847
	and	r1,r10
	.align 1
.L876:
	bra	.L853
	mov	#1,r1
	.align 1
.L875:
	mov	#24,r2
	mov	r8,r0
	mov	#0,r1
	add	r15,r2
	bra	.L849
	mov.b	r1,@(r0,r2)
	.align 1
.L855:
	mov.l	@(4,r15),r1
	add	#-1,r1
	cmp/eq	r11,r1
	bf	.L877
.L846:
	mov.l	@(44,r9),r1
.L893:
	tst	r1,r1
	bt	.L844
	jsr	@r1
	nop
.L844:
	mov.l	@r13,r1
.L892:
	add	#-2,r1
	mov.l	r1,@r13
	add	#36,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L877:
	mov.l	@(24,r9),r1
	mov.l	.L886,r4
	jsr	@r1
	nop
	bra	.L893
	mov.l	@(44,r9),r1
.L887:
	.align 2
.L878:
	.long	1073741823
.L879:
	.long	.LC0
.L882:
	.long	text_hex32_padded
.L881:
	.long	.LC16
.L883:
	.long	.LC1
.L884:
	.long	.LC18
.L885:
	.long	.LC17
.L886:
	.long	.LC19
	.size	prim_dump, .-prim_dump
	.align 1
	.align 2
	.global	prim_hidden_if
	.type	prim_hidden_if, @function
prim_hidden_if:
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L899
	mov	r4,r2
	add	#-1,r0
	mov.l	@(4,r4),r3
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r3
	add	#64,r2
	tst	r3,r3
	bf/s	.L897
	mov.l	@(12,r2),r1
	mov.l	@(4,r1),r3
	add	r3,r1
	rts	
	mov.l	r1,@(12,r2)
	.align 1
.L897:
	add	#4,r1
	rts	
	mov.l	r1,@(12,r2)
	.align 1
.L899:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov.b	r0,@(0,r4)
	rts	
	nop
	.size	prim_hidden_if, .-prim_hidden_if
	.align 1
	.align 2
	.global	prim_hidden_plus_loop
	.type	prim_hidden_plus_loop, @function
prim_hidden_plus_loop:
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L905
	mov	r4,r3
	add	#-1,r0
	mov.l	@(4,r4),r1
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(8,r4),r2
	mov.l	@(r0,r1),r1
	add	#64,r3
	mov.l	@(44,r4),r7
	add	r2,r1
	mov.l	@(12,r3),r2
	cmp/ge	r7,r1
	bt/s	.L903
	mov.l	r1,@(8,r4)
	mov.l	@(4,r2),r1
	add	r1,r2
	rts	
	mov.l	r2,@(12,r3)
	.align 1
.L903:
	mov.l	@(12,r4),r1
	add	#4,r2
	mov.l	r2,@(12,r3)
	mov.l	r1,@(8,r4)
	mov.l	@(48,r4),r1
	mov.l	@(24,r4),r2
	mov.l	r1,@(44,r4)
	mov	r2,r1
	mov.l	@(16,r2),r2
	add	#16,r1
	mov.l	r2,@(12,r4)
	mov.l	r1,@(24,r4)
	mov.l	@(4,r1),r1
	rts	
	mov.l	r1,@(48,r4)
	.align 1
.L905:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov.b	r0,@(0,r4)
	rts	
	nop
	.size	prim_hidden_plus_loop, .-prim_hidden_plus_loop
	.section	.rodata.str1.4
	.align 2
.LC20:
	.string	"prim_hidden_s_quote"
	.text
	.align 1
	.align 2
	.global	prim_hidden_s_quote
	.type	prim_hidden_s_quote, @function
prim_hidden_s_quote:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov.l	r14,@-r15
	mov	r4,r14
	sts.l	pr,@-r15
	mov.w	.L918,r1
	mov.l	@r4,r2
	cmp/gt	r1,r2
	bf/s	.L907
	add	#-4,r15
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r14
	mov	#0,r1
	mov.b	r1,@r14
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L907:
	mov.l	@(60,r4),r1
	mov	r4,r9
	add	#64,r9
	mov.l	.L919,r5
	mov.l	r1,@r15
	mov	#17,r4
	mov.l	.L920,r1
	mov.l	@(12,r9),r10
	mov.l	.L921,r8
	mov.l	@(4,r10),r13
	jsr	@r1
	mov	r10,r11
	mov.l	@(12,r9),r5
	mov.l	.L922,r4
	jsr	@r8
	add	#8,r11
	mov.l	@(12,r9),r5
	mov.l	.L923,r4
	jsr	@r8
	add	#4,r5
	mov.l	.L924,r4
	jsr	@r8
	mov	r13,r5
	mov.l	.L927,r4
	jsr	@r8
	mov	r11,r5
	tst	r13,r13
	bt	.L909
	mov	r13,r1
	add	#8,r1
	add	r1,r10
	mov	r11,r12
	.align 2
.L910:
	mov.b	@r12,r5
	mov.l	.L926,r4
	jsr	@r8
	mov	r5,r6
	mov.b	@r12+,r3
	mov.l	@(52,r14),r1
	mov.l	@(60,r14),r0
	cmp/eq	r10,r12
	mov.b	r3,@(r0,r1)
	mov.l	@(60,r14),r1
	mov.l	@(0,r9),r3
	add	#1,r1
	and	r3,r1
	bf/s	.L910
	mov.l	r1,@(60,r14)
	add	r13,r11
.L909:
	mov.l	.L927,r4
	jsr	@r8
	mov	r11,r5
	neg	r13,r0
	mov.l	.L928,r4
	and	#3,r0
	add	r0,r11
	mov	r11,r1
	add	#-4,r1
	mov.l	r1,@(12,r9)
	jsr	@r8
	mov	#4,r5
	mov.l	.L929,r4
	jsr	@r8
	mov	r11,r5
	mov.l	.L930,r4
	jsr	@r8
	mov.l	@(12,r9),r5
	mov.l	@r14,r0
	mov.l	@(4,r14),r1
	mov.l	@r15,r2
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r14,r0
	add	#1,r0
	mov.l	r0,@r14
	shll2	r0
	mov.l	r13,@(r0,r1)
	mov.l	@r14,r1
	add	#1,r1
	mov.l	r1,@r14
	mov.l	.L931,r1
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L918:
	.short	254
.L932:
	.align 2
.L919:
	.long	.LC20
.L920:
	.long	log_push
.L921:
	.long	log_text
.L922:
	.long	.LC3
.L923:
	.long	.LC4
.L924:
	.long	.LC5
.L927:
	.long	.LC6
.L926:
	.long	.LC7
.L928:
	.long	.LC10
.L929:
	.long	.LC11
.L930:
	.long	.LC12
.L931:
	.long	log_pop
	.size	prim_hidden_s_quote, .-prim_hidden_s_quote
	.section	.rodata.str1.4
	.align 2
.LC21:
	.string	"<"
	.align 2
.LC22:
	.string	"> "
	.text
	.align 1
	.align 2
	.global	prim_dot_s
	.type	prim_dot_s, @function
prim_dot_s:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#124,r9
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	mov	r4,r13
	sts.l	pr,@-r15
	mov.l	@(24,r9),r1
	tst	r1,r1
	bt/s	.L945
	add	#-12,r15
	mov.l	.L946,r0
	mov.l	.L947,r11
	jsr	@r0
	nop
	mov.l	@(24,r9),r1
	mov.l	.L948,r4
	jsr	@r1
	mov	r0,r10
	mov	r15,r5
	jsr	@r11
	mov	r10,r4
	mov.l	@(24,r9),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(24,r9),r1
	mov.l	.L949,r4
	jsr	@r1
	nop
	cmp/pl	r10
	bf	.L935
	mov.l	.L950,r12
	mov	#0,r8
	.align 2
.L936:
	mov.l	@(4,r13),r1
	mov	r8,r0
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	jsr	@r11
	add	#1,r8
	mov.l	@(24,r9),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(24,r9),r1
	jsr	@r1
	mov	r12,r4
	cmp/eq	r8,r10
	bf	.L936
.L935:
	mov.l	@(44,r9),r1
	tst	r1,r1
	bt	.L945
	jsr	@r1
	nop
.L945:
	add	#12,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L951:
	.align 2
.L946:
	.long	forth_stack_count
.L947:
	.long	text_int32
.L948:
	.long	.LC21
.L949:
	.long	.LC22
.L950:
	.long	.LC1
	.size	prim_dot_s, .-prim_dot_s
	.align 1
	.align 2
	.global	prim_hidden_loop
	.type	prim_hidden_loop, @function
prim_hidden_loop:
	mov.l	@(8,r4),r1
	mov	r4,r3
	mov.l	@(44,r4),r7
	add	#64,r3
	add	#1,r1
	mov.l	@(12,r3),r2
	cmp/eq	r7,r1
	bt/s	.L953
	mov.l	r1,@(8,r4)
	mov.l	@(4,r2),r1
	add	r1,r2
	rts	
	mov.l	r2,@(12,r3)
	.align 1
.L953:
	mov.l	@(12,r4),r1
	add	#4,r2
	mov.l	r2,@(12,r3)
	mov.l	r1,@(8,r4)
	mov.l	@(48,r4),r1
	mov.l	@(24,r4),r2
	mov.l	r1,@(44,r4)
	mov	r2,r1
	mov.l	@(16,r2),r2
	add	#16,r1
	mov.l	r2,@(12,r4)
	mov.l	r1,@(24,r4)
	mov.l	@(4,r1),r1
	rts	
	mov.l	r1,@(48,r4)
	.size	prim_hidden_loop, .-prim_hidden_loop
	.align 1
	.align 2
	.global	prim_true
	.type	prim_true, @function
prim_true:
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	shll2	r2
	add	r2,r1
	mov	#0,r2
	mov.l	r2,@r1
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_true, .-prim_true
	.global	forth_primitives_len
	.section	.rodata
	.align 2
	.type	forth_primitives_len, @object
	.size	forth_primitives_len, 4
forth_primitives_len:
	.long	151
	.global	forth_primitives
	.section	.rodata.str1.4
	.align 2
.LC23:
	.string	"!"
	.align 2
.LC24:
	.string	"C!"
	.align 2
.LC25:
	.string	"W!"
	.align 2
.LC26:
	.string	"'"
	.align 2
.LC27:
	.string	"("
	.align 2
.LC28:
	.string	"*"
	.align 2
.LC29:
	.string	"*/"
	.align 2
.LC30:
	.string	"*/MOD"
	.align 2
.LC31:
	.string	"+"
	.align 2
.LC32:
	.string	"+LOOP"
	.align 2
.LC33:
	.string	","
	.align 2
.LC34:
	.string	"C,"
	.align 2
.LC35:
	.string	"W,"
	.align 2
.LC36:
	.string	"-"
	.align 2
.LC37:
	.string	"\\"
	.align 2
.LC38:
	.string	"."
	.align 2
.LC39:
	.string	"U."
	.align 2
.LC40:
	.string	"X."
	.align 2
.LC41:
	.string	".\""
	.align 2
.LC42:
	.string	"/"
	.align 2
.LC43:
	.string	"/MOD"
	.align 2
.LC44:
	.string	":"
	.align 2
.LC45:
	.string	";"
	.align 2
.LC46:
	.string	"="
	.align 2
.LC47:
	.string	">"
	.align 2
.LC48:
	.string	">NUMBER"
	.align 2
.LC49:
	.string	">NUM"
	.align 2
.LC50:
	.string	"NUMBER>"
	.align 2
.LC51:
	.string	"NUM>"
	.align 2
.LC52:
	.string	">HEX"
	.align 2
.LC53:
	.string	"HEX>"
	.align 2
.LC54:
	.string	"?DUP"
	.align 2
.LC55:
	.string	"@"
	.align 2
.LC56:
	.string	"C@"
	.align 2
.LC57:
	.string	"W@"
	.align 2
.LC58:
	.string	"QUIT"
	.align 2
.LC59:
	.string	"ABS"
	.align 2
.LC60:
	.string	"ACCEPT"
	.align 2
.LC61:
	.string	"ALIGN"
	.align 2
.LC62:
	.string	"ALIGNED"
	.align 2
.LC63:
	.string	"ALLOT"
	.align 2
.LC64:
	.string	"AND"
	.align 2
.LC65:
	.string	"BEGIN"
	.align 2
.LC66:
	.string	"BL"
	.align 2
.LC67:
	.string	"BOUNDS"
	.align 2
.LC68:
	.string	"CELLS"
	.align 2
.LC69:
	.string	"CHAR"
	.align 2
.LC70:
	.string	"CONSTANT"
	.align 2
.LC71:
	.string	"CONST"
	.align 2
.LC72:
	.string	"CR"
	.align 2
.LC73:
	.string	"CREATE"
	.align 2
.LC74:
	.string	"DEPTH"
	.align 2
.LC75:
	.string	"DO"
	.align 2
.LC76:
	.string	"DROP"
	.align 2
.LC77:
	.string	"2DROP"
	.align 2
.LC78:
	.string	"DUP"
	.align 2
.LC79:
	.string	"2DUP"
	.align 2
.LC80:
	.string	"ELSE"
	.align 2
.LC81:
	.string	"EMIT"
	.align 2
.LC82:
	.string	"ERASE"
	.align 2
.LC83:
	.string	"EXECUTE"
	.align 2
.LC84:
	.string	"EXEC"
	.align 2
.LC85:
	.string	"EXIT"
	.align 2
.LC86:
	.string	"FILL"
	.align 2
.LC87:
	.string	"HERE"
	.align 2
.LC88:
	.string	"I"
	.align 2
.LC89:
	.string	"IF"
	.align 2
.LC90:
	.string	"INVERT"
	.align 2
.LC91:
	.string	"J"
	.align 2
.LC92:
	.string	"KEY"
	.align 2
.LC93:
	.string	"LEAVE"
	.align 2
.LC94:
	.string	"LITERAL"
	.align 2
.LC95:
	.string	"LIT"
	.align 2
.LC96:
	.string	"LOOP"
	.align 2
.LC97:
	.string	"LSHIFT"
	.align 2
.LC98:
	.string	"MAX"
	.align 2
.LC99:
	.string	"MIN"
	.align 2
.LC100:
	.string	"MOD"
	.align 2
.LC101:
	.string	"MOVE"
	.align 2
.LC102:
	.string	"NEGATE"
	.align 2
.LC103:
	.string	"OR"
	.align 2
.LC104:
	.string	"OVER"
	.align 2
.LC105:
	.string	"2OVER"
	.align 2
.LC106:
	.string	"PAGE"
	.align 2
.LC107:
	.string	"REPEAT"
	.align 2
.LC108:
	.string	"ROT"
	.align 2
.LC109:
	.string	"-ROT"
	.align 2
.LC110:
	.string	"RSHIFT"
	.align 2
.LC111:
	.string	"S\""
	.align 2
.LC112:
	.string	"SPACE"
	.align 2
.LC113:
	.string	"SPACES"
	.align 2
.LC114:
	.string	"SWAP"
	.align 2
.LC115:
	.string	"2SWAP"
	.align 2
.LC116:
	.string	"THEN"
	.align 2
.LC117:
	.string	"TYPE"
	.align 2
.LC118:
	.string	"U<"
	.align 2
.LC119:
	.string	"U>"
	.align 2
.LC120:
	.string	"UNTIL"
	.align 2
.LC121:
	.string	"VARIABLE"
	.align 2
.LC122:
	.string	"VAR"
	.align 2
.LC123:
	.string	"WHILE"
	.align 2
.LC124:
	.string	"XOR"
	.align 2
.LC125:
	.string	"["
	.align 2
.LC126:
	.string	"]"
	.align 2
.LC127:
	.string	"[']"
	.align 2
.LC128:
	.string	"[CHAR]"
	.align 2
.LC129:
	.string	".R"
	.align 2
.LC130:
	.string	"U.R"
	.align 2
.LC131:
	.string	"X.R"
	.align 2
.LC132:
	.string	"<>"
	.align 2
.LC133:
	.string	"AGAIN"
	.align 2
.LC134:
	.string	"FALSE"
	.align 2
.LC135:
	.string	"NIP"
	.align 2
.LC136:
	.string	"S\\\""
	.align 2
.LC137:
	.string	"TRUE"
	.align 2
.LC138:
	.string	"TUCK"
	.align 2
.LC139:
	.string	"UNUSED"
	.align 2
.LC140:
	.string	"WITHIN"
	.align 2
.LC141:
	.string	".S"
	.align 2
.LC142:
	.string	"?"
	.align 2
.LC143:
	.string	"DUMP"
	.align 2
.LC144:
	.string	"WORDS"
	.align 2
.LC145:
	.string	"WORDSIZE"
	.align 2
.LC146:
	.string	"BYE"
	.align 2
.LC147:
	.string	"{"
	.align 2
.LC148:
	.string	"0{"
	.align 2
.LC149:
	.string	"TO"
	.align 2
.LC150:
	.string	"RESET"
	.align 2
.LC151:
	.string	"WALIGN"
	.align 2
.LC152:
	.string	"WALIGNED"
	.align 2
.LC153:
	.string	"PRINTABLE"
	.align 2
.LC154:
	.string	"CXT"
	.align 2
.LC155:
	.string	"WXT"
	.align 2
.LC156:
	.string	"PRIMITIVES"
	.align 2
.LC157:
	.string	"SECONDARIES"
	.align 2
.LC158:
	.string	"UNDEFINED"
	.align 2
.LC159:
	.string	"PERF"
	.align 2
.LC160:
	.string	"SIZE"
	.align 2
.LC161:
	.string	"RESIZE"
	.align 2
.LC162:
	.string	""
	.section	.rodata
	.align 2
	.type	forth_primitives, @object
	.size	forth_primitives, 4832
forth_primitives:
	.long	.LC23
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC24
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC25
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC26
	.byte	1
	.zero	3
	.long	39
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC27
	.byte	1
	.zero	3
	.long	28
	.long	28
	.long	0
	.byte	1
	.zero	11
	.long	.LC28
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_star
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC29
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_star_slash
	.byte	0
	.zero	3
	.long	3
	.long	1
	.long	.LC30
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_star_slash_mod
	.byte	0
	.zero	3
	.long	3
	.long	2
	.long	.LC31
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_plus
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC32
	.byte	5
	.zero	3
	.long	1
	.long	29
	.long	0
	.byte	1
	.zero	11
	.long	.LC33
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC34
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC35
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC36
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_minus
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC37
	.byte	1
	.zero	3
	.long	10
	.long	10
	.long	0
	.byte	1
	.zero	11
	.long	.LC38
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_dot
	.byte	1
	.zero	11
	.long	.LC39
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_dot
	.byte	1
	.zero	11
	.long	.LC40
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_x_dot
	.byte	1
	.zero	11
	.long	.LC41
	.byte	2
	.zero	3
	.long	14
	.long	14
	.long	0
	.byte	1
	.zero	11
	.long	.LC42
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_slash
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC43
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_slash_mod
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC44
	.byte	1
	.zero	3
	.long	9
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC45
	.byte	1
	.zero	3
	.long	1
	.long	37
	.long	0
	.byte	1
	.zero	11
	.long	.LC21
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_less_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC46
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_equals
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC47
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_greater_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC48
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_to_number
	.byte	1
	.zero	11
	.long	.LC49
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_to_number
	.byte	1
	.zero	11
	.long	.LC50
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_number_to
	.byte	1
	.zero	11
	.long	.LC51
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_number_to
	.byte	1
	.zero	11
	.long	.LC52
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_to_hex
	.byte	1
	.zero	11
	.long	.LC53
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_hex_to
	.byte	1
	.zero	11
	.long	.LC54
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_question_dupe
	.byte	1
	.zero	11
	.long	.LC55
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC56
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC57
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC58
	.byte	4
	.zero	3
	.long	1
	.long	0
	.long	prim_quit
	.byte	1
	.zero	11
	.long	.LC59
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_abs
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC60
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_accept
	.byte	1
	.zero	11
	.long	.LC61
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_align
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	.LC62
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_aligned
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC63
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_allot
	.byte	1
	.zero	11
	.long	.LC64
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_and
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC65
	.byte	5
	.zero	3
	.long	1
	.long	4
	.long	0
	.byte	1
	.zero	11
	.long	.LC66
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_b_l
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC67
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_bounds
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC68
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_cells
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC69
	.byte	4
	.zero	3
	.long	8
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC70
	.byte	8
	.zero	3
	.long	11
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC71
	.byte	5
	.zero	3
	.long	11
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC72
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_r
	.byte	1
	.zero	11
	.long	.LC73
	.byte	6
	.zero	3
	.long	12
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC74
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_depth
	.byte	1
	.zero	11
	.long	.LC75
	.byte	2
	.zero	3
	.long	1
	.long	13
	.long	0
	.byte	1
	.zero	11
	.long	.LC76
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_drop
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC77
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_drop
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC78
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_dupe
	.byte	0
	.zero	3
	.long	1
	.long	2
	.long	.LC79
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_two_dupe
	.byte	0
	.zero	3
	.long	2
	.long	4
	.long	.LC80
	.byte	4
	.zero	3
	.long	1
	.long	15
	.long	0
	.byte	1
	.zero	11
	.long	.LC81
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_emit
	.byte	1
	.zero	11
	.long	.LC82
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_erase
	.byte	1
	.zero	11
	.long	.LC83
	.byte	7
	.zero	3
	.long	19
	.long	0
	.long	prim_execute
	.byte	1
	.zero	11
	.long	.LC84
	.byte	4
	.zero	3
	.long	19
	.long	0
	.long	prim_execute
	.byte	1
	.zero	11
	.long	.LC85
	.byte	4
	.zero	3
	.long	1
	.long	0
	.long	prim_hidden_done
	.byte	1
	.zero	11
	.long	.LC86
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_fill
	.byte	1
	.zero	11
	.long	.LC87
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_here
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC88
	.byte	1
	.zero	3
	.long	1
	.long	0
	.long	prim_i
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC89
	.byte	2
	.zero	3
	.long	1
	.long	20
	.long	0
	.byte	1
	.zero	11
	.long	.LC90
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_invert
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC91
	.byte	1
	.zero	3
	.long	1
	.long	0
	.long	prim_j
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC92
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_key
	.byte	1
	.zero	11
	.long	.LC93
	.byte	5
	.zero	3
	.long	1
	.long	21
	.long	0
	.byte	1
	.zero	11
	.long	.LC94
	.byte	7
	.zero	3
	.long	1
	.long	23
	.long	0
	.byte	1
	.zero	11
	.long	.LC95
	.byte	3
	.zero	3
	.long	1
	.long	23
	.long	0
	.byte	1
	.zero	11
	.long	.LC96
	.byte	4
	.zero	3
	.long	1
	.long	26
	.long	0
	.byte	1
	.zero	11
	.long	.LC97
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_l_shift
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC98
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_max
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC99
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_min
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC100
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_mod
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC101
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_move
	.byte	1
	.zero	11
	.long	.LC102
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_negate
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC103
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_or
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC104
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_over
	.byte	0
	.zero	3
	.long	2
	.long	3
	.long	.LC105
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_over
	.byte	0
	.zero	3
	.long	4
	.long	6
	.long	.LC106
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_page
	.byte	1
	.zero	11
	.long	.LC107
	.byte	6
	.zero	3
	.long	1
	.long	31
	.long	0
	.byte	1
	.zero	11
	.long	.LC108
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_rote
	.byte	0
	.zero	3
	.long	3
	.long	3
	.long	.LC109
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_minus_rote
	.byte	0
	.zero	3
	.long	3
	.long	3
	.long	.LC110
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_r_shift
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC111
	.byte	2
	.zero	3
	.long	34
	.long	34
	.long	0
	.byte	1
	.zero	11
	.long	.LC112
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_space
	.byte	1
	.zero	11
	.long	.LC113
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_spaces
	.byte	1
	.zero	11
	.long	.LC114
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_swap
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC115
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_swap
	.byte	0
	.zero	3
	.long	4
	.long	4
	.long	.LC116
	.byte	4
	.zero	3
	.long	1
	.long	38
	.long	0
	.byte	1
	.zero	11
	.long	.LC117
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_type
	.byte	1
	.zero	11
	.long	.LC118
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_less_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC119
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_greater_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC120
	.byte	5
	.zero	3
	.long	1
	.long	42
	.long	0
	.byte	1
	.zero	11
	.long	.LC121
	.byte	8
	.zero	3
	.long	43
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC122
	.byte	3
	.zero	3
	.long	43
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC123
	.byte	5
	.zero	3
	.long	1
	.long	44
	.long	0
	.byte	1
	.zero	11
	.long	.LC124
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_x_or
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC125
	.byte	1
	.zero	3
	.long	1
	.long	22
	.long	0
	.byte	1
	.zero	11
	.long	.LC126
	.byte	1
	.zero	3
	.long	33
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC127
	.byte	3
	.zero	3
	.long	1
	.long	6
	.long	0
	.byte	1
	.zero	11
	.long	.LC128
	.byte	6
	.zero	3
	.long	1
	.long	5
	.long	0
	.byte	1
	.zero	11
	.long	.LC129
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_dot_r
	.byte	1
	.zero	11
	.long	.LC130
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_u_dot_r
	.byte	1
	.zero	11
	.long	.LC131
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_x_dot_r
	.byte	1
	.zero	11
	.long	.LC132
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_not_equals
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC133
	.byte	5
	.zero	3
	.long	1
	.long	3
	.long	0
	.byte	1
	.zero	11
	.long	.LC134
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_false
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC135
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_nip
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC136
	.byte	3
	.zero	3
	.long	35
	.long	35
	.long	0
	.byte	1
	.zero	11
	.long	.LC137
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_true
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC138
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_tuck
	.byte	0
	.zero	3
	.long	2
	.long	3
	.long	.LC139
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_unused
	.byte	1
	.zero	11
	.long	.LC140
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_within
	.byte	0
	.zero	3
	.long	3
	.long	1
	.long	.LC141
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_dot_s
	.byte	1
	.zero	11
	.long	.LC142
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_question
	.byte	1
	.zero	11
	.long	.LC143
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_dump
	.byte	1
	.zero	11
	.long	.LC144
	.byte	5
	.zero	3
	.long	45
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC145
	.byte	8
	.zero	3
	.long	46
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC146
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_bye
	.byte	1
	.zero	11
	.long	.LC147
	.byte	1
	.zero	3
	.long	1
	.long	24
	.long	0
	.byte	1
	.zero	11
	.long	.LC148
	.byte	2
	.zero	3
	.long	1
	.long	25
	.long	0
	.byte	1
	.zero	11
	.long	.LC149
	.byte	2
	.zero	3
	.long	1
	.long	40
	.long	0
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC150
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_reset
	.byte	1
	.zero	11
	.long	.LC151
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_walign
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	.LC152
	.byte	8
	.zero	3
	.long	0
	.long	0
	.long	prim_waligned
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC153
	.byte	9
	.zero	3
	.long	0
	.long	0
	.long	prim_printable
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC154
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_cxt
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC155
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_wxt
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC156
	.byte	10
	.zero	3
	.long	30
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC157
	.byte	11
	.zero	3
	.long	36
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC158
	.byte	9
	.zero	3
	.long	41
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC159
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_perf
	.byte	1
	.zero	11
	.long	.LC160
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_size
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC161
	.byte	6
	.zero	3
	.long	32
	.long	2
	.long	0
	.zero	12
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_do
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_done
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_dot_quote
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_if
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_jump
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_leave
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_loop
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_plus_loop
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_push
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_s_quote
	.byte	1
	.zero	11
	.long	.LC162
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_secondary
	.byte	1
	.zero	11
	.global	__moddi3
	.global	__divdi3
	.ident	"GCC: (GNU) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
