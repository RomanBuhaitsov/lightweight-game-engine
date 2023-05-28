#include "sfx_player.h"
#include "../log.h"

void SfxPlayer::addSoundEffect(const std::string sfxTitle, const char* path){
    Mix_Chunk* chunk = Mix_LoadWAV(path);
    if (chunk != nullptr) {
        sound_effects.insert({ sfxTitle, chunk });
        Log << "Sound effect ready at : " << path << '\n';
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot load soundeffect : %s", Mix_GetError());
    }
}

void SfxPlayer::playSoundEffect(const std::string sfxTitle){
    if (sound_effects.count(sfxTitle) == 0) {
        LogError << "Cannot find sound effect '" << sfxTitle << "'.\n";
        return;
    }
    Mix_Chunk* sfx = sound_effects.find(sfxTitle)->second;
    Mix_PlayChannel(-1, sfx, 0);
}

SfxPlayer::~SfxPlayer(){
    for(std::map<std::string, Mix_Chunk*>::iterator itr = sound_effects.begin(); itr != sound_effects.end(); itr++){
        delete itr->second;
    }
}