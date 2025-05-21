#include "GameOverMenu.h"
#include <string>

using namespace std;


GameOverMenu::GameOverMenu(SDL_Renderer* r, TTF_Font* f, int w, int h)
	: renderer(r), font(f), screenHeight(h), screenWidth(w) {
	playAgainButton = { w / 2 - 100, 200, 200, 50 };
	exitButton = { w / 2 - 100, 270, 200, 50 };
}

void GameOverMenu::render(int score) {
	// nen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect overlay = { 0, 0, screenWidth, screenHeight };
	SDL_RenderFillRect(renderer, &overlay);

	// tieu de
	renderText("Game Over", screenWidth / 2 - 50, 150, { 255, 0, 0, 255 });

	// play again
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &playAgainButton);
	renderText("Play Again", playAgainButton.x + 20, playAgainButton.y + 10, { 255, 255, 255, 255 });

	// exit
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &exitButton);
	renderText("Exit", exitButton.x + 20, exitButton.y + 10, { 255, 255, 255, 255 });

	// diem
	string scoreText = "Score: " + to_string(score);
	renderText(scoreText, screenWidth / 2 - 50, 100, { 255, 0, 0, 255 });

}

int GameOverMenu::handleEvent(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int x = event.button.x;
		int y = event.button.y;

		if (x >= playAgainButton.x && x <= playAgainButton.x + playAgainButton.w &&
			y >= playAgainButton.y && y <= playAgainButton.y + playAgainButton.h) {

			return 1;

		}

		if (x >= exitButton.x && x <= exitButton.x + exitButton.w &&
			y >= exitButton.y && y <= exitButton.y + exitButton.h) {

			return 2;

		}

		
	}

	return 0;
}

void GameOverMenu::renderText(const string& text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect dstRect = { x, y, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}