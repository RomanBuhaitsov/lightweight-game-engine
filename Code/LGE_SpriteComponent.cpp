#include "LGE_Entity.h"
#include "LGE_SpriteComponent.h"
#include "LGE_PhysicsComponent.h"
#include "LGE_InputOutput.h"

LGE_SpriteComponent::LGE_SpriteComponent(SDL_Texture* texture,
	int spriteWidth, int spriteHeight,
	int frameWidth, int frameHeight,
	const std::initializer_list<Uint16>& numFrames, 
	Uint16 animationSpeed, int shift_x, int shift_y)
	: LGE_Component(LGE_ComponentType::CT_SPRITE), texture(texture),
	src({ 0, 0, frameWidth, frameHeight }), dst({ 0, 0, spriteWidth, spriteHeight }), center({ frameWidth / 2, frameHeight / 2 }),
	animationSpeed(animationSpeed),
	currentFrame(0), currentRow(0), lastUpdate(0), nRows(numFrames.size()),
	flip(SDL_FLIP_NONE), playing(true), angle(0.0), shift_x(shift_x), shift_y(shift_y) {
	if (!nRows) {
		LGE_LogError << "The spritesheet has 0 rows. Defaulting to 1.\n";
		nRows = 1;
	}
	frames = std::make_unique<Uint16*>(new Uint16[nRows]);
	std::copy(numFrames.begin(), numFrames.end(), *frames);
}

LGE_SpriteComponent::LGE_SpriteComponent(SDL_Texture* texture, 
	int spriteWidth, int spriteHeight, 
	int frameWidth, int frameHeight, 
	int shift_x, int shift_y) : LGE_SpriteComponent(texture, spriteWidth, spriteHeight, frameWidth, frameHeight, { 1 }, 0, shift_x, shift_y)
{
}

void LGE_SpriteComponent::init() {
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

Uint16 LGE_SpriteComponent::getFlipped() {
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

void LGE_SpriteComponent::setAngle(float angle)
{
	this->angle = angle;
}

void LGE_SpriteComponent::setPosition(int x, int y)
{
	dst.x = x + shift_x;
	dst.y = y + shift_y;
}

void LGE_SpriteComponent::setRow(const int row) {
	currentRow = std::min(row, nRows - 1);
	//currentFrame = 0;
	src.y = currentRow * src.h;
}

void LGE_SpriteComponent::update(const Uint64 gameTime) {
	Uint16 numFrames = (*frames)[currentRow];
#if 0
	LGE_PhysicsComponent* p = (LGE_PhysicsComponent*)entity->getComponent(LGE_ComponentType::CT_PHYSICS);
	if (p != nullptr) {
		b2Vec2 position = p->position(), vel = p->velocity();
		dst.x = position.x * LGE_PhysicsComponent::M2P + shift_x;
		dst.y = position.y * LGE_PhysicsComponent::M2P + shift_y;
		if (numFrames > 1 && ((vel.x > 0.1f && (flip & SDL_FLIP_HORIZONTAL)) || (vel.x < -0.1f && !(flip & SDL_FLIP_HORIZONTAL)))) {
			flip ^= SDL_FLIP_HORIZONTAL;
		}
		angle = p->getBody()->GetAngle() * LGE_PhysicsComponent::RAD2DEG;
	}
#endif
	if (numFrames <= 1 || !playing) {
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