#include "Game.h"
#include "TextureManager.h"
#include <cstdlib>


Game::Game() {}
Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title, x, y, width, height, fullscreen);
	renderer = SDL_CreateRenderer(window, -1, 0);

	carTexture = TextureManager::LoadTexture("assets/SportsRacingCar_3.png",renderer);
	roadTexture = TextureManager::LoadTexture("assets/background-1.png", renderer);
	enermyCar1Texture = TextureManager::LoadTexture("assets/xe1.png", renderer);
	enermyCar2Texture = TextureManager::LoadTexture("assets/xe3.png", renderer);

	carRect = { 310, 400, 120, 120 };
	enermyCar1Rect = { 175, 0, 80, 80 };
	enermyCar2Rect = { 310, 0, 49, 118 };

	

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


// background di chuyen

SDL_Rect bgRect1 = { 0, 0, 800, 600 };
SDL_Rect bgRect2 = { 0, -600, 800, 600 };

void Game::update() {
	float dx = 0, dy = 0;
	float speed = 15.0f;
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


	int scrollSpeed = 20;
	bgRect1.y += scrollSpeed;
	bgRect2.y += scrollSpeed;


	if (bgRect1.y >= 600) {
		bgRect1.y = -600;
	}
	if (bgRect2.y >= 600) {
		bgRect2.y = -600;
	}


	// gioi han xe trong khoang nhat dinh

	if (carRect.x < 100) carRect.x = 100;
	if (carRect.y < 0) carRect.y = 0;
	if (carRect.x + carRect.w > 700) carRect.x = 700 - carRect.w;
	if (carRect.y + carRect.h > 600) carRect.y = 600 - carRect.h;

	// chuong ngai vat 1

	const int lanePositions1[] = { 175, 295, 415, 535 };
	int laneIndex = rand() % 4;
	enermyCar1Rect.y += 5;
	if (enermyCar1Rect.y > 600) {
		enermyCar1Rect.y = -200;
		enermyCar1Rect.x = lanePositions1[laneIndex];
	}

	// chuong ngai vat 2

	const int lanePositions[] = { 439, 190, 550, 310 };
	enermyCar2Rect.y += 5;
	if (enermyCar2Rect.y > 600) {
		enermyCar2Rect.y = -200;
		enermyCar2Rect.x = lanePositions[laneIndex];
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, roadTexture, NULL, &bgRect1);
	SDL_RenderCopy(renderer, roadTexture, NULL, &bgRect2);
	SDL_RenderCopy(renderer, carTexture, NULL, &carRect);
	SDL_RenderCopy(renderer, enermyCar1Texture, NULL, &enermyCar1Rect);
	SDL_RenderCopy(renderer, enermyCar2Texture, NULL, &enermyCar2Rect);
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

