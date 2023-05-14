
#include "../entity/builder.h"
#include <iostream>

#include "SDL2/SDL.h"

#include "factory.h"

#define ENUM2STRING(x) #x

const std::string EntityFactory::enumString[ENTITYFACTORY_MAX + 1] = {
    ENUM2STRING(ENTITYFACTORY_PLAYER),
    ENUM2STRING(ENTITYFACTORY_TILE),
    "Invalid ENTITYFACTORY type"
};

const std::string & EntityFactory::EnumToString(EntityFactoryType type) {
    if (type > 0 && type < ENTITYFACTORY_MAX) {
        return enumString[type];
    }
    return enumString[ENTITYFACTORY_MAX];
}

Entity *EntityFactory::createTile(int pos_x, int pos_y, SDL_Texture *texture,
                                  MessageBus *message_bus) {
  return (new EntityBuilder(EntityType::ET_GENERIC))
      ->addPhysics(new PhysicsComponent(
          PhysicsComponent::TileBody(pos_x, pos_y, 32, 32, 0.8f), message_bus))
      ->addSprite(new SpriteComponent(message_bus, texture, 32, 32, 64, 64))
      ->addSpritePhysics(new SpritePhysicsHandler(message_bus))
      ->getEntity();
}

Entity *EntityFactory::createPlayer(int pos_x, int pos_y, SDL_Texture *texture,
                                    MessageBus *message_bus) {
  return (new EntityBuilder(EntityType::ET_PLAYER))
      ->addPhysics(new PhysicsComponent(
          PhysicsComponent::CharacterBody(pos_x, pos_y, 24, 24, 0.1f),
          message_bus))
      ->addSprite(new SpriteComponent(message_bus, texture, 24, 28, 24, 28,
                                      {6, 6}, 100, 4))
      ->addSpritePhysics(
          new SpritePhysicsHandler(message_bus, PlayerMovementHandler))
      ->getEntity();
}

template <typename ...Args>
Entity* EntityFactory::createEntityFromEnum(EntityFactoryType type, Args&& ...args) {
    switch (type) {
    case ENTITYFACTORY_PLAYER:
        return createPlayer(std::forward<Args>(args)...);
    case ENTITYFACTORY_TILE:
        return createTile(std::forward<Args>(args)...);
    default:
        return NULL;
    }
}