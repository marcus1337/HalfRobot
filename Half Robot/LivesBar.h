#pragma once
#include "SDL.h"
#include "ShapeHandler.h"
#include "Entity.h"
#include "Text.h"

class LivesBar {
public:

	LivesBar() : _lives(-2) {

	}

	SDL_Rect getRect() {
		return rect;
	}

	void render(SDL_Renderer* renderer, int lives) {

		if (_lives != lives) {
			_lives = lives;
			lifeText.setColor(200, 150, 50);
			lifeText.init("Lives x " + std::to_string(_lives), renderer, 80);
			lifeText.setRect(rect);
			
		}
		SDL_SetRenderDrawColor(renderer, 20, 40, 5, 255);
		SDL_RenderFillRect(renderer, &rect);
		lifeText.render(renderer);

	}

	void setRect(SDL_Rect _rect) {
		rect = _rect;
	}

	void setXY(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

private:
	int _lives;
	Text lifeText;
	SDL_Rect rect;

};