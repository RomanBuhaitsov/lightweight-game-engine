#include "audio_manager.h"
#include "../log.h"

AudioManager::AudioManager(MessageBus *message_bus) : BusNode(message_bus){
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot initialize audio: %s", Mix_GetError());
        return;
    }  
    music_player.addMusicTrack("campfire","src/static/sound/music/campfire.wav");
    sfx_player.addSoundEffect("ui_click","src/static/sound/sound_effects/ui_click.wav");
    sfx_player.addSoundEffect("coin","src/static/sound/sound_effects/coin.wav");
}

void AudioManager::loadMusic(const std::filesystem::path &dir, bool ignoreDirs){
  "src/static/sound/music/";
    // TODO: add option to load music based on config (either to load all 
    // music in /music directory or every track in music config file)
}


void AudioManager::onNotify(const Message & message) {
  switch (message.getEvent()) {
  case MessageEvent::PLAY_SOUND_EFFECT:
    sfx_player.playSoundEffect(convertAudioData(message["audio"]));
    break;
  case MessageEvent::PLAY_MUSIC_TRACK:
    music_player.playMusicTrack(convertAudioData(message["audio"]));
    break;
  case MessageEvent::PAUSE_MUSIC_TRACK:
    music_player.pauseTrack();
    break;
  default:
    break;
  }
}



std::string AudioManager::convertAudioData(std::any title){
    if (title.type() != typeid(std::string)) {
        LogError << "Title has to be a string. Instead, got " << title.type().name() << "\n";
        return std::string();
    }
    return std::any_cast<std::string>(title);
}
