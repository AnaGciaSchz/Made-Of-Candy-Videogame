
#pragma once

#include "Actor.h"

/**
* Class that represents the Background
*/
class Background : public Actor
{
public:
	Background(string filename, float x, float y, Game* game);

	Background(string filename, float x, float y, float vx, Game* game);
	void draw() override;
	void update();

private:
	Background* backgroundAux = nullptr;
	int vx;


};

