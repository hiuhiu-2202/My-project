#pragma once
#include <SDL.h>

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

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* carTexture = nullptr;
	SDL_Texture* roadTexture = nullptr;
	SDL_Texture* enermyCar1Texture = nullptr;
	SDL_Texture* enermyCar2Texture = nullptr;
	
	SDL_Rect carRect;
	SDL_Rect enermyCar1Rect;
	SDL_Rect enermyCar2Rect;


	bool isRunning = true;
};
