#include "renderer.h"
#include "LGE_InputOutput.h"

bool WindowRenderer::SDL_initialized = false;
int WindowRenderer::LGE_numInstances = 0;

WindowRenderer::WindowRenderer(const char *title, int width, int height, bool fullscreen) : window(NULL), renderer(NULL), init(false)
{
  if (!SDL_initialized)
  {
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
      LGE_LogError << "Failed to initialize SDL, error: " << SDL_GetError() << "\n";
      return;
    }
    SDL_initialized = true;
  }
  int flags = fullscreen ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN : SDL_WINDOW_SHOWN;
  if ((window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)) == NULL)
  {
    LGE_LogError << "SDL_CreateWindow failed to initialize, error: " << SDL_GetError() << "\n";
    return;
  }
  if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
  {
    LGE_LogError << "SDL_CreateRenderer failed to initialize, error: " << SDL_GetError() << "\n";
    SDL_DestroyWindow(window);
    return;
  }
  init = true;
  ++LGE_numInstances;
}

WindowRenderer::~WindowRenderer()
{
  if (init)
  {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    --LGE_numInstances;
  }
  if (SDL_initialized && LGE_numInstances == 0)
  {
    SDL_Quit();
    SDL_initialized = false;
  }
}

bool WindowRenderer::isInitialized() { return init; }

SDL_Texture *WindowRenderer::loadTexture(const char *filepath)
{
  SDL_Texture *texture = IMG_LoadTexture(renderer, filepath);
  if (texture == NULL)
  {
    LGE_LogError << "IMG_LoadTexture failed, error: " << SDL_GetError() << "\n";
  }
  return texture;
}

void WindowRenderer::destroyTexture(SDL_Texture *texture)
{
  SDL_DestroyTexture(texture);
}

void WindowRenderer::clear()
{
  SDL_RenderClear(renderer);
}

void WindowRenderer::renderTexture(SDL_Texture *texture, const SDL_Rect src, const SDL_Rect dst)
{
  SDL_RenderCopy(renderer, texture, &src, &dst);
}

void WindowRenderer::renderTexture(SDL_Texture *texture, const SDL_Rect src, const SDL_Rect dst,
                                   const double angle,
                                   const SDL_Point *center,
                                   const SDL_RendererFlip flip)
{
  SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, center, flip);
}

void WindowRenderer::present()
{
  SDL_RenderPresent(renderer);
}

void WindowRenderer::getSize(int &width, int &height)
{
  SDL_GetWindowSize(window, &width, &height);
}