#include "LGE_GameWindow.h"

int main(int argc, char** argv) {
	LGE_GameWindow gameWindow("LGE Test", 1280, 720, false, 60);
	gameWindow.gameLoop();
	return 0;
}