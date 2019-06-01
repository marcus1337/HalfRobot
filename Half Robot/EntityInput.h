#pragma once
#include "Entity.h"
#include "SDL.h"
#include <string>

class EntityInput {
public:

	//EntityInput() = 0;
	virtual void handleInput(Entity& entity) {};
	virtual void handleInput(Entity& entity, Model& model) {};
	virtual std::string getType() = 0;

private:

};