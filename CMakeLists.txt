cmake_minimum_required(VERSION 3.22)

project(railbot)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Og -pipe")
add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
link_libraries(-fsanitize=address)
# set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -O3 -pipe")
set(CMAKE_EXE_LINKER_FLAGS " -no-pie")


include_directories(
  Src
)

file(GLOB_RECURSE _SRC Src/[^.]*.cpp)
add_executable(${PROJECT_NAME} ${_SRC})
target_link_libraries(${PROJECT_NAME} -pthread)
