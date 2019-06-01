#pragma once
#include "InputState.h"

class StillState : public InputState {
public:

	virtual InputState* handleInput(Entity& entity);
	virtual void enter(Entity& entity);
	virtual std::string getType() {
		return "still";
	}

private:
	bool oldJumpPress = false;
};