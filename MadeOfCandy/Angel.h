#pragma once

#include "Movable.h"
#include "CelestialRay.h"
#include "Audio.h"
#include "Animation.h" 

#include <list>

/**
* Class that represents the Angel (the player)
*/
class Angel : public Actor
{
public:
	Angel(int numberAngel,float pathX, float pathY, Game* game);

	void update();
	void draw() override;
	void shoot(bool shoot);
	bool moveElement(bool move, list<Movable*> movables);
	void moveX(float axis);
	void moveY(float axis);
	int getOrientation();
	bool emptySlotForElement(list<Movable*> movables);
	void cantShoot();
	void deleteRay();

	CelestialRay* getRay();

private:
	bool canShoot;
	CelestialRay* ray;

	bool isMoving;
	Movable* movedElement;
	void findMovedElement(list<Movable*> movables);

	Animation* aLeftUp;
	Animation* aRightUp;
	Animation* aLeft;
	Animation* aRight;
	Animation* animation;

	Audio* audioRay;
};
