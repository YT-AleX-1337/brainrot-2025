#pragma once             

#include "Video.h"

typedef struct UIObject UIObject;
struct UIObject
{
	UIObject* PrevObject;
	UIObject* NextObject;
	uint8_t Type;         
	bool Enabled; 
	int CameraMultiplier;
	int X;
	int Y;         
	int Z;
	void* Data; //Pointer to another struct
} __attribute__((packed));  

typedef enum
{
	UI_OBJECT_TYPE_BUTTON,
	UI_OBJECT_TYPE_HOVER
} UI_OBJECT_TYPES;

typedef struct
{               
	int Width;
	int Height;
	GraphicObject* GraphicButton;
	Picture* IdlePicture;
	Picture* HoverPicture;
	Picture* DisabledPicture;
	Procedure OnClick;
} __attribute__((packed)) ButtonObject;	//Type 0

typedef struct
{               
	int Width;
	int Height;
	GraphicObject* GraphicButton;
	Picture* IdlePicture;
	Picture* HoverPicture; 
	Picture* DisabledPicture;
	Procedure OnHover;
} __attribute__((packed)) HoverObject;	//Type 1

extern UIObject* FirstUIObject;

extern void UI_Initialize();

extern UIObject* AddUIObject(UIObject* object, int z);  
extern UIObject* AddButtonObject(int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick);  
extern UIObject* AddButtonObject(Picture* idlePicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick); 
extern UIObject* AddButtonObject(Picture* idlePicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick); 
extern UIObject* AddButtonObject(Picture* idlePicture, Picture* hoverPicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick); 
extern UIObject* AddHoverObject(int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover);  
extern UIObject* AddHoverObject(Picture* idlePicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover); 
extern UIObject* AddHoverObject(Picture* idlePicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover); 
extern UIObject* AddHoverObject(Picture* idlePicture, Picture* hoverPicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover); 

extern void RemoveUIObject(UIObject* object);