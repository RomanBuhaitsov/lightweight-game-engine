
#include "../entity/builder.h"
#include <iostream>

#include "SDL2/SDL.h"

#include "factory.h"

#define ENUM2STRING(x) #x

const std::string EntityFactory::enumString[ENTITYFACTORY_MAX + 1] = {
    ENUM2STRING(ENTITYFACTORY_PLAYER),
    ENUM2STRING(ENTITYFACTORY_TILE),
    ENUM2STRING(ENTITYFACTORY_COIN),
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

Entity *EntityFactory::createAnimation(int pos_x, int pos_y, SDL_Texture *texture,
                                    MessageBus *message_bus, int animation_speed, 
                                    const std::initializer_list<Uint16> &numFrames, 
                                    std::string track_title) {
  return (new EntityBuilder(EntityType::ET_GENERIC))
      ->addPhysics(new PhysicsComponent(
          PhysicsComponent::TileBody(pos_x, pos_y, 96, 96, 0.8f),
           [track_title](Entity* self, Entity* other, MessageBus* message_bus) {
                if (other->getType() == EntityType::ET_PLAYER) {
                    Message message(MessageEvent::PLAY_MUSIC_TRACK);
                    message.getData()["audio"] = track_title;
                    message_bus->sendMessage(message);
                }
            },
            [](Entity* self, Entity* other, MessageBus* message_bus) {
                if (other->getType() == EntityType::ET_PLAYER) {
                    Message message(MessageEvent::PAUSE_MUSIC_TRACK);
                    message_bus->sendMessage(message);
                }
            },
            [](Entity* other) {
                return (other->getType() != EntityType::ET_PLAYER); //player won't briefly get stuck on a coin before the touch function destroys the latter
            }, message_bus))
      ->addSprite(new SpriteComponent(message_bus, texture, 24, 28, 24, 28,
                                      numFrames, animation_speed, 4))
      ->addSpritePhysics(new SpritePhysicsHandler(message_bus))
      ->getEntity();
}

Entity* EntityFactory::createCoin(int pos_x, int pos_y, SDL_Texture* texture,
    MessageBus* message_bus) {
    return (new EntityBuilder(EntityType::ET_COLLECTIBLE))
        ->addPhysics(new PhysicsComponent(
            PhysicsComponent::TileBody(pos_x, pos_y, 16, 16, 0.1f),
            //custom touch function
            [](Entity* self, Entity* other, MessageBus* message_bus) {
                if (other->getType() == EntityType::ET_PLAYER) {
                    Message remove_coin(MessageEvent::ENTITY_REMOVE);
                    remove_coin.getData()["entity"] = self;
                    message_bus->sendMessage(remove_coin);
                    Message play_sound(MessageEvent::PLAY_SOUND_EFFECT);
                    play_sound.getData()["audio"] = std::string("coin");
                    message_bus->sendMessage(play_sound);
                }
            },
            [](Entity* self, Entity* other, MessageBus* message_bus){}, //no need for detach function
            //custom can_collide
            [](Entity* other) {
                return (other->getType() != EntityType::ET_PLAYER); //player won't briefly get stuck on a coin before the touch function destroys the latter
            }, message_bus))
            ->addSprite(new SpriteComponent(message_bus, texture, 16, 16, 32, 32, { 4 }, 100, 8))
            ->addSpritePhysics(new SpritePhysicsHandler(message_bus))
        ->getEntity();
}