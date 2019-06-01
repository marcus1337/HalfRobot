#pragma once
#include "InputState.h"

class JumpState : public InputState {
public:

	virtual InputState* handleInput(Entity& entity);
	virtual void enter(Entity& entity);
	void setNoJump(bool noJump) {
		_noJump = noJump;
	}

	virtual std::string getType() {
		return "jump";
	}

	JumpState() : latestPress(0), upPressed(false) {
	
	}

private:
	bool continPress = false;
	int countSteps = 0;
	bool _noJump = false;
	int latestPress;
	bool upPressed;
};