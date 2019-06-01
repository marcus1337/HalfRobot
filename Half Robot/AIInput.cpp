#include "AIInput.h"

using namespace std;
void AIInput::handleInput(Entity& entity, Model& model) {


	int xv;
	int yv;
	luabot.handleInput(entity, model, xv, yv);

	
	entity.setVelocityXY(xv, yv);

	//someFunc(nullptr);

	if (entity.getVelocityX() > 0)
		entity.setDirection(1);
	else if (entity.getVelocityX() < 0) 
		entity.setDirection(0);


	/*const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_0]) {
		luabot.reload();
	}*/

}
