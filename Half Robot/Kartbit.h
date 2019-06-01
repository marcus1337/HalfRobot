#pragma once
#include "SDL.h"
#include <iostream>

class Kartbit {
public:

	Kartbit() {

	}

	

	char* getKarta() {
		return karta;
	}


	void setName(int name) {
		_name = name;
	}

	int getName() const {
		return _name;
	}

	void setNeighbors(int neighbors[4]) {
		for (int i = 0; i < 4; i++)
			_neighbors[i] = neighbors[i];
	}

	int* getNeighbors() {
		return _neighbors;
	}

private:
	int _name;
	int _neighbors[4] = {-1,-1,-1,-1};

	char karta[300] = {};

};