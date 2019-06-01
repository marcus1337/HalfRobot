#pragma once
#include "Physics.h"
#include "Model.h"
#include "Entity.h"

class PhysicsBot : public Physics {
public:

	PhysicsBot() {
		xPathBlocked = false;
		yPathBlocked = false;
	}

	virtual void update(Model& model, Entity& entity);

	virtual bool isInAir();
	virtual bool isOnLadder();
	virtual bool canUseLadderUP() {
		return canLadderUP;
	}
	virtual bool canUseLadderDOWN() {
		return canLadderDOWN;
	}

	virtual void enterLadder() {
		using namespace std;
		onLadder = true;
	}

	virtual void exitLadder() {
		onLadder = false;
	}

	virtual bool isXPathBlocked() {
		return xPathBlocked;
	}

	virtual bool isYPathBlocked() {
		return yPathBlocked;
	}

private:

	bool isInLadder(char* karta, int xLeft, int xMid, int xRight, int yDown);

	int checkYCollision(char* karta, int xLeft, int xMid, int xRight, int yUp, int yDown, int yVel);

	void checkExitLadder(char* karta, int xLeft, int xRight, int yDown, int yDownP, int yUp, int yVel);

	void checkCanLadder(char* karta, int xLeft, int xRight, int yDown, int yUp);

private:
	bool inAir = false;
	bool onLadder = false;
	bool wantToExitLadder = false;
	bool canLadderUP = false;
	bool canLadderDOWN = false;

	bool xPathBlocked;
	bool yPathBlocked;

};