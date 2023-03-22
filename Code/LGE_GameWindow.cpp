#include "LGE_GameWindow.h"
#include "LGE_Entity.h"
#include "LGE_Components.h"
#include "LGE_PositionComponent.h"
#include "LGE_SpriteComponent.h"
#include "LGE_PhysicsComponent.h"
#include "LGE_EntityContact.h"
#include "LGE_DebugDraw.h"
#include "LGE_InputOutput.h"
#include <set>

LGE_GameWindow::LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps) : LGE_RenderWindow(title, width, height, fullscreen), frameDelay(fps) {
	b2Vec2 gravity(0.0f, 10.0f);
	world = std::make_unique<b2World>(gravity);
	SDLDebugDraw* debugDraw = new SDLDebugDraw(renderer);
	debugDraw->SetFlags(b2Draw::e_shapeBit);
	world->SetDebugDraw(debugDraw);
}

SDL_Texture* t;
SDL_Texture* spriteSheet,
* grassTile,
* boxTile,
* grassSlope1,
* grassSlope2,
* woodenBox,
* coin;

void LGE_GameWindow::removeEntity(LGE_Entity* ent) {
	removeEntities.push_back(ent);
}

LGE_Entity* makeEntityFromIndex(int index, SDL_Event& ev) {
	if (index == 0) {
		LGE_Entity* newTile = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		newTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32, 32, 32, 0.8f)));
		newTile->addComponent(new LGE_SpriteComponent(grassTile, 32, 32, 64, 64, 0, 0));
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
		newSlopeTile->addComponent(new LGE_SpriteComponent(grassSlope2, 32, 32, 64, 64, 0, 0, 0, -16));
		return newSlopeTile;
	}
	else if (index == 2) {
		LGE_Entity* dynamicBox = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		dynamicBox->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(
			ev.button.x / 32 * 32 - 1,
			ev.button.y / 32 * 32,
			32, 32, 0.8f, 0.1f, true)));
		dynamicBox->addComponent(new LGE_SpriteComponent(woodenBox, 32, 32, 32, 32, 0, 0));
		return dynamicBox;
	}
	else if (index == 3) {
		LGE_Entity* coinEntity = new LGE_Entity(LGE_EntityType::ET_COLLECTIBLE);
		coinEntity->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::CharacterBody(
			ev.button.x / 32 * 32 - 1,
			ev.button.y / 32 * 32,
			32 / 2, 32 / 2, 0.1f)));
		coinEntity->addComponent(new LGE_SpriteComponent(coin, 32 / 2, 32 / 2, 32, 32, 4, 100));
		return coinEntity;
	}
	return nullptr;
}


void LGE_GameWindow::gameLoop() {
	SDL_Texture* background = loadTexture("textures/background.png");
	SDL_Rect bg_src, bg_dest;
	bg_src.x = bg_src.y = 0;
	bg_src.w = 1920;
	bg_src.h = 1080;
	bg_dest.x = bg_dest.y = 0;
	bg_dest.w = 1280;
	bg_dest.h = 720;

	t = loadTexture("textures/placeholder.png");
	spriteSheet = loadTexture("textures/crudewalk.png");
	grassTile = loadTexture("textures/grasstile.png");
	boxTile = loadTexture("textures/boxtest.png");
	grassSlope1 = loadTexture("textures/grass_slope_a.png");
	grassSlope2 = loadTexture("textures/grass_slope_b.png");
	woodenBox = loadTexture("textures/wooden_box.png");
	coin = loadTexture("textures/coin.png");
	LGE_Component::game = this;
	bool gameLoop = true;
	SDL_Event ev;
	const Uint64 desiredFrameTime = 1000 / frameDelay;
	Uint64 frameStart, frameTime;
	const float timeStep = 1.0 / (float)frameDelay;
	const int32 velocityIterations = 8, positionIterations = 3;
	LGE_Entity ent(LGE_EntityType::ET_PLAYER);//, tile;
	int tileIndex = 0;
	ent.addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::CharacterBody(0, 0, 24, 24, 0.1f)));
	ent.addComponent(new LGE_SpriteComponent(spriteSheet, 24, 28, 24, 28, 6, 100, 4));

	std::set<LGE_Entity*> entities;
	for (int i = 0; i < 16; ++i) {
		LGE_Entity* newTile = new LGE_Entity(LGE_EntityType::ET_GENERIC);
		newTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(i * 32 - 1, 448, 32, 32, 0.8f)));
		newTile->addComponent(new LGE_SpriteComponent(grassTile, 32, 32, 64, 64, 0, 0));
		entities.insert(newTile);
	}
	entities.insert(&ent);	
	//LGE_Entity testFixture(LGE_EntityType::ET_GENERIC);
	//testFixture.addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TestFixtureBody(100, 100, 0.1f)));
	//entities.push_back(&testFixture);
	//entities.push_back(&tile);
	LGE_ContactListener contact(this);
	world->SetContactListener(&contact);
	do {
		while (SDL_PollEvent(&ev)) {
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
						LGE_Entity* gent = makeEntityFromIndex(tileIndex, ev);
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
			case SDL_KEYDOWN:
			{
				LGE_PhysicsComponent* phys = (LGE_PhysicsComponent*)ent.getComponent(LGE_ComponentType::CT_PHYSICS);
				b2Body* b = phys->getBody();
				b2Vec2 vel = b->GetLinearVelocity(), desiredVel = b2Vec2(0, 0);
				float scale = 20.0;
				switch (ev.key.keysym.sym) {
				case SDLK_w:
					//b->ApplyForceToCenter(b2Vec2(0, 100), true);
					if (abs(vel.y) < 0.01) {
						desiredVel.y = -100.0 * scale;
					}
					break;
				case SDLK_a:
					if (vel.x > -5) {
						desiredVel.x = -5 * scale;
					}
					//b->ApplyForceToCenter(b2Vec2(-50, 0), true);
					break;
				case SDLK_d:
					if (vel.x < 5) {
						desiredVel.x = 5 * scale;
					}
					//b->ApplyForceToCenter(b2Vec2(50, 0), true);
					break;
				}
				if (desiredVel.x == 0.0) {
					desiredVel.x = vel.x * -10.0;
				}
				//b->ApplyLinearImpulse(desiredVel, b->GetWorldCenter(), true);
				b->ApplyForce(desiredVel, b->GetWorldCenter(), true);
				break;
			}
			}
		}
		frameStart = SDL_GetTicks64();
		//ent.update(frameStart);
		//clear();
		//ent.draw();
		clear();
		renderTexture(background, bg_src, bg_dest);
		world->Step(timeStep, velocityIterations, positionIterations);
		for (LGE_Entity* gent : removeEntities) {
			gent->destroy();
			//delete *gent;
			//*gent = nullptr;
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
		//world->DebugDraw();
		present();
		frameTime = SDL_GetTicks64() - frameStart;
		if (desiredFrameTime > frameTime) {
			SDL_Delay(desiredFrameTime - frameTime);
		}
	} while (gameLoop);
}

b2World* LGE_GameWindow::getWorld()
{
	return world.get();
}