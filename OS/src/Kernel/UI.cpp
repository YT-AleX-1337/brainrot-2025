#include "Kernel.h"

UIObject* FirstUIObject = NULL;
int prevTotal = 0;
bool lastHover = false;

void UI_Update()
{           
	if (Ticks % 2) //50 UI checks per second
		return;
 
	int curTotal = KBTotalChanges[MOUSE_LEFT_BTN];
	bool justClicked = curTotal > prevTotal + (prevTotal % 2);
	prevTotal = curTotal;
	
	int x = MouseCursor.X;   
	int y = MouseCursor.Y;
	
	UIObject* lastObj = FirstUIObject;
	
	while (lastObj)
	{         
		if (lastObj->Type == UI_OBJECT_TYPE_BUTTON)
		{    
			ButtonObject* btnObj = (ButtonObject*)lastObj->Data;
			
			if (lastObj->Enabled)
			{				
				int rx = lastObj->X - Camera.X * lastObj->CameraMultiplier / 256;
				int ry = lastObj->Y - Camera.Y * lastObj->CameraMultiplier / 256;
		
				if (x > rx && x <= rx + btnObj->Width && y > ry && y <= ry + btnObj->Height)
				{       
					if (btnObj->GraphicButton)
					{
						PictureObject* btnPic = (PictureObject*)btnObj->GraphicButton->Data;
						btnPic->Data = btnObj->HoverPicture;
					}
					
					if (justClicked && btnObj->OnClick)
					{    
						btnObj->OnClick();
					}
				}
				else
				{         
					if (btnObj->GraphicButton)
					{
						PictureObject* btnPic = (PictureObject*)btnObj->GraphicButton->Data;
						btnPic->Data = btnObj->IdlePicture;
					}
				}
			}
			else
			{         
				if (btnObj->GraphicButton)
				{
					PictureObject* btnPic = (PictureObject*)btnObj->GraphicButton->Data;
					btnPic->Data = btnObj->DisabledPicture;
				}
			}
		}
		else if (lastObj->Type == UI_OBJECT_TYPE_HOVER)
		{    
			HoverObject* hovObj = (HoverObject*)lastObj->Data;
			
			if (lastObj->Enabled)
			{				
				int rx = lastObj->X - Camera.X * lastObj->CameraMultiplier / 256;
				int ry = lastObj->Y - Camera.Y * lastObj->CameraMultiplier / 256;
		
				if (x > rx && x <= rx + hovObj->Width && y > ry && y <= ry + hovObj->Height)
				{  
					if (hovObj->GraphicButton)
					{
						PictureObject* btnPic = (PictureObject*)hovObj->GraphicButton->Data;
						btnPic->Data = hovObj->HoverPicture;
					}
					
					if (hovObj->OnHover && !lastHover)
					{    
						hovObj->OnHover();  
						lastHover = true;
					}
				}
				else
				{          
					if (hovObj->GraphicButton)
					{
						PictureObject* btnPic = (PictureObject*)hovObj->GraphicButton->Data;
						btnPic->Data = hovObj->IdlePicture; 
					}
					
					lastHover = false;
				}
			}
			else
			{        
				if (hovObj->GraphicButton)
				{
					PictureObject* btnPic = (PictureObject*)hovObj->GraphicButton->Data;
					btnPic->Data = hovObj->DisabledPicture;
				}
			}
		}
		
		lastObj = lastObj->NextObject;
	}
} 

void UI_Initialize()
{
	AddTask(UI_Update);
}

UIObject* AddUIObject(UIObject* object, int z)
{
	if (!FirstUIObject)
	{
		FirstUIObject = object;
	}
	else if (FirstUIObject->Z > z)
	{                    
		FirstUIObject->PrevObject = object;   
		object->NextObject = FirstUIObject;
		FirstUIObject = object;
	}
	else
	{                        
		UIObject* lastObj = FirstUIObject;
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
	
UIObject* AddButtonObject(int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick)
{
	return AddButtonObject(NULL, NULL, NULL, cameraMultiplier, x, y, z, width, height, onClick);
}
	
UIObject* AddButtonObject(Picture* idlePicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick)
{
	return AddButtonObject(idlePicture, idlePicture, idlePicture, cameraMultiplier, x, y, z, width, height, onClick);
}
	
UIObject* AddButtonObject(Picture* idlePicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick)
{
	return AddButtonObject(idlePicture, idlePicture, disabledPicture, cameraMultiplier, x, y, z, width, height, onClick);
}
	
UIObject* AddButtonObject(Picture* idlePicture, Picture* hoverPicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onClick)
{
	UIObject* obj = (UIObject*)MemAlloc(sizeof(UIObject));   
	ButtonObject* data = (ButtonObject*)MemAlloc(sizeof(ButtonObject)); 
	
	obj->PrevObject = NULL;
	obj->NextObject = NULL;
	obj->Type = UI_OBJECT_TYPE_BUTTON;
	obj->Enabled = true;
	obj->CameraMultiplier = cameraMultiplier;
	obj->X = x;
	obj->Y = y;     
	obj->Z = z;
	obj->Data = data;
	
	data->Width = width;
	data->Height = height;
	data->OnClick = onClick;
	
	if (idlePicture || hoverPicture || disabledPicture)
	{
		GraphicObject* graphicButton = AddPictureObject(idlePicture, cameraMultiplier, x, y, z, width, height);
		data->GraphicButton = graphicButton;
		FlagPictureCacheUsage(hoverPicture);
		FlagPictureCacheUsage(disabledPicture);
		
		data->IdlePicture = idlePicture;
		data->HoverPicture = hoverPicture;
		data->DisabledPicture = disabledPicture;
	}
	else
	{
		data->GraphicButton = NULL; 
		data->IdlePicture = NULL;
		data->HoverPicture = NULL;
		data->DisabledPicture = NULL;
	}
	
	return AddUIObject(obj, z);
}

UIObject* AddHoverObject(int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover)
{   
	return AddHoverObject(NULL, NULL, NULL, cameraMultiplier, x, y, z, width, height, onHover);
}
	
UIObject* AddHoverObject(Picture* idlePicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover)
{                                 
	return AddHoverObject(idlePicture, idlePicture, idlePicture, cameraMultiplier, x, y, z, width, height, onHover);
}
	
UIObject* AddHoverObject(Picture* idlePicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover)
{                    
	return AddHoverObject(idlePicture, idlePicture, disabledPicture, cameraMultiplier, x, y, z, width, height, onHover);
}
	
UIObject* AddHoverObject(Picture* idlePicture, Picture* hoverPicture, Picture* disabledPicture, int cameraMultiplier, int x, int y, int z, int width, int height, Procedure onHover)
{
	UIObject* obj = (UIObject*)MemAlloc(sizeof(UIObject));   
	HoverObject* data = (HoverObject*)MemAlloc(sizeof(HoverObject)); 
	
	obj->PrevObject = NULL;
	obj->NextObject = NULL;
	obj->Type = UI_OBJECT_TYPE_HOVER;
	obj->Enabled = true;
	obj->CameraMultiplier = cameraMultiplier;
	obj->X = x;
	obj->Y = y;     
	obj->Z = z;
	obj->Data = data;
	
	data->Width = width;
	data->Height = height;
	data->OnHover = onHover;
	
	if (idlePicture || hoverPicture || disabledPicture)
	{
		GraphicObject* graphicButton = AddPictureObject(idlePicture, cameraMultiplier, x, y, z, width, height);
		data->GraphicButton = graphicButton;
		FlagPictureCacheUsage(hoverPicture);
		FlagPictureCacheUsage(disabledPicture);
		
		data->IdlePicture = idlePicture;
		data->HoverPicture = hoverPicture;
		data->DisabledPicture = disabledPicture;
	}            
	else
	{
		data->GraphicButton = NULL; 
		data->IdlePicture = NULL;
		data->HoverPicture = NULL;
		data->DisabledPicture = NULL;
	}
	
	return AddUIObject(obj, z);
}

void RemoveUIObject(UIObject* object)
{	
	if (object->Type == UI_OBJECT_TYPE_BUTTON)
	{    
		ButtonObject* button = (ButtonObject*)object->Data;
		
		RemoveGraphicObject(button->GraphicButton);
		UnflagPictureCacheUsage(button->HoverPicture);
		UnflagPictureCacheUsage(button->DisabledPicture);
	}
	else if (object->Type == UI_OBJECT_TYPE_HOVER)
	{    
		HoverObject* hover = (HoverObject*)object->Data;
		
		RemoveGraphicObject(hover->GraphicButton);
		UnflagPictureCacheUsage(hover->HoverPicture);     
		UnflagPictureCacheUsage(hover->DisabledPicture); 
	}
	
	if (object->PrevObject)
		object->PrevObject->NextObject = object->NextObject;
	else
		FirstUIObject = object->NextObject;

	if (object->NextObject)
		object->NextObject->PrevObject = object->PrevObject;
	
	MemFree(object->Data);
	MemFree(object);
}