#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include "../renderer/renderer.h"

class TextureManager
{
private:
  std::unordered_map<std::string, SDL_Texture *> *textureAssets;
  void load(const std::filesystem::path &dir, bool ignoreDirs);
  WindowRenderer *renderer;

public:
  TextureManager(WindowRenderer *game, const std::string &dir = "src/static/textures", bool ignoreDirs = false);
  SDL_Texture *operator[](const std::string &name) const;
  ~TextureManager();
};
