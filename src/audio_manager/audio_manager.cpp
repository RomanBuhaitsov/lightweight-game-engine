#include "audio_manager.h"
#include "../log.h"

AudioManager::AudioManager(MessageBus *message_bus) : BusNode(message_bus){
    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot initialize audio: %s", Mix_GetError());
        return;
    }  
    music_player.addMusicTrack("farewell","../static/sound/music/farewell.mp3");
    music_player.addMusicTrack("farewell","../static/sound/music/campfire.mp3");
    sfx_player.addSoundEffect("ui_click","../static/sound/sound_effects/ui_click.wav");
    sfx_player.addSoundEffect("jump","../static/sound/sound_effects/cartoon_jump.mp3");
}

void AudioManager::loadMusic(const std::filesystem::path &dir, bool ignoreDirs){
    // TODO: add option to load music based on config (either to load all 
    // music in /music directory or every track in music config file)
}

AudioManager::~AudioManager(){
    music_player.~MusicPlayer();
    sfx_player.~SfxPlayer();
}

void AudioManager::onNotify(Message message) {
  if(message.getData().count("audio") == 0)
    return;

  std::string title = convertAudioData(message.getData().find("music_track")->second);
  if(title.empty())
    return;

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

std::string convertAudioData(std::any title){
    if(title.type()!=typeid(std::string)){
        LogError << "Title has to be a string. Instead, got " << title.type().raw_name() << "\n";
        return std::string();
    }
    return std::any_cast<std::string>(title);
}


