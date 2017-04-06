cmake_minimum_required(VERSION 2.8)
project (RudyEngine)
add_subdirectory(engine)

include_directories(engine/external/glm/)
include_directories(engine/external/glad/include)
include_directories(engine/external/glfw/include)
include_directories(engine/)

###############################################################################
####################### D E M O ###############################################
###############################################################################
add_executable(learnOpenGL demo/learnopengl/main.cpp)
target_link_libraries(learnOpenGL engine)
set_target_properties(learnOpenGL PROPERTIES COMPILE_FLAGS "-std=c++14")

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

###############################################################################
####################### T E S T S #############################################
###############################################################################
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
# Renderering tests
set(RENDERING_TESTS_DIR ${TESTS_DIR}/renderingTestFixture)
add_executable(renderingTest ${RENDERING_TESTS_DIR}/main.cpp ${RENDERING_TESTS_DIR}/BallBehaviour.cpp)
set_target_properties(renderingTest PROPERTIES COMPILE_FLAGS "-std=c++14")
target_link_libraries(renderingTest engine)

add_custom_command(TARGET renderingTest POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${RENDERING_TESTS_DIR}/shaders $<TARGET_FILE_DIR:renderingTest>/shaders)

add_custom_command(TARGET renderingTest POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${RENDERING_TESTS_DIR}/sprites $<TARGET_FILE_DIR:renderingTest>/sprites)