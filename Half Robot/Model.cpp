#pragma once
#include "Model.h"
#include "Entity.h"
#include "Graphics.h"
#include "Physics.h"
#include "EntityInput.h"
#include "SDL.h"
#include "PlayerInput.h"
#include "GraphicsPlayer.h"
#include "PhysicsPlayer.h"
#include "GraphicsBullet.h"
#include "BulletInput.h"
#include "PhysicsBullet.h"
#include "AIInput.h"
#include "GraphicsAI.h"
#include "GraphicsAI2.h"
#include "BotEntity.h"
#include "PhysicsBot.h"

using namespace std;
Model::Model() : ticks(0) {
	boss = nullptr;
}

Model::~Model() {
	delete player;
}

BulletEntity* generateBullet() {
	return new BulletEntity(new PhysicsBullet, new GraphicsBullet(), new BulletInput());
}

void Model::initWorld(int w_id) {
	ticks = 0;
	world_id = w_id;
	xlock = true;
	player = new PlayerEntity(new PhysicsPlayer(), new GraphicsPlayer(), new PlayerInput());

	//player->setXY(950, 475);
	player->setID(999);
	spawnX = 20;
	spawnY = 200;
	clearWorld();
	spawnAis(world_id);
	player->setXY(spawnX, spawnY);
	player->setDirection(1);
}

long Model::getTicks() {
	return ticks;
}

void Model::clearWorld() {
	while (!ais.empty()) {
		delete ais.back();
		ais.pop_back();
	}
	if (boss) {
		delete boss;
		boss = nullptr;
	}
}

void Model::respawn() {

	clearWorld();
	player->setXY(spawnX, spawnY);
	player->setHP(player->getMaxHP());
	player->setLives(player->getLives() - 1);
	player->getPhysics()->exitLadder();
	player->setDead(false);
	player->setStartedDying(false);
	player->setDamaged(false);
	spawnAis(world_id);


}

void Model::spawnAis(int _world_id) {
	Entity* e;
	player->setMaxHP(100);
	if (_world_id == 1) {
		spawnX = 50;
		spawnY = 100;
		e = new BotEntity(new PhysicsPlayer(), new GraphicsAI2(renderer), new AIInput(1),50);
		e->setXY(450, 100);
		ais.push_back(e);
		e = new BotEntity(new PhysicsPlayer(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(450, 60);
		ais.push_back(e);

		e = new BotEntity(new PhysicsPlayer(), new GraphicsAI(renderer), new AIInput(0), 1);
		
		e->setXY(900, 400);
		boss = e;
		boss->setMaxHP(2250);
	}

	if (_world_id == 2) {
		spawnX = 20;
		spawnY = 200;

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(550, 100);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(550, 130);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(550, 115);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(550, 80);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(600, 80);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(750, 80);
		ais.push_back(e);


		//e = new BotEntity(new PhysicsPlayer(), new GraphicsAI2(renderer), new AIInput(2), 50);
		//e->setXY(700, 60);
		//ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(0), 1);

		e->setXY(1250, 400);
		boss = e;
		boss->setMaxHP(1350);
	}

	if (_world_id == 3) {

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(650, 100);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(550, 100);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(700, 100);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(450, 100);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(0), 1);
		e->setXY(900, 450);
		boss = e;

		boss->setMaxHP(3333);
	}

	if (_world_id == 4) {

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(80, 25);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(150, 25);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(200, 25);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(250, 25);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(290, 25);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(400, 350);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(420, 370);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(420, 322);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(5), 1);
		e->setXY(20, 750);
		boss = e;
		boss->setMaxHP(1650);

	}

	if (_world_id == 5) {

		for (int i = 0; i < 10; i++) {
			if (i == 5)
				i++;

			e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
			e->setXY(26+i*32, 20);
			ais.push_back(e);
		}

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(426, 20);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(450, 50);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(760, 70);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(760, 120);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(760, 180);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(760, 220);
		ais.push_back(e);

		player->setMaxHP(140);
		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(7), 1);
		e->setXY(850, 450);
		boss = e;
		boss->setMaxHP(1850);

	}

	if (_world_id == 6) {

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
		e->setXY(1150, 20);
		ais.push_back(e);

		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(6), 1);
		e->setXY(850, 450);
		boss = e;
		boss->setMaxHP(1850);

	}

	if (_world_id == 7) {

		e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(1), 50);
		e->setXY(30, 1100);
		ais.push_back(e);

		for (int i = 0; i < 5; i++) {
			e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
			e->setXY(100+i*62, 1000);
			ais.push_back(e);
		}

		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(6), 1);
		e->setXY(450, 1300);
		boss = e;
		boss->setMaxHP(1850);
	}

	if (_world_id == 8) {

		for (int i = 0; i < 7; i++) {
			e = new BotEntity(new PhysicsBot(), new GraphicsAI2(renderer), new AIInput(2), 50);
			e->setXY(430 + i * 50, 30);
			ais.push_back(e);
		}

		player->setMaxHP(250);
		e = new BotEntity(new PhysicsBot(), new GraphicsAI(renderer), new AIInput(6), 1);
		e->setXY(1250, 500);
		boss = e;
		boss->setMaxHP(2000);
	}

}


void Model::update() {
	ticks++;
	using namespace std;

	player->update(*this);
	player->checkCollisions(getAis());
	player->checkACollision(*getBoss());

	fireGun(*player);
	if (player->startedDying() && !player->isDead()) {
		player->setDead(true);
		player->setStartedDying(false);
		player->setLives(player->getLives() - 1);
	}

	if (player->isDead()) {

	}

	for (auto &bot : ais) {
		bot->update(*this);

		fireGun(*bot);
	}

	int test = abs(player->getX() - boss->getX()) + abs(player->getY() - boss->getY());

	if (player->getX() / 400 == boss->getX() / 400 && player->getY() / 300 == boss->getY() / 300) {
		boss->update(*this);
		fireGun(*boss);	
	}

	clearOrUpdate();

}

void Model::render(float lag, int xPos, int yPos) {
	using namespace std;
	//cout << xPos << "  " << yPos << endl;

	player->render2(renderer, lag, xPos, yPos, ticks);
	for (auto const& b : bullets) {
		b->render(renderer, lag, xPos, yPos);
	}
	for (auto const& a : ais) {
		a->render(renderer, lag, xPos, yPos);
	}

	boss->render(renderer, lag, xPos, yPos);

}


void Model::clearOrUpdate() {
	using namespace std;

	vector<int> indexes;
	vector<int> indexes2;

	for (size_t i = 0; i < bullets.size(); i++) {
		if (!bullets[i]->isDead())
			bullets[i]->update(*this);
		else {
			indexes.push_back(i);
		}
	}

	for (size_t i = 0; i < ais.size(); i++) {
		if (!ais[i]->isDead())
			ais[i]->update(*this);
		else {
			indexes2.push_back(i);
		}
	}

	for (int i = indexes.size() - 1; i >= 0; i--) {
		int ind = indexes[i];
		delete bullets[ind];
		bullets.erase(bullets.begin() + ind);
	}

	for (int i = indexes2.size() - 1; i >= 0; i--) {
		int ind = indexes2[i];
		delete ais[ind];
		ais.erase(ais.begin() + ind);
	}
}

void Model::fireGun(Entity& e) {
	if (e.isWantFire()) {
		e.setWantFire(false);

		BulletEntity* b = generateBullet();
		b->setID(e.getID());
		if (e.getDirection()) {
			b->setXY(e.getX2(), e.getY() + e.getWidth() / 2 - b->getWidth() / 2);
			b->setDirection(1);
		}
		else {
			b->setDirection(0);
			b->setXY(e.getX() - b->getWidth(), e.getY() + e.getWidth() / 2 - b->getWidth() / 2);
		}

		bullets.push_back(b);

	}
}


