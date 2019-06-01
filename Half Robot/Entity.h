#pragma once
#include "Physics.h"
#include "Graphics.h"
#include <chrono>

class EntityInput;

class Entity {
public:
	Entity(Physics* physics, Graphics* graphics, EntityInput* input);

	~Entity();

	virtual void update(Model& model);

	virtual void render(SDL_Renderer* renderer, float lag,int xPos,int yPos);
	virtual void render2(SDL_Renderer* renderer, float lag, int xPos, int yPos, long ticks);

	Physics* getPhysics();

	Graphics* getGraphics();

	EntityInput* getInput();

	int getX();

	int getY();

	int getVelocityX();

	int getVelocityY();

	int getX2() {
		return _x + _width;
	}

	int getY2() {
		return _y + _height;
	}

	int getWidth() {
		return _width;
	}

	int getHeight() {
		return _height;
	}

	void setWidthHeight(int width, int height) {
		_width = width;
		_height = height;
	}

	void setWidth(int width) {
		_width = width;
	}

	void setHeight(int height) {
		_height = height;
	}

	void setVelocityXY(int xVel, int yVel);
	void setVelX(int xVel) {
		_velX = xVel;
	}

	void setVelY(int yVel) {
		_velY = yVel;
	}

	void setXY(int x, int y);
	void setY(int y) {
		_y = y;
	}
	void setX(int x) {
		_x = x;
	}

	void addXY(int x, int y);

	void setDirection(int _dir) { // true == right
		_direction = _dir;
	}

	/***
	@param direction, 0 = left, 1 = right, 2 = up, 3 = down
	*/
	int getDirection() {
		return _direction;
	}

	void setFiring(bool firing) {
		pointTime = std::chrono::steady_clock::now();
		_firing = firing;
	}

	bool isFiring() {
		return _firing;
	}

	bool isDead() {
		return _dead;
	}
	bool startedDying() {
		if (getHP() <= 0)
			setStartedDying(true);
		return _startedDying;
	}

	void setStartedDying(bool startedDying) {
		_startedDying = startedDying;
	}

	void setDead(bool dead) {
		_dead = dead;
		if (_dead) {
			deadTime = std::chrono::steady_clock::now();
		}	

	}					

	int timeDead() {
		std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
		return (int) std::chrono::duration_cast<std::chrono::milliseconds>(current - deadTime).count();
	}

	int getMaxHP() {
		return _maxHp;
	}

	void setMaxHP(int maxHp) {
		_maxHp = maxHp;
		_hp = maxHp;
	}

	void setHP(int hp) {
		_hp = hp;
		if (_hp > _maxHp)
			_hp = _maxHp;
	}

	int getHP() {
		return _hp;
	}

	void setWantFire(bool wantFire) {
		_wantFire = wantFire;
	}

	bool isWantFire() {
		return _wantFire;
	}

	void setMilliSecondTimer(int millisecondTimer) {
		_milliSecondTimer = millisecondTimer;
	}

	void setID(int id) {
		_id = id;
	}

	int getID() {
		return _id;
	}

	void setDamaged(bool damaged) {
		_damaged = damaged;
	}

	bool isDamaged() {
		return _damaged;
	}

	void setDamagedTime() {
		stime = std::chrono::steady_clock::now();
	}

	int getDamagedTime() {
		using namespace std::chrono;
		steady_clock::time_point nowTime = steady_clock::now();
		int diff = (int)duration_cast<milliseconds>(nowTime - stime).count();
		return diff;
	}

protected:
	Physics* _physics;
	Graphics* _graphics;
	EntityInput* _input;
	virtual bool checkCollision(Entity& e);
	std::chrono::steady_clock::time_point stime;

private:
	int _direction = 0;
	int _x, _y, _width, _height;
	int _velX, _velY;
	int _hp = 0;
	int _maxHp;
	bool _firing = false;
	bool _wantFire = false;
	bool _dead = false;
	bool _startedDying;
	bool _damaged = false;
	int _id = 0;


	std::chrono::steady_clock::time_point deadTime;
	std::chrono::steady_clock::time_point pointTime;
	int _milliSecondTimer = 700;

};