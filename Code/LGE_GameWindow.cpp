#include "LGE_GameWindow.h"
#include "LGE_Entity.h"
#include "LGE_Components.h"
#include "LGE_PositionComponent.h"
#include "LGE_SpriteComponent.h"
#include "LGE_PhysicsComponent.h"
#include <list>
#include <iostream>

class SDLDebugDraw : public b2Draw
{
public:
	SDL_Renderer* m_renderer;
	SDLDebugDraw(SDL_Renderer* renderer)
	{
		m_renderer = renderer;
	}
	/*
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
			static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
		SDL_Point* points = new SDL_Point[vertexCount];
		for (int i = 0; i < vertexCount; i++)
		{
			points[i].x = static_cast<int>(vertices[i].x * 10);
			points[i].y = static_cast<int>(vertices[i].y * 10);
		}
		SDL_RenderDrawLines(m_renderer, points, vertexCount + 1);
		delete[] points;
	}
	*/
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		// Set the renderer color to the Box2D color
		SDL_SetRenderDrawColor(m_renderer, color.r * 255, color.g * 255, color.b * 255, SDL_ALPHA_OPAQUE);
		int SCREEN_HEIGHT = 720;
		float M2P = LGE_PhysicsComponent::M2P;

		// Draw the polygon
		for (int i = 0; i < vertexCount - 1; i++) {
			int x1 = vertices[i].x * M2P;
			int y1 = SCREEN_HEIGHT - vertices[i].y * M2P;
			int x2 = vertices[i + 1].x * M2P;
			int y2 = SCREEN_HEIGHT - vertices[i + 1].y * M2P;
			SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
		}
		int x1 = vertices[vertexCount - 1].x * M2P;
		int y1 = SCREEN_HEIGHT - vertices[vertexCount - 1].y * M2P;
		int x2 = vertices[0].x * M2P;
		int y2 = SCREEN_HEIGHT - vertices[0].y * M2P;
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);

		// Draw a line to close the polygon
		SDL_RenderDrawLine(m_renderer, x2, y2, vertices[1].x * M2P, SCREEN_HEIGHT - vertices[1].y * M2P);
	}
	/*
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
			static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 128);
		SDL_Point* points = new SDL_Point[vertexCount];
		for (int i = 0; i < vertexCount; i++)
		{
			points[i].x = static_cast<int>(vertices[i].x * 10);
			points[i].y = static_cast<int>(vertices[i].y * 10);
		}
		SDL_RenderDrawLines(m_renderer, points, vertexCount + 1);
		delete[] points;
	}*/

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{

		// Set the renderer color to the Box2D color
		SDL_SetRenderDrawColor(m_renderer, color.r * 255, color.g * 255, color.b * 255, SDL_ALPHA_OPAQUE);
		int SCREEN_HEIGHT = 720;
		float M2P = LGE_PhysicsComponent::M2P;

		// Draw the polygon
		for (int i = 0; i < vertexCount - 1; i++) {
			int x1 = vertices[i].x * M2P + 15;
			int y1 = vertices[i].y * M2P + 15;
			int x2 = vertices[i + 1].x * M2P + 15;
			int y2 = vertices[i + 1].y * M2P + 15;
			SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
		}
		int x1 = vertices[vertexCount - 1].x * M2P + 15;
		int y1 = vertices[vertexCount - 1].y * M2P + 15;
		int x2 = vertices[0].x * M2P + 15;
		int y2 = vertices[0].y * M2P + 15;
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);

		// Draw a line to close the polygon
		SDL_RenderDrawLine(m_renderer, x2, y2, vertices[1].x * M2P + 15, vertices[1].y * M2P + 15);

	}

	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override
	{
		SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
			static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
		int x = static_cast<int>(center.x * 10);
		int y = static_cast<int>(center.y * 10);
		int r = static_cast<int>(radius * 10);
		for (int i = 0; i <= r; i++)
		{
			int j = static_cast<int>(sqrt(r * r - i * i));
			SDL_RenderDrawPoint(m_renderer, x + i, y + j);
			SDL_RenderDrawPoint(m_renderer, x + i, y - j);
			SDL_RenderDrawPoint(m_renderer, x - i, y + j);
			SDL_RenderDrawPoint(m_renderer, x - i, y - j);
		}
	}

	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override
	{
		SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
			static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
		int x = static_cast<int>(center.x * 10);
		int y = static_cast<int>(center.y * 10);
		int r = static_cast<int>(radius * 10);
		for (int i = 0; i <= r; i++)
		{
			int j = static_cast<int>(sqrt(r * r - i * i));
			SDL_RenderDrawPoint(m_renderer, x + i, y + j);
			SDL_RenderDrawPoint(m_renderer, x + i, y - j);
			SDL_RenderDrawPoint(m_renderer, x - i, y + j);
			SDL_RenderDrawPoint(m_renderer, x - i, y - j);
		}
	}

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, static_cast<uint8_t>(color.r * 255), static_cast<uint8_t>(color.g * 255), static_cast<uint8_t>(color.b * 255), SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x), static_cast<int>(p1.y), static_cast<int>(p2.x), static_cast<int>(p2.y));
	}

	void DrawTransform(const b2Transform& xf) override
	{
		b2Vec2 xAxis = xf.q.GetXAxis();
		b2Vec2 yAxis = xf.q.GetYAxis();
		b2Vec2 p1 = xf.p;
		b2Vec2 p2 = p1 + 0.4f * xAxis;
		b2Vec2 p3 = p1 + 0.4f * yAxis;
		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x * 10), static_cast<int>(p1.y * 10),
			static_cast<int>(p2.x * 10), static_cast<int>(p2.y * 10));
		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(m_renderer, static_cast<int>(p1.x * 10), static_cast<int>(p1.y * 10),
			static_cast<int>(p3.x * 10), static_cast<int>(p3.y * 10));
	}

	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override
	{
		SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(color.r * 255),
			static_cast<Uint8>(color.g * 255), static_cast<Uint8>(color.b * 255), 255);
		SDL_Rect rect = {
			static_cast<int>((p.x - size / 2.0f) * 10),
			static_cast<int>((p.y - size / 2.0f) * 10),
			static_cast<int>(size * 10),
			static_cast<int>(size * 10)
		};
		SDL_RenderFillRect(m_renderer, &rect);
	}

};

LGE_GameWindow::LGE_GameWindow(const char* title, int width, int height, bool fullscreen, int fps) : LGE_RenderWindow(title, width, height, fullscreen), frameDelay(fps) {
	b2Vec2 gravity(0.0f, 10.0f);
	world = std::make_unique<b2World>(gravity);
	SDLDebugDraw* debugDraw = new SDLDebugDraw(renderer);
	debugDraw->SetFlags(b2Draw::e_shapeBit);
	world->SetDebugDraw(debugDraw);
}


void LGE_GameWindow::gameLoop() {
	SDL_Texture* t = loadTexture("textures/placeholder.png");
	SDL_Texture* spriteSheet = loadTexture("textures/crudewalk.png"), 
		*grassTile = loadTexture("textures/grasstile.png"),
		* boxTile = loadTexture("textures/boxtest.png"),
		*grassSlope1 = loadTexture("textures/grass_slope_a.png"),
		*grassSlope2 = loadTexture("textures/grass_slope_b.png");
	LGE_Component::game = this;
	bool gameLoop = true;
	SDL_Event ev;
	const Uint64 desiredFrameTime = 1000 / frameDelay;
	Uint64 frameStart, frameTime;
	const float timeStep = 1.0 / (float)frameDelay;
	const int32 velocityIterations = 8, positionIterations = 3;
	LGE_Entity ent;//, tile;
	//ent.addComponent(new LGE_PositionComponent());
	//ent.addComponent(new LGE_PhysicsComponent(0, 0, 24, 28, 0.3f, b2_dynamicBody));
	//ent.addComponent(new LGE_SpriteComponent(spriteSheet, 24, 28, 24, 28, 6, 100));
	//ent.addComponent(new LGE_PhysicsComponent(0, 0, 32, 32, 0.3f, b2_dynamicBody));
	ent.addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::CharacterBody(0, 0, 32, 32, 0.1f)));
	ent.addComponent(new LGE_SpriteComponent(boxTile, 32, 32, 64, 64, 0, 0));
	//tile.addComponent(new LGE_PhysicsComponent(10, 10, 32, 32, 0.3f, b2_staticBody));
	//tile.addComponent(new LGE_SpriteComponent(grassTile, 64, 64, 64, 64, 0, 0));
	std::list<LGE_Entity*> entities;
	for (int i = 0; i < 16; ++i) {
		LGE_Entity* newTile = new LGE_Entity();
		//newTile->addComponent(new LGE_PhysicsComponent(i * 32, 480, 32, 32, 0.3f, b2_staticBody));
		newTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(i * 32 - 1, 480, 32, 32, 0.8f)));
		newTile->addComponent(new LGE_SpriteComponent(grassTile, 32, 32, 64, 64, 0, 0));
		entities.push_back(newTile);
	}
	entities.push_back(&ent);
	//entities.push_back(&tile);
	do {
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				gameLoop = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
			{
				//basic grass block
				/*LGE_Entity* newTile = new LGE_Entity();
				newTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32 - 1, 32, 32, 0.8f)));
				newTile->addComponent(new LGE_SpriteComponent(grassTile, 32, 32, 64, 64, 0, 0));
				entities.push_back(newTile);
				*/
				LGE_Entity* newSlopeTile = new LGE_Entity();
				//newSlopeTile->addComponent(new LGE_PhysicsComponent(LGE_PhysicsComponent::TileBody(ev.button.x / 32 * 32 - 1, ev.button.y / 32 * 32 - 1, 32, 32, 0.8f)));
				newSlopeTile->addComponent(new LGE_PhysicsComponent(
					LGE_PhysicsComponent::RightTriangleTileBody(
						ev.button.x / 32 * 32 - 1, 
						ev.button.y / 32 * 32 - 1,
						32, 32, 0.8f)));
				newSlopeTile->addComponent(new LGE_SpriteComponent(grassSlope2, 32, 32, 64, 64, 0, 0));
				entities.push_back(newSlopeTile);
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
		world->Step(timeStep, velocityIterations, positionIterations);
		for (LGE_Entity* gent : entities) {
			gent->update(frameStart);
			gent->draw();
		}
		world->DebugDraw();
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