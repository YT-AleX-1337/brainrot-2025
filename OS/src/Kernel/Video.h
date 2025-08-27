#pragma once            

typedef struct
{
	uint16_t Width;
	uint8_t Height;
	uint8_t* CompressedPixelData;  
	uint8_t* CachedPixelData;
	int UsingCache;
} __attribute__((packed)) Picture;

typedef struct GraphicObject GraphicObject;
struct GraphicObject
{
	GraphicObject* PrevObject;
	GraphicObject* NextObject;
	uint8_t Type;    
	bool Visible;    
	int CameraMultiplier;
	int X;
	int Y;         
	int Z;
	void* Data; //Pointer to another struct
} __attribute__((packed));

typedef enum
{
	GRAPHIC_OBJECT_TYPE_PICTURE,
	GRAPHIC_OBJECT_TYPE_TEXT,
} GRAPHIC_OBJECT_TYPES;

typedef struct
{               
	Picture* Data;
	int Width;								//0 for full picture, other values for variably sized and offset picture
	int Height;
	int XOffset;
	int YOffset;
} __attribute__((packed)) PictureObject;	//Type 0

typedef struct
{               
	char* Text;
	int Length;
	uint8_t ForegroundColor;
	uint8_t BackgroundColor;
} __attribute__((packed)) TextObject;		//Type 1

#define VGA_DAC_MASK_PORT	0x03C6
#define VGA_DAC_READ_PORT	0x03C7
#define VGA_DAC_WRITE_PORT	0x03C8
#define VGA_DAC_IO_PORT		0x03C9

#define FRONT_PIXEL(x, y)		VGAMemory[(x) + (y) * SCREEN_WIDTH]
#define BACK_PIXEL(x, y)		BackBuffer[(x) + (y) * SCREEN_WIDTH]
#define COLOR(r, g, b)			((r) / 51 * 36 + (g) / 51 * 6 + (b) / 51)
#define HEX_COLOR(hex)			COLOR((hex) >> 16, (hex) >> 8 & 0xFF, (hex) & 0xFF)
#define VGA_CHAR(c)				(VGAFont + (c) * 16)
#define VGA_CHAR_PIXEL(c, x, y)	((VGA_CHAR(c)[y] & 0x80 >> (x)) >> (7 - (x)))

#define SCREEN_WIDTH	320
#define SCREEN_HEIGHT	200

#define TRANSPARENT 0xFF

extern uint8_t* VGAMemory;
extern uint8_t* VGAFont;   
   
extern uint8_t* BackBuffer;

extern GraphicObject* FirstGraphicObject; 

extern Vector2 Camera; 

extern void VGA_Initialize();

extern uint8_t GetPixel(uint8_t color, int x, int y);
extern void SetPixel(uint8_t color, int x, int y);

extern void FlagPictureCacheUsage(Picture* picture);
extern void UnflagPictureCacheUsage(Picture* picture);

extern GraphicObject* AddGraphicObject(GraphicObject* object, int z); 
extern GraphicObject* AddPictureObject(Picture* picture, int cameraMultiplier, int x, int y, int z); 
extern GraphicObject* AddPictureObject(Picture* picture, int cameraMultiplier, int x, int y, int z, int width, int height);
extern GraphicObject* AddPictureObject(Picture* picture, int cameraMultiplier, int x, int y, int z, int width, int height, int xOffset, int yOffset);
extern GraphicObject* AddTextObject(char* text, int cameraMultiplier, int x, int y, int z, uint8_t fgColor, uint8_t bgColor);

extern void RemoveGraphicObject(GraphicObject* object);