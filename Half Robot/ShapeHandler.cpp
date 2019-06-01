#include "ShapeHandler.h"

std::string ShapeHandler::rpath;

SDL_Texture* ShapeHandler::mouseText;
SDL_Texture* ShapeHandler::buttonpress;
SDL_Texture* ShapeHandler::button;

SDL_Texture* ShapeHandler::heroLadder;
SDL_Texture* ShapeHandler::heroJump;
SDL_Texture* ShapeHandler::heroStill;
SDL_Texture** ShapeHandler::heroWalk = new SDL_Texture*[5];
SDL_Texture** ShapeHandler::bull1 = new SDL_Texture*[9];
SDL_Texture* ShapeHandler::heroHurt;

SDL_Texture* ShapeHandler::heroFireStill;
SDL_Texture** ShapeHandler::heroFireWalk = new SDL_Texture*[3];
SDL_Texture* ShapeHandler::heroFireJump;
SDL_Texture* ShapeHandler::heroFireLadder;

SDL_Texture** ShapeHandler::tiles = new SDL_Texture*[10];

SDL_Texture* ShapeHandler::health_bar;
SDL_Texture* ShapeHandler::health_bar_b;

SDL_Texture* ShapeHandler::audioOn;
SDL_Texture* ShapeHandler::audioOff;

SDL_Texture* ShapeHandler::backbtn;
SDL_Texture* ShapeHandler::backbtn2;

SDL_Texture* ShapeHandler::background1;
SDL_Texture* ShapeHandler::background2;
SDL_Texture* ShapeHandler::background3;
SDL_Texture* ShapeHandler::background4;
SDL_Texture* ShapeHandler::background5;

SDL_Texture* ShapeHandler::sponsorimg;