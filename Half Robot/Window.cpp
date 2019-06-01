#include "Window.h"
#include <iostream>
#include "IOStuff.h"

Window::Window(const std::string &title, int width, int height)
	: _title(title), _width(width), _height(height)
{
	_closed = !init();
};

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

using namespace std;

bool Window::init() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << "Failed to initialize SDL VIDEO. \n";
		return 0;
	}

	if (IMG_Init(IMG_INIT_PNG) != 2) {
		std::cerr << "Failed to initialize SDL_Image.\n";
		return 0;
	}

	if (TTF_Init() == -1) {
		std::cerr << "Failed to initialize TTF.\n";
		return 0;
	}

	Settings settings;
	IOStuff iostuff;
	iostuff.loadSettings(ref(settings));
	
	if (settings.getH() != -1 && settings.getW() != -1) {
		_width = settings.getW();
		_height = settings.getH();
	}

	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height,
		SDL_WINDOW_RESIZABLE
	);

	SDL_SetWindowTitle(_window, "Half Robot");
	//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	if (_window == nullptr) {
		std::cerr << "Failed to initialize window. \n";
		return 0;
	}
	SDL_GL_SetSwapInterval(1);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		std::cerr << "renderer failed to init. \n";
		return 0;
	}


	return true;

}


void Window::clear() const {
	SDL_SetRenderDrawColor(_renderer, 20, 40, 20, 255);
	SDL_RenderClear(_renderer);
}