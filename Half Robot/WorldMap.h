#pragma once
#include "SDL.h"
#include <string>
#include <iostream>
#include "ShapeHandler.h"

class WorldMap {

public:

	WorldMap() {
		_w = 0;
		_h = 0;
		karta = nullptr;
		texture = nullptr;
	}

	~WorldMap() {
		//std::cout << "B" << std::endl;
		if (texture) {
			SDL_DestroyTexture(texture);
		}

		delete[] karta;
	}

	void initArray(int w, int h) {
		_w = w*20;
		_h = h*15;

		if (karta) {
			delete[] karta;
			karta = nullptr;
		}

		karta = new char[_w * _h];
		for (int i = 0; i < (_w * _h); i++) {
			karta[i] = 1;
		}
	}

	void placePiece(int blockX, int blockY, char* pieceArr) {
		using namespace std;
		blockX = blockX * 20;
		blockY = blockY * 15;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 20; j++) {
				int i2 = i + blockY;
				int j2 = j + blockX;

				karta[j2 + i2*_w] = pieceArr[j + i * 20];
		
			}
		}

	}

	void initWorld(SDL_Renderer* renderer) {
		using namespace std;

		if (texture) {
			SDL_DestroyTexture(texture);
		}
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, _w*20, _h*20);

		SDL_Texture* tmpTex;
		
		SDL_SetRenderTarget(renderer, texture);
		SDL_Rect tmpRect = { 0,0,20,20 };
		for (int a = 0; a < _h; a++) {
			for (int b = 0; b < _w; b++) {
				char val = karta[b + a * _w];
				//cout << to_string(val) << ",";
				tmpRect.x = b * 20;
				tmpRect.y = a * 20;

				if (val == 0) {
					SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(renderer, &tmpRect);
				}
				if (val == 1) {
					tmpTex = ShapeHandler::tiles[0];
					SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);


					SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(renderer, 0x00, 0xF5, 0x55, 0x44);
					SDL_RenderFillRect(renderer, &tmpRect);
				}
				if (val == 2) {
					tmpTex = ShapeHandler::tiles[1];
					SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
				}

				if (val == 6) {
					tmpTex = ShapeHandler::tiles[2];
					SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
				}

				if (val == 7) {
					tmpTex = ShapeHandler::tiles[2];
					SDL_RenderCopyEx(renderer, tmpTex, NULL, &tmpRect, NULL, NULL, SDL_FLIP_VERTICAL);
				}

				if (val == 8) {
					tmpTex = ShapeHandler::tiles[2];
					SDL_RenderCopyEx(renderer, tmpTex, NULL, &tmpRect, 90, NULL, SDL_FLIP_NONE);
				}

				if (val == 9) {
					tmpTex = ShapeHandler::tiles[2];
					SDL_RenderCopyEx(renderer, tmpTex, NULL, &tmpRect, 270, NULL, SDL_FLIP_NONE);
				}


			}
		//	cout << endl;

		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xf4, 0xFF);
		SDL_SetRenderTarget(renderer, NULL);

	}

	SDL_Texture* getTexture() {
		return texture;
	}

	char* getMapArr() {
		return karta;
	}

	//void render(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst) {
	//	SDL_RenderCopy(renderer, texture, &src, &dst);
	//}

	int getWidth() {
		return _w;
	}

	int getHeight() {
		return _h;
	}

private:

	int _w, _h;
	char* karta;
	SDL_Texture* texture;
};