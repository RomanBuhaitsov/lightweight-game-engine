#include "../entity/factory.h"

#include "levels.h"
#include "../audio/audio_component.h"

Level1::Level1(GameWindow *game_window, MessageBus *message_bus)
    : Level("Level One", game_window, message_bus) {}

void Level1::init() {
  SDL_Texture *background =
      this->getGameWindow()->texture_manager["background.png"];
  this->getGameWindow()->setBackgroundTexture(background);
  this->getGameWindow()->getDebugDraw()->SetFlags(b2Draw::e_shapeBit);
  this->getGameWindow()->world->SetDebugDraw(
      this->getGameWindow()->getDebugDraw());

  Entity *player = EntityFactory::createPlayer(
      0, 0, this->getGameWindow()->texture_manager["crudewalk.png"],
      this->getGameWindow()->getMessageBus());
  this->getGameWindow()->entities.insert(player);
  this->getGameWindow()->getCamera()->followEntity(
      player, true); // make the camera follow the player
 
  Entity *campfire = EntityFactory::createAnimation(
    320, 416, this->getGameWindow()->texture_manager["fire.png"],
    this->getGameWindow()->getMessageBus(), 100, {3,1});
  this->getGameWindow()->entities.insert(campfire);
  AudioComponent ac = AudioComponent(this->getGameWindow()->getMessageBus());
  ac.addMusicTrack("campfire.wav");
  // campfire->addComponent();
  // AudioComponent *campfire->getComponent(ComponentType::CT_AUDIO);
  

  for (int i = 0; i < 32; ++i) {
    int pos_x = i * 32 - 1;
    int pos_y = 448;
    this->getGameWindow()->entities.insert(EntityFactory::createTile(
        pos_x, pos_y, this->getGameWindow()->texture_manager["grasstile.png"],
        this->getGameWindow()->getMessageBus()));
  }

  for (int i = 0; i < 28; ++i) {
    int pos_x = (i + 28) * 32 - 1;
    int pos_y = 448 + i * 32;
    this->getGameWindow()->entities.insert(EntityFactory::createTile(
        pos_x, pos_y, this->getGameWindow()->texture_manager["grasstile.png"],
        this->getGameWindow()->getMessageBus()));
  }
}

void Level1::reset() {
  for (Entity *gent : this->getGameWindow()->entities) {
    this->getGameWindow()->removeEntity(gent);
  }
  this->getGameWindow()->clear();
}

void Level1::update() {}

void Level1::onNotify(Message message) {}

Level1::~Level1() { this->reset(); }
