#pragma once

#define MEM_BASE_ADDRESS 0x200000
#define MEM_MAX_ADDRESS 0xA00000

extern uint8_t* MemTable;

extern void* MemAlloc(uint32_t size);
extern void MemFree(void* address);                  
extern void* MemSet(void* address, uint8_t value, int size);
extern void* MemCopy(void* source, void* dest, int size);