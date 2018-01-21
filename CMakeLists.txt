cmake_minimum_required(VERSION 3.0)
project(worm-brain)

# Require -std=c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Require threads
find_package(Threads REQUIRED)

# Require OpenGL
find_package(OpenGL REQUIRED)

# Require GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
string(STRIP ${GLEW_LIBRARIES} GLEW_LIBRARIES)

# Require SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

# Find SDL2_mixer
find_library(SDL2_MIXER_LIBRARIES
  NAMES SDL2_mixer
  PATH_SUFFIXES lib
)

# SnowEngine Library
set(SNOW_ENGINE_LIBRARY "-L${PROJECT_SOURCE_DIR}/lib/snow-engine/debug/ -lSnowEngine")

# Find Box2D
find_library(BOX2D_LIBRARIES
  NAMES Box2D
  PATH_SUFFIXES lib
)

# Inlcude dirs
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

set(srcs Button.cpp Button.h Creature.cpp Creature.h Game.cpp Game.h GenerationScreen.cpp GenerationScreen.h main.cpp MainScreen.cpp MainScreen.h Matrix.h MultiGenScreen.cpp MultiGenScreen.h NeuralNetwork.cpp NeuralNetwork.h Population.cpp Population.h PreviewWindow.cpp PreviewWindow.h)

add_subdirectory(src)