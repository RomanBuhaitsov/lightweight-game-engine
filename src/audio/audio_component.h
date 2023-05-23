#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../component/component.h"
#include "../audio_manager/audio_manager.h"

class AudioComponent : public Component {
public:
	AudioComponent(MessageBus *message_bus);
	void addSoundEffect(const std::string name, const std::string path);
	const void playSoundEffect(const std::string id);
private:
	std::unordered_map<std::string, std::string> sound_effects_paths = std::unordered_map<std::string, std::string>();
};
	