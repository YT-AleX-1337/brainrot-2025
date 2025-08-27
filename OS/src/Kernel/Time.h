#pragma once

typedef enum
{	
	PIT_CTRLB_MODE0			= 0x00, //Interrupt on terminal count
	PIT_CTRLB_MODE1			= 0x02, //Hardware re-triggerable one-shot
	PIT_CTRLB_MODE2			= 0x04, //Rate generator
	PIT_CTRLB_MODE3			= 0x06, //Square wave generator
	PIT_CTRLB_MODE4			= 0x08, //Software triggered mode
	PIT_CTRLB_MODE5			= 0x0A, //Hardware triggered mode
	
	PIT_CTRLB_LATCH_COUNT	= 0x00,
	PIT_CTRLB_ACCESS_LOW	= 0x10,
	PIT_CTRLB_ACCESS_HIGH	= 0x20,
	
	PIT_CTRLB_CHANNEL0		= 0x00,
	PIT_CTRLB_CHANNEL2		= 0x80
} PIT_CTRLB;

typedef struct TaskUnit TaskUnit;
struct TaskUnit
{
	TaskUnit* PrevUnit;
	TaskUnit* NextUnit;
	int Z;
	Procedure Task;
} __attribute__((packed));

typedef struct
{
	int CurrentTicks;
} __attribute__((packed)) Timer;

#define PIT_CHANNEL0_PORT	0x40
#define PIT_CHANNEL2_PORT	0x42
#define PIT_CONTROL_PORT	0x43

#define PC_SPEAKER_PORT		0x61

#define PIT_BASE_FREQUENCY	1193182

extern uint64_t Ticks;
extern uint64_t Frequency;

extern TaskUnit* FirstTaskUnit;

extern void PIT_Initialize(uint16_t frequency);

extern TaskUnit* AddTask(Procedure task);
extern TaskUnit* AddTask(Procedure task, int z);
extern void RemoveTask(TaskUnit* taskUnit);

extern void Sleep(uint64_t milliseconds);

extern Timer* NewTimer();
extern void ResetTimer(Timer* timer);
extern void SleepTimer(Timer* timer, int ms);
extern void DeleteTimer(Timer* timer);

extern void ResetTicks();

extern uint16_t Rand();
extern int16_t RandRange(int16_t min, int16_t max);