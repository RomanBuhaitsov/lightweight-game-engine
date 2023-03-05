#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LGE_RenderWindow
{
protected:
  static bool SDL_initialized;
  static int LGE_numInstances;

  SDL_Window *window;
  SDL_Renderer *renderer;
  bool init;

public:
  LGE_RenderWindow(const char *title, int width, int height, bool fullscreen);
  ~LGE_RenderWindow();
  bool isInitialized();

  SDL_Texture *loadTexture(const char *filepath);
  void clear();
  void renderTexture(SDL_Texture *texture);
  void present();
};
