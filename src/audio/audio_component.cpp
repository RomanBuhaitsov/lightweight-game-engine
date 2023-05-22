#include "audio_component.h"


//AudioComponent::AudioComponent(AudioManager& audio_manager) {
//	this->audio_manager = audio_manager;
//}

AudioComponent::AudioComponent(AudioManager* audio_manager, MessageBus *message_bus): 
	Component(ComponentType::CT_AUDIO, message_bus), audio_manager(audio_manager) {}


void AudioComponent::addSoundEffect(const std::string trackTitle, const std::string path)
{
	sound_effects_paths.insert({ trackTitle, path });
}

const void AudioComponent::playSoundEffect(const std::string id)
{
	audio_manager->playSoundEffect(id);
}
