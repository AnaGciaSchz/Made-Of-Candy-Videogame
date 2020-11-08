
#include "Background.h"

Background::Background(string filename, float x, float y, Game* game)
	: Actor(filename,x,y, WIDTH, HEIGHT,0,0, game) {

}

Background::Background(string filename, float x, float y, float vx, Game* game)
	: Actor(filename, x,y,WIDTH, HEIGHT,0,0, game) {

	this->vx = vx;
	if (vx != 0) {
		backgroundAux = new Background(filename, x + WIDTH, y, game);
	}
}

void Background::update() {
	if (vx != 0) {
		x = x + vx;

		if (x + getWidth() / 2 < 0) {

			x = WIDTH + getWidth() / 2;
		}

		if (x - getWidth() / 2 > WIDTH) {

			x = 0 - getWidth() / 2;
		}

	}
}

void Background::draw() {
	Actor::draw(); 

	if (backgroundAux != NULL) {

		if (x - getWidth() / 2 > 0) {

			backgroundAux->x = x - getWidth();
		}

		if (x + getWidth() / 2 < WIDTH) {

			backgroundAux->x = x + getWidth();
		}
		backgroundAux->draw();
	}

}





