#pragma once
#include <string>
#include <filesystem>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioManager {
private:
	std::map<std::string, std::string> sound_effects;
	std::map<std::string, std::string> music;
    bool music_playing, music_paused;
public:
    AudioManager(const std::string& dir = "src/static/sound");
    void addMusicTrack(const std::string trackTitle, const std::filesystem::path &dir);
    void addSoundEffect(const std::string sfxTitle, const std::filesystem::path &dir);
    void playMusicTrack(const std::string trackTitle);
    void playSoundEffect(const std::string sfxTitle);
    void pauseTrack();
};