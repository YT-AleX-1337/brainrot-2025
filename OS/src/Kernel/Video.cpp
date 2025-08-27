#include "Kernel.h" 

uint8_t* VGAMemory = (uint8_t*)0xA0000;
uint8_t* VGAFont = (uint8_t*)0x6000;

uint8_t* BackBuffer = (uint8_t*)0x100000;   

GraphicObject* FirstGraphicObject = NULL;

Vector2 Camera = { 0, 0 };

void Graphics_Update()
{            
	if (Ticks % 4) //25 FPS
		return;

	MemSet(BackBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
    
	GraphicObject* obj = FirstGraphicObject;
	
	while (obj)
	{    
		int x = obj->X - Camera.X * obj->CameraMultiplier / 256;   
		int y = obj->Y - Camera.Y * obj->CameraMultiplier / 256;
		
		if (!obj->Visible || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)  
		{            
			obj = obj->NextObject;
			continue;
		}
		
		if (obj->Type == GRAPHIC_OBJECT_TYPE_PICTURE)
		{       
			PictureObject* data = (PictureObject*)obj->Data;			
			Picture* picture = data->Data;
			
			if (!picture)
			{            
				obj = obj->NextObject;
				continue;
			}
			
			if (data->Width == 0)
			{			
				data->Width = picture->Width;
				data->Height = picture->Height;
			}
			
			if (x + data->Width < 0 || y + data->Height < 0)
			{            
				obj = obj->NextObject;
				continue;
			}
			
			for (int i = (x > 0 ? x : 0); i < (x + data->Width < SCREEN_WIDTH ? x + data->Width : SCREEN_WIDTH); i++)
				for (int j = (y > 0 ? y : 0); j < (y + data->Height < SCREEN_HEIGHT ? y + data->Height : SCREEN_HEIGHT); j++)
					SetPixel(picture->CachedPixelData[(i - x + data->XOffset) % picture->Width + (j - y + data->YOffset) % picture->Height * picture->Width], i, j);
		}   
		else if (obj->Type == GRAPHIC_OBJECT_TYPE_TEXT)
		{
			TextObject* data = (TextObject*)obj->Data;
			char* text = data->Text;   
			
			if (x + data->Length * 8 < 0 || y < -15)
			{            
				obj = obj->NextObject;
				continue;
			}
			
			for (int h = 0; text[h] != '\0'; h++)
			{
				if (x + h * 8 < -7 || x >= SCREEN_WIDTH)
					continue;
				
				for (int i = 0; i < 8; i++)
					for (int j = 0; j < 16; j++)
					{
						SetPixel(VGA_CHAR_PIXEL(text[h], i, j) ? data->ForegroundColor : data->BackgroundColor, x + h * 8 + i, y + j);
					}
			}
		}
		
		obj = obj->NextObject;
	}

	MemCopy(BackBuffer, VGAMemory, SCREEN_WIDTH * SCREEN_HEIGHT);
}

void VGA_Initialize()
{   	                       	
	//Setup VGA palette
	OutB(VGA_DAC_MASK_PORT, 0xFF); //Make sure the DAC mask registry is set to 0xFF (it should already be)
	OutB(VGA_DAC_WRITE_PORT, 0); //Start writing from color 0
	
	/*
	  Colors 0-215 in the new VGA palette cover a lot of the RGB space.
	  To calculate the RGB value of color n:
	
	  Bx = n % 6
	  Gx = (n % 36 - Bx) / 6
	  Rx = (n % 216 - Bx - Gx) / 36
	  
	  R = Rx / 5 * 255
	  G = Gx / 5 * 255
	  B = Bx / 5 * 255
	*/
	
	//Set colors 0-215
	for (int r = 0; r < 6; r++)
		for (int g = 0; g < 6; g++)
			for (int b = 0; b < 6; b++)
			{
				OutB(VGA_DAC_IO_PORT, r * 63 / 5); //Red
				OutB(VGA_DAC_IO_PORT, g * 63 / 5); //Green
				OutB(VGA_DAC_IO_PORT, b * 63 / 5); //Blue
			}
	
	//Colors 216-255 are set to black
	for (int i = 216; i < 256; i++)
		for (int j = 0; j < 3; j++)
			OutB(VGA_DAC_IO_PORT, 0);
	
	//Clear buffers
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		VGAMemory[i] = TRANSPARENT;
		BackBuffer[i] = TRANSPARENT;
	}
	
	AddTask(Graphics_Update);
}  

void SetPixel(uint8_t color, int x, int y)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT || color == TRANSPARENT)
		return;
	
	BACK_PIXEL(x, y) = color;
}

uint8_t GetPixel(uint8_t color, int x, int y)
{             
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return TRANSPARENT;
	
	return FRONT_PIXEL(x, y);
}

void FlagPictureCacheUsage(Picture* picture)
{             
	if (!picture)
		return; 
	
	picture->UsingCache++;
	
	if (!picture->CachedPixelData)
	{
		uint8_t* pixels = (uint8_t*)MemAlloc(picture->Width * picture->Height);

		int k = 0;
		int n = picture->CompressedPixelData[k + 1]; 
		
		for (int i = 0; i < picture->Width * picture->Height; i++)
		{
			pixels[i] = picture->CompressedPixelData[k];
			
			if (n == 0)
			{
				k += 2;
				n = picture->CompressedPixelData[k + 1];
			}
			else n--;
		}            
		
		picture->CachedPixelData = pixels;
	}
}

void UnflagPictureCacheUsage(Picture* picture)
{                   
	if (!picture || picture->UsingCache <= 0)
		return;             
	
	picture->UsingCache--; 
	
	if (picture->UsingCache == 0)
	{
		MemFree(picture->CachedPixelData);
		picture->CachedPixelData = NULL;
	}
}

GraphicObject* AddGraphicObject(GraphicObject* object, int z)
{
	if (!FirstGraphicObject)
	{
		FirstGraphicObject = object;
	}
	else if (FirstGraphicObject->Z > z)
	{                    
		FirstGraphicObject->PrevObject = object;   
		object->NextObject = FirstGraphicObject;
		FirstGraphicObject = object;
	}
	else
	{                        
		GraphicObject* lastObj = FirstGraphicObject;
		bool done = false;
		
		while (lastObj->NextObject)
		{
			if (lastObj->NextObject->Z > z)
			{
				lastObj->NextObject->PrevObject = object;  
				object->PrevObject = lastObj;
				object->NextObject = lastObj->NextObject; 
				lastObj->NextObject = object;
				
				done = true;
				break;
			}
			
			lastObj = lastObj->NextObject;
		}
		
		if (!done)
		{
			object->PrevObject = lastObj;  
			lastObj->NextObject = object;
		}
	}
	
	return object;
}               

GraphicObject* AddPictureObject(Picture* picture, int cameraMultiplier, int x, int y, int z)
{
	return AddPictureObject(picture, cameraMultiplier, x, y, z, 0, 0, 0, 0);
}                        

GraphicObject* AddPictureObject(Picture* picture, int cameraMultiplier, int x, int y, int z, int width, int height)
{
	return AddPictureObject(picture, cameraMultiplier, x, y, z, width, height, 0, 0);
}

GraphicObject* AddPictureObject(Picture* picture, int cameraMultiplier, int x, int y, int z, int width, int height, int xOffset, int yOffset)
{
	GraphicObject* obj = (GraphicObject*)MemAlloc(sizeof(GraphicObject));   
	PictureObject* data = (PictureObject*)MemAlloc(sizeof(PictureObject)); 
	
	obj->PrevObject = NULL;
	obj->NextObject = NULL;
	obj->Type = GRAPHIC_OBJECT_TYPE_PICTURE;
	obj->Visible = true;
	obj->CameraMultiplier = cameraMultiplier;
	obj->X = x;
	obj->Y = y;     
	obj->Z = z;
	obj->Data = data;
	
	data->Data = picture;
	data->Width = width;
	data->Height = height;
	data->XOffset = xOffset;
	data->YOffset = yOffset;
	
	FlagPictureCacheUsage(picture);
	
	return AddGraphicObject(obj, z);
}

GraphicObject* AddTextObject(char* text, int cameraMultiplier, int x, int y, int z, uint8_t fgColor, uint8_t bgColor)
{
	GraphicObject* obj = (GraphicObject*)MemAlloc(sizeof(GraphicObject));   
	TextObject* data = (TextObject*)MemAlloc(sizeof(TextObject)); 
	
	obj->PrevObject = NULL;
	obj->NextObject = NULL;
	obj->Type = GRAPHIC_OBJECT_TYPE_TEXT;
	obj->Visible = true;
	obj->CameraMultiplier = cameraMultiplier;
	obj->X = x;
	obj->Y = y;     
	obj->Z = z;
	obj->Data = data;
	
	int length = 0;
	while (text[length])
		length++;
	
	data->Text = text;
	data->Length = length;
	data->ForegroundColor = fgColor;
	data->BackgroundColor = bgColor;
	
	return AddGraphicObject(obj, z);
}

void RemoveGraphicObject(GraphicObject* object)
{
	if (!object)
		return;
	
	if (object->Type == GRAPHIC_OBJECT_TYPE_PICTURE)
	{
		PictureObject* data = (PictureObject*)object->Data;
		Picture* picture = data->Data;
		
		UnflagPictureCacheUsage(picture);
	}
	
	if (object->PrevObject)
		object->PrevObject->NextObject = object->NextObject;
	else
		FirstGraphicObject = object->NextObject;

	if (object->NextObject)
		object->NextObject->PrevObject = object->PrevObject;
	
	MemFree(object->Data);
	MemFree(object);
}