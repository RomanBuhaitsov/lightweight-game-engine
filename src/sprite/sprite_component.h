#pragma once
#include "../component/component.h"
#include "../position/position_component.h"

class SpriteComponent : public Component
{
private:
  SDL_Texture *texture;
  SDL_Rect src;
  SDL_Rect dst;
  SDL_Point center;
  Uint16 flip;
  Uint16 animationSpeed;
  Uint16 nRows;
  std::unique_ptr<Uint16 *> frames;
  Uint16 currentFrame;
  Uint16 currentRow;
  Uint64 lastUpdate;
  bool playing;
  float angle;
  int shift_x;
  int shift_y;

public:
  SpriteComponent(SDL_Texture *texture, int spriteWidth, int spriteHeight,
                  int frameWidth, int frameHeight,
                  const std::initializer_list<Uint16> &numFrames, Uint16 animationSpeed,
                  int shift_x = 0, int shift_y = 0);
  SpriteComponent(SDL_Texture *texture, int spriteWidth, int spriteHeight,
                  int frameWidth, int frameHeight,
                  int shift_x = 0, int shift_y = 0);
  void setRow(const int row);
  void update(const Uint64 gameTime);
  void draw();
  void init();
  void flipVertically();
  void flipHorizontally();
  int getSpriteWidth();
  int getSpriteHeight();
  Uint16 getFlipped();
  void startAnimation();
  void stopAnimation();
  void setAngle(float angle);
  void setPosition(int x, int y);
};
