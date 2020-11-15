#pragma once

#include "Layer.h"
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

private:
	Background* backgroundMenu;
	Background* backgroundEdit;
	Actor* playButton;
	Actor* editButton;
	Actor* exitButton;
	Actor* backButton;
	bool controlContinue;
	bool editMode;
};


