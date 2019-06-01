#pragma once
#include "StillState.h"
#include "WalkState.h"
#include "JumpState.h"

void WalkState::enter(Entity& ent) {
	ent.setVelY(0);
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_Z])
		oldJumpPress = true;

	if (state[SDL_SCANCODE_RIGHT]) {
		latestPress = 5;
	}
	else
		latestPress = 1;

}
using namespace std;
InputState* WalkState::handleInput(Entity& entity) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	Physics* physics = entity.getPhysics();

	if ((state[SDL_SCANCODE_Z] && !oldJumpPress) || physics->isInAir())
		return new JumpState();

	if (!state[SDL_SCANCODE_Z])
		oldJumpPress = false;

	if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT]) {
		if (latestPress == 1)
			entity.setDirection(1);
		else
			entity.setDirection(0);
		return new StillState();
	}

	if (state[SDL_SCANCODE_RIGHT]) {
		entity.setVelocityXY(3, 0);
		//entity.setDirection(1);
	}
	else if (state[SDL_SCANCODE_LEFT]) {
		entity.setVelocityXY(-3, 0);
		//entity.setDirection(0);
	}
	else {
		return new StillState();
	}

	return nullptr;
}