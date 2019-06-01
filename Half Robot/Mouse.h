#pragma once
#include "SDL.h"
#include "ShapeHandler.h"

class Mouse {
public:
	Mouse(){
	}

	void render(SDL_Renderer* renderer) {
		SDL_Texture* texture = ShapeHandler::mouseText;
		SDL_RenderCopyEx(renderer, texture, nullptr, &rect, 0, nullptr, SDL_FLIP_NONE);
	}

	void setRect(SDL_Rect _rect) {
		rect = _rect;
	}

	void setXY(int x, int y) {
		rect.x = x;
		rect.y = y;
	}


private:
	SDL_Rect rect;
};