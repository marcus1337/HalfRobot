#include "GraphicsPlayer.h"

using namespace std;
GraphicsPlayer::GraphicsPlayer() {
	rect = { 0, 0, 50, 50 };
	hurtcount = 0;
}

void GraphicsPlayer::render2(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos, long ticks) {
	texture = ShapeHandler::heroStill;

	if (entity.isFiring() && !firePrev) {
		extraCount = 0;
	}

	fixRect(lag, entity, xPos, yPos);

	if (entity.isFiring()) {
		texture = ShapeHandler::heroFireStill;
	}

	if (entity.isDead()) {
		deadAnimation(lag, entity, renderer, xPos, yPos);
		wasDead = true;
		return;
	}
	else
		wasDead = false;

	string sTyp = entity.getInput()->getType();

	if (prevTyp != sTyp) {
		aniIndex = 0;
		extraCount = 0;
	}

	if (ticks != oldTicks) {
		extraCount++;
		hurtcount++;
	}

	if (sTyp == "jump") {
		texture = ShapeHandler::heroJump;
		if (entity.isFiring())
			texture = ShapeHandler::heroFireJump;

		int extra = (int)(rect.h * 1.33333f - rect.h);
		rect.w += extra;
		rect.h += extra;
		extra /= 2;
		rect.x += extra*(-1);



	}
	if (sTyp == "walk") {

		if (oldTicks != ticks) {
			if (extraCount >= 8 && aniIndex == 0) {
				extraCount = 0;
				aniIndex++;
			}
			else if (extraCount >= 12) {
				extraCount = 0;
				aniIndex++;
			}

			if (aniIndex == 3)
				aniIndex = 1;
		}

		texture = ShapeHandler::heroWalk[aniIndex];
		if (entity.isFiring()) {
			texture = ShapeHandler::heroFireWalk[aniIndex];
		}

	}
	if (sTyp == "ladder") {

		if (prevY != entity.getY() && !ladderAniChange) {
			ladderAniChange = true;
			prevY = entity.getY();
			extraCount = 0;

			//	ladderPrev = !ladderPrev;
		}
		int extraX = (int)(rect.w * 0.6666f - rect.w);
		rect.w += extraX;
		int extraY = (int)(rect.h * 1.33333f - rect.h);
		rect.h += extraY;
		extraX /= 2;
		rect.x += extraX*(-1);

		texture = ShapeHandler::heroLadder;
		if (entity.isFiring()) {
			texture = ShapeHandler::heroFireLadder;
		}


	}

	prevTyp = sTyp;

	if (sTyp == "hurt") {

		texture = ShapeHandler::heroHurt;
		if (hurtcount > 4 && hurtcount < 7)
			return;
		else if (hurtcount >= 7)
			hurtcount = 0;
	}
	else if (entity.isDamaged()) {
		if (hurtcount > 4 && hurtcount < 7)
			return;
		else if (hurtcount >= 7)
			hurtcount = 0;
	}

	bool isLeft = entity.getDirection();
	if (sTyp == "ladder") {

		if (!entity.isFiring()) {
			if (ladderPrev) {

				SDL_RenderCopy(renderer, texture, NULL, &rect);
			}
			else {
				SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
			}

			if (ladderAniChange) {
				if (extraCount > 10) {
					extraCount = 0;
					ladderAniChange = false;
					ladderPrev = !ladderPrev;
				}
			}
		}
		else {
			rect.w += 15;
			if (entity.getDirection()) {
				rect.x += 7;
				SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
			}
			else {
				rect.x -= 17;
				SDL_RenderCopy(renderer, texture, NULL, &rect);
			}


		}

	}
	else
		if (isLeft) {
			SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
		}
		else {
			SDL_RenderCopy(renderer, texture, NULL, &rect);
		}

		SDL_SetRenderDrawColor(renderer, 0, 40, 0, 255);

		firePrev = entity.isFiring();

	oldTicks = ticks;
}

void GraphicsPlayer::render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos) {

}
