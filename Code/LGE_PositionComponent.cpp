#include "LGE_Entity.h"
#include "LGE_PositionComponent.h"
#include "LGE_SpriteComponent.h"

void LGE_PositionComponent::update(const Uint64& gameTime) {
	//test
	LGE_SpriteComponent* test = (LGE_SpriteComponent*)entity->getComponent(LGE_ComponentType::CT_SPRITE);
	if (test == NULL) {
		return;
	}
	int width, height;
	game->getSize(width, height);
	x = test->getFlipped() & SDL_FLIP_HORIZONTAL ? x - 1 : x + 1;
	y = test->getFlipped() & SDL_FLIP_VERTICAL ? y - 1 : y + 1;
	if (x + test->getSpriteWidth() > width || x < 0) {
		test->flipHorizontally();
	}
	if (y + test->getSpriteHeight() > height || y < 0) {
		test->flipVertically();
	}
}

void LGE_PositionComponent::setPos(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}
