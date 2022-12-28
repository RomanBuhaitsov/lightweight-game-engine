#include "LGE/LGE_GameWindow.h"
#include <fmt/format.h>
#include <iostream>

int main(int argc, char **argv) {
  LGE_GameWindow gameWindow("LGE Test", 1280, 720, false);
  gameWindow.gameLoop();
  return 0;
}
