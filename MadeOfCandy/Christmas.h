#pragma once

#include "Enemy.h"


class Christmas : public Enemy
{
public:
	Christmas(int pathX, int pathY, Game* game);
	void update() override;
	void draw() override;

	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;

private:

	Animation* aDie;
	Animation* aIdle;
	Animation* animation;

	void getRandomChristmas();
};