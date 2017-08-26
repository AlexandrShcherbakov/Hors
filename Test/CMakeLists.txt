cmake_minimum_required(VERSION 3.7)
project(TestApp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(TestApp ${SOURCE_FILES})

target_link_libraries(
        TestApp
        Hors
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARY}
        ${Boost_LIBRARIES}
)