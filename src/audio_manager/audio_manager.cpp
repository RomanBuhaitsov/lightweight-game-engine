//#include <SDLInit.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include "../log.h"

AudioManager::AudioManager(const std::string& dir){
    //TODO: init AM
    music_playing = false;
    music_paused = false;
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot initialize audio: %s", Mix_GetError());
        return;
    }
    loadSound(dir+"/music");
    loadSound(dir+"/sound_effects");
}


void AudioManager::loadMusic(const std::filesystem::path &dir, bool ignoreDirs)
{
    if (!std::filesystem::exists(dir)) {
        LogError << "Cannot find directory " << dir << ". AudioManager has not been loaded.\n";
        return;
    }
    for (const auto &f : std::filesystem::directory_iterator(dir))
    {
        if (f.is_directory()){
            if (!ignoreDirs){
                load(f.path(), false);
            }
            continue;
        }
//        TODO: load music
        addMusicTrack(f.filename().c_str(), f.path().string().c_str());
    }
}


AudioManager::~AudioManager(){
    //TODO: clean all sfx and music tracks
    SDL_Quit();
}

AudioManager::addSoundEffect(const std::string sfxTitle, const std::filesystem::path &dir){
    Mix_Music* track = Mix_LoadMUS(path);
    if (track != nullptr) {
        music.insert({ trackTitle, path });
        std::cout << "Sound effect ready at : " << path << '\n';
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load soundeffect : %s", Mix_GetError());
    }
}

AudioManager::playSoundEffect(const std::string sfxTitle){
    if (music.count(trackTitle) == 0) {
        return;
    }

    Mix_PlayMusic(music.find(trackTitle), -1);
}

AudioManager::addMusicTrack(const std::string trackTitle, const std::filesystem::path & path){
    Mix_Chunk* chunk = Mix_LoadMUS(path);
    if (chunk != nullptr){
        sound_effects.insert({ trackTitle, path });
        std::cout <<"Music track ready at : " << path << '\n';
    }
    else{
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load track : %s", Mix_GetError());
    }
}

AudioManager::playMusicTrack(const std::string trackTitle){
    if (music.count(trackTitle) == 0) {
        return;
    }

    Mix_PlayMusic(music.find(trackTitle), -1);
    music_playing = true;
}

AudioManager::pauseTrack(){
    if (music_playing && !music_paused){
        Mix_PauseMusic();
        music_paused = true;
    }
    else if (music_playing && music_paused){
        Mix_ResumeMusic();
        music_paused = false;
    }
    else{
        return;
    }
}



