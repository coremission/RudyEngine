cmake_minimum_required(VERSION 2.8)
project (RudyEngine)
add_subdirectory(engine)

include_directories(engine/external/glm/)
include_directories(engine/external/glad/include)
include_directories(engine/external/glfw/include)
include_directories(engine/)

# test project
add_executable(DemoProject main.cpp)
target_link_libraries(DemoProject engine)
set_target_properties(DemoProject PROPERTIES COMPILE_FLAGS "-std=c++14")

# Games
set(GAMES_DIR games)
# Classic Breakout Game
set(BREAKOUT_DIR ${GAMES_DIR}/breakout)
set(BREAKOUT_SRC ${BREAKOUT_DIR}/main.cpp ${BREAKOUT_DIR}/BallBehaviour.cpp ${BREAKOUT_DIR}/BrickBehaviour.cpp ${BREAKOUT_DIR}/Controller.cpp ${BREAKOUT_DIR}/PaddleBehaviour.cpp)

add_executable(breakout ${BREAKOUT_SRC})
set_target_properties(breakout PROPERTIES COMPILE_FLAGS "-std=c++14")
target_link_libraries(breakout engine)