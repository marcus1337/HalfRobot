#pragma once
#include "Physics.h"
#include "Model.h"
#include "Entity.h"
#include "Kartbit.h"
#include <iostream>

void Physics::update(Model& model, Entity& entity) {
	using namespace std;
	WorldMap& worldmap = model.getPlayerMap();
	bw = worldmap.getWidth();
	char* karta = worldmap.getMapArr();

	int xVel = entity.getVelocityX();
	int yVel = entity.getVelocityY();

	
 

}

bool Physics::hitSpike(char* karta, Entity& entity) {
	int xVel = entity.getVelocityX();
	int yVel = entity.getVelocityY();

	if (yVel < 0)
		return false;


	int x1 = entity.getX() / 20;
	int x2 = entity.getX2() / 20;
	int x3 = (x2 + x1) / 2;

	int y1 = (entity.getY()-1) / 20;
	int y2 = (entity.getY2()) / 20;
	int y3 = (y1 + y2) / 2;

	int y5 = (entity.getY2()+1) / 20;

	if (yVel == 0) {
		if (karta[x1 + y5 * bw] == 6 && karta[x2 + y5 * bw] == 6 && karta[x3 + y5 * bw] == 6) {
			return true;
		}

	}

	/*//NE
	if (karta[x1 + y1 * bw] == 7 || karta[x2 + y1 * bw] == 7 || karta[x3 + y1 * bw] == 7) {
		return true;
	}

	//E
	if (karta[x2 + y3 * bw] == 8 || karta[x2 + y1 * bw] == 8 || karta[x2 + y2 * bw] == 8) {
		return true;
	}

	//W

	if (karta[x2 + y3 * bw] == 9 || karta[x2 + y1 * bw] == 9 || karta[x2 + y2 * bw] == 9) {
		return true;
	}*/

	//SW
	if (karta[x1 + y2 * bw] == 6 || karta[x2 + y2 * bw] == 6 || karta[x3 + y2 * bw] == 6) {
		return true;
	}

	return false;

}