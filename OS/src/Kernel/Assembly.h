#pragma once
#include "Kernel.h"

static inline void OutB(uint16_t port, uint8_t value)
{
    __asm volatile ("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

static inline void OutW(uint16_t port, uint16_t value)
{
    __asm volatile ("outw %w0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

static inline void OutL(uint16_t port, uint32_t value)
{
    __asm volatile ("outl %w0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

static inline uint8_t InB(uint16_t port)
{
   uint8_t ret;
    __asm volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	
    return ret;
}

static inline uint16_t InW(uint16_t port)
{
    uint16_t ret;
    __asm volatile ("inw %w1, %w0" : "=a"(ret) : "Nd"(port) : "memory");
	
    return ret;
}

static inline uint32_t InL(uint16_t port)
{
    uint32_t ret;
    __asm volatile ("inl %w1, %w0" : "=a"(ret) : "Nd"(port) : "memory");
	
    return ret;
}

static inline void IOWait()
{
    OutB(0x80, 0); //Write to an unused port
}

static inline void Cli()
{
    __asm volatile ("cli");
}

static inline void Sti()
{
    __asm volatile ("sti");
}

static inline void Hlt()
{
    __asm volatile ("hlt");
}