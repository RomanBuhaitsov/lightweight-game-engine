#pragma once

#include "../entity/entity.h"

class EntityFactory {
public:
  /* EntityFactory(); */
  /* ~EntityFactory(); */

  static Entity *createTile(int pos_x, int pos_y, SDL_Texture *texture,
                            MessageBus *message_bus);
  static Entity *createPlayer(int pos_x, int pos_y, SDL_Texture *texture,
                              MessageBus *message_bus);
};
