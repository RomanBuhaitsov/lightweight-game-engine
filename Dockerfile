FROM ubuntu:lunar-20230314

ENV VCPKG_FORCE_SYSTEM_BINARIES=1

RUN apt-get update

# install git to pull vcpkg
RUN apt install -y git-all

# install basic tools
RUN apt-get install -y curl wget zip unzip tar build-essential libssl-dev ninja-build

# install cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.1/cmake-3.26.1.tar.gz
RUN tar -zxvf cmake-3.26.1.tar.gz
RUN cd cmake-3.26.1 && ./bootstrap && make && make install

# clone vcpkg
RUN git clone https://github.com/Microsoft/vcpkg.git

# install vcpkg
RUN ./vcpkg/bootstrap-vcpkg.sh
RUN ln -s /vcpkg/vcpkg /usr/local/bin/vcpkg

WORKDIR /code
COPY ./src /code


RUN apt-get install -y pkg-config

# install dependencies
RUN vcpkg install

# build dependencies
RUN cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake

# build project
RUN cmake --build ./build

CMD ["./build/lightweight-game-engine"]


