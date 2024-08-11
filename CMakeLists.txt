cmake_minimum_required(VERSION 3.28)
project(Point-Game C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
add_subdirectory(src)

target_link_libraries(Point-Game
        mingw32
        SDL2main
        SDL2
)
