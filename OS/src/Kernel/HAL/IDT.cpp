#include "Kernel.h"

IDTEntry idt[256];
IDTDescriptor idtDescriptor = { sizeof(idt) - 1, (uint64_t)idt };

void IDT_SetGate(uint8_t interrupt, uint64_t base, uint16_t codeSegment, uint8_t flags)
{
    idt[interrupt].BaseLow = base & 0xFFFF;
	idt[interrupt].KernelCS = codeSegment;
	idt[interrupt].IST = 0;
	idt[interrupt].Flags = flags;
    idt[interrupt].BaseMid = (base >> 16) & 0xFFFF;
    idt[interrupt].BaseHigh = (base >> 32) & 0xFFFFFFFF;
	idt[interrupt].Reserved = 0;
}

void IDT_EnableGate(uint8_t interrupt)
{
	FLAG_SET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_DisableGate(uint8_t interrupt)
{
	FLAG_UNSET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_Initialize()
{
	IDT_Load(&idtDescriptor);
}