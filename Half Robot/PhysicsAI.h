#pragma once
#pragma once
#include "Physics.h"
#include "Model.h"

class PhysicsAI : public Physics {
public:
	virtual void update(Model& model, Entity& entity);

private:

};