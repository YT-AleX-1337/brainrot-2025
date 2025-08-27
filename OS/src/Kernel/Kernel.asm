bits 64
extern Main

call HAL_Initialize ;Initialize Hardware Abstraction Layer
jmp Main ;Execute kernel    
jmp $

times 16 - ($ - $$) db 0

db 0, '.KERNEL', 0 ;Kernel label

%macro pushaq 0 ;Custom instruction that works like pusha/pushad but for long mode (64-bit)
	push rax
	push rcx
	push rdx
	push rbx
	push rbp
	push rsi
	push rdi
%endmacro

%macro popaq 0 ;Custom instruction that works like popa/popad but for long mode (64-bit)
	pop rdi
	pop rsi
	pop rbp
	pop rbx
	pop rdx
	pop rcx
	pop rax
%endmacro

%include 'HAL.asm'

CODE_SEGMENT equ 0x08
DATA_SEGMENT equ 0x10