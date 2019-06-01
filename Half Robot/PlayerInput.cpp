#include "PlayerInput.h"
#include "StillState.h"
#include "PhysicsPlayer.h"
#include "HurtState.h"

using namespace std;

PlayerInput::PlayerInput() {
	state = new StillState();
	hurtOnce = false;
}

bool prevFire = false;

void PlayerInput::handleInput(Entity& entity) {
	InputState* s = state->handleInput(entity);
	if (s) {
		delete state;
		state = s;
		state->enter(entity);
	}
	if (entity.getVelocityX() > 0) {
		entity.setDirection(1);
	}
	else if (entity.getVelocityX() < 0) entity.setDirection(0);

	if (state->getType() == "hurt") {
		return;
	}

	if (entity.isDamaged() && state->getType() != "hurt" && !hurtOnce) {
		hurtOnce = true;
		delete state;
		state = new HurtState();
		state->enter(entity);
	}
	else if (hurtOnce) {
		int diff = entity.getDamagedTime();
		if (diff >= 1900)
		{
			hurtOnce = false;
			entity.setDamaged(false);
		}
	}

	handleKeys(entity);


}

void PlayerInput::handleKeys(Entity& entity){
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_X] && !prevFire) {
		entity.setFiring(true);
		entity.setWantFire(true);
		prevFire = true;
	}
	else if (!keys[SDL_SCANCODE_X] && prevFire) {
		prevFire = false;
	}


}