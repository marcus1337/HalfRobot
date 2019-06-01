#pragma once
#include "InputState.h"

class WalkState : public InputState {
public:
	virtual InputState* handleInput(Entity& entity);
	virtual void enter(Entity& entity);
	virtual std::string getType() {
		return "walk";
	}

	WalkState() : latestPress(0), oldJumpPress(false) {
	}

private:
	bool oldJumpPress;
	int latestPress;

};