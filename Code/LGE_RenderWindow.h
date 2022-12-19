#pragma once
#include <SDL.h>
#include <SDL_image.h>

class LGE_RenderWindow {
protected:
	static bool SDL_initialized;
	static int LGE_numInstances;

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool init;
public:
	LGE_RenderWindow(const char* title, int width, int height, bool fullscreen);
	~LGE_RenderWindow();
	bool isInitialized();

	SDL_Texture* loadTexture(const char* filepath);
	void clear();
	void renderTexture(SDL_Texture* texture, const SDL_Rect & src, const SDL_Rect & dst);
	void renderTexture(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dst,
		const double& angle,
		const SDL_Point* center,
		const SDL_RendererFlip& flip);
	void present();
	void getSize(int & width, int & height);
};