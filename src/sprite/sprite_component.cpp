#include "../entity/entity.h"
#include "../physics/physics_component.h"
#include "../log.h"

#include "sprite_component.h"

int SpriteComponent::global_shift_x = 0;
int SpriteComponent::global_shift_y = 0;

void SpriteComponent::setGlobalShift(int x, int y) {
    global_shift_x = x;
    global_shift_y = y;
}

SpriteComponent::SpriteComponent(MessageBus *message_bus, SDL_Texture *texture,
                                 int spriteWidth, int spriteHeight,
                                 int frameWidth, int frameHeight,
                                 const std::initializer_list<Uint16> &numFrames,
                                 Uint16 animationSpeed, int shift_x, int shift_y)
    : Component(ComponentType::CT_SPRITE, message_bus), texture(texture),
      src({0, 0, frameWidth, frameHeight}), dst({0, 0, spriteWidth, spriteHeight}), center({frameWidth / 2, frameHeight / 2}),
      animationSpeed(animationSpeed),
      currentFrame(0), currentRow(0), lastUpdate(0), nRows(numFrames.size()),
      flip(SDL_FLIP_NONE), playing(true), angle(0.0), shift_x(shift_x), shift_y(shift_y)
{
  if (!nRows)
  {
    LogError << "The spritesheet has 0 rows. Defaulting to 1.\n";
    nRows = 1;
  }
  frames = std::make_unique<Uint16 *>(new Uint16[nRows]);
  std::copy(numFrames.begin(), numFrames.end(), *frames);
}

SpriteComponent::SpriteComponent(MessageBus *message_bus, SDL_Texture *texture,
                                 int spriteWidth, int spriteHeight,
                                 int frameWidth, int frameHeight,
                                 int shift_x, int shift_y) : SpriteComponent(message_bus, texture, spriteWidth, spriteHeight, frameWidth, frameHeight, {1}, 0, shift_x, shift_y)
{
}

void SpriteComponent::init()
{
  dst.x = dst.y = 0;
}

void SpriteComponent::flipVertically()
{
  flip ^= SDL_FLIP_VERTICAL;
}

void SpriteComponent::flipHorizontally()
{
  flip ^= SDL_FLIP_HORIZONTAL;
}

int SpriteComponent::getSpriteWidth()
{
  return dst.w;
}

int SpriteComponent::getSpriteHeight()
{
  return dst.h;
}

Uint16 SpriteComponent::getFlipped()
{
  return flip;
}

void SpriteComponent::startAnimation()
{
  playing = true;
}

void SpriteComponent::stopAnimation()
{
  playing = false;
}

void SpriteComponent::setAngle(float angle)
{
  this->angle = angle;
}

void SpriteComponent::setPosition(int x, int y)
{
  dst.x = x + shift_x - global_shift_x;
  dst.y = y + shift_y - global_shift_y;
}

void SpriteComponent::setRow(const int row)
{
  currentRow = std::min(row, nRows - 1);
  // currentFrame = 0;
  src.y = currentRow * src.h;
}

void SpriteComponent::update(const Uint64 gameTime)
{
  Uint16 numFrames = (*frames)[currentRow];
#if 0
	PhysicsComponent* p = (PhysicsComponent*)entity->getComponent(ComponentType::CT_PHYSICS);
	if (p != nullptr) {
		b2Vec2 position = p->position(), vel = p->velocity();
		dst.x = position.x * PhysicsComponent::M2P + shift_x;
		dst.y = position.y * PhysicsComponent::M2P + shift_y;
		if (numFrames > 1 && ((vel.x > 0.1f && (flip & SDL_FLIP_HORIZONTAL)) || (vel.x < -0.1f && !(flip & SDL_FLIP_HORIZONTAL)))) {
			flip ^= SDL_FLIP_HORIZONTAL;
		}
		angle = p->getBody()->GetAngle() * PhysicsComponent::RAD2DEG;
	}
#endif
  if (numFrames <= 1 || !playing)
  {
    return;
  }
  if (gameTime - lastUpdate > animationSpeed)
  {
    currentFrame = (currentFrame + 1) % numFrames;
    src.x = currentFrame * src.w;
    lastUpdate = gameTime;
  }
}

void SpriteComponent::draw()
{
  GAME->renderTexture(texture, src, dst, angle, &center, (SDL_RendererFlip)flip);
}
