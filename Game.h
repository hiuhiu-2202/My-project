#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameOverMenu.h"
#include "Player.h"
#include "Enermy.h"

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handlEvents();
	void update();
	void render();
	void clean();
	void resetGame();
	bool running() const;
	int score = 0;
	int enermySpeed = 4;
	TTF_Font* font = nullptr;
	GameOverMenu* gameOverMenu = nullptr;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* carTexture = nullptr;
	SDL_Texture* roadTexture = nullptr;
	Player* player = nullptr;
	Enermy* obstacles[3];
	bool isgameOver = false;
	bool isRunning = true;
};
