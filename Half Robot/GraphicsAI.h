#pragma once
#include "Graphics.h"
#include "ShapeFuncs.h"
#include "EntityInput.h"
#include "ShapeHandler.h"
#include "Entity.h"
#include "World.h"
#include <iostream> 

class GraphicsAI : public Graphics {
public:
	GraphicsAI(SDL_Renderer* renderer) : Graphics() {
	
		rect = { 0,0,50,50 };
		aiText = ShapeFuncs::textureFromPath(renderer, ShapeHandler::rpath + "unit\\enemy\\bot1.png");
		deadAlpha = 255;
		_time2 = 0;
	};

	~GraphicsAI() {
		SDL_DestroyTexture(aiText);
	}

	virtual void render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos);

private:
	int aniIndex = 0;
	int counter = 0;
	bool flipAni = false;
	SDL_Texture* aiText;
	int deadAlpha;
	size_t _time2;
};