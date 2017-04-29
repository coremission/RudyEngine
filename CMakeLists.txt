cmake_minimum_required(VERSION 3.2)
include(CMakeFunctions.txt)

project (RudyEngine)
add_subdirectory(engine)

include_directories(engine/external/glm/)
include_directories(engine/external/assimp/include)
include_directories(engine/external/glad/include)
include_directories(engine/external/glfw/include)
include_directories(engine/)

###############################################################################
####################### D E M O ###############################################
###############################################################################
# Learn OpenGL Demo
add_executable(learnOpenGL demo/learnopengl/main.cpp)
target_link_libraries(learnOpenGL engine)
set_target_properties(learnOpenGL PROPERTIES COMPILE_FLAGS "-std=c++14")

# Spaceship Demo
set(SPACESHIP_DIR demo/spaceship)
set(SPACESHIP_SRC ${SPACESHIP_DIR}/main.cpp ${SPACESHIP_DIR}/MoveBehaviour.cpp ${SPACESHIP_DIR}/CameraController.cpp ${SPACESHIP_DIR}/MarkerController.cpp ${SPACESHIP_DIR}/RotationBehaviour.cpp)
add_executable(spaceship ${SPACESHIP_SRC})
set_target_properties(spaceship PROPERTIES COMPILE_FLAGS "-std=c++14")
target_link_libraries(spaceship engine)
targetPostBuildCopyDir(spaceship ${SPACESHIP_DIR}/shaders shaders)
targetPostBuildCopyDir(spaceship ${SPACESHIP_DIR}/sprites sprites)
targetPostBuildCopyDir(spaceship ${SPACESHIP_DIR}/assets assets)

###############################################################################
####################### G A M E S #############################################
###############################################################################
set(GAMES_DIR games)
# Classic Breakout Game
set(BREAKOUT_DIR ${GAMES_DIR}/breakout)
set(BREAKOUT_SRC ${BREAKOUT_DIR}/main.cpp ${BREAKOUT_DIR}/BallBehaviour.cpp ${BREAKOUT_DIR}/BrickBehaviour.cpp ${BREAKOUT_DIR}/Controller.cpp ${BREAKOUT_DIR}/PaddleBehaviour.cpp)

add_executable(breakout ${BREAKOUT_SRC})
set_target_properties(breakout PROPERTIES COMPILE_FLAGS "-std=c++14")
target_link_libraries(breakout engine)
targetPostBuildCopyDir(breakout ${BREAKOUT_DIR}/shaders shaders)
targetPostBuildCopyDir(breakout ${BREAKOUT_DIR}/sprites sprites)

###############################################################################
####################### T E S T S #############################################
###############################################################################
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
# Renderering tests
set(RENDERING_TESTS_DIR ${TESTS_DIR}/renderingTestFixture)
add_executable(renderingTest ${RENDERING_TESTS_DIR}/main.cpp ${RENDERING_TESTS_DIR}/BallBehaviour.cpp ${RENDERING_TESTS_DIR}/CameraController.cpp)
set_target_properties(renderingTest PROPERTIES COMPILE_FLAGS "-std=c++14")
target_link_libraries(renderingTest engine)

targetPostBuildCopyDir(renderingTest ${RENDERING_TESTS_DIR}/shaders shaders)
targetPostBuildCopyDir(renderingTest ${RENDERING_TESTS_DIR}/sprites sprites)
