#pragma once
#include "MenuState.h"
#include "Button.h"
#include <iostream>
#include "Text.h"
#include "Settings.h"
#include "IOStuff.h"

class MainMenu : public MenuState {
public:
	MainMenu();
	~MainMenu();
	virtual MenuState* handleInput(Menu& menu, SDL_Event& ev);
	virtual void update(Menu& menu);
	void initLoc(Menu & menu);
	virtual void enter(Menu& menu);

private:
	Button startbtn, continubtn, helpbtn, exitbtn, audiobtn;
	Text startTxt, continueTxt, helpTxt, exitTxt;
	Button sponsorbtn;
	Settings settings;
	Text titleText;

	void stopClicks() {
		startbtn.clearClick(); continubtn.clearClick(); helpbtn.clearClick();
	}

	int curW; int curH;

};