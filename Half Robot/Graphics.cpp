#include "Graphics.h"
#include "ShapeHandler.h"
#include "EntityInput.h"
#include "Entity.h"
#include "World.h"
#include <iostream> 

Graphics::Graphics() {
	wasDead = false;
	dieTimerStarted = false;
	dieTimer = std::chrono::steady_clock::now();
	oldTicks = 0;
}


void Graphics::render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos) {
	using namespace std;


}

int Graphics::getExtraX(double lag, Entity& e) {
	return (int)lag * e.getVelocityX();
}

int Graphics::getExtraY(double lag, Entity& e) {
	return (int)lag * e.getVelocityY();
}

void Graphics::deadAnimation(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos) {
	SDL_Texture* frag = ShapeHandler::bull1[0];

	if (!wasDead) {
		int v = 2;
		for (int i = 0; i < 24; i++) {
			int x = entity.getX() + entity.getWidth() / 2;
			int y = entity.getY() + entity.getHeight() / 2;
			int w = entity.getWidth();
			int h = entity.getHeight();
			sfrags[i].tmpRct = { x,y,15,15 };
			fixRect2(sfrags[i], xPos, yPos);
		}
		sfrags[0].setVelXY(-v, 0);
		sfrags[1].setVelXY(-v, -v);
		sfrags[2].setVelXY(0, -v);
		sfrags[3].setVelXY(v, -v);
		sfrags[4].setVelXY(v, 0);
		sfrags[5].setVelXY(v, v);
		sfrags[6].setVelXY(0, v);
		sfrags[7].setVelXY(-v, v);

		for (int i = 8; i < 16; i++)
			sfrags[i] = sfrags[i - 8];
		for (int i = 16; i < 24; i++)
			sfrags[i] = sfrags[i - 16];

	}
	bool group2 = false;
	bool group3 = false;
	if (abs(sfrags[0].tmpRct.x - sfrags[4].tmpRct.x) > 100) {
		group2 = true;
	}
	if (abs(sfrags[8].tmpRct.x - sfrags[12].tmpRct.x) > 100) {
		group3 = true;
	}

	for (int i = 0; i < 8; i++) {
		sfrags[i].update();
		SDL_RenderCopy(renderer, frag, NULL, &sfrags[i].tmpRct);
	}
	if (group2) {
		for (int i = 8; i < 16; i++) {
			sfrags[i].update();
			SDL_RenderCopy(renderer, frag, NULL, &sfrags[i].tmpRct);
		}
	}
	if (group3) {
		for (int i = 16; i < 24; i++) {
			sfrags[i].update();
			SDL_RenderCopy(renderer, frag, NULL, &sfrags[i].tmpRct);
		}
	}


}

using namespace std;

void Graphics::fixRect(double lag, Entity& entity, int xPos, int yPos) {
	rect.x = entity.getX() + getExtraX(lag, entity);
	rect.y = entity.getY() + getExtraY(lag, entity);
	
	int h = entity.getHeight();
	int w = entity.getWidth();
	float mH = (float)h / 300;
	float mW = (float)w / 400;
	rect.x -= xPos;
	rect.y -= yPos;

	rect.x = World::getKartMidX() + rect.x*((float)World::getKartW() / 400);
	rect.y = rect.y*((float)World::getKartH() / 300);
	rect.w = (int)(mW*World::getKartW());
	rect.h = (int)(mH*World::getKartH());
}

void Graphics::fixRect2(SFrag& sfrag, int xPos, int yPos) {
	SDL_Rect& tmprct = std::ref(sfrag.tmpRct);
	int h = tmprct.h;
	int w = tmprct.w;
	float mH = (float)h / 300;
	float mW = (float)w / 400;
	tmprct.x -= xPos;
	tmprct.y -= yPos;
	tmprct.x = World::getKartMidX() + tmprct.x*((float)World::getKartW() / 400);
	tmprct.y = tmprct.y*((float)World::getKartH() / 300);
	tmprct.w = (int)(mW*World::getKartW());
	tmprct.h = (int)(mH*World::getKartH());
}

void Graphics::dyingTimer(Entity& entity){
	using namespace std::chrono;

	if (!entity.startedDying() && dieTimerStarted) {
		dieTimerStarted = false;
		dieTimer = steady_clock::now();
		return;
	}
	else if (!entity.startedDying()) {
		return;
	}
	if (!dieTimerStarted) {
		dieTimer = steady_clock::now();
		dieTimerStarted = true;
	}
	else
	{
		steady_clock::time_point nowTime = steady_clock::now();
		size_t diff = duration_cast<milliseconds>(nowTime - dieTimer).count();
		if (diff > 1000) {
			entity.setDead(true);
		}
	}

}


void Graphics::renderDir(SDL_Renderer* _rend, bool _rightDir, SDL_Texture* _someTxt, SDL_Rect* tmpSrc, SDL_Rect* tmpTrg)
{
	if (_rightDir) {
		SDL_RenderCopyEx(_rend, _someTxt, tmpSrc, tmpTrg, 0, 0, SDL_FLIP_HORIZONTAL);
	}
	else {
		SDL_RenderCopy(_rend, _someTxt, tmpSrc, tmpTrg);
	}

}