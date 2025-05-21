#include "MainMenu.h"


MainMenu::MainMenu(SDL_Renderer* r, TTF_Font* f, int w, int h)
	: renderer(r), font(f), width(w), height(h) {
	playButton = { w / 2 - 100, 200, 200, 50 };
	settingButton = { w / 2 - 100, 270, 200, 50 };
	exitButton = { w / 2 - 100, 340, 200, 50 };
}

void MainMenu::render() {
	// background
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	// tieu de
	renderText("Racing Car", width / 2 - 120, 120, { 255, 215, 0, 255 });

	// play button
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
	SDL_RenderFillRect(renderer, &playButton);
	renderText("Play", playButton.x + 60, playButton.y + 10, { 255, 255, 255, 255 });

	// setting button
	SDL_SetRenderDrawColor(renderer, 0, 120, 255, 255);
	SDL_RenderFillRect(renderer, &settingButton);
	renderText("Settings", settingButton.x + 45, settingButton.y + 10, { 255, 255, 255, 255 });

	// exit button
	SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
	SDL_RenderFillRect(renderer, &exitButton);
	renderText("Exit", exitButton.x + 65, exitButton.y + 10, { 255, 255, 255, 255 });
}

int MainMenu::handleEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x = event.button.x;
		int y = event.button.y;
		if (x >= playButton.x && x <= playButton.x + playButton.w &&
			y >= playButton.y && y <= playButton.y + playButton.h) {
			return 1; // Play
		}
		if (x >= settingButton.x && x <= settingButton.x + settingButton.w &&
			y >= settingButton.y && y <= settingButton.y + settingButton.h) {
			return 2; // Settings
		}
		if (x >= exitButton.x && x <= exitButton.x + exitButton.w &&
			y >= exitButton.y && y <= exitButton.y + exitButton.h) {
			return 3; // Exit
		}
	}
	return 0; 
}

void MainMenu::renderText(const string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dstRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}