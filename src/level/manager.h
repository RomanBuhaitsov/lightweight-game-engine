#pragma once

#include "level.h"

class LevelManager : public BusNode {
private:
  Level *current_level;

protected:
  virtual void onNotify(Message message);

public:
  LevelManager(Level *current_level, MessageBus *message_bus);
  ~LevelManager();

  void start();
  void next();
  void prev();

  virtual void update(){};
};
