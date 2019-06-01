#pragma once
#include "EntityInput.h"

class BulletInput : public EntityInput {
public:
	BulletInput() {
	
	};

	virtual void handleInput(Entity& entity, Model& model);

	virtual std::string getType() {
		return "normalBullet";
	};

};