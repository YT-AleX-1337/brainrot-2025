#pragma once         

typedef struct
{
	uint16_t BaseLow;	//Base (bits 0-15)
	uint16_t KernelCS;  //Code segment
	uint8_t IST;   		//IST
	uint8_t Flags;		//Type + flags
	uint16_t BaseMid;	//Base (bits 16-31)
	uint32_t BaseHigh;	//Base (bits 32-63)
	uint32_t Reserved;	//Reserved (set to zero)
} __attribute__((packed)) IDTEntry;

typedef struct
{
	uint16_t Limit;		//sizeof(idt) - 1
	uint64_t Base;		//IDT Address
} __attribute__((packed)) IDTDescriptor;

typedef enum
{
	IDT_FLAG_GATE_TASK			= 0x05,
	IDT_FLAG_GATE_16BIT_INT		= 0x06,
	IDT_FLAG_GATE_16BIT_TRAP	= 0x07,
	IDT_FLAG_GATE_32BIT_INT		= 0x0E,
	IDT_FLAG_GATE_32BIT_TRAP	= 0x0F,
	
	IDT_FLAG_RING0				= 0x00,
	IDT_FLAG_RING1				= 0x20,
	IDT_FLAG_RING2				= 0x40,
	IDT_FLAG_RING3				= 0x60,
	
	IDT_FLAG_PRESENT			= 0x80,
} IDT_FLAGS;

extern IDTEntry idt[];
extern IDTDescriptor idtDescriptor;       

extern "C" void IDT_Load(IDTDescriptor* descriptor);
void IDT_SetGate(uint8_t interrupt, uint64_t base, uint16_t codeSegment, uint8_t flags);
void IDT_EnableGate(uint8_t interrupt);
void IDT_DisableGate(uint8_t interrupt);
void IDT_Initialize();