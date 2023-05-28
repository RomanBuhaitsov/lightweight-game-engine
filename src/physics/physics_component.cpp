#include "../message_bus/node.h"

#include "physics_component.h"
#include "../entity/entity.h"

const float PhysicsComponent::RAD2DEG = 180.0 / M_PI;
const float PhysicsComponent::M2P = 16.0;
const float PhysicsComponent::P2M = 1.0 / M2P;

PhysicsComponent::~PhysicsComponent(){
  if (body != nullptr && GAME->getWorld() != nullptr)
  {
    GAME->getWorld()->DestroyBody(body);
    body = nullptr;
  }
}

PhysicsComponent::PhysicsComponent(b2Body *body, std::function<void(Entity *, Entity*, MessageBus*)> touch, 
  std::function<bool(Entity*)> can_collide, MessageBus *message_bus) : 
    Component(ComponentType::CT_PHYSICS, message_bus), body(body), touch(touch), can_collide(can_collide){}

PhysicsComponent::PhysicsComponent(b2Body *body, MessageBus *message_bus) : 
PhysicsComponent(body, nullptr, nullptr, message_bus){}

void PhysicsComponent::init(){
  if (body != nullptr)  {
    body->GetUserData().pointer = (uintptr_t)this->entity;
  }
}

b2Body *PhysicsComponent::getBody(){
  return body;
}

b2Body *PhysicsComponent::CharacterBody(int x, int y, int width, int height, float friction)
{
  b2Body *body = nullptr;
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x * P2M, y * P2M);
  bodyDef.fixedRotation = true;
  body = GAME->getWorld()->CreateBody(&bodyDef);
  b2CircleShape circle;
  circle.m_radius = P2M * (width + height) / 4.0f;
  // b2PolygonShape dynamicBox;
  // dynamicBox.SetAsBox(P2M * width / 2.0f, P2M * height / 2.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &circle; //&dynamicBox;//
  fixtureDef.density = 1.0f;
  fixtureDef.friction = friction;
  body->CreateFixture(&fixtureDef);
  return body;
}

b2Body *PhysicsComponent::TileBody(int x, int y, int width, int height, float friction, float density, bool dynamic)
{
  b2Body *body = nullptr;
  b2BodyDef bodyDef;
  if (dynamic)
  {
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;
  }
  else
  {
    bodyDef.type = b2_staticBody;
    bodyDef.fixedRotation = true;
  }
  bodyDef.position.Set(x * P2M, y * P2M);
  body = GAME->getWorld()->CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(P2M * width / 2.0f, P2M * height / 2.0f);
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = density;
  fixtureDef.friction = friction;
  body->CreateFixture(&fixtureDef);
  return body;
}

b2Body *PhysicsComponent::RightTriangleTileBody(int x, int y, int a, int b, float friction){
  b2Body *body = nullptr;

  float slope_width_meters = a * P2M;
  float slope_height_meters = b * P2M;

  b2Vec2 slope_vertices[3];
  // slope_vertices[0].Set(-slope_width_meters  / 2.f, 0.0f);
  // slope_vertices[1].Set(slope_width_meters / 2.f, 0.0f);
  // slope_vertices[2].Set(-slope_width_meters / 2.f, slope_height_meters);

  slope_vertices[0].Set(slope_width_meters / 2.f, -slope_height_meters);
  slope_vertices[1].Set(-slope_width_meters / 2.f, 0.0f);
  slope_vertices[2].Set(slope_width_meters / 2.f, 0.0f);

  b2PolygonShape triangleShape;
  triangleShape.Set(slope_vertices, 3);

  b2BodyDef triangleBodyDef;
  triangleBodyDef.type = b2_staticBody; // b2_dynamicBody;//
  y += b / 2;
  triangleBodyDef.position.Set(x * P2M, y * P2M);
  // triangleBodyDef.fixedRotation = true;
  body = GAME->getWorld()->CreateBody(&triangleBodyDef);

  b2FixtureDef triangleFixtureDef;
  triangleFixtureDef.shape = &triangleShape;
  triangleFixtureDef.density = 1.0f;
  triangleFixtureDef.friction = friction;

  body->CreateFixture(&triangleFixtureDef);
  // body->SetTransform(body->GetPosition(), 180.0 / RAD2DEG);
  return body;
}

b2Body *PhysicsComponent::TestFixtureBody(int x, int y, float friction)
{
#if 0
	int width = 32;
	int height = 32;
	b2Body* body = nullptr;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x * P2M, y * P2M);
	bodyDef.fixedRotation = true;
	body = game->getGAME->getWorld()()->CreateBody(&bodyDef);
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
  // set up a dynamic body
  b2BodyDef myBodyDef;
  myBodyDef.type = b2_dynamicBody;
  myBodyDef.position.Set(0, 20); // middle
  b2Body *dynamicBody = GAME->getWorld()->CreateBody(&myBodyDef);

  // prepare a shape definition
  b2PolygonShape polygonShape;
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  myFixtureDef.density = 1;

  // add four square shaped fixtures around the body center
  for (int i = 0; i < 4; i++)
  {
    b2Vec2 pos(sinf(i * 90 / RAD2DEG), cosf(i * 90 / RAD2DEG)); // radial placement
    polygonShape.SetAsBox(1, 1, pos, 0);                        // a 2x2 rectangle
    dynamicBody->CreateFixture(&myFixtureDef);                  // add a fixture to the body
  }
  return dynamicBody;
}
