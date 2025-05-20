#pragma once
#include <SDL.h>

class Player {
public:
	Player(SDL_Texture* texture, int x, int y, int w, int h);
	void update();
	void handleInput(SDL_Event& event);
	void render(SDL_Renderer* renderer);
	SDL_Rect getRect() const;

	void reset();

private:
	SDL_Rect rect;
	SDL_Texture* texture;

};