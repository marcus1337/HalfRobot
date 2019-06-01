#include "GraphicsAI2.h"


using namespace std;
void GraphicsAI2::render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos) {
	using namespace std;


	dyingTimer(entity);
	if (entity.startedDying()) {
		size_t _time = getDyingTime();

		SDL_SetTextureAlphaMod(aiText, deadAlpha);
		if (_time - _time2 > 20) {
			deadAlpha -= 10;
			_time2 = _time;
		}

		if (deadAlpha < 0)
			deadAlpha = 0;

		renderDir(renderer, 0, aiText, NULL, &rect);
	}
	else {
		fixRect(lag, entity, xPos, yPos);
		renderDir(renderer, 0, aiText, NULL, &rect);
	}

}