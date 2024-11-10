cmake_minimum_required(VERSION 3.10)

project(Point-Game C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(Point-Game
    src/main.c
    src/draw.c)

find_package(SDL3 REQUIRED)

target_link_libraries(Point-Game PRIVATE SDL3::SDL3)