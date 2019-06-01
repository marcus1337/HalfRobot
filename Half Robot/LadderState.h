#pragma once
#include "InputState.h"

class LadderState : public InputState {
public:

	virtual InputState* handleInput(Entity& entity);
	virtual void enter(Entity& entity);
	virtual std::string getType() {
		return "ladder";
	}

private:
	int fireCounter = 0;
};