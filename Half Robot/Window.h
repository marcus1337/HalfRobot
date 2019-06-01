#pragma once
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Window {

public:
	Window(const std::string &title, int width, int height);
	~Window();

	inline bool isClosed() const { return _closed; }
	inline int getWidth() const { return SDL_GetWindowSurface(_window)->w; }
	inline int getHeight() const { return SDL_GetWindowSurface(_window)->h; }

	const bool isFocus() const {
		return (SDL_GetWindowFlags(_window) & SDL_WINDOW_INPUT_FOCUS) != 0;
	}

	inline int midX() const { return SDL_GetWindowSurface(_window)->w / 2; }
	inline int midY() const { return SDL_GetWindowSurface(_window)->h / 2; }

	void clear() const;

	void closeDown() {
		_closed = true;
	}

	inline SDL_Renderer* getRenderer() const {
		return _renderer;
	}

	SDL_Window* getWindow() {
		return _window;
	}


private:
	bool init();

private:
	std::string _title;
	int _width = 800;
	int _height = 600;
	bool _closed = false;

	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;

	

};