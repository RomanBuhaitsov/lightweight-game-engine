#include "LGE_Entity.h"
#include "LGE_SpriteComponent.h"

LGE_SpriteComponent::LGE_SpriteComponent(SDL_Texture* texture,
	int spriteWidth, int spriteHeight,
	int frameWidth, int frameHeight,
	int numFrames, int animationSpeed)
	: LGE_Component(LGE_ComponentType::CT_SPRITE), texture(texture),
	src({ 0, 0, frameWidth, frameHeight }), dst({ 0, 0, spriteWidth, spriteHeight }), center({ frameWidth / 2, frameHeight / 2 }),
	numFrames(numFrames), animationSpeed(animationSpeed),
	currentFrame(0), lastUpdate(0), position(NULL), flip(SDL_FLIP_NONE) {
}

void LGE_SpriteComponent::init() {
	position = (LGE_PositionComponent*)entity->getComponent(LGE_ComponentType::CT_POSITION);
	dst.x = position->getX();
	dst.y = position->getY();
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

void LGE_SpriteComponent::setRow(const int& row) {
	src.y = row * src.h;
}

void LGE_SpriteComponent::update(const Uint64& gameTime) {
	dst.x = position->getX();
	dst.y = position->getY();
	if (gameTime - lastUpdate > animationSpeed) {
		currentFrame = (currentFrame + 1) % numFrames;
		src.x = currentFrame * src.w;
		lastUpdate = gameTime;
	}
}

void LGE_SpriteComponent::draw() {
	game->renderTexture(texture, src, dst, 0.0, &center, (SDL_RendererFlip)flip);
}