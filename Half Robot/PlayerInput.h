#pragma once
#include "Entity.h"
#include "InputState.h"
#include "SDL.h"
#include "EntityInput.h"

class PlayerInput : public EntityInput {
public:

	PlayerInput();

	virtual void handleInput(Entity& entity);

	virtual std::string getType() {
		if(state)
			return state->getType();
		return "";
	}

private:
	InputState* state;
	bool hurtOnce;
	void handleKeys(Entity& entity);

};