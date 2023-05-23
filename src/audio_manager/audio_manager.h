#pragma once

#include "../message_bus/node.h"

class AudioManager: public BusNode {
private:
    SfxPlayer sfx_player;
    MusicPlayer music_player;
    virtual void onNotify(Message message);
	std::map<std::string, Mix_Chunk*> sound_effects;
    void loadMusic(const std::filesystem::path &dir, bool ignoreDirs);
public:
    AudioManager(MessageBus *message_bus);
    ~AudioManager();
};