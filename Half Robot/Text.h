#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "ShapeFuncs.h"
#include "Windows.h"

class Text {
public:
	Text() {
		emptypath = getfontpath();
		path1 = emptypath + "arial.ttf";
		colorcode = { 255, 255, 255, 255 };
		rect = { 0,0,100,100 };
		message = nullptr;
		ttf = nullptr;
	}

	~Text() {
		if(message)
			SDL_DestroyTexture(message);

	}

	void setFontName(std::string _pathName) {
		path1 = emptypath + _pathName + ".ttf";
	}

	SDL_Rect getRect() {
		return rect;
	}

	void setX(int _x) {
		rect.x = _x;
	}

	int getX() {
		return rect.x;
	}

	void setXY(int _x, int _y) {
		rect.x = _x;
		rect.y = _y;
	}

	int getY() {
		return rect.y;
	}

	int getWidth() {
		return rect.w;
	}

	int getHeight() {
		return rect.h;
	}

	void setY(int _y) {
		rect.y = _y;
	}

	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
		colorcode = {r,g,b, a};
	}

	int getAlpha() {
		return colorcode.a;
	}

	void setAlpha(Uint8 _a) {
		colorcode.a = _a;
	}

	void init(std::string _msg, SDL_Renderer* renderer, int _fSize = 24) {
		if(message)
			SDL_DestroyTexture(message);
		ttf = TTF_OpenFont(path1.c_str(), _fSize);
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(ttf, _msg.c_str(), colorcode);
		ShapeFuncs::setSurfaceAlpha(surfaceMessage, colorcode.a);
		message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
		SDL_FreeSurface(surfaceMessage);
	}

	void init2(SDL_Renderer* _renderer, int _fSize, const std::string &_msg, int _maxWidth) {
			ttf = TTF_OpenFont(path1.c_str(), _fSize);

			SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(ttf, _msg.c_str(), colorcode, _maxWidth);
			ShapeFuncs::setSurfaceAlpha(surf, colorcode.a);
			message = SDL_CreateTextureFromSurface(_renderer, surf);
			SDL_FreeSurface(surf);
			SDL_QueryTexture(message, nullptr, nullptr, &rect.w, &rect.h);
	}

	void reInit2(SDL_Renderer* _renderer, const std::string &_msg, int _maxWidth) {
		SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(ttf, _msg.c_str(), colorcode, _maxWidth);
		if (!surf)
			return;
		ShapeFuncs::setSurfaceAlpha(surf, colorcode.a);
		SDL_Texture* tmp = SDL_CreateTextureFromSurface(_renderer, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(message, nullptr, nullptr, &rect.w, &rect.h);
		if (tmp) {
			SDL_DestroyTexture(message);
			message = tmp;
		}

	}

	void setRect(SDL_Rect _rect) {
		rect = _rect;
	}

	void render(SDL_Renderer* renderer) {
		
	
		SDL_RenderCopy(renderer, message, NULL, &rect);
	}

private:
	SDL_Rect rect;
	SDL_Texture* message;
	SDL_Color colorcode;
	TTF_Font* ttf;
	std::string path1;
	std::string emptypath;

	std::string getfontpath() {
		using namespace std;
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		string test = string(buffer).substr(0, pos);
		test += "\\res\\fonts\\";
		return test;
	}

};