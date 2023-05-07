#pragma once
#include <stdlib.h>

class Config {
private:
  int framerate = atoiDefault(getenv("FRAMERATE"), 60);
  int max_frameskip = atoiDefault(getenv("MAX_FRAMESKIP"), 10);
  bool fullscreen = atoiDefault(getenv("FULLSCREEN"), 0);
  int window_width = atoiDefault(getenv("WINDOW_WIDTH"), 1280);
  int window_height = atoiDefault(getenv("WINDOW_HEIGHT"), 720);

  static int atoiDefault(const char *s, int default_value) {
    if (s == NULL) {
      return default_value;
    }
    return atoi(s);
  }

public:
  void setFramerate(int framerate) { this->framerate = framerate; }

  int getFramerate() { return this->framerate; }

  void setMaxFrameSkip(int max_frameskip) {
    this->max_frameskip = max_frameskip;
  }

  int getMaxFrameSkip() { return this->max_frameskip; }

  void setFullScreen(bool fullscreen) { this->fullscreen = fullscreen; }

  bool getFullScreen() { return this->fullscreen; }

  void setWindowWidth(int window_width) { this->window_width = window_width; }

  int getWindowWidth() { return this->window_width; }

  void setWindowHeight(int window_height) {
    this->window_height = window_height;
  }

  int getWindowHeight() { return this->window_height; }
};
