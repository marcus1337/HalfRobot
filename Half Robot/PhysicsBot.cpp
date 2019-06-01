#pragma once
#include "PhysicsBot.h"
using namespace std;



void PhysicsBot::update(Model& model, Entity& entity) {

	WorldMap& worldmap = model.getPlayerMap();
	bw = worldmap.getWidth();
	char* karta = worldmap.getMapArr();

	if (entity.isDead())
		return;

	int xVel = entity.getVelocityX();
	int yVel = entity.getVelocityY();

	int x1 = entity.getX() / 20;
	int x2 = entity.getX2() / 20;
	int x3 = (x2 + x1) / 2;


	int xtmp = (entity.getX2() + xVel) / 20;
	//cout << "x2: " << xtmp << endl;

	int y1 = (entity.getY2()) / 20;
	int y2 = (entity.getY2() + 1) / 20;
	int y3 = (entity.getY()) / 20;

	//cout << "X: " << x1 << " Y: " << y1 << endl;

	int xSpec1 = (entity.getX2() - 10) / 20;
	int xSpec2 = (entity.getX() + 10) / 20;

	bool tightSpace = false;


	//cout << "X1: " << x3 << " X2: " << x2  << " X3: " << x4 << " Y: "<<y2 <<  endl;
	//cout << "TEST!! " << x3 << "  " << x2 << endl;

	checkCanLadder(karta, xSpec1, xSpec2, y2, y3);

	checkExitLadder(karta, xSpec1, xSpec2, y1, y2, y3, yVel);
	int realYVel = checkYCollision(karta, x1, x3, x2, entity.getY(), entity.getY2(), yVel);

	if (onLadder) {

	/*	realYVel = entity.getVelocityY();

		if (karta[xSpec1 + y2 * bw] == 2 || karta[xSpec1 + y3 * bw] == 2) {
			entity.setX(xSpec1 * 20 - 8);
		}
		else if (karta[xSpec2 + y2 * bw] == 2 || karta[xSpec2 + y3 * bw] == 2) {
			entity.setX(xSpec2 * 20 - 8);
		}
		x1 = entity.getX() / 20;
		x2 = entity.getX2() / 20;
		x3 = (x2 + x1) / 2;
		realYVel = checkYCollision(karta, x3, x3, x3, entity.getY(), entity.getY2(), yVel);
		*/
	}
	else if (!onLadder) {

		if ((karta[x2 + y2 * bw] == 0 || (karta[x2 + y2 * bw] == 2)) &&
			(karta[x1 + y2 * bw] == 0 || (karta[x1 + y2 * bw] == 2)) &&
			(karta[x3 + y2 * bw] == 0 || (karta[x3 + y2 * bw] == 2))) {

			bool inLadder = isInLadder(karta, x1, x3, x2, entity.getY2());

			inAir = true;

			if (!inLadder && (karta[x2 + y2 * bw] == 2 || karta[x1 + y2 * bw] == 2
				|| karta[x3 + y2 * bw] == 2)) {
				inAir = false;
			}

			if (realYVel > 0)
				if (!inLadder) {
					if (karta[x2 + y2 * bw] == 2 || karta[x1 + y2 * bw] == 2 || karta[x3 + y2 * bw] == 2) {
						realYVel = 0;
						inAir = false;
					}

					int ySpec = (entity.getY2() + realYVel) / 20;
					if (karta[x2 + ySpec * bw] == 2 || karta[x1 + ySpec * bw] == 2 || karta[x3 + ySpec * bw] == 2) {
						realYVel = 0;
						inAir = false;
						while ((karta[x2 + y2 * bw] != 2 && karta[x1 + y2 * bw] != 2 && karta[x3 + y2 * bw] != 2)) {

							entity.addXY(0, 1);

							y2 = (entity.getY2() + 1) / 20;
						}

					}

				}

		}
		else {
			inAir = false;
		}

		if (karta[x3 + y1 * bw] == 2 && karta[x1 + y3 * bw] == 1 && karta[x2 + y3 * bw] == 1) {
			realYVel = entity.getVelocityY();
			inAir = true;
			tightSpace = true;
		}
		if (karta[x3 + y1 * bw] == 2 && karta[x1 + y1 * bw] == 1 && karta[x2 + y1 * bw] == 1) {
			realYVel = entity.getVelocityY();
			inAir = true;
			tightSpace = true;
		}
		//	int x1 = entity.getX() / 20;
		//	int x2 = entity.getX2() / 20;
		//	int x3 = (x2 + x1) / 2;
		//	int y1 = (entity.getY2()) / 20;
		//	int y2 = (entity.getY2() + 1) / 20;
		//	int y3 = (entity.getY()) / 20;


	}


	entity.addXY(0, realYVel);

	if (entity.getVelocityY() > 0 && entity.getVelocityY() > realYVel)
		yPathBlocked = true;
	else if (entity.getVelocityY() < 0 && entity.getVelocityY() < realYVel)
		yPathBlocked = true;
	else
		yPathBlocked = false;



	y1 = (entity.getY2()) / 20;
	y3 = (entity.getY()) / 20;

	if (xVel > 0) {
		xPathBlocked = true;
		int x5 = (entity.getX2() + xVel) / 20;
		if (karta[x5 + y1 * bw] != 1 && karta[x5 + y3 * bw] != 1) {
			entity.addXY(entity.getVelocityX(), 0);
			xPathBlocked = false;
		}
	}
	else if (xVel < 0) {
		xPathBlocked = true;
		int x5 = (entity.getX() + xVel) / 20;
		if (karta[x5 + y1 * bw] != 1 && karta[x5 + y3 * bw] != 1) {
			entity.addXY(entity.getVelocityX(), 0);
			xPathBlocked = false;
		}
	}

	if (!onLadder && !tightSpace)
		while ((karta[x2 + y1 * bw] == 1 || karta[x2 + y3 * bw] == 1) && karta[x1 + y1 * bw] != 1) {
			entity.setX(entity.getX() - 1);
			x2 = entity.getX2() / 20;

		}
	if (!onLadder && !tightSpace)
		while ((karta[x1 + y1 * bw] == 1 || karta[x1 + y3 * bw] == 1) && karta[x2 + y1 * bw] != 1) {
			entity.setX(entity.getX() + 1);
			x1 = entity.getX() / 20;
		}

	if (entity.getInput()->getType() != "hurt") {



	}

}


bool PhysicsBot::isOnLadder() {
	return onLadder;
}


bool PhysicsBot::isInAir() {
	return inAir;
}


int PhysicsBot::checkYCollision(char* karta, int xLeft, int xMid, int xRight, int yUp, int yDown, int yVel) {
	using namespace std;
	int yNewUp = (yUp + yVel) / 20;
	int yNewDown = (yDown + yVel) / 20;
	int tmpVel = yVel;
	if (yVel < 0) {

		for (int i = yVel; i <= 0 && tmpVel != 0; i++) {

			if (karta[xRight + yNewUp * bw] != 1 && karta[xLeft + yNewUp * bw] != 1 && karta[xMid + yNewUp * bw] != 1
				&& karta[xRight + yNewUp * bw] != 6 && karta[xLeft + yNewUp * bw] != 6 && karta[xMid + yNewUp * bw] != 6
				)
			{
				return tmpVel;

			}

			tmpVel++;
			yNewUp = (yUp + tmpVel) / 20;
		}
	}
	else if (yVel > 0) {
		for (int i = yVel; i >= 0 && tmpVel != 0; i--) {
			if (karta[xRight + yNewDown * bw] != 1 && karta[xLeft + yNewDown * bw] != 1 && karta[xMid + yNewDown * bw] != 1
				&& karta[xRight + yNewDown * bw] != 6 && karta[xLeft + yNewDown * bw] != 6 && karta[xMid + yNewDown * bw] != 6)
			{
				return tmpVel;
			}

			tmpVel--;
			yNewDown = (yDown + tmpVel) / 20;
		}
	}

	return tmpVel;
}

bool PhysicsBot::isInLadder(char* karta, int xLeft, int xMid, int xRight, int yDown) {
	int y1 = (yDown - 1) / 20;
	if (karta[xRight + y1 * bw] == 2 || karta[xLeft + y1 * bw] == 2 || karta[xMid + y1 * bw] == 2) {
		return true;
	}
	return false;
}

void PhysicsBot::checkExitLadder(char* karta, int xLeft, int xRight, int yDown, int yDownP, int yUp, int yVel) {
	if (!onLadder)
		return;
	using namespace std;

	if (yVel < 0) {
		if (karta[xLeft + yDownP * bw] == 0 && karta[xRight + yDownP * bw] == 0) {
			onLadder = false;
			//cout << "TEST: " << yDownP << endl;

		}
	}
	else if (yVel > 0) {
		if ((karta[xLeft + yUp * bw] != 2 && karta[xRight + yUp * bw] != 2 &&
			(karta[xLeft + yDownP * bw] != 2 && karta[xRight + yDownP * bw] != 2))
			|| (karta[xLeft + yDownP * bw] == 1 || karta[xRight + yDownP * bw] == 1)
			) {
			onLadder = false;
		}
	}
}

void PhysicsBot::checkCanLadder(char* karta, int xLeft, int xRight, int yDown, int yUp) {
	if (karta[xLeft + yDown * bw] == 2 || karta[xRight + yDown * bw] == 2) {
		canLadderDOWN = true;
	}
	else
		canLadderDOWN = false;

	if (karta[xLeft + yUp * bw] == 2 || karta[xRight + yUp * bw] == 2) {
		canLadderUP = true;
	}
	else
		canLadderUP = false;
}
