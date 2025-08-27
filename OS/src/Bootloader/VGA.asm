VGASetup:

;Copy VGA font to memory address 0x6000
push bp
push ds
push es
mov ax, 0x1130 ;Get font information
mov bh, 0x06 ;VGA ROM 8x16 font
int 0x10 ;Sets es:bp such that they point to the font address
push es
pop ds ;Put new es in ds
pop es ;Restore old es
mov si, bp
mov di, VGA_FONT ;Copy the font in here
mov cx, 256 * 16 / 4 ;It's 256 characters, each is 8x16 bits (16 bytes). Using the movsd instruction, we can move 4 bytes at once
rep movsd
pop ds   
pop bp

;Switch to VGA mode 320x200x256
mov ah, 0x00
mov al, 0x13
int 0x10

ret

VGA_FONT equ 0x6000