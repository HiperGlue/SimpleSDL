file(GLOB SIMPLESDL_SOURCES "*.cpp")
file(GLOB SIMPLESDL_HEADERS "../../include/ENGINE/*.h")

add_library(SIMPLESDL STATIC ${SIMPLESDL_SOURCES} ${SIMPLESDL_HEADERS})

target_link_libraries(SIMPLESDL SDL3 SDL3_image)

target_include_directories(SIMPLESDL PUBLIC ${CMAKE_SOURCE_DIR}/include)