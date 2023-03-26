#pragma once
#include "LGE_RenderWindow.h"
#include "LGE_TextureManager.h"
#include "Box2D/Box2D.h"
#include <memory>
#include <list>

class LGE_Entity;

class LGE_GameWindow : public LGE_RenderWindow {
private:
	int frameDelay;
	std::unique_ptr<b2World> world;
	std::list<LGE_Entity*> removeEntities;
	LGE_TextureManager textMgr;
	std::list<SDL_Event> recentEvents;
public:
	LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps);
	void gameLoop();
	b2World* getWorld();
	void removeEntity(LGE_Entity* ent);
	const std::list<SDL_Event>& getRecentEvents() const;
};