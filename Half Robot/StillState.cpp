#pragma once
#include "StillState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "LadderState.h"
using namespace std;
InputState* StillState::handleInput(Entity& entity) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	Physics* physics = entity.getPhysics();

	if ((state[SDL_SCANCODE_Z] && !oldJumpPress) || physics->isInAir())
		return new JumpState();

	if (!state[SDL_SCANCODE_Z])
		oldJumpPress = false;

	if (!state[SDL_SCANCODE_Z] && state[SDL_SCANCODE_UP] && physics->canUseLadderUP()) {
		return new LadderState();
	}

	if (!state[SDL_SCANCODE_Z] && state[SDL_SCANCODE_DOWN] && physics->canUseLadderDOWN()) {
		return new LadderState();
	}

	if ((state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT])
		|| (!state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT])) {
		return new WalkState();
	}
	return nullptr;
}

void StillState::enter(Entity& entity) {
	entity.setVelocityXY(0, 0);
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_Z])
		oldJumpPress = true;

}