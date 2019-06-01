#pragma once
#include "Entity.h"
#include "Graphics.h"
#include "Physics.h"
#include "EntityInput.h"
#include "SDL.h"
#include "Window.h"
#include "World.h"
#include "Kartbit.h"
#include "WorldMap.h"
#include "BulletEntity.h"
#include "PlayerEntity.h"

#include <vector>

class Model {
public:
	Model();
	~Model();

	void update();
	void initWorld(int w_id);

	void render(float lag, int xPos, int yPos);

	void setWorld(WorldMap* _themap) {
		worldmap = _themap;
	}

	WorldMap& getPlayerMap() {
		return *worldmap;
	}

	Entity& getPlayerEntity() {
		return *player;
	}

	int getLives() {
		return player->getLives();
	}

	void setLives(int _lives) {
		player->setLives(_lives);
	}

	bool lockX() {
		return xlock;
	}

	void setLockX(bool _lock) {
		xlock = _lock;
	}

	bool mapWon() {
		return false;
	}

	bool gameWon() {
		return false;
	}

	bool gameLost() {
		return (player->getLives() <= 0 && player->getHP() <= 0);
	}

	std::vector<Entity*>& getAis() {
		return std::ref(ais);
	}

	Entity* getBoss() {
		return boss;
	}

	//std::vector<Kartbit>& getWorld() {
	//	return std::ref(_kartor);
	//}

	void respawn();

	bool inBossArea() { 
		int px = (getPlayerEntity().getX() / 400) * 400;
		int py = (getPlayerEntity().getY() / 300) * 300;
		int px2 = (getBoss()->getX() / 400) * 400;
		int py2 = (getBoss()->getY() / 300) * 300;
		return px == px2 && py == py2;
	}

	void setRenderer(SDL_Renderer* _renderer) {
		renderer = _renderer;
	}

	long getTicks();

	int getWorldID() {
		return world_id;
	}

private:
	long ticks;

	PlayerEntity* player;
	Entity* boss;
	SDL_Renderer* renderer;

	WorldMap* worldmap;
	std::vector<Entity*> bullets;
	std::vector<Entity*> ais;

	bool xlock;

	int bossCoords[4];

	int world_id;


	void spawnAis(int _world_id);

	void fireGun(Entity& e);

	void clearOrUpdate();

	int spawnX, spawnY;

	void clearWorld();

};