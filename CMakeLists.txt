cmake_minimum_required(VERSION 3.13)
project(Point-Game)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include/)

add_executable(Point-Game
    src/window.c
    src/player.c
    src/camera.c
    src/map.c
    src/bullet.c
    src/painter.c
    src/infoLabel.c
)

file(COPY sources/fusion-pixel-10px-monospaced-zh_hans.ttf DESTINATION ${CMAKE_BINARY_DIR}/sources/)
file(COPY sources/map.txt DESTINATION ${CMAKE_BINARY_DIR}/sources/)

find_package(SDL3 REQUIRED)
target_link_libraries(Point-Game PRIVATE SDL3::SDL3)

find_package(SDL3_ttf REQUIRED)
target_link_libraries(Point-Game PRIVATE SDL3_ttf::SDL3_ttf)
