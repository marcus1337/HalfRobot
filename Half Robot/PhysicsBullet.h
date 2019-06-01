#pragma once
#include "Physics.h"
#include "Model.h"

class PhysicsBullet : public Physics {
public:
	virtual void update(Model& model, Entity& entity);

private:

};