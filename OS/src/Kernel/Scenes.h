#pragma once

#include "UI.h"
#include "Video.h"

typedef struct GraphicUnit GraphicUnit;
struct GraphicUnit
{
	GraphicUnit* PrevUnit;	
	GraphicUnit* NextUnit;	
	GraphicObject* Object;	
} __attribute__((packed));

typedef struct UIUnit UIUnit;
struct UIUnit
{
	UIUnit* PrevUnit;	
	UIUnit* NextUnit;	
	UIObject* Object;	
} __attribute__((packed)); 

typedef struct
{
	GraphicUnit* FirstGraphicUnit;
	UIUnit* FirstUIUnit;
} __attribute__((packed)) Scene;

extern Scene* NewScene();
extern Scene* ResetScene(Scene* scene);
extern void DeleteScene(Scene* scene);

extern GraphicObject* LinkToScene(GraphicObject* object, Scene* scene);
extern UIObject* LinkToScene(UIObject* object, Scene* scene);

extern void DestroyUnitChain(GraphicUnit* firstUnit);
extern void DestroyUnitChain(UIUnit* firstUnit);