#sh4eb-linux-musl has no underscore but sh-elf-gcc does so define both
.macro func name
    .globl \name
    .globl _\name
    \name:
    _\name:
.endm

