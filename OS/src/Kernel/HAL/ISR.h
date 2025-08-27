#pragma once 

#include "HAL\ISR_List.h"       

typedef struct
{
	uint64_t ds;                                //Data segment
	uint64_t rdi, rsi, rbp, rbx, rdx, rcx, rax;	//Pushed by the custom pushaq instruction
	uint64_t interrupt, error;					//What the ISR pushes
	uint64_t rip, cs, rflags, kernelRsp;		//Pushed by the CPU
} __attribute__((packed)) Registers; //In the order they're pushed

typedef void (*ISRHandler)(Registers* regs);

extern ISRHandler isrHandlers[];

extern void ISR_Initialize();
extern void ISR_RegisterHandler(int interrupt, ISRHandler handler);