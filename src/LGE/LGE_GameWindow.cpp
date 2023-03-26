#include "LGE_GameWindow.h"

LGE_GameWindow::LGE_GameWindow(const char *title, int width, int height,
                               bool fullscreen)
    : LGE_RenderWindow(title, width, height, fullscreen){};

void LGE_GameWindow::gameLoop()
{
  SDL_Texture *t = loadTexture("textures/placeholder.png");
  bool gameLoop = true;
  SDL_Event ev;
  do
  {
    while (SDL_PollEvent(&ev))
    {
      switch (ev.type)
      {
      case SDL_QUIT:
        gameLoop = false;
        break;
      }
    }
    clear();
    renderTexture(t);
    present();
  } while (gameLoop);
}
