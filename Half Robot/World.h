#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <iostream>
#include "Window.h"
#include <vector>
#include "Kartbit.h"
#include <set>
#include <algorithm>
#include "WorldMap.h"
#include <Windows.h>

class World {
public:

	void loadMapNum(int num, Kartbit& kartbit) {
		using namespace std;
		char* kartpiece = kartbit.getKarta();

		ifstream infile(w_path + to_string(num) + ".plan");
		string line;

		int counter = 0;
		while (getline(infile, line))
		{
			stringstream ss(line);
			int a;

			while (ss >> a)
			{
				kartpiece[counter] = (char)a;
				if (ss.peek() == ',')
					ss.ignore();
				counter++;
			}

		}
		infile.close();

	}

	void readInfo() {
		using namespace std;

		ifstream infile(w_path + "specs" + ".plan");
		string line;

		
		getline(infile, line);
		stringstream ss(line);
		int width; int height;
		ss >> width;
		ss >> height;

		worldMap.initArray(width, height);

		while (getline(infile, line))
		{
			stringstream ss(line);
			int name;
			int posX; int posY;
			ss >> name;
			ss >> posX;
			ss >> posY;
		//	cout << "NAME: " << name << " X: " << posX << " Y: " << posY << endl;
			worldMap.placePiece(posX, posY, kartan[name-1].getKarta());

		}
		infile.close();


	}

	/*static int gcd(int a, int b) {
		return (b == 0) ? a : gcd(b, a%b);
	}*/

	void initDimensions(Window& window) {
		int w = window.getWidth();
		int h = window.getHeight();


		if ((float)h / w >= 0.75f) {
			int x = w;
			int y = (3.0f / 4.0f)*w;
			w = x;
			h = y;
		}
		else {
			int y = h;
			int x = (4.0f / 3.0f)*h;
			w = x;
			h = y;
		}

		kartHeight = h;
		kartWidth = w;

		midX = (window.getWidth() - w) / 2;
	}

	void init(Window& window, int w_id) {
		using namespace std;
		w_path = pathfull() + to_string(w_id) + "\\";

		int w = window.getWidth();
		int h = window.getHeight();


		if ((float)h / w >= 0.75f) {
			int x = w;
			int y = (3.0f / 4.0f)*w;
			w = x;
			h = y;
		}
		else {
			int y = h;
			int x = (4.0f / 3.0f)*h;
			w = x;
			h = y;
		}
	
		kartHeight = h;
		kartWidth = w;

		midX = (window.getWidth() - w) / 2;
		SDL_Renderer* renderer = window.getRenderer();

		for (int i = 0; i < 10; i++) {
			Kartbit piece;
			piece.setName(i);
			loadMapNum(i + 1, ref(piece));
			kartan.push_back(piece);
		}

		readInfo();
		worldMap.initWorld(renderer);

	}

	static int getKartW();

	static int getKartH();

	static int getKartMidX();


	std::vector<Kartbit> getWorldPieces() {
		return kartan;
	}

	void clearWorld() {
		kartan.clear();
	}

	WorldMap& getWorld() {
		return std::ref(worldMap);
	}


private:
	static int midX;
	static int kartHeight;
	static int kartWidth;
	std::vector<Kartbit> kartan;
	WorldMap worldMap;

	std::string w_path;

	static std::string pathfull() {
		using namespace std;
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		string test = string(buffer).substr(0, pos);
		test += "\\bin\\save\\world";
		return test;
	}

};






/*for (int b = 0; b < 15; b++) {
for (int j = 0; j < 20; j++) {
cout << to_string(karta[j + b * 20]) << ",";
}
cout << endl;
}*/