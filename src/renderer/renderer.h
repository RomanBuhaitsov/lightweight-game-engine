#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class WindowRenderer
{
protected:
  static bool SDL_initialized;
  static int num_instances;

public:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool init;
  WindowRenderer(const char *title, int width, int height, bool fullscreen);
  ~WindowRenderer();
  bool isInitialized();

  SDL_Texture *loadTexture(const char *filepath);
  void destroyTexture(SDL_Texture *texture);
  void clear();
  void renderTexture(SDL_Texture *texture, const SDL_Rect src, const SDL_Rect dst);
  void renderTexture(SDL_Texture *texture, const SDL_Rect src, const SDL_Rect dst,
                     const double angle,
                     const SDL_Point *center,
                     const SDL_RendererFlip flip);
  void present();
  void getSize(int &width, int &height);
};
