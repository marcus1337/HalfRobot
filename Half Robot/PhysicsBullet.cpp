#include "PhysicsBullet.h"


void PhysicsBullet::update(Model& model, Entity& entity) {
	using namespace std;
	WorldMap& worldmap = model.getPlayerMap();
	bw = worldmap.getWidth();
	char* karta = worldmap.getMapArr();

	int xVel = entity.getVelocityX();
	int yVel = entity.getVelocityY();

	int y = (entity.getY()) / 20;
	int x = (entity.getX()) / 20;

	if (karta[x + y * bw] == 1) {
		entity.setDead(true);
	}
	
	entity.setX(entity.getX() + xVel);
	entity.setY(entity.getY() + yVel);
}