#pragma once
#include "Entity.h"
#include "EntityInput.h"
#include "Physics.h"
#include "Graphics.h"

using namespace std;

Entity::Entity(Physics* physics, Graphics* graphics, EntityInput* input) {
	_physics = physics;
	_graphics = graphics;
	_input = input;
	_x = _y = _velX = _velY = 0;
	_width = 32;
	_height = 32;
	_maxHp = _hp = 100;
	_startedDying = false;
	_dead = false;
	_direction = 0;
}

Entity::~Entity() {
	delete _physics;
	delete _graphics;
	delete _input;
}

void Entity::update(Model& model) {

	if (isDead() || startedDying())
		return;

	_input->handleInput(*this);
	_physics->update(model, *this);
	
	if (isFiring()) {
		std::chrono::steady_clock::time_point afterTime = std::chrono::steady_clock::now();
		int diff = std::chrono::duration_cast<std::chrono::milliseconds>(afterTime-pointTime).count();
		if (diff > _milliSecondTimer) {
			setFiring(false);
		}
	
	}

}

void Entity::render(SDL_Renderer* renderer, float lag, int xPos, int yPos) {
	_graphics->render(lag, *this, renderer, xPos, yPos);
}

void Entity::render2(SDL_Renderer* renderer, float lag, int xPos, int yPos, long ticks) {
	_graphics->render2(lag, *this, renderer, xPos, yPos, ticks);
}

Physics* Entity::getPhysics() {
	return _physics;
}

Graphics* Entity::getGraphics() {
	return _graphics;
}

EntityInput* Entity::getInput() {
	return _input;
}

int Entity::getX() {
	return _x;
}

int Entity::getY() {
	return _y;
}



int Entity::getVelocityX() {
	return _velX;
}

int Entity::getVelocityY() {
	return _velY;
}

void Entity::setVelocityXY(int xVel, int yVel) {
	_velX = xVel;
	_velY = yVel;
}

void Entity::setXY(int x, int y) {
	_x = x;
	_y = y;
}

void Entity::addXY(int x, int y) {
	_x += x;
	_y += y;
}


bool Entity::checkCollision(Entity& e) {
	if (getX() > e.getX() && getX() < e.getX2() && getY() > e.getY() && getY() < e.getY2())
		return true;
	if (getX2() > e.getX() && getX2() < e.getX2() && getY() > e.getY() && getY() < e.getY2())
		return true;
	if (getX() > e.getX() && getX() < e.getX2() && getY2() > e.getY() && getY2() < e.getY2())
		return true;
	if (getX2() > e.getX() && getX2() < e.getX2() && getY2() > e.getY() && getY2() < e.getY2())
		return true;

	int midy1 = getY() + getHeight() / 2;
	if (getX() > e.getX() && getX() < e.getX2() && midy1 > e.getY() && midy1 < e.getY2())
		return true;
	if (getX2() > e.getX() && getX2() < e.getX2() && midy1 > e.getY() && midy1 < e.getY2())
		return true;

	return false;
}