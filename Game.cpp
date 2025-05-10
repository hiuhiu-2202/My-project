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

	carRect = { 350, 400, 100, 100 };
	roadRect = { 0, 0, 800, 600 };

	isRunning = true;
}
void Game::handlEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}
}

void Game::update() {

}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, roadTexture, NULL, &roadRect);
	SDL_RenderCopy(renderer, carTexture, NULL, &carRect);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
