cmake_minimum_required(VERSION 3.10)

## project descirption
project(Arcade LANGUAGES CXX)

## set std 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## add executable to root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
# set path to lib 
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

# g++ flags 
set(CPP_GCC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic")

# set g++ flags 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_GCC_FLAGS}")

# exec name
set(EXEC_NAME arcade)

# all cpp file in src directory only
file(GLOB SOURCES src/*.cpp src/core/*.cpp src/core/menu/*.cpp src/core/score/*.cpp src/loader/*.cpp src/plugin/*.cpp src/graphics/transform/*.cpp src/graphics/objects/*.cpp src/graphics/cache/*.cpp)

# remove lib before in so name 
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

file(GLOB NCURSE_SRC src/graphics/libraries/ncurse/*.cpp src/graphics/objects/*.cpp src/graphics/cache/*.cpp src/plugin/*.cpp src/graphics/transform/*.cpp)
# create shared lib 
add_library(arcade_ncurses SHARED ${NCURSE_SRC})

file(GLOB SDL_SRC src/graphics/libraries/sdl/*.cpp src/graphics/objects/*.cpp src/graphics/cache/*.cpp src/plugin/*.cpp src/graphics/transform/*.cpp)
# create shared lib 
add_library(arcade_sdl2 SHARED ${SDL_SRC})

file(GLOB SFML_SRC src/graphics/libraries/sfml/*.cpp src/graphics/objects/*.cpp src/graphics/cache/*.cpp src/plugin/*.cpp src/graphics/transform/*.cpp)
add_library(arcade_sfml SHARED ${SFML_SRC})

# create shared lib games 
file(GLOB SNAKE_SRC src/games/snake/*.cpp src/graphics/objects/*.cpp src/plugin/*.cpp src/graphics/cache/*.cpp src/graphics/transform/*.cpp)
add_library(arcade_snake SHARED ${SNAKE_SRC})
#
file(GLOB PACMAN_SRC src/games/pacman/*.cpp src/graphics/objects/*.cpp src/plugin/*.cpp src/graphics/cache/*.cpp src/graphics/transform/*.cpp)
add_library(arcade_pacman SHARED ${PACMAN_SRC})
#
file(GLOB MINE_SRC src/games/minesweeper/*.cpp src/graphics/objects/*.cpp src/plugin/*.cpp src/graphics/cache/*.cpp src/graphics/transform/*.cpp)
add_library(arcade_minesweeper SHARED ${MINE_SRC})
# set(CMAKE_EXE_LINKER_FLAGS "-ldl")
add_executable(${EXEC_NAME} ${SOURCES})

# sdl lib
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# ncurse lib 
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

#sfml lib
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

target_link_libraries(arcade_sfml
    sfml-graphics
    sfml-window
    sfml-system
)

target_link_libraries(arcade_sdl2 ${SDL2_LIBRARIES} SDL2_image SDL2_ttf)
target_link_libraries(arcade_ncurses ncurses form)
