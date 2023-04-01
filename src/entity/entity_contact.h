#pragma once
#include "../entity/entity.h"
#include "../entity/entity_type.h"
#include "../game_window/game_window.h"

class EntityContactListener : public b2ContactListener
{
private:
  GameWindow *m_game;

public:
  EntityContactListener(GameWindow *game);
  void BeginContact(b2Contact *contact);
  void EndContact(b2Contact *contact);
};
