#include "Game.h"
#include "TextureManager.h"


Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title, x, y, width, height, fullscreen);
	renderer = SDL_CreateRenderer(window, -1, 0);

	carTexture = TextureManager::LoadTexture("assets/SportsRacingCar_3.png",renderer);
	roadTexture = TextureManager::LoadTexture("assets/background-1.png", renderer);

	carRect = { 350, 400, 250, 250 };
	

	carRect.x = 350;
	carRect.y = 400;
	carRect.w = 180;
	carRect.h = 180;

	isRunning = true;
}

bool movingRight = false;
bool movingLeft = false;
bool movingUp = false;
bool movingDown = false;

void Game::handlEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			movingUp = true;
			break;
		case SDLK_DOWN:
			movingDown = true;
			break;
		case SDLK_LEFT:
			movingLeft = true;
			break;
		case SDLK_RIGHT:
			movingRight = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			movingUp = false;
			break;
		case SDLK_DOWN:
			movingDown = false;
			break;
		case SDLK_LEFT:
			movingLeft = false;
			break;
		case SDLK_RIGHT:
			movingRight = false;
			break;
		}
		break;
	}

}

bool Game::running() const {
	return isRunning;
}

void Game::update() {
	float dx = 0, dy = 0;
	float speed = 10.0f;
	if (movingUp) {
		dy -= 1;
	}
	if (movingDown) {
		dy += 1;
	}
	if (movingLeft) {
		dx -= 1;
	}
	if (movingRight) {
		dx += 1;
	}
	if (dx != 0 && dy != 0) {
		dx *= 0.7071f;
		dy *= 0.7071f;
	}

	carRect.x += dx * speed;
	carRect.y += dy * speed;
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, roadTexture, NULL, NULL);
	SDL_RenderCopy(renderer, carTexture, NULL, &carRect);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
