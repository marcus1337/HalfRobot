#pragma once
#include "Button.h"
#include <iostream>
#include "Window.h"
#include "MenuState.h"
#include "Menu.h"
#include "GameSave.h"
#include "IOStuff.h"
#include "Toast.h"
#include "LivesBar.h"

class StartMenu {
public:

	StartMenu(GameSave _gamesave) : gamesave(_gamesave), clicked(false) {

	}

	virtual int handleInput(Window& window, SDL_Event& ev) {
		using namespace std;

		if (ev.type == SDL_QUIT) {
			return -3;
		}

		switch (ev.type) {

		case SDL_MOUSEBUTTONDOWN:
			clicked = true;
			for(int i = 0; i < 9; i++)
				if(worldBtn[i].isActive())
					worldBtn[i].clickPress(ev.motion.x, ev.motion.y);

			backbtn.clickPress(ev.motion.x, ev.motion.y);
			savebtn.clickPress(ev.motion.x, ev.motion.y);
			break;
		case SDL_MOUSEBUTTONUP:
			if (!clicked)
				break;
			clicked = false;

			for (int i = 0; i < 9; i++)
				worldBtn[i].clickRelease(ev.motion.x, ev.motion.y);

			savebtn.clickRelease(ev.motion.x, ev.motion.y);
			backbtn.clickRelease(ev.motion.x, ev.motion.y);
			break;

		case SDL_MOUSEMOTION:
			for (int i = 0; i < 9; i++)
				worldBtn[i].hover(ev.motion.x, ev.motion.y);

			break;

		case SDL_WINDOWEVENT:
			if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
				initLoc(window);
			}
			break;

		}


		for (int i = 0; i < 9; i++) {
			if (worldBtn[i].isClicked() && worldBtn[i].isActive()) {
				return i+1;
			}
		}

		if (backbtn.isClicked()) {
			return -2;
		}

		if (savebtn.isClicked()) {
			IOStuff iostuff;
			iostuff.save(gamesave);
			toast.setActive(true);
		}
	
		return -1;
	}

	virtual void update(Window& window) {
		SDL_Renderer* r = window.getRenderer();
		SDL_RenderCopy(r, ShapeHandler::background3, NULL, NULL);
		for (int i = 0; i < 9; i++) {
			if (worldBtn[i].isActive()) {
				worldBtn[i].render(r);
				worldTxt[i].render(r);
			}
		}
		backbtn.render(r);
		savebtn.render(r);
		saveTxt.render(r);

		toast.render(r);
		livesBar.render(r, gamesave.getLives());

	}

	void initLoc(Window& window) {
		int w = window.getWidth();
		int h = window.getHeight();
		int bwi = (float)w / 10;
		int bhe = (float)h / 8;

		int xtmp = (int)(w*0.1f);

		int x = window.midX() - bwi / 2;
		int xl = x - bwi - 100;
		int xr = x + bwi + 100;

		int y = window.midY() - bhe / 2;
		int yp = y - bhe - 100;
		int yd = y + bhe + 100;


		worldBtn[0].setRect({ xl,yp,bwi,bhe });
		worldBtn[1].setRect({ x,yp,bwi,bhe });
		worldBtn[2].setRect({ xr,yp,bwi,bhe });

		worldBtn[3].setRect({ xl,y,bwi,bhe });
		worldBtn[4].setRect({ xr,y,bwi,bhe });

		worldBtn[5].setRect({ xl,yd,bwi,bhe });
		worldBtn[6].setRect({ x,yd,bwi,bhe });
		worldBtn[7].setRect({ xr,yd,bwi,bhe });

		for (int i = 0; i <= 7; i++)
			fixText(i, window.getRenderer());

		for (int i = 0; i <= 7; i++) {
			if (gamesave.isLvlClear(i + 1)) {
				worldBtn[i].setActive(false);
			}
		}

		backbtn.setRect({ 0,0,bwi,bhe });
		backbtn.setImage(ShapeHandler::backbtn, ShapeHandler::backbtn2);

		savebtn.setRect({ w - bwi * 2,h - bhe,bwi * 2,bhe });
		saveTxt = Text();
		toast = Toast();
		livesBar = LivesBar();
		saveTxt.setRect({ w - bwi * 2,h - bhe,bwi * 2,bhe });
		saveTxt.setColor(255, 64, 65);
		saveTxt.init("SAVE", window.getRenderer(), 75);


		int tmplen = window.getWidth() / 5 + 4;
		int tmpheight = tmplen / 4;
		int _xtmp = window.midX() - tmplen / 2;
		int _ytmp = window.getHeight() - window.getHeight() / 5;

		SDL_Rect toastRect = { _xtmp, _ytmp, tmplen, tmpheight };

		toast.init("GAME SAVED", 500, toastRect, window.getRenderer());

		livesBar.setRect({ 0, h - 30, 100, 30 });
	}

	virtual void enter(Window& window) {
		initLoc(window);
	}

private:

	void fixText(int i, SDL_Renderer* rend) {
		worldTxt[i].setColor(255, 64, 65);
		worldTxt[i].init(std::to_string(i+1), rend, 200);
		SDL_Rect r = worldBtn[i].getRect();
		r.x += 20;
		r.w -= 40;
		r.y += 5;
		r.h -= 5;
		worldTxt[i].setRect(r);
	}

	Button worldBtn[9];
	Text worldTxt[9];

	Button backbtn;
	Button savebtn;
	Text saveTxt;

	GameSave gamesave;
	Toast toast;

	LivesBar livesBar;

	bool clicked;
};