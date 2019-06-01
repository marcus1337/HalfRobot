#pragma once
#include "MainMenu.h"
#include "Menu.h"
#include "IOStuff.h"
#include <iostream>
#include "SoundLocator.h"
#include "SoundPlayer.h"
#include "NullAudio.h"
#include "HelpMenu.h"


using namespace std;

MainMenu::MainMenu() {
	IOStuff iostuff;
	iostuff.loadSettings(ref(settings));
	curW = curH = -1;
//	cout << "TEST: "<< settings.isSoundOn() << endl;
}

MainMenu::~MainMenu() {
	IOStuff iostuff;
	settings.setWH(curW, curH);
	iostuff.saveSettings(ref(settings));
//	cout << "TEST2: " << settings.isSoundOn() << endl;
}

MenuState* MainMenu::handleInput(Menu& menu, SDL_Event& ev) {
	curW = menu.getWindow().getWidth();
	curH = menu.getWindow().getHeight();

	switch (ev.type) {
	case SDL_MOUSEBUTTONDOWN:
		startbtn.clickPress(ev.motion.x, ev.motion.y);
		continubtn.clickPress(ev.motion.x, ev.motion.y);
		helpbtn.clickPress(ev.motion.x, ev.motion.y);
		exitbtn.clickPress(ev.motion.x, ev.motion.y);
		audiobtn.clickPress(ev.motion.x, ev.motion.y);
		sponsorbtn.clickPress(ev.motion.x, ev.motion.y);
		break;
	case SDL_MOUSEBUTTONUP:
		startbtn.clickRelease(ev.motion.x, ev.motion.y);
		continubtn.clickRelease(ev.motion.x, ev.motion.y);
		helpbtn.clickRelease(ev.motion.x, ev.motion.y);
		exitbtn.clickRelease(ev.motion.x, ev.motion.y);
		audiobtn.clickRelease(ev.motion.x, ev.motion.y);
		sponsorbtn.clickRelease(ev.motion.x, ev.motion.y);
		break;
	case SDL_MOUSEMOTION:
		startbtn.hover(ev.motion.x, ev.motion.y);
		continubtn.hover(ev.motion.x, ev.motion.y);
		helpbtn.hover(ev.motion.x, ev.motion.y);
		exitbtn.hover(ev.motion.x, ev.motion.y);
		sponsorbtn.hover(ev.motion.x, ev.motion.y);
		break;

	case SDL_WINDOWEVENT:
		if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
			initLoc(menu);
		}
		break;
	}

	if (startbtn.isClicked()) {
		stopClicks();
		menu.startGame(0);
	}

	if (exitbtn.isClicked()) {
		menu.quitGame();
	}

	if (audiobtn.isClicked()) {
		audiobtn.setPressed(!audiobtn.isPressed());
		settings.setSoundOn(!audiobtn.isPressed());
		SoundLocator::setActive(!audiobtn.isPressed());
		if (!audiobtn.isPressed()) {
	
			SoundLocator::getAudio().resumeAllSounds();
		}

	}

	if (helpbtn.isClicked()) {
		return new HelpMenu();
	}

	if (sponsorbtn.isClicked()) {
		std::string myurl = "https://play.google.com/store/apps/details?id=com.fullrune.areashifter&hl=sv";
		system(std::string("start " + myurl).c_str());
	}

	if (continubtn.isActive() && continubtn.isClicked()) {
		stopClicks();
		menu.startGame(2);
	}

	return nullptr;
};
void MainMenu::update(Menu& menu) {
	SDL_Renderer* renderer = menu.getWindow().getRenderer();

	SDL_RenderCopy(renderer, ShapeHandler::background2, NULL, NULL);

	if (continubtn.isActive()) {
		continubtn.render(renderer);
		continueTxt.render(renderer);
	}
	startbtn.render(renderer);
	helpbtn.render(renderer);
	exitbtn.render(renderer);

	startTxt.render(renderer);
	helpTxt.render(renderer);
	exitTxt.render(renderer);
	audiobtn.render(renderer);
	sponsorbtn.render(renderer);
	titleText.render(renderer);

};

void MainMenu::initLoc(Menu& menu) {
	SDL_Renderer* renderer = menu.getWindow().getRenderer();
	int w = menu.getWindow().getWidth();
	int h = menu.getWindow().getHeight();
	int btnwidth = w*0.22;
	int xs = menu.getWindow().midX() - btnwidth / 2;
	int btnheight = btnwidth / 3.5;
	int h1 = h*0.33;
	IOStuff iostuff;
	bool filexist = iostuff.fileExist();

	titleText.setColor(255, 161, 161);
	titleText.setFontName("CENTURY");
	titleText.init("Half Robot", renderer, 85);
	SDL_Rect rct22 = { 0,0,0,0 };
	rct22.w = w*0.38f;
	rct22.h = rct22.w*0.3f;
	rct22.x = w / 2 - rct22.w / 2;
	rct22.y = h*0.03f;
	titleText.setRect(rct22);

	h1 = (rct22.y + rct22.h) + h*0.03f;

	SDL_Rect r = { xs,h1,btnwidth,btnheight };
	continubtn.setRect(r);
	continueTxt.setColor(255, 64, 65);
	continueTxt.init("CONTINUE", renderer, 200);
	continueTxt.setRect(r);

	if (filexist) {
		h1 += btnheight + btnheight * 0.4f;
		continubtn.setActive(true);
	}
	else {
		continubtn.setActive(false);
	}
	startbtn.setRect({ xs,h1,btnwidth,btnheight });
	h1 += btnheight + btnheight * 0.4f;
	helpbtn.setRect({ xs,h1,btnwidth,btnheight });
	h1 += btnheight + btnheight * 0.4f;
	exitbtn.setRect({ xs,h1,btnwidth,btnheight });

	audiobtn.setImage(ShapeHandler::audioOn, ShapeHandler::audioOff);

	int audiL = (int)(w*0.06);
	audiobtn.setRect({ 10,10,audiL,audiL });


	startTxt.setColor(255, 64, 65);
	startTxt.init("START", renderer, 200);
	r = startbtn.getRect();
	r.x += 20;
	r.w -= 40;
	r.y += 5;
	r.h -= 5;
	startTxt.setRect(r);

	helpTxt.setColor(255, 64, 65);
	helpTxt.init("HELP ", renderer, 200);
	r = helpbtn.getRect();
	r.x += 20;
	r.w -= 40;
	r.y += 5;
	r.h -= 5;
	helpTxt.setRect(r);

	exitTxt.setColor(255, 64, 65);
	exitTxt.init("EXIT ", renderer, 200);
	r = exitbtn.getRect();
	r.x += 20;
	r.w -= 40;
	r.y += 5;
	r.h -= 5;
	exitTxt.setRect(r);
	//SoundLocator::getAudio().playSound(1);
	audiobtn.setPressed(!SoundLocator::isActive());

	SDL_Rect srct;
	srct.w = w / 10;
	srct.h = srct.w;
	srct.x = w - srct.w - 10;
	srct.y = 10;
	sponsorbtn.setRect(srct);
	sponsorbtn.setImage(ShapeHandler::sponsorimg, ShapeHandler::sponsorimg);


}

void MainMenu::enter(Menu& menu) {
	initLoc(menu);
	SoundLocator::getAudio().playSound(MENU1);
	if (settings.isSoundOn()) {
		SoundLocator::getAudio().resumeAllSounds();
	}
	else {
		SoundLocator::getAudio().stopAllSounds();
		audiobtn.setPressed(true);
	}
};