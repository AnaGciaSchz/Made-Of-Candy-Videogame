#pragma once

#include "Enemy.h"

/**
* Class that represents an enemy that is a green thing
*/
class Blob : public Enemy
{
public:
	Blob(float x, float y, Game* game);
	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;
};

