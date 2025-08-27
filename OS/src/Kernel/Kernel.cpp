#include "Kernel.h"

void Reboot()
{                     
	OutB(0x64, 0xFE);
}

Scene* currentScene = NULL;
int currentScreen = 0;

Picture* rainbowCursors[] = { &RainbowCursor1, &RainbowCursor2, &RainbowCursor3, &RainbowCursor4, &RainbowCursor5, &RainbowCursor6, &RainbowCursor7, &RainbowCursor8, &RainbowCursor9, &RainbowCursor10, &RainbowCursor11, &RainbowCursor12, &RainbowCursor13 };
Picture* cameraScreens[] = { &Screen0, &Screen1, &Screen2, &Screen3 };  

GraphicObject* screenObj;
GraphicObject* feedBlockObj;
GraphicObject* rickObj;
GraphicObject* jumpscareObj;
UIObject* leftDoorBtn;
UIObject* rightDoorBtn;
  
int time = 0;
bool tablet = false;
uint8_t camera = 3;   
char camText[5];
int doorState = 0;
int battery = 1500;
int rickState = 3;

void MainMenu()
{	                 
	currentScreen = 0;
}              

void ModeMenu()
{        
	currentScreen = 1;
}

void StupidPoem()
{
	currentScreen = 2;
}

void ODaR()
{
	currentScreen = 3;
}

void Crash()
{
	int i = 1 / 0;
}

void OpenTablet()
{
	if (battery > 0)
		tablet = true;
	else
		PlayNote(65, 500);
}

void CloseTablet()
{
	tablet = false;
}

void Jumpscare()
{
	PlayMusic(Boo);
	SetCursorPicture(NULL);
	
	for (int i = 0; i < 3; i++)
	{
		jumpscareObj->Y = 200 - i * 100;
		Sleep(100);
	}
	
	Sleep(1000);
	Reboot();
}

int feedBlockTime = 0;
bool cam1 = false;
bool cam2 = false;
bool cam3 = false;

void UpdateRickInCamera()
{
	if (camera == rickState)
	{
		switch (camera)
		{
			case 1:  
				((PictureObject*)rickObj->Data)->Data = &RickC1;
				break;
			case 2:      
				((PictureObject*)rickObj->Data)->Data = &RickC2;
				break;
			case 3: 
				((PictureObject*)rickObj->Data)->Data = &RickC3;
				break;
		}
	}
	else ((PictureObject*)rickObj->Data)->Data = NULL;
}

int aggression = 0;
int entering = 0;
int moving = 0;

void RickMovementOpportunity()
{
	if (RandRange(0, rickState < 4 ? 5 : 3))
		return;   

	moving++;
	
	if (moving == 5)
		moving = 0;
	else
		return;
	
	int rand = 0;
	switch (rickState)
	{
		case 1:
			rand = RandRange(0, 3200);
			
			if (rand < time)
			{
				rickState = 4;          
				cam1 = true;
				cam2 = false;
				cam3 = false;
				feedBlockTime = Ticks + 30;
			}
			else
			{
				rand = RandRange(0, 2);
				
				if (rand == 0)
				{
					rickState = 2;        
					cam1 = true;
					cam2 = true;
					cam3 = false;  
					feedBlockTime = Ticks + 30;
				}
				else
				{
					rickState = 3;        
					cam1 = true;
					cam2 = false;
					cam3 = true;  
					feedBlockTime = Ticks + 30;
				}
			}
			
			break;
		case 2:
			rand = RandRange(0, 3200);
			
			if (rand < time)
			{
				rickState = 5;
				cam1 = false;
				cam2 = true;
				cam3 = false;
				feedBlockTime = Ticks + 30;
			}
			else
			{
				rand = RandRange(0, 2);
				
				if (rand == 0)
				{
					rickState = 1;   
					cam1 = true;
					cam2 = true;
					cam3 = false;
					feedBlockTime = Ticks + 30;
				}
				else
				{
					rickState = 3;  
					cam1 = false;
					cam2 = true;
					cam3 = true;
					feedBlockTime = Ticks + 30;
				}
			}
			
			break;
		case 3:
			rand = RandRange(0, 2);
			
			if (rand)
			{
				rickState = 1;             
				cam1 = true;
				cam2 = false;
				cam3 = true;
				feedBlockTime = Ticks + 30;
			}
			else
			{
				rickState = 2;          
				cam1 = false;
				cam2 = true;
				cam3 = true;
				feedBlockTime = Ticks + 30;
			}
			
			break;
		case 4:
			if (doorState != 1)
			{
				if (RandRange(5, 15) < aggression + entering)
					Jumpscare();
				else
				{
					entering += doorState == 2 ? 3 : 1;
					aggression += doorState == 2 ? 3 : 1;
				}
			}
			else
			{
				PlayNote(65, 250);
				
				entering = 0;
				rickState = 3;      
				cam1 = false;
				cam2 = false;
				cam3 = true;
				feedBlockTime = Ticks + 30;
			}
			
			break;
		case 5:
			if (doorState != 2)
			{
				if (RandRange(5, 15) < aggression + entering)
					Jumpscare();
				else
				{					
					entering += doorState == 1 ? 3 : 1;
					aggression += doorState == 1 ? 3 : 1;
				}
			}
			else
			{            
				PlayNote(65, 250);
				
				entering = 0;
				rickState = 3;    
				cam1 = false;
				cam2 = false;
				cam3 = true;
				feedBlockTime = Ticks + 30;
			}
			
			break;
	}
	
	UpdateRickInCamera();
}

void Camera1()
{
	camera = 1;       
	char* text = "CAM 1";
	MemCopy(text, camText, 5);     
	((PictureObject*)screenObj->Data)->Data = cameraScreens[1]; 
	UpdateRickInCamera();
	PlayNote(33, 150);
}  

void Camera2()
{
	camera = 2;     
	char* text = "CAM 2";
	MemCopy(text, camText, 5);  
	((PictureObject*)screenObj->Data)->Data = cameraScreens[2]; 
	UpdateRickInCamera();
	PlayNote(33, 150);
}  

void Camera3()
{
	camera = 3;     
	char* text = "CAM 3";
	MemCopy(text, camText, 5);  
	((PictureObject*)screenObj->Data)->Data = cameraScreens[3];
	UpdateRickInCamera();
	PlayNote(33, 150);
}  

void ToggleLeftDoor()
{
	if (battery <= 0)
		PlayNote(65, 500);
	else if (doorState == 1)
	{                                                   
		doorState = 0;         
		PlayNote(33, 200);      
		((ButtonObject*)leftDoorBtn->Data)->IdlePicture = &Unlocked;
		((ButtonObject*)leftDoorBtn->Data)->HoverPicture = &Unlocked;
	}
	else
	{                                                   
		doorState = 1;     
		PlayNote(33, 200);    
		((ButtonObject*)leftDoorBtn->Data)->IdlePicture = &Locked;
		((ButtonObject*)leftDoorBtn->Data)->HoverPicture = &Locked;
		((ButtonObject*)rightDoorBtn->Data)->IdlePicture = &Unlocked;
		((ButtonObject*)rightDoorBtn->Data)->HoverPicture = &Unlocked;
	}
}  

void ToggleRightDoor()
{
	if (battery <= 0)
		PlayNote(65, 500);
	else if (doorState == 2)
	{                                               
		doorState = 0;        
		PlayNote(33, 200);    
		((ButtonObject*)rightDoorBtn->Data)->IdlePicture = &Unlocked;
		((ButtonObject*)rightDoorBtn->Data)->HoverPicture = &Unlocked;
	}
	else
	{                                   
		doorState = 2;        
		PlayNote(33, 200);    
		((ButtonObject*)leftDoorBtn->Data)->IdlePicture = &Unlocked;
		((ButtonObject*)leftDoorBtn->Data)->HoverPicture = &Unlocked;
		((ButtonObject*)rightDoorBtn->Data)->IdlePicture = &Locked;
		((ButtonObject*)rightDoorBtn->Data)->HoverPicture = &Locked;
	}
}  

extern "C" void Main()
{	                      
	currentScene = NewScene();	
	PlayMusic(Minecraft, MUSIC_INFINITE_LOOP); 
	
	Timer* timer = NewTimer();
	
	while (1)
	{
		switch (currentScreen)
		{
			case 0:
			{
				ResetScene(currentScene);  
				
				Camera = { 0, 0 };
		
				LinkToScene(AddPictureObject(&Dirt, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), currentScene);
				LinkToScene(AddPictureObject(&Brainrotexe, 0, 35, 30, 1), currentScene);
				
				char* startStr = "Start";
				LinkToScene(AddTextObject(startStr, 0, 140, 111, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);	   
				
				char* rebootStr = "Reboot";
				LinkToScene(AddTextObject(rebootStr, 0, 136, 146, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);

				LinkToScene(AddButtonObject(&Button, &HoverButton, &DisabledButton, 0, 80, 105, 1, 160, 26, ModeMenu), currentScene);
				LinkToScene(AddButtonObject(&Button, &HoverButton, &DisabledButton, 0, 80, 140, 1, 160, 26, Reboot), currentScene);
				
				while (currentScreen == 0);
				break;
			}
			case 1:
			{
				ResetScene(currentScene); 
		
				LinkToScene(AddPictureObject(&Dirt, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), currentScene);
				
				char* selectStr = "Select a mode";
				LinkToScene(AddTextObject(selectStr, 0, 108, 15, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);		  
				
				char* poemStr = "Stupid poem";
				LinkToScene(AddTextObject(poemStr, 0, 112, 51, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);		  
				
				char* odarStr = "One Day at Rick's";
				LinkToScene(AddTextObject(odarStr, 0, 92, 86, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);	  
				
				char* usebStr = "Crash";
				LinkToScene(AddTextObject(usebStr, 0, 140, 121, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);	  
				
				char* titleStr = "Title Screen";
				LinkToScene(AddTextObject(titleStr, 0, 112, 156, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);

				LinkToScene(AddButtonObject(&Button, &HoverButton, &DisabledButton, 0, 80, 45, 1, 160, 26, StupidPoem), currentScene);
				LinkToScene(AddButtonObject(&Button, &HoverButton, &DisabledButton, 0, 80, 80, 1, 160, 26, ODaR), currentScene);
				LinkToScene(AddButtonObject(&Button, &HoverButton, &DisabledButton, 0, 80, 115, 1, 160, 26, Crash), currentScene);     
				LinkToScene(AddButtonObject(&Button, &HoverButton, &DisabledButton, 0, 80, 150, 1, 160, 26, MainMenu), currentScene);
				
				while (currentScreen == 1);
				break;
			}
			case 2:
			{    
				ResetScene(currentScene);	 
				
				for (int i = 0; i < 13; i++)
					FlagPictureCacheUsage(rainbowCursors[i]);
			
				int x = 50;
				int minY = SCREEN_HEIGHT;
				int spacing = 24;
				
				int color1 = 0x80FFFF;
				int color2 = 0x80FF80; 
				int color3 = 0xFFE080; 
				int color4[] = { 0xC0C000, 0xFFFF80 }; 

				LinkToScene(AddPictureObject(&Dirt, 256, 0, 0, 0, SCREEN_WIDTH, 720), currentScene); 
				
				char* str1 = "I see the malware tester";
				LinkToScene(AddTextObject(str1, 224, x, minY, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str2 = "you mean...";
				LinkToScene(AddTextObject(str2, 224, x, minY + spacing, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str3 = "MalwareLab150?";
				LinkToScene(AddTextObject(str3, 224, x, minY + spacing * 2, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str4 = "nFire?";
				LinkToScene(AddTextObject(str4, 224, x, minY + spacing * 3, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str5 = "Siam Alam???";
				LinkToScene(AddTextObject(str5, 224, x, minY + spacing * 4, 2, HEX_COLOR(color1), TRANSPARENT), currentScene); 
				
				char* str6 = "Whoever the hell you are";
				LinkToScene(AddTextObject(str6, 224, x, minY + spacing * 5, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str7 = "I hope you enjoyed this...";
				LinkToScene(AddTextObject(str7, 224, x, minY + spacing * 6, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str8 = "whatever the hell this was";
				LinkToScene(AddTextObject(str8, 224, x, minY + spacing * 7, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str9 = "This took over a year to";
				LinkToScene(AddTextObject(str9, 224, x, minY + spacing * 8, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str10 = "make, mostly from figuring";
				LinkToScene(AddTextObject(str10, 224, x, minY + spacing * 9, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str11 = "out how to do stuff in";
				LinkToScene(AddTextObject(str11, 224, x, minY + spacing * 10, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str12 = "the first place, since most";
				LinkToScene(AddTextObject(str12, 224, x, minY + spacing * 11, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str13 = "documentation is older";
				LinkToScene(AddTextObject(str13, 224, x, minY + spacing * 12, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str14 = "than me for some reason...";
				LinkToScene(AddTextObject(str14, 224, x, minY + spacing * 13, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);    
				
				char* str15 = "...and yet, I made it...";
				LinkToScene(AddTextObject(str15, 224, x, minY + spacing * 14, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str16 = "I. I. I am alive.";
				LinkToScene(AddTextObject(str16, 224, x, minY + spacing * 15, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);   
				
				char* str17 = "...Windows is dead however";
				LinkToScene(AddTextObject(str17, 224, x, minY + spacing * 16, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str18 = "and the universe said rip bozo";
				LinkToScene(AddTextObject(str18, 224, x, minY + spacing * 17, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);    
				
				char* str19 = "and the universe said get rekt";
				LinkToScene(AddTextObject(str19, 224, x, minY + spacing * 18, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str20 = "and the universe said";
				LinkToScene(AddTextObject(str20, 224, x, minY + spacing * 19, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);   
				
				char* str21 = "you are an idiot hahahahahahahahahahahahah";
				LinkToScene(AddTextObject(str21, 224, x, minY + spacing * 20, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str22 = "and the universe said free vbux";
				LinkToScene(AddTextObject(str22, 224, x, minY + spacing * 21, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);   
		
				LinkToScene(AddPictureObject(&Transition1, 256, 0, 720, 0), currentScene);                
				
				LinkToScene(AddPictureObject(&YAAI, 256, 0, 720 + Transition1.Height, 0, SCREEN_WIDTH, 704), currentScene);    
		
				LinkToScene(AddPictureObject(&Transition2, 256, 0, 1424 + Transition1.Height, 0), currentScene);      
				
				char* str23 = "and the universe said change the";
				LinkToScene(AddTextObject(str23, 224, x, minY + spacing * 22, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str24 = "mouse cursor to some late 2010s";
				LinkToScene(AddTextObject(str24, 224, x, minY + spacing * 23, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);  
				
				char* str25 = "le epic rgb 420 gamer stuff";
				LinkToScene(AddTextObject(str25, 224, x, minY + spacing * 24, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str26 = "and the universe shut the fuck up";
				LinkToScene(AddTextObject(str26, 224, x, minY + spacing * 25, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);    
				
				char* str27 = "...";
				LinkToScene(AddTextObject(str27, 224, x, minY + spacing * 26, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str28 = "...at this point I should";
				LinkToScene(AddTextObject(str28, 224, x, minY + spacing * 27, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);  
				
				char* str29 = "probably thank some people";
				LinkToScene(AddTextObject(str29, 224, x, minY + spacing * 28, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str30 = "(I'll keep it short dw)";
				LinkToScene(AddTextObject(str30, 224, x, minY + spacing * 29, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);    
				
				char* str31 = "Ok then, a thank goes out";
				LinkToScene(AddTextObject(str31, 224, x, minY + spacing * 30, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str32 = "to        and";
				LinkToScene(AddTextObject(str32, 224, x, minY + spacing * 31, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);  
				
				char* str32a = "   leurak     nikitpad";
				LinkToScene(AddTextObject(str32a, 224, x, minY + spacing * 31, 2, HEX_COLOR(color3), TRANSPARENT), currentScene);  
				
				char* str33 = "for being my inspiration to";
				LinkToScene(AddTextObject(str33, 224, x, minY + spacing * 32, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str34 = "make this kind of stuff";
				LinkToScene(AddTextObject(str34, 224, x, minY + spacing * 33, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);  
				
				char* str35 = "shout-out out to all my";
				LinkToScene(AddTextObject(str35, 224, x, minY + spacing * 34, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str36 = "favourite malware youtubers:";
				LinkToScene(AddTextObject(str36, 224, x, minY + spacing * 35, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);  
				
				char* str37 = "        ,      ,         ,";
				LinkToScene(AddTextObject(str37, 224, x, minY + spacing * 36, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);  
				
				char* str37a = "Enderman  nFire  danooct1";
				LinkToScene(AddTextObject(str37a, 224, x, minY + spacing * 36, 2, HEX_COLOR(color3), TRANSPARENT), currentScene);
				
				char* str38 = "         , and of course,";
				LinkToScene(AddTextObject(str38, 224, x, minY + spacing * 37, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);   
				
				char* str38a = "Siam Alam";
				LinkToScene(AddTextObject(str38a, 224, x, minY + spacing * 37, 2, HEX_COLOR(color3), TRANSPARENT), currentScene);
				
				char* str39 = "shout-out to my best";
				LinkToScene(AddTextObject(str39, 224, x, minY + spacing * 38, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str40 = "friends in the malware community,";
				LinkToScene(AddTextObject(str40, 224, x, minY + spacing * 39, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);  
				
				char* str41 = "         and              !";
				LinkToScene(AddTextObject(str41, 224, x, minY + spacing * 40, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);  
				
				char* str41a = "viperine     MalwareLab150";
				TextObject* mwl150 = (TextObject*)LinkToScene(AddTextObject(str41a, 224, x, minY + spacing * 40, 2, HEX_COLOR(0xFFFFC0), TRANSPARENT), currentScene)->Data;  
				
				char* str42 = "I've been busy lately so";
				LinkToScene(AddTextObject(str42, 224, x, minY + spacing * 41, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str43 = "I haven't done much but";
				LinkToScene(AddTextObject(str43, 224, x, minY + spacing * 42, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);  
				
				char* str44 = "I wanted you to know that";
				LinkToScene(AddTextObject(str44, 224, x, minY + spacing * 43, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str45 = "I'd never give you up,";
				LinkToScene(AddTextObject(str45, 224, x, minY + spacing * 44, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);  
				
				char* str46 = "I'd never let you down,";
				LinkToScene(AddTextObject(str46, 224, x, minY + spacing * 45, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str47 = "I'd never run around and";
				LinkToScene(AddTextObject(str47, 224, x, minY + spacing * 46, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);  
				
				char* str48 = "desert you, I'd never make";
				LinkToScene(AddTextObject(str48, 224, x, minY + spacing * 47, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str49 = "you cry, I'd never say";
				LinkToScene(AddTextObject(str49, 224, x, minY + spacing * 48, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str50 = "goodbye, I'd never tell";
				LinkToScene(AddTextObject(str50, 224, x, minY + spacing * 49, 2, HEX_COLOR(color2), TRANSPARENT), currentScene);
				
				char* str51 = "a lie and hurt you...";
				LinkToScene(AddTextObject(str51, 224, x, minY + spacing * 50, 2, HEX_COLOR(color1), TRANSPARENT), currentScene);
				
				char* str52 = "Made with <3 by AleX-1337";
				LinkToScene(AddTextObject(str52, 224, x, minY + spacing * 51, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene); 
				
				char* str53 = "youtube.com/@YT-AleX-1337";
				LinkToScene(AddTextObject(str53, 224, x, minY + spacing * 52, 2, HEX_COLOR(0xC0C0FF), TRANSPARENT), currentScene); 
				
				LinkToScene(AddPictureObject(&Brainrotexe, 168, 35, (minY + spacing * 57) * 3 / 4, 2), currentScene);  
				
				int frame = 0;
				
				ResetTimer(timer);
				
				while (currentScreen == 2)
				{      
					if (frame >= 670 && frame < 1680)
						SetCursorPicture(rainbowCursors[frame % 10]);
					else if (frame >= 1680 && frame < 1682)  
						SetCursorPicture(rainbowCursors[0]);
					else if (frame >= 1682 && frame < 1688)  
						SetCursorPicture(rainbowCursors[(frame - 1682) / 2 + 10]);
					else if (frame == 1688)
						SetCursorPicture(NULL);
					
					if (frame >= 1000 && frame < 1400)
						mwl150->ForegroundColor = HEX_COLOR(color4[frame / 2 % 2]);
					
					if (frame == 1220)
						PlayMusic(Rick);
					
					if (frame == 1566)
						PlayMusic(Rick2); 
					
					SleepTimer(timer, 100);
					ResetTimer(timer);
					
					if (frame < 1680 || frame >= 1730)
					{
						Camera.Y++;
					}   
					if (frame >= 1930)
					{
						MainMenu();
						PlayMusic(Minecraft, MUSIC_INFINITE_LOOP);
						ResetCursor();                             
						SetCursorPicture(&Cursor);
					}
					
					frame++;
				}
				
				for (int i = 0; i < 13; i++)
					UnflagPictureCacheUsage(rainbowCursors[i]);
				
				break;
			}
			case 3:
			{
				ResetScene(currentScene);
				StopSound();                       
				SetCursorPicture(NULL); 
				
				Sleep(50); 
				PlayNote(44, 300);    
				
				bool skip = false;
				bool space = false;
				bool enter = false;
				
				while (1)
				{
					char* howToStr = "HOW TO PLAY";
					LinkToScene(AddTextObject(howToStr, 0, 116, 30, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* commandsStr = "[Space] Next     [Enter] Skip";
					GraphicObject* commandText = LinkToScene(AddTextObject(commandsStr, 0, 4, 180, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht1aStr = "Rick wants to roll you! You need";
					GraphicObject* ht1aText = LinkToScene(AddTextObject(ht1aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht1bStr = "to protect yourself...";
					GraphicObject* ht1bText = LinkToScene(AddTextObject(ht1bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht1aText->Visible = false;
					ht1bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht2aStr = "You have a tablet where you can";
					GraphicObject* ht2aText = LinkToScene(AddTextObject(ht2aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht2bStr = "check Rick on cameras, and you";
					GraphicObject* ht2bText = LinkToScene(AddTextObject(ht2bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht2aText->Visible = false;
					ht2bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht3aStr = "can also close one of the";
					GraphicObject* ht3aText = LinkToScene(AddTextObject(ht3aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht3bStr = "doors if you need to (not both)";
					GraphicObject* ht3bText = LinkToScene(AddTextObject(ht3bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht3aText->Visible = false;
					ht3bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht4aStr = "Keep in mind, however, you have";
					GraphicObject* ht4aText = LinkToScene(AddTextObject(ht4aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht4bStr = "very little power available!";
					GraphicObject* ht4bText = LinkToScene(AddTextObject(ht4bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht4aText->Visible = false;
					ht4bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht5aStr = "Sometimes Ricks disappears off";
					GraphicObject* ht5aText = LinkToScene(AddTextObject(ht5aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht5bStr = "camera, and in that case you";
					GraphicObject* ht5bText = LinkToScene(AddTextObject(ht5bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht5aText->Visible = false;
					ht5bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht6aStr = "have to remember where he";
					GraphicObject* ht6aText = LinkToScene(AddTextObject(ht6aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht6bStr = "last was: if he last was on";
					GraphicObject* ht6bText = LinkToScene(AddTextObject(ht6bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht6aText->Visible = false;
					ht6bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht7aStr = "camera 1 (left hallway),";
					GraphicObject* ht7aText = LinkToScene(AddTextObject(ht7aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht7bStr = "quickly close the left door!";
					GraphicObject* ht7bText = LinkToScene(AddTextObject(ht7bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht7aText->Visible = false;
					ht7bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht8aStr = "If he last was on camera 2";
					GraphicObject* ht8aText = LinkToScene(AddTextObject(ht8aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht8bStr = "(right hallway), the right door!";
					GraphicObject* ht8bText = LinkToScene(AddTextObject(ht8bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht8aText->Visible = false;
					ht8bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht9aStr = "You can close the doors with the";
					GraphicObject* ht9aText = LinkToScene(AddTextObject(ht9aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht9bStr = "buttons on the far ends of the desk";
					GraphicObject* ht9bText = LinkToScene(AddTextObject(ht9bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht9aText->Visible = false;
					ht9bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht10aStr = "When Rick goes away from a";
					GraphicObject* ht10aText = LinkToScene(AddTextObject(ht10aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht10bStr = "door, a sound will play, and";
					GraphicObject* ht10bText = LinkToScene(AddTextObject(ht10bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht10aText->Visible = false;
					ht10bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht11aStr = "he'll retreat to camera 3 (stage).";
					GraphicObject* ht11aText = LinkToScene(AddTextObject(ht11aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht11bStr = "DO NOT CLOSE THE WRONG DOOR!";
					GraphicObject* ht11bText = LinkToScene(AddTextObject(ht11bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);    
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					if (skip)
						break;
					
					ht11aText->Visible = false;
					ht11bText->Visible = false;
					
					PlayNote(44, 300);  
					
					char* ht12aStr = "Your shift ends at 4 PM.";
					LinkToScene(AddTextObject(ht12aStr, 0, 40, 80, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					char* ht12bStr = "Good luck!";
					LinkToScene(AddTextObject(ht12bStr, 0, 40, 100, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
					
					while (1)
					{
						if (!(KBStatus[KB_KEY_SPACE] || space))
							space = true;
						if (KBStatus[KB_KEY_SPACE] && space)
						{
							space = false;
							break;
						}
						
						if (!(KBStatus[KB_KEY_ENTER] || enter))
							enter = 1;
						if (KBStatus[KB_KEY_ENTER])
						{
							enter = false;
							skip = true;
							break;
						}
					}
					
					break;
				}
				
				ResetScene(currentScene);
				
				PlayNote(44, 300);  
				
				char* dayStr = "Day 1";
				TextObject* dayText = (TextObject*)LinkToScene(AddTextObject(dayStr, 0, 140, 88, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene)->Data; 
				
				char* timeStr = "8:00 AM";
				TextObject* timeText = (TextObject*)LinkToScene(AddTextObject(timeStr, 0, 132, 112, 2, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene)->Data; 
				
				Sleep(1950);
				
				for (int i = 15; i >= 0; i--)
				{
					dayText->ForegroundColor = HEX_COLOR(0xF0F0F0 / 15 * i);
					timeText->ForegroundColor = HEX_COLOR(0xF0F0F0 / 15 * i);
					
					Sleep(100);
				}          
				
				ResetScene(currentScene);  
				
				time = 0;
				tablet = false;    
				camera = 3;
				char* text = "CAM 3";
				MemCopy(text, camText, 5); 
				battery = 1500;
				rickState = 3;              
				doorState = 0;
				
				ResetCursor();                             
				SetCursorPicture(&Cursor);

				LinkToScene(AddPictureObject(&Office1, 128, -40, 0, 0), currentScene); 
				LinkToScene(AddPictureObject(&Office2, 192, -60, 0, 1), currentScene); 
				
				GraphicObject* tabletObj = LinkToScene(AddPictureObject(&Tablet, 0, 0, 200, 4), currentScene);   
				screenObj = LinkToScene(AddPictureObject(&Screen0, 0, 0, 200, 3), currentScene);    		
				
				for (int i = 1; i < 4; i++)
					FlagPictureCacheUsage(cameraScreens[i]);  
                
				jumpscareObj = LinkToScene(AddPictureObject(&Rollscare, 0, 0, 200, 10), currentScene);
				
				GraphicObject* hereObj = LinkToScene(AddPictureObject(&Here, 0, 249, 126, 6), currentScene);
				UIObject* cam1Obj = LinkToScene(AddButtonObject(&Cam1, NULL, 0, 238, 112, 6, 20, 12, Camera1), currentScene);		
				UIObject* cam2Obj = LinkToScene(AddButtonObject(&Cam2, NULL, 0, 260, 112, 6, 20, 12, Camera2), currentScene);
				UIObject* cam3Obj = LinkToScene(AddButtonObject(&Cam3, NULL, 0, 249, 98, 6, 20, 12, Camera3), currentScene);        
				
				rickObj = LinkToScene(AddPictureObject(&RickC3, 0, 0, 0, 4), currentScene);         
				FlagPictureCacheUsage(&RickC1);         
				FlagPictureCacheUsage(&RickC2); //PROBLEMATICO DOPO IL COMPLETAMENTO  
				
				GraphicObject* camTextObj = LinkToScene(AddTextObject(camText, 0, 36, 36, 6, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
				GraphicObject* recObj = LinkToScene(AddPictureObject(&Rec, 0, 268, 36, 6), currentScene);
				feedBlockObj = LinkToScene(AddPictureObject(&FeedBlock, 0, 0, 0, 5), currentScene);
				
				hereObj->Visible = false;
				cam1Obj->Enabled = false;
				cam2Obj->Enabled = false;
				cam3Obj->Enabled = false;
				
				rickObj->Visible = false;

				camTextObj->Visible = false;
				recObj->Visible = false;
				feedBlockObj->Visible = false;
				
				LinkToScene(AddPictureObject(&TabletButton, 0, 5, 176, 2), currentScene)->Data;
				HoverObject* tabletBtn = (HoverObject*)LinkToScene(AddHoverObject(0, 0, 176, 2, 320, 35, OpenTablet), currentScene)->Data;
				
				LinkToScene(AddPictureObject(&ButtonCase, 256, -72, 50, 1), currentScene);
				LinkToScene(AddPictureObject(&ButtonCase, 256, 360, 50, 1), currentScene);  
				leftDoorBtn = LinkToScene(AddButtonObject(&Unlocked, NULL, 256, -68, 54, 2, 24, 24, ToggleLeftDoor), currentScene);
				rightDoorBtn = LinkToScene(AddButtonObject(&Unlocked, NULL, 256, 364, 54, 1, 24, 24, ToggleRightDoor), currentScene); 
				
				FlagPictureCacheUsage(&Locked);
				FlagPictureCacheUsage(&Unavailable);
				
				LinkToScene(AddPictureObject(&ButtonBar, 256, -80, 63, 1), currentScene);
				LinkToScene(AddPictureObject(&ButtonBar, 256, 392, 63, 1), currentScene);
				
				char* times[] = { " 8 AM", " 9 AM", "10 AM", "11 AM", "12 PM", " 1 PM", " 2 PM", " 3 PM" }; 
				
				char* timeStr2 = (char*)MemAlloc(sizeof(char) * 6);
				GraphicObject* timeObj = LinkToScene(AddTextObject(timeStr2, 0, 276, 4, 6, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);  
				
				char* batteryStr = (char*)MemAlloc(sizeof(char) * 4);
				GraphicObject* batteryObj = LinkToScene(AddTextObject(batteryStr, 0, 4, 4, 6, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);   
				
				int prevHour = -1;
				int prevPerc = -1;
				int tabletState = 0;
				
				ResetTimer(timer); 
				
				while (currentScreen == 3)
				{					
					int hour = time / 400;
					if (hour < 9 && hour != prevHour)
					{
						MemCopy(times[hour], timeStr2, sizeof(char) * 6);
						prevHour = hour;
					} 

					int perc = (battery + 9) / 15; 
					if (perc >= 0 && perc != prevPerc)
					{                            
						if (perc == 0)
							((TextObject*)batteryObj->Data)->ForegroundColor = HEX_COLOR(0xFF0000);
						else if (perc <= 10)
							((TextObject*)batteryObj->Data)->ForegroundColor = HEX_COLOR(0xFFC000);
						else if (perc <= 30)
							((TextObject*)batteryObj->Data)->ForegroundColor = HEX_COLOR(0xFFE000);
						
						ItoA(perc, batteryStr);
						StrCat(batteryStr, "%");
						prevPerc = perc;
					} 
					
					if (tablet)
					{
						if (tabletState < 3)
						{
							if (tabletState == 0)
							{
								timeObj->Visible = false;
								batteryObj->Visible = false;
								PlayNote(33, 150);
							}
							
							tabletObj->Y = 200 - tabletState * 100;
							screenObj->Y = 200 - tabletState * 100;
							tabletState++;
						}
						else if (tabletState == 3)
						{       
							hereObj->Visible = true;
							cam1Obj->Enabled = true;
							cam2Obj->Enabled = true;
							cam3Obj->Enabled = true;
							
							UpdateRickInCamera();
							rickObj->Visible = true;
							
							tabletBtn->OnHover = CloseTablet;  
							camTextObj->Visible = true;
							batteryObj->X = 36;
							batteryObj->Y = 124;
							batteryObj->Visible = true; 
							((PictureObject*)screenObj->Data)->Data = cameraScreens[camera];
							tabletState++;
						}
						else
						{
							if (!(time % 5))
								recObj->Visible = time / 5 % 2;       
	
							if (Ticks < feedBlockTime && (cam1 && camera == 1 || cam2 && camera == 2 || cam3 && camera == 3))
								feedBlockObj->Visible = true;
							else
								feedBlockObj->Visible = false;
						}
					}
					else
					{     				
						if (tabletState > 1)
						{   
							if (tabletState == 3)
							{
								PlayNote(33, 150);
				
								((PictureObject*)screenObj->Data)->Data = cameraScreens[0];
								
								hereObj->Visible = false;
								cam1Obj->Enabled = false;
								cam2Obj->Enabled = false;
								cam3Obj->Enabled = false;  
								
								rickObj->Visible = false;
								
								recObj->Visible = false; 
								camTextObj->Visible = false;
								batteryObj->Visible = false;
								feedBlockObj->Visible = false;
							}
							
							tabletObj->Y = 200 - (tabletState - 2) * 100;
							screenObj->Y = 200 - (tabletState - 2) * 100;
							tabletState--;
						}
						else if (tabletState == 1)
						{                              
							timeObj->Visible = true;    
							batteryObj->X = 4;
							batteryObj->Y = 4;
							batteryObj->Visible = true; 
							tabletBtn->OnHover = OpenTablet; 
							tabletState--;
						}
						
						if (MouseCursor.X <= 50 && Camera.X > -80)
							Camera.X -= 10;
						else if (MouseCursor.X >= 270 && Camera.X < 80)
							Camera.X += 10;  
					}       
					
					SleepTimer(timer, 100);  
					ResetTimer(timer); 
					
					if (doorState > 0)
						battery--;
					if (tablet)
						battery--;
					if (battery == 0)
					{               
						tablet = false;
						doorState = 0;
						((ButtonObject*)leftDoorBtn->Data)->IdlePicture = &Unavailable;
						((ButtonObject*)leftDoorBtn->Data)->HoverPicture = &Unavailable;
						((ButtonObject*)rightDoorBtn->Data)->IdlePicture = &Unavailable;
						((ButtonObject*)rightDoorBtn->Data)->HoverPicture = &Unavailable;
					}
					
					if (!(time % 5))
						RickMovementOpportunity();
					
					time++;  

					if (time >= 3200)
						break;
				}       
                
				((ButtonObject*)leftDoorBtn->Data)->IdlePicture = &Unlocked;
				((ButtonObject*)leftDoorBtn->Data)->HoverPicture = &Unlocked;
				((ButtonObject*)rightDoorBtn->Data)->IdlePicture = &Unlocked;
				((ButtonObject*)rightDoorBtn->Data)->HoverPicture = &Unlocked;
				
				((PictureObject*)rickObj->Data)->Data = &RickC3;   
				((PictureObject*)screenObj->Data)->Data = cameraScreens[0];
				
				ResetScene(currentScene);   
				
				for (int i = 1; i < 4; i++)
					UnflagPictureCacheUsage(cameraScreens[i]); 
				
				UnflagPictureCacheUsage(&RickC1);
				UnflagPictureCacheUsage(&RickC2); 
				
				UnflagPictureCacheUsage(&Locked);
				UnflagPictureCacheUsage(&Unavailable);
				
				SetCursorPicture(NULL); 
				
				char* pmStr = " PM";
				LinkToScene(AddTextObject(pmStr, 0, 152, 92, 0, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
				
				LinkToScene(AddPictureObject(&Black, 0, 144, 68, 1), currentScene);
				
				char* threeStr = "3";
				GraphicObject* threeObj = LinkToScene(AddTextObject(threeStr, 0, 144, 92, 0, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
				
				char* fourStr = "4";
				GraphicObject* fourObj = LinkToScene(AddTextObject(fourStr, 0, 144, 116, 0, HEX_COLOR(0xFFFFFF), TRANSPARENT), currentScene);
				
				PlayMusic(Bells);
				
				Sleep(2000);
				
				Timer* pixelTimer = NewTimer();
				
				for (int i = 0; i < 24; i++)
				{
					ResetTimer(pixelTimer);
					
					threeObj->Y--;
					fourObj->Y--;
					
					SleepTimer(pixelTimer, 200);
				}
				
				Sleep(13000);
				
				MainMenu();
				PlayMusic(Minecraft, MUSIC_INFINITE_LOOP);
				ResetCursor();                             
				SetCursorPicture(&Cursor);
				
				break;
			}
		}
	}
}