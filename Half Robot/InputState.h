#pragma once
#include "Entity.h"

class InputState {
public:
	virtual ~InputState() {}
	virtual InputState* handleInput(Entity& entity) = 0;
	virtual void enter(Entity& entity) = 0;
	virtual std::string getType() = 0;

};