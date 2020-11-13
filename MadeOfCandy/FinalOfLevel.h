#pragma once

#include "Actor.h"

class FinalOfLevel : public Actor
{
public:
	FinalOfLevel(int pathX, int pathY, Game* game);
	void update();
	void endOfLevel();
};

