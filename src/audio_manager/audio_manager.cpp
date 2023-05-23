#include "audio_manager.h"
#include "../log.h"
#include "sfx_player.h"
#include "music_player.h"

void AudioManager::loadMusic(const std::filesystem::path &dir, bool ignoreDirs){
    // TODO: add option to load music based on config (either to load all 
    // music in /music directory or every track in music config file)
}

AudioManager::~AudioManager()
{
    music_player.~MusicPlayer();
    sfx_player.~SfxPlayer();
}

void AudioManager::onNotify(Message message) {
  switch (message.getEvent()) {
  case MessageEvent::PLAY_SOUND_EFFECT:
    sfx_player.playSoundEffect(message.getData());
    break;
  case MessageEvent::PLAY_MUSIC_TRACK:
    music_player.playMusicTrack(message.getData());
    break;
  default:
    break;
  }
}


