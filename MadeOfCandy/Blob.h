#pragma once

#include "Enemy.h"

/**
* Class that represents an enemy that is a green thing
*/
class Blob : public Enemy
{
public:
	Blob(int pathX, int pathY, Game* game);
	void update() override;
	void draw() override;

	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;

private:

	Animation* aDie;
	Animation* aIdle;
	Animation* animation;
};

