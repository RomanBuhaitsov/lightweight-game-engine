#include "../renderer/renderer.h"
#include "../log.h"

#include "texture_manager.h"

TextureManager::TextureManager(WindowRenderer *render, const std::string &dir, bool ignoreDirs) : renderer(render)
{
  this->textureAssets = new std::map<std::string, SDL_Texture *>();
  Log << "size " << textureAssets->size() << std::endl;
  std::filesystem::path p(dir);
  load(p, ignoreDirs);
}

SDL_Texture *TextureManager::operator[](const std::string &name) const
{
  Log << "hai" << std::endl;
  Log << "size " << textureAssets << std::endl;
  for (auto &it : *textureAssets)
  {
    Log << it.first << std::endl;
  }
  Log << "hai1" << std::endl;
  auto tex = textureAssets->find(name);
  if (tex == textureAssets->end())
  {
    return NULL;
  }
  return tex->second;
}

TextureManager::~TextureManager()
{
  for (auto &it : *textureAssets)
  {
    renderer->destroyTexture(it.second);
  }
  delete textureAssets;
}

void TextureManager::load(const std::filesystem::path &dir, bool ignoreDirs)
{
  if (!std::filesystem::exists(dir)) {
    LogError << "Couldn't find directory " << dir << ". textureManager has not been loaded.\n";
    return;
  }
  for (const auto &f : std::filesystem::directory_iterator(dir))
  {
    if (f.is_directory())
    {
      if (!ignoreDirs)
      {
        load(f.path(), false);
      }
      continue;
    }
    SDL_Texture *tex = renderer->loadTexture(f.path().string().c_str());
    if (tex != NULL)
    {
      Log << "Loading texture " << f << '\n';
      textureAssets->insert(std::make_pair(f.path().filename().string(), tex));
    }
    else
    {
      LogError << "Couldn't load texture" << f << '\n';
    }
  }
}
