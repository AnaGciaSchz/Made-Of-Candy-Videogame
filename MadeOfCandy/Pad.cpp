#include "Pad.h"

Pad::Pad(float x, float y, Game* game)
	: Actor("res/interface/pad.png", x, y, 100, 100,0,0, game) {

}

float Pad::getOrientationX(float clickX) {
	return clickX - x;
}

float Pad::getOrientationY(float clickY) {
	return clickY - y;
}

