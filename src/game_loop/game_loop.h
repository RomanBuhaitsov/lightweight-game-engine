
class GameLoop
{
private:
  int framerate;
  int max_frameskip;
  int skip_ticks;
  int execution_start_time;

  void handleEvents(){};
  void update(){};
  void render(){};

protected:
  bool game_running; // TODO: consider moving this field to a more global scope

public:
  GameLoop(int framerate, int max_frameskip);
  GameLoop(){};
  ~GameLoop(){};

  void run();
};
