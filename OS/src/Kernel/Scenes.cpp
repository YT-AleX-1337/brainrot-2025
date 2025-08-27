#include "Kernel.h"

Scene* NewScene()
{	
	Scene* scene = (Scene*)MemAlloc(sizeof(Scene));
	
	scene->FirstGraphicUnit = NULL;
	scene->FirstUIUnit = NULL;
	
	return scene;
}

Scene* ResetScene(Scene* scene)
{	
	DestroyUnitChain(scene->FirstGraphicUnit);
	DestroyUnitChain(scene->FirstUIUnit); 
	
	scene->FirstGraphicUnit = NULL;
	scene->FirstUIUnit = NULL;
	
	return scene;
}

void DeleteScene(Scene* scene)
{	
	DestroyUnitChain(scene->FirstGraphicUnit);
	DestroyUnitChain(scene->FirstUIUnit);       
	
	MemFree(scene);
}

GraphicObject* LinkToScene(GraphicObject* object, Scene* scene)
{
	GraphicUnit* unit = (GraphicUnit*)MemAlloc(sizeof(GraphicUnit));
	
	unit->Object = object;
	unit->NextUnit = NULL;
	
	if (!scene->FirstGraphicUnit)
	{
		unit->PrevUnit = NULL;
		scene->FirstGraphicUnit = unit;
	}
	else
	{
		GraphicUnit* lastUnit = scene->FirstGraphicUnit;
		
		while (lastUnit->NextUnit)
			lastUnit = lastUnit->NextUnit;
		
		unit->PrevUnit = lastUnit;
		lastUnit->NextUnit = unit;
	}
	
	return object;
}

UIObject* LinkToScene(UIObject* object, Scene* scene)
{
	UIUnit* unit = (UIUnit*)MemAlloc(sizeof(UIUnit));
	
	unit->Object = object;
	unit->NextUnit = NULL;
	
	if (!scene->FirstUIUnit)
	{
		unit->PrevUnit = NULL;
		scene->FirstUIUnit = unit;
	}
	else
	{
		UIUnit* lastUnit = scene->FirstUIUnit;
		
		while (lastUnit->NextUnit)
			lastUnit = lastUnit->NextUnit;
		
		unit->PrevUnit = lastUnit;
		lastUnit->NextUnit = unit;
	}
	
	return object;
}

void DestroyUnitChain(GraphicUnit* unit)
{
    while (unit)
	{
        GraphicUnit* next = unit->NextUnit;
        RemoveGraphicObject(unit->Object);
        MemFree(unit);
        unit = next;
    }             
}

void DestroyUnitChain(UIUnit* unit)
{	
    while (unit)
	{		
        UIUnit* next = unit->NextUnit;   
        RemoveUIObject(unit->Object);        
        MemFree(unit);
        unit = next;
    }
}