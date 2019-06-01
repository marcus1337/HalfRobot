#pragma once
#include <iostream>
#include "Miniworld.h"
#include "WorldMap.h"

class Model;
class Entity;

class Physics {
public:

	Physics() {
		bw = 20;
	}

	virtual void update(Model& model, Entity& entity);
	virtual bool isInAir() { return true; };

	virtual bool isOnLadder() {
		return false;
	};
	virtual bool canUseLadderUP() {
		return false;
	}
	virtual bool canUseLadderDOWN() {
		return false;
	}

	virtual void enterLadder() {
	}

	virtual void exitLadder() {
	}

	virtual bool isXPathBlocked() {
		return false;
	}

	virtual bool isYPathBlocked() {
		return false;
	}


protected:
	const static int sqrSize = 32;
	int bw;

	bool hitWall(int pos, char* karta) {
		return karta[pos] == 2 || (karta[pos] >= 6 && karta[pos] <= 9);
	}

	bool hitSpike(char* karta, Entity& entity);

};