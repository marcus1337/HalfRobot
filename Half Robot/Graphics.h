#pragma once
#include "SDL.h"
#include <string>
#include "ShapeHandler.h"
#include <chrono>

class Entity;

class Graphics {
public:
	Graphics();

	virtual void render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos);
	virtual void render2(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos, long ticks) {};

	virtual void deadAnimation(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos);



protected:

	void renderDir(SDL_Renderer* _rend, bool _rightDir, SDL_Texture* _someTxt, SDL_Rect* tmpSrc, SDL_Rect* tmpTrg);

	void fixRect(double lag, Entity& e,int xCam,int yCam);
	static int getExtraX(double lag, Entity& e);
	static int getExtraY(double lag, Entity& e);
	SDL_Texture* texture;
	SDL_Rect rect;
	bool wasDead;

	void dyingTimer(Entity& entity);

	size_t getDyingTime() {
		using namespace std::chrono;
		steady_clock::time_point nowTime = steady_clock::now();
		size_t diff = duration_cast<milliseconds>(nowTime - dieTimer).count();
		return diff;
	}
	long oldTicks;

private:

	std::chrono::steady_clock::time_point dieTimer;
	bool dieTimerStarted;

	struct SFrag {
		SDL_Rect tmpRct;
		int velX = 0;
		int velY = 0;

		void update() {
			tmpRct.x += velX;
			tmpRct.y += velY;
		}

		void setVelXY(int _velX, int _velY) {
			velX = _velX;
			velY = _velY;
		}
	};
	void fixRect2(SFrag& sfrag, int xCam, int yCam);
	SFrag sfrags[24];

};