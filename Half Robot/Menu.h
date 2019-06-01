#pragma once

#include "Mouse.h"
#include "Window.h"
#include <functional>
#include <chrono>
#include <thread>
#include "ShapeHandler.h"
#include "MainMenu.h"
#include "MenuState.h"
#include "SoundPlayer.h"

class Menu {

public:

	Menu();
	~Menu();

	void menuLoop();

	Window& getWindow();

	SDL_Event& getEvent();

	Mouse& getMouse();

	void processInput();
	void startGame(int startOption) {
		_startOption = startOption;
		gameRunning = true;
	}
	void goBackToMenu() {
		backToMain = true;
	}

	void quitGame() {
		_quit = true;
	}

private:
	SDL_Event ev;
	Window window;
	Mouse mouse;
	MenuState* state;
	int _startOption;
	bool gameRunning;
	bool backToMain = false;
	SoundPlayer soundPlayer;
	bool _quit;

};