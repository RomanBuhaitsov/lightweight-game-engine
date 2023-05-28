#include "audio_manager.h"
#include "../log.h"

AudioManager::AudioManager(MessageBus *message_bus) : BusNode(message_bus){
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot initialize audio: %s", Mix_GetError());
        return;
    }  
    music_player.addMusicTrack("farewell","src/static/sound/music/campfire.wav");
    sfx_player.addSoundEffect("ui_click","src/static/sound/sound_effects/ui_click.wav");
    sfx_player.addSoundEffect("coin","src/static/sound/sound_effects/coin.wav");
}

void AudioManager::loadMusic(const std::filesystem::path &dir, bool ignoreDirs){
    // TODO: add option to load music based on config (either to load all 
    // music in /music directory or every track in music config file)
}

AudioManager::~AudioManager(){
    music_player.~MusicPlayer();
    sfx_player.~SfxPlayer();
}

void AudioManager::onNotify(const Message & message) {
  std::string key("audio");
  std::cout << "AudioManager1\n";
// std::cout << whichEvent(message.getEvent(0)) << "\n";
  if(!message.dataExists(key))
    return;

  std::cout << "AudioManager2\n";
  
  std::string title = convertAudioData(message.getData(key));
  if(title.empty())
    return;

  std::cout << "AudioManager3\n";
  switch (message.getEvent()) {
  case MessageEvent::PLAY_SOUND_EFFECT:
    sfx_player.playSoundEffect(title);
    break;
  case MessageEvent::PLAY_MUSIC_TRACK:
    music_player.playMusicTrack(title);
    break;
  default:
    break;
  }
}



std::string AudioManager::convertAudioData(std::any title){
    if(title.type()!=typeid(std::string)){
        LogError << "Title has to be a string. Instead, got " << title.type().raw_name() << "\n";
        return std::string();
    }
    return std::any_cast<std::string>(title);
}
