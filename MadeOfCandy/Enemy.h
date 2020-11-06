#pragma once

#include "Actor.h"
#include "TheGirl.h"
#include "Angel.h"

/**
* Class that represent an enemy
*/
class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y,int damage, int width, int height, Game* game);
	void update();
	virtual void attack(TheGirl* girl, Angel* angel) {};
	virtual void beShoot() {};
	bool isDead();
	int getDamage();
	void move(int x, int y);

protected:
	int damage;
	bool dead;

};

