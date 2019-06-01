#pragma once
#include "Entity.h"
#include "SDL.h"
#include "Model.h"
#include "EntityInput.h"
#include <chrono>

#include "LuaBot.h"

class AIInput : public EntityInput {
public:

	AIInput(int botId) : luabot(botId) {};

	virtual void handleInput(Entity& entity, Model& model);

	virtual std::string getType() {
		return "AI";
	};

private:
	LuaBot luabot;

};