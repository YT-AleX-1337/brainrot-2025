#include "Kernel.h"

uint32_t freq = 0; 
uint32_t soundLeft = 0;

Music playingMusic;
uint16_t* musicData;
uint16_t notesLeft = 0;
uint16_t noteLengthLeft = 0;
uint16_t loopCount = 0;

bool musicMode = true; 
bool playNoteNext = false; 

void InternalSoundStop()
{
	OutB(PC_SPEAKER_PORT, 0xFC);
}

void InternalPlayNote(uint16_t frequency)
{
	if (frequency < 16 || frequency > 8372)
	{
		InternalSoundStop();
		return;
	}
	
	uint16_t divisor = PIT_BASE_FREQUENCY / frequency;
		
	OutB(PIT_CONTROL_PORT, PIT_CTRLB_CHANNEL2 | PIT_CTRLB_ACCESS_LOW | PIT_CTRLB_ACCESS_HIGH | PIT_CTRLB_MODE3);
	OutB(PIT_CHANNEL2_PORT, (uint8_t)(divisor & 0xFF)); 
	OutB(PIT_CHANNEL2_PORT, (uint8_t)((divisor >> 8) & 0xFF));
	
	uint8_t signal = InB(PC_SPEAKER_PORT);
	if (signal != (signal | 3))
	{
		OutB(PC_SPEAKER_PORT, signal | 3);
	}
}     

void InternalPlayMusic(Music music)
{       
	playingMusic = music;

	musicData = music.MusicData;
	notesLeft = music.DataLength;
	soundLeft = musicData[1] + 1;
	
	musicMode = true;
	playNoteNext = true;               
}         

void Sound_Update()
{ 
	if (soundLeft > 0)
	{
		if (musicMode)
		{
			if (soundLeft > 1)
			{            
				if (playNoteNext)
				{         
					InternalSoundStop();
					InternalPlayNote(musicData[0]);
					playNoteNext = false;
				}
				
				soundLeft--;
			}
			else if (soundLeft == 1)
			{
				if (notesLeft > 0)
				{
					while (soundLeft == 1 && notesLeft > 0)
					{                          
						musicData += 2;  
						soundLeft = musicData[1] + 1;
						notesLeft--;  
					}     
						
					if (notesLeft > 0)
						playNoteNext = true;
					else
					{       
						if (loopCount > 0)
						{    
							if (loopCount != MUSIC_INFINITE_LOOP)
								loopCount--;
							InternalPlayMusic(playingMusic);
						}
						else
						{       
							InternalSoundStop();
							soundLeft = 0;
						}
					} 
				}
				else
				{    
					if (loopCount > 0)
					{
						if (loopCount != MUSIC_INFINITE_LOOP)
							loopCount--;
						InternalPlayMusic(playingMusic);
					}
					else
					{      
						InternalSoundStop();
						soundLeft = 0;
					}
				}
			}
		}
		else
		{  
			if (soundLeft > 1)
			{
				if (playNoteNext)
				{
					InternalPlayNote(freq);
					playNoteNext = false;
				}
				
				soundLeft--;
			}
			else if (soundLeft == 1)
			{
				InternalSoundStop();
				soundLeft = 0;
			}
		}
	}
}          

void Sound_Initialize()
{
	AddTask(Sound_Update);
}  

void PlayMusic(Music music, uint16_t loop)
{
	loopCount = loop == MUSIC_INFINITE_LOOP ? loop : loop - 1;
	InternalPlayMusic(music);
}

void PlayMusic(Music music)
{    
	PlayMusic(music, 1);
}

void PlayNote(uint16_t frequency, uint32_t ms)
{	
	if (frequency < 16 || frequency > 8372)
	{
		StopSound();
		return;
	}             
	
	freq = frequency;
	
	soundLeft = ms * Frequency / 1000 + 1;
	musicMode = false;	
	playNoteNext = true;
}

void StopSound()
{
	musicMode = false;
	soundLeft = 1;
}