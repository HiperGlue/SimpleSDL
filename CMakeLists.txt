cmake_minimum_required(VERSION 3.10.0)
project(sdl2 VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(include)

add_subdirectory(src/ENGINE)

if(EXISTS "src/GAME")
    add_subdirectory(src/GAME)
endif()
