#pragma once
#include "Entity.h"
#include "EntityInput.h"
#include <iostream>

class BulletEntity : public Entity {
public:
	BulletEntity(Physics* physics, Graphics* graphics, EntityInput* input);

	virtual void update(Model& model);




private:
	int ttl = 1500;

};