#include "LGE_PhysicsComponent.h"
#include "LGE_InputOutput.h"

const float LGE_PhysicsComponent::RAD2DEG = 180.0 / M_PI;
const float LGE_PhysicsComponent::M2P = 16.0;
const float LGE_PhysicsComponent::P2M = 1.0 / M2P;

LGE_PhysicsComponent::~LGE_PhysicsComponent() {
	if (body != nullptr && game->getWorld() != nullptr) {
		game->getWorld()->DestroyBody(body);
		body = nullptr;
	}
}

LGE_PhysicsComponent::LGE_PhysicsComponent(b2Body* body) : LGE_Component(LGE_ComponentType::CT_PHYSICS), body(body)
{

}

void LGE_PhysicsComponent::init() {
	if (body != nullptr) {
		//body->SetUserData(this->entity); //kill me //unrecognized symbol, good job
		body->GetUserData().pointer = (uintptr_t)this->entity;
	}
}

/*
LGE_PhysicsComponent::LGE_PhysicsComponent(int x, int y, int width, int height, float friction, b2BodyType bodyType) : LGE_Component(LGE_ComponentType::CT_PHYSICS)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;//b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	bodyDef.fixedRotation = true;
	body = game->getWorld()->CreateBody(&bodyDef);
	if (bodyType != b2_dynamicBody) {
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(P2M * width / 2.0, P2M * height / 2.0);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = friction;
		body->CreateFixture(&fixtureDef);
	}
	else {
		b2CircleShape circle;
		//circle.m_p.Set(2.0f, 3.0f);
		circle.m_radius = P2M * (width + height) / 4;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = friction;
		body->CreateFixture(&fixtureDef);
	}
}
*/
const b2Vec2 & LGE_PhysicsComponent::position() const
{
	return body->GetPosition();
}

const b2Vec2& LGE_PhysicsComponent::velocity() const
{
	return body->GetLinearVelocity();
}

b2Body* LGE_PhysicsComponent::getBody()
{
	return body;
}

b2Body* LGE_PhysicsComponent::CharacterBody(int x, int y, int width, int height, float friction)
{
	b2Body* body = nullptr;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	bodyDef.fixedRotation = true;
	body = game->getWorld()->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = P2M * (width + height) / 4.0f;
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(P2M * width / 2.0f, P2M * height / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;//&dynamicBox;//
	fixtureDef.density = 1.0f;
	fixtureDef.friction = friction;
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* LGE_PhysicsComponent::TileBody(int x, int y, int width, int height, float friction, float density, bool dynamic)
{
	b2Body* body = nullptr;
	b2BodyDef bodyDef;
	if (dynamic) {
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = false;
	}
	else {
		bodyDef.type = b2_staticBody;
		bodyDef.fixedRotation = true;
	}
	bodyDef.position.Set(x * P2M, y * P2M);
	body = game->getWorld()->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * width / 2.0f, P2M * height / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* LGE_PhysicsComponent::RightTriangleTileBody(int x, int y, int a, int b, float friction)
{
	b2Body* body = nullptr;

	float slope_width_meters = a * P2M;
	float slope_height_meters = b * P2M;

	b2Vec2 slope_vertices[3];
	//slope_vertices[0].Set(-slope_width_meters  / 2.f, 0.0f);
	//slope_vertices[1].Set(slope_width_meters / 2.f, 0.0f);
	//slope_vertices[2].Set(-slope_width_meters / 2.f, slope_height_meters);

	slope_vertices[0].Set(slope_width_meters / 2.f, -slope_height_meters);
	slope_vertices[1].Set(-slope_width_meters / 2.f, 0.0f);
	slope_vertices[2].Set(slope_width_meters / 2.f, 0.0f);

	b2PolygonShape triangleShape;
	triangleShape.Set(slope_vertices, 3);


	b2BodyDef triangleBodyDef;
	triangleBodyDef.type = b2_staticBody;//b2_dynamicBody;//
	y += b / 2;
	triangleBodyDef.position.Set(x * P2M, y * P2M);
	//triangleBodyDef.fixedRotation = true;
	body = game->getWorld()->CreateBody(&triangleBodyDef);

	b2FixtureDef triangleFixtureDef;
	triangleFixtureDef.shape = &triangleShape;
	triangleFixtureDef.density = 1.0f;
	triangleFixtureDef.friction = friction;

	body->CreateFixture(&triangleFixtureDef);
	//body->SetTransform(body->GetPosition(), 180.0 / RAD2DEG);
	return body;
}

b2Body* LGE_PhysicsComponent::TestFixtureBody(int x, int y, float friction)
{
#if 0
	int width = 32;
	int height = 32;
	b2Body* body = nullptr;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	bodyDef.fixedRotation = true;
	body = game->getWorld()->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = P2M * (width + height) / 4.0f;
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(P2M * width / 8.0f, P2M * height / 8.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;//&dynamicBox;//
	fixtureDef.density = 1.0f;
	fixtureDef.friction = friction;
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &dynamicBox;
	fixtureDef2.density = 1.0f;
	fixtureDef2.friction = friction;
	body->CreateFixture(&fixtureDef);
	//body->CreateFixture(&fixtureDef2);
	return body;
#endif
	//set up a dynamic body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0, 20); //middle
	b2Body* dynamicBody = game->getWorld()->CreateBody(&myBodyDef);

	//prepare a shape definition
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	//add four square shaped fixtures around the body center
	for (int i = 0; i < 4; i++) {
		b2Vec2 pos(sinf(i * 90 / RAD2DEG), cosf(i * 90 / RAD2DEG)); //radial placement
		polygonShape.SetAsBox(1, 1, pos, 0); //a 2x2 rectangle
		dynamicBody->CreateFixture(&myFixtureDef); //add a fixture to the body
	}
	return dynamicBody;
}


