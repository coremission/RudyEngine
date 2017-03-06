cmake_minimum_required(VERSION 2.8)

set(GLFW_SOURCE_DIR "external/glfw")
set(GLM_SOURCE_DIR  "external/glm")
set(GLAD_SOURCE_DIR "external/glad")

# Building only the GLFW lib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")

add_subdirectory(${GLFW_SOURCE_DIR})

include_directories(${GLAD_SOURCE_DIR}/include
                    ${GLFW_SOURCE_DIR}/include
                    ${GLFW_SOURCE_DIR}/deps
                    ${GLM_SOURCE_DIR})

add_library(glad STATIC ${GLAD_SOURCE_DIR}/src/glad.c)

# Rudy Engine set up
add_library(engine Engine.cpp)
target_link_libraries(engine glfw ${GLFW_LIBRARIES} glad)
