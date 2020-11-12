#pragma once

#include "Movable.h"
#include "TheGirl.h"

class Recolectable : public Movable
{
public:
	Recolectable(string filename,int pathX, int pathY, Game* game);
	void update();
	void addLife(TheGirl* girl);
	void move();

};

