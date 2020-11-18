#pragma once

#include "Enemy.h"


class Halloween : public Enemy
{
public:
	Halloween(int pathX, int pathY, Game* game);
	void update() override;
	void draw() override;

	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;

private:

	Animation* aDie;
	Animation* aIdle;
	Animation* animation;

	void getRandomHalloween();
};