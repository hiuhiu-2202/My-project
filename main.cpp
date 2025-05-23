#include "Game.h"
#include "GameOverMenu.h"

Game* game = NULL;

int main(int argc, char* argv[]) {
	game = new Game();
	
	game->init("Racing Car", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running()) {
		game->handlEvents();
		game->update();
		game->render();
		SDL_Delay(16);
	}

	game->clean();
	delete game;
	
	return 0;
}