#pragma once
#include "StillState.h"
#include "WalkState.h"
#include "JumpState.h"
#include "LadderState.h"
#include <iostream>
#include "SoundLocator.h"

InputState* JumpState::handleInput(Entity& entity) {
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	using namespace std;
	countSteps++;


	Physics* physics = entity.getPhysics();
	if (physics->isInAir()) {

	}
	else {
		if (entity.getVelocityX() != 0)
			return new WalkState();
		else
			return new StillState();
	}

	if (!state[SDL_SCANCODE_UP]) {
		upPressed = false;
	}

	if (!upPressed && state[SDL_SCANCODE_UP] && physics->canUseLadderUP()){
		return new LadderState();
	}

	if (!state[SDL_SCANCODE_Z] || countSteps > 15) {
		continPress = false;
	}

	if (continPress) {
		entity.setVelocityXY(entity.getVelocityX(), -4);
	}
	else {
		entity.setVelocityXY(entity.getVelocityX(), 4);
	}
	if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT]) {
		if (latestPress == 1) {
			entity.setVelocityXY(-3, entity.getVelocityY());
		}
		else if (latestPress == 2) {
			entity.setVelocityXY(3, entity.getVelocityY());
		}
		else {
			entity.setVelocityXY(0, entity.getVelocityY());
		}
	}
	else if (state[SDL_SCANCODE_RIGHT]) {
		if (latestPress == 0)
			latestPress = 1;
		entity.setVelocityXY(3, entity.getVelocityY());
	}
	else if (state[SDL_SCANCODE_LEFT]) {
		if (latestPress == 0)
			latestPress = 2;
		entity.setVelocityXY(-3, entity.getVelocityY());
	}
	else {
		latestPress = 0;
		entity.setVelocityXY(0, entity.getVelocityY());
	}

	if (state[SDL_SCANCODE_5]) {

		SoundLocator::getAudio().playSound(3);
	}

	return nullptr;
}

void JumpState::enter(Entity& entity) {

	continPress = true;
	countSteps = 0;
	entity.setVelY(-5);
	if (_noJump) {
		continPress = false;
		entity.setVelY(1);
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP]) {
		upPressed = true;
	}

	if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT]) {
		latestPress = 0;
	}
	else if (state[SDL_SCANCODE_RIGHT]) {
		latestPress = 1;
	}
	else if (state[SDL_SCANCODE_LEFT]) {
		latestPress = 2;
	}

}