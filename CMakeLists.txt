project("libhercules" C) 
cmake_minimum_required(VERSION 3.0)

if(EXISTS "${TOP_DIRECTORY}/.git" AND NOT EXISTS "${TOP_DIRECTORY}/libs/unity/CMakeLists.txt")
    message (FATAL_ERROR "Submodules are not initialized. Run\n\tgit submodule update --init --recursive")
endif()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(libs)

add_library(list_library SHARED
    libs/list.c
)

add_library(object_library SHARED
    src/object.c
)

add_subdirectory(libs/unity)
add_subdirectory(libs/test) 

