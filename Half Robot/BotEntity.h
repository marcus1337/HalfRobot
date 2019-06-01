#pragma once
#include "Entity.h"
#include "EntityInput.h"
#include <iostream>

class BotEntity : public Entity {
public:

	BotEntity(Physics* physics, Graphics* graphics, EntityInput* input, int _someid = 777)
		: Entity(physics, graphics, input) {
		setID(_someid);
	};

	virtual void update(Model& model) {
		if (isDead() || startedDying())
			return;

		_input->handleInput(*this, model);
		_physics->update(model, *this);
	}


private:


};