#pragma once

#include "Movable.h"
#include "TheGirl.h"
#include "Angel.h"

#include "Animation.h" 

/**
* Class that represent an enemy
*/
class Enemy : public Movable
{
public:
	Enemy(string filename, int damage, int width, int height,int pathX, int pathY, Game* game);
	virtual void update() {};
	virtual void attack(TheGirl* girl, Angel* angel) {};
	virtual void beShoot() {};
	bool isDead();
	int getDamage();
	void move();

	bool beDeleted();

protected:
	int damage;
	bool dead;

	bool canBeDeleted;


};

