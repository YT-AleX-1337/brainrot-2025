PrintString_String: dw 0

;Print string on screen
PrintString:
	pusha

	mov ah, 0x0E
	mov bx, word [PrintString_String]

	.loop:
		mov al, [bx]
		cmp al, 0
		jz .end

		push bx
		xor bx, bx

		int 0x10

		pop bx
		inc bx
		jmp .loop

	.end:
		popa
		ret