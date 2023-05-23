#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <filesystem>

class MusicPlayer {
private:
	std::map<std::string, Mix_Music*> music;
    bool music_playing, music_paused;
public:
    MusicPlayer();
    void addMusicTrack(const std::string trackTitle, const char *path);
    void playMusicTrack(const std::string trackTitle);
    void pauseTrack();
    ~MusicPlayer();
};