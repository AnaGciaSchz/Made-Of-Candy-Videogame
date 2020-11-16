#pragma once

#include "Layer.h"
#include "GameLayer.h"
class GameLayer;
#include "Actor.h"
#include "Background.h"

class MenuLayer : public Layer
{
public:
	MenuLayer(Game* game);
	void init() override;
	void draw() override;

	void processControls() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);

	void selectGirl(int numberGirl);
	void selectAngel(int numberAngel);

private:
	Background* backgroundMenu;
	Background* backgroundEdit;
	Actor* playButton;
	Actor* editButton;
	Actor* exitButton;
	Actor* backButton;

	Actor* editGirl1;
	Actor* editGirl2;
	Actor* editGirl3;
	Actor* editAngel1;
	Actor* editAngel2;
	Actor* editAngel3;

	GameLayer* gameLayer;


	bool controlContinue;
	bool editMode;
};


