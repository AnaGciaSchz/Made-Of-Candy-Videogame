#pragma once

#include "Enemy.h"

class BlobMinion : public Enemy
{
public:
	BlobMinion(int pathX, int pathY, Game* game);
	void update() override;
	void draw() override;

	void attack(TheGirl* girl, Angel* angel) override;
	void beShoot() override;

private:

	Animation* aIdle;
};
