#include "SingletonGame.h"
#undef main  //To quit the "main" method in SDL_main

/**
* Method to execute the game
*/
int main() {
	SingletonGame* sg = new SingletonGame();
	sg->getInstance();
	return 0;
}
