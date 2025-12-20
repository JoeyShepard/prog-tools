	.file	"forth-locals.c"
	.text
	.text
	.align 1
	.align 2
	.global	prim_local_fetch0
	.type	prim_local_fetch0, @function
prim_local_fetch0:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@r1,r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch0, .-prim_local_fetch0
	.align 1
	.align 2
	.global	prim_local_fetch1
	.type	prim_local_fetch1, @function
prim_local_fetch1:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(4,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch1, .-prim_local_fetch1
	.align 1
	.align 2
	.global	prim_local_fetch2
	.type	prim_local_fetch2, @function
prim_local_fetch2:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(8,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch2, .-prim_local_fetch2
	.align 1
	.align 2
	.global	prim_local_fetch3
	.type	prim_local_fetch3, @function
prim_local_fetch3:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(12,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch3, .-prim_local_fetch3
	.align 1
	.align 2
	.global	prim_local_fetch4
	.type	prim_local_fetch4, @function
prim_local_fetch4:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(16,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch4, .-prim_local_fetch4
	.align 1
	.align 2
	.global	prim_local_fetch5
	.type	prim_local_fetch5, @function
prim_local_fetch5:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(20,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch5, .-prim_local_fetch5
	.align 1
	.align 2
	.global	prim_local_fetch6
	.type	prim_local_fetch6, @function
prim_local_fetch6:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(24,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch6, .-prim_local_fetch6
	.align 1
	.align 2
	.global	prim_local_fetch7
	.type	prim_local_fetch7, @function
prim_local_fetch7:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(28,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch7, .-prim_local_fetch7
	.align 1
	.align 2
	.global	prim_local_fetch8
	.type	prim_local_fetch8, @function
prim_local_fetch8:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(32,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch8, .-prim_local_fetch8
	.align 1
	.align 2
	.global	prim_local_fetch9
	.type	prim_local_fetch9, @function
prim_local_fetch9:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(36,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch9, .-prim_local_fetch9
	.align 1
	.align 2
	.global	prim_local_fetch10
	.type	prim_local_fetch10, @function
prim_local_fetch10:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(40,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch10, .-prim_local_fetch10
	.align 1
	.align 2
	.global	prim_local_fetch11
	.type	prim_local_fetch11, @function
prim_local_fetch11:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(44,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch11, .-prim_local_fetch11
	.align 1
	.align 2
	.global	prim_local_fetch12
	.type	prim_local_fetch12, @function
prim_local_fetch12:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(48,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch12, .-prim_local_fetch12
	.align 1
	.align 2
	.global	prim_local_fetch13
	.type	prim_local_fetch13, @function
prim_local_fetch13:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(52,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch13, .-prim_local_fetch13
	.align 1
	.align 2
	.global	prim_local_fetch14
	.type	prim_local_fetch14, @function
prim_local_fetch14:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(56,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch14, .-prim_local_fetch14
	.align 1
	.align 2
	.global	prim_local_fetch15
	.type	prim_local_fetch15, @function
prim_local_fetch15:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	mov.l	@(60,r1),r2
	mov.l	@(4,r4),r1
	shll2	r0
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch15, .-prim_local_fetch15
	.align 1
	.align 2
	.global	prim_local_fetch16
	.type	prim_local_fetch16, @function
prim_local_fetch16:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(0,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch16, .-prim_local_fetch16
	.align 1
	.align 2
	.global	prim_local_fetch17
	.type	prim_local_fetch17, @function
prim_local_fetch17:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(4,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch17, .-prim_local_fetch17
	.align 1
	.align 2
	.global	prim_local_fetch18
	.type	prim_local_fetch18, @function
prim_local_fetch18:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(8,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch18, .-prim_local_fetch18
	.align 1
	.align 2
	.global	prim_local_fetch19
	.type	prim_local_fetch19, @function
prim_local_fetch19:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(12,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch19, .-prim_local_fetch19
	.align 1
	.align 2
	.global	prim_local_fetch20
	.type	prim_local_fetch20, @function
prim_local_fetch20:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(16,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch20, .-prim_local_fetch20
	.align 1
	.align 2
	.global	prim_local_fetch21
	.type	prim_local_fetch21, @function
prim_local_fetch21:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(20,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch21, .-prim_local_fetch21
	.align 1
	.align 2
	.global	prim_local_fetch22
	.type	prim_local_fetch22, @function
prim_local_fetch22:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(24,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch22, .-prim_local_fetch22
	.align 1
	.align 2
	.global	prim_local_fetch23
	.type	prim_local_fetch23, @function
prim_local_fetch23:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(28,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch23, .-prim_local_fetch23
	.align 1
	.align 2
	.global	prim_local_fetch24
	.type	prim_local_fetch24, @function
prim_local_fetch24:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(32,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch24, .-prim_local_fetch24
	.align 1
	.align 2
	.global	prim_local_fetch25
	.type	prim_local_fetch25, @function
prim_local_fetch25:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(36,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch25, .-prim_local_fetch25
	.align 1
	.align 2
	.global	prim_local_fetch26
	.type	prim_local_fetch26, @function
prim_local_fetch26:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(40,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch26, .-prim_local_fetch26
	.align 1
	.align 2
	.global	prim_local_fetch27
	.type	prim_local_fetch27, @function
prim_local_fetch27:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(44,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch27, .-prim_local_fetch27
	.align 1
	.align 2
	.global	prim_local_fetch28
	.type	prim_local_fetch28, @function
prim_local_fetch28:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(48,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch28, .-prim_local_fetch28
	.align 1
	.align 2
	.global	prim_local_fetch29
	.type	prim_local_fetch29, @function
prim_local_fetch29:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(52,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch29, .-prim_local_fetch29
	.align 1
	.align 2
	.global	prim_local_fetch30
	.type	prim_local_fetch30, @function
prim_local_fetch30:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(56,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch30, .-prim_local_fetch30
	.align 1
	.align 2
	.global	prim_local_fetch31
	.type	prim_local_fetch31, @function
prim_local_fetch31:
	mov.l	@(36,r4),r1
	mov.l	@r4,r0
	add	#64,r1
	mov.l	@(60,r1),r2
	shll2	r0
	mov.l	@(4,r4),r1
	mov.l	r2,@(r0,r1)
	mov.l	@r4,r1
	add	#1,r1
	rts	
	mov.l	r1,@r4
	.size	prim_local_fetch31, .-prim_local_fetch31
	.align 1
	.align 2
	.global	prim_local_store0
	.type	prim_local_store0, @function
prim_local_store0:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@r1
	.size	prim_local_store0, .-prim_local_store0
	.align 1
	.align 2
	.global	prim_local_store1
	.type	prim_local_store1, @function
prim_local_store1:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(4,r1)
	.size	prim_local_store1, .-prim_local_store1
	.align 1
	.align 2
	.global	prim_local_store2
	.type	prim_local_store2, @function
prim_local_store2:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(8,r1)
	.size	prim_local_store2, .-prim_local_store2
	.align 1
	.align 2
	.global	prim_local_store3
	.type	prim_local_store3, @function
prim_local_store3:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(12,r1)
	.size	prim_local_store3, .-prim_local_store3
	.align 1
	.align 2
	.global	prim_local_store4
	.type	prim_local_store4, @function
prim_local_store4:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(16,r1)
	.size	prim_local_store4, .-prim_local_store4
	.align 1
	.align 2
	.global	prim_local_store5
	.type	prim_local_store5, @function
prim_local_store5:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(20,r1)
	.size	prim_local_store5, .-prim_local_store5
	.align 1
	.align 2
	.global	prim_local_store6
	.type	prim_local_store6, @function
prim_local_store6:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(24,r1)
	.size	prim_local_store6, .-prim_local_store6
	.align 1
	.align 2
	.global	prim_local_store7
	.type	prim_local_store7, @function
prim_local_store7:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(28,r1)
	.size	prim_local_store7, .-prim_local_store7
	.align 1
	.align 2
	.global	prim_local_store8
	.type	prim_local_store8, @function
prim_local_store8:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(32,r1)
	.size	prim_local_store8, .-prim_local_store8
	.align 1
	.align 2
	.global	prim_local_store9
	.type	prim_local_store9, @function
prim_local_store9:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(36,r1)
	.size	prim_local_store9, .-prim_local_store9
	.align 1
	.align 2
	.global	prim_local_store10
	.type	prim_local_store10, @function
prim_local_store10:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(40,r1)
	.size	prim_local_store10, .-prim_local_store10
	.align 1
	.align 2
	.global	prim_local_store11
	.type	prim_local_store11, @function
prim_local_store11:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(44,r1)
	.size	prim_local_store11, .-prim_local_store11
	.align 1
	.align 2
	.global	prim_local_store12
	.type	prim_local_store12, @function
prim_local_store12:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(48,r1)
	.size	prim_local_store12, .-prim_local_store12
	.align 1
	.align 2
	.global	prim_local_store13
	.type	prim_local_store13, @function
prim_local_store13:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(52,r1)
	.size	prim_local_store13, .-prim_local_store13
	.align 1
	.align 2
	.global	prim_local_store14
	.type	prim_local_store14, @function
prim_local_store14:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(56,r1)
	.size	prim_local_store14, .-prim_local_store14
	.align 1
	.align 2
	.global	prim_local_store15
	.type	prim_local_store15, @function
prim_local_store15:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	rts	
	mov.l	r2,@(60,r1)
	.size	prim_local_store15, .-prim_local_store15
	.align 1
	.align 2
	.global	prim_local_store16
	.type	prim_local_store16, @function
prim_local_store16:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(0,r1)
	.size	prim_local_store16, .-prim_local_store16
	.align 1
	.align 2
	.global	prim_local_store17
	.type	prim_local_store17, @function
prim_local_store17:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(4,r1)
	.size	prim_local_store17, .-prim_local_store17
	.align 1
	.align 2
	.global	prim_local_store18
	.type	prim_local_store18, @function
prim_local_store18:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(8,r1)
	.size	prim_local_store18, .-prim_local_store18
	.align 1
	.align 2
	.global	prim_local_store19
	.type	prim_local_store19, @function
prim_local_store19:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(12,r1)
	.size	prim_local_store19, .-prim_local_store19
	.align 1
	.align 2
	.global	prim_local_store20
	.type	prim_local_store20, @function
prim_local_store20:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(16,r1)
	.size	prim_local_store20, .-prim_local_store20
	.align 1
	.align 2
	.global	prim_local_store21
	.type	prim_local_store21, @function
prim_local_store21:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(20,r1)
	.size	prim_local_store21, .-prim_local_store21
	.align 1
	.align 2
	.global	prim_local_store22
	.type	prim_local_store22, @function
prim_local_store22:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(24,r1)
	.size	prim_local_store22, .-prim_local_store22
	.align 1
	.align 2
	.global	prim_local_store23
	.type	prim_local_store23, @function
prim_local_store23:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(28,r1)
	.size	prim_local_store23, .-prim_local_store23
	.align 1
	.align 2
	.global	prim_local_store24
	.type	prim_local_store24, @function
prim_local_store24:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(32,r1)
	.size	prim_local_store24, .-prim_local_store24
	.align 1
	.align 2
	.global	prim_local_store25
	.type	prim_local_store25, @function
prim_local_store25:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(36,r1)
	.size	prim_local_store25, .-prim_local_store25
	.align 1
	.align 2
	.global	prim_local_store26
	.type	prim_local_store26, @function
prim_local_store26:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(40,r1)
	.size	prim_local_store26, .-prim_local_store26
	.align 1
	.align 2
	.global	prim_local_store27
	.type	prim_local_store27, @function
prim_local_store27:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(44,r1)
	.size	prim_local_store27, .-prim_local_store27
	.align 1
	.align 2
	.global	prim_local_store28
	.type	prim_local_store28, @function
prim_local_store28:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(48,r1)
	.size	prim_local_store28, .-prim_local_store28
	.align 1
	.align 2
	.global	prim_local_store29
	.type	prim_local_store29, @function
prim_local_store29:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(52,r1)
	.size	prim_local_store29, .-prim_local_store29
	.align 1
	.align 2
	.global	prim_local_store30
	.type	prim_local_store30, @function
prim_local_store30:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(56,r1)
	.size	prim_local_store30, .-prim_local_store30
	.align 1
	.align 2
	.global	prim_local_store31
	.type	prim_local_store31, @function
prim_local_store31:
	mov.l	@r4,r0
	mov.l	@(4,r4),r1
	add	#-1,r0
	mov.l	r0,@r4
	shll2	r0
	mov.l	@(r0,r1),r2
	mov.l	@(36,r4),r1
	add	#64,r1
	rts	
	mov.l	r2,@(60,r1)
	.size	prim_local_store31, .-prim_local_store31
	.align 1
	.align 2
	.global	prim_locals_copy
	.type	prim_locals_copy, @function
prim_locals_copy:
	mov	r4,r2
	add	#64,r2
	mov.l	@(12,r2),r1
	mov.l	@r4,r5
	mov.l	@(4,r1),r7
	add	#4,r1
	mov	r7,r6
	shlr16	r6
	cmp/ge	r6,r5
	bf/s	.L76
	mov.l	r1,@(12,r2)
	tst	r6,r6
	bt	.L69
	mov.l	@(4,r4),r2
	mov	r5,r1
	shll2	r1
	mov.l	@(36,r4),r3
	add	r1,r2
	mov	r6,r1
	shll2	r1
	extu.w	r7,r7
	add	#-4,r1
	add	#4,r3
	shll2	r7
	shlr2	r1
	add	r7,r3
	add	#1,r1
	.align 2
.L70:
	add	#-4,r2
	mov.l	@r2,r7
	dt	r1
	bf/s	.L70
	mov.l	r7,@-r3
	sub	r6,r5
.L69:
	rts	
	mov.l	r5,@r4
	.align 1
.L76:
	mov	r4,r1
	mov	#10,r2
	add	#124,r1
	mov.l	r2,@(4,r1)
	add	#80,r4
	mov	#0,r1
	mov.b	r1,@r4
	rts	
	nop
	.size	prim_locals_copy, .-prim_locals_copy
	.align 1
	.align 2
	.global	prim_locals_zero
	.type	prim_locals_zero, @function
prim_locals_zero:
	mov	r4,r3
	add	#64,r3
	mov.l	@(12,r3),r2
	mov.l	@(4,r2),r1
	add	#4,r2
	mov	r1,r6
	shlr16	r6
	tst	r6,r6
	bt/s	.L79
	mov.l	r2,@(12,r3)
	extu.w	r1,r1
	mov.l	@(36,r4),r4
	sub	r6,r1
	mov.l	.L80,r0
	add	#1,r1
	shll2	r1
	shll2	r6
	mov	#0,r5
	jmp	@r0
	add	r1,r4
	.align 1
.L79:
	rts	
	nop
.L81:
	.align 2
.L80:
	.long	memset
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
