cmake_minimum_required(VERSION 3.16.3)
project(Breakout)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

file(GLOB_RECURSE BREAKOUT_SOURCE "src/*.c")

add_executable(${PROJECT_NAME} ${BREAKOUT_SOURCE})

target_link_libraries(${PROJECT_NAME} SDL2main SDL2_ttf SDL2)
target_link_libraries(${PROJECT_NAME} m)