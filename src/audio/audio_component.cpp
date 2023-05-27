#include "audio_component.h"
#include "../log.h"

AudioComponent::AudioComponent(MessageBus *message_bus): 
	Component(ComponentType::CT_AUDIO, message_bus) {}

void AudioComponent::addSoundEffect(const std::string sfxTitle)
{
	sound_effects.insert(sfxTitle);
}

void AudioComponent::addMusicTrack(const std::string title)
{
	music_tracks.insert(title);
}

const void AudioComponent::playSoundEffect(const std::string sfxTitle){
	if(sound_effects.count(sfxTitle)==0){
		LogError << "Audio Component does not contain " << sfxTitle << ".\n";
		return;
	}
	Message message(MessageEvent::PLAY_SOUND_EFFECT);
	message.getData()["music"] = sfxTitle;
	this->send(message);
}

const void AudioComponent::playMusicTrack(const std::string trackTitle)
{
    if(music_tracks.count(trackTitle)==0){
		LogError << "Audio Component does not contain " << trackTitle << ".\n";
		return;
	}
	Message message(MessageEvent::PLAY_MUSIC_TRACK);
	message.getData()["music"] = trackTitle;
	this->send(message);
}
