#pragma once

#include "Actor.h"
#include "Audio.h"
#include "Animation.h" 

/**
	* Class that represents the Girl that has to be protected
	*/
class TheGirl : public Actor
{
public:
	TheGirl(int numberGirl, int timeY, float v, int pathX, int pathY, Game* game);

	void update();
	void draw() override; 
	void moveY();

	void loseLife(int damage);
	void addLife(int life);
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

	int invulnerableTime;

	/**
	* velocity of the girl
	*/
	float v;

	Animation* aRight;

	Audio* audioDamage;
	Audio* audioAddLife;

	bool stop;
	int timeStop;
};

