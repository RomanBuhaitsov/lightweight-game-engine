#include "texture_manager.h"
#include "../log.h"

TextureManager::TextureManager(WindowRenderer *render, const std::string &dir, bool ignoreDirs) : render(render)
{
  std::filesystem::path p(dir);
  load(p, ignoreDirs);
}

SDL_Texture *TextureManager::operator[](const std::string &name) const
{
  auto tex = textureAssets.find(name);
  if (tex == textureAssets.end())
  {
    return NULL;
  }
  return tex->second;
}

TextureManager::~TextureManager()
{
  for (auto &it : textureAssets)
  {
    render->destroyTexture(it.second);
  }
}

void TextureManager::load(const std::filesystem::path &dir, bool ignoreDirs)
{
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
    SDL_Texture *tex = render->loadTexture(f.path().string().c_str());
    if (tex != NULL)
    {
      Log << "Loading texture " << f << '\n';
      textureAssets.insert(std::make_pair(f.path().filename().string(), tex));
    }
    else
    {
      LogError << "Couldn't load texture" << f << '\n';
    }
  }
}
