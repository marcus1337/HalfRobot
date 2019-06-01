#pragma once
#include "MenuState.h"
#include "GameActivity.h"

class GameMenu : public MenuState {
public:
	GameMenu();

	virtual MenuState* handleInput(Menu& menu, SDL_Event& ev);
	virtual void update(Menu& menu);
	virtual void enter(Menu& menu);

private:
	GameActivity gameActivity;
};