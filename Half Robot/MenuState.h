#pragma once
#include "SDL.h"
#include <string>
class Menu;

class MenuState {
public:
	virtual ~MenuState() {}
	virtual MenuState* handleInput(Menu& menu, SDL_Event& ev) = 0;
	virtual void update(Menu& menu) = 0;
	virtual void enter(Menu& menu) = 0;
};