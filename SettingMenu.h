#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class SettingMenu {
public:
	SettingMenu(SDL_Renderer* renderer, TTF_Font* font, int width, int height);
	void render(int volume);
	int handleEvent(SDL_Event& event, int& volume);
private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	int width;
	int height;
	SDL_Rect backbutton;
	SDL_Rect volumeDownButton, volumeUpButton;
	void renderText(const string& text, int x, int y, SDL_Color color);
};
