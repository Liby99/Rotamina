cmake_minimum_required(VERSION 3.5)
project(my_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(lib/nanogui)
include_directories(lib/nanogui/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})

include_directories(src/extern)

file(GLOB animator_sources src/intern/*/*.cpp)
SET(animator ${animator_sources})
add_library(animator ${animator})
target_link_libraries(animator nanogui ${NANOGUI_EXTRA_LIBS})

add_executable(my_test test/my_test.cpp)
target_link_libraries(my_test animator)
