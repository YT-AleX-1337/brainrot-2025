#include "Kernel.h"

void PIC_Configure(uint8_t offsetPic1, uint8_t offsetPic2)
{
	//Initialization Control Word 1
	OutB(PIC1_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
	IOWait();                                          
	OutB(PIC2_COMMAND_PORT, PIC_ICW1_ICW4 | PIC_ICW1_INITIALIZE);
	IOWait();

	//Initialization Control Word 2
	OutB(PIC1_DATA_PORT, offsetPic1);
	IOWait();                                          
	OutB(PIC2_DATA_PORT, offsetPic2);
	IOWait();

	//Initialization Control Word 3
	OutB(PIC1_DATA_PORT, 1 << 2); //Tell PIC1 it has a slave PIC at IRQ2
	IOWait();                                          
	OutB(PIC2_DATA_PORT, 2); //Tell PIC2 it's a slave (this sounds so bad) connected at IRQ2
	IOWait();

	//Initialization Control Word 4
	OutB(PIC1_DATA_PORT, PIC_ICW4_8086);
	IOWait();                                          
	OutB(PIC2_DATA_PORT, PIC_ICW4_8086);
	IOWait();

	//Clear interrupt masks
	OutB(PIC1_DATA_PORT, 0);
	IOWait();                                          
	OutB(PIC2_DATA_PORT, 0);
	IOWait();
}

void PIC_MaskIRQ(int irq)
{
	uint8_t port;
	
	if (irq < 8)
		port = PIC1_DATA_PORT;
	else
	{
		irq -= 8;
		port = PIC2_DATA_PORT;
	}
	
	uint8_t mask = InB(port);
	OutB(port, mask | (1 << irq));
}

void PIC_UnmaskIRQ(int irq)
{
	uint8_t port;
	
	if (irq < 8)
		port = PIC1_DATA_PORT;
	else
	{
		irq -= 8;
		port = PIC2_DATA_PORT;
	}
	
	uint8_t mask = InB(port);
	OutB(port, mask & ~(1 << irq));
}

void PIC_Disable()
{
	OutB(PIC1_DATA_PORT, 0xFF);
	IOWait();                                          
	OutB(PIC2_DATA_PORT, 0xFF);
	IOWait();
}

void PIC_EndOfInterrupt(int irq)
{
	if (irq >= 8)
		OutB(PIC2_COMMAND_PORT, PIC_CMD_EOI); //If the IRQ is from PIC2, send the EOI to PIC2
	OutB(PIC1_COMMAND_PORT, PIC_CMD_EOI); //In any case, you should send the EOI to PIC1 (since PIC2 is attached to PIC1)
}

uint16_t PIC_ReadIRQRequestRegister()
{
	OutB(PIC1_COMMAND_PORT, PIC_CMD_READ_IRR);
	OutB(PIC2_COMMAND_PORT, PIC_CMD_READ_IRR);
	
	return InB(PIC2_COMMAND_PORT) | (InB(PIC2_COMMAND_PORT) << 8);
}

uint16_t PIC_ReadInServiceRegister()
{
	OutB(PIC1_COMMAND_PORT, PIC_CMD_READ_ISR);
	OutB(PIC2_COMMAND_PORT, PIC_CMD_READ_ISR);
	
	return InB(PIC2_COMMAND_PORT) | (InB(PIC2_COMMAND_PORT) << 8);
}