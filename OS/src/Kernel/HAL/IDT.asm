;void IDT_Load(IDTDescriptor* descriptor [rdi])
global IDT_Load
IDT_Load:
	;New call frame
	push rbp
	mov rbp, rsp
	
	;Load IDT
	lidt [rdi]

	;Restore call frame
	mov rsp, rbp
	pop rbp
	
	ret