#include "BulletInput.h"

void BulletInput::handleInput(Entity& entity, Model& model) {
	if (entity.getDirection())
		entity.setVelocityXY(4, 0);
	else
		entity.setVelocityXY(-4, 0);
}