#pragma once
#include "SDL.h"
#include "ShapeHandler.h"
#include "Entity.h"

class HP_Bar {

public:

	HP_Bar() {

	}

	void render(SDL_Renderer* renderer, Entity& entity) {
		SDL_Texture* texture1 = ShapeHandler::health_bar;
		SDL_Texture* texture2 = ShapeHandler::health_bar_b;

		SDL_Rect tmpR2 = rect;


		float percOff = (1 - ((float)entity.getHP() / entity.getMaxHP()));

		int tw, th;
		SDL_QueryTexture(texture1, NULL, NULL, &tw, &th);
		SDL_Rect tmpr3 = {0,0,tw,th};
		th = percOff*th;
		tmpr3.y += th;
		tmpr3.h -= th;

		int offsetY = (1 - ((float)entity.getHP() / entity.getMaxHP()))*rect.h;
		tmpR2.y += offsetY;
		tmpR2.h -= offsetY;

		SDL_RenderCopy(renderer, texture2, nullptr, &rect);
		SDL_RenderCopy(renderer, texture1, &tmpr3, &tmpR2);

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