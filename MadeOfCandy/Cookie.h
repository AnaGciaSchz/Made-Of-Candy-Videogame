#pragma once

#include "Movable.h"
#include "TheGirl.h"

class Cookie : public Movable
{
public:
	Cookie(int pathX, int pathY, Game* game);
	void update();
	void addLife(TheGirl* girl);
	void move();

	static string getRandomCookie();

};

