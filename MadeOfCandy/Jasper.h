#pragma once

#include "Enemy.h"

class Jasper : public Enemy
{
public:
	Jasper(int pathX, int pathY, Game* game);
	void update() override;
	void draw() override;

	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;

private:

	Animation* aDie;
	Animation* aIdle;
	Animation* animation;

};

