#include "Blob.h"

Blob::Blob(float x, float y, Game* game)
	: Enemy("res/Enemies/Blob/Blob.png", x, y, 1, 64, 21, game) {

}
void Blob::attack(TheGirl* girl, Angel* angel) {
	girl->loseLife(1);
}
void Blob::beShoot() {
	dead = true;
}
