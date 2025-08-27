#include "Kernel.h"

uint64_t Ticks = 0;
uint64_t Frequency = PIT_BASE_FREQUENCY;

TaskUnit* FirstTaskUnit = NULL;

void PIT_Tick(Registers* regs)
{
	Ticks += 1;
	
	TaskUnit* lastUnit = FirstTaskUnit;
	
	while (lastUnit)
	{
		lastUnit->Task();
		lastUnit = lastUnit->NextUnit;
	}
}

void PIT_Initialize(uint16_t frequency)
{
	uint16_t divisor = PIT_BASE_FREQUENCY / frequency;
    
    OutB(PIT_CONTROL_PORT, PIT_CTRLB_CHANNEL0 | PIT_CTRLB_ACCESS_LOW | PIT_CTRLB_ACCESS_HIGH | PIT_CTRLB_MODE3);
    OutB(PIT_CHANNEL0_PORT, (uint8_t)(divisor & 0xFF)); 
    OutB(PIT_CHANNEL0_PORT, (uint8_t)((divisor >> 8) & 0xFF));
	
	Frequency = frequency;
	IRQ_RegisterHandler(0, PIT_Tick); 
} 
  
TaskUnit* AddTask(Procedure task)
{
	return AddTask(task, 0);
}	

TaskUnit* AddTask(Procedure task, int z)
{            
	TaskUnit* unit = (TaskUnit*)MemAlloc(sizeof(TaskUnit));
	
	unit->Task = task;
	unit->PrevUnit = NULL;
	unit->NextUnit = NULL;
	
	if (!FirstTaskUnit)
	{
		FirstTaskUnit = unit;
	}
	else if (FirstTaskUnit->Z > z)
	{                    
		FirstTaskUnit->PrevUnit = unit;   
		unit->NextUnit = FirstTaskUnit;
		FirstTaskUnit = unit;
	}
	else
	{                        
		TaskUnit* lastUnit = FirstTaskUnit;
		bool done = false;
		
		while (lastUnit->NextUnit)
		{
			if (lastUnit->NextUnit->Z > z)
			{
				lastUnit->NextUnit->PrevUnit = unit;  
				unit->PrevUnit = lastUnit;
				unit->NextUnit = lastUnit->NextUnit; 
				lastUnit->NextUnit = unit;
				
				done = true;
				break;
			}
			
			lastUnit = lastUnit->NextUnit;
		}
		
		if (!done)
		{
			unit->PrevUnit = lastUnit;  
			lastUnit->NextUnit = unit;
		}
	}
	
	return unit;
}

void RemoveTask(TaskUnit* taskUnit)
{	
	if (taskUnit->PrevUnit)
		taskUnit->PrevUnit->NextUnit = taskUnit->NextUnit;
	else
		FirstTaskUnit = taskUnit->NextUnit;

	if (taskUnit->NextUnit)
		taskUnit->NextUnit->PrevUnit = taskUnit->PrevUnit;
	
	MemFree(taskUnit);
}  

void Sleep(uint64_t ms)
{
    uint64_t endTicks = Ticks + (ms * Frequency / 1000);
	
    while (Ticks < endTicks)
		Hlt();
}    

Timer* NewTimer()
{
	Timer* timer = (Timer*)MemAlloc(sizeof(Timer));
	ResetTimer(timer);
	
	return timer;
}

void ResetTimer(Timer* timer)
{
	timer->CurrentTicks = Ticks;
}

void SleepTimer(Timer* timer, int ms)
{
    uint64_t endTicks = timer->CurrentTicks + (ms * Frequency / 1000);
	
    while (Ticks < endTicks)
		Hlt();
}

void DeleteTimer(Timer* timer)
{
    MemFree(timer);
}

void ResetTicks()
{
	Ticks = 0;
}                                                  

uint16_t Rand()
{
	//This is taken from MurmurHash3
    uint32_t x = Ticks * Ticks * Ticks;
    x ^= x >> 16;
    x *= 0x85EBCA6B;
    x ^= x >> 13;
    x *= 0xC2B2AE35;
    x ^= x >> 16;
    return (uint16_t)(x & 0xFFFF);
}

int16_t RandRange(int16_t min, int16_t max)
{
	if (max <= min)
        return min;	
	return Rand() % (max - min) + min;
}