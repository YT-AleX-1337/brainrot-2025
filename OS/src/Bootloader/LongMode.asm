GDT_Start:
	GDT_NullDesc:
		dq 0			;Null descriptor
	GDT_CodeDesc:
		dw 0xFFFF		;Limit (bits 0-15)
		dw 0x0000		;Base (bits 0-15)
		db 0x00			;Base (bits 16-23)
		db 10011010b	;Access
		db 11001111b	;Flags + limit (bits 16-19)
		db 0x00			;Base (bits 24-31)
	GDT_DataDesc:
		dw 0xFFFF
		dw 0x0000
		db 0x00
		db 10010010b
		db 11001111b
		db 0x00
GDT_End:

GDT_Descriptor:
	dw GDT_End - GDT_Start - 1 ;GDT size - 1
	dq GDT_Start ;GDT address

;Defined as a macro because I a function wouldn't work
%macro EnterProtectedMode 0
	;Enable A20 line
	in al, 0x92
	or al, 1 << 1
	out 0x92, al

	;Disable interrupts
	cli

	;Load GDT
	lgdt [GDT_Descriptor]

	;Set protected mode bit
	mov eax, cr0
	or eax, 1 << 0
	mov cr0, eax
%endmacro

%macro EnterLongMode 0
	;Detect cpuid instruction
	pushfd ;Push eflags register
	pop eax ;Pop it into eax
	mov ecx, eax ;Copy it into eax
	xor eax, 1 << 21 ;Set the 21st bit (whether cpuid is supported)
	push eax
	popfd ;Save the eflags register
	pushfd ;Repush it
	pop eax ;Repop it in eax
	push ecx
	popfd ;Save the old eflags
	xor eax, ecx ;If eax and ecx are the same, cpuid isn't supported
	jz Halt ;Halt if cpuid isn't supported

	;Detect long mode
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz Halt ;Halt if long mode is not supported

	;Enable PAE
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax 

	;Set long mode bit
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	;Set Page Map Level 4 address
	mov eax, PAGE_MAP_LEVEL_4
	mov cr3, eax
	
	mov eax, PAGE_DIRECTORY_PTR | 0x03 ;PDPT address + flags (lower 12 bits): present + writable
	mov [PAGE_MAP_LEVEL_4], eax ;Set first entry of the PML4 to the PDPT address
	
	mov eax, PAGE_DIRECTORY | 0x03 ;PD address + flags (lower 12 bits): present + writable
	mov [PAGE_DIRECTORY_PTR], eax ;Set first entry of the PDPT to the PD address
	
	mov eax, PAGE_TABLE_1 | 0x03 ;PT address + flags (lower 12 bits): present + writable
	mov [PAGE_DIRECTORY], eax ;Set first entry of the PD to the first PT address
	
	mov eax, PAGE_TABLE_2 | 0x03 ;PT address + flags (lower 12 bits): present + writable
	mov [PAGE_DIRECTORY + 8], eax ;Set second entry of the PD to the second PT address
	
	mov eax, PAGE_TABLE_3 | 0x03 ;PT address + flags (lower 12 bits): present + writable
	mov [PAGE_DIRECTORY + 16], eax ;Set second entry of the PD to the second PT address
	
	mov eax, PAGE_TABLE_4 | 0x03 ;PT address + flags (lower 12 bits): present + writable
	mov [PAGE_DIRECTORY + 24], eax ;Set second entry of the PD to the second PT address
	
	mov eax, PAGE_TABLE_5 | 0x03 ;PT address + flags (lower 12 bits): present + writable
	mov [PAGE_DIRECTORY + 32], eax ;Set second entry of the PD to the second PT address
	
	mov edi, PAGE_TABLE_1
	mov ebx, 0x03 ;Set flags: present + writable
	mov ecx, 512 ;Set counter (loop will iterate 512 times)
	.setEntry1:
		mov dword [edi], ebx ;Set Page Table entry
		add ebx, 0x1000 ;Increment the address by 0x1000 (next memory address)
		add edi, 8 ;Next entry
		loop .setEntry1
	
	mov edi, PAGE_TABLE_2
	mov ecx, 512 ;Set counter (loop will iterate 512 times)
	.setEntry2:
		mov dword [edi], ebx ;Set Page Table entry
		add ebx, 0x1000 ;Increment the address by 0x1000 (next memory address)
		add edi, 8 ;Next entry
		loop .setEntry2
	
	mov edi, PAGE_TABLE_3
	mov ecx, 512 ;Set counter (loop will iterate 512 times)
	.setEntry3:
		mov dword [edi], ebx ;Set Page Table entry
		add ebx, 0x1000 ;Increment the address by 0x1000 (next memory address)
		add edi, 8 ;Next entry
		loop .setEntry3
	
	mov edi, PAGE_TABLE_4
	mov ecx, 512 ;Set counter (loop will iterate 512 times)
	.setEntry4:
		mov dword [edi], ebx ;Set Page Table entry
		add ebx, 0x1000 ;Increment the address by 0x1000 (next memory address)
		add edi, 8 ;Next entry
		loop .setEntry4
	
	mov edi, PAGE_TABLE_5
	mov ecx, 512 ;Set counter (loop will iterate 512 times)
	.setEntry5:
		mov dword [edi], ebx ;Set Page Table entry
		add ebx, 0x1000 ;Increment the address by 0x1000 (next memory address)
		add edi, 8 ;Next entry
		loop .setEntry5

	;Enable paging
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax  

	;Disable protected mode flag and enable long mode flag in GDT descriptors
	xor byte [GDT_CodeDesc + 6], 11b << 5
	xor byte [GDT_DataDesc + 6], 11b << 5
%endmacro

CODE_SEG equ GDT_CodeDesc - GDT_Start
DATA_SEG equ GDT_DataDesc - GDT_Start

PAGE_MAP_LEVEL_4	equ 0x1000
PAGE_DIRECTORY_PTR	equ 0x2000
PAGE_DIRECTORY		equ 0x3000
PAGE_TABLE_1		equ 0x4000
PAGE_TABLE_2		equ 0x5000
PAGE_TABLE_3		equ 0x38000
PAGE_TABLE_4		equ 0x39000
PAGE_TABLE_5		equ 0x40000