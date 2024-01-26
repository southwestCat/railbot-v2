cmake_minimum_required(VERSION 3.22)

project(railbot)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Og -pipe")
add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
## strict compile options
# add_compile_options(-std=c++20 -Og -pipe -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror -fsanitize=undefined,address -fno-omit-frame-pointer -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wformat=2 -Wimport -Winvalid-pch -Wlogical-op -Wmissing-declarations -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wpointer-arith -Wredundant-decls -Wstack-protector -Wstrict-null-sentinel -Wswitch-enum -Wundef -Wwrite-strings)
link_libraries(-fsanitize=address)
# set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -O2 -pipe")
set(CMAKE_EXE_LINKER_FLAGS " -no-pie")


include_directories(
  Src
)

file(GLOB_RECURSE _SRC Src/[^.]*.cpp)
add_executable(${PROJECT_NAME} ${_SRC})
target_link_libraries(${PROJECT_NAME} -pthread)
