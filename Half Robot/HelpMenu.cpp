#pragma once
#include "HelpMenu.h"
#include "MainMenu.h"
#include "Menu.h"
#include "SoundLocator.h"

using namespace std;
MenuState* HelpMenu::handleInput(Menu& menu, SDL_Event& ev) {

	switch (ev.type) {
	case SDL_MOUSEBUTTONDOWN:
		backbtn.clickPress(ev.motion.x, ev.motion.y);
		break;
	case SDL_MOUSEBUTTONUP:
		backbtn.clickRelease(ev.motion.x, ev.motion.y);
		break;
	case SDL_MOUSEMOTION:
		backbtn.hover(ev.motion.x, ev.motion.y);
		break;
	}

	if (backbtn.isClicked()) {
		return new MainMenu();
	}


	return nullptr;
};
void HelpMenu::update(Menu& menu) {
	SDL_Renderer* r = menu.getWindow().getRenderer();
	SDL_RenderCopy(r, ShapeHandler::background2, NULL, NULL);
	backbtn.render(r);
	backTxt.render(r);
	helpTxt.render(r);

};

void HelpMenu::enter(Menu& menu) {
	int w = menu.getWindow().getWidth();
	int h = menu.getWindow().getHeight();

	SoundLocator::getAudio().playSound(93752);


	SDL_Renderer* r = menu.getWindow().getRenderer();

	int hdown = h - (float)h / 5;
	int wnorm = (float)w / 10;

	SDL_Rect btnrct = { menu.getWindow().midX() - wnorm, hdown, wnorm * 2, wnorm };

	backbtn.setRect(btnrct);
	backTxt.setRect(btnrct);
	backTxt.init("BACK", r, 88);

	helpTxt.setX(10);
	helpTxt.setY(10);
	std::string _tmpmsg = "The goal is to beat all the 8 levels.\n"
		"Save current process by clicking the 'SAVE-button' in the start menu.\n"
		"MOVE/LADDER: Arrow keys\n"
		"SHOOT: Z\n"
		"JUMP: X.\n"
		"EXIT: Esc\n\n"
		"WEBSITE: Fullrune.com"
		;
	helpTxt.setColor(90,150,170);
	helpTxt.init2(r,45, _tmpmsg, w-10);

};