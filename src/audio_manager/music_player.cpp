#include "music_player.h"
#include "../log.h"


MusicPlayer::MusicPlayer(){
    music_playing = false;
    music_paused = false;
}

MusicPlayer::~MusicPlayer(){
    for(std::map<std::string, Mix_Music*>::iterator itr = music.begin(); itr != music.end(); itr++){
        delete itr->second;
    }
}

void MusicPlayer::addMusicTrack(const std::string trackTitle,  const char* path){
    Mix_Music* track = Mix_LoadMUS(path);
    if (track != nullptr){
        music.insert({ trackTitle, track });
        std::cout <<"Music track ready at : " << path << '\n';
    }
    else{
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load track : %s", Mix_GetError());
    }
}

void MusicPlayer::playMusicTrack(const std::string trackTitle){
    if (music.count(trackTitle) == 0) {
        LogError << "Cannot find music track '" << trackTitle << "'.\n";
        return;
    }
    if (music_playing && music_paused){
        pauseTrack();
        return;
    }
    Mix_Music* track = music.find(trackTitle)->second;
    Mix_PlayMusic(track, -1);
    music_playing = true;
}

void MusicPlayer::pauseTrack(){
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