#pragma once   

#include "Video.h"   

#define KB_DATA_PORT	0x60
#define KB_COMMAND_PORT	0x64

//This is the QWERTY layout (if you use AZERTY... then switch to a good layout /j)
#define KB_KEY_1		0x02
#define KB_KEY_2		0x03
#define KB_KEY_3		0x04
#define KB_KEY_4		0x05
#define KB_KEY_5		0x06
#define KB_KEY_6		0x07
#define KB_KEY_7		0x08
#define KB_KEY_8		0x09
#define KB_KEY_9		0x0A
#define KB_KEY_0		0x0B
#define KB_KEY_BKSP		0x0E
#define KB_KEY_Q		0x10
#define KB_KEY_W		0x11
#define KB_KEY_E		0x12
#define KB_KEY_R		0x13
#define KB_KEY_T		0x14
#define KB_KEY_Y		0x15
#define KB_KEY_U		0x16
#define KB_KEY_I		0x17
#define KB_KEY_O		0x18
#define KB_KEY_P		0x19
#define KB_KEY_ENTER	0x1C
#define KB_KEY_CTRL		0x1D
#define KB_KEY_A		0x1E
#define KB_KEY_S		0x1F
#define KB_KEY_D		0x20
#define KB_KEY_F		0x21
#define KB_KEY_G		0x22
#define KB_KEY_H		0x23
#define KB_KEY_J		0x24
#define KB_KEY_K		0x25
#define KB_KEY_L		0x26
#define KB_KEY_SHIFT	0x2A
#define KB_KEY_Z		0x2C
#define KB_KEY_X		0x2D
#define KB_KEY_C		0x2E
#define KB_KEY_V		0x2F
#define KB_KEY_B		0x30
#define KB_KEY_N		0x31
#define KB_KEY_M		0x32
#define KB_KEY_ALT		0x38
#define KB_KEY_SPACE	0x39
#define KB_ARROW_UP		0x48
#define KB_ARROW_LEFT	0x4B
#define KB_ARROW_RIGHT	0x4D
#define KB_ARROW_DOWN	0x50

#define MOUSE_LEFT_BTN		0x7D
#define MOUSE_RIGHT_BTN		0x7E
#define MOUSE_MIDDLE_BTN	0x7F

extern uint8_t KBStatus[];     
extern int KBTotalChanges[];     

extern Vector2 MouseCursor;
extern GraphicObject* CursorObject;

extern void KB_ClearBuffer();
extern void KB_Initialize();

extern void SetCursorPicture(Picture* picture);
extern void ResetCursor();