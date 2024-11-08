cmake_minimum_required(VERSION 3.10)

project(Point_Game)

set(CMAKE_C_STANDARD 11)

add_executable(Point_Game src/main.c)

find_package(SDL3 REQUIRED)

target_link_libraries(Point_Game PRIVATE SDL3::SDL3)