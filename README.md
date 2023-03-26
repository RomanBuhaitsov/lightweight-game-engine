# lightweight-game-engine

## Prerequisites
- vcpkg
- cmake
- c++ compiler std 17

## Build
Linux/Macos
All commands should be executed from project root directory.
Install dependencies:

```
cd src && vcpkg install && cd ..
```
Build dependencies:
```
cmake -B build -S ./src -DCMAKE_TOOLCHAIN_FILE=$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake
```
Build project:
```
cmake --build build
```

# Running project
From project root directory, run:
```
./build/lightweight-game-engine
```

# Building with docker
Create `.docker.env` with content listed out in `docker.env.example`

Build docker image
```
docker build -t "lge" .
```
Run docker image
```
docker run -it --env-file ".docker.env" lge
```

## Wiki
The system wiki is available under [this](https://github.com/RomanBuhaitsov/lightweight-game-engine/wiki) url.


## Log

### `11.12.2022`
- defined system architecture - more details [here](https://github.com/RomanBuhaitsov/lightweight-game-engine/wiki/Architecture)
- agreed not to use a standalone database, which increases latency. Data which needs to be stored persistently, will be serialized to invidual files.
- game objects - favor composition over inheritance
