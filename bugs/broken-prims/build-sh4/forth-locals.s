	.file	"forth-locals.c"
	.text
	.text
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
	.global	prim_local_fetch0
	.type	prim_local_fetch0, @function
prim_local_fetch0:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@r1,r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L4,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L5,r1
	mov.l	.L6,r4
	jsr	@r1
	nop
	mov.l	.L7,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L8,r4
	jsr	@r10
	nop
	mov.l	.L9,r4
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
.L10:
	.align 2
.L4:
	.long	log_text_raw
.L5:
	.long	log_text
.L6:
	.long	.LC0
.L7:
	.long	log_bytes
.L8:
	.long	.LC1
.L9:
	.long	.LC2
	.size	prim_local_fetch0, .-prim_local_fetch0
	.align 1
	.align 2
	.global	prim_local_fetch1
	.type	prim_local_fetch1, @function
prim_local_fetch1:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(4,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L13,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L14,r1
	mov.l	.L15,r4
	jsr	@r1
	nop
	mov.l	.L16,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L17,r4
	jsr	@r10
	nop
	mov.l	.L18,r4
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
.L19:
	.align 2
.L13:
	.long	log_text_raw
.L14:
	.long	log_text
.L15:
	.long	.LC0
.L16:
	.long	log_bytes
.L17:
	.long	.LC1
.L18:
	.long	.LC2
	.size	prim_local_fetch1, .-prim_local_fetch1
	.align 1
	.align 2
	.global	prim_local_fetch2
	.type	prim_local_fetch2, @function
prim_local_fetch2:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(8,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L22,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L23,r1
	mov.l	.L24,r4
	jsr	@r1
	nop
	mov.l	.L25,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L26,r4
	jsr	@r10
	nop
	mov.l	.L27,r4
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
.L28:
	.align 2
.L22:
	.long	log_text_raw
.L23:
	.long	log_text
.L24:
	.long	.LC0
.L25:
	.long	log_bytes
.L26:
	.long	.LC1
.L27:
	.long	.LC2
	.size	prim_local_fetch2, .-prim_local_fetch2
	.align 1
	.align 2
	.global	prim_local_fetch3
	.type	prim_local_fetch3, @function
prim_local_fetch3:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(12,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L31,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L32,r1
	mov.l	.L33,r4
	jsr	@r1
	nop
	mov.l	.L34,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L35,r4
	jsr	@r10
	nop
	mov.l	.L36,r4
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
.L37:
	.align 2
.L31:
	.long	log_text_raw
.L32:
	.long	log_text
.L33:
	.long	.LC0
.L34:
	.long	log_bytes
.L35:
	.long	.LC1
.L36:
	.long	.LC2
	.size	prim_local_fetch3, .-prim_local_fetch3
	.align 1
	.align 2
	.global	prim_local_fetch4
	.type	prim_local_fetch4, @function
prim_local_fetch4:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(16,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L40,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L41,r1
	mov.l	.L42,r4
	jsr	@r1
	nop
	mov.l	.L43,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L44,r4
	jsr	@r10
	nop
	mov.l	.L45,r4
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
.L46:
	.align 2
.L40:
	.long	log_text_raw
.L41:
	.long	log_text
.L42:
	.long	.LC0
.L43:
	.long	log_bytes
.L44:
	.long	.LC1
.L45:
	.long	.LC2
	.size	prim_local_fetch4, .-prim_local_fetch4
	.align 1
	.align 2
	.global	prim_local_fetch5
	.type	prim_local_fetch5, @function
prim_local_fetch5:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(20,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L49,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L50,r1
	mov.l	.L51,r4
	jsr	@r1
	nop
	mov.l	.L52,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L53,r4
	jsr	@r10
	nop
	mov.l	.L54,r4
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
.L55:
	.align 2
.L49:
	.long	log_text_raw
.L50:
	.long	log_text
.L51:
	.long	.LC0
.L52:
	.long	log_bytes
.L53:
	.long	.LC1
.L54:
	.long	.LC2
	.size	prim_local_fetch5, .-prim_local_fetch5
	.align 1
	.align 2
	.global	prim_local_fetch6
	.type	prim_local_fetch6, @function
prim_local_fetch6:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(24,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L58,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L59,r1
	mov.l	.L60,r4
	jsr	@r1
	nop
	mov.l	.L61,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L62,r4
	jsr	@r10
	nop
	mov.l	.L63,r4
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
.L64:
	.align 2
.L58:
	.long	log_text_raw
.L59:
	.long	log_text
.L60:
	.long	.LC0
.L61:
	.long	log_bytes
.L62:
	.long	.LC1
.L63:
	.long	.LC2
	.size	prim_local_fetch6, .-prim_local_fetch6
	.align 1
	.align 2
	.global	prim_local_fetch7
	.type	prim_local_fetch7, @function
prim_local_fetch7:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(28,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L67,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L68,r1
	mov.l	.L69,r4
	jsr	@r1
	nop
	mov.l	.L70,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L71,r4
	jsr	@r10
	nop
	mov.l	.L72,r4
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
.L73:
	.align 2
.L67:
	.long	log_text_raw
.L68:
	.long	log_text
.L69:
	.long	.LC0
.L70:
	.long	log_bytes
.L71:
	.long	.LC1
.L72:
	.long	.LC2
	.size	prim_local_fetch7, .-prim_local_fetch7
	.align 1
	.align 2
	.global	prim_local_fetch8
	.type	prim_local_fetch8, @function
prim_local_fetch8:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(32,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L76,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L77,r1
	mov.l	.L78,r4
	jsr	@r1
	nop
	mov.l	.L79,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L80,r4
	jsr	@r10
	nop
	mov.l	.L81,r4
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
.L82:
	.align 2
.L76:
	.long	log_text_raw
.L77:
	.long	log_text
.L78:
	.long	.LC0
.L79:
	.long	log_bytes
.L80:
	.long	.LC1
.L81:
	.long	.LC2
	.size	prim_local_fetch8, .-prim_local_fetch8
	.align 1
	.align 2
	.global	prim_local_fetch9
	.type	prim_local_fetch9, @function
prim_local_fetch9:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(36,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L85,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L86,r1
	mov.l	.L87,r4
	jsr	@r1
	nop
	mov.l	.L88,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L89,r4
	jsr	@r10
	nop
	mov.l	.L90,r4
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
.L91:
	.align 2
.L85:
	.long	log_text_raw
.L86:
	.long	log_text
.L87:
	.long	.LC0
.L88:
	.long	log_bytes
.L89:
	.long	.LC1
.L90:
	.long	.LC2
	.size	prim_local_fetch9, .-prim_local_fetch9
	.align 1
	.align 2
	.global	prim_local_fetch10
	.type	prim_local_fetch10, @function
prim_local_fetch10:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(40,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L94,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L95,r1
	mov.l	.L96,r4
	jsr	@r1
	nop
	mov.l	.L97,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L98,r4
	jsr	@r10
	nop
	mov.l	.L99,r4
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
.L100:
	.align 2
.L94:
	.long	log_text_raw
.L95:
	.long	log_text
.L96:
	.long	.LC0
.L97:
	.long	log_bytes
.L98:
	.long	.LC1
.L99:
	.long	.LC2
	.size	prim_local_fetch10, .-prim_local_fetch10
	.align 1
	.align 2
	.global	prim_local_fetch11
	.type	prim_local_fetch11, @function
prim_local_fetch11:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(44,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L103,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L104,r1
	mov.l	.L105,r4
	jsr	@r1
	nop
	mov.l	.L106,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L107,r4
	jsr	@r10
	nop
	mov.l	.L108,r4
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
.L109:
	.align 2
.L103:
	.long	log_text_raw
.L104:
	.long	log_text
.L105:
	.long	.LC0
.L106:
	.long	log_bytes
.L107:
	.long	.LC1
.L108:
	.long	.LC2
	.size	prim_local_fetch11, .-prim_local_fetch11
	.align 1
	.align 2
	.global	prim_local_fetch12
	.type	prim_local_fetch12, @function
prim_local_fetch12:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(48,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L112,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L113,r1
	mov.l	.L114,r4
	jsr	@r1
	nop
	mov.l	.L115,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L116,r4
	jsr	@r10
	nop
	mov.l	.L117,r4
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
.L118:
	.align 2
.L112:
	.long	log_text_raw
.L113:
	.long	log_text
.L114:
	.long	.LC0
.L115:
	.long	log_bytes
.L116:
	.long	.LC1
.L117:
	.long	.LC2
	.size	prim_local_fetch12, .-prim_local_fetch12
	.align 1
	.align 2
	.global	prim_local_fetch13
	.type	prim_local_fetch13, @function
prim_local_fetch13:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(52,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L121,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L122,r1
	mov.l	.L123,r4
	jsr	@r1
	nop
	mov.l	.L124,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L125,r4
	jsr	@r10
	nop
	mov.l	.L126,r4
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
.L127:
	.align 2
.L121:
	.long	log_text_raw
.L122:
	.long	log_text
.L123:
	.long	.LC0
.L124:
	.long	log_bytes
.L125:
	.long	.LC1
.L126:
	.long	.LC2
	.size	prim_local_fetch13, .-prim_local_fetch13
	.align 1
	.align 2
	.global	prim_local_fetch14
	.type	prim_local_fetch14, @function
prim_local_fetch14:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(56,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L130,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L131,r1
	mov.l	.L132,r4
	jsr	@r1
	nop
	mov.l	.L133,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L134,r4
	jsr	@r10
	nop
	mov.l	.L135,r4
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
.L136:
	.align 2
.L130:
	.long	log_text_raw
.L131:
	.long	log_text
.L132:
	.long	.LC0
.L133:
	.long	log_bytes
.L134:
	.long	.LC1
.L135:
	.long	.LC2
	.size	prim_local_fetch14, .-prim_local_fetch14
	.align 1
	.align 2
	.global	prim_local_fetch15
	.type	prim_local_fetch15, @function
prim_local_fetch15:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(60,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	@(12,r9),r5
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	mov.l	.L139,r10
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L140,r1
	mov.l	.L141,r4
	jsr	@r1
	nop
	mov.l	.L142,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L143,r4
	jsr	@r10
	nop
	mov.l	.L144,r4
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
.L145:
	.align 2
.L139:
	.long	log_text_raw
.L140:
	.long	log_text
.L141:
	.long	.LC0
.L142:
	.long	log_bytes
.L143:
	.long	.LC1
.L144:
	.long	.LC2
	.size	prim_local_fetch15, .-prim_local_fetch15
	.align 1
	.align 2
	.global	prim_local_fetch16
	.type	prim_local_fetch16, @function
prim_local_fetch16:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(0,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L148,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L149,r1
	mov.l	.L150,r4
	jsr	@r1
	nop
	mov.l	.L151,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L152,r4
	jsr	@r10
	nop
	mov.l	.L153,r4
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
.L154:
	.align 2
.L148:
	.long	log_text_raw
.L149:
	.long	log_text
.L150:
	.long	.LC0
.L151:
	.long	log_bytes
.L152:
	.long	.LC1
.L153:
	.long	.LC2
	.size	prim_local_fetch16, .-prim_local_fetch16
	.align 1
	.align 2
	.global	prim_local_fetch17
	.type	prim_local_fetch17, @function
prim_local_fetch17:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(4,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L157,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L158,r1
	mov.l	.L159,r4
	jsr	@r1
	nop
	mov.l	.L160,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L161,r4
	jsr	@r10
	nop
	mov.l	.L162,r4
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
.L163:
	.align 2
.L157:
	.long	log_text_raw
.L158:
	.long	log_text
.L159:
	.long	.LC0
.L160:
	.long	log_bytes
.L161:
	.long	.LC1
.L162:
	.long	.LC2
	.size	prim_local_fetch17, .-prim_local_fetch17
	.align 1
	.align 2
	.global	prim_local_fetch18
	.type	prim_local_fetch18, @function
prim_local_fetch18:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(8,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L166,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L167,r1
	mov.l	.L168,r4
	jsr	@r1
	nop
	mov.l	.L169,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L170,r4
	jsr	@r10
	nop
	mov.l	.L171,r4
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
.L172:
	.align 2
.L166:
	.long	log_text_raw
.L167:
	.long	log_text
.L168:
	.long	.LC0
.L169:
	.long	log_bytes
.L170:
	.long	.LC1
.L171:
	.long	.LC2
	.size	prim_local_fetch18, .-prim_local_fetch18
	.align 1
	.align 2
	.global	prim_local_fetch19
	.type	prim_local_fetch19, @function
prim_local_fetch19:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(12,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L175,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L176,r1
	mov.l	.L177,r4
	jsr	@r1
	nop
	mov.l	.L178,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L179,r4
	jsr	@r10
	nop
	mov.l	.L180,r4
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
.L181:
	.align 2
.L175:
	.long	log_text_raw
.L176:
	.long	log_text
.L177:
	.long	.LC0
.L178:
	.long	log_bytes
.L179:
	.long	.LC1
.L180:
	.long	.LC2
	.size	prim_local_fetch19, .-prim_local_fetch19
	.align 1
	.align 2
	.global	prim_local_fetch20
	.type	prim_local_fetch20, @function
prim_local_fetch20:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(16,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L184,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L185,r1
	mov.l	.L186,r4
	jsr	@r1
	nop
	mov.l	.L187,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L188,r4
	jsr	@r10
	nop
	mov.l	.L189,r4
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
.L190:
	.align 2
.L184:
	.long	log_text_raw
.L185:
	.long	log_text
.L186:
	.long	.LC0
.L187:
	.long	log_bytes
.L188:
	.long	.LC1
.L189:
	.long	.LC2
	.size	prim_local_fetch20, .-prim_local_fetch20
	.align 1
	.align 2
	.global	prim_local_fetch21
	.type	prim_local_fetch21, @function
prim_local_fetch21:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(20,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L193,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L194,r1
	mov.l	.L195,r4
	jsr	@r1
	nop
	mov.l	.L196,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L197,r4
	jsr	@r10
	nop
	mov.l	.L198,r4
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
.L199:
	.align 2
.L193:
	.long	log_text_raw
.L194:
	.long	log_text
.L195:
	.long	.LC0
.L196:
	.long	log_bytes
.L197:
	.long	.LC1
.L198:
	.long	.LC2
	.size	prim_local_fetch21, .-prim_local_fetch21
	.align 1
	.align 2
	.global	prim_local_fetch22
	.type	prim_local_fetch22, @function
prim_local_fetch22:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(24,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L202,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L203,r1
	mov.l	.L204,r4
	jsr	@r1
	nop
	mov.l	.L205,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L206,r4
	jsr	@r10
	nop
	mov.l	.L207,r4
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
.L208:
	.align 2
.L202:
	.long	log_text_raw
.L203:
	.long	log_text
.L204:
	.long	.LC0
.L205:
	.long	log_bytes
.L206:
	.long	.LC1
.L207:
	.long	.LC2
	.size	prim_local_fetch22, .-prim_local_fetch22
	.align 1
	.align 2
	.global	prim_local_fetch23
	.type	prim_local_fetch23, @function
prim_local_fetch23:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(28,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L211,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L212,r1
	mov.l	.L213,r4
	jsr	@r1
	nop
	mov.l	.L214,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L215,r4
	jsr	@r10
	nop
	mov.l	.L216,r4
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
.L217:
	.align 2
.L211:
	.long	log_text_raw
.L212:
	.long	log_text
.L213:
	.long	.LC0
.L214:
	.long	log_bytes
.L215:
	.long	.LC1
.L216:
	.long	.LC2
	.size	prim_local_fetch23, .-prim_local_fetch23
	.align 1
	.align 2
	.global	prim_local_fetch24
	.type	prim_local_fetch24, @function
prim_local_fetch24:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(32,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L220,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L221,r1
	mov.l	.L222,r4
	jsr	@r1
	nop
	mov.l	.L223,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L224,r4
	jsr	@r10
	nop
	mov.l	.L225,r4
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
.L226:
	.align 2
.L220:
	.long	log_text_raw
.L221:
	.long	log_text
.L222:
	.long	.LC0
.L223:
	.long	log_bytes
.L224:
	.long	.LC1
.L225:
	.long	.LC2
	.size	prim_local_fetch24, .-prim_local_fetch24
	.align 1
	.align 2
	.global	prim_local_fetch25
	.type	prim_local_fetch25, @function
prim_local_fetch25:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(36,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L229,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L230,r1
	mov.l	.L231,r4
	jsr	@r1
	nop
	mov.l	.L232,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L233,r4
	jsr	@r10
	nop
	mov.l	.L234,r4
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
.L235:
	.align 2
.L229:
	.long	log_text_raw
.L230:
	.long	log_text
.L231:
	.long	.LC0
.L232:
	.long	log_bytes
.L233:
	.long	.LC1
.L234:
	.long	.LC2
	.size	prim_local_fetch25, .-prim_local_fetch25
	.align 1
	.align 2
	.global	prim_local_fetch26
	.type	prim_local_fetch26, @function
prim_local_fetch26:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(40,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L238,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L239,r1
	mov.l	.L240,r4
	jsr	@r1
	nop
	mov.l	.L241,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L242,r4
	jsr	@r10
	nop
	mov.l	.L243,r4
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
.L244:
	.align 2
.L238:
	.long	log_text_raw
.L239:
	.long	log_text
.L240:
	.long	.LC0
.L241:
	.long	log_bytes
.L242:
	.long	.LC1
.L243:
	.long	.LC2
	.size	prim_local_fetch26, .-prim_local_fetch26
	.align 1
	.align 2
	.global	prim_local_fetch27
	.type	prim_local_fetch27, @function
prim_local_fetch27:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(44,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L247,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L248,r1
	mov.l	.L249,r4
	jsr	@r1
	nop
	mov.l	.L250,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L251,r4
	jsr	@r10
	nop
	mov.l	.L252,r4
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
.L253:
	.align 2
.L247:
	.long	log_text_raw
.L248:
	.long	log_text
.L249:
	.long	.LC0
.L250:
	.long	log_bytes
.L251:
	.long	.LC1
.L252:
	.long	.LC2
	.size	prim_local_fetch27, .-prim_local_fetch27
	.align 1
	.align 2
	.global	prim_local_fetch28
	.type	prim_local_fetch28, @function
prim_local_fetch28:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(48,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L256,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L257,r1
	mov.l	.L258,r4
	jsr	@r1
	nop
	mov.l	.L259,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L260,r4
	jsr	@r10
	nop
	mov.l	.L261,r4
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
.L262:
	.align 2
.L256:
	.long	log_text_raw
.L257:
	.long	log_text
.L258:
	.long	.LC0
.L259:
	.long	log_bytes
.L260:
	.long	.LC1
.L261:
	.long	.LC2
	.size	prim_local_fetch28, .-prim_local_fetch28
	.align 1
	.align 2
	.global	prim_local_fetch29
	.type	prim_local_fetch29, @function
prim_local_fetch29:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(52,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L265,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L266,r1
	mov.l	.L267,r4
	jsr	@r1
	nop
	mov.l	.L268,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L269,r4
	jsr	@r10
	nop
	mov.l	.L270,r4
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
.L271:
	.align 2
.L265:
	.long	log_text_raw
.L266:
	.long	log_text
.L267:
	.long	.LC0
.L268:
	.long	log_bytes
.L269:
	.long	.LC1
.L270:
	.long	.LC2
	.size	prim_local_fetch29, .-prim_local_fetch29
	.align 1
	.align 2
	.global	prim_local_fetch30
	.type	prim_local_fetch30, @function
prim_local_fetch30:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(56,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L274,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L275,r1
	mov.l	.L276,r4
	jsr	@r1
	nop
	mov.l	.L277,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L278,r4
	jsr	@r10
	nop
	mov.l	.L279,r4
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
.L280:
	.align 2
.L274:
	.long	log_text_raw
.L275:
	.long	log_text
.L276:
	.long	.LC0
.L277:
	.long	log_bytes
.L278:
	.long	.LC1
.L279:
	.long	.LC2
	.size	prim_local_fetch30, .-prim_local_fetch30
	.align 1
	.align 2
	.global	prim_local_fetch31
	.type	prim_local_fetch31, @function
prim_local_fetch31:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	mov	r4,r9
	mov.l	r10,@-r15
	add	#64,r9
	sts.l	pr,@-r15
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r9),r5
	mov.l	@(60,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	.L283,r10
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	mov.l	r1,@r4
	mov.l	.L284,r1
	mov.l	.L285,r4
	jsr	@r1
	nop
	mov.l	.L286,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L287,r4
	jsr	@r10
	nop
	mov.l	.L288,r4
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
.L289:
	.align 2
.L283:
	.long	log_text_raw
.L284:
	.long	log_text
.L285:
	.long	.LC0
.L286:
	.long	log_bytes
.L287:
	.long	.LC1
.L288:
	.long	.LC2
	.size	prim_local_fetch31, .-prim_local_fetch31
	.align 1
	.align 2
	.global	prim_local_store0
	.type	prim_local_store0, @function
prim_local_store0:
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
	mov.l	@(36,r4),r1
	mov.l	.L292,r4
	mov.l	r2,@r1
	mov.l	.L293,r1
	mov.l	.L294,r10
	jsr	@r1
	nop
	mov.l	.L295,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L296,r4
	jsr	@r10
	nop
	mov.l	.L297,r4
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
.L298:
	.align 2
.L292:
	.long	.LC0
.L293:
	.long	log_text
.L294:
	.long	log_text_raw
.L295:
	.long	log_bytes
.L296:
	.long	.LC1
.L297:
	.long	.LC2
	.size	prim_local_store0, .-prim_local_store0
	.align 1
	.align 2
	.global	prim_local_store1
	.type	prim_local_store1, @function
prim_local_store1:
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
	mov.l	@(36,r4),r1
	mov.l	.L301,r4
	mov.l	r2,@(4,r1)
	mov.l	.L302,r1
	mov.l	.L303,r10
	jsr	@r1
	nop
	mov.l	.L304,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L305,r4
	jsr	@r10
	nop
	mov.l	.L306,r4
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
.L307:
	.align 2
.L301:
	.long	.LC0
.L302:
	.long	log_text
.L303:
	.long	log_text_raw
.L304:
	.long	log_bytes
.L305:
	.long	.LC1
.L306:
	.long	.LC2
	.size	prim_local_store1, .-prim_local_store1
	.align 1
	.align 2
	.global	prim_local_store2
	.type	prim_local_store2, @function
prim_local_store2:
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
	mov.l	@(36,r4),r1
	mov.l	.L310,r4
	mov.l	r2,@(8,r1)
	mov.l	.L311,r1
	mov.l	.L312,r10
	jsr	@r1
	nop
	mov.l	.L313,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L314,r4
	jsr	@r10
	nop
	mov.l	.L315,r4
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
.L316:
	.align 2
.L310:
	.long	.LC0
.L311:
	.long	log_text
.L312:
	.long	log_text_raw
.L313:
	.long	log_bytes
.L314:
	.long	.LC1
.L315:
	.long	.LC2
	.size	prim_local_store2, .-prim_local_store2
	.align 1
	.align 2
	.global	prim_local_store3
	.type	prim_local_store3, @function
prim_local_store3:
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
	mov.l	@(36,r4),r1
	mov.l	.L319,r4
	mov.l	r2,@(12,r1)
	mov.l	.L320,r1
	mov.l	.L321,r10
	jsr	@r1
	nop
	mov.l	.L322,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L323,r4
	jsr	@r10
	nop
	mov.l	.L324,r4
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
.L325:
	.align 2
.L319:
	.long	.LC0
.L320:
	.long	log_text
.L321:
	.long	log_text_raw
.L322:
	.long	log_bytes
.L323:
	.long	.LC1
.L324:
	.long	.LC2
	.size	prim_local_store3, .-prim_local_store3
	.align 1
	.align 2
	.global	prim_local_store4
	.type	prim_local_store4, @function
prim_local_store4:
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
	mov.l	@(36,r4),r1
	mov.l	.L328,r4
	mov.l	r2,@(16,r1)
	mov.l	.L329,r1
	mov.l	.L330,r10
	jsr	@r1
	nop
	mov.l	.L331,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L332,r4
	jsr	@r10
	nop
	mov.l	.L333,r4
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
.L334:
	.align 2
.L328:
	.long	.LC0
.L329:
	.long	log_text
.L330:
	.long	log_text_raw
.L331:
	.long	log_bytes
.L332:
	.long	.LC1
.L333:
	.long	.LC2
	.size	prim_local_store4, .-prim_local_store4
	.align 1
	.align 2
	.global	prim_local_store5
	.type	prim_local_store5, @function
prim_local_store5:
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
	mov.l	@(36,r4),r1
	mov.l	.L337,r4
	mov.l	r2,@(20,r1)
	mov.l	.L338,r1
	mov.l	.L339,r10
	jsr	@r1
	nop
	mov.l	.L340,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L341,r4
	jsr	@r10
	nop
	mov.l	.L342,r4
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
.L343:
	.align 2
.L337:
	.long	.LC0
.L338:
	.long	log_text
.L339:
	.long	log_text_raw
.L340:
	.long	log_bytes
.L341:
	.long	.LC1
.L342:
	.long	.LC2
	.size	prim_local_store5, .-prim_local_store5
	.align 1
	.align 2
	.global	prim_local_store6
	.type	prim_local_store6, @function
prim_local_store6:
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
	mov.l	@(36,r4),r1
	mov.l	.L346,r4
	mov.l	r2,@(24,r1)
	mov.l	.L347,r1
	mov.l	.L348,r10
	jsr	@r1
	nop
	mov.l	.L349,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L350,r4
	jsr	@r10
	nop
	mov.l	.L351,r4
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
.L352:
	.align 2
.L346:
	.long	.LC0
.L347:
	.long	log_text
.L348:
	.long	log_text_raw
.L349:
	.long	log_bytes
.L350:
	.long	.LC1
.L351:
	.long	.LC2
	.size	prim_local_store6, .-prim_local_store6
	.align 1
	.align 2
	.global	prim_local_store7
	.type	prim_local_store7, @function
prim_local_store7:
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
	mov.l	@(36,r4),r1
	mov.l	.L355,r4
	mov.l	r2,@(28,r1)
	mov.l	.L356,r1
	mov.l	.L357,r10
	jsr	@r1
	nop
	mov.l	.L358,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L359,r4
	jsr	@r10
	nop
	mov.l	.L360,r4
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
.L361:
	.align 2
.L355:
	.long	.LC0
.L356:
	.long	log_text
.L357:
	.long	log_text_raw
.L358:
	.long	log_bytes
.L359:
	.long	.LC1
.L360:
	.long	.LC2
	.size	prim_local_store7, .-prim_local_store7
	.align 1
	.align 2
	.global	prim_local_store8
	.type	prim_local_store8, @function
prim_local_store8:
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
	mov.l	@(36,r4),r1
	mov.l	.L364,r4
	mov.l	r2,@(32,r1)
	mov.l	.L365,r1
	mov.l	.L366,r10
	jsr	@r1
	nop
	mov.l	.L367,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L368,r4
	jsr	@r10
	nop
	mov.l	.L369,r4
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
.L370:
	.align 2
.L364:
	.long	.LC0
.L365:
	.long	log_text
.L366:
	.long	log_text_raw
.L367:
	.long	log_bytes
.L368:
	.long	.LC1
.L369:
	.long	.LC2
	.size	prim_local_store8, .-prim_local_store8
	.align 1
	.align 2
	.global	prim_local_store9
	.type	prim_local_store9, @function
prim_local_store9:
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
	mov.l	@(36,r4),r1
	mov.l	.L373,r4
	mov.l	r2,@(36,r1)
	mov.l	.L374,r1
	mov.l	.L375,r10
	jsr	@r1
	nop
	mov.l	.L376,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L377,r4
	jsr	@r10
	nop
	mov.l	.L378,r4
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
.L379:
	.align 2
.L373:
	.long	.LC0
.L374:
	.long	log_text
.L375:
	.long	log_text_raw
.L376:
	.long	log_bytes
.L377:
	.long	.LC1
.L378:
	.long	.LC2
	.size	prim_local_store9, .-prim_local_store9
	.align 1
	.align 2
	.global	prim_local_store10
	.type	prim_local_store10, @function
prim_local_store10:
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
	mov.l	@(36,r4),r1
	mov.l	.L382,r4
	mov.l	r2,@(40,r1)
	mov.l	.L383,r1
	mov.l	.L384,r10
	jsr	@r1
	nop
	mov.l	.L385,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L386,r4
	jsr	@r10
	nop
	mov.l	.L387,r4
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
.L388:
	.align 2
.L382:
	.long	.LC0
.L383:
	.long	log_text
.L384:
	.long	log_text_raw
.L385:
	.long	log_bytes
.L386:
	.long	.LC1
.L387:
	.long	.LC2
	.size	prim_local_store10, .-prim_local_store10
	.align 1
	.align 2
	.global	prim_local_store11
	.type	prim_local_store11, @function
prim_local_store11:
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
	mov.l	@(36,r4),r1
	mov.l	.L391,r4
	mov.l	r2,@(44,r1)
	mov.l	.L392,r1
	mov.l	.L393,r10
	jsr	@r1
	nop
	mov.l	.L394,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L395,r4
	jsr	@r10
	nop
	mov.l	.L396,r4
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
.L397:
	.align 2
.L391:
	.long	.LC0
.L392:
	.long	log_text
.L393:
	.long	log_text_raw
.L394:
	.long	log_bytes
.L395:
	.long	.LC1
.L396:
	.long	.LC2
	.size	prim_local_store11, .-prim_local_store11
	.align 1
	.align 2
	.global	prim_local_store12
	.type	prim_local_store12, @function
prim_local_store12:
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
	mov.l	@(36,r4),r1
	mov.l	.L400,r4
	mov.l	r2,@(48,r1)
	mov.l	.L401,r1
	mov.l	.L402,r10
	jsr	@r1
	nop
	mov.l	.L403,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L404,r4
	jsr	@r10
	nop
	mov.l	.L405,r4
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
.L406:
	.align 2
.L400:
	.long	.LC0
.L401:
	.long	log_text
.L402:
	.long	log_text_raw
.L403:
	.long	log_bytes
.L404:
	.long	.LC1
.L405:
	.long	.LC2
	.size	prim_local_store12, .-prim_local_store12
	.align 1
	.align 2
	.global	prim_local_store13
	.type	prim_local_store13, @function
prim_local_store13:
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
	mov.l	@(36,r4),r1
	mov.l	.L409,r4
	mov.l	r2,@(52,r1)
	mov.l	.L410,r1
	mov.l	.L411,r10
	jsr	@r1
	nop
	mov.l	.L412,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L413,r4
	jsr	@r10
	nop
	mov.l	.L414,r4
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
.L415:
	.align 2
.L409:
	.long	.LC0
.L410:
	.long	log_text
.L411:
	.long	log_text_raw
.L412:
	.long	log_bytes
.L413:
	.long	.LC1
.L414:
	.long	.LC2
	.size	prim_local_store13, .-prim_local_store13
	.align 1
	.align 2
	.global	prim_local_store14
	.type	prim_local_store14, @function
prim_local_store14:
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
	mov.l	@(36,r4),r1
	mov.l	.L418,r4
	mov.l	r2,@(56,r1)
	mov.l	.L419,r1
	mov.l	.L420,r10
	jsr	@r1
	nop
	mov.l	.L421,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L422,r4
	jsr	@r10
	nop
	mov.l	.L423,r4
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
.L424:
	.align 2
.L418:
	.long	.LC0
.L419:
	.long	log_text
.L420:
	.long	log_text_raw
.L421:
	.long	log_bytes
.L422:
	.long	.LC1
.L423:
	.long	.LC2
	.size	prim_local_store14, .-prim_local_store14
	.align 1
	.align 2
	.global	prim_local_store15
	.type	prim_local_store15, @function
prim_local_store15:
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
	mov.l	@(36,r4),r1
	mov.l	.L427,r4
	mov.l	r2,@(60,r1)
	mov.l	.L428,r1
	mov.l	.L429,r10
	jsr	@r1
	nop
	mov.l	.L430,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L431,r4
	jsr	@r10
	nop
	mov.l	.L432,r4
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
.L433:
	.align 2
.L427:
	.long	.LC0
.L428:
	.long	log_text
.L429:
	.long	log_text_raw
.L430:
	.long	log_bytes
.L431:
	.long	.LC1
.L432:
	.long	.LC2
	.size	prim_local_store15, .-prim_local_store15
	.align 1
	.align 2
	.global	prim_local_store16
	.type	prim_local_store16, @function
prim_local_store16:
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
	mov.l	@(36,r4),r1
	mov.l	.L436,r4
	add	#64,r1
	mov.l	.L437,r10
	mov.l	r2,@(0,r1)
	mov.l	.L438,r1
	jsr	@r1
	nop
	mov.l	.L439,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L440,r4
	jsr	@r10
	nop
	mov.l	.L441,r4
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
.L442:
	.align 2
.L436:
	.long	.LC0
.L437:
	.long	log_text_raw
.L438:
	.long	log_text
.L439:
	.long	log_bytes
.L440:
	.long	.LC1
.L441:
	.long	.LC2
	.size	prim_local_store16, .-prim_local_store16
	.align 1
	.align 2
	.global	prim_local_store17
	.type	prim_local_store17, @function
prim_local_store17:
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
	mov.l	@(36,r4),r1
	mov.l	.L445,r4
	add	#64,r1
	mov.l	.L446,r10
	mov.l	r2,@(4,r1)
	mov.l	.L447,r1
	jsr	@r1
	nop
	mov.l	.L448,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L449,r4
	jsr	@r10
	nop
	mov.l	.L450,r4
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
.L451:
	.align 2
.L445:
	.long	.LC0
.L446:
	.long	log_text_raw
.L447:
	.long	log_text
.L448:
	.long	log_bytes
.L449:
	.long	.LC1
.L450:
	.long	.LC2
	.size	prim_local_store17, .-prim_local_store17
	.align 1
	.align 2
	.global	prim_local_store18
	.type	prim_local_store18, @function
prim_local_store18:
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
	mov.l	@(36,r4),r1
	mov.l	.L454,r4
	add	#64,r1
	mov.l	.L455,r10
	mov.l	r2,@(8,r1)
	mov.l	.L456,r1
	jsr	@r1
	nop
	mov.l	.L457,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L458,r4
	jsr	@r10
	nop
	mov.l	.L459,r4
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
.L460:
	.align 2
.L454:
	.long	.LC0
.L455:
	.long	log_text_raw
.L456:
	.long	log_text
.L457:
	.long	log_bytes
.L458:
	.long	.LC1
.L459:
	.long	.LC2
	.size	prim_local_store18, .-prim_local_store18
	.align 1
	.align 2
	.global	prim_local_store19
	.type	prim_local_store19, @function
prim_local_store19:
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
	mov.l	@(36,r4),r1
	mov.l	.L463,r4
	add	#64,r1
	mov.l	.L464,r10
	mov.l	r2,@(12,r1)
	mov.l	.L465,r1
	jsr	@r1
	nop
	mov.l	.L466,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L467,r4
	jsr	@r10
	nop
	mov.l	.L468,r4
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
.L469:
	.align 2
.L463:
	.long	.LC0
.L464:
	.long	log_text_raw
.L465:
	.long	log_text
.L466:
	.long	log_bytes
.L467:
	.long	.LC1
.L468:
	.long	.LC2
	.size	prim_local_store19, .-prim_local_store19
	.align 1
	.align 2
	.global	prim_local_store20
	.type	prim_local_store20, @function
prim_local_store20:
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
	mov.l	@(36,r4),r1
	mov.l	.L472,r4
	add	#64,r1
	mov.l	.L473,r10
	mov.l	r2,@(16,r1)
	mov.l	.L474,r1
	jsr	@r1
	nop
	mov.l	.L475,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L476,r4
	jsr	@r10
	nop
	mov.l	.L477,r4
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
.L478:
	.align 2
.L472:
	.long	.LC0
.L473:
	.long	log_text_raw
.L474:
	.long	log_text
.L475:
	.long	log_bytes
.L476:
	.long	.LC1
.L477:
	.long	.LC2
	.size	prim_local_store20, .-prim_local_store20
	.align 1
	.align 2
	.global	prim_local_store21
	.type	prim_local_store21, @function
prim_local_store21:
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
	mov.l	@(36,r4),r1
	mov.l	.L481,r4
	add	#64,r1
	mov.l	.L482,r10
	mov.l	r2,@(20,r1)
	mov.l	.L483,r1
	jsr	@r1
	nop
	mov.l	.L484,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L485,r4
	jsr	@r10
	nop
	mov.l	.L486,r4
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
.L487:
	.align 2
.L481:
	.long	.LC0
.L482:
	.long	log_text_raw
.L483:
	.long	log_text
.L484:
	.long	log_bytes
.L485:
	.long	.LC1
.L486:
	.long	.LC2
	.size	prim_local_store21, .-prim_local_store21
	.align 1
	.align 2
	.global	prim_local_store22
	.type	prim_local_store22, @function
prim_local_store22:
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
	mov.l	@(36,r4),r1
	mov.l	.L490,r4
	add	#64,r1
	mov.l	.L491,r10
	mov.l	r2,@(24,r1)
	mov.l	.L492,r1
	jsr	@r1
	nop
	mov.l	.L493,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L494,r4
	jsr	@r10
	nop
	mov.l	.L495,r4
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
.L496:
	.align 2
.L490:
	.long	.LC0
.L491:
	.long	log_text_raw
.L492:
	.long	log_text
.L493:
	.long	log_bytes
.L494:
	.long	.LC1
.L495:
	.long	.LC2
	.size	prim_local_store22, .-prim_local_store22
	.align 1
	.align 2
	.global	prim_local_store23
	.type	prim_local_store23, @function
prim_local_store23:
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
	mov.l	@(36,r4),r1
	mov.l	.L499,r4
	add	#64,r1
	mov.l	.L500,r10
	mov.l	r2,@(28,r1)
	mov.l	.L501,r1
	jsr	@r1
	nop
	mov.l	.L502,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L503,r4
	jsr	@r10
	nop
	mov.l	.L504,r4
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
.L505:
	.align 2
.L499:
	.long	.LC0
.L500:
	.long	log_text_raw
.L501:
	.long	log_text
.L502:
	.long	log_bytes
.L503:
	.long	.LC1
.L504:
	.long	.LC2
	.size	prim_local_store23, .-prim_local_store23
	.align 1
	.align 2
	.global	prim_local_store24
	.type	prim_local_store24, @function
prim_local_store24:
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
	mov.l	@(36,r4),r1
	mov.l	.L508,r4
	add	#64,r1
	mov.l	.L509,r10
	mov.l	r2,@(32,r1)
	mov.l	.L510,r1
	jsr	@r1
	nop
	mov.l	.L511,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L512,r4
	jsr	@r10
	nop
	mov.l	.L513,r4
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
.L514:
	.align 2
.L508:
	.long	.LC0
.L509:
	.long	log_text_raw
.L510:
	.long	log_text
.L511:
	.long	log_bytes
.L512:
	.long	.LC1
.L513:
	.long	.LC2
	.size	prim_local_store24, .-prim_local_store24
	.align 1
	.align 2
	.global	prim_local_store25
	.type	prim_local_store25, @function
prim_local_store25:
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
	mov.l	@(36,r4),r1
	mov.l	.L517,r4
	add	#64,r1
	mov.l	.L518,r10
	mov.l	r2,@(36,r1)
	mov.l	.L519,r1
	jsr	@r1
	nop
	mov.l	.L520,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L521,r4
	jsr	@r10
	nop
	mov.l	.L522,r4
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
.L523:
	.align 2
.L517:
	.long	.LC0
.L518:
	.long	log_text_raw
.L519:
	.long	log_text
.L520:
	.long	log_bytes
.L521:
	.long	.LC1
.L522:
	.long	.LC2
	.size	prim_local_store25, .-prim_local_store25
	.align 1
	.align 2
	.global	prim_local_store26
	.type	prim_local_store26, @function
prim_local_store26:
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
	mov.l	@(36,r4),r1
	mov.l	.L526,r4
	add	#64,r1
	mov.l	.L527,r10
	mov.l	r2,@(40,r1)
	mov.l	.L528,r1
	jsr	@r1
	nop
	mov.l	.L529,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L530,r4
	jsr	@r10
	nop
	mov.l	.L531,r4
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
.L532:
	.align 2
.L526:
	.long	.LC0
.L527:
	.long	log_text_raw
.L528:
	.long	log_text
.L529:
	.long	log_bytes
.L530:
	.long	.LC1
.L531:
	.long	.LC2
	.size	prim_local_store26, .-prim_local_store26
	.align 1
	.align 2
	.global	prim_local_store27
	.type	prim_local_store27, @function
prim_local_store27:
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
	mov.l	@(36,r4),r1
	mov.l	.L535,r4
	add	#64,r1
	mov.l	.L536,r10
	mov.l	r2,@(44,r1)
	mov.l	.L537,r1
	jsr	@r1
	nop
	mov.l	.L538,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L539,r4
	jsr	@r10
	nop
	mov.l	.L540,r4
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
.L541:
	.align 2
.L535:
	.long	.LC0
.L536:
	.long	log_text_raw
.L537:
	.long	log_text
.L538:
	.long	log_bytes
.L539:
	.long	.LC1
.L540:
	.long	.LC2
	.size	prim_local_store27, .-prim_local_store27
	.align 1
	.align 2
	.global	prim_local_store28
	.type	prim_local_store28, @function
prim_local_store28:
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
	mov.l	@(36,r4),r1
	mov.l	.L544,r4
	add	#64,r1
	mov.l	.L545,r10
	mov.l	r2,@(48,r1)
	mov.l	.L546,r1
	jsr	@r1
	nop
	mov.l	.L547,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L548,r4
	jsr	@r10
	nop
	mov.l	.L549,r4
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
.L550:
	.align 2
.L544:
	.long	.LC0
.L545:
	.long	log_text_raw
.L546:
	.long	log_text
.L547:
	.long	log_bytes
.L548:
	.long	.LC1
.L549:
	.long	.LC2
	.size	prim_local_store28, .-prim_local_store28
	.align 1
	.align 2
	.global	prim_local_store29
	.type	prim_local_store29, @function
prim_local_store29:
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
	mov.l	@(36,r4),r1
	mov.l	.L553,r4
	add	#64,r1
	mov.l	.L554,r10
	mov.l	r2,@(52,r1)
	mov.l	.L555,r1
	jsr	@r1
	nop
	mov.l	.L556,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L557,r4
	jsr	@r10
	nop
	mov.l	.L558,r4
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
.L559:
	.align 2
.L553:
	.long	.LC0
.L554:
	.long	log_text_raw
.L555:
	.long	log_text
.L556:
	.long	log_bytes
.L557:
	.long	.LC1
.L558:
	.long	.LC2
	.size	prim_local_store29, .-prim_local_store29
	.align 1
	.align 2
	.global	prim_local_store30
	.type	prim_local_store30, @function
prim_local_store30:
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
	mov.l	@(36,r4),r1
	mov.l	.L562,r4
	add	#64,r1
	mov.l	.L563,r10
	mov.l	r2,@(56,r1)
	mov.l	.L564,r1
	jsr	@r1
	nop
	mov.l	.L565,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L566,r4
	jsr	@r10
	nop
	mov.l	.L567,r4
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
.L568:
	.align 2
.L562:
	.long	.LC0
.L563:
	.long	log_text_raw
.L564:
	.long	log_text
.L565:
	.long	log_bytes
.L566:
	.long	.LC1
.L567:
	.long	.LC2
	.size	prim_local_store30, .-prim_local_store30
	.align 1
	.align 2
	.global	prim_local_store31
	.type	prim_local_store31, @function
prim_local_store31:
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
	mov.l	@(36,r4),r1
	mov.l	.L571,r4
	add	#64,r1
	mov.l	.L572,r10
	mov.l	r2,@(60,r1)
	mov.l	.L573,r1
	jsr	@r1
	nop
	mov.l	.L574,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r9),r4
	mov.l	.L575,r4
	jsr	@r10
	nop
	mov.l	.L576,r4
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
.L577:
	.align 2
.L571:
	.long	.LC0
.L572:
	.long	log_text_raw
.L573:
	.long	log_text
.L574:
	.long	log_bytes
.L575:
	.long	.LC1
.L576:
	.long	.LC2
	.size	prim_local_store31, .-prim_local_store31
	.align 1
	.align 2
	.global	prim_locals_copy
	.type	prim_locals_copy, @function
prim_locals_copy:
	mov.l	r8,@-r15
	mov	r4,r8
	sts.l	pr,@-r15
	add	#64,r8
	mov	r4,r6
	mov.l	@(12,r8),r5
	add	#-8,r15
	mov.l	@r4,r4
	mov.l	@(4,r5),r1
	add	#4,r5
	mov	r1,r0
	shlr16	r0
	cmp/ge	r0,r4
	bf/s	.L589
	mov.l	r5,@(12,r8)
	tst	r0,r0
	bt	.L581
	mov.l	@(4,r6),r2
	mov	r4,r3
	shll2	r3
	add	r3,r2
	mov.l	@(36,r6),r3
	extu.w	r1,r1
	shll2	r1
	add	#4,r3
	add	r1,r3
	mov	r0,r1
	shll2	r1
	add	#-4,r1
	shlr2	r1
	add	#1,r1
	.align 2
.L582:
	add	#-4,r2
	mov.l	@r2,r7
	dt	r1
	bf/s	.L582
	mov.l	r7,@-r3
	sub	r0,r4
.L581:
	mov.l	.L590,r1
	mov.l	r4,@r6
	mov.l	.L591,r4
	jsr	@r1
	mov.l	r6,@r15
	mov.l	.L592,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L593,r1
	mov.l	.L594,r4
	jsr	@r1
	mov.l	r1,@(4,r15)
	mov.l	@(4,r15),r1
	mov.l	.L595,r4
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
.L589:
	mov	#10,r2
	mov	r6,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r6
	mov	#0,r1
	mov.b	r1,@r6
	add	#8,r15
	lds.l	@r15+,pr
	rts	
	mov.l	@r15+,r8
.L596:
	.align 2
.L590:
	.long	log_text
.L591:
	.long	.LC0
.L592:
	.long	log_bytes
.L593:
	.long	log_text_raw
.L594:
	.long	.LC1
.L595:
	.long	.LC2
	.size	prim_locals_copy, .-prim_locals_copy
	.align 1
	.align 2
	.global	prim_locals_zero
	.type	prim_locals_zero, @function
prim_locals_zero:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	r4,r10
	sts.l	pr,@-r15
	mov.l	@(12,r8),r9
	mov.l	@(4,r9),r4
	add	#4,r9
	mov	r4,r6
	shlr16	r6
	tst	r6,r6
	bt/s	.L598
	mov.l	r9,@(12,r8)
	extu.w	r4,r4
	mov.l	.L603,r0
	sub	r6,r4
	mov.l	@(36,r10),r1
	add	#1,r4
	shll2	r4
	shll2	r6
	mov	#0,r5
	jsr	@r0
	add	r1,r4
.L598:
	mov.l	.L604,r1
	mov	r9,r5
	mov.l	.L605,r4
	mov.l	.L606,r9
	jsr	@r1
	nop
	mov.l	.L607,r1
	mov	#32,r5
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L608,r4
	jsr	@r9
	nop
	mov.l	.L609,r4
	jsr	@r9
	nop
	mov.l	@(12,r8),r1
	mov	r10,r4
	mov	r1,r2
	add	#4,r2
	mov.l	r2,@(12,r8)
	mov.l	@(4,r1),r1
	lds.l	@r15+,pr
	mov.l	@r15+,r10
	mov.l	@r15+,r9
	jmp	@r1
	mov.l	@r15+,r8
.L610:
	.align 2
.L603:
	.long	memset
.L604:
	.long	log_text
.L605:
	.long	.LC0
.L606:
	.long	log_text_raw
.L607:
	.long	log_bytes
.L608:
	.long	.LC1
.L609:
	.long	.LC2
	.size	prim_locals_zero, .-prim_locals_zero
	.global	forth_locals_store
	.data
	.align 2
	.type	forth_locals_store, @object
	.size	forth_locals_store, 128
forth_locals_store:
	.long	prim_local_store0
	.long	prim_local_store1
	.long	prim_local_store2
	.long	prim_local_store3
	.long	prim_local_store4
	.long	prim_local_store5
	.long	prim_local_store6
	.long	prim_local_store7
	.long	prim_local_store8
	.long	prim_local_store9
	.long	prim_local_store10
	.long	prim_local_store11
	.long	prim_local_store12
	.long	prim_local_store13
	.long	prim_local_store14
	.long	prim_local_store15
	.long	prim_local_store16
	.long	prim_local_store17
	.long	prim_local_store18
	.long	prim_local_store19
	.long	prim_local_store20
	.long	prim_local_store21
	.long	prim_local_store22
	.long	prim_local_store23
	.long	prim_local_store24
	.long	prim_local_store25
	.long	prim_local_store26
	.long	prim_local_store27
	.long	prim_local_store28
	.long	prim_local_store29
	.long	prim_local_store30
	.long	prim_local_store31
	.global	forth_locals_fetch
	.align 2
	.type	forth_locals_fetch, @object
	.size	forth_locals_fetch, 128
forth_locals_fetch:
	.long	prim_local_fetch0
	.long	prim_local_fetch1
	.long	prim_local_fetch2
	.long	prim_local_fetch3
	.long	prim_local_fetch4
	.long	prim_local_fetch5
	.long	prim_local_fetch6
	.long	prim_local_fetch7
	.long	prim_local_fetch8
	.long	prim_local_fetch9
	.long	prim_local_fetch10
	.long	prim_local_fetch11
	.long	prim_local_fetch12
	.long	prim_local_fetch13
	.long	prim_local_fetch14
	.long	prim_local_fetch15
	.long	prim_local_fetch16
	.long	prim_local_fetch17
	.long	prim_local_fetch18
	.long	prim_local_fetch19
	.long	prim_local_fetch20
	.long	prim_local_fetch21
	.long	prim_local_fetch22
	.long	prim_local_fetch23
	.long	prim_local_fetch24
	.long	prim_local_fetch25
	.long	prim_local_fetch26
	.long	prim_local_fetch27
	.long	prim_local_fetch28
	.long	prim_local_fetch29
	.long	prim_local_fetch30
	.long	prim_local_fetch31
	.ident	"GCC: (GNU) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
