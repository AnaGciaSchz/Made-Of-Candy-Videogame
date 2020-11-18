#include "Angel.h"

Angel::Angel(int numberAngel,float pathX, float pathY, Game* game)
	: Actor("res/characters/Angel/Robbie/Robbie.png", 30, 46,pathX, pathY, game) {


	canShoot = true;
	ray = nullptr;


	isMoving = false;
	movedElement = nullptr;

	audioRay = new Audio("res/music/effects/Ray.wav", false);
	string animationS = "";

	if (numberAngel == 1) {
		animationS = "Robbie";
	}
	else if (numberAngel == 2) {
		animationS = "Max";
	}
	else {
		animationS = "Kentin";
	}

	aLeft= new Animation("res/characters/Angel/"+ animationS +"/"+ animationS +"_left.png", getWidth(), getHeight(),
		96, 50, 6, 3, true,game);

	aLeftUp= new Animation("res/characters/Angel/"+ animationS +"/" + animationS + "_leftUp.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);

	aRight = new Animation("res/characters/Angel/" + animationS + "/" + animationS + "_right.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);
	aRightUp = new Animation("res/characters/Angel/" + animationS + "/" + animationS + "_rightUp.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);
	animation = aLeft;

	paralyzedAngel = false;
	paralizedTime = 60;
}

void Angel::update() {
	if (!paralyzedAngel) {
		animation->update();

		if (ray != nullptr) {
			ray->update();
			deleteRay();
		}
	}
	else {
		if (paralizedTime != 0) {
			paralizedTime--;
		}
		else {
			paralizedTime = 60;
			paralyzedAngel = false;
		}
	}
}

void Angel::moveX(float axis) {
	if (!paralyzedAngel) {
		if (axis > 0 && getPathX() == PATHS_X - 1) {

		}
		else if (axis < 0 && getPathX() == 1) {

		}
		else {
			if (axis < 0) {
				animation = aLeft;
			}
			else {
				animation = aRight;
			}

			incrementX(axis);
			if (isMoving) {
				movedElement->move(axis, 0);
			}
		}
	}
	
}

void Angel::moveY(float axis) {
	if (!paralyzedAngel) {
		if (axis > 0 && getPathY() == PATHS_Y) {
		}
		else if (axis < 0 && getPathY() == 1) {
		}
		else {
			if (axis < 0) {
				if (getOrientation() == 1) {
					animation = aRightUp;
				}
				else {
					animation = aLeftUp;
				}
			}
			else {
				if (getOrientation() == 1) {
					animation = aRight;
				}
				else {
					animation = aLeft;
				}

			}
			incrementY(axis);

			if (isMoving) {
				movedElement->move(0, axis);
			}
		}
	}
	
}

void Angel::paralyzed() {
	paralyzedAngel = true;
}

void Angel::shoot(bool shoot) {
	if (!paralyzedAngel) {
		if (shoot && canShoot) {
			audioRay->play();
			cantShoot();
			if (getOrientation() == -1) {
				ray = new CelestialRay(getPathX(), getPathY(), 30, true, getGame());
			}
			else {
				ray = new CelestialRay(getPathX(), getPathY(), 30, false, getGame());
			}
		}
	}
}

CelestialRay* Angel::getRay() {
	return ray;
}

void Angel::cantShoot() {
	if (!paralyzedAngel) {
		canShoot = false;
	}
}

bool Angel::getCanShoot() {
	return canShoot;
}

void Angel::deleteRay() {
	if (ray->isInRender()==false) {
		delete ray;
		ray = nullptr;
	}
}

bool Angel::moveElement(bool move, list<Movable*> movables) {
	if (!paralyzedAngel) {
		if (move && !isMoving) {
			findMovedElement(movables);
		}

		else if (move && isMoving) {
			if (emptySlotForElement(movables)) {
				isMoving = false;
				movedElement->moveObject(false);
				movedElement = nullptr;
			}
		}
	}
	return isMoving;
}

bool Angel::emptySlotForElement(list<Movable*> movables) {
	for (auto const& movable : movables) {
			if (movedElement->isOverlap(movable) && movable != movedElement) {
				return false;
			}
	}
	return true;
}

int Angel::getOrientation() {
	if (animation == aRight || animation == aRightUp) {
		return 1;
	}
	return -1;
}

void Angel::findMovedElement(list<Movable*> movables) {
	for (auto const& movable : movables) {
		if(isOverlap(movable)){
				movedElement = movable;
				isMoving = true;
				break;
		}

	}

	if (isMoving) {
		movedElement->moveObject(true);
	}
}

void Angel::draw() {
	animation->draw(x, y);
	if (ray != nullptr) {
		ray->draw();
	}

}



