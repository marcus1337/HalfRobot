#pragma once
#include "MenuState.h"
#include "Button.h"
#include <iostream>
#include "Text.h"

class HelpMenu : public MenuState {
public:
	virtual MenuState* handleInput(Menu& menu, SDL_Event& ev);
	virtual void update(Menu& menu);
	virtual void enter(Menu& menu);

private:

	Text  helpTxt;
	Button backbtn;
	Text backTxt;
};