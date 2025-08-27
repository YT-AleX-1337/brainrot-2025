extern ISR_Handler

%macro ISR_NOERROR 1
	global ISR%1
	ISR%1:       
		push 0 ;Push dummy error code
		push %1 ;Push interrupt number
		jmp ISR_Common
%endmacro

%macro ISR_ERROR 1
	global ISR%1
	ISR%1:
		;Error code is pushed by the CPU for error ISRs
		push %1 ;Push interrupt number
		jmp ISR_Common
%endmacro     

%include 'HAL\ISR_List.asm'
	
ISR_Common:
	pushaq ;Custom instruction that works like pusha/pushad but in long mode (64-bit)
	
	;Push ds
	xor rax, rax
	mov ax, ds
	push rax
	
	mov ax, DATA_SEGMENT ;Use kernel's data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov rdi, rsp ;Push pointer to stack
	call ISR_Handler ;Call the handler (defined in C++)
	
	;Pop ds and move it to all data segment registers
	pop rax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	popaq ;Custom instruction that works like popa/popad but in long mode (64-bit)
	add rsp, 16 ;Remove error code and interrupt number from stack
	iretq