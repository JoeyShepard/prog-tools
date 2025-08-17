.text

#void sync_icache(void *ptr, int size)
.globl sync_icache
sync_icache:
    #R4 = ptr
    #R5 = size
    .equ CACHE_LINE_SIZE, 32

    #R0 = mask
    mov #~(CACHE_LINE_SIZE-1),r0
    
    #R1 = begin
    mov r4,r1
    and r0,r1
    
    #R4 = end
    add r5,r4
    add #-1,r4
    and r0,r4

    #Write back cache lines

    #R2 = copy of begin for loop
    mov r1,r2
    .ocbwb_loop:
        ocbwb @r2
        cmp/eq r2,r4
        bf/s .ocbwb_loop
        add #CACHE_LINE_SIZE,r2

    #Sync data accesses 
    synco

    #Invalidate instruction cache

    #R2 = copy of begin for loop
    mov r1,r2
    .icbi_loop:
        icbi @r2
        cmp/eq r2,r4
        bf/s .icbi_loop
        add #CACHE_LINE_SIZE,r2

    rts
    nop

