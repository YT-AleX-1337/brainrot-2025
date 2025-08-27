#include "Kernel.h"      

uint8_t* MemTable = (uint8_t*)0x110000;
int maxChunks = (MEM_MAX_ADDRESS - MEM_BASE_ADDRESS) / 16;

void* MemAlloc(uint32_t size)
{	
	if (size == 0)
		return NULL;
	
	int chunks = size / 16 + (size % 16 == 0 ? 0 : 1);
	if (chunks > maxChunks)
		return NULL;
	
	//Look for enough consecutive free memory
	for (int i = 0; i < maxChunks - chunks; i++)
	{        
		bool available = true;
		
		for (int j = 0; j < chunks; j++)
		{
			if (MemTable[i + j])
			{          
				available = false;
				i += j + MemTable[i + j];
				break;
			}
		}
		
		if (available)
		{			
			for (int j = 0; j < chunks; j++)
			{
				MemTable[i + j] = chunks - j > 255 ? 255 : chunks - j;
			}
			
			return (void*)(MEM_BASE_ADDRESS + i * 16);
		}
	}
	
	return NULL;
}

void MemFree(void* address)
{
	if (!address || (uint64_t)address < MEM_BASE_ADDRESS || (uint64_t)address >= MEM_MAX_ADDRESS)
		return;
	
	int i = ((uint64_t)address - MEM_BASE_ADDRESS) / 16;
	int chunks = MemTable[i];
	
	for (int j = 0; j < chunks; j++)
	{
		MemTable[i + j] = 0;
	}
}     

void* MemSet(void* address, uint8_t value, int size)
{
	if (!address)
		return NULL;
	
	uint8_t* a = (uint8_t*)address;
	
	while (size > 0)
	{
		*a++ = value;
		size--;
	}
	
	return address;
}

void* MemCopy(void* source, void* dest, int size)
{
	if (!source || !dest)
		return NULL;
	
	uint64_t* s = (uint64_t*)source;
	uint64_t* d = (uint64_t*)dest;
	
	while (size > 7)
	{
		*d++ = *s++;
		size -= 8;
	}
	
	uint8_t* sb = (uint8_t*)s;
	uint8_t* db = (uint8_t*)d;
	
	while (size > 0)
	{
		*db++ = *sb++;
		size--;
	}
	
	return dest;
}