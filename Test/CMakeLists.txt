cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 14)
set(TEST_SOURCE_FILES DataGenerator.cpp DataGenerator.h)

project(TestSurfaceVisualizer)
set(SURFACE_VISUALIZER_SOURCE_FILES TestSurfaceVisualizer.cpp ${TEST_SOURCE_FILES})
add_executable(TestSurfaceVisualizer ${SURFACE_VISUALIZER_SOURCE_FILES})
target_link_libraries(
        TestSurfaceVisualizer
        Hors
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARY}
        ${Boost_LIBRARIES}
)

project(TestSkeletonVisualizer)
set(SKELETON_VISUALIZER_SOURCE_FILES TestSkeletonVisualizer.cpp ${TEST_SOURCE_FILES})
add_executable(TestSkeletonVisualizer ${SKELETON_VISUALIZER_SOURCE_FILES})

target_link_libraries(
        TestSkeletonVisualizer
        Hors
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLEW_LIBRARY}
        ${Boost_LIBRARIES}
)