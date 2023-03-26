#pragma once
#include "LGE_Components.h"
#include "box2d/box2d.h"
#include <cmath>
#include <functional>

class LGE_PhysicsComponent : public LGE_Component {
private:
	b2Body* body;
	std::function<bool(LGE_Entity*)> touch; //return true => remove the entity
public:
	//LGE_PhysicsComponent(int x, int y, int width, int height, float friction, b2BodyType bodyType);
	LGE_PhysicsComponent(b2Body* body, std::function<bool(LGE_Entity*)> touch);
	LGE_PhysicsComponent(b2Body* body);
	void draw() override {};
	void init() override;
	b2Body* getBody();
	~LGE_PhysicsComponent();
	const static float RAD2DEG;
	const static float M2P;
	const static float P2M;

	static b2Body* CharacterBody(int x, int y, int width, int height, float friction);
	static b2Body* TileBody(int x, int y, int width, int height, float friction, float density = 1.0f, bool dynamic = false);
	static b2Body* RightTriangleTileBody(int x, int y, int a, int b, float friction);
	static b2Body* TestFixtureBody(int x, int y, float friction);

	friend class LGE_ContactListener;
};