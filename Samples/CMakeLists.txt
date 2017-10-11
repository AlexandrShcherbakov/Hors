cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)

project(SSAO)
set(SSAO_SOURCE_FILES SSAO.cpp)
add_executable(SSAO ${SSAO_SOURCE_FILES})
target_link_libraries(
        SSAO
        Hors
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARY}
        ${Boost_LIBRARIES}
)
