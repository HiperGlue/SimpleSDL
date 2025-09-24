cmake_minimum_required(VERSION 3.10.0)
project(SIMPLESDL VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

include_directories(include)

file(GLOB SIMPLESDL_SOURCES "src/SIMPLESDL/*.cpp")
file(GLOB SIMPLESDL_HEADERS "include/SIMPLESDL/*.hpp")

add_library(SIMPLESDL STATIC ${SIMPLESDL_SOURCES} ${SIMPLESDL_HEADERS})

target_link_libraries(SIMPLESDL SDL3 SDL3_image)

target_include_directories(SIMPLESDL PUBLIC ${CMAKE_SOURCE_DIR}/include)