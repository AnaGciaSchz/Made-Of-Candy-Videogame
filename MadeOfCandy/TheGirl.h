#pragma once

#include "Actor.h"
#include "Audio.h"

/**
	* Class that represents the Girl that has to be protected
	*/
class TheGirl : public Actor
{
public:
	TheGirl( int timeY, float v, int pathX, int pathY, Game* game);

	void update();
	void moveY();

	void loseLife(int damage);
	int getLife();
	bool isDead();

private:
	//time to wait until the girl moves in Y
	int timeY;
	int actualTimeY;

	/**
	* Lifes of the girl
	*/
	int lifes;

	/**
	* velocity of the girl
	*/
	float v;

	Audio* audioDamage;

	bool stop;
	int timeStop;
};

