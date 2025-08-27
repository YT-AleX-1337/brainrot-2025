#include "Kernel.h"    

uint8_t KBStatus[128];
int KBTotalChanges[128];

Vector2 MouseCursor = { 0, 0 };
GraphicObject* CursorObject = NULL;

void KB_ClearBuffer()
{
	while (InB(KB_COMMAND_PORT) & 1)
        InB(KB_DATA_PORT);
}

void KB_Handle(Registers* regs)
{                   
	uint8_t scanCode = InB(KB_DATA_PORT);
	uint8_t pressed = scanCode & 0x80 ? 0 : 1;
	scanCode &= 0x7F;
	
	KBTotalChanges[scanCode] += 1;
	KBStatus[scanCode] = pressed;
}

void Mouse_Update()
{
	CursorObject->X = MouseCursor.X;
	CursorObject->Y = MouseCursor.Y;       
}

uint8_t mouseCycle = 0;
uint8_t mousePacket[3];

void Mouse_ProcessPacket()
{
    int8_t deltaX = mousePacket[1];
    int8_t deltaY = -mousePacket[2];  
	
	MouseCursor.X += deltaX;
	MouseCursor.Y += deltaY;
	
	if (MouseCursor.X < 0)
		MouseCursor.X = 0;
	else if (MouseCursor.X >= SCREEN_WIDTH)
		MouseCursor.X = SCREEN_WIDTH - 1;
	
	if (MouseCursor.Y < 0)
		MouseCursor.Y = 0;
	else if (MouseCursor.Y >= SCREEN_HEIGHT)
		MouseCursor.Y = SCREEN_HEIGHT - 1;

    KBTotalChanges[MOUSE_LEFT_BTN] += ((mousePacket[0] & 0x01 ? 1 : 0) == KBStatus[MOUSE_LEFT_BTN]) ? 0 : 1;
    KBTotalChanges[MOUSE_RIGHT_BTN] += ((mousePacket[0] & 0x02 ? 1 : 0) == KBStatus[MOUSE_RIGHT_BTN]) ? 0 : 1;
    KBTotalChanges[MOUSE_MIDDLE_BTN] += ((mousePacket[0] & 0x04 ? 1 : 0) == KBStatus[MOUSE_MIDDLE_BTN]) ? 0 : 1;

    KBStatus[MOUSE_LEFT_BTN] = mousePacket[0] & 0x01 ? 1 : 0;
    KBStatus[MOUSE_RIGHT_BTN] = mousePacket[0] & 0x02 ? 1 : 0;
    KBStatus[MOUSE_MIDDLE_BTN] = mousePacket[0] & 0x04 ? 1 : 0;
}

void Mouse_Handle(Registers* regs)
{
	uint8_t mouseData = InB(KB_DATA_PORT);
	
	//The mouse sends a 3-bytes packet one byte at a time
	if (mouseCycle == 0)
    {
        if (mouseData & 0x08)
        {
            mousePacket[0] = mouseData;
            mouseCycle++;
        }
    }
    else if (mouseCycle == 1)
    {
        mousePacket[1] = mouseData;
        mouseCycle++;
    }
    else if (mouseCycle == 2)
    {
        mousePacket[2] = mouseData;
        mouseCycle = 0;

        Mouse_ProcessPacket();
    }
}

void KB_Initialize()
{                            
	MemSet(KBStatus, 0, sizeof(uint8_t) * 128);
	MemSet(KBTotalChanges, 0, sizeof(int) * 128);
	
	KB_ClearBuffer();   
	
	CursorObject = AddPictureObject(&Cursor, 0, MouseCursor.X, MouseCursor.Y, 1000);
	
	OutB(KB_COMMAND_PORT, 0xA7);	//Disable auxiliar PS/2 device
    OutB(KB_COMMAND_PORT, 0xA8);	//Enable mouse   
	
	OutB(KB_COMMAND_PORT, 0x20);	//Get status byte
    uint8_t status = InB(KB_DATA_PORT);
    status |= 0x02;					//Enable mouse interrupts
    OutB(KB_COMMAND_PORT, 0x60);	//Set status byte
    OutB(KB_DATA_PORT, status);   
	
	IRQ_RegisterHandler(1, KB_Handle);
	IRQ_RegisterHandler(12, Mouse_Handle);

    OutB(KB_COMMAND_PORT, 0xD4);
    OutB(KB_DATA_PORT, 0xF4);		//Enable mouse data streaming
	
	AddTask(Mouse_Update);
	ResetCursor();
}

void SetCursorPicture(Picture* picture)
{
	PictureObject* obj = (PictureObject*)CursorObject->Data;
	obj->Data = picture;
}

void ResetCursor()
{
	MouseCursor = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
}