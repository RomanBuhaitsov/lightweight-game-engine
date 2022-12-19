#pragma once
#include "LGE_RenderWindow.h"

class LGE_GameWindow : public LGE_RenderWindow {
private:
	int frameDelay;
public:
	LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps);
	void gameLoop();
};