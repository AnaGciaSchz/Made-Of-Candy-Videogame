#pragma once

#include "Actor.h"
#include "TheGirl.h"
#include "Angel.h"

#include "Animation.h" 

/**
* Class that represent an enemy
*/
class Enemy : public Actor
{
public:
	Enemy(string filename, int damage, int width, int height,int pathX, int pathY, Game* game);
	virtual void update() {};
	virtual void attack(TheGirl* girl, Angel* angel) {};
	virtual void beShoot() {};
	bool isDead();
	int getDamage();
	void move();

protected:
	int damage;
	bool dead;


};

