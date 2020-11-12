#include "TheGirl.h"

TheGirl::TheGirl(int timeY,float v, int pathX, int pathY, Game* game)
	: Actor("", 30, 46,pathX,pathY, game) {
	this->timeY = timeY;
	this->actualTimeY = timeY;

	this->lifes = 3;
	
	this->v = v;

	this->stop = false;
	this->timeStop = 100;

	audioDamage = new Audio("res/music/effects/GirlDamage.wav", false);

	aRight = new Animation("res/characters/TheGirl/Anna/Anna_right.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);

}

void TheGirl::update() {
	aRight->update();
	actualTimeY--;
	if (actualTimeY <= 0) {
		actualTimeY = timeY;
		if (!stop) {
			if (rand() > RAND_MAX / 2) {
				moveY();
			}
		}
	}
		if(!stop){
			this->x = x + v;
			if (x > getPathX() * PATH_X) {
				pathX++;
			}
		}
		else {
			timeStop--;
			if (timeStop <= 0) {
				timeStop = 50;
				stop = false;
			}
		}
}

void TheGirl::draw() {
	aRight->draw(x, y);
}

void TheGirl::moveY() {
	int value;
	if (getPathY()<=1){ 
		incrementY(1);
	}
	else if (getPathY() >= PATHS_Y) {
		incrementY(-1);
	}
	else {
		if (rand() > RAND_MAX / 2) {
			incrementY(1);
		}
		else {
			incrementY(-1);
		}
	}

}
void TheGirl::addLife(int life) {
	lifes+=life;
}

void TheGirl::loseLife(int damage) {
	audioDamage->play();
	lifes -= damage;
	stop = true;
}

int TheGirl::getLife() {
	return lifes;
}

bool TheGirl::isDead() {
	if (lifes <= 0) {
		return true;
	}
	return false;
}

