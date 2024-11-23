cmake_minimum_required(VERSION 3.14)
project(Point-Game)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Point-Game
        src/main.c
        src/player.c
        src/draw.c
        src/map.c
)

find_package(SDL2)

target_link_libraries(Point-Game PRIVATE SDL2 SDL2main)

target_compile_definitions(Point-Game PRIVATE SDL_MAIN_HANDLED)