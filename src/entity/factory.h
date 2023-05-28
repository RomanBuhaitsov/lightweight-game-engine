#pragma once

#include "../entity/entity.h"
#include <functional>
#include <initializer_list>

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
  static Entity *createAnimation(int pos_x, int pos_y, SDL_Texture *texture,
                MessageBus *message_bus, int animation_speed, 
                const std::initializer_list<Uint16> &numFrames, std::string track_title);
  static Entity* createCoin(int pos_x, int pos_y, SDL_Texture* texture, MessageBus* message_bus);

private:
    static const std::string enumString[ENTITYFACTORY_MAX + 1];
};
