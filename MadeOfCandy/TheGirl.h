#pragma once

#include "Actor.h"

/**
	* Class that represents the Girl that has to be protected
	*/
class TheGirl : public Actor
{
public:
	TheGirl(float x, float y, int time, Game* game);

	void update();
	void moveY();

private:
	//time to wait until the girl moves
	int time;
	int actualTime;
};

