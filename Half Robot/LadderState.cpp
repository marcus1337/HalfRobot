#pragma once
#include "LadderState.h"
#include "StillState.h"
#include "WalkState.h"
#include "JumpState.h"
#include <iostream>

InputState* LadderState::handleInput(Entity& entity) {
	using namespace std;
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	Physics* physics = entity.getPhysics();

	if (!physics->isOnLadder()) {
		physics->exitLadder();
		if (physics->isInAir()) {
			JumpState* j = new JumpState();
			j->setNoJump(true);
			return new JumpState();
		}
		else 
			return new StillState();

	}

	if (state[SDL_SCANCODE_LEFT]) {
		entity.setDirection(0);
	}
	else if (state[SDL_SCANCODE_RIGHT]) {
		entity.setDirection(1);
	}

	if (state[SDL_SCANCODE_UP]) {
		entity.setVelY(-3);
	}else
	if (state[SDL_SCANCODE_DOWN]) {
		entity.setVelY(3);
	}
	else {
		entity.setVelY(0);
	}
	if (entity.isFiring()) {
		entity.setVelY(0);
		fireCounter++;
	}
	else {
		fireCounter = 0;
	}
	if (fireCounter > 15)
		entity.setFiring(false);

	if (state[SDL_SCANCODE_Z]) {
		physics->exitLadder();
		JumpState* j = new JumpState();
		j->setNoJump(true);
		return j;
	}

	return nullptr;
}

void LadderState::enter(Entity& entity) {

	Physics* physics = entity.getPhysics();
	physics->enterLadder();
	entity.setVelocityXY(0, 0);

}

