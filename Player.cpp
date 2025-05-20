#include "Player.h";

Player::Player(SDL_Texture* tex, int x, int y, int w, int h) : texture(tex) {
	rect = { 310, 400, 52, 111 };
}

bool movingRight = false;
bool movingLeft = false;
bool movingUp = false;
bool movingDown = false;

void Player::handleInput(SDL_Event& event) {
	switch (event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			movingUp = true;
			break;
		case SDLK_DOWN:
			movingDown = true;
			break;
		case SDLK_LEFT:
			movingLeft = true;
			break;
		case SDLK_RIGHT:
			movingRight = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			movingUp = false;
			break;
		case SDLK_DOWN:
			movingDown = false;
			break;
		case SDLK_LEFT:
			movingLeft = false;
			break;
		case SDLK_RIGHT:
			movingRight = false;
			break;
		}
		break;
	}
}


void Player::update() {
	float dx = 0, dy = 0;
	float speed = 6.0f;

	// Di chuy?n xe
	if (movingUp) {
		dy -= 1;
	}
	if (movingDown) {
		dy += 1;
	}
	if (movingLeft) {
		dx -= 1;
	}
	if (movingRight) {
		dx += 1;
	}
	if (dx != 0 && dy != 0) {
		dx *= 0.7071f;
		dy *= 0.7071f;
	}

	rect.x += dx * speed;
	rect.y += dy * speed;

	//  Gioi han xe trong khoang nhat dinh
	if (rect.x < 150) rect.x = 150;
	if (rect.y < 0) rect.y = 0;
	if (rect.x + rect.w > 650) rect.x = 650 - rect.w;
	if (rect.y + rect.h > 600) rect.y = 600 - rect.h;
}

void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Rect Player::getRect() const {
	return rect;
}

void Player::reset() {
	rect.x = 310;
	rect.y = 400;
}
