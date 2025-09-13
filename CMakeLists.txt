cmake_minimum_required(VERSION 3.13)
project(Point-Game)

set(CMAKE_C_STANDARD 11)

include_directories(include/)

add_executable(Point-Game
    src/window.c
    src/player.c
)

find_package(SDL3 REQUIRED)
target_link_libraries(Point-Game PRIVATE SDL3::SDL3)
