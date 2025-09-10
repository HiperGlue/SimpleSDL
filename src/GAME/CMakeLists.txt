file(GLOB GAME_SOURCES "*.cpp")
file(GLOB GAME_HEADERS "../../include/GAME/*.h")

add_executable(sdl2 ${GAME_SOURCES} ${GAME_HEADERS})

target_link_libraries(sdl2 ENGINE SDL2 SDL2_image)

target_include_directories(sdl2 PUBLIC ${CMAKE_SOURCE_DIR}/include)

