# lightweight-game-engine

## Wiki
The system wiki is available under [this](https://github.com/RomanBuhaitsov/lightweight-game-engine/wiki) url.

## Gantt diagram
![alt text](/Documentation/gantt.png "Roadmap")


## Log

### `11.12.2022`
- defined system architecture - more details [here](https://github.com/RomanBuhaitsov/lightweight-game-engine/wiki/Architecture)
- agreed not to use a standalone database, which increases latency. Data which needs to be stored persistently, will be serialized to invidual files.
- game objects - favor composition over inheritance
