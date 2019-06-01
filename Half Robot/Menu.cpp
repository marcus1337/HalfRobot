#include "Menu.h"
#include <iostream>
#include "GameActivity.h"
#include "SoundLocator.h"


Menu::Menu() : window("MegaGame", 1000, 599) {
	_quit = false;
	SDL_Init(SDL_INIT_AUDIO);
	SoundLocator::initialize();
	SoundLocator::provide(&soundPlayer);
	ShapeHandler shapehandler(window.getRenderer());
	shapehandler.init();
	gameRunning = false;
	mouse.setRect(SDL_Rect{ 50,50,15,25 });
	state = new MainMenu();
	state->enter(*this);
}

Menu::~Menu() {
	ShapeHandler::deleteVariables();
	delete state;

}



void Menu::menuLoop() {
	using namespace std;
	//SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 200, 255);

	while (!gameRunning) {

		processInput();

		if (_quit)
			return;

		if (window.isFocus()) {
			window.clear();
			state->update(*this);
			mouse.render(window.getRenderer());
			SDL_RenderPresent(window.getRenderer());
		
		}
		
		this_thread::sleep_for(chrono::milliseconds(3));
	}


	if (gameRunning) {
		GameActivity gameActivity(*this, ref(window));

		gameActivity.gameLoop(_startOption);

		if (gameActivity.isShutDown())
			return;

		if (gameActivity.isExit() || gameActivity.isGameOver()) {
			gameRunning = false;
			state->enter(*this);
			menuLoop();
		}
	
	}

}

Window& Menu::getWindow() {
	return std::ref(window);
}

SDL_Event& Menu::getEvent() {
	return std::ref(ev);
}

Mouse& Menu::getMouse() {
	return std::ref(mouse);
}

void Menu::processInput() {
	while (SDL_PollEvent(&ev)) {
		MenuState* tmpState = state->handleInput(*this, std::ref(ev));
		if (tmpState) {
			delete state;
			state = tmpState;
			state->enter(*this);
		}
		if (ev.type == SDL_QUIT) {
			_quit = true;
		}

	}
	mouse.setXY(ev.motion.x, ev.motion.y);
}