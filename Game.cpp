#include "Game.h"
#include "TextureManager.h"
#include <cstdlib>
#include <SDL_ttf.h>
#include <string>


Game::Game() {}
Game::~Game() {}

using namespace std;

// chuong ngai vat
const int NUM_OBSTCLES = 3;
SDL_Rect obstacles[NUM_OBSTCLES];
const int lanePositions[] = { 190, 310, 430, 550 };
int enermySpeed = 5;

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title, x, y, width, height, fullscreen);
	renderer = SDL_CreateRenderer(window, -1, 0);

	carTexture = TextureManager::LoadTexture("assets/car1.png",renderer);
	roadTexture = TextureManager::LoadTexture("assets/background-1.png", renderer);
	enermyCar1Texture = TextureManager::LoadTexture("assets/car2.png", renderer);
	enermyCar2Texture = TextureManager::LoadTexture("assets/car8.png", renderer);
	enermyCar3Texture = TextureManager::LoadTexture("assets/car7.png", renderer);

	carRect = { 310, 400, 52, 111 };

	
	for (int i = 0; i < NUM_OBSTCLES; i++) {
		int lane = rand() % 4;
		obstacles[i].x = lanePositions[lane];
		obstacles[i].y = -(rand() % 200 + i * 150);
		obstacles[i].w = 50;
		obstacles[i].h = 110;
	}

	

	isRunning = true;

	//  diem so
	TTF_Init();
	font = TTF_OpenFont("assets/arial.ttf", 24);
	
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


// va cham
bool checkCollision(SDL_Rect a, SDL_Rect b) {
	return SDL_HasIntersection(&a, &b);
}

void Game::update() {
	float dx = 0, dy = 0;
	float speed = 6.0f;
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

	if (carRect.x < 150) carRect.x = 150;
	if (carRect.y < 0) carRect.y = 0;
	if (carRect.x + carRect.w > 650) carRect.x = 650 - carRect.w;
	if (carRect.y + carRect.h > 600) carRect.y = 600 - carRect.h;

	// chuong ngai vat
	for (int i = 0; i < NUM_OBSTCLES; i++) {
		obstacles[i].y += enermySpeed;

		if (obstacles[i].y > 600) {
			int lane = rand() % 4;
			obstacles[i].x = lanePositions[lane];
			obstacles[i].y = -100;
			obstacles[i].h = 110;
			obstacles[i].w = 50;
		}
	}

	// va cham
	for (int i = 0; i < 3; i++) {
		if (checkCollision(carRect, obstacles[i])) {
			isRunning = false;
			break;
		}
	}

	//diem so
	score++;
	if (score % 500 == 0) {
		enermySpeed += 1;
	}
	
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, roadTexture, NULL, &bgRect1);
	SDL_RenderCopy(renderer, roadTexture, NULL, &bgRect2);
	SDL_RenderCopy(renderer, carTexture, NULL, &carRect);
	SDL_RenderCopy(renderer, enermyCar1Texture, NULL, &obstacles[0]);
	SDL_RenderCopy(renderer, enermyCar2Texture, NULL, &obstacles[1]);
	SDL_RenderCopy(renderer, enermyCar3Texture, NULL, &obstacles[2]);
	// diem so
	SDL_Color textColor = { 255, 255, 255, 255 };
	string scoreText = "Score: " + to_string(score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { 20, 20, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

