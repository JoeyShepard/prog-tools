	.file	"forth-primitives.c"
	.text
	.text
	.align 1
	.align 2
	.global	f1
	.type	f1, @function
f1:
	rts	
	mov	#12,r0
	.size	f1, .-f1
	.align 1
	.align 2
	.global	f3
	.type	f3, @function
f3:
	rts	
	mov	#56,r0
	.size	f3, .-f3
	.align 1
	.align 2
	.global	f_exec
	.type	f_exec, @function
f_exec:
	mov.l	.L5,r1
	mov.l	@r1,r0
	add	#4,r0
	jmp	@r0
	mov.l	r0,@r1
.L6:
	.align 2
.L5:
	.long	f
	.size	f_exec, .-f_exec
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
	bf/s	.L15
	mov	r4,r1
	mov.l	.L17,r0
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
	bf/s	.L16
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
.L12:
	mov.l	.L18,r2
	mov.l	@(12,r8),r5
	mov.l	.L19,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L20,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L21,r2
	mov.l	.L22,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L23,r4
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
.L16:
	mov	#7,r3
	mov	r4,r2
	add	#124,r2
	mov	r4,r8
	mov.l	r3,@(24,r2)
	mov	#0,r3
	mov	r4,r2
	add	#80,r2
	mov.b	r3,@r2
	bra	.L12
	add	#64,r8
	.align 1
.L15:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L24:
	.align 2
.L17:
	.long	1073741823
.L18:
	.long	log_text
.L19:
	.long	.LC0
.L20:
	.long	log_bytes
.L21:
	.long	log_text_raw
.L22:
	.long	.LC1
.L23:
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
	bra	.L27
	add	#-8,r15
	.align 1
.L26:
	tst	r0,r0
	bt	.L29
.L27:
	mov	r1,r7
	add	#16,r1
	mov.l	r1,@(24,r3)
	mov.b	@(14,r1),r0
	mov	r0,r2
	extu.b	r0,r0
	cmp/eq	#1,r0
	bf/s	.L26
	mov	r3,r8
	add	#64,r8
	mov.l	@(16,r7),r1
	mov.l	@(28,r8),r5
	mov.w	@(28,r7),r0
	add	r1,r5
	mov.l	.L30,r4
	mov.l	r5,@(12,r8)
	extu.w	r0,r7
	mov.l	@(36,r3),r1
	shll2	r7
	mov.l	r3,@r15
	add	r7,r1
	mov.l	r1,@(36,r3)
	mov.l	.L31,r1
	jsr	@r1
	nop
	mov.l	.L32,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L33,r1
	mov.l	.L34,r4
	jsr	@r1
	mov.l	r1,@(4,r15)
	mov.l	@(4,r15),r1
	mov.l	.L35,r4
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
.L29:
	add	#80,r3
	mov.b	r2,@r3
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L36:
	.align 2
.L30:
	.long	.LC0
.L31:
	.long	log_text
.L32:
	.long	log_bytes
.L33:
	.long	log_text_raw
.L34:
	.long	.LC1
.L35:
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
	mov.l	.L39,r4
	mov.l	@(4,r5),r1
	mov.l	.L40,r10
	add	r1,r5
	mov.l	.L41,r1
	jsr	@r1
	mov.l	r5,@(12,r8)
	mov.l	.L42,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L43,r4
	jsr	@r10
	nop
	mov.l	.L44,r4
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
.L45:
	.align 2
.L39:
	.long	.LC0
.L40:
	.long	log_text_raw
.L41:
	.long	log_text
.L42:
	.long	log_bytes
.L43:
	.long	.LC1
.L44:
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
	mov.l	.L48,r10
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
	mov.l	.L49,r4
	add	r1,r5
	mov.l	.L50,r1
	jsr	@r1
	mov.l	r5,@(12,r9)
	mov.l	.L51,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L52,r4
	jsr	@r10
	nop
	mov.l	.L53,r4
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
.L54:
	.align 2
.L48:
	.long	log_text_raw
.L49:
	.long	.LC0
.L50:
	.long	log_text
.L51:
	.long	log_bytes
.L52:
	.long	.LC1
.L53:
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
	bt/s	.L56
	mov.l	r1,@(8,r4)
	mov.l	@(4,r5),r1
	add	r1,r5
	mov.l	r5,@(12,r9)
.L57:
	mov.l	.L59,r1
	mov.l	.L60,r4
	mov.l	.L61,r10
	jsr	@r1
	nop
	mov.l	.L62,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L63,r4
	jsr	@r10
	nop
	mov.l	.L64,r4
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
.L56:
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
	bra	.L57
	mov.l	r1,@(48,r4)
.L65:
	.align 2
.L59:
	.long	log_text
.L60:
	.long	.LC0
.L61:
	.long	log_text_raw
.L62:
	.long	log_bytes
.L63:
	.long	.LC1
.L64:
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
	bt/s	.L73
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
	bf/s	.L74
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
.L70:
	mov.l	.L75,r2
	mov.l	.L76,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L77,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L78,r2
	mov.l	.L79,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L80,r4
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
.L74:
	mov.l	@(4,r5),r2
	add	r2,r5
	bra	.L70
	mov.l	r5,@(12,r8)
	.align 1
.L73:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov.b	r0,@(0,r1)
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L81:
	.align 2
.L75:
	.long	log_text
.L76:
	.long	.LC0
.L77:
	.long	log_bytes
.L78:
	.long	log_text_raw
.L79:
	.long	.LC1
.L80:
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
	mov.l	.L84,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L85,r1
	mov.l	.L86,r4
	jsr	@r1
	nop
	mov.l	.L87,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L88,r4
	jsr	@r10
	nop
	mov.l	.L89,r4
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
.L90:
	.align 2
.L84:
	.long	log_text_raw
.L85:
	.long	log_text
.L86:
	.long	.LC0
.L87:
	.long	log_bytes
.L88:
	.long	.LC1
.L89:
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
	bt/s	.L103
	mov	r4,r9
	add	#-1,r0
	extu.b	r0,r0
	mov	#2,r2
	cmp/hi	r2,r0
	bt	.L94
	mov.l	@r4,r0
	mov.w	.L106,r2
	cmp/gt	r2,r0
	bt/s	.L104
	shll2	r0
	mov.l	@r1,r1
	mov.l	@(4,r1),r2
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
.L93:
	mov.l	.L107,r1
	mov.l	.L108,r4
	mov.l	.L109,r10
	jsr	@r1
	nop
	mov.l	.L110,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L111,r4
	jsr	@r10
	nop
	mov.l	.L112,r4
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
.L94:
	mov.l	@(24,r4),r2
	mov.l	@(20,r4),r3
	cmp/hs	r3,r2
	bf/s	.L105
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
	bt/s	.L99
	mov.l	r3,@(36,r4)
	mov	#5,r7
	mov	r4,r3
	add	#124,r3
	mov.l	r7,@(24,r3)
	mov	#0,r7
	mov	r4,r3
	add	#80,r3
	mov.b	r7,@r3
.L99:
	add	#-16,r2
	mov.l	r2,@(24,r9)
	mov.l	@r1,r5
	add	#-4,r5
	bra	.L93
	mov.l	r5,@(12,r8)
	.align 1
.L103:
	mov.l	@(20,r1),r1
	mov	#9,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(40,r2)
	mov.l	r3,@(24,r2)
	mov	r4,r1
	mov	#0,r2
	add	#80,r1
	mov.b	r2,@r1
	bra	.L93
	nop
	.align 1
.L105:
	mov	#7,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	mov	#0,r2
	mov	r4,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L93
	nop
	.align 1
.L104:
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L106:
	.short	255
.L113:
	.align 2
.L107:
	.long	log_text
.L108:
	.long	.LC0
.L109:
	.long	log_text_raw
.L110:
	.long	log_bytes
.L111:
	.long	.LC1
.L112:
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
	mov.l	.L116,r4
	mov.l	r2,@(r0,r1)
	mov.l	.L117,r1
	mov.l	.L118,r10
	jsr	@r1
	nop
	mov.l	.L119,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L120,r4
	jsr	@r10
	nop
	mov.l	.L121,r4
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
.L122:
	.align 2
.L116:
	.long	.LC0
.L117:
	.long	log_text
.L118:
	.long	log_text_raw
.L119:
	.long	log_bytes
.L120:
	.long	.LC1
.L121:
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
	mov.l	.L125,r10
	mov.l	@(r0,r1),r3
	add	r0,r1
	mov.l	r2,@r4
	add	#-4,r1
	mov.l	@(0,r9),r2
	mov.l	@r1,r1
	and	r3,r2
	mov.l	@(52,r4),r3
	mov	r2,r0
	mov.l	.L126,r4
	mov.b	r1,@(r0,r3)
	mov.l	.L127,r1
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L128,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L129,r4
	jsr	@r10
	nop
	mov.l	.L130,r4
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
.L131:
	.align 2
.L125:
	.long	log_text_raw
.L126:
	.long	.LC0
.L127:
	.long	log_text
.L128:
	.long	log_bytes
.L129:
	.long	.LC1
.L130:
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
	mov.l	.L134,r4
	mov.w	r1,@(r0,r3)
	mov.l	.L135,r1
	mov.l	.L136,r10
	jsr	@r1
	nop
	mov.l	.L137,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L138,r4
	jsr	@r10
	nop
	mov.l	.L139,r4
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
.L140:
	.align 2
.L134:
	.long	.LC0
.L135:
	.long	log_text
.L136:
	.long	log_text_raw
.L137:
	.long	log_bytes
.L138:
	.long	.LC1
.L139:
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
	mov.l	.L143,r4
	mul.l	r2,r3
	mov.l	.L144,r10
	sts	macl,r2
	mov.l	r2,@r1
	mov.l	.L145,r1
	jsr	@r1
	nop
	mov.l	.L146,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L147,r4
	jsr	@r10
	nop
	mov.l	.L148,r4
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
.L149:
	.align 2
.L143:
	.long	.LC0
.L144:
	.long	log_text_raw
.L145:
	.long	log_text
.L146:
	.long	log_bytes
.L147:
	.long	.LC1
.L148:
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
	bf	.L151
	mov	#1,r7
.L151:
	dmuls.l	r2,r1
	mov.l	.L153,r0
	mov	r7,r6
	shll	r6
	mov.l	.L154,r10
	sts	macl,r5
	sts	mach,r4
	jsr	@r0
	subc	r6,r6
	mov.l	r1,@r9
	mov	r8,r9
	mov.l	.L155,r1
	add	#64,r9
	mov.l	.L156,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L157,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L158,r4
	jsr	@r10
	nop
	mov.l	.L159,r4
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
.L160:
	.align 2
.L153:
	.long	__divdi3
.L154:
	.long	log_text_raw
.L155:
	.long	log_text
.L156:
	.long	.LC0
.L157:
	.long	log_bytes
.L158:
	.long	.LC1
.L159:
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
	bt/s	.L162
	mov.l	r1,@(12,r15)
	mov.l	.L166,r0
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
	mov.l	.L167,r0
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
.L162:
	mov.l	r10,@r3
	mov.l	@r8,r0
	mov.l	.L168,r3
	mov.l	.L169,r1
	add	r3,r0
	mov.l	.L170,r4
	shll2	r0
	mov.l	.L171,r10
	mov.l	r2,@(r0,r9)
	mov	r8,r9
	add	#64,r9
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L172,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L173,r4
	jsr	@r10
	nop
	mov.l	.L174,r4
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
.L175:
	.align 2
.L166:
	.long	__moddi3
.L167:
	.long	__divdi3
.L168:
	.long	1073741822
.L169:
	.long	log_text
.L170:
	.long	.LC0
.L171:
	.long	log_text_raw
.L172:
	.long	log_bytes
.L173:
	.long	.LC1
.L174:
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
	mov.l	.L178,r4
	add	r3,r2
	mov.l	.L179,r10
	mov.l	r2,@r1
	mov.l	.L180,r1
	jsr	@r1
	nop
	mov.l	.L181,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L182,r4
	jsr	@r10
	nop
	mov.l	.L183,r4
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
.L184:
	.align 2
.L178:
	.long	.LC0
.L179:
	.long	log_text_raw
.L180:
	.long	log_text
.L181:
	.long	log_bytes
.L182:
	.long	.LC1
.L183:
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
	mov.l	.L187,r10
	and	r2,r1
	mov.l	r1,@(60,r4)
	mov.l	.L188,r1
	mov.l	.L189,r4
	jsr	@r1
	nop
	mov.l	.L190,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L191,r4
	jsr	@r10
	nop
	mov.l	.L192,r4
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
.L193:
	.align 2
.L187:
	.long	log_text_raw
.L188:
	.long	log_text
.L189:
	.long	.LC0
.L190:
	.long	log_bytes
.L191:
	.long	.LC1
.L192:
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
	mov.l	.L196,r10
	mov.b	r3,@(r0,r2)
	mov.l	@(60,r4),r1
	mov.l	@(0,r9),r2
	add	#1,r1
	mov.l	@(12,r9),r5
	and	r2,r1
	mov.l	r1,@(60,r4)
	mov.l	.L197,r1
	mov.l	.L198,r4
	jsr	@r1
	nop
	mov.l	.L199,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L200,r4
	jsr	@r10
	nop
	mov.l	.L201,r4
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
.L202:
	.align 2
.L196:
	.long	log_text_raw
.L197:
	.long	log_text
.L198:
	.long	.LC0
.L199:
	.long	log_bytes
.L200:
	.long	.LC1
.L201:
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
	mov.l	.L205,r1
	and	r2,r0
	mov.l	r0,@(60,r4)
	mov.l	.L206,r4
	jsr	@r1
	nop
	mov.l	.L207,r1
	mov	#32,r5
	mov.l	.L208,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L209,r4
	jsr	@r10
	nop
	mov.l	.L210,r4
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
.L211:
	.align 2
.L205:
	.long	log_text
.L206:
	.long	.LC0
.L207:
	.long	log_bytes
.L208:
	.long	log_text_raw
.L209:
	.long	.LC1
.L210:
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
	mov.l	.L214,r4
	sub	r3,r2
	mov.l	.L215,r10
	mov.l	r2,@r1
	mov.l	.L216,r1
	jsr	@r1
	nop
	mov.l	.L217,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L218,r4
	jsr	@r10
	nop
	mov.l	.L219,r4
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
.L220:
	.align 2
.L214:
	.long	.LC0
.L215:
	.long	log_text_raw
.L216:
	.long	log_text
.L217:
	.long	log_bytes
.L218:
	.long	.LC1
.L219:
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
	bt/s	.L222
	mov.l	@r2,r4
	mov.l	.L227,r0
	jsr	@r0
	nop
	mov	r0,r4
.L222:
	mov.l	.L228,r1
	mov	r8,r9
	add	#64,r9
	mov.l	r4,@r2
	mov.l	.L229,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L230,r1
	mov	#32,r5
	mov.l	.L231,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L232,r4
	jsr	@r10
	nop
	mov.l	.L233,r4
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
.L234:
	.align 2
.L227:
	.long	__sdivsi3_i4i
.L228:
	.long	log_text
.L229:
	.long	.LC0
.L230:
	.long	log_bytes
.L231:
	.long	log_text_raw
.L232:
	.long	.LC1
.L233:
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
	mov.l	.L241,r1
	mov.l	@r4,r2
	mov.l	@(4,r4),r6
	add	r1,r2
	shll2	r2
	add	r6,r2
	mov.l	@r2,r3
	mov	r2,r1
	add	#-4,r1
	tst	r3,r3
	bt/s	.L236
	mov.l	@r1,r7
	mov.l	.L242,r0
	mov	r7,r4
	jsr	@r0
	mov	r3,r5
	mul.l	r3,r0
	mov	r7,r3
	mov	r0,r7
	sts	macl,r1
	sub	r1,r3
.L236:
	mov.l	r7,@r2
	mov	r8,r9
	mov.l	@r8,r0
	add	#64,r9
	mov.l	.L243,r1
	mov.l	@(12,r9),r5
	add	r1,r0
	mov.l	.L244,r1
	shll2	r0
	mov.l	.L245,r4
	jsr	@r1
	mov.l	r3,@(r0,r6)
	mov.l	.L246,r1
	mov	#32,r5
	mov.l	.L247,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L248,r4
	jsr	@r10
	nop
	mov.l	.L249,r4
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
.L250:
	.align 2
.L241:
	.long	1073741823
.L242:
	.long	__sdivsi3_i4i
.L243:
	.long	1073741822
.L244:
	.long	log_text
.L245:
	.long	.LC0
.L246:
	.long	log_bytes
.L247:
	.long	log_text_raw
.L248:
	.long	.LC1
.L249:
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
	mov.l	.L253,r4
	cmp/gt	r2,r3
	mov.l	.L254,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L255,r1
	jsr	@r1
	nop
	mov.l	.L256,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L257,r4
	jsr	@r10
	nop
	mov.l	.L258,r4
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
.L259:
	.align 2
.L253:
	.long	.LC0
.L254:
	.long	log_text_raw
.L255:
	.long	log_text
.L256:
	.long	log_bytes
.L257:
	.long	.LC1
.L258:
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
	mov.l	.L262,r4
	cmp/eq	r2,r3
	mov.l	.L263,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L264,r1
	jsr	@r1
	nop
	mov.l	.L265,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L266,r4
	jsr	@r10
	nop
	mov.l	.L267,r4
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
.L268:
	.align 2
.L262:
	.long	.LC0
.L263:
	.long	log_text_raw
.L264:
	.long	log_text
.L265:
	.long	log_bytes
.L266:
	.long	.LC1
.L267:
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
	mov.l	.L271,r4
	cmp/gt	r2,r3
	mov.l	.L272,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L273,r1
	jsr	@r1
	nop
	mov.l	.L274,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L275,r4
	jsr	@r10
	nop
	mov.l	.L276,r4
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
.L277:
	.align 2
.L271:
	.long	.LC0
.L272:
	.long	log_text_raw
.L273:
	.long	log_text
.L274:
	.long	log_bytes
.L275:
	.long	.LC1
.L276:
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
	bt/s	.L333
	mov	r4,r10
	bra	.L302
	mov	#10,r2
.L333:
	mov.w	.L307,r1
	mov.l	@(4,r15),r13
	cmp/gt	r1,r13
	bf	.L332
	bra	.L303
	mov	#6,r2
.L332:
	mov.l	@(4,r15),r3
	mov.l	.L311,r0
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
	bf	.L282
	mov	r1,r6
.L282:
	tst	r6,r6
	bf	.L331
	bra	.L294
	mov	r10,r13
.L331:
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
.L293:
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
	bf/s	.L295
	add	#-48,r0
	extu.b	r0,r2
	mov	#9,r13
	cmp/hi	r13,r2
	bf	.L330
	bra	.L304
	mov.l	@r15,r10
.L330:
	mul.l	r1,r4
	tst	r8,r8
	sts	macl,r1
	dmulu.l	r4,r7
	sts	mach,r2
	sts	macl,r7
	bt/s	.L329
	add	r1,r2
	bra	.L286
	cmp/gt	r0,r10
.L329:
	cmp/gt	r0,r8
	subc	r1,r1
	clrt
	addc	r0,r7
	addc	r2,r1
.L287:
	mov.l	.L309,r0
	clrt
	mov	#0,r2
	addc	r7,r0
	addc	r1,r2
	cmp/hs	r14,r2
	bf/s	.L284
	cmp/hi	r14,r2
	bt	.L297
	bra	.L305
	nop
.L297:
	mov.l	@(16,r15),r1
.L334:
	mov.l	@r15,r10
	and	r11,r1
	mov.w	.L310,r3
	mov	r1,r0
	mov.b	@(r0,r9),r7
	add	r10,r3
	exts.b	r7,r0
	mov	r7,r2
	cmp/eq	#45,r0
	bf/s	.L292
	mov	#1,r7
.L289:
	mov.b	r0,@r3
	mov	#0,r0
	mov.b	r0,@(1,r3)
	mov	r7,r0
	cmp/eq	#11,r0
	bt	.L291
	add	#1,r1
.L335:
	and	r11,r1
	mov	r1,r0
	mov.b	@(r0,r9),r6
	add	#1,r3
	add	#1,r7
	mov	r6,r2
	mov	r6,r0
.L292:
	add	#-48,r2
	extu.b	r2,r2
	mov	#9,r6
	cmp/hi	r6,r2
	bf	.L289
	mov	r7,r0
	cmp/eq	#11,r0
	bf/s	.L335
	add	#1,r1
	add	#-1,r1
.L291:
	mov	#3,r2
	mov	r10,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L303:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L295:
	mov	r10,r8
.L284:
	dt	r6
	add	#1,r3
	bf/s	.L293
	add	#-1,r5
	mov.l	@r15,r10
	mov	#0,r5
	mov.l	r3,@(16,r15)
.L283:
	mov.l	@(20,r15),r1
	mov.l	.L311,r2
	mov.l	r5,@(4,r1)
	mov.l	@r10,r0
	mov.l	@(12,r15),r3
	mov.l	@(16,r15),r13
	add	r2,r0
	shll2	r0
	mov.l	.L312,r1
	mov.l	r13,@(r0,r3)
	mov.l	@r10,r0
	mov.l	@(8,r15),r2
	add	r1,r0
	mov.l	.L313,r4
	shll2	r0
	mov.l	@(12,r2),r5
	mov.l	r7,@(r0,r3)
	mov.l	@r10,r1
	mov.l	.L314,r8
	add	#1,r1
	mov.l	r1,@r10
	mov.l	.L315,r1
	jsr	@r1
	nop
	mov.l	.L316,r1
	mov	#32,r5
	mov.l	@(8,r15),r3
	jsr	@r1
	mov.l	@(12,r3),r4
	mov.l	.L317,r4
	jsr	@r8
	nop
	mov.l	.L318,r4
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
.L307:
	.short	255
.L310:
	.short	152
.L319:
	.align 2
.L311:
	.long	1073741823
.L309:
	.long	-2147483648
.L312:
	.long	1073741822
.L313:
	.long	.LC0
.L314:
	.long	log_text_raw
.L315:
	.long	log_text
.L316:
	.long	log_bytes
.L317:
	.long	.LC1
.L318:
	.long	.LC2
	.align 1
.L286:
	mov	r2,r1
	subc	r10,r10
	clrt
	subc	r0,r7
	bra	.L287
	subc	r10,r1
	.align 1
.L302:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L304:
	add	#1,r5
	bra	.L283
	mov.l	r3,@(16,r15)
	.align 1
.L294:
	add	#64,r13
	mov	#0,r7
	mov.l	r13,@(8,r15)
	bra	.L283
	mov	#0,r5
	.align 1
.L305:
	mov.l	.L320,r2
	cmp/hi	r2,r0
	bf	.L284
	bra	.L334
	mov.l	@(16,r15),r1
.L321:
	.align 2
.L320:
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
	bt/s	.L424
	mov	r4,r11
	bra	.L376
	mov	#10,r2
.L424:
	mov.w	.L386,r1
	mov.l	@(4,r15),r6
	cmp/gt	r1,r6
	bf	.L423
	bra	.L377
	mov	#6,r2
.L423:
	mov.l	@(4,r15),r3
	mov.l	.L387,r0
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
	bf	.L340
	mov	r1,r4
.L340:
	tst	r4,r4
	bf	.L422
	bra	.L362
	mov	r11,r6
.L422:
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
	bf/s	.L421
	mov.l	r1,@(20,r15)
	bra	.L378
	add	#-1,r4
.L421:
	mov	r4,r0
	cmp/eq	#1,r0
	bf/s	.L420
	mov.l	@(20,r15),r3
	bra	.L379
	mov	#0,r1
.L420:
	mov	#0,r6
	mov	r5,r2
	mov.l	r6,@r15
.L361:
	mov	r3,r0
	cmp/eq	#48,r0
	bf/s	.L344
	and	r10,r5
	bra	.L380
	add	#1,r2
.L344:
	mov	#0,r7
.L426:
	mov	r4,r9
	mov	#9,r8
	mov	r5,r0
	mov	#0,r14
	mov	#1,r12
	mov	#0,r1
	.align 2
.L360:
	mov	r3,r6
	add	#-48,r6
	extu.b	r6,r2
	cmp/hi	r8,r2
	bf	.L347
	mov	r3,r2
	add	#-97,r2
	extu.b	r2,r2
	mov	#5,r6
	cmp/hi	r6,r2
	bf	.L418
	bra	.L348
	mov	r3,r2
.L418:
	mov	r3,r6
	add	#-87,r6
.L347:
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
	bt/s	.L417
	shll2	r3
	bra	.L350
	mov	r3,r7
.L417:
	clrt
	mov	r3,r7
	addc	r6,r7
	addc	r5,r1
.L351:
	mov.l	.L388,r3
	clrt
	mov	#0,r2
	addc	r7,r3
	addc	r1,r2
	cmp/hs	r12,r2
	bt	.L416
	bra	.L425
	dt	r9
.L416:
	cmp/hi	r12,r2
	bt	.L365
	bra	.L381
	nop
.L365:
	mov.w	.L389,r1
	mov	#9,r5
	mov.w	.L390,r7
	mov	#-33,r8
	mov.l	@(24,r15),r3
	add	r11,r1
	mov.l	@(20,r15),r12
	sub	r11,r7
	mov	#5,r4
	bra	.L358
	mov	#8,r2
	.align 1
.L382:
	mov	r9,r0
	cmp/eq	#45,r0
	bf/s	.L427
	mov	r12,r0
.L354:
	mov	#0,r0
	mov.b	r9,@r1
	mov.b	r0,@(1,r1)
	dt	r2
	bt/s	.L373
	add	#1,r1
.L383:
	and	r10,r3
	mov	r10,r0
	add	#1,r3
	and	r3,r0
	mov.b	@(r0,r13),r12
.L358:
	mov	r7,r0
	add	r1,r0
	tst	r0,r0
	bt/s	.L382
	exts.b	r12,r9
	mov	r12,r0
.L427:
	add	#-48,r0
	extu.b	r0,r0
	cmp/hi	r5,r0
	bf/s	.L354
	mov	r12,r0
	and	r8,r0
	add	#-65,r0
	extu.b	r0,r0
	cmp/hi	r4,r0
	bf	.L354
	dt	r2
	bf/s	.L383
	add	#1,r1
.L373:
	mov	#4,r2
	mov	r11,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L377:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L376:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L386:
	.short	255
.L389:
	.short	152
.L390:
	.short	-152
.L391:
	.align 2
.L387:
	.long	1073741823
.L388:
	.long	-2147483648
	.align 1
.L362:
	add	#64,r6
	mov	#0,r7
	mov.l	r6,@(12,r15)
	mov	#0,r4
.L341:
	mov.l	@(16,r15),r1
	mov.l	.L392,r2
	mov.l	r4,@(4,r1)
	mov.l	@r11,r0
	mov.l	@(8,r15),r3
	add	r2,r0
	mov.l	.L393,r6
	shll2	r0
	mov.l	@(12,r15),r14
	mov.l	r5,@(r0,r3)
	mov.l	@r11,r0
	mov.l	@(12,r14),r5
	add	r6,r0
	mov.l	.L394,r4
	shll2	r0
	mov.l	.L395,r8
	mov.l	r7,@(r0,r3)
	mov.l	@r11,r1
	add	#1,r1
	mov.l	r1,@r11
	mov.l	.L396,r1
	jsr	@r1
	nop
	mov.l	.L397,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L398,r4
	jsr	@r8
	nop
	mov.l	.L399,r4
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
.L378:
	mov	#1,r1
	cmp/hi	r1,r4
	bf/s	.L363
	add	#1,r5
	mov	r10,r2
	and	r5,r2
	mov	r2,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r3
	mov	#1,r1
	bra	.L361
	mov.l	r1,@r15
	.align 1
.L381:
	mov.l	.L400,r6
	cmp/hi	r6,r3
	bf	.L352
	bra	.L365
	nop
	.align 2
.L352:
	dt	r9
	.align 2
.L425:
	add	#-1,r4
	bt/s	.L384
	add	#1,r0
	and	r10,r0
	mov.b	@(r0,r13),r3
	bra	.L360
	extu.b	r3,r3
	.align 1
.L350:
	subc	r6,r7
	bra	.L351
	subc	r5,r1
	.align 1
.L348:
	add	#-65,r2
	extu.b	r2,r2
	mov	#5,r6
	cmp/hi	r6,r2
	bt/s	.L385
	mov	r3,r6
	bra	.L347
	add	#-55,r6
	.align 1
.L384:
	mov	#0,r4
	bra	.L341
	mov	r0,r5
	.align 1
.L379:
	mov.l	r1,@r15
	bra	.L344
	and	r10,r5
	.align 1
.L385:
	bra	.L341
	mov	r0,r5
	.align 1
.L363:
	mov	#1,r2
	mov.l	r2,@r15
.L343:
	tst	r4,r4
	bt/s	.L341
	mov	#0,r7
	and	r10,r5
	mov	r5,r0
	mov.b	@(r0,r13),r1
	extu.b	r1,r3
.L413:
	bra	.L426
	mov	#0,r7
	.align 1
.L380:
	and	r10,r2
	mov	r2,r0
	mov.b	@(r0,r13),r0
	cmp/eq	#120,r0
	bf	.L413
	mov	r2,r5
	add	#-2,r4
	bra	.L343
	add	#1,r5
.L401:
	.align 2
.L392:
	.long	1073741823
.L393:
	.long	1073741822
.L394:
	.long	.LC0
.L395:
	.long	log_text_raw
.L396:
	.long	log_text
.L397:
	.long	log_bytes
.L398:
	.long	.LC1
.L399:
	.long	.LC2
.L400:
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
	bt/s	.L437
	add	#-8,r15
	mov.l	.L439,r0
	mov.l	@(4,r4),r3
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r3),r7
	tst	r7,r7
	bt	.L431
	mov.w	.L440,r6
	cmp/gt	r6,r2
	bt/s	.L438
	add	r0,r3
	mov.l	r7,@(4,r3)
	mov.l	@r4,r2
	add	#1,r2
	mov.l	r2,@r4
.L431:
	mov.l	.L441,r2
	mov	r1,r8
	add	#64,r8
	mov.l	.L442,r4
	mov.l	@(12,r8),r5
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L443,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L444,r2
	mov.l	.L445,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L446,r4
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
.L437:
	mov	#10,r7
	mov	r4,r3
	add	#124,r3
	mov.l	r7,@(24,r3)
	add	#80,r1
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L438:
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L440:
	.short	255
.L447:
	.align 2
.L439:
	.long	1073741823
.L441:
	.long	log_text
.L442:
	.long	.LC0
.L443:
	.long	log_bytes
.L444:
	.long	log_text_raw
.L445:
	.long	.LC1
.L446:
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
	mov.l	.L450,r2
	mov.l	@r4,r1
	mov.l	@(8,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L451,r10
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	.L452,r4
	mov.l	@(r0,r2),r2
	mov.l	r2,@r1
	mov.l	.L453,r1
	jsr	@r1
	nop
	mov.l	.L454,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L455,r4
	jsr	@r10
	nop
	mov.l	.L456,r4
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
.L457:
	.align 2
.L450:
	.long	1073741823
.L451:
	.long	log_text_raw
.L452:
	.long	.LC0
.L453:
	.long	log_text
.L454:
	.long	log_bytes
.L455:
	.long	.LC1
.L456:
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
	mov.l	.L460,r2
	mov.l	@r4,r1
	mov.l	@(0,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L461,r10
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	.L462,r4
	mov.b	@(r0,r2),r2
	extu.b	r2,r2
	mov.l	r2,@r1
	mov.l	.L463,r1
	jsr	@r1
	nop
	mov.l	.L464,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L465,r4
	jsr	@r10
	nop
	mov.l	.L466,r4
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
.L467:
	.align 2
.L460:
	.long	1073741823
.L461:
	.long	log_text_raw
.L462:
	.long	.LC0
.L463:
	.long	log_text
.L464:
	.long	log_bytes
.L465:
	.long	.LC1
.L466:
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
	mov.l	.L470,r2
	mov.l	@r4,r1
	mov.l	@(4,r9),r0
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	.L471,r10
	mov.l	@r1,r2
	and	r2,r0
	mov.l	@(52,r4),r2
	mov.l	.L472,r4
	mov.w	@(r0,r2),r2
	extu.w	r2,r2
	mov.l	r2,@r1
	mov.l	.L473,r1
	jsr	@r1
	nop
	mov.l	.L474,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L475,r4
	jsr	@r10
	nop
	mov.l	.L476,r4
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
.L477:
	.align 2
.L470:
	.long	1073741823
.L471:
	.long	log_text_raw
.L472:
	.long	.LC0
.L473:
	.long	log_text
.L474:
	.long	log_bytes
.L475:
	.long	.LC1
.L476:
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
	mov.l	.L481,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r2
	cmp/pz	r2
	bt/s	.L479
	mov	r4,r8
	neg	r2,r2
	mov.l	r2,@r1
.L479:
	mov.l	.L482,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L483,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L484,r1
	mov	#32,r5
	mov.l	.L485,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L486,r4
	jsr	@r10
	nop
	mov.l	.L487,r4
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
.L488:
	.align 2
.L481:
	.long	1073741823
.L482:
	.long	log_text
.L483:
	.long	.LC0
.L484:
	.long	log_bytes
.L485:
	.long	log_text_raw
.L486:
	.long	.LC1
.L487:
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
	bf/s	.L497
	add	#-4,r15
	mov.l	.L498,r7
	mov	r4,r2
	add	#124,r2
	mov	r1,r3
	mov.l	@(52,r2),r0
	add	#-1,r3
	mov.l	@(4,r4),r2
	add	r7,r1
	shll2	r1
	mov.l	r3,@r4
	tst	r0,r0
	bt/s	.L492
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
	mov.l	.L499,r3
	mov	r0,r2
	mov.l	@r8,r0
	mov.l	@(4,r8),r1
	add	r3,r0
	shll2	r0
	mov.l	r2,@(r0,r1)
.L493:
	mov.l	.L500,r1
	mov.l	.L501,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L502,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L503,r1
	mov.l	.L504,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L505,r4
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
.L497:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L492:
	mov	r4,r9
	mov.l	r0,@r1
	bra	.L493
	add	#64,r9
.L506:
	.align 2
.L498:
	.long	1073741822
.L499:
	.long	1073741823
.L500:
	.long	log_text
.L501:
	.long	.LC0
.L502:
	.long	log_bytes
.L503:
	.long	log_text_raw
.L504:
	.long	.LC1
.L505:
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
	bt/s	.L508
	and	r1,r2
	add	#4,r1
	sub	r2,r1
	mov.l	@(8,r8),r2
	and	r2,r1
	mov.l	r1,@(60,r4)
.L508:
	mov.l	.L513,r1
	mov.l	.L514,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L515,r1
	mov	#32,r5
	mov.l	.L516,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L517,r4
	jsr	@r10
	nop
	mov.l	.L518,r4
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
.L519:
	.align 2
.L513:
	.long	log_text
.L514:
	.long	.LC0
.L515:
	.long	log_bytes
.L516:
	.long	log_text_raw
.L517:
	.long	.LC1
.L518:
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
	mov.l	.L526,r2
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
	bt/s	.L521
	sub	r2,r6
	add	#4,r1
	sub	r6,r1
.L521:
	mov	r9,r8
	add	#64,r8
	mov.l	@(8,r8),r2
	mov.l	@(12,r8),r5
	and	r2,r1
	mov.l	.L527,r4
	mov.l	r1,@r3
	mov.l	.L528,r1
	mov.l	.L529,r10
	jsr	@r1
	nop
	mov.l	.L530,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L531,r4
	jsr	@r10
	nop
	mov.l	.L532,r4
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
.L533:
	.align 2
.L526:
	.long	1073741823
.L527:
	.long	.LC0
.L528:
	.long	log_text
.L529:
	.long	log_text_raw
.L530:
	.long	log_bytes
.L531:
	.long	.LC1
.L532:
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
	mov.l	.L536,r4
	and	r3,r2
	mov.l	.L537,r10
	mov.l	r2,@r1
	mov.l	.L538,r1
	jsr	@r1
	nop
	mov.l	.L539,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L540,r4
	jsr	@r10
	nop
	mov.l	.L541,r4
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
.L542:
	.align 2
.L536:
	.long	.LC0
.L537:
	.long	log_text_raw
.L538:
	.long	log_text
.L539:
	.long	log_bytes
.L540:
	.long	.LC1
.L541:
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
	mov.l	.L545,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L546,r1
	mov.l	.L547,r4
	jsr	@r1
	nop
	mov.l	.L548,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L549,r4
	jsr	@r10
	nop
	mov.l	.L550,r4
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
.L551:
	.align 2
.L545:
	.long	log_text_raw
.L546:
	.long	log_text
.L547:
	.long	.LC0
.L548:
	.long	log_bytes
.L549:
	.long	.LC1
.L550:
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
	mov.l	.L554,r2
	mov.l	@r4,r1
	mov.l	@(4,r4),r3
	add	r2,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L555,r10
	add	r3,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r7
	mov.l	@r1,r2
	mov.l	r7,@r1
	mov.l	.L556,r1
	mov.l	@r4,r0
	mov.l	.L557,r4
	add	r1,r0
	mov	r2,r1
	mov.l	@(0,r9),r2
	add	r7,r1
	shll2	r0
	and	r2,r1
	mov.l	r1,@(r0,r3)
	mov.l	.L558,r1
	jsr	@r1
	nop
	mov.l	.L559,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L560,r4
	jsr	@r10
	nop
	mov.l	.L561,r4
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
.L562:
	.align 2
.L554:
	.long	1073741823
.L555:
	.long	log_text_raw
.L556:
	.long	1073741822
.L557:
	.long	.LC0
.L558:
	.long	log_text
.L559:
	.long	log_bytes
.L560:
	.long	.LC1
.L561:
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
	mov.l	.L565,r2
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	.L566,r4
	add	r2,r1
	mov.l	.L567,r10
	mov.l	@r1,r2
	shll2	r2
	mov.l	r2,@r1
	mov.l	.L568,r1
	jsr	@r1
	nop
	mov.l	.L569,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L570,r4
	jsr	@r10
	nop
	mov.l	.L571,r4
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
.L572:
	.align 2
.L565:
	.long	1073741823
.L566:
	.long	.LC0
.L567:
	.long	log_text_raw
.L568:
	.long	log_text
.L569:
	.long	log_bytes
.L570:
	.long	.LC1
.L571:
	.long	.LC2
	.size	prim_cells, .-prim_cells
	.align 1
	.align 2
	.global	prim_c_r
	.type	prim_c_r, @function
prim_c_r:
	mov.l	r8,@-r15
	mov	r4,r1
	mov.l	r9,@-r15
	add	#124,r1
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@(44,r1),r1
	tst	r1,r1
	bt/s	.L575
	mov	r4,r9
	mov.l	.L588,r4
	jsr	@r1
	nop
	mov.w	.L582,r1
	add	r9,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L575
	jsr	@r1
	nop
.L575:
	mov.l	.L583,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L584,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L585,r1
	mov	#32,r5
	mov.l	.L586,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L587,r4
	jsr	@r10
	nop
	mov.l	.L588,r4
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
.L582:
	.short	188
.L589:
	.align 2
.L588:
	.long	.LC2
.L583:
	.long	log_text
.L584:
	.long	.LC0
.L585:
	.long	log_bytes
.L586:
	.long	log_text_raw
.L587:
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
	mov.l	.L592,r10
	mov.l	r1,@r4
	mov.l	.L593,r1
	mov.l	.L594,r4
	jsr	@r1
	nop
	mov.l	.L595,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L596,r4
	jsr	@r10
	nop
	mov.l	.L597,r4
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
.L598:
	.align 2
.L592:
	.long	log_text_raw
.L593:
	.long	log_text
.L594:
	.long	.LC0
.L595:
	.long	log_bytes
.L596:
	.long	.LC1
.L597:
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
	mov.l	.L601,r10
	mov.l	r1,@r4
	mov.l	.L602,r1
	mov.l	.L603,r4
	jsr	@r1
	nop
	mov.l	.L604,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L605,r4
	jsr	@r10
	nop
	mov.l	.L606,r4
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
.L607:
	.align 2
.L601:
	.long	log_text_raw
.L602:
	.long	log_text
.L603:
	.long	.LC0
.L604:
	.long	log_bytes
.L605:
	.long	.LC1
.L606:
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
	mov.l	.L610,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	@(12,r9),r5
	shll2	r0
	mov.l	.L611,r10
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(4,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L612,r1
	mov.l	.L613,r4
	jsr	@r1
	nop
	mov.l	.L614,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L615,r4
	jsr	@r10
	nop
	mov.l	.L616,r4
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
.L617:
	.align 2
.L610:
	.long	1073741823
.L611:
	.long	log_text_raw
.L612:
	.long	log_text
.L613:
	.long	.LC0
.L614:
	.long	log_bytes
.L615:
	.long	.LC1
.L616:
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
	mov.l	.L620,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L621,r3
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov.l	.L622,r10
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
	mov.l	.L623,r1
	mov.l	.L624,r4
	jsr	@r1
	nop
	mov.l	.L625,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L626,r4
	jsr	@r10
	nop
	mov.l	.L627,r4
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
.L628:
	.align 2
.L620:
	.long	1073741822
.L621:
	.long	1073741823
.L622:
	.long	log_text_raw
.L623:
	.long	log_text
.L624:
	.long	.LC0
.L625:
	.long	log_bytes
.L626:
	.long	.LC1
.L627:
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
	bt/s	.L642
	add	#-8,r15
	mov	r4,r1
	add	#124,r1
	mov.l	@(44,r1),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L632
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
	mov.w	.L643,r1
	add	r8,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L632
	jsr	@r1
	nop
.L632:
	mov.l	.L644,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L645,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L646,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L647,r1
	mov.l	.L648,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L649,r4
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
.L642:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#8,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L643:
	.short	188
.L650:
	.align 2
.L644:
	.long	log_text
.L645:
	.long	.LC0
.L646:
	.long	log_bytes
.L647:
	.long	log_text_raw
.L648:
	.long	.LC1
.L649:
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
	bf/s	.L665
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
	bf/s	.L654
	mov.l	r2,@r4
.L664:
	mov	r1,r8
	add	#64,r8
.L656:
	mov.l	.L667,r2
	mov.l	@(12,r8),r5
	mov.l	.L668,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L669,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L670,r2
	mov.l	.L671,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L672,r4
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
.L654:
	mov.l	@(56,r4),r2
	cmp/hi	r6,r2
	bt	.L666
.L655:
	tst	r2,r2
	bt/s	.L664
	mov	r1,r8
	add	#-8,r3
	mov.l	@r3,r0
	add	#64,r8
	.align 2
.L657:
	mov.l	@(0,r8),r3
	dt	r2
	and	r3,r0
	mov.l	@(52,r1),r3
	mov.b	r7,@(r0,r3)
	bf/s	.L657
	add	#1,r0
	bra	.L656
	nop
	.align 1
.L665:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L666:
	bra	.L655
	mov	r6,r2
.L673:
	.align 2
.L667:
	.long	log_text
.L668:
	.long	.LC0
.L669:
	.long	log_bytes
.L670:
	.long	log_text_raw
.L671:
	.long	.LC1
.L672:
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
	mov.l	.L676,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L677,r1
	mov.l	.L678,r4
	jsr	@r1
	nop
	mov.l	.L679,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L680,r4
	jsr	@r10
	nop
	mov.l	.L681,r4
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
.L682:
	.align 2
.L676:
	.long	log_text_raw
.L677:
	.long	log_text
.L678:
	.long	.LC0
.L679:
	.long	log_bytes
.L680:
	.long	.LC1
.L681:
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
	mov.l	.L685,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L686,r1
	mov.l	.L687,r4
	jsr	@r1
	nop
	mov.l	.L688,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L689,r4
	jsr	@r10
	nop
	mov.l	.L690,r4
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
.L691:
	.align 2
.L685:
	.long	log_text_raw
.L686:
	.long	log_text
.L687:
	.long	.LC0
.L688:
	.long	log_bytes
.L689:
	.long	.LC1
.L690:
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
	mov.l	.L694,r2
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	.L695,r4
	add	r2,r1
	mov.l	.L696,r10
	mov.l	@r1,r2
	not	r2,r2
	mov.l	r2,@r1
	mov.l	.L697,r1
	jsr	@r1
	nop
	mov.l	.L698,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L699,r4
	jsr	@r10
	nop
	mov.l	.L700,r4
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
.L701:
	.align 2
.L694:
	.long	1073741823
.L695:
	.long	.LC0
.L696:
	.long	log_text_raw
.L697:
	.long	log_text
.L698:
	.long	log_bytes
.L699:
	.long	.LC1
.L700:
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
	mov.l	.L704,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L705,r1
	mov.l	.L706,r4
	jsr	@r1
	nop
	mov.l	.L707,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L708,r4
	jsr	@r10
	nop
	mov.l	.L709,r4
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
.L710:
	.align 2
.L704:
	.long	log_text_raw
.L705:
	.long	log_text
.L706:
	.long	.LC0
.L707:
	.long	log_bytes
.L708:
	.long	.LC1
.L709:
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
	bt/s	.L722
	add	#-4,r15
	mov.l	.L725,r2
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov	r4,r2
	add	#124,r2
	mov.l	@(56,r2),r0
	tst	r0,r0
	bt/s	.L723
	mov	#-1,r4
	mov.l	@r1,r1
	tst	r1,r1
	jsr	@r0
	negc	r4,r4
	mov.l	.L725,r1
	mov	r0,r2
	mov.l	@r8,r0
	add	r1,r0
	mov.l	@(4,r8),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.w	.L726,r1
	add	r8,r1
	mov.l	@(4,r1),r1
	tst	r1,r1
	bt	.L715
	jsr	@r1
	nop
.L715:
	mov.l	.L727,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L728,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L729,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L730,r1
	mov.l	.L731,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L732,r4
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
.L722:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r8
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L723:
	bra	.L715
	mov.l	r0,@r1
	.align 1
.L726:
	.short	188
.L733:
	.align 2
.L725:
	.long	1073741823
.L727:
	.long	log_text
.L728:
	.long	.LC0
.L729:
	.long	log_bytes
.L730:
	.long	log_text_raw
.L731:
	.long	.LC1
.L732:
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
	mov.l	.L736,r4
	shld	r3,r2
	mov.l	.L737,r10
	mov.l	r2,@r1
	mov.l	.L738,r1
	jsr	@r1
	nop
	mov.l	.L739,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L740,r4
	jsr	@r10
	nop
	mov.l	.L741,r4
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
.L742:
	.align 2
.L736:
	.long	.LC0
.L737:
	.long	log_text_raw
.L738:
	.long	log_text
.L739:
	.long	log_bytes
.L740:
	.long	.LC1
.L741:
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
	bf	.L744
	mov.l	r2,@(r0,r1)
.L744:
	mov.l	.L746,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L747,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L748,r1
	mov	#32,r5
	mov.l	.L749,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L750,r4
	jsr	@r10
	nop
	mov.l	.L751,r4
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
.L752:
	.align 2
.L746:
	.long	log_text
.L747:
	.long	.LC0
.L748:
	.long	log_bytes
.L749:
	.long	log_text_raw
.L750:
	.long	.LC1
.L751:
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
	bt	.L754
	mov.l	r2,@(r0,r1)
.L754:
	mov.l	.L756,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L757,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L758,r1
	mov	#32,r5
	mov.l	.L759,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L760,r4
	jsr	@r10
	nop
	mov.l	.L761,r4
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
.L762:
	.align 2
.L756:
	.long	log_text
.L757:
	.long	.LC0
.L758:
	.long	log_bytes
.L759:
	.long	log_text_raw
.L760:
	.long	.LC1
.L761:
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
	bt/s	.L764
	add	r0,r2
	mov.l	.L769,r0
	mov	r3,r5
	mov.l	@r2,r7
	jsr	@r0
	mov	r7,r4
	mul.l	r3,r0
	mov	r7,r3
	sts	macl,r1
	sub	r1,r3
.L764:
	mov.l	.L770,r1
	mov	r8,r9
	add	#64,r9
	mov.l	r3,@r2
	mov.l	.L771,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L772,r1
	mov	#32,r5
	mov.l	.L773,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L774,r4
	jsr	@r10
	nop
	mov.l	.L775,r4
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
.L776:
	.align 2
.L769:
	.long	__sdivsi3_i4i
.L770:
	.long	log_text
.L771:
	.long	.LC0
.L772:
	.long	log_bytes
.L773:
	.long	log_text_raw
.L774:
	.long	.LC1
.L775:
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
	mov.l	.L779,r2
	mov.l	@r4,r1
	mov.l	@(12,r9),r5
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	.L780,r4
	add	r2,r1
	mov.l	.L781,r10
	mov.l	@r1,r2
	neg	r2,r2
	mov.l	r2,@r1
	mov.l	.L782,r1
	jsr	@r1
	nop
	mov.l	.L783,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L784,r4
	jsr	@r10
	nop
	mov.l	.L785,r4
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
.L786:
	.align 2
.L779:
	.long	1073741823
.L780:
	.long	.LC0
.L781:
	.long	log_text_raw
.L782:
	.long	log_text
.L783:
	.long	log_bytes
.L784:
	.long	.LC1
.L785:
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
	mov.l	.L789,r4
	or	r3,r2
	mov.l	.L790,r10
	mov.l	r2,@r1
	mov.l	.L791,r1
	jsr	@r1
	nop
	mov.l	.L792,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L793,r4
	jsr	@r10
	nop
	mov.l	.L794,r4
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
.L795:
	.align 2
.L789:
	.long	.LC0
.L790:
	.long	log_text_raw
.L791:
	.long	log_text
.L792:
	.long	log_bytes
.L793:
	.long	.LC1
.L794:
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
	mov.l	.L798,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	@(12,r9),r5
	shll2	r0
	mov.l	.L799,r10
	mov.l	@(r0,r1),r2
	add	r0,r1
	mov.l	r2,@(8,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L800,r1
	mov.l	.L801,r4
	jsr	@r1
	nop
	mov.l	.L802,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L803,r4
	jsr	@r10
	nop
	mov.l	.L804,r4
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
.L805:
	.align 2
.L798:
	.long	1073741822
.L799:
	.long	log_text_raw
.L800:
	.long	log_text
.L801:
	.long	.LC0
.L802:
	.long	log_bytes
.L803:
	.long	.LC1
.L804:
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
	mov.l	.L808,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L809,r3
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov.l	.L810,r10
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
	mov.l	.L811,r1
	mov.l	.L812,r4
	jsr	@r1
	nop
	mov.l	.L813,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L814,r4
	jsr	@r10
	nop
	mov.l	.L815,r4
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
.L816:
	.align 2
.L808:
	.long	1073741820
.L809:
	.long	1073741821
.L810:
	.long	log_text_raw
.L811:
	.long	log_text
.L812:
	.long	.LC0
.L813:
	.long	log_bytes
.L814:
	.long	.LC1
.L815:
	.long	.LC2
	.size	prim_two_over, .-prim_two_over
	.align 1
	.align 2
	.global	prim_page
	.type	prim_page, @function
prim_page:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.w	.L825,r8
	sts.l	pr,@-r15
	add	r4,r8
	mov.l	@(8,r8),r1
	tst	r1,r1
	bt/s	.L819
	mov	r4,r9
	jsr	@r1
	nop
	mov.l	@(0,r8),r1
	tst	r1,r1
	bt	.L819
	jsr	@r1
	nop
.L819:
	mov.l	.L826,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L827,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L828,r1
	mov	#32,r5
	mov.l	.L829,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L830,r4
	jsr	@r10
	nop
	mov.l	.L831,r4
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
.L825:
	.short	188
.L832:
	.align 2
.L826:
	.long	log_text
.L827:
	.long	.LC0
.L828:
	.long	log_bytes
.L829:
	.long	log_text_raw
.L830:
	.long	.LC1
.L831:
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
	mov.l	.L835,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L836,r10
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
	mov.l	.L837,r6
	mov.l	.L838,r1
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L839,r4
	add	r1,r0
	mov.l	.L840,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L841,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L842,r4
	jsr	@r10
	nop
	mov.l	.L843,r4
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
.L844:
	.align 2
.L835:
	.long	1073741823
.L836:
	.long	log_text_raw
.L837:
	.long	1073741822
.L838:
	.long	1073741821
.L839:
	.long	.LC0
.L840:
	.long	log_text
.L841:
	.long	log_bytes
.L842:
	.long	.LC1
.L843:
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
	mov.l	.L847,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L848,r10
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
	mov.l	.L849,r6
	mov.l	.L850,r1
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L851,r4
	add	r1,r0
	mov.l	.L852,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
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
.L847:
	.long	1073741823
.L848:
	.long	log_text_raw
.L849:
	.long	1073741822
.L850:
	.long	1073741821
.L851:
	.long	.LC0
.L852:
	.long	log_text
.L853:
	.long	log_bytes
.L854:
	.long	.LC1
.L855:
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
	mov.l	.L859,r4
	shad	r3,r2
	mov.l	.L860,r10
	mov.l	r2,@r1
	mov.l	.L861,r1
	jsr	@r1
	nop
	mov.l	.L862,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L863,r4
	jsr	@r10
	nop
	mov.l	.L864,r4
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
.L865:
	.align 2
.L859:
	.long	.LC0
.L860:
	.long	log_text_raw
.L861:
	.long	log_text
.L862:
	.long	log_bytes
.L863:
	.long	.LC1
.L864:
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
	mov	r4,r1
	mov.l	r9,@-r15
	add	#124,r1
	mov.l	r10,@-r15
	sts.l	pr,@-r15
	mov.l	@(44,r1),r1
	tst	r1,r1
	bt/s	.L868
	mov	r4,r9
	mov.l	.L874,r4
	jsr	@r1
	nop
	mov.w	.L875,r1
	add	r9,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L868
	jsr	@r1
	nop
.L868:
	mov.l	.L876,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L877,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L878,r1
	mov	#32,r5
	mov.l	.L879,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L880,r4
	jsr	@r10
	nop
	mov.l	.L881,r4
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
.L875:
	.short	188
.L882:
	.align 2
.L874:
	.long	.LC3
.L876:
	.long	log_text
.L877:
	.long	.LC0
.L878:
	.long	log_bytes
.L879:
	.long	log_text_raw
.L880:
	.long	.LC1
.L881:
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
	mov	r4,r9
	mov.l	r10,@-r15
	mov.l	r11,@-r15
	sts.l	pr,@-r15
	mov.l	@r4,r0
	cmp/gt	r1,r0
	bf/s	.L901
	add	#-4,r15
	add	#-1,r0
	mov.l	@(4,r4),r1
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	cmp/pl	r2
	bf	.L887
	mov	r4,r11
	add	#124,r11
	mov.l	@(44,r11),r1
	tst	r1,r1
	bt	.L887
	mov.w	.L904,r7
	add	r4,r7
	mov.l	@(12,r7),r10
	cmp/gt	r2,r10
	bt/s	.L902
	mov.l	r7,@r15
.L889:
	cmp/pl	r10
	bf	.L890
	bra	.L891
	mov	#0,r8
	.align 1
.L903:
	mov.l	@(44,r11),r1
.L891:
	mov.l	.L905,r4
	jsr	@r1
	add	#1,r8
	cmp/eq	r8,r10
	bf	.L903
.L890:
	mov.l	@r15,r7
	mov.l	@(0,r7),r1
	tst	r1,r1
	bt	.L887
	jsr	@r1
	nop
.L887:
	mov.l	.L906,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L907,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L908,r1
	mov	#32,r5
	mov.l	.L909,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L910,r4
	jsr	@r10
	nop
	mov.l	.L911,r4
	jsr	@r10
	nop
	mov.l	@(12,r8),r1
	mov	r9,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
	.align 1
.L901:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r9
	mov	#0,r1
	mov.b	r1,@r9
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L902:
	bra	.L889
	mov	r2,r10
	.align 1
.L904:
	.short	188
.L912:
	.align 2
.L905:
	.long	.LC3
.L906:
	.long	log_text
.L907:
	.long	.LC0
.L908:
	.long	log_bytes
.L909:
	.long	log_text_raw
.L910:
	.long	.LC1
.L911:
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
	mov.l	.L915,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	@(12,r9),r5
	shll2	r1
	mov.l	.L916,r10
	add	r2,r1
	mov	r1,r7
	add	#-4,r7
	mov.l	@r7,r7
	mov.l	@r1,r3
	mov.l	r7,@r1
	mov.l	@r4,r0
	mov.l	.L917,r1
	mov.l	.L918,r4
	add	r1,r0
	mov.l	.L919,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L920,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L921,r4
	jsr	@r10
	nop
	mov.l	.L922,r4
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
.L923:
	.align 2
.L915:
	.long	1073741823
.L916:
	.long	log_text_raw
.L917:
	.long	1073741822
.L918:
	.long	.LC0
.L919:
	.long	log_text
.L920:
	.long	log_bytes
.L921:
	.long	.LC1
.L922:
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
	mov.l	.L926,r3
	mov.l	@r4,r1
	mov.l	@(4,r4),r2
	add	r3,r1
	mov.l	.L927,r10
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
	mov.l	.L928,r5
	mov.l	.L929,r1
	add	r5,r0
	mov.l	@(12,r9),r5
	shll2	r0
	mov.l	r6,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L930,r6
	add	r6,r0
	shll2	r0
	mov.l	r7,@(r0,r2)
	mov.l	@r4,r0
	mov.l	.L931,r4
	add	r1,r0
	mov.l	.L932,r1
	shll2	r0
	jsr	@r1
	mov.l	r3,@(r0,r2)
	mov.l	.L933,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L934,r4
	jsr	@r10
	nop
	mov.l	.L935,r4
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
.L936:
	.align 2
.L926:
	.long	1073741823
.L927:
	.long	log_text_raw
.L928:
	.long	1073741822
.L929:
	.long	1073741820
.L930:
	.long	1073741821
.L931:
	.long	.LC0
.L932:
	.long	log_text
.L933:
	.long	log_bytes
.L934:
	.long	.LC1
.L935:
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
	bf/s	.L957
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
	mov.l	@(44,r12),r1
	tst	r1,r1
	bt/s	.L958
	add	r0,r2
	mov.l	@(56,r4),r11
	add	#-4,r2
	cmp/hi	r3,r11
	bt/s	.L959
	mov.l	@r2,r8
	mov	#0,r0
	tst	r11,r11
	mov.b	r0,@(1,r15)
	mov	r13,r14
	bt/s	.L942
	add	#64,r14
.L961:
	mov	r13,r14
	mov	#0,r9
	bra	.L943
	add	#64,r14
	.align 1
.L960:
	mov.l	@(44,r12),r1
	add	#1,r8
.L943:
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
	bf	.L960
.L942:
	mov.w	.L962,r1
	add	r13,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L940
	jsr	@r1
	nop
.L940:
	mov.l	.L963,r1
	mov.l	.L964,r4
	jsr	@r1
	mov.l	@(12,r14),r5
	mov.l	.L965,r1
	mov	#32,r5
	mov.l	.L966,r8
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L967,r4
	jsr	@r8
	nop
	mov.l	.L968,r4
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
.L959:
	mov	#0,r0
	mov	r3,r11
	mov.b	r0,@(1,r15)
	tst	r11,r11
	mov	r13,r14
	bf/s	.L961
	add	#64,r14
	bra	.L942
	nop
	.align 1
.L957:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L958:
	mov	r4,r14
	bra	.L940
	add	#64,r14
	.align 1
.L962:
	.short	188
.L969:
	.align 2
.L963:
	.long	log_text
.L964:
	.long	.LC0
.L965:
	.long	log_bytes
.L966:
	.long	log_text_raw
.L967:
	.long	.LC1
.L968:
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
	mov.l	.L972,r4
	cmp/hi	r2,r3
	mov.l	.L973,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L974,r1
	jsr	@r1
	nop
	mov.l	.L975,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L976,r4
	jsr	@r10
	nop
	mov.l	.L977,r4
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
.L978:
	.align 2
.L972:
	.long	.LC0
.L973:
	.long	log_text_raw
.L974:
	.long	log_text
.L975:
	.long	log_bytes
.L976:
	.long	.LC1
.L977:
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
	mov.l	.L981,r4
	cmp/hi	r2,r3
	mov.l	.L982,r10
	subc	r2,r2
	mov.l	r2,@r1
	mov.l	.L983,r1
	jsr	@r1
	nop
	mov.l	.L984,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L985,r4
	jsr	@r10
	nop
	mov.l	.L986,r4
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
.L987:
	.align 2
.L981:
	.long	.LC0
.L982:
	.long	log_text_raw
.L983:
	.long	log_text
.L984:
	.long	log_bytes
.L985:
	.long	.LC1
.L986:
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
	mov.l	.L990,r4
	xor	r3,r2
	mov.l	.L991,r10
	mov.l	r2,@r1
	mov.l	.L992,r1
	jsr	@r1
	nop
	mov.l	.L993,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L994,r4
	jsr	@r10
	nop
	mov.l	.L995,r4
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
.L996:
	.align 2
.L990:
	.long	.LC0
.L991:
	.long	log_text_raw
.L992:
	.long	log_text
.L993:
	.long	log_bytes
.L994:
	.long	.LC1
.L995:
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
	mov.l	.L999,r4
	cmp/eq	r2,r3
	mov.l	.L1000,r10
	subc	r2,r2
	not	r2,r2
	mov.l	r2,@r1
	mov.l	.L1001,r1
	jsr	@r1
	nop
	mov.l	.L1002,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1003,r4
	jsr	@r10
	nop
	mov.l	.L1004,r4
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
.L1005:
	.align 2
.L999:
	.long	.LC0
.L1000:
	.long	log_text_raw
.L1001:
	.long	log_text
.L1002:
	.long	log_bytes
.L1003:
	.long	.LC1
.L1004:
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
	mov.l	.L1008,r10
	mov	#0,r2
	mov.l	r2,@r1
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L1009,r1
	mov.l	.L1010,r4
	jsr	@r1
	nop
	mov.l	.L1011,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1012,r4
	jsr	@r10
	nop
	mov.l	.L1013,r4
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
.L1014:
	.align 2
.L1008:
	.long	log_text_raw
.L1009:
	.long	log_text
.L1010:
	.long	.LC0
.L1011:
	.long	log_bytes
.L1012:
	.long	.LC1
.L1013:
	.long	.LC2
	.size	prim_false, .-prim_false
	.align 1
	.align 2
	.global	prim_true
	.type	prim_true, @function
prim_true:
	mov.l	.L1016,r1
	jmp	@r1
	nop
.L1017:
	.align 2
.L1016:
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
	mov.l	.L1020,r4
	mov.l	r2,@r1
	mov.l	.L1021,r1
	mov.l	.L1022,r10
	jsr	@r1
	nop
	mov.l	.L1023,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1024,r4
	jsr	@r10
	nop
	mov.l	.L1025,r4
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
.L1026:
	.align 2
.L1020:
	.long	.LC0
.L1021:
	.long	log_text
.L1022:
	.long	log_text_raw
.L1023:
	.long	log_bytes
.L1024:
	.long	.LC1
.L1025:
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
	mov.l	.L1030,r2
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	r2,r0
	mov.l	.L1030,r7
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	@(r0,r1),r2
	add	r1,r0
	mov	r0,r3
	add	#-4,r3
	mov.l	@r3,r3
	mov.l	r2,@(4,r0)
	mov.l	@r4,r0
	mov.l	.L1031,r10
	add	r7,r0
	shll2	r0
	mov.l	r3,@(r0,r1)
	mov.l	@r4,r0
	mov.l	.L1032,r3
	add	r3,r0
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L1033,r1
	mov.l	.L1034,r4
	jsr	@r1
	nop
	mov.l	.L1035,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1036,r4
	jsr	@r10
	nop
	mov.l	.L1037,r4
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
.L1038:
	.align 2
.L1030:
	.long	1073741823
.L1031:
	.long	log_text_raw
.L1032:
	.long	1073741822
.L1033:
	.long	log_text
.L1034:
	.long	.LC0
.L1035:
	.long	log_bytes
.L1036:
	.long	.LC1
.L1037:
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
	mov.w	.L1044,r2
	mov.l	@r4,r0
	cmp/gt	r2,r0
	bf/s	.L1040
	add	#-8,r15
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L1040:
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
	mov.l	.L1045,r2
	mov.l	.L1046,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L1047,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L1048,r2
	mov.l	.L1049,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L1050,r4
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
.L1044:
	.short	255
.L1051:
	.align 2
.L1045:
	.long	log_text
.L1046:
	.long	.LC0
.L1047:
	.long	log_bytes
.L1048:
	.long	log_text_raw
.L1049:
	.long	.LC1
.L1050:
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
	mov.l	.L1054,r4
	add	r1,r2
	mov.l	.L1055,r10
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
	mov.l	.L1056,r1
	jsr	@r1
	nop
	mov.l	.L1057,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1058,r4
	jsr	@r10
	nop
	mov.l	.L1059,r4
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
.L1060:
	.align 2
.L1054:
	.long	.LC0
.L1055:
	.long	log_text_raw
.L1056:
	.long	log_text
.L1057:
	.long	log_bytes
.L1058:
	.long	.LC1
.L1059:
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
	mov.l	.L1063,r1
	mov.l	.L1064,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1065,r1
	mov	#32,r5
	mov.l	.L1066,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1067,r4
	jsr	@r10
	nop
	mov.l	.L1068,r4
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
.L1069:
	.align 2
.L1063:
	.long	log_text
.L1064:
	.long	.LC0
.L1065:
	.long	log_bytes
.L1066:
	.long	log_text_raw
.L1067:
	.long	.LC1
.L1068:
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
	mov.l	.L1072,r1
	mov.l	.L1073,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1074,r1
	mov	#32,r5
	mov.l	.L1075,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1076,r4
	jsr	@r10
	nop
	mov.l	.L1077,r4
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
.L1078:
	.align 2
.L1072:
	.long	log_text
.L1073:
	.long	.LC0
.L1074:
	.long	log_bytes
.L1075:
	.long	log_text_raw
.L1076:
	.long	.LC1
.L1077:
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
	mov.l	.L1081,r10
	mov	#-2,r2
	and	r2,r1
	mov.l	r1,@(60,r4)
	mov.l	.L1082,r1
	mov.l	.L1083,r4
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
.L1081:
	.long	log_text_raw
.L1082:
	.long	log_text
.L1083:
	.long	.LC0
.L1084:
	.long	log_bytes
.L1085:
	.long	.LC1
.L1086:
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
	mov.l	.L1090,r2
	mov.l	@r4,r1
	mov.l	@(4,r8),r3
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	mov.l	@(12,r8),r5
	add	r1,r2
	mov.l	.L1091,r4
	mov.l	@r2,r1
	mov.l	.L1092,r10
	add	#1,r1
	and	r3,r1
	mov	#-2,r3
	and	r3,r1
	mov.l	r1,@r2
	mov.l	.L1093,r1
	jsr	@r1
	nop
	mov.l	.L1094,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1095,r4
	jsr	@r10
	nop
	mov.l	.L1096,r4
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
.L1097:
	.align 2
.L1090:
	.long	1073741823
.L1091:
	.long	.LC0
.L1092:
	.long	log_text_raw
.L1093:
	.long	log_text
.L1094:
	.long	log_bytes
.L1095:
	.long	.LC1
.L1096:
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
	mov.l	.L1102,r2
	mov.l	@r4,r1
	mov.l	@(4,r4),r9
	add	r2,r1
	shll2	r1
	add	r1,r9
	mov	r4,r1
	add	#124,r1
	mov.l	@(60,r1),r0
	tst	r0,r0
	bt/s	.L1100
	mov	r4,r8
	jsr	@r0
	mov.l	@r9,r4
.L1099:
	mov.l	.L1103,r1
	mov.l	r0,@r9
	mov	r8,r9
	add	#64,r9
	mov.l	.L1104,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1105,r1
	mov	#32,r5
	mov.l	.L1106,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1107,r4
	jsr	@r10
	nop
	mov.l	.L1108,r4
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
.L1100:
	bra	.L1099
	mov	#0,r0
.L1109:
	.align 2
.L1102:
	.long	1073741823
.L1103:
	.long	log_text
.L1104:
	.long	.LC0
.L1105:
	.long	log_bytes
.L1106:
	.long	log_text_raw
.L1107:
	.long	.LC1
.L1108:
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
	bf	.L1111
	mov	r3,r1
.L1111:
	tst	r1,r1
	mov	r8,r9
	bt/s	.L1112
	add	#64,r9
	add	r0,r2
	mov	r8,r9
	add	#-4,r2
	mov.l	@r2,r0
	add	#64,r9
	mov	#0,r3
	.align 2
.L1113:
	mov.l	@(0,r9),r2
	dt	r1
	and	r2,r0
	mov.l	@(52,r8),r2
	mov.b	r3,@(r0,r2)
	bf/s	.L1113
	add	#1,r0
.L1112:
	mov.l	.L1119,r1
	mov.l	.L1120,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1121,r1
	mov	#32,r5
	mov.l	.L1122,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1123,r4
	jsr	@r10
	nop
	mov.l	.L1124,r4
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
.L1125:
	.align 2
.L1119:
	.long	log_text
.L1120:
	.long	.LC0
.L1121:
	.long	log_bytes
.L1122:
	.long	log_text_raw
.L1123:
	.long	.LC1
.L1124:
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
	mov.l	.L1132,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	@r1,r0
	tst	#128,r0
	bt/s	.L1128
	extu.b	r0,r2
	mov.w	.L1133,r2
	or	r0,r2
.L1128:
	mov.l	r2,@r1
	mov	r8,r9
	mov.l	.L1134,r1
	add	#64,r9
	mov.l	.L1135,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1136,r1
	mov	#32,r5
	mov.l	.L1137,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1138,r4
	jsr	@r10
	nop
	mov.l	.L1139,r4
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
.L1133:
	.short	-256
.L1140:
	.align 2
.L1132:
	.long	1073741823
.L1134:
	.long	log_text
.L1135:
	.long	.LC0
.L1136:
	.long	log_bytes
.L1137:
	.long	log_text_raw
.L1138:
	.long	.LC1
.L1139:
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
	mov.l	.L1147,r2
	mov.l	@r4,r1
	add	r2,r1
	mov.l	@(4,r4),r2
	shll2	r1
	add	r2,r1
	mov.l	.L1148,r2
	mov.l	@r1,r3
	tst	r2,r3
	bt/s	.L1143
	extu.w	r3,r2
	mov.l	.L1149,r2
	or	r3,r2
.L1143:
	mov.l	r2,@r1
	mov	r8,r9
	mov.l	.L1150,r1
	add	#64,r9
	mov.l	.L1151,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1152,r1
	mov	#32,r5
	mov.l	.L1153,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1154,r4
	jsr	@r10
	nop
	mov.l	.L1155,r4
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
.L1156:
	.align 2
.L1147:
	.long	1073741823
.L1148:
	.long	32768
.L1149:
	.long	-65536
.L1150:
	.long	log_text
.L1151:
	.long	.LC0
.L1152:
	.long	log_bytes
.L1153:
	.long	log_text_raw
.L1154:
	.long	.LC1
.L1155:
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
	mov.w	.L1162,r2
	mov.l	@r4,r0
	cmp/gt	r2,r0
	bf/s	.L1158
	add	#-8,r15
	mov	#6,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov	#0,r2
	mov.b	r2,@r1
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
	.align 1
.L1158:
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
	mov.l	.L1163,r2
	mov.l	.L1164,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L1165,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L1166,r2
	mov.l	.L1167,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L1168,r4
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
.L1162:
	.short	255
.L1169:
	.align 2
.L1163:
	.long	log_text
.L1164:
	.long	.LC0
.L1165:
	.long	log_bytes
.L1166:
	.long	log_text_raw
.L1167:
	.long	.LC1
.L1168:
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
	mov.l	.L1172,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L1173,r1
	mov.l	.L1174,r4
	jsr	@r1
	nop
	mov.l	.L1175,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1176,r4
	jsr	@r10
	nop
	mov.l	.L1177,r4
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
.L1178:
	.align 2
.L1172:
	.long	log_text_raw
.L1173:
	.long	log_text
.L1174:
	.long	.LC0
.L1175:
	.long	log_bytes
.L1176:
	.long	.LC1
.L1177:
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
	mov	r4,r11
	mov.l	r12,@-r15
	add	#64,r11
	mov.l	r13,@-r15
	mov.l	r14,@-r15
	sts.l	pr,@-r15
	mov.l	@(12,r11),r10
	add	#-12,r15
	mov.l	.L1194,r5
	mov	r15,r9
	mov.l	@(4,r10),r1
	mov	r10,r12
	mov.l	r4,@(4,r15)
	mov	#18,r4
	mov.l	r1,@r15
	add	#8,r12
	mov.l	.L1195,r1
	mov.l	.L1196,r8
	jsr	@r1
	add	#8,r9
	mov.l	.L1197,r4
	jsr	@r8
	mov.l	@(12,r11),r5
	mov.l	@(12,r11),r5
	mov.l	.L1198,r4
	jsr	@r8
	add	#4,r5
	mov.l	.L1199,r4
	jsr	@r8
	mov.l	@r15,r5
	mov.l	.L1200,r4
	jsr	@r8
	mov	r12,r5
	mov.l	@r15,r1
	mov	#0,r0
	tst	r1,r1
	bt/s	.L1180
	mov.b	r0,@(1,r9)
	mov.l	@(4,r15),r13
	add	r1,r10
	add	#8,r10
	mov	r12,r14
	add	#124,r13
	.align 2
.L1182:
	mov.b	@r14+,r5
	mov.l	.L1201,r4
	jsr	@r8
	mov	r5,r6
	mov.l	@(44,r13),r2
	tst	r2,r2
	bt/s	.L1181
	mov	r14,r0
	add	#-16,r0
	mov.b	@(15,r0),r0
	mov	r9,r4
	jsr	@r2
	mov.b	r0,@r9
	mov.l	.L1202,r4
	jsr	@r8
	mov	r9,r5
.L1181:
	cmp/eq	r14,r10
	bf/s	.L1182
	mov.l	@r15,r1
	add	r1,r12
.L1180:
	mov.l	@(4,r15),r3
	mov.w	.L1203,r1
	add	r3,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1183
	jsr	@r1
	nop
.L1183:
	mov.l	.L1204,r4
	jsr	@r8
	mov	r12,r5
	mov.l	@r15,r1
	mov	#4,r5
	mov.l	.L1205,r4
	neg	r1,r0
	and	#3,r0
	add	r0,r12
	mov	r12,r1
	add	#-4,r1
	jsr	@r8
	mov.l	r1,@(12,r11)
	mov.l	.L1206,r4
	jsr	@r8
	mov	r12,r5
	mov.l	.L1207,r4
	jsr	@r8
	mov.l	@(12,r11),r5
	mov.l	.L1208,r1
	jsr	@r1
	nop
	mov.l	.L1209,r4
	jsr	@r8
	mov.l	@(12,r11),r5
	mov.l	.L1210,r1
	mov	#32,r5
	mov.l	.L1211,r8
	jsr	@r1
	mov.l	@(12,r11),r4
	mov.l	.L1212,r4
	jsr	@r8
	nop
	mov.l	.L1213,r4
	jsr	@r8
	nop
	mov.l	@(12,r11),r1
	mov.l	@(4,r15),r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r11)
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
.L1203:
	.short	188
.L1214:
	.align 2
.L1194:
	.long	.LC4
.L1195:
	.long	log_push
.L1196:
	.long	log_text
.L1197:
	.long	.LC5
.L1198:
	.long	.LC6
.L1199:
	.long	.LC7
.L1200:
	.long	.LC8
.L1201:
	.long	.LC9
.L1202:
	.long	.LC10
.L1204:
	.long	.LC11
.L1205:
	.long	.LC12
.L1206:
	.long	.LC13
.L1207:
	.long	.LC14
.L1208:
	.long	log_pop
.L1209:
	.long	.LC0
.L1210:
	.long	log_bytes
.L1211:
	.long	log_text_raw
.L1212:
	.long	.LC1
.L1213:
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
	mov.l	.L1221,r1
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	.L1222,r5
	sts.l	pr,@-r15
	jsr	@r1
	mov	#11,r4
	mov.l	.L1223,r9
	mov.l	.L1224,r4
	jsr	@r9
	mov.l	@(60,r8),r5
	mov.l	@r8,r0
	tst	r0,r0
	bf/s	.L1216
	mov	#10,r2
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1216:
	mov.l	@(4,r8),r1
	add	#-1,r0
	mov.l	r0,@r8
	shll2	r0
	mov.l	@(r0,r1),r5
	mov	r8,r10
	mov.l	@(60,r8),r1
	add	#64,r10
	mov.l	.L1225,r4
	add	r1,r5
	mov.l	@(0,r10),r1
	and	r1,r5
	jsr	@r9
	mov.l	r5,@(60,r8)
	mov.l	.L1226,r1
	jsr	@r1
	nop
	mov.l	.L1227,r4
	jsr	@r9
	mov.l	@(12,r10),r5
	mov.l	.L1228,r1
	mov	#32,r5
	mov.l	.L1229,r9
	jsr	@r1
	mov.l	@(12,r10),r4
	mov.l	.L1230,r4
	jsr	@r9
	nop
	mov.l	.L1231,r4
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
.L1232:
	.align 2
.L1221:
	.long	log_push
.L1222:
	.long	.LC15
.L1223:
	.long	log_text
.L1224:
	.long	.LC16
.L1225:
	.long	.LC17
.L1226:
	.long	log_pop
.L1227:
	.long	.LC0
.L1228:
	.long	log_bytes
.L1229:
	.long	log_text_raw
.L1230:
	.long	.LC1
.L1231:
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
	bt/s	.L1246
	add	#-16,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(44,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L1236
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	mov.l	.L1247,r1
	jsr	@r1
	add	#4,r5
	mov.l	@(44,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(44,r9),r1
	mov.l	.L1248,r4
	jsr	@r1
	nop
	mov.w	.L1249,r1
	add	r8,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1236
	jsr	@r1
	nop
.L1236:
	mov.l	.L1250,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L1251,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1252,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1253,r1
	mov.l	.L1254,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1255,r4
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
.L1246:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1249:
	.short	188
.L1256:
	.align 2
.L1247:
	.long	text_int32
.L1248:
	.long	.LC3
.L1250:
	.long	log_text
.L1251:
	.long	.LC0
.L1252:
	.long	log_bytes
.L1253:
	.long	log_text_raw
.L1254:
	.long	.LC1
.L1255:
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
	mov.l	@(44,r10),r1
	add	#-12,r15
	add	#-1,r0
	mov.l	r0,@r4
	tst	r1,r1
	bt/s	.L1258
	add	#64,r9
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(r0,r1),r0
	mov.l	@(8,r9),r1
	and	r1,r0
	mov.l	@(52,r4),r1
	mov.l	@(r0,r1),r4
	mov.l	.L1266,r1
	jsr	@r1
	mov	r15,r5
	mov.l	@(44,r10),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(44,r10),r1
	mov.l	.L1267,r4
	jsr	@r1
	nop
	mov.w	.L1268,r1
	add	r8,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1258
	jsr	@r1
	nop
.L1258:
	mov.l	.L1269,r1
	mov.l	.L1270,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1271,r1
	mov	#32,r5
	mov.l	.L1272,r10
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1273,r4
	jsr	@r10
	nop
	mov.l	.L1274,r4
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
	.align 1
.L1268:
	.short	188
.L1275:
	.align 2
.L1266:
	.long	text_int32
.L1267:
	.long	.LC3
.L1269:
	.long	log_text
.L1270:
	.long	.LC0
.L1271:
	.long	log_bytes
.L1272:
	.long	log_text_raw
.L1273:
	.long	.LC1
.L1274:
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
	bt/s	.L1289
	add	#-16,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(44,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L1279
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	mov.l	.L1290,r1
	jsr	@r1
	add	#4,r5
	mov.l	@(44,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(44,r9),r1
	mov.l	.L1291,r4
	jsr	@r1
	nop
	mov.w	.L1292,r1
	add	r8,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1279
	jsr	@r1
	nop
.L1279:
	mov.l	.L1293,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L1294,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1295,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1296,r1
	mov.l	.L1297,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1298,r4
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
.L1289:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1292:
	.short	188
.L1299:
	.align 2
.L1290:
	.long	text_uint32
.L1291:
	.long	.LC3
.L1293:
	.long	log_text
.L1294:
	.long	.LC0
.L1295:
	.long	log_bytes
.L1296:
	.long	log_text_raw
.L1297:
	.long	.LC1
.L1298:
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
	bt/s	.L1315
	add	#-4,r15
	mov.l	@(4,r4),r2
	add	#-1,r1
	mov.l	r1,@r4
	shll2	r1
	add	r2,r1
	mov.w	.L1318,r2
	mov.l	@r1,r4
	cmp/hi	r2,r4
	bt/s	.L1303
	mov	#5,r7
	mov.l	.L1319,r1
	shld	r7,r4
	add	r4,r1
	mov.l	@(16,r1),r2
	tst	r2,r2
	bt/s	.L1304
	mov	r8,r4
	jsr	@r2
	mov	r8,r9
	add	#64,r9
	mov.l	@(12,r9),r5
.L1305:
	mov.l	.L1320,r1
	mov.l	.L1321,r4
	jsr	@r1
	nop
	mov.l	.L1322,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1323,r1
	mov.l	.L1324,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1325,r4
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
.L1303:
	mov	r8,r9
	add	#64,r9
	mov.l	@(32,r9),r2
	mov.w	.L1326,r3
	add	r3,r2
	cmp/hi	r4,r2
	bf/s	.L1306
	mov	#5,r2
	mov.w	.L1327,r7
	add	r7,r4
	shld	r2,r4
	mov.l	@(24,r9),r2
	add	r4,r2
	mov	r2,r0
	add	#16,r0
	mov.b	@(12,r0),r0
	extu.b	r0,r0
	cmp/eq	#4,r0
	bt/s	.L1316
	mov.l	@(12,r9),r5
	add	#-1,r0
	extu.b	r0,r0
	mov	#2,r3
	cmp/hi	r3,r0
	bt	.L1309
	mov.l	@r2,r2
	mov.l	@(4,r2),r2
	mov.l	r2,@r1
	mov.l	@r8,r1
	add	#1,r1
	bra	.L1305
	mov.l	r1,@r8
	.align 1
.L1315:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r8
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1316:
	mov.l	@(20,r2),r2
	mov	#9,r3
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(40,r1)
	mov	#0,r2
	mov.l	r3,@(24,r1)
	mov	r8,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L1305
	nop
	.align 1
.L1306:
	mov.l	.L1328,r1
	mov.w	.L1329,r5
	jsr	@r1
	add	r8,r5
	mov	#1,r2
	mov	r8,r1
	add	#124,r1
	mov.l	@(12,r9),r5
	mov.l	r2,@(24,r1)
	mov	#0,r2
	mov	r8,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L1305
	nop
	.align 1
.L1304:
	mov.l	@r1,r1
	mov	#2,r7
	mov	r8,r3
	add	#124,r3
	mov.l	r1,@(40,r3)
	mov	r8,r9
	mov.l	r7,@(24,r3)
	add	#64,r9
	mov	r8,r1
	add	#80,r1
	mov.l	@(12,r9),r5
	mov.b	r2,@r1
	bra	.L1305
	nop
	.align 1
.L1309:
	mov.l	@(24,r8),r1
	mov.l	@(20,r8),r3
	cmp/hs	r3,r1
	bf/s	.L1317
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
	bt/s	.L1311
	mov.l	r3,@(36,r8)
	mov	#5,r7
	mov	r8,r3
	add	#124,r3
	mov.l	r7,@(24,r3)
	mov	#0,r7
	mov	r8,r3
	add	#80,r3
	mov.b	r7,@r3
.L1311:
	add	#-16,r1
	mov.l	r1,@(24,r8)
	mov.l	@r2,r5
	add	#-4,r5
	bra	.L1305
	mov.l	r5,@(12,r9)
	.align 1
.L1317:
	mov	#7,r2
	mov	r8,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	mov	#0,r2
	mov	r8,r1
	add	#80,r1
	mov.b	r2,@r1
	bra	.L1305
	nop
	.align 1
.L1318:
	.short	150
.L1326:
	.short	151
.L1327:
	.short	-151
.L1329:
	.short	152
.L1330:
	.align 2
.L1319:
	.long	forth_primitives
.L1320:
	.long	log_text
.L1321:
	.long	.LC0
.L1322:
	.long	log_bytes
.L1323:
	.long	log_text_raw
.L1324:
	.long	.LC1
.L1325:
	.long	.LC2
.L1328:
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
	bt/s	.L1344
	add	#-16,r15
	mov	r4,r9
	add	#124,r9
	mov.l	@(44,r9),r1
	add	#-1,r0
	tst	r1,r1
	bt/s	.L1334
	mov.l	r0,@r4
	mov.l	@(4,r4),r1
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	mov.l	.L1345,r1
	jsr	@r1
	add	#4,r5
	mov.l	@(44,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.l	@(44,r9),r1
	mov.l	.L1346,r4
	jsr	@r1
	nop
	mov.w	.L1347,r1
	add	r8,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1334
	jsr	@r1
	nop
.L1334:
	mov.l	.L1348,r1
	mov	r8,r9
	add	#64,r9
	mov.l	.L1349,r4
	jsr	@r1
	mov.l	@(12,r9),r5
	mov.l	.L1350,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1351,r1
	mov.l	.L1352,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1353,r4
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
.L1344:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov.b	r0,@(0,r8)
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1347:
	.short	188
.L1354:
	.align 2
.L1345:
	.long	text_hex32
.L1346:
	.long	.LC3
.L1348:
	.long	log_text
.L1349:
	.long	.LC0
.L1350:
	.long	log_bytes
.L1351:
	.long	log_text_raw
.L1352:
	.long	.LC1
.L1353:
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
	bf/s	.L1379
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
	mov.l	.L1381,r3
	mov	r9,r5
	jsr	@r3
	mov.l	r2,@r15
	mov.l	@r15,r2
	mov	#0,r6
	mov	r9,r3
.L1360:
	mov.l	@r3+,r7
	cmp/str	r6,r7
	bf	.L1360
	add	#-4,r3
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1358
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1358
	mov.b	@r3+,r7
	tst	r7,r7
	mov	#-1,r7
	subc	r7,r3
.L1358:
	sett
	mov	r3,r7
	subc	r9,r7
	tst	r7,r7
	bt/s	.L1380
	mov	r9,r5
	mov	r8,r9
	add	#64,r9
	mov	r7,r1
	.align 2
.L1363:
	mov.l	@(0,r9),r0
	dt	r1
	mov.b	@r5+,r3
	and	r2,r0
	mov.l	@(52,r8),r2
	mov.b	r3,@(r0,r2)
	mov	r0,r2
	bf/s	.L1363
	add	#1,r2
.L1362:
	mov.l	@r8,r0
	mov.l	.L1382,r1
	mov.l	@(12,r9),r5
	add	r1,r0
	mov.l	@(4,r8),r1
	shll2	r0
	mov.l	.L1383,r4
	mov.l	r7,@(r0,r1)
	mov.l	.L1384,r1
	jsr	@r1
	nop
	mov.l	.L1385,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1386,r1
	mov.l	.L1387,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1388,r4
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
.L1379:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1380:
	mov	r8,r9
	bra	.L1362
	add	#64,r9
.L1389:
	.align 2
.L1381:
	.long	text_int32
.L1382:
	.long	1073741823
.L1383:
	.long	.LC0
.L1384:
	.long	log_text
.L1385:
	.long	log_bytes
.L1386:
	.long	log_text_raw
.L1387:
	.long	.LC1
.L1388:
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
	bf/s	.L1414
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
	mov.l	.L1416,r3
	mov	r9,r5
	jsr	@r3
	mov.l	r2,@r15
	mov.l	@r15,r2
	mov	#0,r6
	mov	r9,r3
.L1395:
	mov.l	@r3+,r7
	cmp/str	r6,r7
	bf	.L1395
	add	#-4,r3
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1393
	mov.b	@r3+,r7
	tst	r7,r7
	bt	.L1393
	mov.b	@r3+,r7
	tst	r7,r7
	mov	#-1,r7
	subc	r7,r3
.L1393:
	sett
	mov	r3,r7
	subc	r9,r7
	tst	r7,r7
	bt/s	.L1415
	mov	r9,r5
	mov	r8,r9
	add	#64,r9
	mov	r7,r1
	.align 2
.L1398:
	mov.l	@(0,r9),r0
	dt	r1
	mov.b	@r5+,r3
	and	r2,r0
	mov.l	@(52,r8),r2
	mov.b	r3,@(r0,r2)
	mov	r0,r2
	bf/s	.L1398
	add	#1,r2
.L1397:
	mov.l	@r8,r0
	mov.l	.L1417,r1
	mov.l	@(12,r9),r5
	add	r1,r0
	mov.l	@(4,r8),r1
	shll2	r0
	mov.l	.L1418,r4
	mov.l	r7,@(r0,r1)
	mov.l	.L1419,r1
	jsr	@r1
	nop
	mov.l	.L1420,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1421,r1
	mov.l	.L1422,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1423,r4
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
.L1414:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#16,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1415:
	mov	r8,r9
	bra	.L1397
	add	#64,r9
.L1424:
	.align 2
.L1416:
	.long	text_hex32
.L1417:
	.long	1073741823
.L1418:
	.long	.LC0
.L1419:
	.long	log_text
.L1420:
	.long	log_bytes
.L1421:
	.long	log_text_raw
.L1422:
	.long	.LC1
.L1423:
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
	bf/s	.L1454
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
	mov.l	@(44,r10),r1
	tst	r1,r1
	bt/s	.L1428
	add	r0,r2
	mov.l	.L1455,r1
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
.L1431:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L1431
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1429
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1429
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L1429:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r11,r1
	bt/s	.L1436
	cmp/eq	r11,r1
	bt	.L1436
	sub	r1,r11
	mov.w	.L1456,r1
	cmp/hi	r1,r11
	bf	.L1437
	mov	r1,r11
.L1437:
	mov.l	.L1457,r12
	mov	#0,r8
	.align 2
.L1438:
	mov.l	@(44,r10),r1
	mov	r12,r4
	jsr	@r1
	add	#1,r8
	cmp/hi	r8,r11
	bt	.L1438
.L1436:
	mov.l	@(44,r10),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.w	.L1458,r1
	add	r9,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1428
	jsr	@r1
	nop
.L1428:
	mov.l	.L1459,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L1460,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1461,r1
	mov	#32,r5
	mov.l	.L1462,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1463,r4
	jsr	@r10
	nop
	mov.l	.L1464,r4
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
.L1454:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L1456:
	.short	1500
.L1458:
	.short	188
.L1465:
	.align 2
.L1455:
	.long	text_int32
.L1457:
	.long	.LC3
.L1459:
	.long	log_text
.L1460:
	.long	.LC0
.L1461:
	.long	log_bytes
.L1462:
	.long	log_text_raw
.L1463:
	.long	.LC1
.L1464:
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
	bf/s	.L1495
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
	mov.l	@(44,r10),r1
	tst	r1,r1
	bt/s	.L1469
	add	r0,r2
	mov.l	.L1496,r1
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
.L1472:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L1472
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1470
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1470
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L1470:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r11,r1
	bt/s	.L1477
	cmp/eq	r11,r1
	bt	.L1477
	sub	r1,r11
	mov.w	.L1497,r1
	cmp/hi	r1,r11
	bf	.L1478
	mov	r1,r11
.L1478:
	mov.l	.L1498,r12
	mov	#0,r8
	.align 2
.L1479:
	mov.l	@(44,r10),r1
	mov	r12,r4
	jsr	@r1
	add	#1,r8
	cmp/hi	r8,r11
	bt	.L1479
.L1477:
	mov.l	@(44,r10),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.w	.L1499,r1
	add	r9,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1469
	jsr	@r1
	nop
.L1469:
	mov.l	.L1500,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L1501,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1502,r1
	mov	#32,r5
	mov.l	.L1503,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1504,r4
	jsr	@r10
	nop
	mov.l	.L1505,r4
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
.L1495:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L1497:
	.short	1500
.L1499:
	.short	188
.L1506:
	.align 2
.L1496:
	.long	text_uint32
.L1498:
	.long	.LC3
.L1500:
	.long	log_text
.L1501:
	.long	.LC0
.L1502:
	.long	log_bytes
.L1503:
	.long	log_text_raw
.L1504:
	.long	.LC1
.L1505:
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
	bf/s	.L1536
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
	mov.l	@(44,r10),r1
	tst	r1,r1
	bt/s	.L1510
	add	r0,r2
	mov.l	.L1537,r1
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
.L1513:
	mov.l	@r1+,r2
	cmp/str	r3,r2
	bf	.L1513
	add	#-4,r1
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1511
	mov.b	@r1+,r2
	tst	r2,r2
	bt	.L1511
	mov.b	@r1+,r2
	tst	r2,r2
	mov	#-1,r2
	subc	r2,r1
.L1511:
	mov.l	@r15,r2
	sett
	subc	r2,r1
	cmp/hi	r11,r1
	bt/s	.L1518
	cmp/eq	r11,r1
	bt	.L1518
	sub	r1,r11
	mov.w	.L1538,r1
	cmp/hi	r1,r11
	bf	.L1519
	mov	r1,r11
.L1519:
	mov.l	.L1539,r12
	mov	#0,r8
	.align 2
.L1520:
	mov.l	@(44,r10),r1
	mov	r12,r4
	jsr	@r1
	add	#1,r8
	cmp/hi	r8,r11
	bt	.L1520
.L1518:
	mov.l	@(44,r10),r1
	mov	r15,r4
	jsr	@r1
	add	#4,r4
	mov.w	.L1540,r1
	add	r9,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1510
	jsr	@r1
	nop
.L1510:
	mov.l	.L1541,r1
	mov	r9,r8
	add	#64,r8
	mov.l	.L1542,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1543,r1
	mov	#32,r5
	mov.l	.L1544,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1545,r4
	jsr	@r10
	nop
	mov.l	.L1546,r4
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
.L1536:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L1538:
	.short	1500
.L1540:
	.short	188
.L1547:
	.align 2
.L1537:
	.long	text_hex32
.L1539:
	.long	.LC3
.L1541:
	.long	log_text
.L1542:
	.long	.LC0
.L1543:
	.long	log_bytes
.L1544:
	.long	log_text_raw
.L1545:
	.long	.LC1
.L1546:
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
	mov.w	.L1554,r2
	mov.l	@r4,r1
	cmp/gt	r2,r1
	bf/s	.L1549
	add	#-4,r15
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r8
	mov	#0,r1
	mov.b	r1,@r8
	add	#4,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 1
.L1549:
	mov.l	.L1555,r0
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
	mov.l	.L1556,r4
	mov.l	r1,@r8
	mov.l	.L1557,r1
	jsr	@r1
	nop
	mov.l	.L1558,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L1559,r1
	mov.l	.L1560,r4
	jsr	@r1
	mov.l	r1,@r15
	mov.l	@r15,r1
	mov.l	.L1561,r4
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
.L1554:
	.short	255
.L1562:
	.align 2
.L1555:
	.long	forth_stack_count
.L1556:
	.long	.LC0
.L1557:
	.long	log_text
.L1558:
	.long	log_bytes
.L1559:
	.long	log_text_raw
.L1560:
	.long	.LC1
.L1561:
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
	mov.l	@(44,r9),r1
	tst	r1,r1
	bt/s	.L1564
	add	#-12,r15
	mov.l	.L1575,r0
	mov.l	.L1576,r12
	jsr	@r0
	nop
	mov.l	@(44,r9),r1
	mov.l	.L1577,r4
	jsr	@r1
	mov	r0,r11
	mov	r15,r5
	jsr	@r12
	mov	r11,r4
	mov.l	@(44,r9),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(44,r9),r1
	mov.l	.L1578,r4
	jsr	@r1
	nop
	cmp/pl	r11
	bf	.L1565
	mov.l	.L1579,r13
	mov	#0,r8
	.align 2
.L1566:
	mov.l	@(4,r10),r1
	mov	r8,r0
	shll2	r0
	mov	r15,r5
	mov.l	@(r0,r1),r4
	jsr	@r12
	add	#1,r8
	mov.l	@(44,r9),r1
	jsr	@r1
	mov	r15,r4
	mov.l	@(44,r9),r1
	jsr	@r1
	mov	r13,r4
	cmp/eq	r8,r11
	bf	.L1566
.L1565:
	mov.w	.L1580,r1
	add	r10,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1564
	jsr	@r1
	nop
.L1564:
	mov.l	.L1581,r1
	mov	r10,r8
	add	#64,r8
	mov.l	.L1582,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L1583,r1
	mov	#32,r5
	mov.l	.L1584,r9
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1585,r4
	jsr	@r9
	nop
	mov.l	.L1586,r4
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
	.align 1
.L1580:
	.short	188
.L1587:
	.align 2
.L1575:
	.long	forth_stack_count
.L1576:
	.long	text_int32
.L1577:
	.long	.LC18
.L1578:
	.long	.LC19
.L1579:
	.long	.LC3
.L1581:
	.long	log_text
.L1582:
	.long	.LC0
.L1583:
	.long	log_bytes
.L1584:
	.long	log_text_raw
.L1585:
	.long	.LC1
.L1586:
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
	bf/s	.L1612
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
	bt/s	.L1613
	mov	r1,r12
.L1591:
	tst	r12,r12
	mov	r13,r14
	bt/s	.L1597
	add	#64,r14
	mov	r13,r14
	add	#64,r14
	mov.l	@(0,r14),r9
	add	#-8,r2
	mov.l	@r2,r8
	and	r9,r11
	mov.l	.L1616,r10
	mov	r11,r2
	add	r12,r2
	and	r8,r9
	cmp/hi	r1,r2
	mov	r9,r3
	bf/s	.L1593
	add	r12,r3
	.align 2
.L1614:
	cmp/hs	r3,r1
	mov	r1,r2
	mov	r12,r8
	bf/s	.L1598
	sub	r11,r2
.L1594:
	cmp/hi	r2,r8
	bf	.L1595
	mov	r2,r8
.L1595:
	mov.l	@(52,r13),r4
	mov	r8,r6
	sub	r8,r12
	mov	r4,r5
	add	r11,r4
	jsr	@r10
	add	r9,r5
	tst	r12,r12
	add	r8,r11
	bt/s	.L1597
	add	r9,r8
	mov.l	@(0,r14),r9
	mov.l	@(56,r13),r1
	and	r9,r11
	mov	r11,r2
	add	r12,r2
	and	r8,r9
	cmp/hi	r1,r2
	mov	r9,r3
	bt/s	.L1614
	add	r12,r3
.L1593:
	cmp/hs	r3,r1
	bt/s	.L1615
	mov	r12,r2
.L1598:
	mov	r1,r8
	bra	.L1594
	sub	r9,r8
	.align 1
.L1615:
	mov.l	@(52,r13),r4
	mov	r12,r6
	mov	r4,r5
	add	r11,r4
	jsr	@r10
	add	r9,r5
.L1597:
	mov.l	.L1617,r1
	mov.l	.L1618,r4
	jsr	@r1
	mov.l	@(12,r14),r5
	mov.l	.L1619,r1
	mov	#32,r5
	mov.l	.L1620,r8
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L1621,r4
	jsr	@r8
	nop
	mov.l	.L1622,r4
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
.L1613:
	bra	.L1591
	mov	r3,r12
	.align 1
.L1612:
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L1623:
	.align 2
.L1616:
	.long	memmove
.L1617:
	.long	log_text
.L1618:
	.long	.LC0
.L1619:
	.long	log_bytes
.L1620:
	.long	log_text_raw
.L1621:
	.long	.LC1
.L1622:
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
	mov.l	@(44,r9),r1
	tst	r1,r1
	bf/s	.L1680
	add	#-36,r15
	bra	.L1655
	mov	r4,r14
.L1680:
	mov.l	@r4,r0
	mov	r4,r14
	mov.l	.L1660,r2
	add	#64,r14
	mov.l	@(4,r4),r1
	add	r2,r0
	shll2	r0
	mov.l	@(r0,r1),r3
	tst	r3,r3
	bf/s	.L1679
	mov.l	r3,@(4,r15)
	bra	.L1627
	nop
.L1679:
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
.L1628:
	mov.l	@(44,r9),r1
	mov.l	.L1674,r4
	jsr	@r1
	mov	#0,r8
	mov.l	.L1664,r0
	mov	#6,r6
	mov	r10,r4
	mov	r15,r5
	jsr	@r0
	add	#16,r5
	mov.l	@(44,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#16,r4
	mov.l	@(44,r9),r1
	mov.l	.L1663,r4
	jsr	@r1
	nop
.L1641:
	mov.l	@(52,r13),r1
	mov	r10,r0
	mov	#2,r6
	mov	r15,r5
	mov.b	@(r0,r1),r12
	add	#16,r5
	mov.l	.L1664,r1
	jsr	@r1
	extu.b	r12,r4
	mov.l	@(44,r9),r1
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
	bt/s	.L1656
	mov.l	@(12,r15),r0
	cmp/eq	r11,r0
	bt	.L1657
	mov.l	@(44,r9),r1
	mov.l	.L1665,r4
	jsr	@r1
	add	#1,r11
	mov.l	@(4,r15),r0
	cmp/eq	r11,r0
	bt/s	.L1627
	add	#1,r10
	mov.l	@(0,r14),r1
	bra	.L1641
	and	r1,r10
	.align 1
.L1656:
	mov.l	@r15,r1
	mov	#0,r0
	mov.b	r0,@(8,r1)
.L1630:
	tst	r8,r8
	mov	r15,r2
	mov	#31,r7
	mov	r8,r1
	add	#24,r2
	bt/s	.L1658
	mov	#46,r0
.L1634:
	mov.b	@r2+,r3
	cmp/gt	r7,r3
	bt/s	.L1633
	mov	r2,r3
	add	#-16,r3
	mov.b	r0,@(15,r3)
.L1633:
	dt	r1
	bf	.L1634
	mov	r8,r0
	cmp/eq	#8,r0
	bt	.L1639
	neg	r8,r8
	add	#8,r8
	mov	#0,r12
	.align 2
.L1632:
	mov.l	@(44,r9),r1
	mov.l	.L1666,r4
	jsr	@r1
	add	#1,r12
	cmp/hs	r8,r12
	bf	.L1632
.L1639:
	mov.l	@(44,r9),r1
	mov.l	.L1667,r4
	jsr	@r1
	nop
	mov.l	@(44,r9),r1
	mov	r15,r4
	jsr	@r1
	add	#24,r4
	mov.l	@(8,r15),r0
	add	#1,r0
	cmp/eq	#20,r0
	bt/s	.L1636
	mov.l	r0,@(8,r15)
	mov.l	@(4,r15),r0
	add	#1,r11
	cmp/eq	r11,r0
	bt/s	.L1627
	add	#1,r10
	mov.l	@(0,r14),r1
	bra	.L1628
	and	r1,r10
	.align 1
.L1658:
	bra	.L1634
	mov	#1,r1
	.align 1
.L1657:
	mov	#24,r2
	mov	r8,r0
	mov	#0,r1
	add	r15,r2
	bra	.L1630
	mov.b	r1,@(r0,r2)
	.align 1
.L1636:
	mov.l	@(4,r15),r1
	add	#-1,r1
	cmp/eq	r11,r1
	bf	.L1659
.L1627:
	mov.w	.L1668,r1
	add	r13,r1
	mov.l	@(0,r1),r1
	tst	r1,r1
	bt	.L1625
	jsr	@r1
	nop
.L1625:
	mov.l	@r13,r1
	mov.l	@(12,r14),r5
	add	#-2,r1
	mov.l	.L1669,r4
	mov.l	r1,@r13
	mov.l	.L1670,r1
	mov.l	.L1671,r8
	jsr	@r1
	nop
	mov.l	.L1672,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r14),r4
	mov.l	.L1673,r4
	jsr	@r8
	nop
	mov.l	.L1674,r4
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
.L1655:
	bra	.L1625
	add	#64,r14
	.align 1
.L1659:
	mov.l	@(44,r9),r1
	mov.l	.L1675,r4
	jsr	@r1
	nop
	bra	.L1627
	nop
	.align 1
.L1668:
	.short	188
.L1676:
	.align 2
.L1660:
	.long	1073741823
.L1674:
	.long	.LC2
.L1664:
	.long	text_hex32_padded
.L1663:
	.long	.LC20
.L1665:
	.long	.LC3
.L1666:
	.long	.LC22
.L1667:
	.long	.LC21
.L1669:
	.long	.LC0
.L1670:
	.long	log_text
.L1671:
	.long	log_text_raw
.L1672:
	.long	log_bytes
.L1673:
	.long	.LC1
.L1675:
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
	bt/s	.L1688
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
	bf/s	.L1685
	add	#4,r5
	mov.l	@(4,r2),r5
	add	r2,r5
.L1685:
	mov.l	.L1689,r2
	mov.l	r5,@(12,r8)
	mov.l	.L1690,r4
	jsr	@r2
	mov.l	r1,@r15
	mov.l	.L1691,r2
	mov	#32,r5
	jsr	@r2
	mov.l	@(12,r8),r4
	mov.l	.L1692,r2
	mov.l	.L1693,r4
	jsr	@r2
	mov.l	r2,@(4,r15)
	mov.l	@(4,r15),r2
	mov.l	.L1694,r4
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
.L1688:
	mov	#10,r3
	mov	r4,r2
	add	#124,r2
	mov.l	r3,@(24,r2)
	add	#80,r1
	mov.b	r0,@(0,r1)
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L1695:
	.align 2
.L1689:
	.long	log_text
.L1690:
	.long	.LC0
.L1691:
	.long	log_bytes
.L1692:
	.long	log_text_raw
.L1693:
	.long	.LC1
.L1694:
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
	mov.w	.L1708,r1
	mov.l	@r4,r2
	cmp/gt	r1,r2
	bf/s	.L1697
	add	#-4,r15
	mov	#6,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
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
.L1697:
	mov.l	.L1709,r1
	mov	r4,r8
	add	#64,r8
	mov.l	@(60,r4),r2
	mov.l	@(12,r8),r10
	mov	#19,r4
	mov.l	r2,@r15
	mov.l	@(4,r10),r13
	mov	r10,r11
	mov.l	.L1710,r5
	jsr	@r1
	add	#8,r11
	mov.l	.L1711,r9
	mov.l	.L1712,r4
	jsr	@r9
	mov.l	@(12,r8),r5
	mov.l	@(12,r8),r5
	mov.l	.L1713,r4
	jsr	@r9
	add	#4,r5
	mov.l	.L1714,r4
	jsr	@r9
	mov	r13,r5
	mov.l	.L1717,r4
	jsr	@r9
	mov	r11,r5
	tst	r13,r13
	bt	.L1699
	mov	r13,r1
	add	#8,r1
	add	r1,r10
	mov	r11,r12
	.align 2
.L1700:
	mov.b	@r12,r5
	mov.l	.L1716,r4
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
	bf/s	.L1700
	mov.l	r1,@(60,r14)
	add	r13,r11
.L1699:
	mov.l	.L1717,r4
	jsr	@r9
	mov	r11,r5
	neg	r13,r0
	mov.l	.L1718,r4
	and	#3,r0
	add	r0,r11
	mov	r11,r1
	add	#-4,r1
	mov.l	r1,@(12,r8)
	jsr	@r9
	mov	#4,r5
	mov.l	.L1719,r4
	jsr	@r9
	mov	r11,r5
	mov.l	.L1720,r4
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
	mov.l	.L1721,r1
	jsr	@r1
	nop
	mov.l	.L1722,r4
	jsr	@r9
	mov.l	@(12,r8),r5
	mov.l	.L1723,r1
	mov	#32,r5
	mov.l	.L1724,r9
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L1725,r4
	jsr	@r9
	nop
	mov.l	.L1726,r4
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
.L1708:
	.short	254
.L1727:
	.align 2
.L1709:
	.long	log_push
.L1710:
	.long	.LC24
.L1711:
	.long	log_text
.L1712:
	.long	.LC5
.L1713:
	.long	.LC6
.L1714:
	.long	.LC7
.L1717:
	.long	.LC8
.L1716:
	.long	.LC9
.L1718:
	.long	.LC12
.L1719:
	.long	.LC13
.L1720:
	.long	.LC14
.L1721:
	.long	log_pop
.L1722:
	.long	.LC0
.L1723:
	.long	log_bytes
.L1724:
	.long	log_text_raw
.L1725:
	.long	.LC1
.L1726:
	.long	.LC2
	.size	prim_hidden_s_quote, .-prim_hidden_s_quote
	.section	.rodata.str1.4
	.align 2
.LC25:
	.string	"f: %p, f1: %p, f3: %p\n"
	.align 2
.LC26:
	.string	"%d\n"
	.text
	.align 1
	.align 2
	.global	jit_test2
	.type	jit_test2, @function
jit_test2:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	mov.l	r10,@-r15
	mov.l	.L1736,r10
	mov.l	.L1740,r3
	mov	r10,r1
	shlr16	r1
	shlr8	r1
	mov.l	.L1742,r2
	shll16	r1
	mov.l	r11,@-r15
	and	r10,r3
	mov.l	.L1739,r11
	shll8	r1
	mov.l	.L1740,r6
	mov	r1,r9
	or	r3,r9
	mov.l	.L1741,r3
	and	r10,r2
	or	r2,r9
	mov.l	.L1742,r7
	mov	r3,r2
	shlr16	r2
	sts.l	pr,@-r15
	shlr8	r2
	mov	r11,r0
	shll16	r2
	mov.l	.L1743,r8
	shlr16	r0
	add	#-64,r15
	and	r3,r6
	mov	r15,r5
	shlr8	r0
	shll8	r2
	mov.b	r0,@(12,r15)
	and	r3,r7
	mov	r11,r0
	or	r6,r2
	shlr16	r0
	extu.b	r3,r3
	mov.b	r0,@(13,r15)
	or	r7,r2
	mov	r11,r0
	shlr8	r0
	or	r3,r2
	mov.b	r0,@(14,r15)
	mov	r11,r0
	extu.b	r10,r1
	mov.l	r2,@(4,r15)
	mov	#0,r2
	mov.b	r0,@(15,r15)
	or	r1,r9
	mov.l	.L1744,r0
	mov	#0,r3
	mov.l	.L1745,r1
	mov	#64,r6
	mov.l	r2,@(16,r15)
	mov.l	r2,@(24,r15)
	mov.l	r2,@(32,r15)
	mov.l	r2,@(40,r15)
	mov.l	r2,@(48,r15)
	mov.l	r2,@(56,r15)
	mov.l	.L1746,r2
	mov.l	@r1,r4
	mov.l	r9,@(0,r15)
	mov.l	r3,@(20,r15)
	mov.l	r3,@(28,r15)
	mov.l	r3,@(36,r15)
	mov.l	r3,@(44,r15)
	mov.l	r3,@(52,r15)
	mov.l	r3,@(60,r15)
	jsr	@r0
	mov.l	r2,@(8,r15)
	tst	r9,r9
	mov.l	r0,@r8
	bt/s	.L1735
	mov	r0,r1
	mov.l	.L1747,r9
	.align 2
.L1730:
	mov	r1,r5
	mov.l	.L1748,r4
	mov	r11,r7
	jsr	@r9
	mov	r10,r6
	mov.l	@r8,r1
	mov.l	@r1,r0
	jsr	@r0
	nop
	mov.l	.L1749,r4
	jsr	@r9
	mov	r0,r5
	mov.l	@r8,r2
	mov	r2,r1
	mov.l	@(4,r2),r2
	add	#4,r1
	tst	r2,r2
	bf/s	.L1730
	mov.l	r1,@r8
.L1735:
	add	#64,r15
	lds.l	@r15+,pr
	mov.l	@r15+,r11
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
.L1750:
	.align 2
.L1736:
	.long	f1
.L1740:
	.long	16711680
.L1742:
	.long	65280
.L1739:
	.long	f3
.L1741:
	.long	f_exec
.L1743:
	.long	f
.L1744:
	.long	memcpy
.L1745:
	.long	heap
.L1746:
	.long	778282
.L1747:
	.long	printf
.L1748:
	.long	.LC25
.L1749:
	.long	.LC26
	.size	jit_test2, .-jit_test2
	.align 1
	.align 2
	.global	prim_hidden_jit
	.type	prim_hidden_jit, @function
prim_hidden_jit:
	mov	r4,r1
	add	#64,r1
	mov.l	@(12,r1),r1
	add	#4,r1
	jmp	@r1
	nop
	.size	prim_hidden_jit, .-prim_hidden_jit
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
.LC27:
	.string	"!"
	.align 2
.LC28:
	.string	"C!"
	.align 2
.LC29:
	.string	"W!"
	.align 2
.LC30:
	.string	"'"
	.align 2
.LC31:
	.string	"("
	.align 2
.LC32:
	.string	"*"
	.align 2
.LC33:
	.string	"*/"
	.align 2
.LC34:
	.string	"*/MOD"
	.align 2
.LC35:
	.string	"+"
	.align 2
.LC36:
	.string	"+LOOP"
	.align 2
.LC37:
	.string	","
	.align 2
.LC38:
	.string	"C,"
	.align 2
.LC39:
	.string	"W,"
	.align 2
.LC40:
	.string	"-"
	.align 2
.LC41:
	.string	"\\"
	.align 2
.LC42:
	.string	"."
	.align 2
.LC43:
	.string	"U."
	.align 2
.LC44:
	.string	"X."
	.align 2
.LC45:
	.string	".\""
	.align 2
.LC46:
	.string	"/"
	.align 2
.LC47:
	.string	"/MOD"
	.align 2
.LC48:
	.string	":"
	.align 2
.LC49:
	.string	";"
	.align 2
.LC50:
	.string	"="
	.align 2
.LC51:
	.string	">"
	.align 2
.LC52:
	.string	">NUMBER"
	.align 2
.LC53:
	.string	">NUM"
	.align 2
.LC54:
	.string	"NUMBER>"
	.align 2
.LC55:
	.string	"NUM>"
	.align 2
.LC56:
	.string	">HEX"
	.align 2
.LC57:
	.string	"HEX>"
	.align 2
.LC58:
	.string	"?DUP"
	.align 2
.LC59:
	.string	"@"
	.align 2
.LC60:
	.string	"C@"
	.align 2
.LC61:
	.string	"W@"
	.align 2
.LC62:
	.string	"QUIT"
	.align 2
.LC63:
	.string	"ABS"
	.align 2
.LC64:
	.string	"ACCEPT"
	.align 2
.LC65:
	.string	"ALIGN"
	.align 2
.LC66:
	.string	"ALIGNED"
	.align 2
.LC67:
	.string	"ALLOT"
	.align 2
.LC68:
	.string	"AND"
	.align 2
.LC69:
	.string	"BEGIN"
	.align 2
.LC70:
	.string	"BL"
	.align 2
.LC71:
	.string	"BOUNDS"
	.align 2
.LC72:
	.string	"CELLS"
	.align 2
.LC73:
	.string	"CHAR"
	.align 2
.LC74:
	.string	"CONSTANT"
	.align 2
.LC75:
	.string	"CONST"
	.align 2
.LC76:
	.string	"CR"
	.align 2
.LC77:
	.string	"CREATE"
	.align 2
.LC78:
	.string	"DEPTH"
	.align 2
.LC79:
	.string	"DO"
	.align 2
.LC80:
	.string	"DROP"
	.align 2
.LC81:
	.string	"2DROP"
	.align 2
.LC82:
	.string	"DUP"
	.align 2
.LC83:
	.string	"2DUP"
	.align 2
.LC84:
	.string	"ELSE"
	.align 2
.LC85:
	.string	"EMIT"
	.align 2
.LC86:
	.string	"ERASE"
	.align 2
.LC87:
	.string	"EXECUTE"
	.align 2
.LC88:
	.string	"EXEC"
	.align 2
.LC89:
	.string	"EXIT"
	.align 2
.LC90:
	.string	"FILL"
	.align 2
.LC91:
	.string	"HERE"
	.align 2
.LC92:
	.string	"I"
	.align 2
.LC93:
	.string	"IF"
	.align 2
.LC94:
	.string	"INVERT"
	.align 2
.LC95:
	.string	"J"
	.align 2
.LC96:
	.string	"KEY"
	.align 2
.LC97:
	.string	"LEAVE"
	.align 2
.LC98:
	.string	"LITERAL"
	.align 2
.LC99:
	.string	"LIT"
	.align 2
.LC100:
	.string	"LOOP"
	.align 2
.LC101:
	.string	"LSHIFT"
	.align 2
.LC102:
	.string	"MAX"
	.align 2
.LC103:
	.string	"MIN"
	.align 2
.LC104:
	.string	"MOD"
	.align 2
.LC105:
	.string	"MOVE"
	.align 2
.LC106:
	.string	"NEGATE"
	.align 2
.LC107:
	.string	"OR"
	.align 2
.LC108:
	.string	"OVER"
	.align 2
.LC109:
	.string	"2OVER"
	.align 2
.LC110:
	.string	"PAGE"
	.align 2
.LC111:
	.string	"REPEAT"
	.align 2
.LC112:
	.string	"ROT"
	.align 2
.LC113:
	.string	"-ROT"
	.align 2
.LC114:
	.string	"RSHIFT"
	.align 2
.LC115:
	.string	"S\""
	.align 2
.LC116:
	.string	"SPACE"
	.align 2
.LC117:
	.string	"SPACES"
	.align 2
.LC118:
	.string	"SWAP"
	.align 2
.LC119:
	.string	"2SWAP"
	.align 2
.LC120:
	.string	"THEN"
	.align 2
.LC121:
	.string	"TYPE"
	.align 2
.LC122:
	.string	"U<"
	.align 2
.LC123:
	.string	"U>"
	.align 2
.LC124:
	.string	"UNTIL"
	.align 2
.LC125:
	.string	"VARIABLE"
	.align 2
.LC126:
	.string	"VAR"
	.align 2
.LC127:
	.string	"WHILE"
	.align 2
.LC128:
	.string	"XOR"
	.align 2
.LC129:
	.string	"["
	.align 2
.LC130:
	.string	"]"
	.align 2
.LC131:
	.string	"[']"
	.align 2
.LC132:
	.string	"[CHAR]"
	.align 2
.LC133:
	.string	".R"
	.align 2
.LC134:
	.string	"U.R"
	.align 2
.LC135:
	.string	"X.R"
	.align 2
.LC136:
	.string	"<>"
	.align 2
.LC137:
	.string	"AGAIN"
	.align 2
.LC138:
	.string	"FALSE"
	.align 2
.LC139:
	.string	"NIP"
	.align 2
.LC140:
	.string	"S\\\""
	.align 2
.LC141:
	.string	"TRUE"
	.align 2
.LC142:
	.string	"TUCK"
	.align 2
.LC143:
	.string	"UNUSED"
	.align 2
.LC144:
	.string	"WITHIN"
	.align 2
.LC145:
	.string	".S"
	.align 2
.LC146:
	.string	"?"
	.align 2
.LC147:
	.string	"DUMP"
	.align 2
.LC148:
	.string	"WORDS"
	.align 2
.LC149:
	.string	"WORDSIZE"
	.align 2
.LC150:
	.string	"BYE"
	.align 2
.LC151:
	.string	"{"
	.align 2
.LC152:
	.string	"0{"
	.align 2
.LC153:
	.string	"TO"
	.align 2
.LC154:
	.string	"RESET"
	.align 2
.LC155:
	.string	"WALIGN"
	.align 2
.LC156:
	.string	"WALIGNED"
	.align 2
.LC157:
	.string	"PRINTABLE"
	.align 2
.LC158:
	.string	"CXT"
	.align 2
.LC159:
	.string	"WXT"
	.align 2
.LC160:
	.string	"PRIMITIVES"
	.align 2
.LC161:
	.string	"SECONDARIES"
	.align 2
.LC162:
	.string	"UNDEFINED"
	.align 2
.LC163:
	.string	"PERF"
	.align 2
.LC164:
	.string	"SIZE"
	.align 2
.LC165:
	.string	"RESIZE"
	.align 2
.LC166:
	.string	""
	.section	.rodata
	.align 2
	.type	forth_primitives, @object
	.size	forth_primitives, 4832
forth_primitives:
	.long	.LC27
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC28
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC29
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_store
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC30
	.byte	1
	.zero	3
	.long	39
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC31
	.byte	1
	.zero	3
	.long	28
	.long	28
	.long	0
	.byte	1
	.zero	11
	.long	.LC32
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_star
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC33
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_star_slash
	.byte	0
	.zero	3
	.long	3
	.long	1
	.long	.LC34
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_star_slash_mod
	.byte	0
	.zero	3
	.long	3
	.long	2
	.long	.LC35
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_plus
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC36
	.byte	5
	.zero	3
	.long	1
	.long	29
	.long	0
	.byte	1
	.zero	11
	.long	.LC37
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC38
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC39
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_comma
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC40
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_minus
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC41
	.byte	1
	.zero	3
	.long	10
	.long	10
	.long	0
	.byte	1
	.zero	11
	.long	.LC42
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_dot
	.byte	1
	.zero	11
	.long	.LC43
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_dot
	.byte	1
	.zero	11
	.long	.LC44
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_x_dot
	.byte	1
	.zero	11
	.long	.LC45
	.byte	2
	.zero	3
	.long	14
	.long	14
	.long	0
	.byte	1
	.zero	11
	.long	.LC46
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_slash
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC47
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_slash_mod
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC48
	.byte	1
	.zero	3
	.long	9
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC49
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
	.long	.LC50
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_equals
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC51
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_greater_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC52
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_to_number
	.byte	1
	.zero	11
	.long	.LC53
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_to_number
	.byte	1
	.zero	11
	.long	.LC54
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_number_to
	.byte	1
	.zero	11
	.long	.LC55
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_number_to
	.byte	1
	.zero	11
	.long	.LC56
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_to_hex
	.byte	1
	.zero	11
	.long	.LC57
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_hex_to
	.byte	1
	.zero	11
	.long	.LC58
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_question_dupe
	.byte	1
	.zero	11
	.long	.LC59
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC60
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC61
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_w_fetch
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC62
	.byte	4
	.zero	3
	.long	1
	.long	0
	.long	prim_quit
	.byte	1
	.zero	11
	.long	.LC63
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_abs
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC64
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_accept
	.byte	1
	.zero	11
	.long	.LC65
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_align
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	.LC66
	.byte	7
	.zero	3
	.long	0
	.long	0
	.long	prim_aligned
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC67
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_allot
	.byte	1
	.zero	11
	.long	.LC68
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_and
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC69
	.byte	5
	.zero	3
	.long	1
	.long	4
	.long	0
	.byte	1
	.zero	11
	.long	.LC70
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_b_l
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC71
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_bounds
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC72
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_cells
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC73
	.byte	4
	.zero	3
	.long	8
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC74
	.byte	8
	.zero	3
	.long	11
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC75
	.byte	5
	.zero	3
	.long	11
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC76
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_c_r
	.byte	1
	.zero	11
	.long	.LC77
	.byte	6
	.zero	3
	.long	12
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC78
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_depth
	.byte	1
	.zero	11
	.long	.LC79
	.byte	2
	.zero	3
	.long	1
	.long	13
	.long	0
	.byte	1
	.zero	11
	.long	.LC80
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_drop
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC81
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_drop
	.byte	0
	.zero	3
	.long	2
	.long	0
	.long	.LC82
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_dupe
	.byte	0
	.zero	3
	.long	1
	.long	2
	.long	.LC83
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_two_dupe
	.byte	0
	.zero	3
	.long	2
	.long	4
	.long	.LC84
	.byte	4
	.zero	3
	.long	1
	.long	15
	.long	0
	.byte	1
	.zero	11
	.long	.LC85
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_emit
	.byte	1
	.zero	11
	.long	.LC86
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_erase
	.byte	1
	.zero	11
	.long	.LC87
	.byte	7
	.zero	3
	.long	19
	.long	0
	.long	prim_execute
	.byte	1
	.zero	11
	.long	.LC88
	.byte	4
	.zero	3
	.long	19
	.long	0
	.long	prim_execute
	.byte	1
	.zero	11
	.long	.LC89
	.byte	4
	.zero	3
	.long	1
	.long	0
	.long	prim_hidden_done
	.byte	1
	.zero	11
	.long	.LC90
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_fill
	.byte	1
	.zero	11
	.long	.LC91
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_here
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC92
	.byte	1
	.zero	3
	.long	1
	.long	0
	.long	prim_i
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC93
	.byte	2
	.zero	3
	.long	1
	.long	20
	.long	0
	.byte	1
	.zero	11
	.long	.LC94
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_invert
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC95
	.byte	1
	.zero	3
	.long	1
	.long	0
	.long	prim_j
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC96
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_key
	.byte	1
	.zero	11
	.long	.LC97
	.byte	5
	.zero	3
	.long	1
	.long	21
	.long	0
	.byte	1
	.zero	11
	.long	.LC98
	.byte	7
	.zero	3
	.long	1
	.long	23
	.long	0
	.byte	1
	.zero	11
	.long	.LC99
	.byte	3
	.zero	3
	.long	1
	.long	23
	.long	0
	.byte	1
	.zero	11
	.long	.LC100
	.byte	4
	.zero	3
	.long	1
	.long	26
	.long	0
	.byte	1
	.zero	11
	.long	.LC101
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_l_shift
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC102
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_max
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC103
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_min
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC104
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_mod
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC105
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_move
	.byte	1
	.zero	11
	.long	.LC106
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_negate
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC107
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_or
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC108
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_over
	.byte	0
	.zero	3
	.long	2
	.long	3
	.long	.LC109
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_over
	.byte	0
	.zero	3
	.long	4
	.long	6
	.long	.LC110
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_page
	.byte	1
	.zero	11
	.long	.LC111
	.byte	6
	.zero	3
	.long	1
	.long	31
	.long	0
	.byte	1
	.zero	11
	.long	.LC112
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_rote
	.byte	0
	.zero	3
	.long	3
	.long	3
	.long	.LC113
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_minus_rote
	.byte	0
	.zero	3
	.long	3
	.long	3
	.long	.LC114
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_r_shift
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC115
	.byte	2
	.zero	3
	.long	34
	.long	34
	.long	0
	.byte	1
	.zero	11
	.long	.LC116
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_space
	.byte	1
	.zero	11
	.long	.LC117
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_spaces
	.byte	1
	.zero	11
	.long	.LC118
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_swap
	.byte	0
	.zero	3
	.long	2
	.long	2
	.long	.LC119
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_two_swap
	.byte	0
	.zero	3
	.long	4
	.long	4
	.long	.LC120
	.byte	4
	.zero	3
	.long	1
	.long	38
	.long	0
	.byte	1
	.zero	11
	.long	.LC121
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_type
	.byte	1
	.zero	11
	.long	.LC122
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_less_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC123
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_u_greater_than
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC124
	.byte	5
	.zero	3
	.long	1
	.long	42
	.long	0
	.byte	1
	.zero	11
	.long	.LC125
	.byte	8
	.zero	3
	.long	43
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC126
	.byte	3
	.zero	3
	.long	43
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC127
	.byte	5
	.zero	3
	.long	1
	.long	44
	.long	0
	.byte	1
	.zero	11
	.long	.LC128
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_x_or
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC129
	.byte	1
	.zero	3
	.long	1
	.long	22
	.long	0
	.byte	1
	.zero	11
	.long	.LC130
	.byte	1
	.zero	3
	.long	33
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC131
	.byte	3
	.zero	3
	.long	1
	.long	6
	.long	0
	.byte	1
	.zero	11
	.long	.LC132
	.byte	6
	.zero	3
	.long	1
	.long	5
	.long	0
	.byte	1
	.zero	11
	.long	.LC133
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_dot_r
	.byte	1
	.zero	11
	.long	.LC134
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_u_dot_r
	.byte	1
	.zero	11
	.long	.LC135
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_x_dot_r
	.byte	1
	.zero	11
	.long	.LC136
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_not_equals
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC137
	.byte	5
	.zero	3
	.long	1
	.long	3
	.long	0
	.byte	1
	.zero	11
	.long	.LC138
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_false
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC139
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_nip
	.byte	0
	.zero	3
	.long	2
	.long	1
	.long	.LC140
	.byte	3
	.zero	3
	.long	35
	.long	35
	.long	0
	.byte	1
	.zero	11
	.long	.LC141
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_true
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC142
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_tuck
	.byte	0
	.zero	3
	.long	2
	.long	3
	.long	.LC143
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_unused
	.byte	1
	.zero	11
	.long	.LC144
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_within
	.byte	0
	.zero	3
	.long	3
	.long	1
	.long	.LC145
	.byte	2
	.zero	3
	.long	0
	.long	0
	.long	prim_dot_s
	.byte	1
	.zero	11
	.long	.LC146
	.byte	1
	.zero	3
	.long	0
	.long	0
	.long	prim_question
	.byte	1
	.zero	11
	.long	.LC147
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_dump
	.byte	1
	.zero	11
	.long	.LC148
	.byte	5
	.zero	3
	.long	45
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC149
	.byte	8
	.zero	3
	.long	46
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC150
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_bye
	.byte	1
	.zero	11
	.long	.LC151
	.byte	1
	.zero	3
	.long	1
	.long	24
	.long	0
	.byte	1
	.zero	11
	.long	.LC152
	.byte	2
	.zero	3
	.long	1
	.long	25
	.long	0
	.byte	1
	.zero	11
	.long	.LC153
	.byte	2
	.zero	3
	.long	1
	.long	40
	.long	0
	.byte	0
	.zero	3
	.long	1
	.long	0
	.long	.LC154
	.byte	5
	.zero	3
	.long	0
	.long	0
	.long	prim_reset
	.byte	1
	.zero	11
	.long	.LC155
	.byte	6
	.zero	3
	.long	0
	.long	0
	.long	prim_walign
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	.LC156
	.byte	8
	.zero	3
	.long	0
	.long	0
	.long	prim_waligned
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC157
	.byte	9
	.zero	3
	.long	0
	.long	0
	.long	prim_printable
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC158
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_cxt
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC159
	.byte	3
	.zero	3
	.long	0
	.long	0
	.long	prim_wxt
	.byte	0
	.zero	3
	.long	1
	.long	1
	.long	.LC160
	.byte	10
	.zero	3
	.long	30
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC161
	.byte	11
	.zero	3
	.long	36
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC162
	.byte	9
	.zero	3
	.long	41
	.long	2
	.long	0
	.byte	1
	.zero	11
	.long	.LC163
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_perf
	.byte	1
	.zero	11
	.long	.LC164
	.byte	4
	.zero	3
	.long	0
	.long	0
	.long	prim_size
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC165
	.byte	6
	.zero	3
	.long	32
	.long	2
	.long	0
	.zero	12
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_do
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_done
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_dot_quote
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_if
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_jump
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_leave
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_loop
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_plus_loop
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_push
	.byte	0
	.zero	3
	.long	0
	.long	1
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_s_quote
	.byte	1
	.zero	11
	.long	.LC166
	.byte	0
	.zero	3
	.long	0
	.long	0
	.long	prim_hidden_secondary
	.byte	1
	.zero	11
	.global	f
	.section	.bss
	.align 2
	.type	f, @object
	.size	f, 4
f:
	.zero	4
	.global	__moddi3
	.global	__divdi3
	.ident	"GCC: (GNU) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
