cmake_minimum_required(VERSION 2.8)

# 1. GLFW
# Include GLFW with disabled tests and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# 2. GLEW
#
add_library(glew STATIC external/glew/src/glew.c external/glew/include)
add_definitions(
  -DGLEW_STATIC
)

# 3. Add include directories
#
include_directories(external/glm/glm) # glm is header based library, no need to build
include_directories(external/glew/include)
include_directories(external/glfw/include)

add_library(engine Engine.cpp)

target_link_libraries(engine glfw glew)
