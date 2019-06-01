#pragma once
#include "Text.h"
#include <string>
#include "ShapeHandler.h"

class Toast {

public:
	Toast() {
		_activated = false;
	}

	void init(std::string msg, int ticks, SDL_Rect rect, SDL_Renderer* renderer) {
		_msg = msg;
		_ticks = ticks; 
		_rect = rect;
		_startTicks = ticks;
		_text.setRect(rect);
		_text.setColor(247, 214, 78);

		backplate = ShapeFuncs::textureFromPath(renderer, ShapeHandler::rpath + "bakgrund1.png");

	}

	void render(SDL_Renderer* renderer) {
		if (isDone())
			_activated = false;

		if (!_activated)
			return;

		_text.init(_msg, renderer, 70);
		if(_ticks > 0)
			_ticks--;

		float perc = ((float)_ticks / _startTicks);

		if (perc < 0.4)
		{
			int a = _text.getAlpha();
			if (a > 0)
				a--;
			if (a < 0)
				a = 0;

			_text.setAlpha(a);
			SDL_SetTextureAlphaMod(backplate, a);
		}


		SDL_Rect rect2 = _rect;
		rect2.x -= 20;
		rect2.y -= 20;
		rect2.w += 40;
		rect2.h += 40;


		SDL_RenderCopy(renderer, backplate, NULL, &rect2);
		_text.render(renderer);
	}

	bool isDone() {
		return _ticks == 0;
	}

	void setActive(bool activated) {
		_activated = activated;
		if (_activated) {
			_ticks = _startTicks;
			_text.setAlpha(255);
			SDL_SetTextureAlphaMod(backplate, 255);
		}

	}

private:
	Text _text;
	std::string _msg;
	int _ticks;
	int _startTicks;
	SDL_Rect _rect;
	bool _activated;

	SDL_Texture* backplate;

};