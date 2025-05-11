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
	
	SDL_Rect carRect;
	bool isRunning = true;
};
