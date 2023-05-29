#include "level_builder.h"
// void Level::saveAsJson() {
//   json data;

//   std::string path=std::string("../static/levels/"+name+".json"); 
//   std::map<std::string, Entity*> entities;
//   for(auto &entity: this->game_window->entities){
//     data.push_back((*entity).to_json());
//   }
//   std::ofstream file(path);
//   file << data;
// }

void LevelBuilder::setBackground(std::string texture)
{
  SDL_Texture *background = game_window->texture_manager[texture];
  game_window->setBackgroundTexture(background);
  game_window->getDebugDraw()->SetFlags(b2Draw::e_shapeBit);
  game_window->world->SetDebugDraw(game_window->getDebugDraw());
}

void LevelBuilder::addPlayer(std::string texture, int pos_x, int pos_y){
  Entity *player = EntityFactory::createPlayer(
      pos_x, pos_y, game_window->texture_manager[texture],
      game_window->getMessageBus());
  game_window->entities.insert(player);
  game_window->getCamera()->followEntity(player, true); // make the camera follow the player
}

void LevelBuilder::addAnimation(std::string texture, int pos_x, int pos_y, int speed, unsigned short cols, unsigned short rows, std::string track, int width, int lenght){
  Entity *animation = EntityFactory::createAnimation(
    pos_x, pos_y, game_window->texture_manager[texture],
    game_window->getMessageBus(), speed, {cols,rows}, track, width, lenght);
  game_window->entities.insert(animation);
}

void LevelBuilder::addTile(std::string texture, int pos_x, int pos_y){
  game_window->entities.insert(
    EntityFactory::createTile(pos_x, pos_y, 
    game_window->texture_manager[texture],
    game_window->getMessageBus()));
}

void LevelBuilder::addCoin(std::string texture, int pos_x, int pos_y){
  game_window->entities.insert(
    EntityFactory::createCoin(pos_x, pos_y, 
    game_window->texture_manager["coin.png"], 
    game_window->getMessageBus()));
}

void LevelBuilder::addWithLineFunction(std::string texture, int interval, int start_x, int start_y, int end_x, int end_y,
 std::function<void(std::string, int, int)> addObject){
    int distance_x = end_x - start_x;
    int distance_y = end_y - start_y;

    int num_objects = std::max(std::abs(distance_x), std::abs(distance_y)) / interval;
    int x_step = distance_x / num_objects;
    int y_step = distance_y / num_objects;

    double x = start_x;
    double y = start_y;
    for (int i = 0; i <= num_objects; ++i) {
        addObject(texture, x, y);
        x+=x_step;
        y+=y_step;
    }
}

LevelBuilder::LevelBuilder(GameWindow *game_window, MessageBus *message_bus) : BusNode(message_bus), game_window(game_window){}

LevelBuilder::~LevelBuilder(){}

Level* LevelBuilder::createFromJson(std::string path)
{
  try {
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "Cannot open file with path:" <<path << "\n";
        return new Level("ERROR", game_window, messageBus);
    }
    json data = json::parse(f);
    Level* newLevel = new Level(data["name"], game_window, messageBus);
    this->setBackground(data["backgorundImage"]);
    this->addPlayer(data["player"]["texture"], data["player"]["x"], data["player"]["y"]);
    
    for(auto& animation: data["animations"]){
      int x = animation["x"];
      int y = animation["y"];
      unsigned short width = animation["width"];
      unsigned short length = animation["length"];
      std::string texture = animation["texture"];
      int speed = animation["speed"];
      int cols = animation["frames_column"];
      int rows = animation["frames_row"];
      std::string track = animation["track"];
      this->addAnimation(texture, x, y, speed, cols, rows, track, width, length);
    }

    std::string coinTexture = data["coin"]["texture"];
    for (const auto& position : data["coin"]["positions"])
        addCoin(coinTexture, position["x"], position["y"]);
    
    for (const auto& function : data["coin"]["functions"]){
      addWithLineFunction(coinTexture, 
      function["interval"],
      function["params"]["start_x"],
      function["params"]["start_y"],
      function["params"]["end_x"],
      function["params"]["end_y"],
      [this](std::string texture, int interval, int start_x){
        addCoin(texture, interval, start_x);
      });
    }
    
    std::string tileTexture = data["tile"]["texture"];
    for (const auto& function : data["tile"]["functions"]){
      addWithLineFunction(tileTexture, 
      function["interval"],
      function["params"]["start_x"],
      function["params"]["start_y"],
      function["params"]["end_x"],
      function["params"]["end_y"],
      [this](std::string texture, int interval, int start_x){
        addTile(texture, interval, start_x);
      });
    }

    return newLevel;
  } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return new Level("ERROR", game_window, messageBus);
  }
}
