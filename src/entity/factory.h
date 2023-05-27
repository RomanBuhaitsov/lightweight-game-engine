#pragma once

#include "../entity/entity.h"
#include <functional>
#include <initializer_list>

class EntityFactory {
public:
  /* EntityFactory(); */
  /* ~EntityFactory(); */

  static Entity *createTile(int pos_x, int pos_y, SDL_Texture *texture,
                            MessageBus *message_bus);
  static Entity *createPlayer(int pos_x, int pos_y, SDL_Texture *texture,
                              MessageBus *message_bus);
  static Entity *createAnimation(int pos_x, int pos_y, SDL_Texture *texture,
                MessageBus *message_bus, int animation_speed, 
                const std::initializer_list<Uint16> &numFrames);
};
