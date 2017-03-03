cmake_minimum_required(VERSION 2.8)
project (RudyEngine)

add_subdirectory(engine)

include_directories(engine/external/glm/glm)
include_directories(engine/external/glad/include)
include_directories(engine/external/glfw/include)

# Game or demo proj
add_executable(DemoProject main.cpp)
target_link_libraries(DemoProject engine)