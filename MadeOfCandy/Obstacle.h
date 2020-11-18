#pragma once

#include "Enemy.h"


/**
* Class that represents an enemy that is a obstacle
*/
class Obstacle : public Enemy
{
public:
	Obstacle(string filename, int widthImage, int heightImage, int pathX, int pathY, Game* game);
	void update() override;

	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;

};

