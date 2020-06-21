.set MAGIC,     0xE85250D6       /* 'magic number' lets bootloader find the header */
.set ARCH,      0x0
.set LEN,       (32 * 8) + (16 * 2)
.set CHECKSUM,  -(MAGIC+ARCH+LEN)

.set TYPE_FRAMEBUF, 15
.set FLAGS_FRAMEBUF,0x0000
.set SIZE_FRAMEBUF, 20

.section .multiboot
.align 4
.long MAGIC
.long ARCH
.long LEN
.long CHECKSUM
.short TYPE_FRAMEBUF
.short FLAGS_FRAMEBUF
.long SIZE_FRAMEBUF
.long 0
.long 0
.long 0

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp


    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start
