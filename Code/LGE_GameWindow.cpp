#include "LGE_GameWindow.h"
#include "LGE_Entity.h"
#include "LGE_Components.h"
#include "LGE_PositionComponent.h"
#include "LGE_SpriteComponent.h"
#include "LGE_PhysicsComponent.h"
#include "LGE_SpritePhysicsHandler.h"
#include "LGE_EntityContact.h"
#include "LGE_DebugDraw.h"
#include "LGE_InputOutput.h"
#include "LGE_TextureManager.h"
#include <set>

LGE_GameWindow::LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps) : LGE_RenderWindow(title, width, height, fullscreen), frameDelay(fps), textMgr(this) {
	b2Vec2 gravity(0.0f, 10.0f);
	world = std::make_unique<b2World>(gravity);
}

void LGE_GameWindow::removeEntity(LGE_Entity* ent) {
	removeEntities.push_back(ent);
}

const std::list<SDL_Event>& LGE_GameWindow::getRecentEvents() const
{
	return recentEvents;
}

LGE_Entity* makeEntityFromIndex(int index, SDL_Event& ev, const LGE_TextureManager & textMgr) {
	if (index == 0) {
		LGE_Entity* newTile = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		newTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32, 32, 32, 0.8f)));
		newTile->addComponent(new LGE_SpriteComponent(textMgr["grasstile.png"], 32, 32, 64, 64));
		newTile->addComponent(new LGE_SpritePhysicsHandler());
		return newTile;
	}
	else if (index == 1) {
		LGE_Entity* newSlopeTile = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		//newSlopeTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32 - 1, 32, 32, 0.8f)));
		newSlopeTile->addComponent(new LGE_PhysicsComponent(
			LGE_PhysicsComponent::RightTriangleTileBody(
				ev.button.x / 32 * 32 - 1,
				ev.button.y / 32 * 32,
				32, 32, 0.8f)));
		newSlopeTile->addComponent(new LGE_SpriteComponent(textMgr["grass_slope_b.png"], 32, 32, 64, 64, 0, -16));
		newSlopeTile->addComponent(new LGE_SpritePhysicsHandler());
		return newSlopeTile;
	}
	else if (index == 2) {
		LGE_Entity* dynamicBox = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		dynamicBox->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(
			ev.button.x / 32 * 32 - 1,
			ev.button.y / 32 * 32,
			32, 32, 0.8f, 0.1f, true)));
		dynamicBox->addComponent(new LGE_SpriteComponent(textMgr["wooden_box.png"], 32, 32, 32, 32, 0, 0));
		dynamicBox->addComponent(new LGE_SpritePhysicsHandler());
		return dynamicBox;
	}
	else if (index == 3) {
		LGE_Entity* coinEntity = new LGE_Entity(LGE_EntityType::ET_COLLECTIBLE);
		coinEntity->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::CharacterBody(
			ev.button.x / 32 * 32 - 1,
			ev.button.y / 32 * 32,
			32 / 2, 32 / 2, 0.1f),
			[](LGE_Entity* other)->bool{
				if (other->getType() == LGE_EntityType::ET_PLAYER) {
					return true;
				}
				return false;
			}));
		coinEntity->addComponent(new LGE_SpriteComponent(textMgr["coin.png"], 32 / 2, 32 / 2, 32, 32, { 4 }, 100, 32 / 4, 0));
		coinEntity->addComponent(new LGE_SpritePhysicsHandler());
		return coinEntity;
	}
	return nullptr;
}

void LGE_GameWindow::gameLoop() {
	SDL_Texture* background = textMgr["background.png"];
	SDL_Rect bg_src, bg_dest;
	bg_src.x = bg_src.y = 0;
	bg_src.w = 1920;
	bg_src.h = 1080;
	bg_dest.x = bg_dest.y = 0;
	bg_dest.w = 1280;
	bg_dest.h = 720;
	LGE_Component::game = this;
	bool gameLoop = true;
	SDL_Event ev;
	const Uint64 desiredFrameTime = 1000 / frameDelay;
	Uint64 frameStart, frameTime;
	const float timeStep = 1.0f / (float)frameDelay;
	const int32 velocityIterations = 8, positionIterations = 3;
	LGE_Entity *ent = new LGE_Entity(LGE_EntityType::ET_PLAYER);
	SDLDebugDraw debugDraw(renderer);
	debugDraw.SetFlags(b2Draw::e_shapeBit);
	world->SetDebugDraw(&debugDraw);
	int tileIndex = 0;
	ent->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::CharacterBody(0, 0, 24, 24, 0.1f)));
	ent->addComponent(new LGE_SpriteComponent(textMgr["crudewalk.png"], 24, 28, 24, 28, {6, 6}, 100, 4));
	ent->addComponent(new LGE_SpritePhysicsHandler(LGE_PlayerMovementHandler));
	std::set<LGE_Entity*> entities;
	for (int i = 0; i < 16; ++i) {
		LGE_Entity* newTile = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		newTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(i * 32 - 1, 448, 32, 32, 0.8f)));
		newTile->addComponent(new LGE_SpriteComponent(textMgr["grasstile.png"], 32, 32, 64, 64, 0, 0));
		newTile->addComponent(new LGE_SpritePhysicsHandler());
		entities.insert(newTile);
	}
	entities.insert(ent);	
	LGE_ContactListener contact(this);
	world->SetContactListener(&contact);
	do {
		while (SDL_PollEvent(&ev)) {
			recentEvents.push_back(ev);
			switch (ev.type) {
				case SDL_QUIT:
					gameLoop = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					switch (ev.button.button) {
						case SDL_BUTTON_LEFT:
						{
							LGE_Log << "Tile Index: " << tileIndex << '\n';
							LGE_Entity* gent = makeEntityFromIndex(tileIndex, ev, textMgr);
							entities.insert(gent);
							break;
						}
						case SDL_BUTTON_RIGHT:
							if (++tileIndex == 4) {
								tileIndex = 0;
							}
							LGE_Log << "Tile Index: " << tileIndex << '\n';
							break;
					}
					break;
				}
			}
		}
		frameStart = SDL_GetTicks64();
		clear();
		renderTexture(background, bg_src, bg_dest);
		world->Step(timeStep, velocityIterations, positionIterations);
		for (LGE_Entity* gent : removeEntities) {
			gent->destroy();
			entities.erase(gent);
			delete gent;
		}
		removeEntities.clear();
		for (LGE_Entity* gent : entities) {
			if (gent != nullptr) {
				gent->update(frameStart);
				gent->draw();
			}
		}
		recentEvents.clear();
		//world->DebugDraw();
		present();
		frameTime = SDL_GetTicks64() - frameStart;
		if (desiredFrameTime > frameTime) {
			SDL_Delay(desiredFrameTime - frameTime);
		}
	} while (gameLoop);
	for (LGE_Entity* gent : entities) {
		if (gent != nullptr) {
			delete gent;
		}
	}
	entities.clear();
}

b2World* LGE_GameWindow::getWorld()
{
	return world.get();
}