#pragma once
#include "BulletEntity.h"
#include "Model.h"
#include "SoundLocator.h"


using namespace std;

BulletEntity::BulletEntity(Physics* physics, Graphics* graphics, EntityInput* input) 
	: Entity(physics, graphics, input) {

	Entity::setWidthHeight(15,12);
	SoundLocator::getAudio().playSound(BULL1);
};

void BulletEntity::update(Model& model) {

	if (isDead())
		return;

	Entity& e = model.getPlayerEntity();
	if (!e.isDamaged() && e.getID() != getID()) {
		if (checkCollision(e)) {
			e.setDamaged(true);
			e.setHP(e.getHP() - 40);
			setDead(true);
		}
	}

	vector<Entity*>& ais = model.getAis();
	for (auto& bot : ais) {
		if (bot->getID() == getID() || bot->startedDying())
			continue;
		if (checkCollision(*bot)) {
			bot->setDamaged(true);
			bot->setHP(bot->getHP() - 40);
			setDead(true);
		}
	}

	Entity* boss = model.getBoss();
	if (boss->getID() != getID() && !boss->startedDying()) {
		if (checkCollision(*boss)) {
			boss->setDamaged(true);
			boss->setHP(boss->getHP() - 40);
			setDead(true);
		}
	}

	_input->handleInput(*this, model);
	_physics->update(model, *this);

	if (ttl < 0)
		setDead(true);

	ttl--;
	//(std::cout << "TEST: " << ttl << std::endl;
}