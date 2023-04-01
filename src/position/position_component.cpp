#include "../component/component_type.h"
#include "../entity/entity.h"
#include "../sprite/sprite_component.h"

#include "position_component.h"

void PositionComponent::update(const Uint64 gameTime)
{
  // test
  SpriteComponent *test = (SpriteComponent *)entity->getComponent(ComponentType::CT_SPRITE);
  if (test == NULL)
  {
    return;
  }
  int width, height;
  game->getSize(width, height);
  x = test->getFlipped() & SDL_FLIP_HORIZONTAL ? x - 1 : x + 1;
  y = test->getFlipped() & SDL_FLIP_VERTICAL ? y - 1 : y + 1;
  if (x + test->getSpriteWidth() > width || x < 0)
  {
    test->flipHorizontally();
  }
  if (y + test->getSpriteHeight() > height || y < 0)
  {
    test->flipVertically();
  }
}

void PositionComponent::setPos(const int &x, const int &y)
{
  this->x = x;
  this->y = y;
}
