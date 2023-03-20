#pragma once
#include "LGE_Components.h"
#include "LGE_PositionComponent.h"

class LGE_SpriteComponent : public LGE_Component {
private:
	SDL_Texture* texture;
	LGE_PositionComponent* position;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Point center;
	int flip;
	int animationSpeed;
	int numFrames;
	int currentFrame;
	Uint64 lastUpdate;
	bool playing;
	float angle;
public:
	LGE_SpriteComponent(SDL_Texture* texture, int spriteWidth, int spriteHeight, int frameWidth, int frameHeight, int numFrames, int animationSpeed);
	void setRow(const int row);
	void update(const Uint64 gameTime);
	void draw();
	void init();
	void flipVertically();
	void flipHorizontally();
	int getSpriteWidth();
	int getSpriteHeight();
	int getFlipped();
	void startAnimation();
	void stopAnimation();
};