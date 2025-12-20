	.file	"forth-primitives.c"
	.text
	.text
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
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 2
.LC0:
	.string	"address: %p ["
	.align 2
.LC1:
	.string	"]\n"
	.align 2
.LC2:
	.string	"\n"
	.text
	.align 1
	.align 2
	.global	prim_hidden_do
	.type	prim_hidden_do, @function
prim_hidden_do:
	mov.l	r8,@-r15
	mov	#1,r2
	sts.l	pr,@-r15
	mov.l	@r4,r3
	add	#-8,r15
	cmp/gt	r2,r3
	bf/s	.L10
	mov	r4,r1
	mov.l	.L12,r0
	mov.l	@(4,r4),r2
	add	r3,r0
	shll2	r0
	mov.l	@(r0,r2),r6
	add	r0,r2
	add	#-4,r2
	add	#-2,r3
	mov.l	@r2,r7
	mov.l	@(24,r4),r2
	mov.l	r3,@r4
	mov.l	@(20,r4),r3
	cmp/hs	r3,r2
	bf/s	.L11
	mov	#2,r0
	mov.l	@(12,r4),r3
	mov	r4,r8
	add	#64,r8
	mov.l	r3,@r2
	mov.l	@(48,r4),r3
	mov.b	r0,@(14,r2)
	mov.l	r3,@(4,r2)
	mov.l	@(20,r8),r3
	mov.l	@(24,r4),r2
	mov.l	r3,@(8,r2)
	add	#-16,r2
	mov.l	r2,@(24,r4)
	mov.l	@(8,r4),r2
	mov.l	r6,@(8,r4)
	mov.l	r2,@(12,r4)
	mov.l	@(44,r4),r2
	mov.l	r7,@(44,r4)
	mov.l	r2,@(48,r4)
.L7:
	mov.l	.L13,r2
	mov.l	@(12,r8),r5
	mov.l	.L14,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L15,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L16,r2
	mov.l	.L17,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L18,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L11:
	mov	#7,r3
	mov	r4,r2
	add	#124,r2
	mov	r4,r8
	mov.l	r3,@(12,r2)
	mov	#0,r3
	mov	r4,r2
	add	#80,r2
	mov.b	r3,@r2
	bra	.L7
	add	#64,r8
	.align 1
.L10:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L19:
	.align 2
.L12:
	.long	1073741823
.L13:
	.long	log_text
.L14:
	.long	.LC0
.L15:
	.long	log_bytes
.L16:
	.long	log_text_raw
.L17:
	.long	.LC1
.L18:
	.long	.LC2
	.size	prim_hidden_do, .-prim_hidden_do
	.align 1
	.align 2
	.global	prim_hidden_done
	.type	prim_hidden_done, @function
prim_hidden_done:
	mov.l	r8,@-r15
	mov	r4,r3
	sts.l	pr,@-r15
	mov.l	@(24,r4),r1
	bra	.L22
	add	#-8,r15
	.align 1
.L21:
	tst	r0,r0
	bt	.L24
.L22:
	mov	r1,r7
	add	#16,r1
	mov.l	r1,@(24,r3)
	mov.b	@(14,r1),r0
	mov	r0,r2
	extu.b	r0,r0
	cmp/eq	#1,r0
	bf/s	.L21
	mov	r3,r8
	add	#64,r8
	mov.l	@(16,r7),r1
	mov.l	@(28,r8),r5
	mov.w	@(28,r7),r0
	add	r1,r5
	mov.l	.L25,r4
	mov.l	r5,@(12,r8)
	extu.w	r0,r7
	mov.l	@(36,r3),r1
	shll2	r7
	mov.l	r3,@r15
	add	r7,r1
	mov.l	r1,@(36,r3)
	mov.l	.L26,r1
	jsr	@r1
	nop
	mov.l	.L27,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L28,r1
	mov.l	.L29,r4
	jsr	@r1
	mov.l	r1,@(4,r15)
	mov.l	@(4,r15),r1
	mov.l	.L30,r4
	jsr	@r1
	nop
	mov.l	@(12,r8),r1
	mov.l	@r15,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L24:
	add	#80,r3
	mov.b	r2,@r3
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L31:
	.align 2
.L25:
	.long	.LC0
.L26:
	.long	log_text
.L27:
	.long	log_bytes
.L28:
	.long	log_text_raw
.L29:
	.long	.LC1
.L30:
	.long	.LC2
	.size	prim_hidden_done, .-prim_hidden_done
	.align 1
	.align 2
	.global	prim_hidden_jump
	.type	prim_hidden_jump, @function
prim_hidden_jump:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	r4,r9
	sts.l	pr,@-r15
	mov.l	@(12,r8),r5
	mov.l	.L34,r4
	mov.l	@(4,r5),r1
	mov.l	.L35,r10
	add	r1,r5
	mov.l	.L36,r1
	jsr	@r1
	mov.l	r5,@(12,r8)
	mov.l	.L37,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L38,r4
	jsr	@r10
	nop
	mov.l	.L39,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L40:
	.align 2
.L34:
	.long	.LC0
.L35:
	.long	log_text_raw
.L36:
	.long	log_text
.L37:
	.long	log_bytes
.L38:
	.long	.LC1
.L39:
	.long	.LC2
	.size	prim_hidden_jump, .-prim_hidden_jump
	.align 1
	.align 2
	.global	prim_hidden_leave
	.type	prim_hidden_leave, @function
prim_hidden_leave:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(12,r4),r1
	mov.l	@(24,r4),r2
	mov.l	r1,@(8,r4)
	mov.l	@(48,r4),r1
	mov.l	.L43,r10
	mov.l	r1,@(44,r4)
	mov	r2,r1
	mov.l	@(16,r2),r2
	add	#16,r1
	mov.l	r2,@(12,r4)
	mov.l	r1,@(24,r4)
	mov.l	@(4,r1),r1
	mov.l	@(12,r9),r5
	mov.l	r1,@(48,r4)
	mov.l	@(4,r5),r1
	mov.l	.L44,r4
	add	r1,r5
	mov.l	.L45,r1
	jsr	@r1
	mov.l	r5,@(12,r9)
	mov.l	.L46,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L47,r4
	jsr	@r10
	nop
	mov.l	.L48,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L49:
	.align 2
.L43:
	.long	log_text_raw
.L44:
	.long	.LC0
.L45:
	.long	log_text
.L46:
	.long	log_bytes
.L47:
	.long	.LC1
.L48:
	.long	.LC2
	.size	prim_hidden_leave, .-prim_hidden_leave
	.align 1
	.align 2
	.global	prim_hidden_loop
	.type	prim_hidden_loop, @function
prim_hidden_loop:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(8,r4),r1
	mov.l	@(44,r4),r2
	add	#1,r1
	mov.l	@(12,r9),r5
	cmp/eq	r2,r1
	bt/s	.L51
	mov.l	r1,@(8,r4)
	mov.l	@(4,r5),r1
	add	r1,r5
	mov.l	r5,@(12,r9)
.L52:
	mov.l	.L54,r1
	mov.l	.L55,r4
	mov.l	.L56,r10
	jsr	@r1
	nop
	mov.l	.L57,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L58,r4
	jsr	@r10
	nop
	mov.l	.L59,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L51:
	mov.l	@(12,r4),r1
	add	#4,r5
	mov.l	r5,@(12,r9)
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
	bra	.L52
	mov.l	r1,@(48,r4)
.L60:
	.align 2
.L54:
	.long	log_text
.L55:
	.long	.LC0
.L56:
	.long	log_text_raw
.L57:
	.long	log_bytes
.L58:
	.long	.LC1
.L59:
	.long	.LC2
	.size	prim_hidden_loop, .-prim_hidden_loop
	.align 1
	.align 2
	.global	prim_hidden_plus_loop
	.type	prim_hidden_plus_loop, @function
prim_hidden_plus_loop:
	mov.l	r8,@-r15
	mov	r4,r1
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L68
	add	#-8,r15
	add	#-1,r0
	mov.l	@(4,r4),r2
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(8,r4),r3
	mov	r4,r8
	mov.l	@(r0,r2),r2
	add	#64,r8
	mov.l	@(12,r8),r5
	add	r3,r2
	mov.l	@(44,r4),r3
	cmp/ge	r3,r2
	bf/s	.L69
	mov.l	r2,@(8,r4)
	mov.l	@(12,r4),r2
	add	#4,r5
	mov.l	r5,@(12,r8)
	mov.l	r2,@(8,r4)
	mov.l	@(48,r4),r2
	mov.l	@(24,r4),r3
	mov.l	r2,@(44,r4)
	mov	r3,r2
	mov.l	@(16,r3),r3
	add	#16,r2
	mov.l	r3,@(12,r4)
	mov.l	r2,@(24,r4)
	mov.l	@(4,r2),r2
	mov.l	r2,@(48,r4)
.L65:
	mov.l	.L70,r2
	mov.l	.L71,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L72,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L73,r2
	mov.l	.L74,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L75,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L69:
	mov.l	@(4,r5),r2
	add	r2,r5
	bra	.L65
	mov.l	r5,@(12,r8)
	.align 1
.L68:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov.b	r0,@(0,r1)
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L76:
	.align 2
.L70:
	.long	log_text
.L71:
	.long	.LC0
.L72:
	.long	log_bytes
.L73:
	.long	log_text_raw
.L74:
	.long	.LC1
.L75:
	.long	.LC2
	.size	prim_hidden_plus_loop, .-prim_hidden_plus_loop
	.align 1
	.align 2
	.global	prim_hidden_push
	.type	prim_hidden_push, @function
prim_hidden_push:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(12,r9),r5
	mov.l	@r4,r0
	mov.l	@(4,r5),r2
	add	#4,r5
	mov.l	r5,@(12,r9)
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L79,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L80,r1
	mov.l	.L81,r4
	jsr	@r1
	nop
	mov.l	.L82,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L83,r4
	jsr	@r10
	nop
	mov.l	.L84,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L85:
	.align 2
.L79:
	.long	log_text_raw
.L80:
	.long	log_text
.L81:
	.long	.LC0
.L82:
	.long	log_bytes
.L83:
	.long	.LC1
.L84:
	.long	.LC2
	.size	prim_hidden_push, .-prim_hidden_push
	.align 1
	.align 2
	.global	prim_hidden_secondary
	.type	prim_hidden_secondary, @function
prim_hidden_secondary:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	#5,r3
	sts.l	pr,@-r15
	mov.l	@(12,r8),r5
	mov.l	@(24,r8),r1
	mov.l	@(4,r5),r2
	add	#4,r5
	mov.l	r5,@(12,r8)
	shld	r3,r2
	add	r2,r1
	mov	r1,r0
	add	#16,r0
	mov.b	@(12,r0),r0
	extu.b	r0,r0
	cmp/eq	#4,r0
	bt/s	.L98
	mov	r4,r9
	add	#-1,r0
	extu.b	r0,r0
	mov	#2,r2
	cmp/hi	r2,r0
	bt	.L89
	mov.l	@r4,r0
	mov.w	.L101,r2
	cmp/gt	r2,r0
	bt/s	.L99
	shll2	r0
	mov.l	@r1,r1
	mov.l	@(4,r1),r2
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
.L88:
	mov.l	.L102,r1
	mov.l	.L103,r4
	mov.l	.L104,r10
	jsr	@r1
	nop
	mov.l	.L105,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L106,r4
	jsr	@r10
	nop
	mov.l	.L107,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L89:
	mov.l	@(24,r4),r2
	mov.l	@(20,r4),r3
	cmp/hs	r3,r2
	bf/s	.L100
	mov	#1,r0
	mov.l	@(20,r8),r3
	add	#1,r3
	mov.l	r3,@(20,r8)
	mov.l	@(28,r8),r3
	mov.b	r0,@(14,r2)
	sub	r3,r5
	mov.w	@(26,r1),r0
	mov.l	r5,@r2
	mov.l	@(20,r8),r3
	mov.l	@(24,r4),r2
	mov.l	@(32,r4),r7
	mov.l	r3,@(8,r2)
	mov.w	r0,@(12,r2)
	extu.w	r0,r0
	mov.l	@(36,r4),r3
	shll2	r0
	sub	r0,r3
	cmp/hs	r7,r3
	bt/s	.L94
	mov.l	r3,@(36,r4)
	mov	#5,r7
	mov	r4,r3
	add	#124,r3
	mov.l	r7,@(12,r3)
	mov	#0,r7
	mov	r4,r3
	add	#80,r3
	mov.b	r7,@r3
.L94:
	mov.l	@r1,r5
	add	#-16,r2
	mov.l	r2,@(24,r9)
	add	#-4,r5
	bra	.L88
	mov.l	r5,@(12,r8)
	.align 1
.L98:
	mov.l	@(20,r1),r1
	mov	#9,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(28,r2)
	mov.l	r3,@(12,r2)
	mov	r4,r1
	mov	#0,r2
	add	#80,r1
	mov.b	r2,@r1
	bra	.L88
	nop
	.align 1
.L100:
	mov	#7,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	mov	#0,r2
	mov	r4,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L88
	nop
	.align 1
.L99:
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L101:
	.short	255
.L108:
	.align 2
.L102:
	.long	log_text
.L103:
	.long	.LC0
.L104:
	.long	log_text_raw
.L105:
	.long	log_bytes
.L106:
	.long	.LC1
.L107:
	.long	.LC2
	.size	prim_hidden_secondary, .-prim_hidden_secondary
	.align 1
	.align 2
	.global	prim_store
	.type	prim_store, @function
prim_store:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
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
	mov.l	@(8,r9),r1
	mov.l	@(12,r9),r5
	and	r1,r0
	mov.l	@(52,r4),r1
	mov.l	.L111,r4
	mov.l	r2,@(r0,r1)
	mov.l	.L112,r1
	mov.l	.L113,r10
	jsr	@r1
	nop
	mov.l	.L114,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L115,r4
	jsr	@r10
	nop
	mov.l	.L116,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L117:
	.align 2
.L111:
	.long	.LC0
.L112:
	.long	log_text
.L113:
	.long	log_text_raw
.L114:
	.long	log_bytes
.L115:
	.long	.LC1
.L116:
	.long	.LC2
	.size	prim_store, .-prim_store
	.align 1
	.align 2
	.global	prim_c_store
	.type	prim_c_store, @function
prim_c_store:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r2
	shll2	r0
	mov.l	.L120,r10
	mov.l	@(r0,r1),r3
	add	r0,r1
	mov.l	r2,@r4
	add	#-4,r1
	mov.l	@(0,r9),r2
	mov.l	@r1,r1
	and	r3,r2
	mov.l	@(52,r4),r3
	mov	r2,r0
	mov.l	.L121,r4
	mov.b	r1,@(r0,r3)
	mov.l	.L122,r1
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L123,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L124,r4
	jsr	@r10
	nop
	mov.l	.L125,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L126:
	.align 2
.L120:
	.long	log_text_raw
.L121:
	.long	.LC0
.L122:
	.long	log_text
.L123:
	.long	log_bytes
.L124:
	.long	.LC1
.L125:
	.long	.LC2
	.size	prim_c_store, .-prim_c_store
	.align 1
	.align 2
	.global	prim_w_store
	.type	prim_w_store, @function
prim_w_store:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r2
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r3
	add	r0,r1
	mov.l	r2,@r4
	add	#-4,r1
	mov.l	@(4,r9),r2
	mov.l	@r1,r1
	and	r3,r2
	mov.l	@(52,r4),r3
	mov	r2,r0
	mov.l	.L129,r4
	mov.w	r1,@(r0,r3)
	mov.l	.L130,r1
	mov.l	.L131,r10
	jsr	@r1
	nop
	mov.l	.L132,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L133,r4
	jsr	@r10
	nop
	mov.l	.L134,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L135:
	.align 2
.L129:
	.long	.LC0
.L130:
	.long	log_text
.L131:
	.long	log_text_raw
.L132:
	.long	log_bytes
.L133:
	.long	.LC1
.L134:
	.long	.LC2
	.size	prim_w_store, .-prim_w_store
	.align 1
	.align 2
	.global	prim_star
	.type	prim_star, @function
prim_star:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r2
	mov.l	@r1,r3
	mov.l	.L138,r4
	mul.l	r2,r3
	mov.l	.L139,r10
	sts	macl,r2
	mov.l	r2,@r1
	mov.l	.L140,r1
	jsr	@r1
	nop
	mov.l	.L141,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L142,r4
	jsr	@r10
	nop
	mov.l	.L143,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L144:
	.align 2
.L138:
	.long	.LC0
.L139:
	.long	log_text_raw
.L140:
	.long	log_text
.L141:
	.long	log_bytes
.L142:
	.long	.LC1
.L143:
	.long	.LC2
	.size	prim_star, .-prim_star
	.align 1
	.align 2
	.global	prim_star_slash
	.type	prim_star_slash, @function
prim_star_slash:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
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
	mov	r1,r9
	add	#-8,r0
	tst	r7,r7
	add	#-4,r2
	add	r0,r9
	mov.l	@r2,r2
	mov.l	@r9,r1
	bf	.L146
	mov	#1,r7
.L146:
	dmuls.l	r2,r1
	mov.l	.L148,r0
	mov	r7,r6
	shll	r6
	mov.l	.L149,r10
	sts	macl,r5
	sts	mach,r4
	jsr	@r0
	subc	r6,r6
	mov.l	r1,@r9
	mov	r8,r9
	mov.l	.L150,r1
	add	#64,r9
	mov.l	.L151,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L152,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L153,r4
	jsr	@r10
	nop
	mov.l	.L154,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L155:
	.align 2
.L148:
	.long	__divdi3
.L149:
	.long	log_text_raw
.L150:
	.long	log_text
.L151:
	.long	.LC0
.L152:
	.long	log_bytes
.L153:
	.long	.LC1
.L154:
	.long	.LC2
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
	mov.l	@(4,r4),r9
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r9),r2
	mov	r0,r3
	add	r9,r0
	add	#-4,r3
	tst	r2,r2
	add	r9,r3
	add	#-8,r0
	mov.l	@r3,r1
	mov.l	@r0,r7
	dmuls.l	r1,r7
	sts	mach,r1
	sts	macl,r10
	bt/s	.L157
	mov.l	r1,@(12,r15)
	mov.l	.L161,r0
	mov	r2,r1
	shll	r1
	mov	r2,r7
	subc	r1,r1
	mov.l	r2,@(8,r15)
	sts	mach,r4
	sts	macl,r5
	mov.l	r3,@r15
	mov	r1,r6
	jsr	@r0
	mov.l	r1,@(16,r15)
	mov.l	.L162,r0
	mov	r10,r5
	mov.l	@(12,r15),r4
	mov.l	@(16,r15),r6
	mov.l	@(8,r15),r7
	jsr	@r0
	mov.l	r1,@(4,r15)
	mov.l	@r15,r3
	mov	r1,r10
	mov.l	@(4,r15),r2
	mov.l	r0,@(12,r15)
.L157:
	mov.l	r10,@r3
	mov.l	@r8,r0
	mov.l	.L163,r3
	mov.l	.L164,r1
	add	r3,r0
	mov.l	.L165,r4
	shll2	r0
	mov.l	.L166,r10
	mov.l	r2,@(r0,r9)
	mov	r8,r9
	add	#64,r9
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L167,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L168,r4
	jsr	@r10
	nop
	mov.l	.L169,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#20,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L170:
	.align 2
.L161:
	.long	__moddi3
.L162:
	.long	__divdi3
.L163:
	.long	1073741822
.L164:
	.long	log_text
.L165:
	.long	.LC0
.L166:
	.long	log_text_raw
.L167:
	.long	log_bytes
.L168:
	.long	.LC1
.L169:
	.long	.LC2
	.size	prim_star_slash_mod, .-prim_star_slash_mod
	.align 1
	.align 2
	.global	prim_plus
	.type	prim_plus, @function
prim_plus:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	mov.l	.L173,r4
	add	r3,r2
	mov.l	.L174,r10
	mov.l	r2,@r1
	mov.l	.L175,r1
	jsr	@r1
	nop
	mov.l	.L176,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L177,r4
	jsr	@r10
	nop
	mov.l	.L178,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L179:
	.align 2
.L173:
	.long	.LC0
.L174:
	.long	log_text_raw
.L175:
	.long	log_text
.L176:
	.long	log_bytes
.L177:
	.long	.LC1
.L178:
	.long	.LC2
	.size	prim_plus, .-prim_plus
	.align 1
	.align 2
	.global	prim_comma
	.type	prim_comma, @function
prim_comma:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(8,r9),r2
	mov.l	@(60,r4),r1
	mov.l	@r4,r0
	and	r2,r1
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r1,@(60,r4)
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r2),r3
	mov	r1,r0
	mov.l	@(52,r4),r2
	mov.l	@(12,r9),r5
	mov.l	r3,@(r0,r2)
	mov.l	@(60,r4),r1
	mov.l	@(8,r9),r2
	add	#4,r1
	mov.l	.L182,r10
	and	r2,r1
	mov.l	r1,@(60,r4)
	mov.l	.L183,r1
	mov.l	.L184,r4
	jsr	@r1
	nop
	mov.l	.L185,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L186,r4
	jsr	@r10
	nop
	mov.l	.L187,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L188:
	.align 2
.L182:
	.long	log_text_raw
.L183:
	.long	log_text
.L184:
	.long	.LC0
.L185:
	.long	log_bytes
.L186:
	.long	.LC1
.L187:
	.long	.LC2
	.size	prim_comma, .-prim_comma
	.align 1
	.align 2
	.global	prim_c_comma
	.type	prim_c_comma, @function
prim_c_comma:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(0,r9),r2
	mov.l	@(60,r4),r1
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	and	r2,r1
	add	#-1,r0
	mov.l	r1,@(60,r4)
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r3
	mov	r1,r0
	mov.l	@(52,r4),r2
	mov.l	.L191,r10
	mov.b	r3,@(r0,r2)
	mov.l	@(60,r4),r1
	mov.l	@(0,r9),r2
	add	#1,r1
	mov.l	@(12,r9),r5
	and	r2,r1
	mov.l	r1,@(60,r4)
	mov.l	.L192,r1
	mov.l	.L193,r4
	jsr	@r1
	nop
	mov.l	.L194,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L195,r4
	jsr	@r10
	nop
	mov.l	.L196,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L197:
	.align 2
.L191:
	.long	log_text_raw
.L192:
	.long	log_text
.L193:
	.long	.LC0
.L194:
	.long	log_bytes
.L195:
	.long	.LC1
.L196:
	.long	.LC2
	.size	prim_c_comma, .-prim_c_comma
	.align 1
	.align 2
	.global	prim_w_comma
	.type	prim_w_comma, @function
prim_w_comma:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(4,r9),r2
	mov.l	@(60,r4),r6
	mov.l	@r4,r1
	mov.l	@(4,r4),r7
	and	r2,r6
	add	#-1,r1
	mov.l	r6,@(60,r4)
	mov.l	r1,@r4
	shll2	r1
	mov.l	@(52,r4),r3
	mov	r1,r0
	mov.l	@(r0,r7),r1
	mov	r6,r0
	mov.l	@(12,r9),r5
	mov.w	r1,@(r0,r3)
	add	#1,r0
	mov.l	.L200,r1
	and	r2,r0
	mov.l	r0,@(60,r4)
	mov.l	.L201,r4
	jsr	@r1
	nop
	mov.l	.L202,r1
	mov	#32,r5
	mov.l	.L203,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L204,r4
	jsr	@r10
	nop
	mov.l	.L205,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L206:
	.align 2
.L200:
	.long	log_text
.L201:
	.long	.LC0
.L202:
	.long	log_bytes
.L203:
	.long	log_text_raw
.L204:
	.long	.LC1
.L205:
	.long	.LC2
	.size	prim_w_comma, .-prim_w_comma
	.align 1
	.align 2
	.global	prim_minus
	.type	prim_minus, @function
prim_minus:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	mov.l	.L209,r4
	sub	r3,r2
	mov.l	.L210,r10
	mov.l	r2,@r1
	mov.l	.L211,r1
	jsr	@r1
	nop
	mov.l	.L212,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L213,r4
	jsr	@r10
	nop
	mov.l	.L214,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L215:
	.align 2
.L209:
	.long	.LC0
.L210:
	.long	log_text_raw
.L211:
	.long	log_text
.L212:
	.long	log_bytes
.L213:
	.long	.LC1
.L214:
	.long	.LC2
	.size	prim_minus, .-prim_minus
	.align 1
	.align 2
	.global	prim_slash
	.type	prim_slash, @function
prim_slash:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r2),r5
	add	#-4,r0
	add	r0,r2
	tst	r5,r5
	bt/s	.L217
	mov.l	@r2,r4
	mov.l	.L222,r0
	jsr	@r0
	nop
	mov	r0,r4
.L217:
	mov.l	.L223,r1
	mov	r8,r9
	add	#64,r9
	mov.l	r4,@r2
	mov.l	.L224,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L225,r1
	mov	#32,r5
	mov.l	.L226,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L227,r4
	jsr	@r10
	nop
	mov.l	.L228,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L229:
	.align 2
.L222:
	.long	__sdivsi3_i4i
.L223:
	.long	log_text
.L224:
	.long	.LC0
.L225:
	.long	log_bytes
.L226:
	.long	log_text_raw
.L227:
	.long	.LC1
.L228:
	.long	.LC2
	.size	prim_slash, .-prim_slash
	.align 1
	.align 2
	.global	prim_slash_mod
	.type	prim_slash_mod, @function
prim_slash_mod:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	.L236,r1
	mov.l	@r4,r2
	mov.l	@(4,r4),r6
	add	r1,r2
	shll2	r2
	add	r6,r2
	mov.l	@r2,r3
	mov	r2,r1
	add	#-4,r1
	tst	r3,r3
	bt/s	.L231
	mov.l	@r1,r7
	mov.l	.L237,r0
	mov	r7,r4
	jsr	@r0
	mov	r3,r5
	mul.l	r3,r0
	mov	r7,r3
	mov	r0,r7
	sts	macl,r1
	sub	r1,r3
.L231:
	mov.l	r7,@r2
	mov	r8,r9
	mov.l	@r8,r0
	add	#64,r9
	mov.l	.L238,r1
	mov.l	@(12,r9),r5
	add	r1,r0
	mov.l	.L239,r1
	shll2	r0
	mov.l	.L240,r4
	jsr	@r1
	mov.l	r3,@(r0,r6)
	mov.l	.L241,r1
	mov	#32,r5
	mov.l	.L242,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L243,r4
	jsr	@r10
	nop
	mov.l	.L244,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L245:
	.align 2
.L236:
	.long	1073741823
.L237:
	.long	__sdivsi3_i4i
.L238:
	.long	1073741822
.L239:
	.long	log_text
.L240:
	.long	.LC0
.L241:
	.long	log_bytes
.L242:
	.long	log_text_raw
.L243:
	.long	.LC1
.L244:
	.long	.LC2
	.size	prim_slash_mod, .-prim_slash_mod
	.align 1
	.align 2
	.global	prim_less_than
	.type	prim_less_than, @function
prim_less_than:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	mov.l	.L248,r4
	cmp/gt	r2,r3
	mov.l	.L249,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L250,r1
	jsr	@r1
	nop
	mov.l	.L251,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L252,r4
	jsr	@r10
	nop
	mov.l	.L253,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L254:
	.align 2
.L248:
	.long	.LC0
.L249:
	.long	log_text_raw
.L250:
	.long	log_text
.L251:
	.long	log_bytes
.L252:
	.long	.LC1
.L253:
	.long	.LC2
	.size	prim_less_than, .-prim_less_than
	.align 1
	.align 2
	.global	prim_equals
	.type	prim_equals, @function
prim_equals:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	mov.l	.L257,r4
	cmp/eq	r2,r3
	mov.l	.L258,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L259,r1
	jsr	@r1
	nop
	mov.l	.L260,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L261,r4
	jsr	@r10
	nop
	mov.l	.L262,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L263:
	.align 2
.L257:
	.long	.LC0
.L258:
	.long	log_text_raw
.L259:
	.long	log_text
.L260:
	.long	log_bytes
.L261:
	.long	.LC1
.L262:
	.long	.LC2
	.size	prim_equals, .-prim_equals
	.align 1
	.align 2
	.global	prim_greater_than
	.type	prim_greater_than, @function
prim_greater_than:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r2
	mov.l	@r1,r3
	mov.l	.L266,r4
	cmp/gt	r2,r3
	mov.l	.L267,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L268,r1
	jsr	@r1
	nop
	mov.l	.L269,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L270,r4
	jsr	@r10
	nop
	mov.l	.L271,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L272:
	.align 2
.L266:
	.long	.LC0
.L267:
	.long	log_text_raw
.L268:
	.long	log_text
.L269:
	.long	log_bytes
.L270:
	.long	.LC1
.L271:
	.long	.LC2
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
	sts.l	pr,@-r15
	mov.l	@r4,r1
	add	#-24,r15
	mov.l	r1,@(4,r15)
	mov	#1,r1
	mov.l	@(4,r15),r2
	cmp/gt	r1,r2
	bt/s	.L328
	mov	r4,r10
	bra	.L297
	mov	#10,r2
.L328:
	mov.w	.L302,r1
	mov.l	@(4,r15),r13
	cmp/gt	r1,r13
	bf	.L327
	bra	.L298
	mov	#6,r2
.L327:
	mov.l	@(4,r15),r3
	mov.l	.L306,r0
	mov.l	@(4,r4),r1
	add	r3,r0
	shll2	r0
	mov.l	r1,@(12,r15)
	add	r0,r1
	mov.l	@(12,r15),r13
	mov.l	r1,@(20,r15)
	add	#-4,r1
	mov.l	@r1,r1
	mov.l	@(r0,r13),r6
	mov.l	r1,@(16,r15)
	mov.l	@(56,r4),r1
	cmp/hi	r1,r6
	bf	.L277
	mov	r1,r6
.L277:
	tst	r6,r6
	bf	.L326
	bra	.L289
	mov	r10,r13
.L326:
	mov.l	@(52,r10),r9
	mov	r10,r1
	mov.l	@(16,r15),r3
	add	#64,r1
	mov.l	@(0,r1),r11
	mov	r6,r12
	mov.l	r1,@(8,r15)
	add	#-1,r12
	mov	#0,r8
	mov.l	r10,@r15
	mov	#0,r1
	mov	r12,r5
	mov	#0,r7
	mov	#10,r4
	mov	#1,r14
	.align 2
.L288:
	and	r11,r3
	mov	r3,r0
	mov.b	@(r0,r9),r2
	extu.b	r2,r0
	cmp/eq	#45,r0
	movt	r10
	cmp/eq	r12,r5
	movt	r2
	and	r2,r10
	tst	r10,r10
	bf/s	.L290
	add	#-48,r0
	extu.b	r0,r2
	mov	#9,r13
	cmp/hi	r13,r2
	bf	.L325
	bra	.L299
	mov.l	@r15,r10
.L325:
	mul.l	r1,r4
	tst	r8,r8
	sts	macl,r1
	dmulu.l	r4,r7
	sts	mach,r2
	sts	macl,r7
	bt/s	.L324
	add	r1,r2
	bra	.L281
	cmp/gt	r0,r10
.L324:
	cmp/gt	r0,r8
	subc	r1,r1
	clrt
	addc	r0,r7
	addc	r2,r1
.L282:
	mov.l	.L304,r0
	clrt
	mov	#0,r2
	addc	r7,r0
	addc	r1,r2
	cmp/hs	r14,r2
	bf/s	.L279
	cmp/hi	r14,r2
	bt	.L292
	bra	.L300
	nop
.L292:
	mov.l	@(16,r15),r1
.L329:
	mov.l	@r15,r10
	and	r11,r1
	mov.w	.L305,r3
	mov	r1,r0
	mov.b	@(r0,r9),r7
	add	r10,r3
	exts.b	r7,r0
	mov	r7,r2
	cmp/eq	#45,r0
	bf/s	.L287
	mov	#1,r7
.L284:
	mov.b	r0,@r3
	mov	#0,r0
	mov.b	r0,@(1,r3)
	mov	r7,r0
	cmp/eq	#11,r0
	bt	.L286
	add	#1,r1
.L330:
	and	r11,r1
	mov	r1,r0
	mov.b	@(r0,r9),r6
	add	#1,r3
	add	#1,r7
	mov	r6,r2
	mov	r6,r0
.L287:
	add	#-48,r2
	extu.b	r2,r2
	mov	#9,r6
	cmp/hi	r6,r2
	bf	.L284
	mov	r7,r0
	cmp/eq	#11,r0
	bf/s	.L330
	add	#1,r1
	add	#-1,r1
.L286:
	mov	#3,r2
	mov	r10,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	mov	#0,r2
	mov	r10,r1
	add	#80,r1
	mov.b	r2,@r1
	mov.l	@(4,r15),r1
	add	#-2,r1
	mov.l	r1,@r10
	add	#24,r15
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
.L298:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r10
	mov	#0,r1
	mov.b	r1,@r10
	add	#24,r15
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
.L290:
	mov	r10,r8
.L279:
	dt	r6
	add	#1,r3
	bf/s	.L288
	add	#-1,r5
	mov.l	@r15,r10
	mov	#0,r5
	mov.l	r3,@(16,r15)
.L278:
	mov.l	@(20,r15),r1
	mov.l	.L306,r2
	mov.l	r5,@(4,r1)
	mov.l	@r10,r0
	mov.l	@(12,r15),r3
	mov.l	@(16,r15),r13
	add	r2,r0
	shll2	r0
	mov.l	.L307,r1
	mov.l	r13,@(r0,r3)
	mov.l	@r10,r0
	mov.l	@(8,r15),r2
	add	r1,r0
	mov.l	.L308,r4
	shll2	r0
	mov.l	@(12,r2),r5
	mov.l	r7,@(r0,r3)
	mov.l	@r10,r1
	mov.l	.L309,r8
	add	#1,r1
	mov.l	r1,@r10
	mov.l	.L310,r1
	jsr	@r1
	nop
	mov.l	.L311,r1
	mov	#32,r5
	mov.l	@(8,r15),r3
	jsr	@r1
	mov.l	@(12,r3),r4
	mov.l	.L312,r4
	jsr	@r8
	nop
	mov.l	.L313,r4
	jsr	@r8
	nop
	mov.l	@(8,r15),r13
	mov	r10,r4
	mov.l	@(12,r13),r1
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r13)
	mov.l	@(4,r1),r1
	add	#24,r15
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
.L302:
	.short	255
.L305:
	.short	140
.L314:
	.align 2
.L306:
	.long	1073741823
.L304:
	.long	-2147483648
.L307:
	.long	1073741822
.L308:
	.long	.LC0
.L309:
	.long	log_text_raw
.L310:
	.long	log_text
.L311:
	.long	log_bytes
.L312:
	.long	.LC1
.L313:
	.long	.LC2
	.align 1
.L281:
	mov	r2,r1
	subc	r10,r10
	clrt
	subc	r0,r7
	bra	.L282
	subc	r10,r1
	.align 1
.L297:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r10
	mov	#0,r1
	mov.b	r1,@r10
	add	#24,r15
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
.L299:
	add	#1,r5
	bra	.L278
	mov.l	r3,@(16,r15)
	.align 1
.L289:
	add	#64,r13
	mov	#0,r7
	mov.l	r13,@(8,r15)
	bra	.L278
	mov	#0,r5
	.align 1
.L300:
	mov.l	.L315,r2
	cmp/hi	r2,r0
	bf	.L279
	bra	.L329
	mov.l	@(16,r15),r1
.L316:
	.align 2
.L315:
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
	sts.l	pr,@-r15
	mov.l	@r4,r1
	add	#-28,r15
	mov.l	r1,@(4,r15)
	mov	#1,r1
	mov.l	@(4,r15),r2
	cmp/gt	r1,r2
	bt/s	.L419
	mov	r4,r11
	bra	.L371
	mov	#10,r2
.L419:
	mov.w	.L381,r1
	mov.l	@(4,r15),r6
	cmp/gt	r1,r6
	bf	.L418
	bra	.L372
	mov	#6,r2
.L418:
	mov.l	@(4,r15),r3
	mov.l	.L382,r0
	mov.l	@(4,r4),r1
	add	r3,r0
	mov.l	r1,@(8,r15)
	shll2	r0
	add	r0,r1
	mov.l	@(8,r15),r6
	mov.l	r1,@(16,r15)
	add	#-4,r1
	mov.l	@r1,r5
	mov.l	@(56,r4),r1
	mov.l	@(r0,r6),r4
	cmp/hi	r1,r4
	bf	.L335
	mov	r1,r4
.L335:
	tst	r4,r4
	bf	.L417
	bra	.L357
	mov	r11,r6
.L417:
	mov	r11,r14
	add	#64,r14
	mov.l	@(0,r14),r10
	mov.l	@(52,r11),r13
	mov.l	r5,@(24,r15)
	and	r10,r5
	mov	r5,r0
	mov.b	@(r0,r13),r1
	mov.l	r14,@(12,r15)
	extu.b	r1,r1
	mov	r1,r0
	cmp/eq	#45,r0
	bf/s	.L416
	mov.l	r1,@(20,r15)
	bra	.L373
	add	#-1,r4
.L416:
	mov	r4,r0
	cmp/eq	#1,r0
	bf/s	.L415
	mov.l	@(20,r15),r3
	bra	.L374
	mov	#0,r1
.L415:
	mov	#0,r6
	mov	r5,r2
	mov.l	r6,@r15
.L356:
	mov	r3,r0
	cmp/eq	#48,r0
	bf/s	.L339
	and	r10,r5
	bra	.L375
	add	#1,r2
.L339:
	mov	#0,r7
.L421:
	mov	r4,r9
	mov	#9,r8
	mov	r5,r0
	mov	#0,r14
	mov	#1,r12
	mov	#0,r1
	.align 2
.L355:
	mov	r3,r6
	add	#-48,r6
	extu.b	r6,r2
	cmp/hi	r8,r2
	bf	.L342
	mov	r3,r2
	add	#-97,r2
	extu.b	r2,r2
	mov	#5,r6
	cmp/hi	r6,r2
	bf	.L413
	bra	.L343
	mov	r3,r2
.L413:
	mov	r3,r6
	add	#-87,r6
.L342:
	mov	#-28,r3
	mov	r1,r2
	shll2	r2
	mov	r7,r5
	shll2	r2
	cmp/gt	r6,r14
	shld	r3,r5
	mov	r7,r3
	mov	r5,r1
	or	r2,r1
	mov.l	@r15,r2
	subc	r5,r5
	shll2	r3
	tst	r2,r2
	bt/s	.L412
	shll2	r3
	bra	.L345
	mov	r3,r7
.L412:
	clrt
	mov	r3,r7
	addc	r6,r7
	addc	r5,r1
.L346:
	mov.l	.L383,r3
	clrt
	mov	#0,r2
	addc	r7,r3
	addc	r1,r2
	cmp/hs	r12,r2
	bt	.L411
	bra	.L420
	dt	r9
.L411:
	cmp/hi	r12,r2
	bt	.L360
	bra	.L376
	nop
.L360:
	mov.w	.L384,r1
	mov	#9,r5
	mov.w	.L385,r7
	mov	#-33,r8
	mov.l	@(24,r15),r3
	add	r11,r1
	mov.l	@(20,r15),r12
	sub	r11,r7
	mov	#5,r4
	bra	.L353
	mov	#8,r2
	.align 1
.L377:
	mov	r9,r0
	cmp/eq	#45,r0
	bf/s	.L422
	mov	r12,r0
.L349:
	mov	#0,r0
	mov.b	r9,@r1
	mov.b	r0,@(1,r1)
	dt	r2
	bt/s	.L368
	add	#1,r1
.L378:
	and	r10,r3
	mov	r10,r0
	add	#1,r3
	and	r3,r0
	mov.b	@(r0,r13),r12
.L353:
	mov	r7,r0
	add	r1,r0
	tst	r0,r0
	bt/s	.L377
	exts.b	r12,r9
	mov	r12,r0
.L422:
	add	#-48,r0
	extu.b	r0,r0
	cmp/hi	r5,r0
	bf/s	.L349
	mov	r12,r0
	and	r8,r0
	add	#-65,r0
	extu.b	r0,r0
	cmp/hi	r4,r0
	bf	.L349
	dt	r2
	bf/s	.L378
	add	#1,r1
.L368:
	mov	#4,r2
	mov	r11,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	mov	#0,r2
	mov	r11,r1
	add	#80,r1
	mov.b	r2,@r1
	mov.l	@(4,r15),r1
	add	#-2,r1
	mov.l	r1,@r11
	add	#28,r15
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
.L372:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r11
	mov	#0,r1
	mov.b	r1,@r11
	add	#28,r15
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
.L371:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r11
	mov	#0,r1
	mov.b	r1,@r11
	add	#28,r15
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
.L381:
	.short	255
.L384:
	.short	140
.L385:
	.short	-140
.L386:
	.align 2
.L382:
	.long	1073741823
.L383:
	.long	-2147483648
	.align 1
.L357:
	add	#64,r6
	mov	#0,r7
	mov.l	r6,@(12,r15)
	mov	#0,r4
.L336:
	mov.l	@(16,r15),r1
	mov.l	.L387,r2
	mov.l	r4,@(4,r1)
	mov.l	@r11,r0
	mov.l	@(8,r15),r3
	add	r2,r0
	mov.l	.L388,r6
	shll2	r0
	mov.l	@(12,r15),r14
	mov.l	r5,@(r0,r3)
	mov.l	@r11,r0
	mov.l	@(12,r14),r5
	add	r6,r0
	mov.l	.L389,r4
	shll2	r0
	mov.l	.L390,r8
	mov.l	r7,@(r0,r3)
	mov.l	@r11,r1
	add	#1,r1
	mov.l	r1,@r11
	mov.l	.L391,r1
	jsr	@r1
	nop
	mov.l	.L392,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L393,r4
	jsr	@r8
	nop
	mov.l	.L394,r4
	jsr	@r8
	nop
	mov.l	@(12,r14),r1
	mov	r11,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r14)
	mov.l	@(4,r1),r1
	add	#28,r15
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
.L373:
	mov	#1,r1
	cmp/hi	r1,r4
	bf/s	.L358
	add	#1,r5
	mov	r10,r2
	and	r5,r2
	mov	r2,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r3
	mov	#1,r1
	bra	.L356
	mov.l	r1,@r15
	.align 1
.L376:
	mov.l	.L395,r6
	cmp/hi	r6,r3
	bf	.L347
	bra	.L360
	nop
	.align 2
.L347:
	dt	r9
	.align 2
.L420:
	add	#-1,r4
	bt/s	.L379
	add	#1,r0
	and	r10,r0
	mov.b	@(r0,r13),r3
	bra	.L355
	extu.b	r3,r3
	.align 1
.L345:
	subc	r6,r7
	bra	.L346
	subc	r5,r1
	.align 1
.L343:
	add	#-65,r2
	extu.b	r2,r2
	mov	#5,r6
	cmp/hi	r6,r2
	bt/s	.L380
	mov	r3,r6
	bra	.L342
	add	#-55,r6
	.align 1
.L379:
	mov	#0,r4
	bra	.L336
	mov	r0,r5
	.align 1
.L374:
	mov.l	r1,@r15
	bra	.L339
	and	r10,r5
	.align 1
.L380:
	bra	.L336
	mov	r0,r5
	.align 1
.L358:
	mov	#1,r2
	mov.l	r2,@r15
.L338:
	tst	r4,r4
	bt/s	.L336
	mov	#0,r7
	and	r10,r5
	mov	r5,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r3
.L408:
	bra	.L421
	mov	#0,r7
	.align 1
.L375:
	and	r10,r2
	mov	r2,r0
	mov.b	@(r0,r13),r0
	cmp/eq	#120,r0
	bf	.L408
	mov	r2,r5
	add	#-2,r4
	bra	.L338
	add	#1,r5
.L396:
	.align 2
.L387:
	.long	1073741823
.L388:
	.long	1073741822
.L389:
	.long	.LC0
.L390:
	.long	log_text_raw
.L391:
	.long	log_text
.L392:
	.long	log_bytes
.L393:
	.long	.LC1
.L394:
	.long	.LC2
.L395:
	.long	2147483647
	.size	prim_to_hex, .-prim_to_hex
	.align 1
	.align 2
	.global	prim_question_dupe
	.type	prim_question_dupe, @function
prim_question_dupe:
	mov.l	r8,@-r15
	mov	r4,r1
	sts.l	pr,@-r15
	mov.l	@r4,r2
	tst	r2,r2
	bt/s	.L432
	add	#-8,r15
	mov.l	.L434,r0
	mov.l	@(4,r4),r3
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r3),r7
	tst	r7,r7
	bt	.L426
	mov.w	.L435,r6
	cmp/gt	r6,r2
	bt/s	.L433
	add	r0,r3
	mov.l	r7,@(4,r3)
	mov.l	@r4,r2
	add	#1,r2
	mov.l	r2,@r4
.L426:
	mov.l	.L436,r2
	mov	r1,r8
	add	#64,r8
	mov.l	.L437,r4
	mov.l	@(12,r8),r5
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L438,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L439,r2
	mov.l	.L440,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L441,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L432:
	mov	#10,r7
	mov	r4,r3
	add	#124,r3
	mov.l	r7,@(12,r3)
	add	#80,r1
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L433:
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L435:
	.short	255
.L442:
	.align 2
.L434:
	.long	1073741823
.L436:
	.long	log_text
.L437:
	.long	.LC0
.L438:
	.long	log_bytes
.L439:
	.long	log_text_raw
.L440:
	.long	.LC1
.L441:
	.long	.LC2
	.size	prim_question_dupe, .-prim_question_dupe
	.align 1
	.align 2
	.global	prim_fetch
	.type	prim_fetch, @function
prim_fetch:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L445,r2
	mov.l	@r4,r1
	mov.l	@(8,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L446,r10
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	.L447,r4
	mov.l	@(r0,r2),r2
	mov.l	r2,@r1
	mov.l	.L448,r1
	jsr	@r1
	nop
	mov.l	.L449,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L450,r4
	jsr	@r10
	nop
	mov.l	.L451,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L452:
	.align 2
.L445:
	.long	1073741823
.L446:
	.long	log_text_raw
.L447:
	.long	.LC0
.L448:
	.long	log_text
.L449:
	.long	log_bytes
.L450:
	.long	.LC1
.L451:
	.long	.LC2
	.size	prim_fetch, .-prim_fetch
	.align 1
	.align 2
	.global	prim_c_fetch
	.type	prim_c_fetch, @function
prim_c_fetch:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L455,r2
	mov.l	@r4,r1
	mov.l	@(0,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L456,r10
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	.L457,r4
	mov.b	@(r0,r2),r2
	extu.b	r2,r2
	mov.l	r2,@r1
	mov.l	.L458,r1
	jsr	@r1
	nop
	mov.l	.L459,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L460,r4
	jsr	@r10
	nop
	mov.l	.L461,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L462:
	.align 2
.L455:
	.long	1073741823
.L456:
	.long	log_text_raw
.L457:
	.long	.LC0
.L458:
	.long	log_text
.L459:
	.long	log_bytes
.L460:
	.long	.LC1
.L461:
	.long	.LC2
	.size	prim_c_fetch, .-prim_c_fetch
	.align 1
	.align 2
	.global	prim_w_fetch
	.type	prim_w_fetch, @function
prim_w_fetch:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L465,r2
	mov.l	@r4,r1
	mov.l	@(4,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L466,r10
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	.L467,r4
	mov.w	@(r0,r2),r2
	extu.w	r2,r2
	mov.l	r2,@r1
	mov.l	.L468,r1
	jsr	@r1
	nop
	mov.l	.L469,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L470,r4
	jsr	@r10
	nop
	mov.l	.L471,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L472:
	.align 2
.L465:
	.long	1073741823
.L466:
	.long	log_text_raw
.L467:
	.long	.LC0
.L468:
	.long	log_text
.L469:
	.long	log_bytes
.L470:
	.long	.LC1
.L471:
	.long	.LC2
	.size	prim_w_fetch, .-prim_w_fetch
	.align 1
	.align 2
	.global	prim_abs
	.type	prim_abs, @function
prim_abs:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	.L476,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r2
	cmp/pz	r2
	bt/s	.L474
	mov	r4,r8
	neg	r2,r2
	mov.l	r2,@r1
.L474:
	mov.l	.L477,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L478,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L479,r1
	mov	#32,r5
	mov.l	.L480,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L481,r4
	jsr	@r10
	nop
	mov.l	.L482,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L483:
	.align 2
.L476:
	.long	1073741823
.L477:
	.long	log_text
.L478:
	.long	.LC0
.L479:
	.long	log_bytes
.L480:
	.long	log_text_raw
.L481:
	.long	.LC1
.L482:
	.long	.LC2
	.size	prim_abs, .-prim_abs
	.align 1
	.align 2
	.global	prim_accept
	.type	prim_accept, @function
prim_accept:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov	r4,r8
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L492
	add	#-4,r15
	mov.l	.L493,r7
	mov	r4,r2
	add	#124,r2
	mov	r1,r3
	mov.l	@(40,r2),r0
	add	#-1,r3
	mov.l	@(4,r4),r2
	add	r7,r1
	shll2	r1
	mov.l	r3,@r4
	tst	r0,r0
	bt/s	.L487
	add	r2,r1
	mov	r4,r9
	add	#64,r9
	mov.l	@(0,r9),r2
	mov.l	@r1,r4
	mov.l	@(4,r1),r6
	mov	r2,r7
	and	r2,r4
	jsr	@r0
	mov.l	@(52,r8),r5
	mov.l	.L494,r3
	mov	r0,r2
	mov.l	@r8,r0
	mov.l	@(4,r8),r1
	add	r3,r0
	shll2	r0
	mov.l	r2,@(r0,r1)
.L488:
	mov.l	.L495,r1
	mov.l	.L496,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L497,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L498,r1
	mov.l	.L499,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L500,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L492:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L487:
	mov	r4,r9
	mov.l	r0,@r1
	bra	.L488
	add	#64,r9
.L501:
	.align 2
.L493:
	.long	1073741822
.L494:
	.long	1073741823
.L495:
	.long	log_text
.L496:
	.long	.LC0
.L497:
	.long	log_bytes
.L498:
	.long	log_text_raw
.L499:
	.long	.LC1
.L500:
	.long	.LC2
	.size	prim_accept, .-prim_accept
	.align 1
	.align 2
	.global	prim_align
	.type	prim_align, @function
prim_align:
	mov.l	r8,@-r15
	mov	#3,r2
	mov.l	r9,@-r15
	mov	r4,r8
	mov.l	r10,@-r15
	add	#64,r8
	sts.l	pr,@-r15
	mov.l	@(60,r4),r1
	mov	r4,r9
	mov	r1,r0
	tst	#3,r0
	bt/s	.L503
	and	r1,r2
	add	#4,r1
	sub	r2,r1
	mov.l	@(8,r8),r2
	and	r2,r1
	mov.l	r1,@(60,r4)
.L503:
	mov.l	.L508,r1
	mov.l	.L509,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L510,r1
	mov	#32,r5
	mov.l	.L511,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L512,r4
	jsr	@r10
	nop
	mov.l	.L513,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L514:
	.align 2
.L508:
	.long	log_text
.L509:
	.long	.LC0
.L510:
	.long	log_bytes
.L511:
	.long	log_text_raw
.L512:
	.long	.LC1
.L513:
	.long	.LC2
	.size	prim_align, .-prim_align
	.align 1
	.align 2
	.global	prim_aligned
	.type	prim_aligned, @function
prim_aligned:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	.L521,r2
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
	bt/s	.L516
	sub	r2,r6
	add	#4,r1
	sub	r6,r1
.L516:
	mov	r9,r8
	add	#64,r8
	mov.l	@(8,r8),r2
	mov.l	@(12,r8),r5
	and	r2,r1
	mov.l	.L522,r4
	mov.l	r1,@r3
	mov.l	.L523,r1
	mov.l	.L524,r10
	jsr	@r1
	nop
	mov.l	.L525,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L526,r4
	jsr	@r10
	nop
	mov.l	.L527,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L528:
	.align 2
.L521:
	.long	1073741823
.L522:
	.long	.LC0
.L523:
	.long	log_text
.L524:
	.long	log_text_raw
.L525:
	.long	log_bytes
.L526:
	.long	.LC1
.L527:
	.long	.LC2
	.size	prim_aligned, .-prim_aligned
	.align 1
	.align 2
	.global	prim_and
	.type	prim_and, @function
prim_and:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	mov.l	.L531,r4
	and	r3,r2
	mov.l	.L532,r10
	mov.l	r2,@r1
	mov.l	.L533,r1
	jsr	@r1
	nop
	mov.l	.L534,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L535,r4
	jsr	@r10
	nop
	mov.l	.L536,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L537:
	.align 2
.L531:
	.long	.LC0
.L532:
	.long	log_text_raw
.L533:
	.long	log_text
.L534:
	.long	log_bytes
.L535:
	.long	.LC1
.L536:
	.long	.LC2
	.size	prim_and, .-prim_and
	.align 1
	.align 2
	.global	prim_b_l
	.type	prim_b_l, @function
prim_b_l:
	mov.l	r8,@-r15
	mov	#32,r2
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov	r4,r8
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L540,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L541,r1
	mov.l	.L542,r4
	jsr	@r1
	nop
	mov.l	.L543,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L544,r4
	jsr	@r10
	nop
	mov.l	.L545,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L546:
	.align 2
.L540:
	.long	log_text_raw
.L541:
	.long	log_text
.L542:
	.long	.LC0
.L543:
	.long	log_bytes
.L544:
	.long	.LC1
.L545:
	.long	.LC2
	.size	prim_b_l, .-prim_b_l
	.align 1
	.align 2
	.global	prim_bounds
	.type	prim_bounds, @function
prim_bounds:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L549,r2
	mov.l	@r4,r1
	mov.l	@(4,r4),r3
	add	r2,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L550,r10
	add	r3,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r7
	mov.l	@r1,r2
	mov.l	r7,@r1
	mov.l	.L551,r1
	mov.l	@r4,r0
	mov.l	.L552,r4
	add	r1,r0
	mov	r2,r1
	mov.l	@(0,r9),r2
	add	r7,r1
	shll2	r0
	and	r2,r1
	mov.l	r1,@(r0,r3)
	mov.l	.L553,r1
	jsr	@r1
	nop
	mov.l	.L554,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L555,r4
	jsr	@r10
	nop
	mov.l	.L556,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L557:
	.align 2
.L549:
	.long	1073741823
.L550:
	.long	log_text_raw
.L551:
	.long	1073741822
.L552:
	.long	.LC0
.L553:
	.long	log_text
.L554:
	.long	log_bytes
.L555:
	.long	.LC1
.L556:
	.long	.LC2
	.size	prim_bounds, .-prim_bounds
	.align 1
	.align 2
	.global	prim_cells
	.type	prim_cells, @function
prim_cells:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L560,r2
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	.L561,r4
	add	r2,r1
	mov.l	.L562,r10
	mov.l	@r1,r2
	shll2	r2
	mov.l	r2,@r1
	mov.l	.L563,r1
	jsr	@r1
	nop
	mov.l	.L564,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L565,r4
	jsr	@r10
	nop
	mov.l	.L566,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L567:
	.align 2
.L560:
	.long	1073741823
.L561:
	.long	.LC0
.L562:
	.long	log_text_raw
.L563:
	.long	log_text
.L564:
	.long	log_bytes
.L565:
	.long	.LC1
.L566:
	.long	.LC2
	.size	prim_cells, .-prim_cells
	.align 1
	.align 2
	.global	prim_c_r
	.type	prim_c_r, @function
prim_c_r:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#124,r8
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@(32,r8),r1
	tst	r1,r1
	bt/s	.L570
	mov	r4,r9
	mov.l	.L582,r4
	jsr	@r1
	nop
	mov.l	@(52,r8),r1
	tst	r1,r1
	bt	.L570
	jsr	@r1
	nop
.L570:
	mov.l	.L577,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L578,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L579,r1
	mov	#32,r5
	mov.l	.L580,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L581,r4
	jsr	@r10
	nop
	mov.l	.L582,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L583:
	.align 2
.L582:
	.long	.LC2
.L577:
	.long	log_text
.L578:
	.long	.LC0
.L579:
	.long	log_bytes
.L580:
	.long	log_text_raw
.L581:
	.long	.LC1
	.size	prim_c_r, .-prim_c_r
	.align 1
	.align 2
	.global	prim_drop
	.type	prim_drop, @function
prim_drop:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	#-1,r1
	mov.l	.L586,r10
	mov.l	r1,@r4
	mov.l	.L587,r1
	mov.l	.L588,r4
	jsr	@r1
	nop
	mov.l	.L589,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L590,r4
	jsr	@r10
	nop
	mov.l	.L591,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L592:
	.align 2
.L586:
	.long	log_text_raw
.L587:
	.long	log_text
.L588:
	.long	.LC0
.L589:
	.long	log_bytes
.L590:
	.long	.LC1
.L591:
	.long	.LC2
	.size	prim_drop, .-prim_drop
	.align 1
	.align 2
	.global	prim_two_drop
	.type	prim_two_drop, @function
prim_two_drop:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	#-2,r1
	mov.l	.L595,r10
	mov.l	r1,@r4
	mov.l	.L596,r1
	mov.l	.L597,r4
	jsr	@r1
	nop
	mov.l	.L598,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L599,r4
	jsr	@r10
	nop
	mov.l	.L600,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L601:
	.align 2
.L595:
	.long	log_text_raw
.L596:
	.long	log_text
.L597:
	.long	.LC0
.L598:
	.long	log_bytes
.L599:
	.long	.LC1
.L600:
	.long	.LC2
	.size	prim_two_drop, .-prim_two_drop
	.align 1
	.align 2
	.global	prim_dupe
	.type	prim_dupe, @function
prim_dupe:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L604,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	@(12,r9),r5
	shll2	r0
	mov.l	.L605,r10
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(4,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L606,r1
	mov.l	.L607,r4
	jsr	@r1
	nop
	mov.l	.L608,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L609,r4
	jsr	@r10
	nop
	mov.l	.L610,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L611:
	.align 2
.L604:
	.long	1073741823
.L605:
	.long	log_text_raw
.L606:
	.long	log_text
.L607:
	.long	.LC0
.L608:
	.long	log_bytes
.L609:
	.long	.LC1
.L610:
	.long	.LC2
	.size	prim_dupe, .-prim_dupe
	.align 1
	.align 2
	.global	prim_two_dupe
	.type	prim_two_dupe, @function
prim_two_dupe:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L614,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L615,r3
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov.l	.L616,r10
	mov.l	r2,@(8,r0)
	mov.l	@r4,r0
	add	r3,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(8,r1)
	mov.l	@r4,r1
	add	#2,r1
	mov.l	r1,@r4
	mov.l	.L617,r1
	mov.l	.L618,r4
	jsr	@r1
	nop
	mov.l	.L619,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L620,r4
	jsr	@r10
	nop
	mov.l	.L621,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L622:
	.align 2
.L614:
	.long	1073741822
.L615:
	.long	1073741823
.L616:
	.long	log_text_raw
.L617:
	.long	log_text
.L618:
	.long	.LC0
.L619:
	.long	log_bytes
.L620:
	.long	.LC1
.L621:
	.long	.LC2
	.size	prim_two_dupe, .-prim_two_dupe
	.align 1
	.align 2
	.global	prim_emit
	.type	prim_emit, @function
prim_emit:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L636
	add	#-8,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(32,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L626
	mov.l	r0,@r4
	mov.l	@(4,r8),r2
	shll2	r0
	mov	r15,r4
	add	#4,r4
	mov.l	@(r0,r2),r2
	mov	#0,r0
	mov.b	r0,@(1,r4)
	jsr	@r1
	mov.b	r2,@r4
	mov.l	@(52,r9),r1
	tst	r1,r1
	bt	.L626
	jsr	@r1
	nop
.L626:
	mov.l	.L637,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L638,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L639,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L640,r1
	mov.l	.L641,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L642,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#8,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L636:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#8,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L643:
	.align 2
.L637:
	.long	log_text
.L638:
	.long	.LC0
.L639:
	.long	log_bytes
.L640:
	.long	log_text_raw
.L641:
	.long	.LC1
.L642:
	.long	.LC2
	.size	prim_emit, .-prim_emit
	.align 1
	.align 2
	.global	prim_fill
	.type	prim_fill, @function
prim_fill:
	mov.l	r8,@-r15
	mov	#2,r3
	sts.l	pr,@-r15
	mov.l	@r4,r2
	add	#-8,r15
	cmp/gt	r3,r2
	bf/s	.L658
	mov	r4,r1
	mov.l	@(4,r4),r3
	mov	r2,r0
	add	#-1,r0
	mov	r2,r6
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r7
	add	#-2,r6
	add	r0,r3
	mov.l	r6,@r4
	mov	r3,r6
	add	#-4,r6
	mov.l	@r6,r6
	add	#-3,r2
	tst	r6,r6
	bf/s	.L647
	mov.l	r2,@r4
.L657:
	mov	r1,r8
	add	#64,r8
.L649:
	mov.l	.L660,r2
	mov.l	@(12,r8),r5
	mov.l	.L661,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L662,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L663,r2
	mov.l	.L664,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L665,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L647:
	mov.l	@(56,r4),r2
	cmp/hi	r6,r2
	bt	.L659
.L648:
	tst	r2,r2
	bt/s	.L657
	mov	r1,r8
	add	#-8,r3
	mov.l	@r3,r0
	add	#64,r8
	.align 2
.L650:
	mov.l	@(0,r8),r3
	dt	r2
	and	r3,r0
	mov.l	@(52,r1),r3
	mov.b	r7,@(r0,r3)
	bf/s	.L650
	add	#1,r0
	bra	.L649
	nop
	.align 1
.L658:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L659:
	bra	.L648
	mov	r6,r2
.L666:
	.align 2
.L660:
	.long	log_text
.L661:
	.long	.LC0
.L662:
	.long	log_bytes
.L663:
	.long	log_text_raw
.L664:
	.long	.LC1
.L665:
	.long	.LC2
	.size	prim_fill, .-prim_fill
	.align 1
	.align 2
	.global	prim_here
	.type	prim_here, @function
prim_here:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(60,r4),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L669,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L670,r1
	mov.l	.L671,r4
	jsr	@r1
	nop
	mov.l	.L672,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L673,r4
	jsr	@r10
	nop
	mov.l	.L674,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L675:
	.align 2
.L669:
	.long	log_text_raw
.L670:
	.long	log_text
.L671:
	.long	.LC0
.L672:
	.long	log_bytes
.L673:
	.long	.LC1
.L674:
	.long	.LC2
	.size	prim_here, .-prim_here
	.align 1
	.align 2
	.global	prim_i
	.type	prim_i, @function
prim_i:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(8,r4),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L678,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L679,r1
	mov.l	.L680,r4
	jsr	@r1
	nop
	mov.l	.L681,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L682,r4
	jsr	@r10
	nop
	mov.l	.L683,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L684:
	.align 2
.L678:
	.long	log_text_raw
.L679:
	.long	log_text
.L680:
	.long	.LC0
.L681:
	.long	log_bytes
.L682:
	.long	.LC1
.L683:
	.long	.LC2
	.size	prim_i, .-prim_i
	.align 1
	.align 2
	.global	prim_invert
	.type	prim_invert, @function
prim_invert:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L687,r2
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	.L688,r4
	add	r2,r1
	mov.l	.L689,r10
	mov.l	@r1,r2
	not	r2,r2
	mov.l	r2,@r1
	mov.l	.L690,r1
	jsr	@r1
	nop
	mov.l	.L691,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L692,r4
	jsr	@r10
	nop
	mov.l	.L693,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L694:
	.align 2
.L687:
	.long	1073741823
.L688:
	.long	.LC0
.L689:
	.long	log_text_raw
.L690:
	.long	log_text
.L691:
	.long	log_bytes
.L692:
	.long	.LC1
.L693:
	.long	.LC2
	.size	prim_invert, .-prim_invert
	.align 1
	.align 2
	.global	prim_j
	.type	prim_j, @function
prim_j:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(12,r4),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L697,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L698,r1
	mov.l	.L699,r4
	jsr	@r1
	nop
	mov.l	.L700,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L701,r4
	jsr	@r10
	nop
	mov.l	.L702,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L703:
	.align 2
.L697:
	.long	log_text_raw
.L698:
	.long	log_text
.L699:
	.long	.LC0
.L700:
	.long	log_bytes
.L701:
	.long	.LC1
.L702:
	.long	.LC2
	.size	prim_j, .-prim_j
	.align 1
	.align 2
	.global	prim_key
	.type	prim_key, @function
prim_key:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	tst	r1,r1
	bt/s	.L715
	add	#-4,r15
	mov.l	.L718,r2
	mov	r4,r9
	add	#124,r9
	mov.l	@(44,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	tst	r0,r0
	bt/s	.L716
	add	r2,r1
	mov.l	@r1,r1
	mov	#-1,r4
	tst	r1,r1
	jsr	@r0
	negc	r4,r4
	mov.l	.L718,r1
	mov	r0,r2
	mov.l	@r8,r0
	add	r1,r0
	mov.l	@(4,r8),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@(56,r9),r1
	tst	r1,r1
	bt	.L708
	jsr	@r1
	nop
.L708:
	mov.l	.L719,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L720,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L721,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L722,r1
	mov.l	.L723,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L724,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L715:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r8
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L716:
	bra	.L708
	mov.l	r0,@r1
.L725:
	.align 2
.L718:
	.long	1073741823
.L719:
	.long	log_text
.L720:
	.long	.LC0
.L721:
	.long	log_bytes
.L722:
	.long	log_text_raw
.L723:
	.long	.LC1
.L724:
	.long	.LC2
	.size	prim_key, .-prim_key
	.align 1
	.align 2
	.global	prim_l_shift
	.type	prim_l_shift, @function
prim_l_shift:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	mov.l	.L728,r4
	shld	r3,r2
	mov.l	.L729,r10
	mov.l	r2,@r1
	mov.l	.L730,r1
	jsr	@r1
	nop
	mov.l	.L731,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L732,r4
	jsr	@r10
	nop
	mov.l	.L733,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L734:
	.align 2
.L728:
	.long	.LC0
.L729:
	.long	log_text_raw
.L730:
	.long	log_text
.L731:
	.long	log_bytes
.L732:
	.long	.LC1
.L733:
	.long	.LC2
	.size	prim_l_shift, .-prim_l_shift
	.align 1
	.align 2
	.global	prim_max
	.type	prim_max, @function
prim_max:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	add	#-4,r0
	mov.l	@(r0,r1),r3
	cmp/gt	r3,r2
	bf	.L736
	mov.l	r2,@(r0,r1)
.L736:
	mov.l	.L738,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L739,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L740,r1
	mov	#32,r5
	mov.l	.L741,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L742,r4
	jsr	@r10
	nop
	mov.l	.L743,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L744:
	.align 2
.L738:
	.long	log_text
.L739:
	.long	.LC0
.L740:
	.long	log_bytes
.L741:
	.long	log_text_raw
.L742:
	.long	.LC1
.L743:
	.long	.LC2
	.size	prim_max, .-prim_max
	.align 1
	.align 2
	.global	prim_min
	.type	prim_min, @function
prim_min:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	add	#-4,r0
	mov.l	@(r0,r1),r3
	cmp/ge	r3,r2
	bt	.L746
	mov.l	r2,@(r0,r1)
.L746:
	mov.l	.L748,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L749,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L750,r1
	mov	#32,r5
	mov.l	.L751,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L752,r4
	jsr	@r10
	nop
	mov.l	.L753,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L754:
	.align 2
.L748:
	.long	log_text
.L749:
	.long	.LC0
.L750:
	.long	log_bytes
.L751:
	.long	log_text_raw
.L752:
	.long	.LC1
.L753:
	.long	.LC2
	.size	prim_min, .-prim_min
	.align 1
	.align 2
	.global	prim_mod
	.type	prim_mod, @function
prim_mod:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r3
	add	#-4,r0
	mov	r1,r2
	tst	r3,r3
	bt/s	.L756
	add	r0,r2
	mov.l	.L761,r0
	mov	r3,r5
	mov.l	@r2,r7
	jsr	@r0
	mov	r7,r4
	mul.l	r3,r0
	mov	r7,r3
	sts	macl,r1
	sub	r1,r3
.L756:
	mov.l	.L762,r1
	mov	r8,r9
	add	#64,r9
	mov.l	r3,@r2
	mov.l	.L763,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L764,r1
	mov	#32,r5
	mov.l	.L765,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L766,r4
	jsr	@r10
	nop
	mov.l	.L767,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L768:
	.align 2
.L761:
	.long	__sdivsi3_i4i
.L762:
	.long	log_text
.L763:
	.long	.LC0
.L764:
	.long	log_bytes
.L765:
	.long	log_text_raw
.L766:
	.long	.LC1
.L767:
	.long	.LC2
	.size	prim_mod, .-prim_mod
	.align 1
	.align 2
	.global	prim_negate
	.type	prim_negate, @function
prim_negate:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L771,r2
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	.L772,r4
	add	r2,r1
	mov.l	.L773,r10
	mov.l	@r1,r2
	neg	r2,r2
	mov.l	r2,@r1
	mov.l	.L774,r1
	jsr	@r1
	nop
	mov.l	.L775,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L776,r4
	jsr	@r10
	nop
	mov.l	.L777,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L778:
	.align 2
.L771:
	.long	1073741823
.L772:
	.long	.LC0
.L773:
	.long	log_text_raw
.L774:
	.long	log_text
.L775:
	.long	log_bytes
.L776:
	.long	.LC1
.L777:
	.long	.LC2
	.size	prim_negate, .-prim_negate
	.align 1
	.align 2
	.global	prim_or
	.type	prim_or, @function
prim_or:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	mov.l	.L781,r4
	or	r3,r2
	mov.l	.L782,r10
	mov.l	r2,@r1
	mov.l	.L783,r1
	jsr	@r1
	nop
	mov.l	.L784,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L785,r4
	jsr	@r10
	nop
	mov.l	.L786,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L787:
	.align 2
.L781:
	.long	.LC0
.L782:
	.long	log_text_raw
.L783:
	.long	log_text
.L784:
	.long	log_bytes
.L785:
	.long	.LC1
.L786:
	.long	.LC2
	.size	prim_or, .-prim_or
	.align 1
	.align 2
	.global	prim_over
	.type	prim_over, @function
prim_over:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L790,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	@(12,r9),r5
	shll2	r0
	mov.l	.L791,r10
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(8,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L792,r1
	mov.l	.L793,r4
	jsr	@r1
	nop
	mov.l	.L794,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L795,r4
	jsr	@r10
	nop
	mov.l	.L796,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L797:
	.align 2
.L790:
	.long	1073741822
.L791:
	.long	log_text_raw
.L792:
	.long	log_text
.L793:
	.long	.LC0
.L794:
	.long	log_bytes
.L795:
	.long	.LC1
.L796:
	.long	.LC2
	.size	prim_over, .-prim_over
	.align 1
	.align 2
	.global	prim_two_over
	.type	prim_two_over, @function
prim_two_over:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L800,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L801,r3
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov.l	.L802,r10
	mov.l	r2,@(16,r0)
	mov.l	@r4,r0
	add	r3,r0
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(16,r1)
	mov.l	@r4,r1
	add	#2,r1
	mov.l	r1,@r4
	mov.l	.L803,r1
	mov.l	.L804,r4
	jsr	@r1
	nop
	mov.l	.L805,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L806,r4
	jsr	@r10
	nop
	mov.l	.L807,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L808:
	.align 2
.L800:
	.long	1073741820
.L801:
	.long	1073741821
.L802:
	.long	log_text_raw
.L803:
	.long	log_text
.L804:
	.long	.LC0
.L805:
	.long	log_bytes
.L806:
	.long	.LC1
.L807:
	.long	.LC2
	.size	prim_two_over, .-prim_two_over
	.align 1
	.align 2
	.global	prim_page
	.type	prim_page, @function
prim_page:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#124,r8
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@(60,r8),r1
	tst	r1,r1
	bt/s	.L811
	mov	r4,r9
	jsr	@r1
	nop
	mov.l	@(52,r8),r1
	tst	r1,r1
	bt	.L811
	jsr	@r1
	nop
.L811:
	mov.l	.L817,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L818,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L819,r1
	mov	#32,r5
	mov.l	.L820,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L821,r4
	jsr	@r10
	nop
	mov.l	.L822,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L823:
	.align 2
.L817:
	.long	log_text
.L818:
	.long	.LC0
.L819:
	.long	log_bytes
.L820:
	.long	log_text_raw
.L821:
	.long	.LC1
.L822:
	.long	.LC2
	.size	prim_page, .-prim_page
	.align 1
	.align 2
	.global	prim_rote
	.type	prim_rote, @function
prim_rote:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L826,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L827,r10
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
	mov.l	.L828,r6
	mov.l	.L829,r1
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L830,r4
	add	r1,r0
	mov.l	.L831,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L832,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L833,r4
	jsr	@r10
	nop
	mov.l	.L834,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L835:
	.align 2
.L826:
	.long	1073741823
.L827:
	.long	log_text_raw
.L828:
	.long	1073741822
.L829:
	.long	1073741821
.L830:
	.long	.LC0
.L831:
	.long	log_text
.L832:
	.long	log_bytes
.L833:
	.long	.LC1
.L834:
	.long	.LC2
	.size	prim_rote, .-prim_rote
	.align 1
	.align 2
	.global	prim_minus_rote
	.type	prim_minus_rote, @function
prim_minus_rote:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L838,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L839,r10
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
	mov.l	.L840,r6
	mov.l	.L841,r1
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L842,r4
	add	r1,r0
	mov.l	.L843,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L844,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L845,r4
	jsr	@r10
	nop
	mov.l	.L846,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L847:
	.align 2
.L838:
	.long	1073741823
.L839:
	.long	log_text_raw
.L840:
	.long	1073741822
.L841:
	.long	1073741821
.L842:
	.long	.LC0
.L843:
	.long	log_text
.L844:
	.long	log_bytes
.L845:
	.long	.LC1
.L846:
	.long	.LC2
	.size	prim_minus_rote, .-prim_minus_rote
	.align 1
	.align 2
	.global	prim_r_shift
	.type	prim_r_shift, @function
prim_r_shift:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	neg	r3,r3
	mov.l	.L850,r4
	shad	r3,r2
	mov.l	.L851,r10
	mov.l	r2,@r1
	mov.l	.L852,r1
	jsr	@r1
	nop
	mov.l	.L853,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L854,r4
	jsr	@r10
	nop
	mov.l	.L855,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L856:
	.align 2
.L850:
	.long	.LC0
.L851:
	.long	log_text_raw
.L852:
	.long	log_text
.L853:
	.long	log_bytes
.L854:
	.long	.LC1
.L855:
	.long	.LC2
	.size	prim_r_shift, .-prim_r_shift
	.section	.rodata.str1.4
	.align 2
.LC3:
	.string	" "
	.text
	.align 1
	.align 2
	.global	prim_space
	.type	prim_space, @function
prim_space:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#124,r8
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@(32,r8),r1
	tst	r1,r1
	bt/s	.L859
	mov	r4,r9
	mov.l	.L865,r4
	jsr	@r1
	nop
	mov.l	@(52,r8),r1
	tst	r1,r1
	bt	.L859
	jsr	@r1
	nop
.L859:
	mov.l	.L866,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L867,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L868,r1
	mov	#32,r5
	mov.l	.L869,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L870,r4
	jsr	@r10
	nop
	mov.l	.L871,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L872:
	.align 2
.L865:
	.long	.LC3
.L866:
	.long	log_text
.L867:
	.long	.LC0
.L868:
	.long	log_bytes
.L869:
	.long	log_text_raw
.L870:
	.long	.LC1
.L871:
	.long	.LC2
	.size	prim_space, .-prim_space
	.align 1
	.align 2
	.global	prim_spaces
	.type	prim_spaces, @function
prim_spaces:
	mov.l	r8,@-r15
	mov	#1,r1
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	cmp/gt	r1,r0
	bf/s	.L891
	mov	r4,r9
	add	#-1,r0
	mov.l	@(4,r4),r1
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	cmp/pl	r2
	bf/s	.L877
	mov	r4,r11
	add	#124,r11
	mov.l	@(32,r11),r1
	tst	r1,r1
	bt	.L877
	mov.w	.L894,r3
	add	r4,r3
	mov.l	@(0,r3),r10
	cmp/gt	r2,r10
	bt	.L892
.L879:
	cmp/pl	r10
	bf	.L880
	bra	.L881
	mov	#0,r8
	.align 1
.L893:
	mov.l	@(32,r11),r1
.L881:
	mov.l	.L895,r4
	jsr	@r1
	add	#1,r8
	cmp/eq	r8,r10
	bf	.L893
.L880:
	mov.l	@(52,r11),r1
	tst	r1,r1
	bt	.L877
	jsr	@r1
	nop
.L877:
	mov.l	.L896,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L897,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L898,r1
	mov	#32,r5
	mov.l	.L899,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L900,r4
	jsr	@r10
	nop
	mov.l	.L901,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L891:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L892:
	bra	.L879
	mov	r2,r10
	.align 1
.L894:
	.short	188
.L902:
	.align 2
.L895:
	.long	.LC3
.L896:
	.long	log_text
.L897:
	.long	.LC0
.L898:
	.long	log_bytes
.L899:
	.long	log_text_raw
.L900:
	.long	.LC1
.L901:
	.long	.LC2
	.size	prim_spaces, .-prim_spaces
	.align 1
	.align 2
	.global	prim_swap
	.type	prim_swap, @function
prim_swap:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L905,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L906,r10
	add	r2,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r7
	mov.l	@r1,r3
	mov.l	r7,@r1
	mov.l	@r4,r0
	mov.l	.L907,r1
	mov.l	.L908,r4
	add	r1,r0
	mov.l	.L909,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L910,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L911,r4
	jsr	@r10
	nop
	mov.l	.L912,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L913:
	.align 2
.L905:
	.long	1073741823
.L906:
	.long	log_text_raw
.L907:
	.long	1073741822
.L908:
	.long	.LC0
.L909:
	.long	log_text
.L910:
	.long	log_bytes
.L911:
	.long	.LC1
.L912:
	.long	.LC2
	.size	prim_swap, .-prim_swap
	.align 1
	.align 2
	.global	prim_two_swap
	.type	prim_two_swap, @function
prim_two_swap:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L916,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	.L917,r10
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
	mov.l	@r3,r3
	mov.l	@r6,r6
	mov.l	r5,@r1
	mov.l	@r4,r0
	mov.l	.L918,r5
	mov.l	.L919,r1
	add	r5,r0
	mov.l	@(12,r9),r5
	shll2	r0
	mov.l	r6,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L920,r6
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L921,r4
	add	r1,r0
	mov.l	.L922,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L923,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L924,r4
	jsr	@r10
	nop
	mov.l	.L925,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L926:
	.align 2
.L916:
	.long	1073741823
.L917:
	.long	log_text_raw
.L918:
	.long	1073741822
.L919:
	.long	1073741820
.L920:
	.long	1073741821
.L921:
	.long	.LC0
.L922:
	.long	log_text
.L923:
	.long	log_bytes
.L924:
	.long	.LC1
.L925:
	.long	.LC2
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
	bf/s	.L947
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
	mov.l	@(32,r12),r1
	tst	r1,r1
	bt/s	.L948
	add	r0,r2
	mov.l	@(56,r4),r11
	add	#-4,r2
	cmp/hi	r3,r11
	bt/s	.L949
	mov.l	@r2,r8
	mov	#0,r0
	tst	r11,r11
	mov.b	r0,@(1,r15)
	mov	r13,r14
	bt/s	.L932
	add	#64,r14
.L951:
	mov	r13,r14
	mov	#0,r9
	bra	.L933
	add	#64,r14
	.align 1
.L950:
	mov.l	@(32,r12),r1
	add	#1,r8
.L933:
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
	bf	.L950
.L932:
	mov.l	@(52,r12),r1
.L959:
	tst	r1,r1
	bt	.L930
	jsr	@r1
	nop
.L930:
	mov.l	.L952,r1
	mov.l	.L953,r4
	jsr	@r1
	mov.l	@(12,r14),r5
	mov.l	.L954,r1
	mov	#32,r5
	mov.l	.L955,r8
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L956,r4
	jsr	@r8
	nop
	mov.l	.L957,r4
	jsr	@r8
	nop
	mov.l	@(12,r14),r1
	mov	r13,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r14)
	mov.l	@(4,r1),r1
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
.L949:
	mov	#0,r0
	mov	r3,r11
	mov.b	r0,@(1,r15)
	tst	r11,r11
	mov	r13,r14
	bf/s	.L951
	add	#64,r14
	bra	.L959
	mov.l	@(52,r12),r1
	.align 1
.L947:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
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
	.align 1
.L948:
	mov	r4,r14
	bra	.L930
	add	#64,r14
.L958:
	.align 2
.L952:
	.long	log_text
.L953:
	.long	.LC0
.L954:
	.long	log_bytes
.L955:
	.long	log_text_raw
.L956:
	.long	.LC1
.L957:
	.long	.LC2
	.size	prim_type, .-prim_type
	.align 1
	.align 2
	.global	prim_u_less_than
	.type	prim_u_less_than, @function
prim_u_less_than:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	mov.l	.L962,r4
	cmp/hi	r2,r3
	mov.l	.L963,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L964,r1
	jsr	@r1
	nop
	mov.l	.L965,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L966,r4
	jsr	@r10
	nop
	mov.l	.L967,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L968:
	.align 2
.L962:
	.long	.LC0
.L963:
	.long	log_text_raw
.L964:
	.long	log_text
.L965:
	.long	log_bytes
.L966:
	.long	.LC1
.L967:
	.long	.LC2
	.size	prim_u_less_than, .-prim_u_less_than
	.align 1
	.align 2
	.global	prim_u_greater_than
	.type	prim_u_greater_than, @function
prim_u_greater_than:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r2
	mov.l	@r1,r3
	mov.l	.L971,r4
	cmp/hi	r2,r3
	mov.l	.L972,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L973,r1
	jsr	@r1
	nop
	mov.l	.L974,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L975,r4
	jsr	@r10
	nop
	mov.l	.L976,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L977:
	.align 2
.L971:
	.long	.LC0
.L972:
	.long	log_text_raw
.L973:
	.long	log_text
.L974:
	.long	log_bytes
.L975:
	.long	.LC1
.L976:
	.long	.LC2
	.size	prim_u_greater_than, .-prim_u_greater_than
	.align 1
	.align 2
	.global	prim_x_or
	.type	prim_x_or, @function
prim_x_or:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r3,r1
	mov.l	@(r0,r3),r3
	mov.l	@r1,r2
	mov.l	.L980,r4
	xor	r3,r2
	mov.l	.L981,r10
	mov.l	r2,@r1
	mov.l	.L982,r1
	jsr	@r1
	nop
	mov.l	.L983,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L984,r4
	jsr	@r10
	nop
	mov.l	.L985,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L986:
	.align 2
.L980:
	.long	.LC0
.L981:
	.long	log_text_raw
.L982:
	.long	log_text
.L983:
	.long	log_bytes
.L984:
	.long	.LC1
.L985:
	.long	.LC2
	.size	prim_x_or, .-prim_x_or
	.align 1
	.align 2
	.global	prim_not_equals
	.type	prim_not_equals, @function
prim_not_equals:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov	r0,r1
	add	#-4,r1
	add	r2,r1
	mov.l	@(r0,r2),r3
	mov.l	@r1,r2
	mov.l	.L989,r4
	cmp/eq	r2,r3
	mov.l	.L990,r10
	subc	r2,r2
	not	r2,r2
	mov.l	r2,@r1
	mov.l	.L991,r1
	jsr	@r1
	nop
	mov.l	.L992,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L993,r4
	jsr	@r10
	nop
	mov.l	.L994,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L995:
	.align 2
.L989:
	.long	.LC0
.L990:
	.long	log_text_raw
.L991:
	.long	log_text
.L992:
	.long	log_bytes
.L993:
	.long	.LC1
.L994:
	.long	.LC2
	.size	prim_not_equals, .-prim_not_equals
	.align 1
	.align 2
	.global	prim_false
	.type	prim_false, @function
prim_false:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	shll2	r2
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L998,r10
	mov	#0,r2
	mov.l	r2,@r1
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L999,r1
	mov.l	.L1000,r4
	jsr	@r1
	nop
	mov.l	.L1001,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1002,r4
	jsr	@r10
	nop
	mov.l	.L1003,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1004:
	.align 2
.L998:
	.long	log_text_raw
.L999:
	.long	log_text
.L1000:
	.long	.LC0
.L1001:
	.long	log_bytes
.L1002:
	.long	.LC1
.L1003:
	.long	.LC2
	.size	prim_false, .-prim_false
	.align 1
	.align 2
	.global	prim_true
	.type	prim_true, @function
prim_true:
	mov.l	.L1006,r1
	jmp	@r1
	nop
.L1007:
	.align 2
.L1006:
	.long	prim_false
	.size	prim_true, .-prim_true
	.align 1
	.align 2
	.global	prim_nip
	.type	prim_nip, @function
prim_nip:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	@(12,r9),r5
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	add	r0,r1
	add	#-4,r1
	mov.l	.L1010,r4
	mov.l	r2,@r1
	mov.l	.L1011,r1
	mov.l	.L1012,r10
	jsr	@r1
	nop
	mov.l	.L1013,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1014,r4
	jsr	@r10
	nop
	mov.l	.L1015,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1016:
	.align 2
.L1010:
	.long	.LC0
.L1011:
	.long	log_text
.L1012:
	.long	log_text_raw
.L1013:
	.long	log_bytes
.L1014:
	.long	.LC1
.L1015:
	.long	.LC2
	.size	prim_nip, .-prim_nip
	.align 1
	.align 2
	.global	prim_tuck
	.type	prim_tuck, @function
prim_tuck:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	.L1020,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L1020,r7
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov	r0,r3
	add	#-4,r3
	mov.l	@r3,r3
	mov.l	r2,@(4,r0)
	mov.l	@r4,r0
	mov.l	.L1021,r10
	add	r7,r0
	shll2	r0
	mov.l	r3,@(r0,r1)
	mov.l	@r4,r0
	mov.l	.L1022,r3
	add	r3,r0
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L1023,r1
	mov.l	.L1024,r4
	jsr	@r1
	nop
	mov.l	.L1025,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1026,r4
	jsr	@r10
	nop
	mov.l	.L1027,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1028:
	.align 2
.L1020:
	.long	1073741823
.L1021:
	.long	log_text_raw
.L1022:
	.long	1073741822
.L1023:
	.long	log_text
.L1024:
	.long	.LC0
.L1025:
	.long	log_bytes
.L1026:
	.long	.LC1
.L1027:
	.long	.LC2
	.size	prim_tuck, .-prim_tuck
	.align 1
	.align 2
	.global	prim_unused
	.type	prim_unused, @function
prim_unused:
	mov.l	r8,@-r15
	mov	r4,r1
	sts.l	pr,@-r15
	mov.w	.L1034,r2
	mov.l	@r4,r0
	cmp/gt	r2,r0
	bf/s	.L1030
	add	#-8,r15
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L1030:
	mov.l	@(60,r4),r7
	shll2	r0
	mov.l	@(56,r4),r2
	mov	r4,r8
	mov.l	@(4,r4),r3
	add	#64,r8
	sub	r7,r2
	mov.l	@(12,r8),r5
	mov.l	r2,@(r0,r3)
	mov.l	@r4,r2
	add	#1,r2
	mov.l	r2,@r4
	mov.l	.L1035,r2
	mov.l	.L1036,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L1037,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L1038,r2
	mov.l	.L1039,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L1040,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L1034:
	.short	255
.L1041:
	.align 2
.L1035:
	.long	log_text
.L1036:
	.long	.LC0
.L1037:
	.long	log_bytes
.L1038:
	.long	log_text_raw
.L1039:
	.long	.LC1
.L1040:
	.long	.LC2
	.size	prim_unused, .-prim_unused
	.align 1
	.align 2
	.global	prim_within
	.type	prim_within, @function
prim_within:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r2
	mov.l	@(4,r4),r1
	mov	r2,r0
	add	#-1,r0
	mov.l	r0,@r4
	add	#-2,r2
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r7
	mov.l	r2,@r4
	mov	r0,r2
	add	#-8,r2
	mov.l	.L1044,r4
	add	r1,r2
	mov.l	.L1045,r10
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
	mov.l	r1,@r2
	mov.l	.L1046,r1
	jsr	@r1
	nop
	mov.l	.L1047,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1048,r4
	jsr	@r10
	nop
	mov.l	.L1049,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1050:
	.align 2
.L1044:
	.long	.LC0
.L1045:
	.long	log_text_raw
.L1046:
	.long	log_text
.L1047:
	.long	log_bytes
.L1048:
	.long	.LC1
.L1049:
	.long	.LC2
	.size	prim_within, .-prim_within
	.align 1
	.align 2
	.global	prim_bye
	.type	prim_bye, @function
prim_bye:
	mov.l	r8,@-r15
	mov	#1,r0
	mov.l	r9,@-r15
	mov	#0,r2
	mov.l	r10,@-r15
	mov	r4,r1
	sts.l	pr,@-r15
	add	#80,r1
	mov	r4,r8
	mov.b	r0,@(1,r1)
	add	#64,r8
	mov.b	r2,@r1
	mov	r4,r9
	mov.l	.L1053,r1
	mov.l	.L1054,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1055,r1
	mov	#32,r5
	mov.l	.L1056,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1057,r4
	jsr	@r10
	nop
	mov.l	.L1058,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1059:
	.align 2
.L1053:
	.long	log_text
.L1054:
	.long	.LC0
.L1055:
	.long	log_bytes
.L1056:
	.long	log_text_raw
.L1057:
	.long	.LC1
.L1058:
	.long	.LC2
	.size	prim_bye, .-prim_bye
	.align 1
	.align 2
	.global	prim_reset
	.type	prim_reset, @function
prim_reset:
	mov.l	r8,@-r15
	mov	#0,r1
	mov.l	r9,@-r15
	mov	r4,r8
	mov.l	r10,@-r15
	add	#64,r8
	sts.l	pr,@-r15
	mov.l	r1,@r4
	mov	r4,r9
	mov.l	.L1062,r1
	mov.l	.L1063,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1064,r1
	mov	#32,r5
	mov.l	.L1065,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1066,r4
	jsr	@r10
	nop
	mov.l	.L1067,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1068:
	.align 2
.L1062:
	.long	log_text
.L1063:
	.long	.LC0
.L1064:
	.long	log_bytes
.L1065:
	.long	log_text_raw
.L1066:
	.long	.LC1
.L1067:
	.long	.LC2
	.size	prim_reset, .-prim_reset
	.align 1
	.align 2
	.global	prim_walign
	.type	prim_walign, @function
prim_walign:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	r4,r9
	sts.l	pr,@-r15
	mov.l	@(60,r4),r1
	mov.l	@(4,r8),r2
	add	#1,r1
	mov.l	@(12,r8),r5
	and	r2,r1
	mov.l	.L1071,r10
	mov	#-2,r2
	and	r2,r1
	mov.l	r1,@(60,r4)
	mov.l	.L1072,r1
	mov.l	.L1073,r4
	jsr	@r1
	nop
	mov.l	.L1074,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1075,r4
	jsr	@r10
	nop
	mov.l	.L1076,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1077:
	.align 2
.L1071:
	.long	log_text_raw
.L1072:
	.long	log_text
.L1073:
	.long	.LC0
.L1074:
	.long	log_bytes
.L1075:
	.long	.LC1
.L1076:
	.long	.LC2
	.size	prim_walign, .-prim_walign
	.align 1
	.align 2
	.global	prim_waligned
	.type	prim_waligned, @function
prim_waligned:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	r4,r9
	sts.l	pr,@-r15
	mov.l	.L1080,r2
	mov.l	@r4,r1
	mov.l	@(4,r8),r3
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r8),r5
	add	r1,r2
	mov.l	.L1081,r4
	mov.l	@r2,r1
	mov.l	.L1082,r10
	add	#1,r1
	and	r3,r1
	mov	#-2,r3
	and	r3,r1
	mov.l	r1,@r2
	mov.l	.L1083,r1
	jsr	@r1
	nop
	mov.l	.L1084,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1085,r4
	jsr	@r10
	nop
	mov.l	.L1086,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1087:
	.align 2
.L1080:
	.long	1073741823
.L1081:
	.long	.LC0
.L1082:
	.long	log_text_raw
.L1083:
	.long	log_text
.L1084:
	.long	log_bytes
.L1085:
	.long	.LC1
.L1086:
	.long	.LC2
	.size	prim_waligned, .-prim_waligned
	.align 1
	.align 2
	.global	prim_printable
	.type	prim_printable, @function
prim_printable:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	.L1092,r2
	mov.l	@r4,r1
	mov.l	@(4,r4),r9
	add	r2,r1
	shll2	r1
	add	r1,r9
	mov	r4,r1
	add	#124,r1
	mov.l	@(48,r1),r0
	tst	r0,r0
	bt/s	.L1090
	mov	r4,r8
	jsr	@r0
	mov.l	@r9,r4
.L1089:
	mov.l	.L1093,r1
	mov.l	r0,@r9
	mov	r8,r9
	add	#64,r9
	mov.l	.L1094,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1095,r1
	mov	#32,r5
	mov.l	.L1096,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1097,r4
	jsr	@r10
	nop
	mov.l	.L1098,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1090:
	bra	.L1089
	mov	#0,r0
.L1099:
	.align 2
.L1092:
	.long	1073741823
.L1093:
	.long	log_text
.L1094:
	.long	.LC0
.L1095:
	.long	log_bytes
.L1096:
	.long	log_text_raw
.L1097:
	.long	.LC1
.L1098:
	.long	.LC2
	.size	prim_printable, .-prim_printable
	.align 1
	.align 2
	.global	prim_erase
	.type	prim_erase, @function
prim_erase:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
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
	bf	.L1101
	mov	r3,r1
.L1101:
	tst	r1,r1
	mov	r8,r9
	bt/s	.L1102
	add	#64,r9
	add	r0,r2
	mov	r8,r9
	add	#-4,r2
	mov.l	@r2,r0
	add	#64,r9
	mov	#0,r3
	.align 2
.L1103:
	mov.l	@(0,r9),r2
	dt	r1
	and	r2,r0
	mov.l	@(52,r8),r2
	mov.b	r3,@(r0,r2)
	bf/s	.L1103
	add	#1,r0
.L1102:
	mov.l	.L1109,r1
	mov.l	.L1110,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1111,r1
	mov	#32,r5
	mov.l	.L1112,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1113,r4
	jsr	@r10
	nop
	mov.l	.L1114,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1115:
	.align 2
.L1109:
	.long	log_text
.L1110:
	.long	.LC0
.L1111:
	.long	log_bytes
.L1112:
	.long	log_text_raw
.L1113:
	.long	.LC1
.L1114:
	.long	.LC2
	.size	prim_erase, .-prim_erase
	.align 1
	.align 2
	.global	prim_cxt
	.type	prim_cxt, @function
prim_cxt:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	.L1122,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r0
	tst	#128,r0
	bt/s	.L1118
	extu.b	r0,r2
	mov.w	.L1123,r2
	or	r0,r2
.L1118:
	mov.l	r2,@r1
	mov	r8,r9
	mov.l	.L1124,r1
	add	#64,r9
	mov.l	.L1125,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1126,r1
	mov	#32,r5
	mov.l	.L1127,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1128,r4
	jsr	@r10
	nop
	mov.l	.L1129,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1123:
	.short	-256
.L1130:
	.align 2
.L1122:
	.long	1073741823
.L1124:
	.long	log_text
.L1125:
	.long	.LC0
.L1126:
	.long	log_bytes
.L1127:
	.long	log_text_raw
.L1128:
	.long	.LC1
.L1129:
	.long	.LC2
	.size	prim_cxt, .-prim_cxt
	.align 1
	.align 2
	.global	prim_wxt
	.type	prim_wxt, @function
prim_wxt:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	.L1137,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	.L1138,r2
	mov.l	@r1,r3
	tst	r2,r3
	bt/s	.L1133
	extu.w	r3,r2
	mov.l	.L1139,r2
	or	r3,r2
.L1133:
	mov.l	r2,@r1
	mov	r8,r9
	mov.l	.L1140,r1
	add	#64,r9
	mov.l	.L1141,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1142,r1
	mov	#32,r5
	mov.l	.L1143,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1144,r4
	jsr	@r10
	nop
	mov.l	.L1145,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1146:
	.align 2
.L1137:
	.long	1073741823
.L1138:
	.long	32768
.L1139:
	.long	-65536
.L1140:
	.long	log_text
.L1141:
	.long	.LC0
.L1142:
	.long	log_bytes
.L1143:
	.long	log_text_raw
.L1144:
	.long	.LC1
.L1145:
	.long	.LC2
	.size	prim_wxt, .-prim_wxt
	.align 1
	.align 2
	.global	prim_perf
	.type	prim_perf, @function
prim_perf:
	mov.l	r8,@-r15
	mov	r4,r1
	sts.l	pr,@-r15
	mov.w	.L1152,r2
	mov.l	@r4,r0
	cmp/gt	r2,r0
	bf/s	.L1148
	add	#-8,r15
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L1148:
	mov	r4,r8
	add	#64,r8
	mov.l	@(52,r8),r3
	shll2	r0
	mov.l	@(4,r4),r2
	mov.l	@(12,r8),r5
	mov.l	r3,@(r0,r2)
	mov.l	@r4,r2
	add	#1,r2
	mov.l	r2,@r4
	mov.l	.L1153,r2
	mov.l	.L1154,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L1155,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L1156,r2
	mov.l	.L1157,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L1158,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L1152:
	.short	255
.L1159:
	.align 2
.L1153:
	.long	log_text
.L1154:
	.long	.LC0
.L1155:
	.long	log_bytes
.L1156:
	.long	log_text_raw
.L1157:
	.long	.LC1
.L1158:
	.long	.LC2
	.size	prim_perf, .-prim_perf
	.align 1
	.align 2
	.global	prim_size
	.type	prim_size, @function
prim_size:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@r4,r0
	mov.l	@(56,r4),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L1162,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L1163,r1
	mov.l	.L1164,r4
	jsr	@r1
	nop
	mov.l	.L1165,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1166,r4
	jsr	@r10
	nop
	mov.l	.L1167,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1168:
	.align 2
.L1162:
	.long	log_text_raw
.L1163:
	.long	log_text
.L1164:
	.long	.LC0
.L1165:
	.long	log_bytes
.L1166:
	.long	.LC1
.L1167:
	.long	.LC2
	.size	prim_size, .-prim_size
	.section	.rodata.str1.4
	.align 2
.LC4:
	.string	"prim_hidden_dot_quote"
	.align 2
.LC5:
	.string	"engine->address: %p\n"
	.align 2
.LC6:
	.string	"length address: %p\n"
	.align 2
.LC7:
	.string	"quote_length: %u\n"
	.align 2
.LC8:
	.string	"text: %p\n"
	.align 2
.LC9:
	.string	"character: %c (%d)\n"
	.align 2
.LC10:
	.string	"printed: %s\n"
	.align 2
.LC11:
	.string	"text after printing: %p\n"
	.align 2
.LC12:
	.string	"ptr_size: %u\n"
	.align 2
.LC13:
	.string	"new text: %p\n"
	.align 2
.LC14:
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
	mov.l	r12,@-r15
	mov	r4,r12
	mov.l	r13,@-r15
	add	#64,r12
	mov.l	r14,@-r15
	sts.l	pr,@-r15
	mov.l	@(12,r12),r10
	add	#-12,r15
	mov.l	.L1185,r5
	mov	r15,r9
	mov.l	@(4,r10),r1
	mov	r10,r14
	mov.l	r4,@(4,r15)
	mov	#16,r4
	mov.l	r1,@r15
	add	#8,r14
	mov.l	.L1186,r1
	mov.l	.L1187,r8
	jsr	@r1
	add	#8,r9
	mov.l	.L1188,r4
	jsr	@r8
	mov.l	@(12,r12),r5
	mov.l	@(12,r12),r5
	mov.l	.L1189,r4
	jsr	@r8
	add	#4,r5
	mov.l	.L1190,r4
	jsr	@r8
	mov.l	@r15,r5
	mov.l	.L1191,r4
	jsr	@r8
	mov	r14,r5
	mov.l	@r15,r1
	mov	#0,r0
	tst	r1,r1
	bt/s	.L1184
	mov.b	r0,@(1,r9)
	mov.l	@r15,r2
	mov	r14,r13
	mov.l	@(4,r15),r11
	add	r2,r10
	add	#8,r10
	add	#124,r11
	.align 2
.L1172:
	mov.b	@r13+,r5
	mov.l	.L1192,r4
	jsr	@r8
	mov	r5,r6
	mov.l	@(32,r11),r2
	tst	r2,r2
	bt/s	.L1171
	mov	r13,r0
	add	#-16,r0
	mov.b	@(15,r0),r0
	mov	r9,r4
	jsr	@r2
	mov.b	r0,@r9
	mov.l	.L1193,r4
	jsr	@r8
	mov	r9,r5
.L1171:
	cmp/eq	r13,r10
	bf/s	.L1172
	mov.l	@r15,r1
	add	r1,r14
.L1170:
	mov.l	@(52,r11),r1
	tst	r1,r1
	bt	.L1173
	jsr	@r1
	nop
.L1173:
	mov.l	.L1194,r4
	jsr	@r8
	mov	r14,r5
	mov.l	@r15,r2
	mov	#4,r5
	mov.l	.L1195,r4
	neg	r2,r0
	and	#3,r0
	add	r0,r14
	mov	r14,r1
	add	#-4,r1
	jsr	@r8
	mov.l	r1,@(12,r12)
	mov.l	.L1196,r4
	jsr	@r8
	mov	r14,r5
	mov.l	.L1197,r4
	jsr	@r8
	mov.l	@(12,r12),r5
	mov.l	.L1198,r1
	jsr	@r1
	nop
	mov.l	.L1199,r4
	jsr	@r8
	mov.l	@(12,r12),r5
	mov.l	.L1200,r1
	mov	#32,r5
	mov.l	.L1201,r8
	jsr	@r1
	mov.l	@(12,r12),r4
	mov.l	.L1202,r4
	jsr	@r8
	nop
	mov.l	.L1203,r4
	jsr	@r8
	nop
	mov.l	@(12,r12),r1
	mov.l	@(4,r15),r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r12)
	mov.l	@(4,r1),r1
	add	#12,r15
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
.L1184:
	mov.l	@(4,r15),r11
	bra	.L1170
	add	#124,r11
.L1204:
	.align 2
.L1185:
	.long	.LC4
.L1186:
	.long	log_push
.L1187:
	.long	log_text
.L1188:
	.long	.LC5
.L1189:
	.long	.LC6
.L1190:
	.long	.LC7
.L1191:
	.long	.LC8
.L1192:
	.long	.LC9
.L1193:
	.long	.LC10
.L1194:
	.long	.LC11
.L1195:
	.long	.LC12
.L1196:
	.long	.LC13
.L1197:
	.long	.LC14
.L1198:
	.long	log_pop
.L1199:
	.long	.LC0
.L1200:
	.long	log_bytes
.L1201:
	.long	log_text_raw
.L1202:
	.long	.LC1
.L1203:
	.long	.LC2
	.size	prim_hidden_dot_quote, .-prim_hidden_dot_quote
	.section	.rodata.str1.4
	.align 2
.LC15:
	.string	"allot"
	.align 2
.LC16:
	.string	"data_index: %d\n"
	.align 2
.LC17:
	.string	"new data_index: %d\n"
	.text
	.align 1
	.align 2
	.global	prim_allot
	.type	prim_allot, @function
prim_allot:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	.L1211,r1
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	.L1212,r5
	sts.l	pr,@-r15
	jsr	@r1
	mov	#11,r4
	mov.l	.L1213,r9
	mov.l	.L1214,r4
	jsr	@r9
	mov.l	@(60,r8),r5
	mov.l	@r8,r0
	tst	r0,r0
	bf/s	.L1206
	mov	#10,r2
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1206:
	mov.l	@(4,r8),r1
	add	#-1,r0
	mov.l	r0,@r8
	shll2	r0
	mov.l	@(r0,r1),r5
	mov	r8,r10
	mov.l	@(60,r8),r1
	add	#64,r10
	mov.l	.L1215,r4
	add	r1,r5
	mov.l	@(0,r10),r1
	and	r1,r5
	jsr	@r9
	mov.l	r5,@(60,r8)
	mov.l	.L1216,r1
	jsr	@r1
	nop
	mov.l	.L1217,r4
	jsr	@r9
	mov.l	@(12,r10),r5
	mov.l	.L1218,r1
	mov	#32,r5
	mov.l	.L1219,r9
	jsr	@r1
	mov.l	@(12,r10),r4
	mov.l	.L1220,r4
	jsr	@r9
	nop
	mov.l	.L1221,r4
	jsr	@r9
	nop
	mov.l	@(12,r10),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r10)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1222:
	.align 2
.L1211:
	.long	log_push
.L1212:
	.long	.LC15
.L1213:
	.long	log_text
.L1214:
	.long	.LC16
.L1215:
	.long	.LC17
.L1216:
	.long	log_pop
.L1217:
	.long	.LC0
.L1218:
	.long	log_bytes
.L1219:
	.long	log_text_raw
.L1220:
	.long	.LC1
.L1221:
	.long	.LC2
	.size	prim_allot, .-prim_allot
	.align 1
	.align 2
	.global	prim_dot
	.type	prim_dot, @function
prim_dot:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L1236
	add	#-16,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(32,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L1226
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	mov.l	.L1237,r1
	jsr	@r1
	add	#4,r5
	mov.l	@(32,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(32,r9),r1
	mov.l	.L1238,r4
	jsr	@r1
	nop
	mov.l	@(52,r9),r1
	tst	r1,r1
	bt	.L1226
	jsr	@r1
	nop
.L1226:
	mov.l	.L1239,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L1240,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1241,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1242,r1
	mov.l	.L1243,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1244,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1236:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L1245:
	.align 2
.L1237:
	.long	text_int32
.L1238:
	.long	.LC3
.L1239:
	.long	log_text
.L1240:
	.long	.LC0
.L1241:
	.long	log_bytes
.L1242:
	.long	log_text_raw
.L1243:
	.long	.LC1
.L1244:
	.long	.LC2
	.size	prim_dot, .-prim_dot
	.align 1
	.align 2
	.global	prim_question
	.type	prim_question, @function
prim_question:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	mov	r4,r10
	sts.l	pr,@-r15
	add	#124,r10
	mov.l	@r4,r0
	mov.l	@(32,r10),r1
	add	#-12,r15
	add	#-1,r0
	mov.l	r0,@r4
	tst	r1,r1
	bt/s	.L1247
	add	#64,r9
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(r0,r1),r0
	mov.l	@(8,r9),r1
	and	r1,r0
	mov.l	@(52,r4),r1
	mov.l	@(r0,r1),r4
	mov.l	.L1255,r1
	jsr	@r1
	mov	r15,r5
	mov.l	@(32,r10),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(32,r10),r1
	mov.l	.L1256,r4
	jsr	@r1
	nop
	mov.l	@(52,r10),r1
	tst	r1,r1
	bt	.L1247
	jsr	@r1
	nop
.L1247:
	mov.l	.L1257,r1
	mov.l	.L1258,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1259,r1
	mov	#32,r5
	mov.l	.L1260,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1261,r4
	jsr	@r10
	nop
	mov.l	.L1262,r4
	jsr	@r10
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#12,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1263:
	.align 2
.L1255:
	.long	text_int32
.L1256:
	.long	.LC3
.L1257:
	.long	log_text
.L1258:
	.long	.LC0
.L1259:
	.long	log_bytes
.L1260:
	.long	log_text_raw
.L1261:
	.long	.LC1
.L1262:
	.long	.LC2
	.size	prim_question, .-prim_question
	.align 1
	.align 2
	.global	prim_u_dot
	.type	prim_u_dot, @function
prim_u_dot:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L1277
	add	#-16,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(32,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L1267
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	mov.l	.L1278,r1
	jsr	@r1
	add	#4,r5
	mov.l	@(32,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(32,r9),r1
	mov.l	.L1279,r4
	jsr	@r1
	nop
	mov.l	@(52,r9),r1
	tst	r1,r1
	bt	.L1267
	jsr	@r1
	nop
.L1267:
	mov.l	.L1280,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L1281,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1282,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1283,r1
	mov.l	.L1284,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1285,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1277:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L1286:
	.align 2
.L1278:
	.long	text_uint32
.L1279:
	.long	.LC3
.L1280:
	.long	log_text
.L1281:
	.long	.LC0
.L1282:
	.long	log_bytes
.L1283:
	.long	log_text_raw
.L1284:
	.long	.LC1
.L1285:
	.long	.LC2
	.size	prim_u_dot, .-prim_u_dot
	.align 1
	.align 2
	.global	prim_execute
	.type	prim_execute, @function
prim_execute:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	tst	r1,r1
	bt/s	.L1302
	add	#-4,r15
	mov.l	@(4,r4),r2
	add	#-1,r1
	mov.l	r1,@r4
	shll2	r1
	add	r2,r1
	mov.w	.L1305,r2
	mov.l	@r1,r4
	cmp/hi	r2,r4
	bt/s	.L1290
	mov	#5,r7
	mov.l	.L1306,r1
	shld	r7,r4
	add	r4,r1
	mov.l	@(16,r1),r2
	tst	r2,r2
	bt/s	.L1291
	mov	r8,r4
	jsr	@r2
	mov	r8,r9
	add	#64,r9
	mov.l	@(12,r9),r5
.L1292:
	mov.l	.L1307,r1
	mov.l	.L1308,r4
	jsr	@r1
	nop
	mov.l	.L1309,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1310,r1
	mov.l	.L1311,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1312,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1290:
	mov	r8,r9
	add	#64,r9
	mov.l	@(32,r9),r2
	mov.w	.L1313,r3
	add	r3,r2
	cmp/hi	r4,r2
	bf/s	.L1293
	mov	#5,r2
	mov.w	.L1314,r7
	add	r7,r4
	shld	r2,r4
	mov.l	@(24,r9),r2
	add	r4,r2
	mov	r2,r0
	add	#16,r0
	mov.b	@(12,r0),r0
	extu.b	r0,r0
	cmp/eq	#4,r0
	bt/s	.L1303
	mov.l	@(12,r9),r5
	add	#-1,r0
	extu.b	r0,r0
	mov	#2,r3
	cmp/hi	r3,r0
	bt	.L1296
	mov.l	@r2,r2
	mov.l	@(4,r2),r2
	mov.l	r2,@r1
	mov.l	@r8,r1
	add	#1,r1
	bra	.L1292
	mov.l	r1,@r8
	.align 1
.L1302:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r8
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1303:
	mov.l	@(20,r2),r2
	mov	#9,r3
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(28,r1)
	mov	#0,r2
	mov.l	r3,@(12,r1)
	mov	r8,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L1292
	nop
	.align 1
.L1293:
	mov.l	.L1315,r1
	mov.w	.L1316,r5
	jsr	@r1
	add	r8,r5
	mov	#1,r2
	mov	r8,r1
	add	#124,r1
	mov.l	@(12,r9),r5
	mov.l	r2,@(12,r1)
	mov	#0,r2
	mov	r8,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L1292
	nop
	.align 1
.L1291:
	mov.l	@r1,r1
	mov	#2,r7
	mov	r8,r3
	add	#124,r3
	mov.l	r1,@(28,r3)
	mov	r8,r9
	mov.l	r7,@(12,r3)
	add	#64,r9
	mov	r8,r1
	add	#80,r1
	mov.l	@(12,r9),r5
	mov.b	r2,@r1
	bra	.L1292
	nop
	.align 1
.L1296:
	mov.l	@(24,r8),r1
	mov.l	@(20,r8),r3
	cmp/hs	r3,r1
	bf/s	.L1304
	mov	#1,r0
	mov.l	@(20,r9),r3
	add	#1,r3
	mov.l	r3,@(20,r9)
	mov.l	@(28,r9),r3
	mov.b	r0,@(14,r1)
	sub	r3,r5
	mov.w	@(26,r2),r0
	mov.l	r5,@r1
	mov.l	@(20,r9),r3
	mov.l	@(24,r8),r1
	mov.l	@(32,r8),r7
	mov.l	r3,@(8,r1)
	mov.w	r0,@(12,r1)
	extu.w	r0,r0
	mov.l	@(36,r8),r3
	shll2	r0
	sub	r0,r3
	cmp/hs	r7,r3
	bt/s	.L1298
	mov.l	r3,@(36,r8)
	mov	#5,r7
	mov	r8,r3
	add	#124,r3
	mov.l	r7,@(12,r3)
	mov	#0,r7
	mov	r8,r3
	add	#80,r3
	mov.b	r7,@r3
.L1298:
	mov.l	@r2,r5
	add	#-16,r1
	mov.l	r1,@(24,r8)
	add	#-4,r5
	bra	.L1292
	mov.l	r5,@(12,r9)
	.align 1
.L1304:
	mov	#7,r2
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	mov	#0,r2
	mov	r8,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L1292
	nop
	.align 1
.L1305:
	.short	150
.L1313:
	.short	151
.L1314:
	.short	-151
.L1316:
	.short	140
.L1317:
	.align 2
.L1306:
	.long	forth_primitives
.L1307:
	.long	log_text
.L1308:
	.long	.LC0
.L1309:
	.long	log_bytes
.L1310:
	.long	log_text_raw
.L1311:
	.long	.LC1
.L1312:
	.long	.LC2
.L1315:
	.long	text_uint32
	.size	prim_execute, .-prim_execute
	.align 1
	.align 2
	.global	prim_x_dot
	.type	prim_x_dot, @function
prim_x_dot:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L1331
	add	#-16,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(32,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L1321
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	mov.l	.L1332,r1
	jsr	@r1
	add	#4,r5
	mov.l	@(32,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(32,r9),r1
	mov.l	.L1333,r4
	jsr	@r1
	nop
	mov.l	@(52,r9),r1
	tst	r1,r1
	bt	.L1321
	jsr	@r1
	nop
.L1321:
	mov.l	.L1334,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L1335,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1336,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1337,r1
	mov.l	.L1338,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1339,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1331:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L1340:
	.align 2
.L1332:
	.long	text_hex32
.L1333:
	.long	.LC3
.L1334:
	.long	log_text
.L1335:
	.long	.LC0
.L1336:
	.long	log_bytes
.L1337:
	.long	log_text_raw
.L1338:
	.long	.LC1
.L1339:
	.long	.LC2
	.size	prim_x_dot, .-prim_x_dot
	.align 1
	.align 2
	.global	prim_number_to
	.type	prim_number_to, @function
prim_number_to:
	mov.l	r8,@-r15
	mov	#1,r1
	mov.l	r9,@-r15
	mov	r4,r8
	sts.l	pr,@-r15
	mov.l	@r4,r0
	cmp/gt	r1,r0
	bf/s	.L1365
	add	#-16,r15
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r2
	add	r0,r3
	add	#-4,r3
	mov	r15,r9
	mov.l	@r3,r4
	add	#4,r9
	mov.l	.L1367,r3
	mov	r9,r5
	jsr	@r3
	mov.l	r2,@r15
	mov.l	@r15,r2
	mov	#0,r6
	mov	r9,r3
.L1346:
	mov.l	@r3+,r7
	cmp/str	r6,r7
	bf	.L1346
	add	#-4,r3
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1344
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1344
	mov.b	@r3+,r7
	tst	r7,r7
	mov	#-1,r7
	subc	r7,r3
.L1344:
	sett
	mov	r3,r7
	subc	r9,r7
	tst	r7,r7
	bt/s	.L1366
	mov	r9,r5
	mov	r8,r9
	add	#64,r9
	mov	r7,r1
	.align 2
.L1349:
	mov.l	@(0,r9),r0
	dt	r1
	mov.b	@r5+,r3
	and	r2,r0
	mov.l	@(52,r8),r2
	mov.b	r3,@(r0,r2)
	mov	r0,r2
	bf/s	.L1349
	add	#1,r2
.L1348:
	mov.l	@r8,r0
	mov.l	.L1368,r1
	mov.l	@(12,r9),r5
	add	r1,r0
	mov.l	@(4,r8),r1
	shll2	r0
	mov.l	.L1369,r4
	mov.l	r7,@(r0,r1)
	mov.l	.L1370,r1
	jsr	@r1
	nop
	mov.l	.L1371,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1372,r1
	mov.l	.L1373,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1374,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1365:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1366:
	mov	r8,r9
	bra	.L1348
	add	#64,r9
.L1375:
	.align 2
.L1367:
	.long	text_int32
.L1368:
	.long	1073741823
.L1369:
	.long	.LC0
.L1370:
	.long	log_text
.L1371:
	.long	log_bytes
.L1372:
	.long	log_text_raw
.L1373:
	.long	.LC1
.L1374:
	.long	.LC2
	.size	prim_number_to, .-prim_number_to
	.align 1
	.align 2
	.global	prim_hex_to
	.type	prim_hex_to, @function
prim_hex_to:
	mov.l	r8,@-r15
	mov	#1,r1
	mov.l	r9,@-r15
	mov	r4,r8
	sts.l	pr,@-r15
	mov.l	@r4,r0
	cmp/gt	r1,r0
	bf/s	.L1400
	add	#-16,r15
	mov.l	@(4,r4),r3
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r2
	add	r0,r3
	add	#-4,r3
	mov	r15,r9
	mov.l	@r3,r4
	add	#4,r9
	mov.l	.L1402,r3
	mov	r9,r5
	jsr	@r3
	mov.l	r2,@r15
	mov.l	@r15,r2
	mov	#0,r6
	mov	r9,r3
.L1381:
	mov.l	@r3+,r7
	cmp/str	r6,r7
	bf	.L1381
	add	#-4,r3
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1379
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1379
	mov.b	@r3+,r7
	tst	r7,r7
	mov	#-1,r7
	subc	r7,r3
.L1379:
	sett
	mov	r3,r7
	subc	r9,r7
	tst	r7,r7
	bt/s	.L1401
	mov	r9,r5
	mov	r8,r9
	add	#64,r9
	mov	r7,r1
	.align 2
.L1384:
	mov.l	@(0,r9),r0
	dt	r1
	mov.b	@r5+,r3
	and	r2,r0
	mov.l	@(52,r8),r2
	mov.b	r3,@(r0,r2)
	mov	r0,r2
	bf/s	.L1384
	add	#1,r2
.L1383:
	mov.l	@r8,r0
	mov.l	.L1403,r1
	mov.l	@(12,r9),r5
	add	r1,r0
	mov.l	@(4,r8),r1
	shll2	r0
	mov.l	.L1404,r4
	mov.l	r7,@(r0,r1)
	mov.l	.L1405,r1
	jsr	@r1
	nop
	mov.l	.L1406,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1407,r1
	mov.l	.L1408,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1409,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1400:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1401:
	mov	r8,r9
	bra	.L1383
	add	#64,r9
.L1410:
	.align 2
.L1402:
	.long	text_hex32
.L1403:
	.long	1073741823
.L1404:
	.long	.LC0
.L1405:
	.long	log_text
.L1406:
	.long	log_bytes
.L1407:
	.long	log_text_raw
.L1408:
	.long	.LC1
.L1409:
	.long	.LC2
	.size	prim_hex_to, .-prim_hex_to
	.align 1
	.align 2
	.global	prim_dot_r
	.type	prim_dot_r, @function
prim_dot_r:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L1440
	add	#-16,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r10
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r10
	mov.l	@(r0,r2),r11
	mov.l	r1,@r4
	mov.l	@(32,r10),r1
	tst	r1,r1
	bt/s	.L1414
	add	r0,r2
	mov.l	.L1441,r1
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
.L1417:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L1417
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1415
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1415
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L1415:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r11,r1
	bt/s	.L1422
	cmp/eq	r11,r1
	bt	.L1422
	sub	r1,r11
	mov.w	.L1442,r1
	cmp/hi	r1,r11
	bf	.L1423
	mov	r1,r11
.L1423:
	mov.l	.L1443,r12
	mov	#0,r8
	.align 2
.L1424:
	mov.l	@(32,r10),r1
	mov	r12,r4
	jsr	@r1
	add	#1,r8
	cmp/hi	r8,r11
	bt	.L1424
.L1422:
	mov.l	@(32,r10),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(52,r10),r1
	tst	r1,r1
	bt	.L1414
	jsr	@r1
	nop
.L1414:
	mov.l	.L1444,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L1445,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1446,r1
	mov	#32,r5
	mov.l	.L1447,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1448,r4
	jsr	@r10
	nop
	mov.l	.L1449,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1440:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1442:
	.short	1500
.L1450:
	.align 2
.L1441:
	.long	text_int32
.L1443:
	.long	.LC3
.L1444:
	.long	log_text
.L1445:
	.long	.LC0
.L1446:
	.long	log_bytes
.L1447:
	.long	log_text_raw
.L1448:
	.long	.LC1
.L1449:
	.long	.LC2
	.size	prim_dot_r, .-prim_dot_r
	.align 1
	.align 2
	.global	prim_u_dot_r
	.type	prim_u_dot_r, @function
prim_u_dot_r:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L1480
	add	#-16,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r10
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r10
	mov.l	@(r0,r2),r11
	mov.l	r1,@r4
	mov.l	@(32,r10),r1
	tst	r1,r1
	bt/s	.L1454
	add	r0,r2
	mov.l	.L1481,r1
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
.L1457:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L1457
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1455
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1455
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L1455:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r11,r1
	bt/s	.L1462
	cmp/eq	r11,r1
	bt	.L1462
	sub	r1,r11
	mov.w	.L1482,r1
	cmp/hi	r1,r11
	bf	.L1463
	mov	r1,r11
.L1463:
	mov.l	.L1483,r12
	mov	#0,r8
	.align 2
.L1464:
	mov.l	@(32,r10),r1
	mov	r12,r4
	jsr	@r1
	add	#1,r8
	cmp/hi	r8,r11
	bt	.L1464
.L1462:
	mov.l	@(32,r10),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(52,r10),r1
	tst	r1,r1
	bt	.L1454
	jsr	@r1
	nop
.L1454:
	mov.l	.L1484,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L1485,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1486,r1
	mov	#32,r5
	mov.l	.L1487,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1488,r4
	jsr	@r10
	nop
	mov.l	.L1489,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1480:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1482:
	.short	1500
.L1490:
	.align 2
.L1481:
	.long	text_uint32
.L1483:
	.long	.LC3
.L1484:
	.long	log_text
.L1485:
	.long	.LC0
.L1486:
	.long	log_bytes
.L1487:
	.long	log_text_raw
.L1488:
	.long	.LC1
.L1489:
	.long	.LC2
	.size	prim_u_dot_r, .-prim_u_dot_r
	.align 1
	.align 2
	.global	prim_x_dot_r
	.type	prim_x_dot_r, @function
prim_x_dot_r:
	mov.l	r8,@-r15
	mov	#1,r2
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	mov.l	r12,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L1520
	add	#-16,r15
	mov	r1,r0
	mov.l	@(4,r4),r2
	add	#-1,r0
	mov	r4,r10
	mov.l	r0,@r4
	add	#-2,r1
	shll2	r0
	add	#124,r10
	mov.l	@(r0,r2),r11
	mov.l	r1,@r4
	mov.l	@(32,r10),r1
	tst	r1,r1
	bt/s	.L1494
	add	r0,r2
	mov.l	.L1521,r1
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
.L1497:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L1497
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1495
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1495
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L1495:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r11,r1
	bt/s	.L1502
	cmp/eq	r11,r1
	bt	.L1502
	sub	r1,r11
	mov.w	.L1522,r1
	cmp/hi	r1,r11
	bf	.L1503
	mov	r1,r11
.L1503:
	mov.l	.L1523,r12
	mov	#0,r8
	.align 2
.L1504:
	mov.l	@(32,r10),r1
	mov	r12,r4
	jsr	@r1
	add	#1,r8
	cmp/hi	r8,r11
	bt	.L1504
.L1502:
	mov.l	@(32,r10),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(52,r10),r1
	tst	r1,r1
	bt	.L1494
	jsr	@r1
	nop
.L1494:
	mov.l	.L1524,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L1525,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1526,r1
	mov	#32,r5
	mov.l	.L1527,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1528,r4
	jsr	@r10
	nop
	mov.l	.L1529,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1520:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1522:
	.short	1500
.L1530:
	.align 2
.L1521:
	.long	text_hex32
.L1523:
	.long	.LC3
.L1524:
	.long	log_text
.L1525:
	.long	.LC0
.L1526:
	.long	log_bytes
.L1527:
	.long	log_text_raw
.L1528:
	.long	.LC1
.L1529:
	.long	.LC2
	.size	prim_x_dot_r, .-prim_x_dot_r
	.align 1
	.align 2
	.global	prim_depth
	.type	prim_depth, @function
prim_depth:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	sts.l	pr,@-r15
	mov.w	.L1537,r2
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L1532
	add	#-4,r15
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1532:
	mov.l	.L1538,r0
	shll2	r1
	mov.l	@(4,r4),r9
	jsr	@r0
	add	r1,r9
	mov.l	r0,@r9
	mov	r8,r9
	mov.l	@r8,r1
	add	#64,r9
	mov.l	@(12,r9),r5
	add	#1,r1
	mov.l	.L1539,r4
	mov.l	r1,@r8
	mov.l	.L1540,r1
	jsr	@r1
	nop
	mov.l	.L1541,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1542,r1
	mov.l	.L1543,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1544,r4
	jsr	@r1
	nop
	mov.l	@(12,r9),r1
	mov	r8,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r9)
	mov.l	@(4,r1),r1
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L1537:
	.short	255
.L1545:
	.align 2
.L1538:
	.long	forth_stack_count
.L1539:
	.long	.LC0
.L1540:
	.long	log_text
.L1541:
	.long	log_bytes
.L1542:
	.long	log_text_raw
.L1543:
	.long	.LC1
.L1544:
	.long	.LC2
	.size	prim_depth, .-prim_depth
	.section	.rodata.str1.4
	.align 2
.LC18:
	.string	"<"
	.align 2
.LC19:
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
	mov	r4,r10
	mov.l	r12,@-r15
	mov.l	r13,@-r15
	sts.l	pr,@-r15
	mov.l	@(32,r9),r1
	tst	r1,r1
	bt/s	.L1547
	add	#-12,r15
	mov.l	.L1558,r0
	mov.l	.L1559,r12
	jsr	@r0
	nop
	mov.l	@(32,r9),r1
	mov.l	.L1560,r4
	jsr	@r1
	mov	r0,r11
	mov	r15,r5
	jsr	@r12
	mov	r11,r4
	mov.l	@(32,r9),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(32,r9),r1
	mov.l	.L1561,r4
	jsr	@r1
	nop
	cmp/pl	r11
	bf	.L1548
	mov.l	.L1562,r13
	mov	#0,r8
	.align 2
.L1549:
	mov.l	@(4,r10),r1
	mov	r8,r0
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	jsr	@r12
	add	#1,r8
	mov.l	@(32,r9),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(32,r9),r1
	jsr	@r1
	mov	r13,r4
	cmp/eq	r8,r11
	bf	.L1549
.L1548:
	mov.l	@(52,r9),r1
	tst	r1,r1
	bt	.L1547
	jsr	@r1
	nop
.L1547:
	mov.l	.L1563,r1
	mov	r10,r8
	add	#64,r8
	mov.l	.L1564,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1565,r1
	mov	#32,r5
	mov.l	.L1566,r9
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1567,r4
	jsr	@r9
	nop
	mov.l	.L1568,r4
	jsr	@r9
	nop
	mov.l	@(12,r8),r1
	mov	r10,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	add	#12,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L1569:
	.align 2
.L1558:
	.long	forth_stack_count
.L1559:
	.long	text_int32
.L1560:
	.long	.LC18
.L1561:
	.long	.LC19
.L1562:
	.long	.LC3
.L1563:
	.long	log_text
.L1564:
	.long	.LC0
.L1565:
	.long	log_bytes
.L1566:
	.long	log_text_raw
.L1567:
	.long	.LC1
.L1568:
	.long	.LC2
	.size	prim_dot_s, .-prim_dot_s
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
	bf/s	.L1594
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
	bt/s	.L1595
	mov	r1,r12
.L1573:
	tst	r12,r12
	mov	r13,r14
	bt/s	.L1579
	add	#64,r14
	mov	r13,r14
	add	#64,r14
	mov.l	@(0,r14),r9
	add	#-8,r2
	mov.l	@r2,r8
	and	r9,r11
	mov.l	.L1598,r10
	mov	r11,r2
	add	r12,r2
	and	r8,r9
	cmp/hi	r1,r2
	mov	r9,r3
	bf/s	.L1575
	add	r12,r3
	.align 2
.L1596:
	cmp/hs	r3,r1
	mov	r1,r2
	mov	r12,r8
	bf/s	.L1580
	sub	r11,r2
.L1576:
	cmp/hi	r2,r8
	bf	.L1577
	mov	r2,r8
.L1577:
	mov.l	@(52,r13),r4
	mov	r8,r6
	sub	r8,r12
	mov	r4,r5
	add	r11,r4
	jsr	@r10
	add	r9,r5
	tst	r12,r12
	add	r8,r11
	bt/s	.L1579
	add	r9,r8
	mov.l	@(0,r14),r9
	mov.l	@(56,r13),r1
	and	r9,r11
	mov	r11,r2
	add	r12,r2
	and	r8,r9
	cmp/hi	r1,r2
	mov	r9,r3
	bt/s	.L1596
	add	r12,r3
.L1575:
	cmp/hs	r3,r1
	bt/s	.L1597
	mov	r12,r2
.L1580:
	mov	r1,r8
	bra	.L1576
	sub	r9,r8
	.align 1
.L1597:
	mov.l	@(52,r13),r4
	mov	r12,r6
	mov	r4,r5
	add	r11,r4
	jsr	@r10
	add	r9,r5
.L1579:
	mov.l	.L1599,r1
	mov.l	.L1600,r4
	jsr	@r1
	mov.l	@(12,r14),r5
	mov.l	.L1601,r1
	mov	#32,r5
	mov.l	.L1602,r8
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L1603,r4
	jsr	@r8
	nop
	mov.l	.L1604,r4
	jsr	@r8
	nop
	mov.l	@(12,r14),r1
	mov	r13,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r14)
	mov.l	@(4,r1),r1
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
.L1595:
	bra	.L1573
	mov	r3,r12
	.align 1
.L1594:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
	add	#80,r13
	mov	#0,r1
	mov.b	r1,@r13
	lds.l	@r15+,pr
	mov.l	@r15+,r14
	mov.l	@r15+,r13
	mov.l	@r15+,r12
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L1605:
	.align 2
.L1598:
	.long	memmove
.L1599:
	.long	log_text
.L1600:
	.long	.LC0
.L1601:
	.long	log_bytes
.L1602:
	.long	log_text_raw
.L1603:
	.long	.LC1
.L1604:
	.long	.LC2
	.size	prim_move, .-prim_move
	.section	.rodata.str1.4
	.align 2
.LC20:
	.string	": "
	.align 2
.LC21:
	.string	"  "
	.align 2
.LC22:
	.string	"   "
	.align 2
.LC23:
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
	mov.l	@(32,r9),r1
	tst	r1,r1
	bf/s	.L1661
	add	#-36,r15
	bra	.L1637
	mov	r4,r14
.L1661:
	mov.l	@r4,r0
	mov	r4,r14
	mov.l	.L1642,r2
	add	#64,r14
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r3
	tst	r3,r3
	bf/s	.L1660
	mov.l	r3,@(4,r15)
	bra	.L1662
	mov.l	@(52,r9),r1
.L1660:
	add	r0,r1
	mov	r4,r14
	add	#-4,r1
	mov.l	@(4,r15),r3
	add	#64,r14
	mov.l	@r1,r10
	mov.l	@(0,r14),r1
	mov	#0,r0
	add	#-1,r3
	mov.l	r0,@(8,r15)
	and	r1,r10
	mov.l	r3,@(12,r15)
	mov	r15,r1
	add	#24,r1
	mov	#0,r11
	mov.l	r1,@r15
.L1610:
	mov.l	@(32,r9),r1
	mov.l	.L1655,r4
	jsr	@r1
	mov	#0,r8
	mov.l	.L1646,r0
	mov	#6,r6
	mov	r10,r4
	mov	r15,r5
	jsr	@r0
	add	#16,r5
	mov.l	@(32,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#16,r4
	mov.l	@(32,r9),r1
	mov.l	.L1645,r4
	jsr	@r1
	nop
.L1623:
	mov.l	@(52,r13),r1
	mov	r10,r0
	mov	#2,r6
	mov	r15,r5
	mov.b	@(r0,r1),r12
	add	#16,r5
	mov.l	.L1646,r1
	jsr	@r1
	extu.b	r12,r4
	mov.l	@(32,r9),r1
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
	bt/s	.L1638
	mov.l	@(12,r15),r0
	cmp/eq	r11,r0
	bt	.L1639
	mov.l	@(32,r9),r1
	mov.l	.L1647,r4
	jsr	@r1
	add	#1,r11
	mov.l	@(4,r15),r0
	cmp/eq	r11,r0
	bt/s	.L1609
	add	#1,r10
	mov.l	@(0,r14),r1
	bra	.L1623
	and	r1,r10
	.align 1
.L1638:
	mov.l	@r15,r1
	mov	#0,r0
	mov.b	r0,@(8,r1)
.L1612:
	tst	r8,r8
	mov	r15,r2
	mov	#31,r7
	mov	r8,r1
	add	#24,r2
	bt/s	.L1640
	mov	#46,r0
.L1616:
	mov.b	@r2+,r3
	cmp/gt	r7,r3
	bt/s	.L1615
	mov	r2,r3
	add	#-16,r3
	mov.b	r0,@(15,r3)
.L1615:
	dt	r1
	bf	.L1616
	mov	r8,r0
	cmp/eq	#8,r0
	bt	.L1621
	neg	r8,r8
	add	#8,r8
	mov	#0,r12
	.align 2
.L1614:
	mov.l	@(32,r9),r1
	mov.l	.L1648,r4
	jsr	@r1
	add	#1,r12
	cmp/hs	r8,r12
	bf	.L1614
.L1621:
	mov.l	@(32,r9),r1
	mov.l	.L1649,r4
	jsr	@r1
	nop
	mov.l	@(32,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#24,r4
	mov.l	@(8,r15),r0
	add	#1,r0
	cmp/eq	#20,r0
	bt/s	.L1618
	mov.l	r0,@(8,r15)
	mov.l	@(4,r15),r0
	add	#1,r11
	cmp/eq	r11,r0
	bt/s	.L1609
	add	#1,r10
	mov.l	@(0,r14),r1
	bra	.L1610
	and	r1,r10
	.align 1
.L1640:
	bra	.L1616
	mov	#1,r1
	.align 1
.L1639:
	mov	#24,r2
	mov	r8,r0
	mov	#0,r1
	add	r15,r2
	bra	.L1612
	mov.b	r1,@(r0,r2)
	.align 1
.L1618:
	mov.l	@(4,r15),r1
	add	#-1,r1
	cmp/eq	r11,r1
	bf	.L1641
.L1609:
	mov.l	@(52,r9),r1
.L1662:
	tst	r1,r1
	bt	.L1607
	jsr	@r1
	nop
.L1607:
	mov.l	@r13,r1
	mov.l	@(12,r14),r5
	add	#-2,r1
	mov.l	.L1650,r4
	mov.l	r1,@r13
	mov.l	.L1651,r1
	mov.l	.L1652,r8
	jsr	@r1
	nop
	mov.l	.L1653,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L1654,r4
	jsr	@r8
	nop
	mov.l	.L1655,r4
	jsr	@r8
	nop
	mov.l	@(12,r14),r1
	mov	r13,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r14)
	mov.l	@(4,r1),r1
	add	#36,r15
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
.L1637:
	bra	.L1607
	add	#64,r14
	.align 1
.L1641:
	mov.l	@(32,r9),r1
	mov.l	.L1656,r4
	jsr	@r1
	nop
	bra	.L1662
	mov.l	@(52,r9),r1
.L1657:
	.align 2
.L1642:
	.long	1073741823
.L1655:
	.long	.LC2
.L1646:
	.long	text_hex32_padded
.L1645:
	.long	.LC20
.L1647:
	.long	.LC3
.L1648:
	.long	.LC22
.L1649:
	.long	.LC21
.L1650:
	.long	.LC0
.L1651:
	.long	log_text
.L1652:
	.long	log_text_raw
.L1653:
	.long	log_bytes
.L1654:
	.long	.LC1
.L1656:
	.long	.LC23
	.size	prim_dump, .-prim_dump
	.align 1
	.align 2
	.global	prim_hidden_if
	.type	prim_hidden_if, @function
prim_hidden_if:
	mov.l	r8,@-r15
	mov	r4,r1
	sts.l	pr,@-r15
	mov.l	@r4,r0
	tst	r0,r0
	bt/s	.L1670
	add	#-8,r15
	add	#-1,r0
	mov.l	@(4,r4),r3
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r3),r3
	mov	r4,r8
	add	#64,r8
	mov.l	@(12,r8),r2
	tst	r3,r3
	mov	r2,r5
	bf/s	.L1667
	add	#4,r5
	mov.l	@(4,r2),r5
	add	r2,r5
.L1667:
	mov.l	.L1671,r2
	mov.l	r5,@(12,r8)
	mov.l	.L1672,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L1673,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L1674,r2
	mov.l	.L1675,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L1676,r4
	jsr	@r2
	nop
	mov.l	@(12,r8),r2
	mov.l	@r15,r4
	mov	r2,r3
	add	#4,r3
	mov.l	r3,@(12,r8)
	mov.l	@(4,r2),r2
	add	#8,r15
	lds.l	@r15+,pr
	jmp	@r2
	mov.l	@r15+,r8
	.align 1
.L1670:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(12,r2)
	add	#80,r1
	mov.b	r0,@(0,r1)
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L1677:
	.align 2
.L1671:
	.long	log_text
.L1672:
	.long	.LC0
.L1673:
	.long	log_bytes
.L1674:
	.long	log_text_raw
.L1675:
	.long	.LC1
.L1676:
	.long	.LC2
	.size	prim_hidden_if, .-prim_hidden_if
	.section	.rodata.str1.4
	.align 2
.LC24:
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
	mov.w	.L1690,r1
	mov.l	@r4,r2
	cmp/gt	r1,r2
	bf/s	.L1679
	add	#-4,r15
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(12,r1)
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
.L1679:
	mov.l	.L1691,r1
	mov	r4,r8
	add	#64,r8
	mov.l	@(60,r4),r2
	mov.l	@(12,r8),r10
	mov	#17,r4
	mov.l	r2,@r15
	mov.l	@(4,r10),r13
	mov	r10,r11
	mov.l	.L1692,r5
	jsr	@r1
	add	#8,r11
	mov.l	.L1693,r9
	mov.l	.L1694,r4
	jsr	@r9
	mov.l	@(12,r8),r5
	mov.l	@(12,r8),r5
	mov.l	.L1695,r4
	jsr	@r9
	add	#4,r5
	mov.l	.L1696,r4
	jsr	@r9
	mov	r13,r5
	mov.l	.L1699,r4
	jsr	@r9
	mov	r11,r5
	tst	r13,r13
	bt	.L1681
	mov	r13,r1
	add	#8,r1
	add	r1,r10
	mov	r11,r12
	.align 2
.L1682:
	mov.b	@r12,r5
	mov.l	.L1698,r4
	jsr	@r9
	mov	r5,r6
	mov.b	@r12+,r3
	mov.l	@(52,r14),r1
	mov.l	@(60,r14),r0
	cmp/eq	r10,r12
	mov.b	r3,@(r0,r1)
	mov.l	@(60,r14),r1
	mov.l	@(0,r8),r3
	add	#1,r1
	and	r3,r1
	bf/s	.L1682
	mov.l	r1,@(60,r14)
	add	r13,r11
.L1681:
	mov.l	.L1699,r4
	jsr	@r9
	mov	r11,r5
	neg	r13,r0
	mov.l	.L1700,r4
	and	#3,r0
	add	r0,r11
	mov	r11,r1
	add	#-4,r1
	mov.l	r1,@(12,r8)
	jsr	@r9
	mov	#4,r5
	mov.l	.L1701,r4
	jsr	@r9
	mov	r11,r5
	mov.l	.L1702,r4
	jsr	@r9
	mov.l	@(12,r8),r5
	mov.l	@r14,r0
	mov.l	@r15,r3
	mov.l	@(4,r14),r1
	shll2	r0
	mov.l	r3,@(r0,r1)
	mov.l	@r14,r0
	add	#1,r0
	mov.l	r0,@r14
	shll2	r0
	mov.l	r13,@(r0,r1)
	mov.l	@r14,r1
	add	#1,r1
	mov.l	r1,@r14
	mov.l	.L1703,r1
	jsr	@r1
	nop
	mov.l	.L1704,r4
	jsr	@r9
	mov.l	@(12,r8),r5
	mov.l	.L1705,r1
	mov	#32,r5
	mov.l	.L1706,r9
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1707,r4
	jsr	@r9
	nop
	mov.l	.L1708,r4
	jsr	@r9
	nop
	mov.l	@(12,r8),r1
	mov	r14,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
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
.L1690:
	.short	254
.L1709:
	.align 2
.L1691:
	.long	log_push
.L1692:
	.long	.LC24
.L1693:
	.long	log_text
.L1694:
	.long	.LC5
.L1695:
	.long	.LC6
.L1696:
	.long	.LC7
.L1699:
	.long	.LC8
.L1698:
	.long	.LC9
.L1700:
	.long	.LC12
.L1701:
	.long	.LC13
.L1702:
	.long	.LC14
.L1703:
	.long	log_pop
.L1704:
	.long	.LC0
.L1705:
	.long	log_bytes
.L1706:
	.long	log_text_raw
.L1707:
	.long	.LC1
.L1708:
	.long	.LC2
	.size	prim_hidden_s_quote, .-prim_hidden_s_quote
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
.LC25:
	.string	"!"
	.align 2
.LC26:
	.string	"C!"
	.align 2
.LC27:
	.string	"W!"
	.align 2
.LC28:
	.string	"'"
	.align 2
.LC29:
	.string	"("
	.align 2
.LC30:
	.string	"*"
	.align 2
.LC31:
	.string	"*/"
	.align 2
.LC32:
	.string	"*/MOD"
	.align 2
.LC33:
	.string	"+"
	.align 2
.LC34:
	.string	"+LOOP"
	.align 2
.LC35:
	.string	","
	.align 2
.LC36:
	.string	"C,"
	.align 2
.LC37:
	.string	"W,"
	.align 2
.LC38:
	.string	"-"
	.align 2
.LC39:
	.string	"\\"
	.align 2
.LC40:
	.string	"."
	.align 2
.LC41:
	.string	"U."
	.align 2
.LC42:
	.string	"X."
	.align 2
.LC43:
	.string	".\""
	.align 2
.LC44:
	.string	"/"
	.align 2
.LC45:
	.string	"/MOD"
	.align 2
.LC46:
	.string	":"
	.align 2
.LC47:
	.string	";"
	.align 2
.LC48:
	.string	"="
	.align 2
.LC49:
	.string	">"
	.align 2
.LC50:
	.string	">NUMBER"
	.align 2
.LC51:
	.string	">NUM"
	.align 2
.LC52:
	.string	"NUMBER>"
	.align 2
.LC53:
	.string	"NUM>"
	.align 2
.LC54:
	.string	">HEX"
	.align 2
.LC55:
	.string	"HEX>"
	.align 2
.LC56:
	.string	"?DUP"
	.align 2
.LC57:
	.string	"@"
	.align 2
.LC58:
	.string	"C@"
	.align 2
.LC59:
	.string	"W@"
	.align 2
.LC60:
	.string	"QUIT"
	.align 2
.LC61:
	.string	"ABS"
	.align 2
.LC62:
	.string	"ACCEPT"
	.align 2
.LC63:
	.string	"ALIGN"
	.align 2
.LC64:
	.string	"ALIGNED"
	.align 2
.LC65:
	.string	"ALLOT"
	.align 2
.LC66:
	.string	"AND"
	.align 2
.LC67:
	.string	"BEGIN"
	.align 2
.LC68:
	.string	"BL"
	.align 2
.LC69:
	.string	"BOUNDS"
	.align 2
.LC70:
	.string	"CELLS"
	.align 2
.LC71:
	.string	"CHAR"
	.align 2
.LC72:
	.string	"CONSTANT"
	.align 2
.LC73:
	.string	"CONST"
	.align 2
.LC74:
	.string	"CR"
	.align 2
.LC75:
	.string	"CREATE"
	.align 2
.LC76:
	.string	"DEPTH"
	.align 2
.LC77:
	.string	"DO"
	.align 2
.LC78:
	.string	"DROP"
	.align 2
.LC79:
	.string	"2DROP"
	.align 2
.LC80:
	.string	"DUP"
	.align 2
.LC81:
	.string	"2DUP"
	.align 2
.LC82:
	.string	"ELSE"
	.align 2
.LC83:
	.string	"EMIT"
	.align 2
.LC84:
	.string	"ERASE"
	.align 2
.LC85:
	.string	"EXECUTE"
	.align 2
.LC86:
	.string	"EXEC"
	.align 2
.LC87:
	.string	"EXIT"
	.align 2
.LC88:
	.string	"FILL"
	.align 2
.LC89:
	.string	"HERE"
	.align 2
.LC90:
	.string	"I"
	.align 2
.LC91:
	.string	"IF"
	.align 2
.LC92:
	.string	"INVERT"
	.align 2
.LC93:
	.string	"J"
	.align 2
.LC94:
	.string	"KEY"
	.align 2
.LC95:
	.string	"LEAVE"
	.align 2
.LC96:
	.string	"LITERAL"
	.align 2
.LC97:
	.string	"LIT"
	.align 2
.LC98:
	.string	"LOOP"
	.align 2
.LC99:
	.string	"LSHIFT"
	.align 2
.LC100:
	.string	"MAX"
	.align 2
.LC101:
	.string	"MIN"
	.align 2
.LC102:
	.string	"MOD"
	.align 2
.LC103:
	.string	"MOVE"
	.align 2
.LC104:
	.string	"NEGATE"
	.align 2
.LC105:
	.string	"OR"
	.align 2
.LC106:
	.string	"OVER"
	.align 2
.LC107:
	.string	"2OVER"
	.align 2
.LC108:
	.string	"PAGE"
	.align 2
.LC109:
	.string	"REPEAT"
	.align 2
.LC110:
	.string	"ROT"
	.align 2
.LC111:
	.string	"-ROT"
	.align 2
.LC112:
	.string	"RSHIFT"
	.align 2
.LC113:
	.string	"S\""
	.align 2
.LC114:
	.string	"SPACE"
	.align 2
.LC115:
	.string	"SPACES"
	.align 2
.LC116:
	.string	"SWAP"
	.align 2
.LC117:
	.string	"2SWAP"
	.align 2
.LC118:
	.string	"THEN"
	.align 2
.LC119:
	.string	"TYPE"
	.align 2
.LC120:
	.string	"U<"
	.align 2
.LC121:
	.string	"U>"
	.align 2
.LC122:
	.string	"UNTIL"
	.align 2
.LC123:
	.string	"VARIABLE"
	.align 2
.LC124:
	.string	"VAR"
	.align 2
.LC125:
	.string	"WHILE"
	.align 2
.LC126:
	.string	"XOR"
	.align 2
.LC127:
	.string	"["
	.align 2
.LC128:
	.string	"]"
	.align 2
.LC129:
	.string	"[']"
	.align 2
.LC130:
	.string	"[CHAR]"
	.align 2
.LC131:
	.string	".R"
	.align 2
.LC132:
	.string	"U.R"
	.align 2
.LC133:
	.string	"X.R"
	.align 2
.LC134:
	.string	"<>"
	.align 2
.LC135:
	.string	"AGAIN"
	.align 2
.LC136:
	.string	"FALSE"
	.align 2
.LC137:
	.string	"NIP"
	.align 2
.LC138:
	.string	"S\\\""
	.align 2
.LC139:
	.string	"TRUE"
	.align 2
.LC140:
	.string	"TUCK"
	.align 2
.LC141:
	.string	"UNUSED"
	.align 2
.LC142:
	.string	"WITHIN"
	.align 2
.LC143:
	.string	".S"
	.align 2
.LC144:
	.string	"?"
	.align 2
.LC145:
	.string	"DUMP"
	.align 2
.LC146:
	.string	"WORDS"
	.align 2
.LC147:
	.string	"WORDSIZE"
	.align 2
.LC148:
	.string	"BYE"
	.align 2
.LC149:
	.string	"{"
	.align 2
.LC150:
	.string	"0{"
	.align 2
.LC151:
	.string	"TO"
	.align 2
.LC152:
	.string	"RESET"
	.align 2
.LC153:
	.string	"WALIGN"
	.align 2
.LC154:
	.string	"WALIGNED"
	.align 2
.LC155:
	.string	"PRINTABLE"
	.align 2
.LC156:
	.string	"CXT"
	.align 2
.LC157:
	.string	"WXT"
	.align 2
.LC158:
	.string	"PRIMITIVES"
	.align 2
.LC159:
	.string	"SECONDARIES"
	.align 2
.LC160:
	.string	"UNDEFINED"
	.align 2
.LC161:
	.string	"PERF"
	.align 2
.LC162:
	.string	"SIZE"
	.align 2
.LC163:
	.string	"RESIZE"
	.align 2
.LC164:
	.string	""
	.section	.rodata
	.align 2
	.type	forth_primitives, @object
	.size	forth_primitives, 4832
forth_primitives:
	.long	.LC25
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC26
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC27
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC28
	.byte	1
	.zero	3
	.long	39
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC29
	.byte	1
	.zero	3
	.long	28
	.long	28
	.long	0
	.byte	1
	.zero	11
	.long	.LC30
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_star
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC31
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_star_slash
	.byte	0
	.zero	3
	.long	3
	.long	1
	.long	.LC32
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_star_slash_mod
	.byte	0
	.zero	3
	.long	3
	.long	2
	.long	.LC33
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_plus
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC34
	.byte	5
	.zero	3
	.long	1
	.long	29
	.long	0
	.byte	1
	.zero	11
	.long	.LC35
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC36
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC37
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC38
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_minus
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC39
	.byte	1
	.zero	3
	.long	10
	.long	10
	.long	0
	.byte	1
	.zero	11
	.long	.LC40
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_dot
	.byte	1
	.zero	11
	.long	.LC41
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_dot
	.byte	1
	.zero	11
	.long	.LC42
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_x_dot
	.byte	1
	.zero	11
	.long	.LC43
	.byte	2
	.zero	3
	.long	14
	.long	14
	.long	0
	.byte	1
	.zero	11
	.long	.LC44
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_slash
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC45
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_slash_mod
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC46
	.byte	1
	.zero	3
	.long	9
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC47
	.byte	1
	.zero	3
	.long	1
	.long	37
	.long	0
	.byte	1
	.zero	11
	.long	.LC18
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_less_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC48
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_equals
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC49
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_greater_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC50
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_to_number
	.byte	1
	.zero	11
	.long	.LC51
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_to_number
	.byte	1
	.zero	11
	.long	.LC52
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_number_to
	.byte	1
	.zero	11
	.long	.LC53
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_number_to
	.byte	1
	.zero	11
	.long	.LC54
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_to_hex
	.byte	1
	.zero	11
	.long	.LC55
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_hex_to
	.byte	1
	.zero	11
	.long	.LC56
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_question_dupe
	.byte	1
	.zero	11
	.long	.LC57
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC58
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC59
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC60
	.byte	4
	.zero	3
	.long	1
	.long	0
	.long	prim_quit
	.byte	1
	.zero	11
	.long	.LC61
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_abs
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC62
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_accept
	.byte	1
	.zero	11
	.long	.LC63
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_align
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	.LC64
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_aligned
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC65
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_allot
	.byte	1
	.zero	11
	.long	.LC66
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_and
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC67
	.byte	5
	.zero	3
	.long	1
	.long	4
	.long	0
	.byte	1
	.zero	11
	.long	.LC68
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_b_l
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC69
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_bounds
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC70
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_cells
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC71
	.byte	4
	.zero	3
	.long	8
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC72
	.byte	8
	.zero	3
	.long	11
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC73
	.byte	5
	.zero	3
	.long	11
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC74
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_r
	.byte	1
	.zero	11
	.long	.LC75
	.byte	6
	.zero	3
	.long	12
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC76
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_depth
	.byte	1
	.zero	11
	.long	.LC77
	.byte	2
	.zero	3
	.long	1
	.long	13
	.long	0
	.byte	1
	.zero	11
	.long	.LC78
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_drop
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC79
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_drop
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC80
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_dupe
	.byte	0
	.zero	3
	.long	1
	.long	2
	.long	.LC81
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_two_dupe
	.byte	0
	.zero	3
	.long	2
	.long	4
	.long	.LC82
	.byte	4
	.zero	3
	.long	1
	.long	15
	.long	0
	.byte	1
	.zero	11
	.long	.LC83
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_emit
	.byte	1
	.zero	11
	.long	.LC84
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_erase
	.byte	1
	.zero	11
	.long	.LC85
	.byte	7
	.zero	3
	.long	19
	.long	0
	.long	prim_execute
	.byte	1
	.zero	11
	.long	.LC86
	.byte	4
	.zero	3
	.long	19
	.long	0
	.long	prim_execute
	.byte	1
	.zero	11
	.long	.LC87
	.byte	4
	.zero	3
	.long	1
	.long	0
	.long	prim_hidden_done
	.byte	1
	.zero	11
	.long	.LC88
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_fill
	.byte	1
	.zero	11
	.long	.LC89
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_here
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC90
	.byte	1
	.zero	3
	.long	1
	.long	0
	.long	prim_i
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC91
	.byte	2
	.zero	3
	.long	1
	.long	20
	.long	0
	.byte	1
	.zero	11
	.long	.LC92
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_invert
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC93
	.byte	1
	.zero	3
	.long	1
	.long	0
	.long	prim_j
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC94
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_key
	.byte	1
	.zero	11
	.long	.LC95
	.byte	5
	.zero	3
	.long	1
	.long	21
	.long	0
	.byte	1
	.zero	11
	.long	.LC96
	.byte	7
	.zero	3
	.long	1
	.long	23
	.long	0
	.byte	1
	.zero	11
	.long	.LC97
	.byte	3
	.zero	3
	.long	1
	.long	23
	.long	0
	.byte	1
	.zero	11
	.long	.LC98
	.byte	4
	.zero	3
	.long	1
	.long	26
	.long	0
	.byte	1
	.zero	11
	.long	.LC99
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_l_shift
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC100
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_max
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC101
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_min
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC102
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_mod
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC103
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_move
	.byte	1
	.zero	11
	.long	.LC104
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_negate
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC105
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_or
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC106
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_over
	.byte	0
	.zero	3
	.long	2
	.long	3
	.long	.LC107
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_over
	.byte	0
	.zero	3
	.long	4
	.long	6
	.long	.LC108
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_page
	.byte	1
	.zero	11
	.long	.LC109
	.byte	6
	.zero	3
	.long	1
	.long	31
	.long	0
	.byte	1
	.zero	11
	.long	.LC110
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_rote
	.byte	0
	.zero	3
	.long	3
	.long	3
	.long	.LC111
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_minus_rote
	.byte	0
	.zero	3
	.long	3
	.long	3
	.long	.LC112
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_r_shift
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC113
	.byte	2
	.zero	3
	.long	34
	.long	34
	.long	0
	.byte	1
	.zero	11
	.long	.LC114
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_space
	.byte	1
	.zero	11
	.long	.LC115
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_spaces
	.byte	1
	.zero	11
	.long	.LC116
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_swap
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC117
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_swap
	.byte	0
	.zero	3
	.long	4
	.long	4
	.long	.LC118
	.byte	4
	.zero	3
	.long	1
	.long	38
	.long	0
	.byte	1
	.zero	11
	.long	.LC119
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_type
	.byte	1
	.zero	11
	.long	.LC120
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_less_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC121
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_greater_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC122
	.byte	5
	.zero	3
	.long	1
	.long	42
	.long	0
	.byte	1
	.zero	11
	.long	.LC123
	.byte	8
	.zero	3
	.long	43
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC124
	.byte	3
	.zero	3
	.long	43
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC125
	.byte	5
	.zero	3
	.long	1
	.long	44
	.long	0
	.byte	1
	.zero	11
	.long	.LC126
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_x_or
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC127
	.byte	1
	.zero	3
	.long	1
	.long	22
	.long	0
	.byte	1
	.zero	11
	.long	.LC128
	.byte	1
	.zero	3
	.long	33
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC129
	.byte	3
	.zero	3
	.long	1
	.long	6
	.long	0
	.byte	1
	.zero	11
	.long	.LC130
	.byte	6
	.zero	3
	.long	1
	.long	5
	.long	0
	.byte	1
	.zero	11
	.long	.LC131
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_dot_r
	.byte	1
	.zero	11
	.long	.LC132
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_u_dot_r
	.byte	1
	.zero	11
	.long	.LC133
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_x_dot_r
	.byte	1
	.zero	11
	.long	.LC134
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_not_equals
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC135
	.byte	5
	.zero	3
	.long	1
	.long	3
	.long	0
	.byte	1
	.zero	11
	.long	.LC136
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_false
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC137
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_nip
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC138
	.byte	3
	.zero	3
	.long	35
	.long	35
	.long	0
	.byte	1
	.zero	11
	.long	.LC139
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_true
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC140
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_tuck
	.byte	0
	.zero	3
	.long	2
	.long	3
	.long	.LC141
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_unused
	.byte	1
	.zero	11
	.long	.LC142
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_within
	.byte	0
	.zero	3
	.long	3
	.long	1
	.long	.LC143
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_dot_s
	.byte	1
	.zero	11
	.long	.LC144
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_question
	.byte	1
	.zero	11
	.long	.LC145
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_dump
	.byte	1
	.zero	11
	.long	.LC146
	.byte	5
	.zero	3
	.long	45
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC147
	.byte	8
	.zero	3
	.long	46
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC148
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_bye
	.byte	1
	.zero	11
	.long	.LC149
	.byte	1
	.zero	3
	.long	1
	.long	24
	.long	0
	.byte	1
	.zero	11
	.long	.LC150
	.byte	2
	.zero	3
	.long	1
	.long	25
	.long	0
	.byte	1
	.zero	11
	.long	.LC151
	.byte	2
	.zero	3
	.long	1
	.long	40
	.long	0
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC152
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_reset
	.byte	1
	.zero	11
	.long	.LC153
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_walign
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	.LC154
	.byte	8
	.zero	3
	.long	0
	.long	0
	.long	prim_waligned
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC155
	.byte	9
	.zero	3
	.long	0
	.long	0
	.long	prim_printable
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC156
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_cxt
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC157
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_wxt
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC158
	.byte	10
	.zero	3
	.long	30
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC159
	.byte	11
	.zero	3
	.long	36
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC160
	.byte	9
	.zero	3
	.long	41
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC161
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_perf
	.byte	1
	.zero	11
	.long	.LC162
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_size
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC163
	.byte	6
	.zero	3
	.long	32
	.long	2
	.long	0
	.zero	12
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_do
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_done
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_dot_quote
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_if
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_jump
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_leave
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_loop
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_plus_loop
	.byte	1
	.zero	11
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_push
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC164
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_s_quote
	.byte	1
	.zero	11
	.long	.LC164
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
