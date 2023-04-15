#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class AudioComponent : public Component {
public:
	AudioComponent(const AudioManager & audio_manager) : Component(ComponentType::CT_AUDIO);
	void addSoundEffect(const std::string name, const std::string path);
	void playSoundEffect(const std::string id);
private:
	std::unordered_map<std::string, std::string> sound_effects_paths = std::unordered_map<std::string, std::string>();
	audio_manager;
};
	