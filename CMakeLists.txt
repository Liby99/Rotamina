# CMakeList.txt
# author: Liby Lee
# date: Jan 15, 2018

# Basic setups
cmake_minimum_required(VERSION 3.5)
project(CSE169-Animator)

# Basic flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Include NanoGui
add_subdirectory(lib/nanogui EXCLUDE_FROM_ALL)
include_directories(lib/nanogui/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})

# =========================================================================== #

# Set Include Directory to Extern
include_directories(src/extern)

# Compile all the cpp files and link to `animator` library along with NanoGui
file(GLOB animator_sources src/intern/*/*.cpp)
set(animator ${animator_sources})
add_library(animator ${animator})
target_link_libraries(animator nanogui ${NANOGUI_EXTRA_LIBS})

# Compile all the test files
file(GLOB test_sources test/*.cpp test/*/*.cpp test/*/*/*.cpp)
foreach(test_source ${test_sources})
    string(REPLACE ".cpp" "" temp_path ${test_source})
    string(REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "" temp_path ${temp_path})
    get_filename_component(temp_dir ${temp_path} DIRECTORY)
    get_filename_component(temp_name ${temp_path} NAME)
    set(EXECUTABLE_OUTPUT_PATH ${temp_dir})
    add_executable(${temp_name} ${test_source})
    target_link_libraries(${temp_name} animator)
endforeach(test_source ${test_sources})
