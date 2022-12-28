#include "LGE_RenderWindow.h"
#include "LGE_InputOutput.h"

bool LGE_RenderWindow::SDL_initialized = false;
int LGE_RenderWindow::LGE_numInstances = 0;

LGE_RenderWindow::LGE_RenderWindow(const char *title, int width, int height,
                                   bool fullscreen)
    : window(NULL), renderer(NULL), init(false) {
  if (!SDL_initialized) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
      LGE_logError << "Failed to initialize SDL, error: " << SDL_GetError()
                   << "\n";
      return;
    }
    SDL_initialized = true;
  }
  int flags =
      fullscreen ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN : SDL_WINDOW_SHOWN;
  if ((window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height,
                                 flags)) == NULL) {
    LGE_logError << "SDL_CreateWindow failed to initialize, error: "
                 << SDL_GetError() << "\n";
    return;
  }
  if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) ==
      NULL) {
    LGE_logError << "SDL_CreateRenderer failed to initialize, error: "
                 << SDL_GetError() << "\n";
    SDL_DestroyWindow(window);
    return;
  }
  init = true;
  ++LGE_numInstances;
}

LGE_RenderWindow::~LGE_RenderWindow() {
  if (init) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    --LGE_numInstances;
  }
  if (SDL_initialized && LGE_numInstances == 0) {
    SDL_Quit();
    SDL_initialized = false;
  }
}

bool LGE_RenderWindow::isInitialized() { return init; }

SDL_Texture *LGE_RenderWindow::loadTexture(const char *filepath) {
  SDL_Texture *texture = IMG_LoadTexture(renderer, filepath);
  if (texture == NULL) {
    LGE_logError << "IMG_LoadTexture failed, error: " << SDL_GetError() << "\n";
  }
  return texture;
}

void LGE_RenderWindow::clear() { SDL_RenderClear(renderer); }

void LGE_RenderWindow::renderTexture(
    SDL_Texture *texture) { // todo: position, size
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void LGE_RenderWindow::present() { SDL_RenderPresent(renderer); }
