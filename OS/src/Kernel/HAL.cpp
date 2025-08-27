#include "Kernel.h"

extern "C" void HAL_Initialize()
{   
	IDT_Initialize();
	ISR_Initialize();
	IRQ_Initialize();
	VGA_Initialize();  
	Sound_Initialize();
	KB_Initialize();
	UI_Initialize();
	PIT_Initialize(100);
}