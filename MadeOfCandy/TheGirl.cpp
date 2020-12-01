#include "TheGirl.h"

TheGirl::TheGirl(int numberGirl,int timeY,float v, int pathX, int pathY, Game* game)
	: Actor("", 30, 46,pathX,pathY, game) {
	this->timeY = timeY;
	this->actualTimeY = timeY;

	this->lifes = 3;
	this->invulnerableTime = 0;
	
	this->v = v;

	this->stop = false;
	this->timeStop = 100;

	audioDamage = new Audio("res/music/effects/GirlDamage.wav", false);
	audioAddLife = new Audio("res/music/effects/GirlAddLife.wav", false);

	string animation = "";
	if (numberGirl == 1) {
		animation = "Anna";
	}
	else if (numberGirl == 2) {
		animation = "Emma";
	}
	else {
		animation = "Serenna";
	}
	aRight = new Animation("res/characters/TheGirl/" + animation + "/" + animation + "_right.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);

}

TheGirl::~TheGirl() {
	delete audioDamage;
	delete audioAddLife;
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

		if (invulnerableTime > 0) {
			invulnerableTime--;
		}
}

void TheGirl::draw() {
	if (invulnerableTime == 0) {
		aRight->draw(x, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			aRight->draw(x, y);
		}
	}
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
	audioAddLife->play();
	lifes+=life;
}

bool TheGirl::isInvulnerable() {
	return invulnerableTime > 0;
}

void TheGirl::loseLife(int damage) {
	if (invulnerableTime <= 0) {
		audioDamage->play();
		lifes -= damage;
		stop = true;
		invulnerableTime = 100;
	}
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

