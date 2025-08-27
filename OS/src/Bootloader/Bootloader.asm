org 0x7C00
bits 16
jmp Boot

db 0, '.BOOTLOADER1', 0 ;Bootloader part 1 label

times 16 - ($ - $$) db 0
BootDrive: db 0

%include 'Print.asm'

;Disk Address Packet
DAP:
	db 0x10 		;Size of DAP
	db 0			;Unused
	dw 127			;Number of sectors to read 
	dw 0			;Offset
	dw 0x7E00 >> 4	;Segment
	dq 1			;First sector to read in LBA format (sector 0 = 0)

Boot:

;Setup data segments
xor ax, ax
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax

;Set and stack registers
mov ss, ax    
mov sp, 0x7C00
mov bp, sp

mov [BootDrive], dl ;Save drive number

;Clear screen
mov ah, 0x00
mov al, 0x03
int 0x10

mov word [PrintString_String], DebugString1
call PrintString ;Print debug string

;Load bootloader part 2 and kernel from the disk
mov cx, 3  
	
.loop:
	mov ah, 0x42
	mov dl, [BootDrive]
	mov si, DAP   

	int 0x13
	jc .readDiskFailure
	
	add dword [DAP + 8], 127
	add word [DAP + 6], 0xFE00 >> 4
		
	loop .loop
	
mov word [PrintString_String], ReadDiskSuccessString
call PrintString

jmp Main16 ;Jump to bootloader part 2
 
;Disable interrupts and halt on disk read failure
.readDiskFailure:
	mov word [PrintString_String], ReadDiskFailureString
	call PrintString
	jmp Halt

Halt:
	cli
	jmp $

DebugString1: db 'Bootloader part 1 executing.', 0x0D, 0x0A, 0

ReadDiskFailureString: db 'Fatal error: couldn', 0x27, 't read from disk. System halted.', 0x0D, 0x0A, 0
ReadDiskSuccessString: db 'Disk read performed successfully.', 0x0D, 0x0A, 0

db 0, 'Coded by AleX-1337 (http://youtube.com/@YT-AleX-1337)', 0

times 510 - ($ - $$) db 0
dw 0xAA55

;Here begins part 2

db 0, '.BOOTLOADER2', 0 ;Bootloader part 2 label

%include 'LongMode.asm' 
%include 'VGA.asm'

Main16:

mov word [PrintString_String], DebugString2
call PrintString

call VGASetup

EnterProtectedMode

;Far jump to Main32
jmp CODE_SEG:Main32

bits 32

Main32:

;Update data segments
mov ax, DATA_SEG
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax

;Update stack
mov ss, ax
mov ebp, 0x80000
mov esp, ebp

EnterLongMode

;Far jump to the kernel
jmp CODE_SEG:KERNEL

DebugString2: db 'Bootloader part 2 executing.', 0x0D, 0x0A, 0

KERNEL equ 0x8100

times 1280 - ($ - $$) db 0