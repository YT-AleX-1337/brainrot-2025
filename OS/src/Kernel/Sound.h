#pragma once      

#define MUSIC_INFINITE_LOOP 65535

typedef struct
{
	uint32_t DataLength;
	uint16_t* MusicData;
} __attribute__((packed)) Music;

extern void Sound_Initialize();

extern void PlayMusic(Music music, uint16_t loop);
extern void PlayMusic(Music music);
extern void PlayNote(uint16_t frequency, uint32_t ms);
extern void StopSound();