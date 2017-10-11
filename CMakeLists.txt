cmake_minimum_required(VERSION 3.7)
project(Hors)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

include_directories(include)

set(SOURCE_FILES
    include/Camera.h
    include/HorsArgumentParser.h
    include/HorsConfig.h
    include/HorsProgram.h
    include/HydraExport.h
    include/LiteMath.h
    include/SkeletonVisualizer.h
    include/SurfaceVisualizer.h
    include/Utils.h
    src/Camera.cpp
    src/HorsArgumentParser.cpp
    src/HorsConfig.cpp
    src/HorsProgram.cpp
    src/HydraExport.cpp
    src/SkeletonVisualizer.cpp
    src/SurfaceVisualizer.cpp
    src/Utils.cpp
)

add_library(Hors STATIC ${SOURCE_FILES})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
add_definitions(${GLUT_DEFINITIONS})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
add_definitions(${GLEW_DEFINITIONS})

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${GLM_INCLUDE_DIRS})

add_subdirectory(Test)
add_subdirectory(Samples)
