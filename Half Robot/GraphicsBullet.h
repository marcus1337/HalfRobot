#pragma once
#include "Graphics.h"
#include "ShapeHandler.h"
#include "EntityInput.h"
#include "Entity.h"
#include "World.h"
#include <iostream> 

class GraphicsBullet : public Graphics {
public:
	GraphicsBullet() : Graphics(){
		rect = { 0,0,50,50 };
	};

	virtual void render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos);

private:
	int aniIndex = 0;
	int counter = 0;
	bool flipAni = false;

};