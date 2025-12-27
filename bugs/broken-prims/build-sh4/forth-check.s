	.file	"forth-check.c"
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
	.global	prim_check_0_0
	.type	prim_check_0_0, @function
prim_check_0_0:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	r4,r9
	mov.l	.L4,r1
	sts.l	pr,@-r15
	mov.l	.L5,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L6,r1
	mov	#32,r5
	mov.l	.L7,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L8,r4
	jsr	@r10
	nop
	mov.l	.L9,r4
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
.L10:
	.align 2
.L4:
	.long	log_text
.L5:
	.long	.LC0
.L6:
	.long	log_bytes
.L7:
	.long	log_text_raw
.L8:
	.long	.LC1
.L9:
	.long	.LC2
	.size	prim_check_0_0, .-prim_check_0_0
	.align 1
	.align 2
	.type	prim_check_0_1.part.0, @function
prim_check_0_1.part.0:
	mov.l	r8,@-r15
	mov	r4,r8
	mov.l	r9,@-r15
	add	#64,r8
	mov.l	r10,@-r15
	mov	r4,r9
	mov.l	.L13,r1
	sts.l	pr,@-r15
	mov.l	.L14,r4
	jsr	@r1
	mov.l	@(12,r8),r5
	mov.l	.L15,r1
	mov	#32,r5
	mov.l	.L16,r10
	jsr	@r1
	mov.l	@(12,r8),r4
	mov.l	.L17,r4
	jsr	@r10
	nop
	mov.l	.L18,r4
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
.L19:
	.align 2
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
	.size	prim_check_0_1.part.0, .-prim_check_0_1.part.0
	.set	prim_check_7_7.part.0,prim_check_0_1.part.0
	.set	prim_check_7_6.part.0,prim_check_0_1.part.0
	.set	prim_check_7_5.part.0,prim_check_0_1.part.0
	.set	prim_check_7_4.part.0,prim_check_0_1.part.0
	.set	prim_check_7_3.part.0,prim_check_0_1.part.0
	.set	prim_check_7_2.part.0,prim_check_0_1.part.0
	.set	prim_check_7_1.part.0,prim_check_0_1.part.0
	.set	prim_check_7_0.part.0,prim_check_0_1.part.0
	.set	prim_check_6_7.part.0,prim_check_0_1.part.0
	.set	prim_check_6_6.part.0,prim_check_0_1.part.0
	.set	prim_check_6_5.part.0,prim_check_0_1.part.0
	.set	prim_check_6_4.part.0,prim_check_0_1.part.0
	.set	prim_check_6_3.part.0,prim_check_0_1.part.0
	.set	prim_check_6_2.part.0,prim_check_0_1.part.0
	.set	prim_check_6_1.part.0,prim_check_0_1.part.0
	.set	prim_check_6_0.part.0,prim_check_0_1.part.0
	.set	prim_check_5_7.part.0,prim_check_0_1.part.0
	.set	prim_check_5_6.part.0,prim_check_0_1.part.0
	.set	prim_check_5_5.part.0,prim_check_0_1.part.0
	.set	prim_check_5_4.part.0,prim_check_0_1.part.0
	.set	prim_check_5_3.part.0,prim_check_0_1.part.0
	.set	prim_check_5_2.part.0,prim_check_0_1.part.0
	.set	prim_check_5_1.part.0,prim_check_0_1.part.0
	.set	prim_check_5_0.part.0,prim_check_0_1.part.0
	.set	prim_check_4_7.part.0,prim_check_0_1.part.0
	.set	prim_check_4_6.part.0,prim_check_0_1.part.0
	.set	prim_check_4_5.part.0,prim_check_0_1.part.0
	.set	prim_check_4_4.part.0,prim_check_0_1.part.0
	.set	prim_check_4_3.part.0,prim_check_0_1.part.0
	.set	prim_check_4_2.part.0,prim_check_0_1.part.0
	.set	prim_check_4_1.part.0,prim_check_0_1.part.0
	.set	prim_check_4_0.part.0,prim_check_0_1.part.0
	.set	prim_check_3_7.part.0,prim_check_0_1.part.0
	.set	prim_check_3_6.part.0,prim_check_0_1.part.0
	.set	prim_check_3_5.part.0,prim_check_0_1.part.0
	.set	prim_check_3_4.part.0,prim_check_0_1.part.0
	.set	prim_check_3_3.part.0,prim_check_0_1.part.0
	.set	prim_check_3_2.part.0,prim_check_0_1.part.0
	.set	prim_check_3_1.part.0,prim_check_0_1.part.0
	.set	prim_check_3_0.part.0,prim_check_0_1.part.0
	.set	prim_check_2_7.part.0,prim_check_0_1.part.0
	.set	prim_check_2_6.part.0,prim_check_0_1.part.0
	.set	prim_check_2_5.part.0,prim_check_0_1.part.0
	.set	prim_check_2_4.part.0,prim_check_0_1.part.0
	.set	prim_check_2_3.part.0,prim_check_0_1.part.0
	.set	prim_check_2_2.part.0,prim_check_0_1.part.0
	.set	prim_check_2_1.part.0,prim_check_0_1.part.0
	.set	prim_check_2_0.part.0,prim_check_0_1.part.0
	.set	prim_check_1_7.part.0,prim_check_0_1.part.0
	.set	prim_check_1_6.part.0,prim_check_0_1.part.0
	.set	prim_check_1_5.part.0,prim_check_0_1.part.0
	.set	prim_check_1_4.part.0,prim_check_0_1.part.0
	.set	prim_check_1_3.part.0,prim_check_0_1.part.0
	.set	prim_check_1_2.part.0,prim_check_0_1.part.0
	.set	prim_check_1_1.part.0,prim_check_0_1.part.0
	.set	prim_check_1_0.part.0,prim_check_0_1.part.0
	.set	prim_check_0_7.part.0,prim_check_0_1.part.0
	.set	prim_check_0_6.part.0,prim_check_0_1.part.0
	.set	prim_check_0_5.part.0,prim_check_0_1.part.0
	.set	prim_check_0_4.part.0,prim_check_0_1.part.0
	.set	prim_check_0_3.part.0,prim_check_0_1.part.0
	.set	prim_check_0_2.part.0,prim_check_0_1.part.0
	.align 1
	.align 2
	.global	prim_check_0_1
	.type	prim_check_0_1, @function
prim_check_0_1:
	mov.l	@r4,r2
	mov.w	.L25,r1
	cmp/gt	r1,r2
	bf/s	.L21
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L21:
	mov.l	.L26,r1
	jmp	@r1
	nop
	.align 1
.L25:
	.short	255
.L27:
	.align 2
.L26:
	.long	prim_check_0_1.part.0
	.size	prim_check_0_1, .-prim_check_0_1
	.align 1
	.align 2
	.global	prim_check_0_2
	.type	prim_check_0_2, @function
prim_check_0_2:
	mov.l	@r4,r2
	mov.w	.L33,r1
	cmp/gt	r1,r2
	bf/s	.L29
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L29:
	mov.l	.L34,r1
	jmp	@r1
	nop
	.align 1
.L33:
	.short	254
.L35:
	.align 2
.L34:
	.long	prim_check_0_2.part.0
	.size	prim_check_0_2, .-prim_check_0_2
	.align 1
	.align 2
	.global	prim_check_0_3
	.type	prim_check_0_3, @function
prim_check_0_3:
	mov.l	@r4,r2
	mov.w	.L41,r1
	cmp/gt	r1,r2
	bf/s	.L37
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L37:
	mov.l	.L42,r1
	jmp	@r1
	nop
	.align 1
.L41:
	.short	253
.L43:
	.align 2
.L42:
	.long	prim_check_0_3.part.0
	.size	prim_check_0_3, .-prim_check_0_3
	.align 1
	.align 2
	.global	prim_check_0_4
	.type	prim_check_0_4, @function
prim_check_0_4:
	mov.l	@r4,r2
	mov.w	.L49,r1
	cmp/gt	r1,r2
	bf/s	.L45
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L45:
	mov.l	.L50,r1
	jmp	@r1
	nop
	.align 1
.L49:
	.short	252
.L51:
	.align 2
.L50:
	.long	prim_check_0_4.part.0
	.size	prim_check_0_4, .-prim_check_0_4
	.align 1
	.align 2
	.global	prim_check_0_5
	.type	prim_check_0_5, @function
prim_check_0_5:
	mov.l	@r4,r2
	mov.w	.L57,r1
	cmp/gt	r1,r2
	bf/s	.L53
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L53:
	mov.l	.L58,r1
	jmp	@r1
	nop
	.align 1
.L57:
	.short	251
.L59:
	.align 2
.L58:
	.long	prim_check_0_5.part.0
	.size	prim_check_0_5, .-prim_check_0_5
	.align 1
	.align 2
	.global	prim_check_0_6
	.type	prim_check_0_6, @function
prim_check_0_6:
	mov.l	@r4,r2
	mov.w	.L65,r1
	cmp/gt	r1,r2
	bf/s	.L61
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L61:
	mov.l	.L66,r1
	jmp	@r1
	nop
	.align 1
.L65:
	.short	250
.L67:
	.align 2
.L66:
	.long	prim_check_0_6.part.0
	.size	prim_check_0_6, .-prim_check_0_6
	.align 1
	.align 2
	.global	prim_check_0_7
	.type	prim_check_0_7, @function
prim_check_0_7:
	mov.l	@r4,r2
	mov.w	.L73,r1
	cmp/gt	r1,r2
	bf/s	.L69
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L69:
	mov.l	.L74,r1
	jmp	@r1
	nop
	.align 1
.L73:
	.short	249
.L75:
	.align 2
.L74:
	.long	prim_check_0_7.part.0
	.size	prim_check_0_7, .-prim_check_0_7
	.align 1
	.align 2
	.global	prim_check_1_0
	.type	prim_check_1_0, @function
prim_check_1_0:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L81
	mov	#10,r2
	mov.l	.L82,r1
	jmp	@r1
	nop
	.align 1
.L81:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
.L83:
	.align 2
.L82:
	.long	prim_check_1_0.part.0
	.size	prim_check_1_0, .-prim_check_1_0
	.align 1
	.align 2
	.global	prim_check_1_1
	.type	prim_check_1_1, @function
prim_check_1_1:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L89
	mov	#10,r2
	mov.w	.L90,r2
	cmp/gt	r2,r1
	bf/s	.L87
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L87:
	mov.l	.L91,r1
	jmp	@r1
	nop
	.align 1
.L89:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L90:
	.short	255
.L92:
	.align 2
.L91:
	.long	prim_check_1_1.part.0
	.size	prim_check_1_1, .-prim_check_1_1
	.align 1
	.align 2
	.global	prim_check_1_2
	.type	prim_check_1_2, @function
prim_check_1_2:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L98
	mov	#10,r2
	mov.w	.L99,r2
	cmp/gt	r2,r1
	bf/s	.L96
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L96:
	mov.l	.L100,r1
	jmp	@r1
	nop
	.align 1
.L98:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L99:
	.short	254
.L101:
	.align 2
.L100:
	.long	prim_check_1_2.part.0
	.size	prim_check_1_2, .-prim_check_1_2
	.align 1
	.align 2
	.global	prim_check_1_3
	.type	prim_check_1_3, @function
prim_check_1_3:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L107
	mov	#10,r2
	mov.w	.L108,r2
	cmp/gt	r2,r1
	bf/s	.L105
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L105:
	mov.l	.L109,r1
	jmp	@r1
	nop
	.align 1
.L107:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L108:
	.short	253
.L110:
	.align 2
.L109:
	.long	prim_check_1_3.part.0
	.size	prim_check_1_3, .-prim_check_1_3
	.align 1
	.align 2
	.global	prim_check_1_4
	.type	prim_check_1_4, @function
prim_check_1_4:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L116
	mov	#10,r2
	mov.w	.L117,r2
	cmp/gt	r2,r1
	bf/s	.L114
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L114:
	mov.l	.L118,r1
	jmp	@r1
	nop
	.align 1
.L116:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L117:
	.short	252
.L119:
	.align 2
.L118:
	.long	prim_check_1_4.part.0
	.size	prim_check_1_4, .-prim_check_1_4
	.align 1
	.align 2
	.global	prim_check_1_5
	.type	prim_check_1_5, @function
prim_check_1_5:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L125
	mov	#10,r2
	mov.w	.L126,r2
	cmp/gt	r2,r1
	bf/s	.L123
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L123:
	mov.l	.L127,r1
	jmp	@r1
	nop
	.align 1
.L125:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L126:
	.short	251
.L128:
	.align 2
.L127:
	.long	prim_check_1_5.part.0
	.size	prim_check_1_5, .-prim_check_1_5
	.align 1
	.align 2
	.global	prim_check_1_6
	.type	prim_check_1_6, @function
prim_check_1_6:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L134
	mov	#10,r2
	mov.w	.L135,r2
	cmp/gt	r2,r1
	bf/s	.L132
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L132:
	mov.l	.L136,r1
	jmp	@r1
	nop
	.align 1
.L134:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L135:
	.short	250
.L137:
	.align 2
.L136:
	.long	prim_check_1_6.part.0
	.size	prim_check_1_6, .-prim_check_1_6
	.align 1
	.align 2
	.global	prim_check_1_7
	.type	prim_check_1_7, @function
prim_check_1_7:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L143
	mov	#10,r2
	mov.w	.L144,r2
	cmp/gt	r2,r1
	bf/s	.L141
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L141:
	mov.l	.L145,r1
	jmp	@r1
	nop
	.align 1
.L143:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L144:
	.short	249
.L146:
	.align 2
.L145:
	.long	prim_check_1_7.part.0
	.size	prim_check_1_7, .-prim_check_1_7
	.align 1
	.align 2
	.global	prim_check_2_0
	.type	prim_check_2_0, @function
prim_check_2_0:
	mov.l	@r4,r2
	mov	#1,r1
	cmp/gt	r1,r2
	bf	.L152
	mov.l	.L153,r1
	jmp	@r1
	nop
	.align 1
.L152:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
.L154:
	.align 2
.L153:
	.long	prim_check_2_0.part.0
	.size	prim_check_2_0, .-prim_check_2_0
	.align 1
	.align 2
	.global	prim_check_2_1
	.type	prim_check_2_1, @function
prim_check_2_1:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L160
	mov.w	.L161,r2
	cmp/gt	r2,r1
	bf/s	.L158
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L158:
	mov.l	.L162,r1
	jmp	@r1
	nop
	.align 1
.L160:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L161:
	.short	255
.L163:
	.align 2
.L162:
	.long	prim_check_2_1.part.0
	.size	prim_check_2_1, .-prim_check_2_1
	.align 1
	.align 2
	.global	prim_check_2_2
	.type	prim_check_2_2, @function
prim_check_2_2:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L169
	mov.w	.L170,r2
	cmp/gt	r2,r1
	bf/s	.L167
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L167:
	mov.l	.L171,r1
	jmp	@r1
	nop
	.align 1
.L169:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L170:
	.short	254
.L172:
	.align 2
.L171:
	.long	prim_check_2_2.part.0
	.size	prim_check_2_2, .-prim_check_2_2
	.align 1
	.align 2
	.global	prim_check_2_3
	.type	prim_check_2_3, @function
prim_check_2_3:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L178
	mov.w	.L179,r2
	cmp/gt	r2,r1
	bf/s	.L176
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L176:
	mov.l	.L180,r1
	jmp	@r1
	nop
	.align 1
.L178:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L179:
	.short	253
.L181:
	.align 2
.L180:
	.long	prim_check_2_3.part.0
	.size	prim_check_2_3, .-prim_check_2_3
	.align 1
	.align 2
	.global	prim_check_2_4
	.type	prim_check_2_4, @function
prim_check_2_4:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L187
	mov.w	.L188,r2
	cmp/gt	r2,r1
	bf/s	.L185
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L185:
	mov.l	.L189,r1
	jmp	@r1
	nop
	.align 1
.L187:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L188:
	.short	252
.L190:
	.align 2
.L189:
	.long	prim_check_2_4.part.0
	.size	prim_check_2_4, .-prim_check_2_4
	.align 1
	.align 2
	.global	prim_check_2_5
	.type	prim_check_2_5, @function
prim_check_2_5:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L196
	mov.w	.L197,r2
	cmp/gt	r2,r1
	bf/s	.L194
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L194:
	mov.l	.L198,r1
	jmp	@r1
	nop
	.align 1
.L196:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L197:
	.short	251
.L199:
	.align 2
.L198:
	.long	prim_check_2_5.part.0
	.size	prim_check_2_5, .-prim_check_2_5
	.align 1
	.align 2
	.global	prim_check_2_6
	.type	prim_check_2_6, @function
prim_check_2_6:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L205
	mov.w	.L206,r2
	cmp/gt	r2,r1
	bf/s	.L203
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L203:
	mov.l	.L207,r1
	jmp	@r1
	nop
	.align 1
.L205:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L206:
	.short	250
.L208:
	.align 2
.L207:
	.long	prim_check_2_6.part.0
	.size	prim_check_2_6, .-prim_check_2_6
	.align 1
	.align 2
	.global	prim_check_2_7
	.type	prim_check_2_7, @function
prim_check_2_7:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L214
	mov.w	.L215,r2
	cmp/gt	r2,r1
	bf/s	.L212
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L212:
	mov.l	.L216,r1
	jmp	@r1
	nop
	.align 1
.L214:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L215:
	.short	249
.L217:
	.align 2
.L216:
	.long	prim_check_2_7.part.0
	.size	prim_check_2_7, .-prim_check_2_7
	.align 1
	.align 2
	.global	prim_check_3_0
	.type	prim_check_3_0, @function
prim_check_3_0:
	mov.l	@r4,r2
	mov	#2,r1
	cmp/gt	r1,r2
	bt/s	.L219
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L219:
	mov.l	.L223,r1
	jmp	@r1
	nop
.L224:
	.align 2
.L223:
	.long	prim_check_3_0.part.0
	.size	prim_check_3_0, .-prim_check_3_0
	.align 1
	.align 2
	.global	prim_check_3_1
	.type	prim_check_3_1, @function
prim_check_3_1:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L230
	mov.w	.L231,r2
	cmp/gt	r2,r1
	bf/s	.L228
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L228:
	mov.l	.L232,r1
	jmp	@r1
	nop
	.align 1
.L230:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L231:
	.short	255
.L233:
	.align 2
.L232:
	.long	prim_check_3_1.part.0
	.size	prim_check_3_1, .-prim_check_3_1
	.align 1
	.align 2
	.global	prim_check_3_2
	.type	prim_check_3_2, @function
prim_check_3_2:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L239
	mov.w	.L240,r2
	cmp/gt	r2,r1
	bf/s	.L237
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L237:
	mov.l	.L241,r1
	jmp	@r1
	nop
	.align 1
.L239:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L240:
	.short	254
.L242:
	.align 2
.L241:
	.long	prim_check_3_2.part.0
	.size	prim_check_3_2, .-prim_check_3_2
	.align 1
	.align 2
	.global	prim_check_3_3
	.type	prim_check_3_3, @function
prim_check_3_3:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L248
	mov.w	.L249,r2
	cmp/gt	r2,r1
	bf/s	.L246
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L246:
	mov.l	.L250,r1
	jmp	@r1
	nop
	.align 1
.L248:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L249:
	.short	253
.L251:
	.align 2
.L250:
	.long	prim_check_3_3.part.0
	.size	prim_check_3_3, .-prim_check_3_3
	.align 1
	.align 2
	.global	prim_check_3_4
	.type	prim_check_3_4, @function
prim_check_3_4:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L257
	mov.w	.L258,r2
	cmp/gt	r2,r1
	bf/s	.L255
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L255:
	mov.l	.L259,r1
	jmp	@r1
	nop
	.align 1
.L257:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L258:
	.short	252
.L260:
	.align 2
.L259:
	.long	prim_check_3_4.part.0
	.size	prim_check_3_4, .-prim_check_3_4
	.align 1
	.align 2
	.global	prim_check_3_5
	.type	prim_check_3_5, @function
prim_check_3_5:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L266
	mov.w	.L267,r2
	cmp/gt	r2,r1
	bf/s	.L264
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L264:
	mov.l	.L268,r1
	jmp	@r1
	nop
	.align 1
.L266:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L267:
	.short	251
.L269:
	.align 2
.L268:
	.long	prim_check_3_5.part.0
	.size	prim_check_3_5, .-prim_check_3_5
	.align 1
	.align 2
	.global	prim_check_3_6
	.type	prim_check_3_6, @function
prim_check_3_6:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L275
	mov.w	.L276,r2
	cmp/gt	r2,r1
	bf/s	.L273
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L273:
	mov.l	.L277,r1
	jmp	@r1
	nop
	.align 1
.L275:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L276:
	.short	250
.L278:
	.align 2
.L277:
	.long	prim_check_3_6.part.0
	.size	prim_check_3_6, .-prim_check_3_6
	.align 1
	.align 2
	.global	prim_check_3_7
	.type	prim_check_3_7, @function
prim_check_3_7:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bf	.L284
	mov.w	.L285,r2
	cmp/gt	r2,r1
	bf/s	.L282
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L282:
	mov.l	.L286,r1
	jmp	@r1
	nop
	.align 1
.L284:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L285:
	.short	249
.L287:
	.align 2
.L286:
	.long	prim_check_3_7.part.0
	.size	prim_check_3_7, .-prim_check_3_7
	.align 1
	.align 2
	.global	prim_check_4_0
	.type	prim_check_4_0, @function
prim_check_4_0:
	mov.l	@r4,r2
	mov	#3,r1
	cmp/gt	r1,r2
	bt/s	.L289
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L289:
	mov.l	.L293,r1
	jmp	@r1
	nop
.L294:
	.align 2
.L293:
	.long	prim_check_4_0.part.0
	.size	prim_check_4_0, .-prim_check_4_0
	.align 1
	.align 2
	.global	prim_check_4_1
	.type	prim_check_4_1, @function
prim_check_4_1:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L300
	mov.w	.L301,r2
	cmp/gt	r2,r1
	bf/s	.L298
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L298:
	mov.l	.L302,r1
	jmp	@r1
	nop
	.align 1
.L300:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L301:
	.short	255
.L303:
	.align 2
.L302:
	.long	prim_check_4_1.part.0
	.size	prim_check_4_1, .-prim_check_4_1
	.align 1
	.align 2
	.global	prim_check_4_2
	.type	prim_check_4_2, @function
prim_check_4_2:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L309
	mov.w	.L310,r2
	cmp/gt	r2,r1
	bf/s	.L307
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L307:
	mov.l	.L311,r1
	jmp	@r1
	nop
	.align 1
.L309:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L310:
	.short	254
.L312:
	.align 2
.L311:
	.long	prim_check_4_2.part.0
	.size	prim_check_4_2, .-prim_check_4_2
	.align 1
	.align 2
	.global	prim_check_4_3
	.type	prim_check_4_3, @function
prim_check_4_3:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L318
	mov.w	.L319,r2
	cmp/gt	r2,r1
	bf/s	.L316
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L316:
	mov.l	.L320,r1
	jmp	@r1
	nop
	.align 1
.L318:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L319:
	.short	253
.L321:
	.align 2
.L320:
	.long	prim_check_4_3.part.0
	.size	prim_check_4_3, .-prim_check_4_3
	.align 1
	.align 2
	.global	prim_check_4_4
	.type	prim_check_4_4, @function
prim_check_4_4:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L327
	mov.w	.L328,r2
	cmp/gt	r2,r1
	bf/s	.L325
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L325:
	mov.l	.L329,r1
	jmp	@r1
	nop
	.align 1
.L327:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L328:
	.short	252
.L330:
	.align 2
.L329:
	.long	prim_check_4_4.part.0
	.size	prim_check_4_4, .-prim_check_4_4
	.align 1
	.align 2
	.global	prim_check_4_5
	.type	prim_check_4_5, @function
prim_check_4_5:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L336
	mov.w	.L337,r2
	cmp/gt	r2,r1
	bf/s	.L334
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L334:
	mov.l	.L338,r1
	jmp	@r1
	nop
	.align 1
.L336:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L337:
	.short	251
.L339:
	.align 2
.L338:
	.long	prim_check_4_5.part.0
	.size	prim_check_4_5, .-prim_check_4_5
	.align 1
	.align 2
	.global	prim_check_4_6
	.type	prim_check_4_6, @function
prim_check_4_6:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L345
	mov.w	.L346,r2
	cmp/gt	r2,r1
	bf/s	.L343
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L343:
	mov.l	.L347,r1
	jmp	@r1
	nop
	.align 1
.L345:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L346:
	.short	250
.L348:
	.align 2
.L347:
	.long	prim_check_4_6.part.0
	.size	prim_check_4_6, .-prim_check_4_6
	.align 1
	.align 2
	.global	prim_check_4_7
	.type	prim_check_4_7, @function
prim_check_4_7:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bf	.L354
	mov.w	.L355,r2
	cmp/gt	r2,r1
	bf/s	.L352
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L352:
	mov.l	.L356,r1
	jmp	@r1
	nop
	.align 1
.L354:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L355:
	.short	249
.L357:
	.align 2
.L356:
	.long	prim_check_4_7.part.0
	.size	prim_check_4_7, .-prim_check_4_7
	.align 1
	.align 2
	.global	prim_check_5_0
	.type	prim_check_5_0, @function
prim_check_5_0:
	mov.l	@r4,r2
	mov	#4,r1
	cmp/gt	r1,r2
	bt/s	.L359
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L359:
	mov.l	.L363,r1
	jmp	@r1
	nop
.L364:
	.align 2
.L363:
	.long	prim_check_5_0.part.0
	.size	prim_check_5_0, .-prim_check_5_0
	.align 1
	.align 2
	.global	prim_check_5_1
	.type	prim_check_5_1, @function
prim_check_5_1:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L370
	mov.w	.L371,r2
	cmp/gt	r2,r1
	bf/s	.L368
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L368:
	mov.l	.L372,r1
	jmp	@r1
	nop
	.align 1
.L370:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L371:
	.short	255
.L373:
	.align 2
.L372:
	.long	prim_check_5_1.part.0
	.size	prim_check_5_1, .-prim_check_5_1
	.align 1
	.align 2
	.global	prim_check_5_2
	.type	prim_check_5_2, @function
prim_check_5_2:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L379
	mov.w	.L380,r2
	cmp/gt	r2,r1
	bf/s	.L377
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L377:
	mov.l	.L381,r1
	jmp	@r1
	nop
	.align 1
.L379:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L380:
	.short	254
.L382:
	.align 2
.L381:
	.long	prim_check_5_2.part.0
	.size	prim_check_5_2, .-prim_check_5_2
	.align 1
	.align 2
	.global	prim_check_5_3
	.type	prim_check_5_3, @function
prim_check_5_3:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L388
	mov.w	.L389,r2
	cmp/gt	r2,r1
	bf/s	.L386
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L386:
	mov.l	.L390,r1
	jmp	@r1
	nop
	.align 1
.L388:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L389:
	.short	253
.L391:
	.align 2
.L390:
	.long	prim_check_5_3.part.0
	.size	prim_check_5_3, .-prim_check_5_3
	.align 1
	.align 2
	.global	prim_check_5_4
	.type	prim_check_5_4, @function
prim_check_5_4:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L397
	mov.w	.L398,r2
	cmp/gt	r2,r1
	bf/s	.L395
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L395:
	mov.l	.L399,r1
	jmp	@r1
	nop
	.align 1
.L397:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L398:
	.short	252
.L400:
	.align 2
.L399:
	.long	prim_check_5_4.part.0
	.size	prim_check_5_4, .-prim_check_5_4
	.align 1
	.align 2
	.global	prim_check_5_5
	.type	prim_check_5_5, @function
prim_check_5_5:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L406
	mov.w	.L407,r2
	cmp/gt	r2,r1
	bf/s	.L404
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L404:
	mov.l	.L408,r1
	jmp	@r1
	nop
	.align 1
.L406:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L407:
	.short	251
.L409:
	.align 2
.L408:
	.long	prim_check_5_5.part.0
	.size	prim_check_5_5, .-prim_check_5_5
	.align 1
	.align 2
	.global	prim_check_5_6
	.type	prim_check_5_6, @function
prim_check_5_6:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L415
	mov.w	.L416,r2
	cmp/gt	r2,r1
	bf/s	.L413
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L413:
	mov.l	.L417,r1
	jmp	@r1
	nop
	.align 1
.L415:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L416:
	.short	250
.L418:
	.align 2
.L417:
	.long	prim_check_5_6.part.0
	.size	prim_check_5_6, .-prim_check_5_6
	.align 1
	.align 2
	.global	prim_check_5_7
	.type	prim_check_5_7, @function
prim_check_5_7:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bf	.L424
	mov.w	.L425,r2
	cmp/gt	r2,r1
	bf/s	.L422
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L422:
	mov.l	.L426,r1
	jmp	@r1
	nop
	.align 1
.L424:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L425:
	.short	249
.L427:
	.align 2
.L426:
	.long	prim_check_5_7.part.0
	.size	prim_check_5_7, .-prim_check_5_7
	.align 1
	.align 2
	.global	prim_check_6_0
	.type	prim_check_6_0, @function
prim_check_6_0:
	mov.l	@r4,r2
	mov	#5,r1
	cmp/gt	r1,r2
	bt/s	.L429
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L429:
	mov.l	.L433,r1
	jmp	@r1
	nop
.L434:
	.align 2
.L433:
	.long	prim_check_6_0.part.0
	.size	prim_check_6_0, .-prim_check_6_0
	.align 1
	.align 2
	.global	prim_check_6_1
	.type	prim_check_6_1, @function
prim_check_6_1:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L440
	mov.w	.L441,r2
	cmp/gt	r2,r1
	bf/s	.L438
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L438:
	mov.l	.L442,r1
	jmp	@r1
	nop
	.align 1
.L440:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L441:
	.short	255
.L443:
	.align 2
.L442:
	.long	prim_check_6_1.part.0
	.size	prim_check_6_1, .-prim_check_6_1
	.align 1
	.align 2
	.global	prim_check_6_2
	.type	prim_check_6_2, @function
prim_check_6_2:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L449
	mov.w	.L450,r2
	cmp/gt	r2,r1
	bf/s	.L447
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L447:
	mov.l	.L451,r1
	jmp	@r1
	nop
	.align 1
.L449:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L450:
	.short	254
.L452:
	.align 2
.L451:
	.long	prim_check_6_2.part.0
	.size	prim_check_6_2, .-prim_check_6_2
	.align 1
	.align 2
	.global	prim_check_6_3
	.type	prim_check_6_3, @function
prim_check_6_3:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L458
	mov.w	.L459,r2
	cmp/gt	r2,r1
	bf/s	.L456
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L456:
	mov.l	.L460,r1
	jmp	@r1
	nop
	.align 1
.L458:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L459:
	.short	253
.L461:
	.align 2
.L460:
	.long	prim_check_6_3.part.0
	.size	prim_check_6_3, .-prim_check_6_3
	.align 1
	.align 2
	.global	prim_check_6_4
	.type	prim_check_6_4, @function
prim_check_6_4:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L467
	mov.w	.L468,r2
	cmp/gt	r2,r1
	bf/s	.L465
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L465:
	mov.l	.L469,r1
	jmp	@r1
	nop
	.align 1
.L467:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L468:
	.short	252
.L470:
	.align 2
.L469:
	.long	prim_check_6_4.part.0
	.size	prim_check_6_4, .-prim_check_6_4
	.align 1
	.align 2
	.global	prim_check_6_5
	.type	prim_check_6_5, @function
prim_check_6_5:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L476
	mov.w	.L477,r2
	cmp/gt	r2,r1
	bf/s	.L474
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L474:
	mov.l	.L478,r1
	jmp	@r1
	nop
	.align 1
.L476:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L477:
	.short	251
.L479:
	.align 2
.L478:
	.long	prim_check_6_5.part.0
	.size	prim_check_6_5, .-prim_check_6_5
	.align 1
	.align 2
	.global	prim_check_6_6
	.type	prim_check_6_6, @function
prim_check_6_6:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L485
	mov.w	.L486,r2
	cmp/gt	r2,r1
	bf/s	.L483
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L483:
	mov.l	.L487,r1
	jmp	@r1
	nop
	.align 1
.L485:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L486:
	.short	250
.L488:
	.align 2
.L487:
	.long	prim_check_6_6.part.0
	.size	prim_check_6_6, .-prim_check_6_6
	.align 1
	.align 2
	.global	prim_check_6_7
	.type	prim_check_6_7, @function
prim_check_6_7:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bf	.L494
	mov.w	.L495,r2
	cmp/gt	r2,r1
	bf/s	.L492
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L492:
	mov.l	.L496,r1
	jmp	@r1
	nop
	.align 1
.L494:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L495:
	.short	249
.L497:
	.align 2
.L496:
	.long	prim_check_6_7.part.0
	.size	prim_check_6_7, .-prim_check_6_7
	.align 1
	.align 2
	.global	prim_check_7_0
	.type	prim_check_7_0, @function
prim_check_7_0:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt/s	.L499
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L499:
	mov.l	.L503,r1
	jmp	@r1
	nop
.L504:
	.align 2
.L503:
	.long	prim_check_7_0.part.0
	.size	prim_check_7_0, .-prim_check_7_0
	.align 1
	.align 2
	.global	prim_check_7_1
	.type	prim_check_7_1, @function
prim_check_7_1:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L510
	mov.w	.L511,r3
	cmp/gt	r3,r1
	bf/s	.L508
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L508:
	mov.l	.L512,r1
	jmp	@r1
	nop
	.align 1
.L510:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L511:
	.short	255
.L513:
	.align 2
.L512:
	.long	prim_check_7_1.part.0
	.size	prim_check_7_1, .-prim_check_7_1
	.align 1
	.align 2
	.global	prim_check_7_2
	.type	prim_check_7_2, @function
prim_check_7_2:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L519
	mov.w	.L520,r3
	cmp/gt	r3,r1
	bf/s	.L517
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L517:
	mov.l	.L521,r1
	jmp	@r1
	nop
	.align 1
.L519:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L520:
	.short	254
.L522:
	.align 2
.L521:
	.long	prim_check_7_2.part.0
	.size	prim_check_7_2, .-prim_check_7_2
	.align 1
	.align 2
	.global	prim_check_7_3
	.type	prim_check_7_3, @function
prim_check_7_3:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L528
	mov.w	.L529,r3
	cmp/gt	r3,r1
	bf/s	.L526
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L526:
	mov.l	.L530,r1
	jmp	@r1
	nop
	.align 1
.L528:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L529:
	.short	253
.L531:
	.align 2
.L530:
	.long	prim_check_7_3.part.0
	.size	prim_check_7_3, .-prim_check_7_3
	.align 1
	.align 2
	.global	prim_check_7_4
	.type	prim_check_7_4, @function
prim_check_7_4:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L537
	mov.w	.L538,r3
	cmp/gt	r3,r1
	bf/s	.L535
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L535:
	mov.l	.L539,r1
	jmp	@r1
	nop
	.align 1
.L537:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L538:
	.short	252
.L540:
	.align 2
.L539:
	.long	prim_check_7_4.part.0
	.size	prim_check_7_4, .-prim_check_7_4
	.align 1
	.align 2
	.global	prim_check_7_5
	.type	prim_check_7_5, @function
prim_check_7_5:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L546
	mov.w	.L547,r3
	cmp/gt	r3,r1
	bf/s	.L544
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L544:
	mov.l	.L548,r1
	jmp	@r1
	nop
	.align 1
.L546:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L547:
	.short	251
.L549:
	.align 2
.L548:
	.long	prim_check_7_5.part.0
	.size	prim_check_7_5, .-prim_check_7_5
	.align 1
	.align 2
	.global	prim_check_7_6
	.type	prim_check_7_6, @function
prim_check_7_6:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L555
	mov.w	.L556,r3
	cmp/gt	r3,r1
	bf/s	.L553
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L553:
	mov.l	.L557,r1
	jmp	@r1
	nop
	.align 1
.L555:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L556:
	.short	250
.L558:
	.align 2
.L557:
	.long	prim_check_7_6.part.0
	.size	prim_check_7_6, .-prim_check_7_6
	.align 1
	.align 2
	.global	prim_check_7_7
	.type	prim_check_7_7, @function
prim_check_7_7:
	mov.l	@r4,r1
	mov	#6,r2
	cmp/gt	r2,r1
	bf	.L564
	mov.w	.L565,r3
	cmp/gt	r3,r1
	bf/s	.L562
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L562:
	mov.l	.L566,r1
	jmp	@r1
	nop
	.align 1
.L564:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(24,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L565:
	.short	249
.L567:
	.align 2
.L566:
	.long	prim_check_7_7.part.0
	.size	prim_check_7_7, .-prim_check_7_7
	.global	forth_checks
	.data
	.align 2
	.type	forth_checks, @object
	.size	forth_checks, 256
forth_checks:
	.long	prim_check_0_0
	.long	prim_check_0_1
	.long	prim_check_0_2
	.long	prim_check_0_3
	.long	prim_check_0_4
	.long	prim_check_0_5
	.long	prim_check_0_6
	.long	prim_check_0_7
	.long	prim_check_1_0
	.long	prim_check_1_1
	.long	prim_check_1_2
	.long	prim_check_1_3
	.long	prim_check_1_4
	.long	prim_check_1_5
	.long	prim_check_1_6
	.long	prim_check_1_7
	.long	prim_check_2_0
	.long	prim_check_2_1
	.long	prim_check_2_2
	.long	prim_check_2_3
	.long	prim_check_2_4
	.long	prim_check_2_5
	.long	prim_check_2_6
	.long	prim_check_2_7
	.long	prim_check_3_0
	.long	prim_check_3_1
	.long	prim_check_3_2
	.long	prim_check_3_3
	.long	prim_check_3_4
	.long	prim_check_3_5
	.long	prim_check_3_6
	.long	prim_check_3_7
	.long	prim_check_4_0
	.long	prim_check_4_1
	.long	prim_check_4_2
	.long	prim_check_4_3
	.long	prim_check_4_4
	.long	prim_check_4_5
	.long	prim_check_4_6
	.long	prim_check_4_7
	.long	prim_check_5_0
	.long	prim_check_5_1
	.long	prim_check_5_2
	.long	prim_check_5_3
	.long	prim_check_5_4
	.long	prim_check_5_5
	.long	prim_check_5_6
	.long	prim_check_5_7
	.long	prim_check_6_0
	.long	prim_check_6_1
	.long	prim_check_6_2
	.long	prim_check_6_3
	.long	prim_check_6_4
	.long	prim_check_6_5
	.long	prim_check_6_6
	.long	prim_check_6_7
	.long	prim_check_7_0
	.long	prim_check_7_1
	.long	prim_check_7_2
	.long	prim_check_7_3
	.long	prim_check_7_4
	.long	prim_check_7_5
	.long	prim_check_7_6
	.long	prim_check_7_7
	.ident	"GCC: (GNU) 15.1.0"
	.section	.note.GNU-stack,"",@progbits
