#pragma once

#include "Actor.h"
#include "Animation.h" 

/**
* Class that represents the celestial ray that the angel can use 1 time in each level
*/
class CelestialRay : public Actor
{
public:
	CelestialRay(float pathX, float pathY,int time,bool left, Game* game);
	void update();
	void draw() override;

private:
	int time;
	int actualTime;
	bool left; //to see direction

	Animation* animation;
};


