#pragma once
#include "LGE_Components.h"
#include "box2d/box2d.h"
#include <cmath>

class LGE_PhysicsComponent : public LGE_Component {
private:
	b2Body* body;
public:
	//LGE_PhysicsComponent(int x, int y, int width, int height, float friction, b2BodyType bodyType);
	LGE_PhysicsComponent(b2Body* body);
	const b2Vec2 & position() const;
	const b2Vec2& velocity() const;
	void draw() {};
	b2Body* getBody();

	const static float RAD2DEG;
	const static float M2P;
	const static float P2M;

	static b2Body* CharacterBody(int x, int y, int width, int height, float friction);
	static b2Body* TileBody(int x, int y, int width, int height, float friction);
	static b2Body* RightTriangleTileBody(int x, int y, int a, int b, float friction);
};