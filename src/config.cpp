#include <stdlib.h>

class Config
{
private:
  int framerate = atoi(getenv("FRAMERATE"));
  int max_frameskip = atoi(getenv("MAX_FRAMESKIP"));
  bool fullscreen = atoi(getenv("FULLSCREEN"));
  int window_width = atoi(getenv("WINDOW_WIDTH"));
  int window_height = atoi(getenv("WINDOW_HEIGHT"));

public:
  void setFramerate(int framerate)
  {
    this->framerate = framerate;
  }

  int getFramerate()
  {
    return this->framerate;
  }

  void setMaxFrameSkip(int max_frameskip)
  {
    this->max_frameskip = max_frameskip;
  }

  int getMaxFrameSkip()
  {
    return this->max_frameskip;
  }

  void setFullScreen(bool fullscreen)
  {
    this->fullscreen = fullscreen;
  }

  bool getFullScreen()
  {
    return this->fullscreen;
  }

  void setWindowWidth(int window_width)
  {
    this->window_width = window_width;
  }

  int getWindowWidth()
  {
    return this->window_width;
  }

  void setWindowHeight(int window_height)
  {
    this->window_height = window_height;
  }

  int getWindowHeight()
  {
    return this->window_height;
  }
};
