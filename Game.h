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
	bool running() { return isRunning; }

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* carTexture;
	SDL_Texture* roadTexture;
	SDL_Rect carRect, roadRect;
	bool isRunning;
};
