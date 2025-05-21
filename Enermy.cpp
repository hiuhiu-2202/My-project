#include "Enermy.h"
#include <cstdlib>
#include <SDL.h>
#include <vector>

using namespace std;

const int NUM_OBSTCLES = 3;
const int lanePositions[] = { 190, 310, 430, 550 };
bool isgameOver = false;

Enermy::Enermy(SDL_Texture* tex, int x, int y, int w, int h) : texture(tex) {
	
		int lane = rand() % 4;
		rect.x = lanePositions[lane];
		rect.y = -(rand() % 100 + 300);
		rect.w = h;
		rect.h = w;
	
}

void Enermy::update() {
	rect.y += enermySpeed;
	if (rect.y > 600) {
		rect.y = -100;
		int lane = rand() % 4;
		rect.x = lanePositions[lane];
	}
}

void Enermy::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Rect Enermy::getRect() const {
	return rect;
}

void Enermy::resetPosition(const vector<Enermy*>& others) {
	int newLane, newY;
	bool overlap;
	do {
		overlap = false;
		newLane = rand() % 4;
		newY = -(rand() % 100 + 200);
		for (const auto& other : others) {
			if (other == this) continue;
			if (other->getRect().x == lanePositions[newLane] &&
				abs(other->getRect().y - newY) < 200) {
				overlap = true;
				break;
			}
		}
	} while (overlap);

	rect.x = lanePositions[newLane];
	rect.y = newY;

	enermySpeed = 4;

	isgameOver = false;

}