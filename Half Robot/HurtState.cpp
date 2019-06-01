#include "HurtState.h"
#include "PhysicsPlayer.h"
#include "JumpState.h"
#include "StillState.h"

using namespace std;
using namespace chrono;

InputState* HurtState::handleInput(Entity& entity) {
	Physics* physics = entity.getPhysics();
	int diff = entity.getDamagedTime();

	if (!physics->isInAir()) {
		entity.setVelY(0);
	}

	if (diff > 750)
	{
		if (physics->isInAir()) {
			JumpState* j = new JumpState();
			j->setNoJump(true);
			return j;
		}
		return new StillState();
	}

	return nullptr;
}

void HurtState::enter(Entity& entity) {
	entity.setDamagedTime();

	entity.setVelocityXY(0, 0);
	if (entity.getDirection()) {
		entity.setVelX(-1);
	}
	else
		entity.setVelX(1);

	Physics* physics = entity.getPhysics();
	physics->exitLadder();
	if (physics->isInAir()) {
		entity.setVelY(2);
	}

}