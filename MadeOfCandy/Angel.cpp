#include "Angel.h"

Angel::Angel(float pathX, float pathY, Game* game)
	: Actor("res/characters/Angel/Robbie/Robbie.png", 30, 46,pathX, pathY, game) {


	canShoot = true;
	ray = nullptr;


	isMoving = false;
	movedElement = nullptr;

	audioRay = new Audio("res/music/effects/Ray.wav", false);

	aLeft= new Animation("res/characters/Angel/Robbie/Robbie_left.png", getWidth(), getHeight(),
		96, 50, 6, 3, true,game);

	aLeftUp= new Animation("res/characters/Angel/Robbie/Robbie_leftUp.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);

	aRight = new Animation("res/characters/Angel/Robbie/Robbie_right.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);
	aRightUp = new Animation("res/characters/Angel/Robbie/Robbie_rightUp.png", getWidth(), getHeight(),
		96, 50, 6, 3, true, game);
	animation = aLeft;
}

void Angel::update() {
	animation->update();

	if (ray != nullptr) {
		ray->update();
		deleteRay();
	}
}

void Angel::moveX(float axis) {
	if (axis > 0 && getPathX() == PATHS_X-1) {
		
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

void Angel::moveY(float axis) {
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

		if(isMoving) {
			movedElement->move(0, axis);
		}
	}
	
}

void Angel::shoot(bool shoot) {
	if (shoot && canShoot) {
		audioRay->play();
		cantShoot();
		if (getOrientation() == -1) {
			ray = new CelestialRay(getPathX(), getPathY(), 30,true, getGame());
		}
		else {
			ray = new CelestialRay(getPathX(), getPathY(), 30,false, getGame());
		}
	}
}

CelestialRay* Angel::getRay() {
	return ray;
}

void Angel::cantShoot() {
	canShoot = false;
}

void Angel::deleteRay() {
	if (ray->isInRender()==false) {
		delete ray;
		ray = nullptr;
	}
}

void Angel::moveElement(bool move, list<Movable*> movables) {
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
	int x = 100;
	for (auto const& movable : movables) {
		if(isOverlap(movable) && abs(movable->getX()-getX())<x){
				movedElement = movable;
				x = abs(movable->getX() - getX());
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



