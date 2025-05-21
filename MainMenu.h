#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameOverMenu.h"
#include <string>

using namespace std;

class MainMenu {
public:
	MainMenu(SDL_Renderer* renderer, TTF_Font* font, int width, int height);
	void render();
	int handleEvent(SDL_Event& event);
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	int width, height;
	SDL_Rect playButton, settingButton, exitButton;
	void renderText(const string& text, int x, int y, SDL_Color color);
};
