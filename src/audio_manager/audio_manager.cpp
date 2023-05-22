//#include <SDLInit.h>
#include "audio_manager.h"
#include "../log.h"

void AudioManager::loadMusic(const std::filesystem::path &dir, bool ignoreDirs){
    // TODO: add option to load music based on config (either to load all 
    // music in /music directory or every track in music config file)
}

AudioManager::AudioManager(const std::string& dir){
    //TODO: init AM
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    music_playing = false;
    music_paused = false;
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot initialize audio: %s", Mix_GetError());
        return;
    }
    // loadMusic(dir+"/music");
    // loadSound(dir+"/sound_effects");
}

AudioManager::~AudioManager(){
    //TODO: clean all sfx and music tracks
    for(std::map<std::string, Mix_Chunk*>::iterator itr = sound_effects.begin(); itr != sound_effects.end(); itr++)
    {
        delete itr->second;
    }
    for(std::map<std::string, Mix_Music*>::iterator itr = music.begin(); itr != music.end(); itr++)
    {
        delete itr->second;
    }
    SDL_Quit();
}

void AudioManager::addSoundEffect(const std::string sfxTitle, const char* path){
    Mix_Chunk* chunk = Mix_LoadWAV(path);
    if (chunk != nullptr) {
        sound_effects.insert({ sfxTitle, chunk });
        std::cout << "Sound effect ready at : " << path << '\n';
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load soundeffect : %s", Mix_GetError());
    }
}

void AudioManager::addMusicTrack(const std::string trackTitle,  const char* path){
    Mix_Music* track = Mix_LoadMUS(path);
    if (track != nullptr){
        music.insert({ trackTitle, track });
        std::cout <<"Music track ready at : " << path << '\n';
    }
    else{
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load track : %s", Mix_GetError());
    }
}

void AudioManager::playSoundEffect(const std::string sfxTitle){
    if (music.count(sfxTitle) == 0) {
        LogError << "Cannot find sound effect '" << sfxTitle << "'.\n";
        return;
    }
    Mix_Chunk* sfx = sound_effects.find(sfxTitle)->second;
    Mix_PlayChannel(-1, sfx, 0);
}

void AudioManager::playMusicTrack(const std::string trackTitle){
    if (music.count(trackTitle) == 0) {
        LogError << "Cannot find music track '" << trackTitle << "'.\n";
        return;
    }

    Mix_Music* track = music.find(trackTitle)->second;
    Mix_PlayMusic(track, -1);
    music_playing = true;
}

void AudioManager::pauseTrack(){
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
