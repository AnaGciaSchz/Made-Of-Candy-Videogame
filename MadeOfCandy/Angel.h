#pragma once

#include "Actor.h"

/**
* Class that represents the Angel (the player)
*/
class Angel : public Actor
{
public:
	Angel(float x, float y, Game* game);

	void update();
//	void shoot(bool shoot);
	//void moveElement(bool move);
	void moveX(float axis);
	void moveY(float axis);
};
