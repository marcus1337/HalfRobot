#include "GraphicsAI.h"


using namespace std;
void GraphicsAI::render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos) {
	using namespace std;
	int dir = !entity.getDirection();
	dyingTimer(entity);
	if (entity.startedDying()) {
		size_t _time = getDyingTime();
		
		SDL_SetTextureAlphaMod(aiText, deadAlpha);
		if (_time - _time2 > 20) {
			deadAlpha-= 10;
			_time2 = _time;
		}

		if (deadAlpha < 0)
			deadAlpha = 0;

		renderDir(renderer, dir, aiText, NULL, &rect);
	}
	else {
		fixRect(lag, entity, xPos, yPos);
		renderDir(renderer, dir, aiText, NULL, &rect);
	}

}