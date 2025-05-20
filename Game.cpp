#include "Game.h"
#include "TextureManager.h"
#include "GameOverMenu.h"
#include "Player.h"
#include "Enermy.h"
#include <cstdlib>
#include <SDL_ttf.h>
#include <vector>
#include <algorithm>
#include <random>
#include <string>


Game::Game() {}
Game::~Game() {}

using namespace std;

// chuong ngai vat
const int NUM_OBSTCLES = 3;
const int lanePositions[] = { 190, 310, 430, 550 };

vector<int> getRandomLanes() {
	vector <int> lanePositions = { 190, 310, 430, 550 };
	random_device rd;
	mt19937 g(rd());
	shuffle(lanePositions.begin(), lanePositions.end(), g);
	lanePositions.resize(3);
	return lanePositions;

}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title, x, y, width, height, fullscreen);
	renderer = SDL_CreateRenderer(window, -1, 0);
	player = new Player(TextureManager::LoadTexture("assets/car1.png", renderer), 310, 400, 52, 111);
	roadTexture = TextureManager::LoadTexture("assets/background-1.png", renderer);
	obstacles[0] = new Enermy(TextureManager::LoadTexture("assets/car2.png", renderer), lanePositions[rand() % 4], -100, 110, 50);
	obstacles[1] = new Enermy(TextureManager::LoadTexture("assets/car8.png", renderer), lanePositions[rand() % 4], -300, 110, 50);
	obstacles[2] = new Enermy(TextureManager::LoadTexture("assets/car7.png", renderer), lanePositions[rand() % 4], -500, 110, 50);

	vector<int> randomLanes = getRandomLanes();
	obstacles[0]->setPosition(randomLanes[0], -100);
	obstacles[1]->setPosition(randomLanes[1], -300);
	obstacles[2]->setPosition(randomLanes[2], -500);

	isRunning = true;

	//  diem so
	TTF_Init();
	font = TTF_OpenFont("assets/arial.ttf", 24);

	// menu gameover
	gameOverMenu = new GameOverMenu(renderer, font, width, height);
	
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	return SDL_HasIntersection(&a, &b);
}

void Game::handlEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		player->handleInput(event);
	}
	player->update();
	vector<Enermy*> obsVec(obstacles, obstacles + NUM_OBSTCLES);
	for (int i = 0; i < NUM_OBSTCLES; i++) {
		obstacles[i]->update();
		if (obstacles[i]->getRect().y > 600) {
			obstacles[i]->resetPosition(obsVec);
		}
	}

	

	// kiem tra va cham
	for (int i = 0; i < NUM_OBSTCLES; i++) {
		if (checkCollision(player->getRect(), obstacles[i]->getRect())) {
			isgameOver = true;
			break;
		}
	}

}

bool Game::running() const {
	return isRunning;
}

// background di chuyen

SDL_Rect bgRect1 = { 0, 0, 800, 600 };
SDL_Rect bgRect2 = { 0, -600, 800, 600 };

void Game::update() {

	// background di chuyen

	int scrollSpeed = 20;
	bgRect1.y += scrollSpeed;
	bgRect2.y += scrollSpeed;


	if (bgRect1.y >= 600) {
		bgRect1.y = -600;
	}
	if (bgRect2.y >= 600) {
		bgRect2.y = -600;
	}

	//diem so
	score++;
	if (score % 1000 == 0) {
		enermySpeed += 1;
	}

	
}

void Game::render() {
	SDL_RenderClear(renderer);

	// background + car
	SDL_RenderCopy(renderer, roadTexture, NULL, &bgRect1);
	SDL_RenderCopy(renderer, roadTexture, NULL, &bgRect2);
	player->render(renderer);
	for (int i = 0; i < NUM_OBSTCLES; i++) {
		obstacles[i]->render(renderer);
	}

	// diem so
	SDL_Color textColor = { 255, 255, 255, 255 };
	string scoreText = "Score: " + to_string(score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { 20, 20, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	// game over
	if (isgameOver) {
		SDL_Color red = { 255, 0, 0, 255 };
		SDL_Surface* overSurface = TTF_RenderText_Solid(font, "Game Over", red);
		SDL_Texture* overTexture = SDL_CreateTextureFromSurface(renderer, overSurface);
		SDL_Rect overRect = { 300, 200, overSurface->w, overSurface->h };
		SDL_RenderCopy( renderer, overTexture, NULL, &overRect );
		SDL_FreeSurface(overSurface);
		SDL_DestroyTexture(overTexture);
	}

	if (isgameOver) {
		gameOverMenu->render(score);
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete player;
	for (int i = 0; i < NUM_OBSTCLES; i++) {
		delete obstacles[i];
	}
	delete gameOverMenu;
	gameOverMenu = nullptr;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

