#pragma once

#include "../entity/entity.h"

class EntityFactory {
public:
  /* EntityFactory(); */
  /* ~EntityFactory(); */
  enum EntityFactoryType {
      ENTITYFACTORY_PLAYER = 0,
      ENTITYFACTORY_TILE,
      ENTITYFACTORY_COIN,
      ENTITYFACTORY_MAX
  };
  
  static const std::string & EnumToString(EntityFactoryType type);

  static Entity *createTile(int pos_x, int pos_y, SDL_Texture *texture,
                            MessageBus *message_bus);
  static Entity *createPlayer(int pos_x, int pos_y, SDL_Texture *texture,
                              MessageBus *message_bus);

  static Entity* createCoin(int pos_x, int pos_y, SDL_Texture* texture, MessageBus* message_bus);

private:
    static const std::string enumString[ENTITYFACTORY_MAX + 1];
};
