#pragma once
#include "Graphics.h"
#include "ShapeHandler.h"
#include "EntityInput.h"
#include "Entity.h"
#include "World.h"
#include <iostream> 

class GraphicsPlayer : public Graphics {
public:
	GraphicsPlayer();
	virtual void render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos);
	virtual void render2(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos, long ticks);

private:
	std::string prevTyp = "";
	int aniIndex = 0;
	int extraCount = 0;
	int prevY = 0;
	bool ladderAniChange = false;
	bool ladderPrev = false;
	bool firePrev = false;
	int hurtcount;

};