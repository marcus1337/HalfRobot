#include "GraphicsBullet.h"


void GraphicsBullet::render(float lag, Entity& entity, SDL_Renderer* renderer, int xPos, int yPos) {
	using namespace std;


	texture = ShapeHandler::bull1[0];

	counter++;
	if (counter % 2 == 0 && !flipAni) {
	//	cout << "TEST: " << aniIndex << endl;
		if (aniIndex + 1 == 9)
			flipAni = true;
		else
			aniIndex = (aniIndex + 1);
		counter = 0;
	}
	else if (counter % 2 == 0 && flipAni) {
		counter = 0;
		if (aniIndex - 1 == -1) {
			flipAni = false;
			
		}
		else
			aniIndex = (aniIndex - 1);

	}



	fixRect(lag, entity, xPos, yPos);


	SDL_RenderCopy(renderer, texture, NULL, &rect);

}