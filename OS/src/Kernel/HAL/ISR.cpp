#include "Kernel.h"

ISRHandler isrHandlers[256];

extern "C" void ISR_Handler(Registers* regs)
{                                          
	if (isrHandlers[regs->interrupt] != NULL)
		isrHandlers[regs->interrupt](regs);
} 

//void ISR_InitializeGates();
#include "HAL\ISR_InitializeGates.cpp"

void ISR_Initialize()
{
	ISR_InitializeGates();
	for (int i = 0; i < 256; i++)
		IDT_EnableGate(i);
}

void ISR_RegisterHandler(int interrupt, ISRHandler handler)
{
    isrHandlers[interrupt] = handler;
    IDT_EnableGate(interrupt);
}