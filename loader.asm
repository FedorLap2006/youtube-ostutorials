MAGIC equ 0x1BADB002
MEMINFO equ 1<<1
MBALIGN equ 1<<0
FLAGS equ 0 | MBALIGN | MEMINFO
HLEN equ __boot_header_end - __boot_header
CHECKSUM equ 0x100000000 - (MAGIC + FLAGS + HLEN)

STACK_SIZE equ 6000

section .bss

align 4

stack_beg:
	resb STACK_SIZE
stack_top:


section .boot
align 4

__boot_header:
	dd MAGIC
	dd FLAGS
	dd -(MAGIC + FLAGS)
	dd HLEN
	dd CHECKSUM
__boot_header_end:

section .text

global _loader

extern kmain
; ...

_loader:
	; ...
	finit
	; sti - DO NOT enable interrupts until IDT is created!
	mov esp,stack_top
 
	push ebx
	push eax
 
	call kmain
 
	cli
.stop:
	hlt
	jmp .stop
