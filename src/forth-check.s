	.file	"forth-check.c"
	.text
	.text
	.align 1
	.align 2
	.global	prim_check_0_0
	.type	prim_check_0_0, @function
prim_check_0_0:
	rts	
	nop
	.size	prim_check_0_0, .-prim_check_0_0
	.align 1
	.align 2
	.global	prim_check_0_1
	.type	prim_check_0_1, @function
prim_check_0_1:
	mov.l	@r4,r2
	mov.w	.L6,r1
	cmp/gt	r1,r2
	bf/s	.L5
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L5:
	rts	
	nop
	.align 1
.L6:
	.short	255
	.size	prim_check_0_1, .-prim_check_0_1
	.align 1
	.align 2
	.global	prim_check_0_2
	.type	prim_check_0_2, @function
prim_check_0_2:
	mov.l	@r4,r2
	mov.w	.L10,r1
	cmp/gt	r1,r2
	bf/s	.L9
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L9:
	rts	
	nop
	.align 1
.L10:
	.short	254
	.size	prim_check_0_2, .-prim_check_0_2
	.align 1
	.align 2
	.global	prim_check_0_3
	.type	prim_check_0_3, @function
prim_check_0_3:
	mov.l	@r4,r2
	mov.w	.L14,r1
	cmp/gt	r1,r2
	bf/s	.L13
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L13:
	rts	
	nop
	.align 1
.L14:
	.short	253
	.size	prim_check_0_3, .-prim_check_0_3
	.align 1
	.align 2
	.global	prim_check_0_4
	.type	prim_check_0_4, @function
prim_check_0_4:
	mov.l	@r4,r2
	mov.w	.L18,r1
	cmp/gt	r1,r2
	bf/s	.L17
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L17:
	rts	
	nop
	.align 1
.L18:
	.short	252
	.size	prim_check_0_4, .-prim_check_0_4
	.align 1
	.align 2
	.global	prim_check_0_5
	.type	prim_check_0_5, @function
prim_check_0_5:
	mov.l	@r4,r2
	mov.w	.L22,r1
	cmp/gt	r1,r2
	bf/s	.L21
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L21:
	rts	
	nop
	.align 1
.L22:
	.short	251
	.size	prim_check_0_5, .-prim_check_0_5
	.align 1
	.align 2
	.global	prim_check_0_6
	.type	prim_check_0_6, @function
prim_check_0_6:
	mov.l	@r4,r2
	mov.w	.L26,r1
	cmp/gt	r1,r2
	bf/s	.L25
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L25:
	rts	
	nop
	.align 1
.L26:
	.short	250
	.size	prim_check_0_6, .-prim_check_0_6
	.align 1
	.align 2
	.global	prim_check_0_7
	.type	prim_check_0_7, @function
prim_check_0_7:
	mov.l	@r4,r2
	mov.w	.L30,r1
	cmp/gt	r1,r2
	bf/s	.L29
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L29:
	rts	
	nop
	.align 1
.L30:
	.short	249
	.size	prim_check_0_7, .-prim_check_0_7
	.align 1
	.align 2
	.global	prim_check_1_0
	.type	prim_check_1_0, @function
prim_check_1_0:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L34
	mov	#10,r2
	rts	
	nop
	.align 1
.L34:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.size	prim_check_1_0, .-prim_check_1_0
	.align 1
	.align 2
	.global	prim_check_1_1
	.type	prim_check_1_1, @function
prim_check_1_1:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L39
	mov	#10,r2
	mov.w	.L40,r2
	cmp/gt	r2,r1
	bf/s	.L38
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L38:
	rts	
	nop
	.align 1
.L39:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L40:
	.short	255
	.size	prim_check_1_1, .-prim_check_1_1
	.align 1
	.align 2
	.global	prim_check_1_2
	.type	prim_check_1_2, @function
prim_check_1_2:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L45
	mov	#10,r2
	mov.w	.L46,r2
	cmp/gt	r2,r1
	bf/s	.L44
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L44:
	rts	
	nop
	.align 1
.L45:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L46:
	.short	254
	.size	prim_check_1_2, .-prim_check_1_2
	.align 1
	.align 2
	.global	prim_check_1_3
	.type	prim_check_1_3, @function
prim_check_1_3:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L51
	mov	#10,r2
	mov.w	.L52,r2
	cmp/gt	r2,r1
	bf/s	.L50
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L50:
	rts	
	nop
	.align 1
.L51:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L52:
	.short	253
	.size	prim_check_1_3, .-prim_check_1_3
	.align 1
	.align 2
	.global	prim_check_1_4
	.type	prim_check_1_4, @function
prim_check_1_4:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L57
	mov	#10,r2
	mov.w	.L58,r2
	cmp/gt	r2,r1
	bf/s	.L56
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L56:
	rts	
	nop
	.align 1
.L57:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L58:
	.short	252
	.size	prim_check_1_4, .-prim_check_1_4
	.align 1
	.align 2
	.global	prim_check_1_5
	.type	prim_check_1_5, @function
prim_check_1_5:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L63
	mov	#10,r2
	mov.w	.L64,r2
	cmp/gt	r2,r1
	bf/s	.L62
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L62:
	rts	
	nop
	.align 1
.L63:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L64:
	.short	251
	.size	prim_check_1_5, .-prim_check_1_5
	.align 1
	.align 2
	.global	prim_check_1_6
	.type	prim_check_1_6, @function
prim_check_1_6:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L69
	mov	#10,r2
	mov.w	.L70,r2
	cmp/gt	r2,r1
	bf/s	.L68
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L68:
	rts	
	nop
	.align 1
.L69:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L70:
	.short	250
	.size	prim_check_1_6, .-prim_check_1_6
	.align 1
	.align 2
	.global	prim_check_1_7
	.type	prim_check_1_7, @function
prim_check_1_7:
	mov.l	@r4,r1
	cmp/pl	r1
	bf/s	.L75
	mov	#10,r2
	mov.w	.L76,r2
	cmp/gt	r2,r1
	bf/s	.L74
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L74:
	rts	
	nop
	.align 1
.L75:
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L76:
	.short	249
	.size	prim_check_1_7, .-prim_check_1_7
	.align 1
	.align 2
	.global	prim_check_2_0
	.type	prim_check_2_0, @function
prim_check_2_0:
	mov.l	@r4,r2
	mov	#1,r1
	cmp/gt	r1,r2
	bf	.L80
	rts	
	nop
	.align 1
.L80:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.size	prim_check_2_0, .-prim_check_2_0
	.align 1
	.align 2
	.global	prim_check_2_1
	.type	prim_check_2_1, @function
prim_check_2_1:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L85
	mov.w	.L86,r2
	cmp/gt	r2,r1
	bf/s	.L84
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L84:
	rts	
	nop
	.align 1
.L85:
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
.L86:
	.short	255
	.size	prim_check_2_1, .-prim_check_2_1
	.align 1
	.align 2
	.global	prim_check_2_2
	.type	prim_check_2_2, @function
prim_check_2_2:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L91
	mov.w	.L92,r2
	cmp/gt	r2,r1
	bf/s	.L90
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L90:
	rts	
	nop
	.align 1
.L91:
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
.L92:
	.short	254
	.size	prim_check_2_2, .-prim_check_2_2
	.align 1
	.align 2
	.global	prim_check_2_3
	.type	prim_check_2_3, @function
prim_check_2_3:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L97
	mov.w	.L98,r2
	cmp/gt	r2,r1
	bf/s	.L96
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L96:
	rts	
	nop
	.align 1
.L97:
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
.L98:
	.short	253
	.size	prim_check_2_3, .-prim_check_2_3
	.align 1
	.align 2
	.global	prim_check_2_4
	.type	prim_check_2_4, @function
prim_check_2_4:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L103
	mov.w	.L104,r2
	cmp/gt	r2,r1
	bf/s	.L102
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L102:
	rts	
	nop
	.align 1
.L103:
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
.L104:
	.short	252
	.size	prim_check_2_4, .-prim_check_2_4
	.align 1
	.align 2
	.global	prim_check_2_5
	.type	prim_check_2_5, @function
prim_check_2_5:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L109
	mov.w	.L110,r2
	cmp/gt	r2,r1
	bf/s	.L108
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L108:
	rts	
	nop
	.align 1
.L109:
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
.L110:
	.short	251
	.size	prim_check_2_5, .-prim_check_2_5
	.align 1
	.align 2
	.global	prim_check_2_6
	.type	prim_check_2_6, @function
prim_check_2_6:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L115
	mov.w	.L116,r2
	cmp/gt	r2,r1
	bf/s	.L114
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L114:
	rts	
	nop
	.align 1
.L115:
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
.L116:
	.short	250
	.size	prim_check_2_6, .-prim_check_2_6
	.align 1
	.align 2
	.global	prim_check_2_7
	.type	prim_check_2_7, @function
prim_check_2_7:
	mov.l	@r4,r1
	mov	#1,r2
	cmp/gt	r2,r1
	bf	.L121
	mov.w	.L122,r2
	cmp/gt	r2,r1
	bf/s	.L120
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L120:
	rts	
	nop
	.align 1
.L121:
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
.L122:
	.short	249
	.size	prim_check_2_7, .-prim_check_2_7
	.align 1
	.align 2
	.global	prim_check_3_0
	.type	prim_check_3_0, @function
prim_check_3_0:
	mov.l	@r4,r2
	mov	#2,r1
	cmp/gt	r1,r2
	bt/s	.L125
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L125:
	rts	
	nop
	.size	prim_check_3_0, .-prim_check_3_0
	.align 1
	.align 2
	.global	prim_check_3_1
	.type	prim_check_3_1, @function
prim_check_3_1:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L127
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L127:
	mov.w	.L130,r2
	cmp/gt	r2,r1
	bf/s	.L129
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L129:
	rts	
	nop
	.align 1
.L130:
	.short	255
	.size	prim_check_3_1, .-prim_check_3_1
	.align 1
	.align 2
	.global	prim_check_3_2
	.type	prim_check_3_2, @function
prim_check_3_2:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L132
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L132:
	mov.w	.L135,r2
	cmp/gt	r2,r1
	bf/s	.L134
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L134:
	rts	
	nop
	.align 1
.L135:
	.short	254
	.size	prim_check_3_2, .-prim_check_3_2
	.align 1
	.align 2
	.global	prim_check_3_3
	.type	prim_check_3_3, @function
prim_check_3_3:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L137
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L137:
	mov.w	.L140,r2
	cmp/gt	r2,r1
	bf/s	.L139
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L139:
	rts	
	nop
	.align 1
.L140:
	.short	253
	.size	prim_check_3_3, .-prim_check_3_3
	.align 1
	.align 2
	.global	prim_check_3_4
	.type	prim_check_3_4, @function
prim_check_3_4:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L142
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L142:
	mov.w	.L145,r2
	cmp/gt	r2,r1
	bf/s	.L144
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L144:
	rts	
	nop
	.align 1
.L145:
	.short	252
	.size	prim_check_3_4, .-prim_check_3_4
	.align 1
	.align 2
	.global	prim_check_3_5
	.type	prim_check_3_5, @function
prim_check_3_5:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L147
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L147:
	mov.w	.L150,r2
	cmp/gt	r2,r1
	bf/s	.L149
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L149:
	rts	
	nop
	.align 1
.L150:
	.short	251
	.size	prim_check_3_5, .-prim_check_3_5
	.align 1
	.align 2
	.global	prim_check_3_6
	.type	prim_check_3_6, @function
prim_check_3_6:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L152
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L152:
	mov.w	.L155,r2
	cmp/gt	r2,r1
	bf/s	.L154
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L154:
	rts	
	nop
	.align 1
.L155:
	.short	250
	.size	prim_check_3_6, .-prim_check_3_6
	.align 1
	.align 2
	.global	prim_check_3_7
	.type	prim_check_3_7, @function
prim_check_3_7:
	mov.l	@r4,r1
	mov	#2,r2
	cmp/gt	r2,r1
	bt/s	.L157
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L157:
	mov.w	.L160,r2
	cmp/gt	r2,r1
	bf/s	.L159
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L159:
	rts	
	nop
	.align 1
.L160:
	.short	249
	.size	prim_check_3_7, .-prim_check_3_7
	.align 1
	.align 2
	.global	prim_check_4_0
	.type	prim_check_4_0, @function
prim_check_4_0:
	mov.l	@r4,r2
	mov	#3,r1
	cmp/gt	r1,r2
	bt/s	.L163
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L163:
	rts	
	nop
	.size	prim_check_4_0, .-prim_check_4_0
	.align 1
	.align 2
	.global	prim_check_4_1
	.type	prim_check_4_1, @function
prim_check_4_1:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L165
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L165:
	mov.w	.L168,r2
	cmp/gt	r2,r1
	bf/s	.L167
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L167:
	rts	
	nop
	.align 1
.L168:
	.short	255
	.size	prim_check_4_1, .-prim_check_4_1
	.align 1
	.align 2
	.global	prim_check_4_2
	.type	prim_check_4_2, @function
prim_check_4_2:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L170
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L170:
	mov.w	.L173,r2
	cmp/gt	r2,r1
	bf/s	.L172
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L172:
	rts	
	nop
	.align 1
.L173:
	.short	254
	.size	prim_check_4_2, .-prim_check_4_2
	.align 1
	.align 2
	.global	prim_check_4_3
	.type	prim_check_4_3, @function
prim_check_4_3:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L175
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L175:
	mov.w	.L178,r2
	cmp/gt	r2,r1
	bf/s	.L177
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L177:
	rts	
	nop
	.align 1
.L178:
	.short	253
	.size	prim_check_4_3, .-prim_check_4_3
	.align 1
	.align 2
	.global	prim_check_4_4
	.type	prim_check_4_4, @function
prim_check_4_4:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L180
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L180:
	mov.w	.L183,r2
	cmp/gt	r2,r1
	bf/s	.L182
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L182:
	rts	
	nop
	.align 1
.L183:
	.short	252
	.size	prim_check_4_4, .-prim_check_4_4
	.align 1
	.align 2
	.global	prim_check_4_5
	.type	prim_check_4_5, @function
prim_check_4_5:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L185
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L185:
	mov.w	.L188,r2
	cmp/gt	r2,r1
	bf/s	.L187
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L187:
	rts	
	nop
	.align 1
.L188:
	.short	251
	.size	prim_check_4_5, .-prim_check_4_5
	.align 1
	.align 2
	.global	prim_check_4_6
	.type	prim_check_4_6, @function
prim_check_4_6:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L190
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L190:
	mov.w	.L193,r2
	cmp/gt	r2,r1
	bf/s	.L192
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L192:
	rts	
	nop
	.align 1
.L193:
	.short	250
	.size	prim_check_4_6, .-prim_check_4_6
	.align 1
	.align 2
	.global	prim_check_4_7
	.type	prim_check_4_7, @function
prim_check_4_7:
	mov.l	@r4,r1
	mov	#3,r2
	cmp/gt	r2,r1
	bt/s	.L195
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L195:
	mov.w	.L198,r2
	cmp/gt	r2,r1
	bf/s	.L197
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L197:
	rts	
	nop
	.align 1
.L198:
	.short	249
	.size	prim_check_4_7, .-prim_check_4_7
	.align 1
	.align 2
	.global	prim_check_5_0
	.type	prim_check_5_0, @function
prim_check_5_0:
	mov.l	@r4,r2
	mov	#4,r1
	cmp/gt	r1,r2
	bt/s	.L201
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L201:
	rts	
	nop
	.size	prim_check_5_0, .-prim_check_5_0
	.align 1
	.align 2
	.global	prim_check_5_1
	.type	prim_check_5_1, @function
prim_check_5_1:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L203
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L203:
	mov.w	.L206,r2
	cmp/gt	r2,r1
	bf/s	.L205
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L205:
	rts	
	nop
	.align 1
.L206:
	.short	255
	.size	prim_check_5_1, .-prim_check_5_1
	.align 1
	.align 2
	.global	prim_check_5_2
	.type	prim_check_5_2, @function
prim_check_5_2:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L208
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L208:
	mov.w	.L211,r2
	cmp/gt	r2,r1
	bf/s	.L210
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L210:
	rts	
	nop
	.align 1
.L211:
	.short	254
	.size	prim_check_5_2, .-prim_check_5_2
	.align 1
	.align 2
	.global	prim_check_5_3
	.type	prim_check_5_3, @function
prim_check_5_3:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L213
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L213:
	mov.w	.L216,r2
	cmp/gt	r2,r1
	bf/s	.L215
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L215:
	rts	
	nop
	.align 1
.L216:
	.short	253
	.size	prim_check_5_3, .-prim_check_5_3
	.align 1
	.align 2
	.global	prim_check_5_4
	.type	prim_check_5_4, @function
prim_check_5_4:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L218
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L218:
	mov.w	.L221,r2
	cmp/gt	r2,r1
	bf/s	.L220
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L220:
	rts	
	nop
	.align 1
.L221:
	.short	252
	.size	prim_check_5_4, .-prim_check_5_4
	.align 1
	.align 2
	.global	prim_check_5_5
	.type	prim_check_5_5, @function
prim_check_5_5:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L223
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L223:
	mov.w	.L226,r2
	cmp/gt	r2,r1
	bf/s	.L225
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L225:
	rts	
	nop
	.align 1
.L226:
	.short	251
	.size	prim_check_5_5, .-prim_check_5_5
	.align 1
	.align 2
	.global	prim_check_5_6
	.type	prim_check_5_6, @function
prim_check_5_6:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L228
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L228:
	mov.w	.L231,r2
	cmp/gt	r2,r1
	bf/s	.L230
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L230:
	rts	
	nop
	.align 1
.L231:
	.short	250
	.size	prim_check_5_6, .-prim_check_5_6
	.align 1
	.align 2
	.global	prim_check_5_7
	.type	prim_check_5_7, @function
prim_check_5_7:
	mov.l	@r4,r1
	mov	#4,r2
	cmp/gt	r2,r1
	bt/s	.L233
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L233:
	mov.w	.L236,r2
	cmp/gt	r2,r1
	bf/s	.L235
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L235:
	rts	
	nop
	.align 1
.L236:
	.short	249
	.size	prim_check_5_7, .-prim_check_5_7
	.align 1
	.align 2
	.global	prim_check_6_0
	.type	prim_check_6_0, @function
prim_check_6_0:
	mov.l	@r4,r2
	mov	#5,r1
	cmp/gt	r1,r2
	bt/s	.L239
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L239:
	rts	
	nop
	.size	prim_check_6_0, .-prim_check_6_0
	.align 1
	.align 2
	.global	prim_check_6_1
	.type	prim_check_6_1, @function
prim_check_6_1:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L241
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L241:
	mov.w	.L244,r2
	cmp/gt	r2,r1
	bf/s	.L243
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L243:
	rts	
	nop
	.align 1
.L244:
	.short	255
	.size	prim_check_6_1, .-prim_check_6_1
	.align 1
	.align 2
	.global	prim_check_6_2
	.type	prim_check_6_2, @function
prim_check_6_2:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L246
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L246:
	mov.w	.L249,r2
	cmp/gt	r2,r1
	bf/s	.L248
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L248:
	rts	
	nop
	.align 1
.L249:
	.short	254
	.size	prim_check_6_2, .-prim_check_6_2
	.align 1
	.align 2
	.global	prim_check_6_3
	.type	prim_check_6_3, @function
prim_check_6_3:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L251
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L251:
	mov.w	.L254,r2
	cmp/gt	r2,r1
	bf/s	.L253
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L253:
	rts	
	nop
	.align 1
.L254:
	.short	253
	.size	prim_check_6_3, .-prim_check_6_3
	.align 1
	.align 2
	.global	prim_check_6_4
	.type	prim_check_6_4, @function
prim_check_6_4:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L256
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L256:
	mov.w	.L259,r2
	cmp/gt	r2,r1
	bf/s	.L258
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L258:
	rts	
	nop
	.align 1
.L259:
	.short	252
	.size	prim_check_6_4, .-prim_check_6_4
	.align 1
	.align 2
	.global	prim_check_6_5
	.type	prim_check_6_5, @function
prim_check_6_5:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L261
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L261:
	mov.w	.L264,r2
	cmp/gt	r2,r1
	bf/s	.L263
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L263:
	rts	
	nop
	.align 1
.L264:
	.short	251
	.size	prim_check_6_5, .-prim_check_6_5
	.align 1
	.align 2
	.global	prim_check_6_6
	.type	prim_check_6_6, @function
prim_check_6_6:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L266
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L266:
	mov.w	.L269,r2
	cmp/gt	r2,r1
	bf/s	.L268
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L268:
	rts	
	nop
	.align 1
.L269:
	.short	250
	.size	prim_check_6_6, .-prim_check_6_6
	.align 1
	.align 2
	.global	prim_check_6_7
	.type	prim_check_6_7, @function
prim_check_6_7:
	mov.l	@r4,r1
	mov	#5,r2
	cmp/gt	r2,r1
	bt/s	.L271
	mov	#10,r2
	mov	r4,r1
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.align 1
.L271:
	mov.w	.L274,r2
	cmp/gt	r2,r1
	bf/s	.L273
	mov	r4,r1
	mov	#6,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L273:
	rts	
	nop
	.align 1
.L274:
	.short	249
	.size	prim_check_6_7, .-prim_check_6_7
	.align 1
	.align 2
	.global	prim_check_7_0
	.type	prim_check_7_0, @function
prim_check_7_0:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt/s	.L277
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L277:
	rts	
	nop
	.size	prim_check_7_0, .-prim_check_7_0
	.align 1
	.align 2
	.global	prim_check_7_1
	.type	prim_check_7_1, @function
prim_check_7_1:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L279
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
.L279:
	mov.w	.L282,r3
	cmp/gt	r3,r2
	bf/s	.L281
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L281:
	rts	
	nop
	.align 1
.L282:
	.short	255
	.size	prim_check_7_1, .-prim_check_7_1
	.align 1
	.align 2
	.global	prim_check_7_2
	.type	prim_check_7_2, @function
prim_check_7_2:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L284
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
.L284:
	mov.w	.L287,r3
	cmp/gt	r3,r2
	bf/s	.L286
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L286:
	rts	
	nop
	.align 1
.L287:
	.short	254
	.size	prim_check_7_2, .-prim_check_7_2
	.align 1
	.align 2
	.global	prim_check_7_3
	.type	prim_check_7_3, @function
prim_check_7_3:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L289
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
.L289:
	mov.w	.L292,r3
	cmp/gt	r3,r2
	bf/s	.L291
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L291:
	rts	
	nop
	.align 1
.L292:
	.short	253
	.size	prim_check_7_3, .-prim_check_7_3
	.align 1
	.align 2
	.global	prim_check_7_4
	.type	prim_check_7_4, @function
prim_check_7_4:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L294
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
.L294:
	mov.w	.L297,r3
	cmp/gt	r3,r2
	bf/s	.L296
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L296:
	rts	
	nop
	.align 1
.L297:
	.short	252
	.size	prim_check_7_4, .-prim_check_7_4
	.align 1
	.align 2
	.global	prim_check_7_5
	.type	prim_check_7_5, @function
prim_check_7_5:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L299
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
.L299:
	mov.w	.L302,r3
	cmp/gt	r3,r2
	bf/s	.L301
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L301:
	rts	
	nop
	.align 1
.L302:
	.short	251
	.size	prim_check_7_5, .-prim_check_7_5
	.align 1
	.align 2
	.global	prim_check_7_6
	.type	prim_check_7_6, @function
prim_check_7_6:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L304
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
.L304:
	mov.w	.L307,r3
	cmp/gt	r3,r2
	bf/s	.L306
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L306:
	rts	
	nop
	.align 1
.L307:
	.short	250
	.size	prim_check_7_6, .-prim_check_7_6
	.align 1
	.align 2
	.global	prim_check_7_7
	.type	prim_check_7_7, @function
prim_check_7_7:
	mov.l	@r4,r2
	mov	#6,r1
	cmp/gt	r1,r2
	bt	.L309
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
.L309:
	mov.w	.L312,r3
	cmp/gt	r3,r2
	bf/s	.L311
	mov	r4,r2
	add	#124,r2
	mov.l	r1,@(4,r2)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
.L311:
	rts	
	nop
	.align 1
.L312:
	.short	249
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
