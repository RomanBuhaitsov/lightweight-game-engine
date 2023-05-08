#pragma once

#include "../IO/io_manager.h"
#include "../game_window/game_window.h"
#include "../level/manager.h"
#include "../message_bus/bus.h"
#include "../texture_manager/texture_manager.h"
#include "../audio_manager/audio_manager.h"

class GameLoop : public BusNode {
private:
  int framerate;
  int max_frameskip;
  int skip_ticks;
  LevelManager *levels;
  MessageBus *message_bus;
  IOManager *io;
  GameWindow *window;
  TextureManager *texture_manager;
  AudioManager *audio_manager;

protected:
  bool game_running; // TODO: consider moving this field to a more global scope
  virtual void onNotify(Message message);

public:
  GameLoop(LevelManager *levels, MessageBus *message_bus, IOManager *io,
           GameWindow *window, TextureManager* texture_manager, AudioManager* audio_manager, 
           int framerate, int max_frameskip);
  ~GameLoop(){};
  virtual void update(){};

  void run();
};
