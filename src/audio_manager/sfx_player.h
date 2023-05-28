#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <filesystem>

class SfxPlayer {
private:
	std::map<std::string, Mix_Chunk*> sound_effects;
public:
    void addSoundEffect(const std::string sfxTitle, const char* path);
    void playSoundEffect(const std::string sfxTitle);
    ~SfxPlayer();
};