#include "CelestialRay.h"

CelestialRay::CelestialRay(float pathX, float pathY,int time,bool left, Game* game) :
	Actor("", 27, 19,pathX,pathY, game) {
	time = time;
	actualTime = 0;
	this->left = left;
	 if (left) {//to choose an animation
		 animation = new Animation("res/world/CelestialRay/CelestialRay_left.png", getWidth(), getHeight(),
			 159, 23, 5, 5, true, game);
	 }
	 else {
		 animation = new Animation("res/world/CelestialRay/CelestialRay_right.png", getWidth(), getHeight(),
			 159, 23, 5, 5, true, game);
	 }
}

void CelestialRay::update() {
	animation->update();
	actualTime--;
	if (actualTime <= 0) {
		actualTime = time;
		if (left) {
			incrementX(-0.2);
		}
		else {
			incrementX(0.2);
		}
	}
}

void CelestialRay::draw() {
	animation->draw(x, y);

}

