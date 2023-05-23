#include "audio_component.h"


AudioComponent::AudioComponent(MessageBus *message_bus): 
	Component(ComponentType::CT_AUDIO, message_bus) {}


void AudioComponent::addSoundEffect(const std::string trackTitle, const std::string path)
{
	sound_effects_paths.insert({ trackTitle, path });
}

const void AudioComponent::playSoundEffect(const std::string id)
{
	// audio_manager->playSoundEffect(id);
	// TODO: use Message bus
}
