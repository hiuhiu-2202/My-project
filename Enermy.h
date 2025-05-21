#pragma once
#include <SDL.h>
#include <vector>

using namespace std;

class Enermy {
public:
	Enermy(SDL_Texture* texture, int x, int y, int w, int h);
	void update();
	void render(SDL_Renderer* renderer);
	SDL_Rect getRect() const;
	void resetPosition(const std::vector<Enermy*>& others);
	void setPosition(int x, int y) {
		rect.x = x;
		rect.y = y;
	}
	int enermySpeed = 4;
	void setSpeed(int s) {
		enermySpeed = s;
	}

private:
	SDL_Rect rect;
	SDL_Texture* texture;
};