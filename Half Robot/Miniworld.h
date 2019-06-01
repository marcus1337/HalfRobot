#pragma once
#include "Kartbit.h"
#include <vector>
#include <iostream>

class Miniworld {
public:

	void init(std::vector<Kartbit>* kartor, Kartbit* karta) {
		_kartor = kartor;
		_karta = karta;
		kMap = _karta->getKarta();
		grannar = _karta->getNeighbors(); // 0 = Up, 1 = Down, 2 = L, 3 = R
		
		if (grannar[0] != -1) { //UP

		}

		if (grannar[1] != -1) { //DOWN

		}

		if (grannar[2] != -1) { // LEFT

		}

		if (grannar[3] != -1) { //RIGHT
			int name = grannar[3];
			granMap[3] = &kartor->at(name - 1);
		}
		else granMap[3] = nullptr;


	}

	char getValue(int x, int y) {
		if (x < 0) {
			return 1;
		}
		else if (x >= 20) {

			if (granMap[3]) {
				int x2 = x - 20;
				return granMap[3]->getKarta()[x2 + y * 20];
			}

			return 1;
		}

		return _karta->getKarta()[x + y * 20];
	}


private:
	std::vector<Kartbit>* _kartor;
	Kartbit* _karta;
	char* kMap;
	int* grannar;
	Kartbit* granMap[4];

};