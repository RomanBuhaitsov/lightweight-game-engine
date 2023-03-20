#pragma once
#include "LGE_RenderWindow.h"
#include "Box2D/Box2D.h"
#include <memory>

class LGE_GameWindow : public LGE_RenderWindow {
private:
	int frameDelay;
	std::unique_ptr<b2World> world;
public:
	LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps);
	void gameLoop();
	b2World* getWorld();
};