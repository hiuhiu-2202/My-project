#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handlEvents();
	void update();
	void render();
	void clean();
	bool running() const;
	int score = 0;
	TTF_Font* font = nullptr;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* carTexture = nullptr;
	SDL_Texture* roadTexture = nullptr;
	SDL_Texture* enermyCar1Texture = nullptr;
	SDL_Texture* enermyCar2Texture = nullptr;
	SDL_Texture* enermyCar3Texture = nullptr;
	
	
	SDL_Rect carRect;
	SDL_Rect enermyCar1Rect;
	SDL_Rect enermyCar2Rect;
	SDL_Rect enermyCar3Rect;
	


	bool isRunning = true;
};
