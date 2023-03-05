#include <fmt/format.h>
#include <iostream>

#include "game_loop/game_loop.h"
#include "LGE/LGE_GameWindow.h"
#include "config.cpp"

int main(int argc, char **argv)
{
  GameLoop *loop = new GameLoop(FRAMERATE, MAX_FRAMESKIP);
  loop->run();

  delete loop;
  return 0;
}
