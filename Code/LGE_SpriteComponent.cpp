#include "LGE_Entity.h"
#include "LGE_SpriteComponent.h"
#include "LGE_PhysicsComponent.h"

LGE_SpriteComponent::LGE_SpriteComponent(SDL_Texture* texture,
	int spriteWidth, int spriteHeight,
	int frameWidth, int frameHeight,
	int numFrames, int animationSpeed)
	: LGE_Component(LGE_ComponentType::CT_SPRITE), texture(texture),
	src({ 0, 0, frameWidth, frameHeight }), dst({ 0, 0, spriteWidth, spriteHeight }), center({ frameWidth / 2, frameHeight / 2 }),
	numFrames(numFrames), animationSpeed(animationSpeed),
	currentFrame(0), lastUpdate(0), position(NULL), flip(SDL_FLIP_NONE), playing(false), angle(0.0) {
}

void LGE_SpriteComponent::init() {
	//position = (LGE_PositionComponent*)entity->getComponent(LGE_ComponentType::CT_POSITION);
	//dst.x = position->getX();
	//dst.y = position->getY();
	dst.x = dst.y = 0;
}

void LGE_SpriteComponent::flipVertically() {
	flip ^= SDL_FLIP_VERTICAL;
}

void LGE_SpriteComponent::flipHorizontally() {
	flip ^= SDL_FLIP_HORIZONTAL;
}

int LGE_SpriteComponent::getSpriteWidth() {
	return dst.w;
}

int LGE_SpriteComponent::getSpriteHeight() {
	return dst.h;
}

int LGE_SpriteComponent::getFlipped() {
	return flip;
}

void LGE_SpriteComponent::startAnimation()
{
	playing = true;
}

void LGE_SpriteComponent::stopAnimation()
{
	playing = false;
}

void LGE_SpriteComponent::setRow(const int row) {
	src.y = row * src.h;
}

void LGE_SpriteComponent::update(const Uint64 gameTime) {
	LGE_PhysicsComponent* p = (LGE_PhysicsComponent*)entity->getComponent(LGE_ComponentType::CT_PHYSICS);
	if (p != nullptr) {
		b2Vec2 position = p->position(), vel = p->velocity();
		dst.x = position.x * LGE_PhysicsComponent::M2P;
		dst.y = position.y * LGE_PhysicsComponent::M2P;
		playing = vel.LengthSquared() > 0;
		/*
		if ((vel.x > 0 && flip & SDL_FLIP_HORIZONTAL) || (vel.x < 0 && !(flip & SDL_FLIP_HORIZONTAL))) {
			flip ^= SDL_FLIP_HORIZONTAL;
		}*/
		angle = p->getBody()->GetAngle() * LGE_PhysicsComponent::RAD2DEG;
	}
	//dst.x = position->getX();
	//dst.y = position->getY();
	if (!numFrames || !playing) {
		return;
	}
	if (gameTime - lastUpdate > animationSpeed) {
		currentFrame = (currentFrame + 1) % numFrames;
		src.x = currentFrame * src.w;
		lastUpdate = gameTime;
	}
}

void LGE_SpriteComponent::draw() {
	game->renderTexture(texture, src, dst, angle, &center, (SDL_RendererFlip)flip);
}