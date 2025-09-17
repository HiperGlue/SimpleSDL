cmake_minimum_required(VERSION 3.10.0)
project(sdl3 VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

include_directories(include)

add_subdirectory(src/SIMPLESDL)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-local.txt)
    include(CMakeLists-local.txt)
endif()
