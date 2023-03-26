#pragma once
#include <string>
#include <filesystem>
#include <map>
#include "LGE_RenderWindow.h"

class LGE_TextureManager {
private:
	std::map<std::string, SDL_Texture*> textureAssets;
	void load(const std::filesystem::path& dir, bool ignoreDirs);
	LGE_RenderWindow* render;
public:
	LGE_TextureManager(LGE_RenderWindow *game, const std::string& dir = "./textures/", bool ignoreDirs = false);
	SDL_Texture* operator[](const std::string& name) const;
	~LGE_TextureManager();
};