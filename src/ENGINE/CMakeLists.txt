file(GLOB ENGINE_SOURCES "*.cpp")
file(GLOB ENGINE_HEADERS "../../include/ENGINE/*.h")

add_library(ENGINE STATIC ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_link_libraries(ENGINE SDL2 SDL2_image)

target_include_directories(ENGINE PUBLIC ${CMAKE_SOURCE_DIR}/include)