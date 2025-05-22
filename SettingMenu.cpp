#include "SettingMenu.h"

using namespace std;

SettingMenu::SettingMenu(SDL_Renderer* r, TTF_Font* f, int w, int h)
	: renderer(r), font(f), width(w), height(h) {
	backbutton = { w / 2 - 60, 350, 120, 40 };
	volumeDownButton = { w / 2 - 80, 220, 40, 50 };
	volumeUpButton = { w / 2 + 40, 220, 40, 40 };
}

void SettingMenu::render(int volume) {
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	renderText("Setting", width / 2 - 60, 120, { 255, 215, 0, 255 });
	renderText("Music Volume", width / 2 - 80, 180, { 255, 255, 255, 255 });

	// volume down button
	SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
	SDL_RenderFillRect(renderer, &volumeDownButton);
	renderText("-", volumeDownButton.x + 12, volumeDownButton.y + 5, { 255, 255, 255, 255 });

	// volume up button
	SDL_SetRenderDrawColor(renderer, 100, 255, 100, 255);
	SDL_RenderFillRect(renderer, &volumeUpButton);
	renderText("+", volumeUpButton.x + 12, volumeUpButton.y + 5, { 255, 255, 255, 255 });

	// volume value
	renderText(to_string(volume), width / 2 - 10, 225, { 255, 255, 255, 255 });

	// back button
	SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
	SDL_RenderFillRect(renderer, &backbutton);
	renderText("Back", backbutton.x + 25, backbutton.y + 8, { 255, 255, 255, 255 });
}

int SettingMenu::handleEvent(SDL_Event& event, int& volume) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x = event.button.x;
		int y = event.button.y;
		if (x >= backbutton.x && x <= backbutton.x + backbutton.w &&
			y >= backbutton.y && y <= backbutton.y + backbutton.h) {
			return 1;
		}
		else if (x >= volumeDownButton.x && x <= volumeDownButton.x + volumeDownButton.w &&
			y >= volumeDownButton.y && y <= volumeDownButton.y + volumeDownButton.h) {
			if (volume > 0) {
				volume -= 8;
			}
			if (volume < 0) {
				volume = 0;
			}

			return 0; 
		}
		else if (x >= volumeUpButton.x && x <= volumeUpButton.x + volumeUpButton.w &&
			y >= volumeUpButton.y && y <= volumeUpButton.y + volumeUpButton.h) {
			if (volume < 128) {
				volume += 8;
			}
			if (volume > 128) {
				volume = 128;
			}
			return 0;
		}
	}
	return 0;
}

void SettingMenu::renderText(const string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect dstrect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}