#pragma once

#include "HAL\PIC.h"

#define PIC_REMAP_OFFSET 0x20 

typedef void (*IRQHandler)(Registers* regs);

extern IRQHandler irqHandlers[];

extern void IRQ_Handler(Registers* regs);
extern void IRQ_Initialize();
extern void IRQ_RegisterHandler(int irq, IRQHandler handler);