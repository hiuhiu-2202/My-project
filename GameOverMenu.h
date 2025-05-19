#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class GameOverMenu {
public:
	GameOverMenu(SDL_Renderer* renderer, TTF_Font* font, int width, int height);


	void render(int score);

	int handleEvent(SDL_Event& event);

private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	int screenWidth, screenHeight;

	SDL_Rect playAgainButton;
	SDL_Rect exitButton;

	void renderText(const string& text, int x, int y, SDL_Color color);
};