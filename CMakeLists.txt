cmake_minimum_required(VERSION 3.7)
project(Hors)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/HorsProgram.cpp include/HorsProgram.h include/HorsConfig.cpp include/HorsConfig.h)

add_library(Hors ${SOURCE_FILES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
add_definitions(${GLUT_DEFINITIONS})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
add_definitions(${GLEW_DEFINITIONS})


add_subdirectory(Test)
