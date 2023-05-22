#pragma once

#include <string>
#include <filesystem>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioManager
{
private:
	std::map<std::string, Mix_Chunk*> sound_effects;
	std::map<std::string, Mix_Music*> music;
    bool music_playing, music_paused;
    void loadMusic(const std::filesystem::path &dir, bool ignoreDirs);
public:
    AudioManager(const std::string& dir = "src/static/sound");
    void addMusicTrack(const std::string trackTitle, const char *path);
    void addSoundEffect(const std::string sfxTitle, const char* path);
    void playMusicTrack(const std::string trackTitle);
    void playSoundEffect(const std::string sfxTitle);
    void pauseTrack();
    ~AudioManager();
};