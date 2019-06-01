#pragma once
#include "Entity.h"
#include <vector>

class PlayerEntity : public Entity {

public:
	PlayerEntity(Physics* physics, Graphics* graphics, EntityInput* input) : 
		Entity(physics, graphics, input) {
		_lives = 1;
	}


	void checkCollisions(std::vector<Entity*>& ais) {
	
		for (auto& bot : ais) {
			if (!isDamaged() && !bot->startedDying() && !bot->isDead() && checkCollision(*bot)) {
				setHP(getHP() - 30);
				setDamaged(true);
			}
		}

	}

	void checkACollision(Entity& entity) {
		if (entity.isDead() || entity.startedDying())
			return;

		if (!isDamaged() && checkCollision(entity)) {
			setHP(getHP() - 20);
			setDamaged(true);
		}
	}

	int getLives() {
		return _lives;
	}

	void setLives(int lives) {
		_lives = lives;
	}

private:
	int _lives;

};