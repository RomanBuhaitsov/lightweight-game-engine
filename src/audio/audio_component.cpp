#include "audio_component.h"


//AudioComponent::AudioComponent(AudioManager& audio_manager) {
//	this->audio_manager = audio_manager;
//}

AudioComponent::AudioComponent(const AudioManager& audio_manager, MessageBus message_bus)
{
	this->audio_manager = audio_manager;
	this
}

void AudioComponent::addSoundEffect(const std::string trackTitle, const std::string path)
{
	sound_effects_paths.insert({ trackTitle, path });
}

void AudioComponent::playSoundEffect(const std::string id)
{
	audio_manager.playSoundEffect(id);
}
