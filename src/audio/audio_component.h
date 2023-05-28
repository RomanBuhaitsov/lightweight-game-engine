#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../component/component.h"
#include "../audio_manager/audio_manager.h"

class AudioComponent : public Component {
public:
	// AudioComponent(MessageBus *message_bus);
	AudioComponent(MessageBus *message_bus, std::function<void(Entity *, Entity *, MessageBus*)> touch);
	void addSoundEffect(const std::string title);
	void addMusicTrack(const std::string title);
	const void playSoundEffect(const std::string title);
	const void playMusicTrack(const std::string title);
  	std::function<void(Entity *, Entity*, MessageBus*)> touch;
private:
	std::set<std::string> sound_effects;
	std::set<std::string> music_tracks;
};
	