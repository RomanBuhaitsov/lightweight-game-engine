#include "LGE_GameWindow.h"
#include "LGE_Entity.h"
#include "LGE_Components.h"
#include "LGE_PositionComponent.h"
#include "LGE_SpriteComponent.h"

LGE_GameWindow::LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps) : LGE_RenderWindow(title, width, height, fullscreen), frameDelay(fps) {};

void LGE_GameWindow::gameLoop() {
	SDL_Texture* t = loadTexture("textures/placeholder.png");
	SDL_Texture* spriteSheet = loadTexture("textures/crudewalk.png");
	LGE_Component::game = this;
	bool gameLoop = true;
	SDL_Event ev;
	Uint64 desiredFrameTime = 1000 / frameDelay;
	Uint64 frameStart, frameTime;
	LGE_Entity ent;
	ent.addComponent(new LGE_PositionComponent());
	ent.addComponent(new LGE_SpriteComponent(spriteSheet, 24, 28, 24, 28, 6, 100));
	do {
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				gameLoop = false;
				break;
			}
		}
		frameStart = SDL_GetTicks64();
		ent.update(frameStart);
		clear();
		ent.draw();
		present();
		frameTime = SDL_GetTicks64() - frameStart;
		if (desiredFrameTime > frameTime) {
			SDL_Delay(desiredFrameTime - frameTime);
		}
	} while (gameLoop);
}