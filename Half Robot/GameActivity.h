#pragma once
#include "Window.h"
#include "Menu.h"
#include "Model.h"
#include <iostream>
#include "World.h"
#include "Kartbit.h"
#include "StartMenu.h"
#include "Mouse.h"
#include "HP_Bar.h"
#include "LivesBar.h"
#include "Text.h"
#include "GameSave.h"
#include "IOStuff.h"
#include "WinMenu.h"
#include "SoundLocator.h"

class GameActivity {
	Text gameovertxt;
	LivesBar livesBar;

public:
	GameActivity(Menu& menu, Window& window) : _window(window) {
		renderer = window.getRenderer();
		gameovertxt.init("GAME OVER!!", renderer);
		gameovertxt.setRect({window.midX() - 300, window.getHeight() , 600, 300 });
		model.setRenderer(renderer);
		_gameOver = false;
		_exitGame = false;
		_modelinited = false;
		_shutdownGame = false;
		_safeCheck = false;
		instartmenu = false;

	}

	void init() {
		bool shouldRespawn = false;
		bool shouldGameOver = false;
		using namespace std;
		using namespace std::chrono;
		lag = 0.0;
		previous = chrono::steady_clock::now();
		MS_FRAME = 15000;
		oldY = (model.getPlayerEntity().getY() / 300) * 300;
		oldX = (model.getPlayerEntity().getX() / 400) * 400;
		alpha = 255;

		int w = world.getKartW();
		int h = world.getKartH();
		int midX = world.getKartMidX();
		dst = { midX, 0, w, h };
		//cout << "W2: " << w << "  H2: " << h << endl;
		src.x = 0;
		src.y = 0;
		src.w = 400;
		src.h = 300;

		playerHpBar = HP_Bar();
		bossHpBar = HP_Bar();
		int tmpH = _window.getHeight() / 3.5;
		int tmpW = tmpH / 5.5f;
		playerHpBar.setRect({ 10,10, tmpW, tmpH });
		int bossX = _window.getWidth() - tmpW - 10;
		bossHpBar.setRect({ bossX, 10, tmpW, tmpH });

		livesBar = LivesBar();
		livesBar.setRect({ 0,_window.getHeight() - 30, 100, 30 });
		//cout << "TEST: " << _window.getHeight() << " , " << livesBar.getRect().y << endl;

	}

	void processInput() {
		using namespace std;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {
				_shutdownGame = true;
				instartmenu = false;
			}
			if (ev.type == SDL_KEYDOWN) {
		
				if (ev.key.keysym.sym == SDLK_ESCAPE) {
					newGame();
				}
			}

			if (ev.type == SDL_WINDOWEVENT) {
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
					if (!_safeCheck)
						return;

					world.initDimensions(_window);
					world.clearWorld();
					world.init(_window, model.getWorldID());
					model.setWorld(&world.getWorld());
					init();
					gameovertxt.setRect({ _window.midX() - 300, _window.getHeight() , 600, 300 });
					
				}

			}

		}
	}

	bool isExit() {
		return _exitGame;
	}

	bool isShutDown() {
		return _shutdownGame;
	}

	void newGame() {
		if (instartmenu)
			return;

		instartmenu = true;
		mouse.setRect(SDL_Rect{ 50,50,20,25 });
		using namespace std;
		int response;

		if (gamesave.allLvlClear()) {
			response = -100;
			WinMenu winmenu(gamesave);
			winmenu.enter(_window);
			while (response == -100) {
				
				processInput();
				mouse.setXY(ev.motion.x, ev.motion.y);
				response = winmenu.handleInput(_window, ev);

				if (_window.isFocus()) {
					_window.clear();
					winmenu.update(_window);
					mouse.render(renderer);
					SDL_RenderPresent(renderer);

				}
				this_thread::sleep_for(chrono::milliseconds(3));
			}

			if (response == -3) {
				instartmenu = false;
				_shutdownGame = true;
				return;
			}

			if (response == -99) {
				_exitGame = true;
				instartmenu = false;
				return;
			}

		}

		response = worldsMenu();
		instartmenu = false;

		if (response == -3)
			_shutdownGame = true;
		if (response == -2)
			_exitGame = true;
		if (response <= 0)
			return;

		world.clearWorld();
		world.init(_window, response);
		model.setWorld(&world.getWorld());
		model.initWorld(response);
		model.setLives(gamesave.getLives());
		_modelinited = true;
		init();
		_safeCheck = true;
		SoundLocator::getAudio().playSound(93753);
		SoundLocator::getAudio().playSound(response);

	}

	void loadGame() {
		IOStuff iostuff;
		gamesave = iostuff.load();

	}

	void saveGame() {

	}

	int worldsMenu() {

		using namespace std;
		if(_modelinited)
			gamesave.setLives(model.getLives());
		StartMenu startmenu(gamesave);
		startmenu.enter(_window);
		int response = -1;

		while (response == -1) {
			
			processInput();
			mouse.setXY(ev.motion.x, ev.motion.y);
			response = startmenu.handleInput(_window, ev);
		
			if (_window.isFocus()) {
				_window.clear();
				startmenu.update(_window);
				mouse.render(renderer);
				SDL_RenderPresent(renderer);
		
			}
			this_thread::sleep_for(chrono::milliseconds(3));

		}
		return response;
	}

	bool playerDeath() {
		using namespace std;
		using namespace std::chrono;
		if (model.getPlayerEntity().isDead()) {
			if (model.gameLost() && !shouldGameOver) {
				shouldGameOver = true;
				gameovertxt.setY(_window.getHeight());
				endTimer = steady_clock::now();
			}
			else if (!shouldRespawn && !shouldGameOver) {
				shouldRespawn = true;
				endTimer = steady_clock::now();
			}
		}

		if (shouldRespawn) {
			steady_clock::time_point nowTime = steady_clock::now();
			size_t diff = duration_cast<milliseconds>(nowTime - endTimer).count();
			if (diff > 2400) {
				
				Entity& playertmp = model.getPlayerEntity();
				shouldRespawn = false;
				model.respawn();
				int xPostmp = playertmp.getX() + (int)((lag / MS_FRAME) * playertmp.getVelocityX());
				int yPostmp = playertmp.getY() + (int)((lag / MS_FRAME) * playertmp.getVelocityY());
				oldX = (xPostmp / 400) * 400;
				oldY = (yPostmp /= 300 * 300);
			}

		}

		if (shouldGameOver) {
			alpha--;
			if (alpha <= 0)
				alpha = 255;
			gameovertxt.setColor(255, 255, 255, alpha);
			_window.midY();
			if (gameovertxt.getY() > _window.midY() - gameovertxt.getHeight() / 2) {
				gameovertxt.setY(gameovertxt.getY() - 1);
			}

			gameovertxt.init("Game Over", renderer);

			steady_clock::time_point nowTime = steady_clock::now();
			size_t diff = duration_cast<milliseconds>(nowTime - endTimer).count();
			if (diff > 4000) {
				return true;
			}
		}
		return false;
	}

	bool gameTick() {
		using namespace std::chrono;
		bool anUpdate = false;
		current = steady_clock::now();
		int diff = duration_cast<microseconds>(current - previous).count();
		previous = current;
		lag += diff;
		anUpdate = false;
		while (lag >= MS_FRAME) {
			lag -= MS_FRAME;
			model.update();
			anUpdate = true;
		}
		return anUpdate;
	}

	void renderUsual(int offX, int offY) {
		WorldMap& worldmap = model.getPlayerMap();
		_window.clear();
		int w = worldmap.getWidth();
		int h = worldmap.getHeight();

		SDL_RenderCopy(renderer, worldmap.getTexture(), &src, &dst);
		//std::cout << "TEST: " << src.x << "  " << src.y << "   dst: " << dst.x << "  " << dst.y << " w,h: " << " WWW: " << dst.w <<  "  " << w << " " << h << std::endl;
		SDL_Rect tmp = src;
		SDL_Rect tmp2 = dst;
		tmp.x += 400;
		tmp2.x += dst.w;

		if (tmp.x + 400 > worldmap.getWidth() * 20) {
			int overl = (worldmap.getWidth() * 20) - (tmp.x + 400);
			tmp.w += overl;
			int overl2 = ((float)abs(overl) / 400)*tmp2.w;
			tmp2.w -= overl2;
			//std::cout << "TEST: " << tmp2.w << std::endl;
			//tmp.w = worldmap.getWidth() * 20 - 400;
		}
		SDL_RenderCopy(renderer, worldmap.getTexture(), &tmp, &tmp2);
		////////////////////
		tmp = src;
		tmp2 = dst;
		tmp.x -= 400;
		tmp2.x -= dst.w;

		if (tmp.x < 0) {
			int overl = (tmp.x + 400);
			tmp.x = 0;
			tmp.w = overl;
			tmp2.w = 0;
			tmp2.x = dst.x;
			int overl2 = ((float)overl / 400)*dst.w;
		//	std::cout << "TEST: " << overl2 << std::endl;
			tmp2.w = overl2;
			tmp2.x -= overl2;
			//std::cout << "TEST: " << tmp.x  << "  " << tmp.w << std::endl;
			//tmp.w = worldmap.getWidth() * 20 - 400;
		}
	
		SDL_RenderCopy(renderer, worldmap.getTexture(), &tmp, &tmp2);
		using namespace std;

	//	cout << "W: " << dst.w << " H: " << dst.h << endl;
		model.render(lag / MS_FRAME, offX, offY);
		playerHpBar.render(renderer, model.getPlayerEntity());
		livesBar.render(renderer, model.getLives());
	}

	void configSrc(int xPos, int yPos) {
		Entity& player = model.getPlayerEntity();
		WorldMap& worldmap = model.getPlayerMap();
		if (xPos >= 200 - player.getWidth() / 2) {
			src.x = xPos - 200 + player.getWidth() / 2;
		}
		src.y = yPos * 300;
		if (xPos + 200 >= worldmap.getWidth() * 20 - player.getWidth() / 2) {
			src.x = worldmap.getWidth() * 20 - 400;
		}
		if (src.x < 0)
			src.x = 0;
		if (src.y < 0)
			src.y = 0;
	}

	void swapXAnimation(int xPos) {
		using namespace std;
		using namespace std::chrono;
		src.x = (xPos / 400) * 400;
		int tmpx = src.x;
		while (oldX != tmpx) {

			if (tmpx > oldX)
				oldX++;
			else
				oldX--;

			src.x = oldX;

			renderUsual(oldX, src.y);
			SDL_RenderPresent(renderer);
			this_thread::sleep_for(chrono::milliseconds(2));
			previous = current = chrono::steady_clock::now();
		}
	}

	void swapYAnimation(int yPos) {
		using namespace std;
		using namespace std::chrono;
		while (oldY != yPos * 300) {

			if (yPos * 300 > oldY)
				oldY++;
			else
				oldY--;
			src.y = oldY;

			renderUsual(src.x, oldY);
			SDL_RenderPresent(renderer);
			this_thread::sleep_for(chrono::milliseconds(4));
			previous = current = chrono::steady_clock::now();
		}
	}

	void renderBoss() {

		bossHpBar.render(renderer, *model.getBoss());
	}

	void levelWon() {
		int worldID = model.getWorldID();
		gamesave.setLevelCleared(worldID);
		newGame();

	}

	bool isGameOver() {
		return _gameOver;
	}

	void gameLoop(int _startopt) {
		_safeCheck = false;
		using namespace std;
		using namespace std::chrono;


		SoundLocator::getAudio().playSound(93752);

		if (_startopt == 2)
			loadGame();

		newGame();

		if (_exitGame || _shutdownGame)
			return;

		while (true) {
			
			if (playerDeath()){
				_gameOver = true;
				return;
			}

			if (model.getBoss()->isDead()) {
				levelWon();
			
			}

			if (_exitGame || _shutdownGame)
				return;

			processInput();

			if (_exitGame || _shutdownGame)
				return;

			bool anUpdate = gameTick();

			if (_window.isFocus() && anUpdate) {
				Entity& player = model.getPlayerEntity();
				WorldMap& worldmap = model.getPlayerMap();

				int xPos = player.getX() + (int)((lag / MS_FRAME) * player.getVelocityX());
				int yPos = player.getY() + (int)((lag / MS_FRAME) * player.getVelocityY());
				yPos /= 300;

				configSrc(xPos, yPos);

				bool lockX = model.lockX();

				if (lockX && oldX != ((xPos / 400) * 400)) {
					swapXAnimation(xPos);
				}

				if(lockX)
					src.x = (xPos / 400) * 400;


				if (yPos * 300 != oldY) {
					swapYAnimation(yPos);
				}

				renderUsual(src.x, src.y);

				if(shouldGameOver)
					gameovertxt.render(renderer);

				if (model.inBossArea()) {
					renderBoss();

					if (model.getBoss()->isDead()) {

					}

				}

				SDL_RenderPresent(renderer);
				
			}
			this_thread::sleep_for(chrono::milliseconds(1));
			

		}

	}

private:
	Window& _window;
	SDL_Renderer* renderer;
	SDL_Event ev;
	Model model;
	World world;

	bool shouldRespawn;
	bool shouldGameOver;

	int oldY;
	int oldX;
	int alpha;
	std::chrono::steady_clock::time_point endTimer;
	int MS_FRAME;
	float lag;
	std::chrono::steady_clock::time_point previous;
	std::chrono::steady_clock::time_point current;

	SDL_Rect dst, src;

	HP_Bar playerHpBar;
	HP_Bar bossHpBar;

	bool _gameOver;
	bool _exitGame;
	bool _shutdownGame;
	bool _modelinited;
	GameSave gamesave;
	Mouse mouse;

	bool _safeCheck;
	bool instartmenu;
};