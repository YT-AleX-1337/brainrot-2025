#include "Kernel.h"

IRQHandler irqHandlers[16];

void IRQ_Handler(Registers* regs)
{
	int irq = regs->interrupt - PIC_REMAP_OFFSET;
	
	if (irqHandlers[irq] != NULL)
		irqHandlers[irq](regs); //Handle interrupt
	
	PIC_EndOfInterrupt(irq);
}

void IRQ_Initialize()
{
	PIC_Configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);
	
	//Register ISR handlers for each of the 16 IRQ lines
	for (int i = 0; i < 16; i++)
		ISR_RegisterHandler(PIC_REMAP_OFFSET + i, IRQ_Handler);
	
	Sti(); //Finally reenable hardware interrupts since the bootloader!
}

void IRQ_RegisterHandler(int irq, IRQHandler handler)
{
	irqHandlers[irq] = handler;
}