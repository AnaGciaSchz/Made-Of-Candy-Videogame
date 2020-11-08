#pragma once

#include "Actor.h"

/**
	* Class that represents the Girl that has to be protected
	*/
class TheGirl : public Actor
{
public:
	TheGirl( int timeY, int timeX, int v, int pathX, int pathY, Game* game);

	void update();
	void moveY();

	void loseLife(int damage);
	int getLife();
	bool isDead();

private:
	//time to wait until the girl moves in Y
	int timeY;
	int actualTimeY;

	//time to wait until the girl moves in X
	int timeX;
	int actualTimeX;

	/**
	* Lifes of the girl
	*/
	int lifes;

	/**
	* velocity of the girl
	*/
	int v;
};

