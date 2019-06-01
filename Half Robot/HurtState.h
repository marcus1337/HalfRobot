#pragma once
#include "InputState.h"
#include <chrono>

class HurtState : public InputState {
public:

	virtual InputState* handleInput(Entity& entity);
	virtual void enter(Entity& entity);


	virtual std::string getType() {
		return "hurt";
	}


private:
	
};