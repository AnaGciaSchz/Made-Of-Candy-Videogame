#pragma once

#include "Actor.h"

class Movable : public Actor
{
public:
	Movable(string filename, int width, int height, int pathX, int pathY, Game* game);
	void move(int incrementX, int incrementY);
	void moveObject(bool move);
	bool getIsMoving();

private:
	bool isBeingMoved;
};

