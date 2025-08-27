#pragma once

#define PIC1_COMMAND_PORT	0x20
#define PIC1_DATA_PORT		0x21
#define PIC2_COMMAND_PORT	0xA0
#define PIC2_DATA_PORT		0xA1

enum
{
	PIC_ICW1_ICW4		= 0x01,
	PIC_ICW1_SINGLE		= 0x02,
	PIC_ICW1_INTERVAL4	= 0x04,
	PIC_ICW1_LEVEL		= 0x08,
	PIC_ICW1_INITIALIZE	= 0x10
} PIC_ICW1;

enum
{
	PIC_ICW4_8086					= 0x01,
	PIC_ICW4_AUTO_EOI				= 0x02,
	PIC_ICW4_BUFFER_MASTER			= 0x04, //PIC1
	PIC_ICW4_BUFFER_SLAVE			= 0x00, //PIC2
	PIC_ICW4_BUFFER_BUFFERED		= 0x08,
	PIC_ICW4_BUFFER_FULLY_NESTED	= 0x10
} PIC_ICW4;

enum
{
	PIC_CMD_EOI			= 0x20,
	PIC_CMD_READ_IRR	= 0x0A,
	PIC_CMD_READ_ISR	= 0x0B
} PIC_CMD;

extern void PIC_Configure(uint8_t offsetPic1, uint8_t offsetPic2);
extern void PIC_MaskIRQ(int irq);
extern void PIC_UnmaskIRQ(int irq);
extern void PIC_Disable();
extern void PIC_EndOfInterrupt(int irq);
extern uint16_t PIC_ReadIRQRequestRegister();
extern uint16_t PIC_ReadInServiceRegister();